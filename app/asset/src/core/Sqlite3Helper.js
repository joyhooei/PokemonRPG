/**
 * Created by Maple on 8/21/15.
 */

var Sqlite3Helper = {
    executeQuery: function (sql) {
        if (this._db == null) {
            this._db = mw.SqliteDb.openDb(DB_PATH);
        }
        return this._db.executeQuery(sql);
    },
    getPokemonInfo: function (id) {
        if (this._db == null) {
            this._db = mw.SqliteDb.openDb(DB_PATH);
        }
        var sql = cc.formatStr("select * from [pet_info] where [id] = '%d';", parseInt(id));
        var query = this._db.executeQuery(sql);
        if (query && query.length > 0) {
            var data = query[0];
            var needParseIntList = [ "id", "height", "weight", "evolution" ];
            this._parseIntForData(data, needParseIntList);
            var needSplitAndParseIntList = [ "property", "speciality", "racial", "machineSkills", "heredSkills", "fixedSkills" ];
            this._splitAndParseIntForData(data, needSplitAndParseIntList);
            // 升级技能 [ [lv, skillId], ... ]
            data["levelUpSkills"] = data["levelUpSkills"].split(",").map(function (item, index, ary) {
                return item.split(":").map(function (item2, index2, ary2) {
                    return parseInt(item2);
                })
            });
            // 努力值 { prop: val, ... }
            var hardValueMap = new Object();
            var ary = data["hardValue"].split(";").map(function (item, index, ary) {
                return item.split(",").map(function (item2, index2, ary2) {
                    return parseInt(item2);
                })
            });
            for (var i in ary) {
                var vals = ary[i];
                hardValueMap[vals[0]] = vals[1];
            }
            data["hardValue"] = hardValueMap;
            return data;
        }
        return null;
    },
    getSkillInfo: function (id) {
        if (this._db == null) {
            this._db = mw.SqliteDb.openDb(DB_PATH);
        }
        var sql = cc.formatStr("select * from [skill_info] where [id] = '%d';", parseInt(id));
        var query = this._db.executeQuery(sql);
        if (query && query.length > 0) {
            var data = query[0];
            var needParseIntList = [ "id", "property", "type", "attack", "hitRate", "pp", "target" ];
            this._parseIntForData(data, needParseIntList);
            // 不知为何会有换行符 把它去掉
            data["description"] = data["description"].trim();
            return data;
        }
        return null;
    },
    _parseIntForData: function (data, propList) {
        for (var i = 0; i < propList.length; ++i) {
            var key = propList[i];
            if (data[key] && data[key].trim().length > 0) {
                data[key] = parseInt(data[key]);
            } else {
                data[key] = null;
            }
        }
    },
    _splitAndParseIntForData: function (data, propList) {
        for (var i = 0; i < propList.length; ++i) {
            var key = propList[i];
            if (data[key] && data[key].trim().length > 0) {
                data[key] = data[key].split(",").map(function (item, index, ary) {
                    return parseInt(item);
                });
            } else {
                data[key] = [];
            }
        }
    },
    _db: null,
};
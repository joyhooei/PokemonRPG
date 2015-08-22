/**
 * Created by Maple on 8/21/15.
 */

var Sqlite3Helper = {
    getPokemonInfo: function (id) {
        var sql = cc.formatStr("select * from [pet_info] where [id] = '%d';", parseInt(id));
        var query = this._db.executeQuery(sql);
        if (query && query.length > 0) {
            var data = query[0];
            var needParseIntList = [ "id", "height", "weight", "evolution" ];
            this._parseIntForData(data, needParseIntList);
            var needSplitAndParseIntList = [ "property", "speciality", "racial", "levelUpSkills", "machineSkills", "heredSkills", "fixedSkills" ];
            this._splitAndParseIntForData(data, needSplitAndParseIntList);
            data["hardValue"] = data["hardValue"].split(";").map(function (item, index, ary) {
                return item.split(",").map(function (item2, index2, ary2) {
                    return parseInt(item2);
                })
            });
            return data;
        }
        return null;
    },
    _parseIntForData: function (data, propList) {
        for (var i = 0; i < propList.length; ++i) {
            var key = propList[i];
            if (data[key] && data[key].length > 0) {
                data[key] = parseInt(data[key]);
            } else {
                data[key] = null;
            }
        }
    },
    _splitAndParseIntForData: function (data, propList) {
        for (var i = 0; i < propList.length; ++i) {
            var key = propList[i];
            if (data[key] && data[key].length > 0) {
                data[key] = data[key].split(",").map(function (item, index, ary) {
                    return parseInt(item);
                });
            } else {
                data[key] = [];
            }
        }
    },
    _db: mw.SqliteDb.openDb(DB_PATH),
};
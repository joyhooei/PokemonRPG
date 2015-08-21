/**
 * Created by Maple on 8/21/15.
 */

var PokemonInfo = ModelBase.extend({
    ctor: function (id) {
        // 定义model结构
        this._defineScheme({
            id: [ "number", 0 ],    // id
            name: [ "string", null ],   // 名称
            property: [function (val) {
                return val instanceof Array;
            }],     // 属性
            speciality: [function (val) {
                return val instanceof Array;
            }],     // 特性
            type: [ "string", null ],   // 类型
            height: [ "number", 0 ],    // 高度
            weight: [ "number", 0 ],    // 体重
            racial: [function (val) {
                return val instanceof Array;
            }],     // 种族值
            description: [ "string", null ],    // 图鉴描述
            hardValue: [function (val) {
                return val instanceof Array;
            }],     // 可获取的努力值
            levelUpSkills: [function (val) {
                return val instanceof Array;
            }],     // 升级可学习的技能
            machineSkills: [function (val) {
                return val instanceof Array;
            }],     // 可学习的机器技能
            heredSkills: [function (val) {
                return val instanceof Array;
            }],     // 可遗传学习的技能
            fixedSkills: [function (val) {
                return val instanceof Array;
            }],     // 可定点学习的技能
            evolution: [function (val) {
                return typeof val == "number" || val == null;
            }],     // 进化id
        });

        var data = Sqlite3Helper.getPokemonInfo(id);

        // 初始化
        this._setProperties({
            id: data["id"],
            name: data["name"],
            property: data["property"],
            speciality: data["speciality"],
            type: data["type"],
            height: data["height"],
            weight: data["weight"],
            racial: data["racial"],
            description: data["description"],
            hardValue: data["hardValue"],
            levelUpSkills: data["levelUpSkills"],
            machineSkills: data["machineSkills"],
            heredSkills: data["heredSkills"],
            fixedSkills: data["fixedSkills"],
            evolution: data["evolution"],
        });
    },
    getName: function () {
        return this._name;
    },
    getProperties: function () {
        return this._property;
    },
    getSpecialities: function () {
        return this._speciality;
    },
    getType: function () {
        return this._type;
    },
    getHeight: function () {
        return this._height;
    },
    getWeight: function () {
        return this._weight;
    },
    getRacialValues: function () {
        return this._racial;
    },
    getDescription: function () {
        return this._description;
    },
    getHardValues: function () {
        return this._hardValue;
    },
    getLevelUpSkills: function () {
        return this._levelUpSkills;
    },
    getMachineSkills: function () {
        return this._machineSkills;
    },
    getHeredSkills: function () {
        return this._heredSkills;
    },
    getFixedSkills: function () {
        return this._fixedSkills;
    },
    getEvolution: function () {
        return this._evolution;
    },
});
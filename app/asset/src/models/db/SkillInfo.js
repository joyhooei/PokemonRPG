/**
 * Created by Maple on 9/4/15.
 */

var SkillInfo = ModelBase.extend({
    ctor: function (id) {
        // 定义model结构
        this._defineScheme({
            id: [ "number", 0 ],    // id
            name: [ "string", null ],   // 名称
            property: [function (val) {
                return typeof val == "number" && val >= PROPERTIES.NORMAL && val <= PROPERTIES.DARK;
            }, PROPERTIES.NORMAL],      // 技能属性
            type: [function (val) {
                return typeof val == "number" && val >= SKILL_TYPES.PHYSICAL && val <= SKILL_TYPES.VARIATION;
            }, SKILL_TYPES.VARIATION],  // 技能类型
            attack: [function (val) {
                return typeof val == "number" && val >= 0;
            }, 0],  // 技能攻击力
            hitRate: [function (val) {
                return typeof val == "number" && val >= 0;
            }, 0],  // 技能命中率
            pp: [ "number", 0 ],    // 默认pp
            target: [function (val) {
                return typeof val == "number" && val >= SKILL_TARGET_TYPES.SINGLE_ENEMY && val <= SKILL_TARGET_TYPES.ANY;
            }, SKILL_TARGET_TYPES.SINGLE_ENEMY],    // 技能目标类型
            description: [ "string", null ],    // 技能描述
            handler: [ "string", null ],    // 技能处理函数
            params: [ "string", null ],     // 技能参数
        });

        var data = Sqlite3Helper.getSkillInfo(id);

        // 初始化
        this._setProperties({
            id: data["id"],
            name: data["name"],
            property: data["property"],
            type: data["type"],
            attack: data["attack"],
            hitRate: data["hitRate"],
            pp: data["pp"],
            target: data["target"],
            description: data["description"],
            handler: data["handler"],
            params: data["params"],
        });
    },
    getName: function () {
        return this._name;
    },
    getProperty: function () {
        return this._property;
    },
    getType: function () {
        return this._type;
    },
    getAttack: function () {
        return this._attack;
    },
    getHitRate: function () {
        return this._hitRate;
    },
    getPP: function () {
        return this._pp;
    },
    getTarget: function () {
        return this._target;
    },
    getDescription: function () {
        return this._description;
    },
    getHandler: function () {
        return this._handler;
    },
    getParams: function () {
        return this._params;
    }
});
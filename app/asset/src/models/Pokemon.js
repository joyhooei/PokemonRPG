/**
 * Created by Maple on 8/19/15.
 */

var Pokemon = ModelBase.extend({
    /**
     * properties必须拥有id 其他key值为缺省参数 列表如下:
     * id: pokemon id
     * gender: 性别
     * level: 等级
     * personality: 性格
     * shiny: 是否闪光
     * @param properties
     */
    ctor: function (properties) {
        // 定义model结构
        this._defineScheme({
            id: [ "number", 0 ],        // id
            gender: [function (val) {
                return (typeof val == "number" && val >= GENDER.MALE && val <= GENDER.FEMALE) || val === null;
            }, GENDER.MALE ],       // 性别
            level: [function (val) {
                return typeof val == "number" && val > 0;
            }, 1],     // 等级
            exp: [function (val) {
                return typeof val == "number" && val > 0;
            }, 0],     // 经验值
            state: [function (val) {
                return val >= POKEMON_STATES.NORMAL && val <= POKEMON_STATES.DEAD;
            }, POKEMON_STATES.NORMAL ],     // 异常状态
            battleState: [function (val) {
                return val >= BATTLE_STATES.NORMAL && val <= BATTLE_STATES.TIRED;
            }, BATTLE_STATES.NORMAL ],     // 战斗状态
            personality: [function (val) {
                return val >= POKEMON_PERSONALITIES.HARDY && val <= POKEMON_PERSONALITIES.CAREFUL;
            }, POKEMON_PERSONALITIES.HARDY ],     // 性格
            basicValues: [function (val) {
                return val instanceof Array;
            }, [ 0, 0, 0, 0, 0, 0 ]],     // 基础属性值
            talentValues: [function (val) {
                return val instanceof Array;
            }, [ 0, 0, 0, 0, 0, 0 ]],     // 个体值
            hardValues: [function (val) {
                return val instanceof Array;
            }, [ 0, 0, 0, 0, 0, 0 ]],     // 努力值
            shiny: [ "boolean", false ],    // 闪光
        });

        var rd = Math.ceil(Math.random() * 10000);
        var isShiny = rd == 1;
        var randomTalents = [];
        for (var i = 0; i < 6; ++i) {
            rd = Math.floor(Math.random() * 32);
            randomTalents.push(rd);
        }
        cc.log(randomTalents.toString());

        // 初始化
        var lv = properties["level"] || 1;
        var exp = this._getExpAtLv(lv);
        this._setProperties({
            id: properties["id"],
            gender: properties["gender"] || Math.ceil(Math.random() * 2),
            level: lv,
            exp: exp,
            personality: properties["personality"] || Math.floor(Math.random() * 25),
            talentValues: randomTalents,
            shiny: isShiny,
        });

        var fmtId = this._id.toString();
        var len = fmtId.length;
        for (var i = 0; i < 3 - len; ++i) {
            fmtId = "0" + fmtId;
        }
        this._fmtId = fmtId;
    },
    getInfo: function () {
        if (!this._infoModel) {
            this._infoModel = new PokemonInfo(this._id);
        }
        return this._infoModel;
    },
    getFormatedId: function () {
        return this._fmtId;
    },
    getGender: function () {
        return this._gender;
    },
    getLevel: function () {
        return this._level;
    },
    getExp: function () {
        return this._exp;
    },
    getState: function () {
        return this._state;
    },
    getBattleState: function () {
        return this._battleState;
    },
    getPersonality: function () {
        return this._personality;
    },
    isShiny: function () {
        return this._shiny;
    },
    getExpPercent: function () {
        return (this._exp - this._getExpAtLv(this._level)) / (this._getExpAtLv(this._level + 1) - this._getExpAtLv(this._level)) * 100;
    },
    getRestExpToLvUp: function () {
        return this._getExpAtLv(this._level + 1) - this._exp;
    },
    _getExpAtLv: function (lv) {
        return lv * lv * lv;
    },
    _infoModel: null,
});
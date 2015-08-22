/**
 * Created by Maple on 8/19/15.
 */

var Pokemon = ModelBase.extend({
    /**
     * properties必须拥有id 其他key值为缺省参数 列表如下:
     * id: pokemon id
     * gender: 性别
     * @param properties
     */
    ctor: function (properties) {
        // 定义model结构
        this._defineScheme({
            id: [ "number", 0 ],        // id
            gender: [function (val) {
                return typeof val == "number" && val >= GENDER.MALE && val <= GENDER.FEMALE;
            }, GENDER.MALE ],       // 性别
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
            }],     // 基础属性值
            talentValues: [function (val) {
                return val instanceof Array;
            }],     // 个体值
            hardValues: [function (val) {
                return val instanceof Array;
            }],     // 努力值
            shiny: [ "boolean", false ],    // 闪光
        });

        var rd = Math.ceil(Math.random() * 4);
        var isShiny = rd == 1;

        // 初始化
        this._setProperties({
            id: properties["id"],
            gender: properties["gender"] || Math.ceil(Math.random() * 2),
            shiny: isShiny,
        });

        var fmtId = this._id.toString();
        var len = fmtId.length;
        for (var i = 0; i < 3 - len; ++i) {
            fmtId = "0" + fmtId;
        }
        this._fmtId = fmtId;
    },
    getFormatedId: function () {
        return this._fmtId;
    },
    getGender: function () {
        return this._gender;
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
});
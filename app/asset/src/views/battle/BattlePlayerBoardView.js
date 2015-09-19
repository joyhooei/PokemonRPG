/**
 * Created by Maple on 8/20/15.
 */

var BattlePlayerBoardView = BattleEnemyBoardView.extend({
    CCS_NAMES: {
        EXP_BAR: "exp_bar",
        BOARD_BG: "board_bg",
            POKEMON_NAME: "pokemon_name",
            ICON_GENDER: "icon_gender",
            ICON_STATE: "icon_state",
            POKEMON_LEVEL: "pokemon_lv",
            HP_BAR: "hp_bar",
            HP_INFO: "hp_info",
    },
    ctor: function (model) {
        this._super(model);

        this._expBar = this._ccsNode.getChildByName(this.CCS_NAMES.EXP_BAR);
        var boardBg = this._ccsNode.getChildByName(this.CCS_NAMES.BOARD_BG);
        this._lblHp = boardBg.getChildByName(this.CCS_NAMES.HP_INFO);

        this._checkHpState();
        this._expBar.setPercent(this._model.getExpPercent());
        this.updateHpInfo();
    },
    updateHpInfo: function () {
        var basicValues = this._model.getBasicValues();
        this._lblHp.setString(cc.formatStr("%d / %d", this._model.getHp(), basicValues[0]));
    },
    _checkHpState: function () {
        this._super();
        if (this._lblHp) {
            this._lblHp.setString(cc.formatStr("%d / %d", Math.floor(this._hpBar.getPercent() / 100 * this._model.getBasicValues()[0]), this._model.getBasicValues()[0]));
        }
    },
    _type: 1,
    _expBar: null,
    _lblHp: null,
});
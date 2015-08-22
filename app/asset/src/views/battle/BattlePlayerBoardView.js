/**
 * Created by Maple on 8/20/15.
 */

var BattlePlayerBoardView = cc.Node.extend({
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
        this._super();

        this._model = model;

        var node = ccs.csLoader.createNode("res/json/battle_player_board_1.json");
        this.addChild(node);

        this._expBar = node.getChildByName(this.CCS_NAMES.EXP_BAR);
        var boardBg = node.getChildByName(this.CCS_NAMES.BOARD_BG);
        this._lblName = boardBg.getChildByName(this.CCS_NAMES.POKEMON_NAME);
        this._iconGender = boardBg.getChildByName(this.CCS_NAMES.ICON_GENDER);
        this._iconState = boardBg.getChildByName(this.CCS_NAMES.ICON_STATE);
        this._lblLv = boardBg.getChildByName(this.CCS_NAMES.POKEMON_LEVEL);
        this._hpBar = boardBg.getChildByName(this.CCS_NAMES.HP_BAR);
        this._lblHp = boardBg.getChildByName(this.CCS_NAMES.HP_INFO);

        this._expBar.setPercent(this._model.getExpPercent());
        this._lblName.setString(this._model.getInfo().getName());
        var maleMap = {
            1: "male",
            2: "female",
        };
        this._iconGender.setSpriteFrame(
            cc.SpriteFrameCache.getInstance().getSpriteFrame(cc.formatStr("common/icon_%s.png", maleMap[this._model.getGender()]))
        );
        this.updateState(this._model.getState());
        this.updateLevel(this._model.getLevel());
    },
    updateState: function (state) {
        if (state == POKEMON_STATES.NORMAL) {
            this._iconState.setVisible(false);
        } else {
            this._iconState.setVisible(true);
            this._iconState.setSpriteFrame(
                cc.SpriteFrameCache.getInstance().getSpriteFrame("common/icon_state_" + this._model.getState().toString())
            );
        }
    },
    updateLevel: function (lv) {
        this._lblLv.setString("Lv." + lv.toString());
    },
    _model: null,
    _expBar: null,
    _lblName: null,
    _iconGender: null,
    _iconState: null,
    _lblLv: null,
    _hpBar: null,
    _lblHp: null,
});
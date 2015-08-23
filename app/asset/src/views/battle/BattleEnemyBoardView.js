/**
 * Created by Maple on 8/23/15.
 */

var BattleEnemyBoardView = cc.Node.extend({
    CCS_NAMES: {
        BOARD_BG: "board_bg",
            POKEMON_NAME: "pokemon_name",
            ICON_GENDER: "icon_gender",
            ICON_STATE: "icon_state",
            POKEMON_LEVEL: "pokemon_lv",
            HP_BAR: "hp_bar",
            ICON_BALL: "icon_ball",
    },
    ctor: function (model) {
        this._super();

        this._model = model;

        var node = ccs.load(cc.formatStr("res/json/battle_player_board_%d.json", this._type)).node;
        this.addChild(node);
        this._ccsNode = node;

        var boardBg = this._ccsNode.getChildByName(this.CCS_NAMES.BOARD_BG);
        this._lblName = boardBg.getChildByName(this.CCS_NAMES.POKEMON_NAME);
        this._iconGender = boardBg.getChildByName(this.CCS_NAMES.ICON_GENDER);
        this._iconState = boardBg.getChildByName(this.CCS_NAMES.ICON_STATE);
        this._lblLv = boardBg.getChildByName(this.CCS_NAMES.POKEMON_LEVEL);
        this._hpBar = boardBg.getChildByName(this.CCS_NAMES.HP_BAR);

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

        if (this._type == 2) {
            this._iconBall = boardBg.getChildByName(this.CCS_NAMES.ICON_BALL);
            // 只有捕获过的精灵才显示这个球 todo
            this._iconBall.setVisible(true);
        }
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
    _type: 2,
    _model: null,
    _ccsNode: null,
    _lblName: null,
    _iconGender: null,
    _iconState: null,
    _lblLv: null,
    _hpBar: null,
    _iconBall: null,
});
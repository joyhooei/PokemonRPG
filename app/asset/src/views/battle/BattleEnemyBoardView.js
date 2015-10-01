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
    HP_CHANGE_SPEED: 0.01,
    UPDATE_SCHEDULER_KEY: "battle_board_update",
    ctor: function (model) {
        this._super();

        var node = ccs.load(cc.formatStr("json/battle_player_board_%d.json", this._type)).node;
        this.addChild(node);
        this._ccsNode = node;

        var boardBg = this._ccsNode.getChildByName(this.CCS_NAMES.BOARD_BG);
        this._lblName = boardBg.getChildByName(this.CCS_NAMES.POKEMON_NAME);
        this._iconGender = boardBg.getChildByName(this.CCS_NAMES.ICON_GENDER);
        this._iconState = boardBg.getChildByName(this.CCS_NAMES.ICON_STATE);
        this._lblLv = boardBg.getChildByName(this.CCS_NAMES.POKEMON_LEVEL);
        this._hpBar = boardBg.getChildByName(this.CCS_NAMES.HP_BAR);
        if (this._type == 2) {
            this._iconBall = boardBg.getChildByName(this.CCS_NAMES.ICON_BALL);
        }
        this._currentHpState = 3;

        this.setModel(model);
    },
    setModel: function (model) {
        if (this._model == model) {
            return;
        }
        this._model = model;
        this._updateView();
    },
    getHpBarAction: function (delta) {
        var hpBarAction = new cc.TargetedAction(this._hpBar, ex.UIProgressTo.create(delta * this.HP_CHANGE_SPEED, this._model.getHpPercent()));
        var action = new cc.Sequence(
            new cc.CallFunc(MakeScriptHandler(this, this._scheduleUpdate)),
            hpBarAction,
            new cc.CallFunc(MakeScriptHandler(this, this._unscheduleUpdate))
        );
        return action;
    },
    updateState: function (state) {
        if (state == POKEMON_STATES.NORMAL) {
            this._iconState.setVisible(false);
        } else {
            this._iconState.setVisible(true);
            this._iconState.setSpriteFrame(
                cc.SpriteFrameCache.getInstance().getSpriteFrame(cc.formatStr("common/icon_state_%d.png", state))
            );
        }
    },
    updateLevel: function (lv) {
        this._lblLv.setString("Lv." + lv.toString());
    },
    _updateView: function () {
        this._lblName.setString(this._model.getInfo().getName());
        var maleMap = {
            1: "male",
            2: "female",
        };
        if (this._model.getGender() !== null) {
            this._iconGender.setVisible(true);
            this._iconGender.setSpriteFrame(
                cc.SpriteFrameCache.getInstance().getSpriteFrame(cc.formatStr("common/icon_%s.png", maleMap[this._model.getGender()]))
            );
            this._iconGender.setPositionX(this._lblName.getPositionX() + this._lblName.getAutoRenderSize().width + 10);
        } else {
            this._iconGender.setVisible(false);
        }
        this.updateState(this._model.getState());
        this.updateLevel(this._model.getLevel());
        this._hpBar.setPercent(this._model.getHpPercent());
        this._checkHpState();
        if (this._type == 2) {
            // 只有捕获过的精灵才显示这个球 todo
            this._iconBall.setVisible(true);
        }
    },
    _checkHpState: function () {
        var percent = this._hpBar.getPercent();
        var frameSuffix = "hp_green.png";
        var newHpState = 3;
        if (percent < 15) {
            newHpState = 1;
            frameSuffix = "hp_red.png";
        } else if (percent < 50) {
            newHpState = 2;
            frameSuffix = "hp_yellow.png";
        }
        if (this._currentHpState != newHpState) {
            this._currentHpState = newHpState;
            this._hpBar.loadTexture(cc.formatStr("common/%s", frameSuffix), ccui.Widget.PLIST_TEXTURE);
        }
    },
    _update: function (dt) {
        // hp bar color
        this._checkHpState();
    },
    _scheduleUpdate: function () {
        cc.director.getScheduler().schedule(MakeScriptHandler(this, this._update), this, 0, cc.REPEAT_FOREVER, 0, false, this.UPDATE_SCHEDULER_KEY);
    },
    _unscheduleUpdate: function () {
        cc.director.getScheduler().unschedule(this.UPDATE_SCHEDULER_KEY, this);
        // 防止掉帧发生意外
        this._checkHpState(true);
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
    _currentHpState: null,     // 1. hp 15%以下  2. hp 50%以下  3. hp 100%以下
});
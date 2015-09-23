/**
 * Created by Maple on 8/23/15.
 */

/**
 * 负责战斗用户操作 包括进行战斗、使用道具、更换精灵、逃跑 等等
 */
var BattleOperationViewController = mw.ViewController.extend({
    TEXTURES_TO_LOAD: {
        "textures/common.plist": "textures/common.pvr.ccz",
    },
    CCS_NAMES: {
        BG: "bg",
            BTN_BATTLE: "btn_battle",
            BTN_POKEMON: "btn_pokemon",
            BTN_ITEM: "btn_item",
            BTN_ESCAPE: "btn_escape",
    },
    STATES: {
        BATTLE_MENU: 1,
        SKILL_MENU: 2,
        PENDING: 10,
    },
    ACTION_INTERVAL: 0.25,
    ctor: function (segue) {
        this._super(segue);
    },
    viewDidLoad: function () {
        this._loadTextures();
        this._addObservers();
        this._renderView();
    },
    viewDidUnload: function () {
        this._removeObservers();
        this._unloadTextures();
    },
    didReceiveMemoryWarning: function () {
    },
    _loadTextures: function () {
        for (var plist in this.TEXTURES_TO_LOAD) {
            var tex = this.TEXTURES_TO_LOAD[plist];
            TextureManager.loadTexture(plist, tex);
        }
    },
    _unloadTextures: function () {
        for (var plist in this.TEXTURES_TO_LOAD) {
            TextureManager.unloadTexture(plist);
        }
    },
    _addObservers: function () {
        Notifier.addObserver(BATTLE_EVENTS.TURN_ENDED, this, this._onTurnEnded);
    },
    _removeObservers: function () {
        Notifier.removeObserver(BATTLE_EVENTS.TURN_ENDED, this);
    },
    _renderView: function () {
        // 初始化技能菜单
        var battleProcessor = this.scene().getBattleProcessor();
        var pokemon = battleProcessor.getFriendPokemon();
        this._skillBoard = new BattleSkillBoardView(pokemon, this);
        this._skillBoard.setPosition(cc.director.getWinSize().width * 0.8, 80);
        this._skillBoard.setScale(0);
        this.view().addChild(this._skillBoard);

        // 初始化战斗菜单
        this._battleBoard = ccs.load("json/battle_board.json").node;
        this._battleBoard.setPosition(this._skillBoard.getPosition());
        this._battleBoard.setScale(0);
        this.view().addChild(this._battleBoard);

        var bg = this._battleBoard.getChildByName(this.CCS_NAMES.BG);
        var btnBattle = bg.getChildByName(this.CCS_NAMES.BTN_BATTLE);
        btnBattle.addClickEventListener(MakeScriptHandler(this, this._onBtnClicked));
        var btnPokemon = bg.getChildByName(this.CCS_NAMES.BTN_POKEMON);
        btnPokemon.addClickEventListener(MakeScriptHandler(this, this._onBtnClicked));
        var btnItem = bg.getChildByName(this.CCS_NAMES.BTN_ITEM);
        btnItem.addClickEventListener(MakeScriptHandler(this, this._onBtnClicked));
        var btnEscape = bg.getChildByName(this.CCS_NAMES.BTN_ESCAPE);
        btnEscape.addClickEventListener(MakeScriptHandler(this, this._onBtnClicked));
        // 记录board的bound 用来做取消操作
        this._boardBound = bg.getBoundingBoxToWorld();

        this.segue().setDelegate(this);

        this._showBattleBoard();
    },
    _showBattleBoard: function () {
        this._state = this.STATES.PENDING;
        this._battleBoard.runAction(new cc.Sequence(
            new cc.EaseIn(new cc.ScaleTo(this.ACTION_INTERVAL, 1), 2),
            new cc.CallFunc(function () {
                this._state = this.STATES.BATTLE_MENU;
            }.bind(this))
        ));
    },
    _hideBattleBoard: function (callback) {
        this._state = this.STATES.PENDING;
        var action = null;
        if (callback instanceof Function) {
            action = new cc.Sequence(
                new cc.EaseOut(new cc.ScaleTo(this.ACTION_INTERVAL, 0), 2),
                new cc.CallFunc(callback)
            );
        } else {
            action = new cc.EaseOut(new cc.ScaleTo(this.ACTION_INTERVAL, 0), 2);
        }
        this._battleBoard.runAction(action);
    },
    _showSkillBoard: function () {
        // 刷新
        this._skillBoard.refresh();
        this._state = this.STATES.PENDING;
        this._skillBoard.runAction(new cc.Sequence(
            new cc.EaseIn(new cc.ScaleTo(this.ACTION_INTERVAL, 1), 2),
            new cc.CallFunc(function () {
                this._state = this.STATES.SKILL_MENU;
            }.bind(this))
        ));
    },
    _hideSkillBoard: function (callback) {
        this._state = this.STATES.PENDING;
        var action = null;
        if (callback instanceof Function) {
            action = new cc.Sequence(
                new cc.EaseOut(new cc.ScaleTo(this.ACTION_INTERVAL, 0), 2),
                new cc.CallFunc(callback)
            );
        } else {
            action = new cc.EaseOut(new cc.ScaleTo(this.ACTION_INTERVAL, 0), 2);
        }
        this._skillBoard.runAction(action);
    },
    _onBtnClicked: function (sender) {
        if (this._state == this.STATES.PENDING) {
            return;
        }
        var btnName = sender.getName();
        if (btnName == this.CCS_NAMES.BTN_BATTLE) {
            // 战斗
            this._hideBattleBoard(MakeScriptHandler(this, this._showSkillBoard));
        } else if (btnName == this.CCS_NAMES.BTN_POKEMON) {
            // 更换精灵
        } else if (btnName == this.CCS_NAMES.BTN_ITEM) {
            // 使用道具
        } else if (btnName == this.CCS_NAMES.BTN_ESCAPE) {
            // 逃跑
        }
    },
    onTouchEnded: function (touch, event) {
        // 触屏到board外的区域 需要做取消操作(如果可以)
        var loc = touch.getLocation();
        if (this._state == this.STATES.SKILL_MENU && !cc.rectContainsPoint(this._boardBound, loc)) {
            this._hideSkillBoard(MakeScriptHandler(this, this._showBattleBoard));
        }
    },
    onLongTouchBegan: function (target, loc, delta) {
        if (!this._isVisible(target)) {
            return;
        }
        target.getChildByName("detail_bg").setVisible(true);
    },
    onClick: function (target) {
        if (!this._isVisible(target)) {
            return;
        }
        var battleProcessor = this.scene().getBattleProcessor();
        var friendPokemon = battleProcessor.getFriendPokemon();
        var skills = friendPokemon.getSkills();
        var skillId = skills[target.getIndex()][0];
        var skillInfo = new SkillInfo(skillId);
        var behavior = new SkillBehavior(friendPokemon, skillInfo);
        this._lastBehavior = behavior;
        battleProcessor.prepareForTurn(behavior);

        this._hideSkillBoard(function () {
            battleProcessor.process();
        });
    },
    onLongTouchEnded: function (target, loc, delta) {
        if (!this._isVisible(target)) {
            return;
        }
        target.getChildByName("detail_bg").setVisible(false);
    },
    _isVisible: function (node) {
        var visible = true;
        var current = node;
        do {
            if (!current.isVisible()) {
                visible = false;
                break;
            }
            current = current.getParent();
        } while (current);
        return visible;
    },
    // event handlers
    _onTurnEnded: function () {
        var battleProcessor = this.scene().getBattleProcessor();
        if (battleProcessor.getFriendPokemon().getRepeat() > 0) {
            battleProcessor.prepareForTurn(this._lastBehavior);
            battleProcessor.process();
        } else {
            this._showBattleBoard();
        }
    },
    _battleBoard: null,
    _skillBoard: null,
    _state: null,
    _boardBound: null,
    _lastBehavior: null,
});
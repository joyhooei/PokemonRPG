/**
 * Created by Maple on 8/15/15.
 */

/**
 * 负责战斗的UI控制 包括精灵面板的变化、精灵的变化、技能特效 等等。
  */
var BattleUIViewController = mw.ViewController.extend({
    TEXTURES_TO_LOAD: {
        "textures/battle.plist": "textures/battle.pvr.ccz",
        "textures/common.plist": "textures/common.pvr.ccz",
    },
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
        mw.log("RECEIVE MEMORY WARNING");
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
        Notifier.addObserver(BATTLE_UI_EVENTS.PLAY_SKILL, this, this._onPlaySkill);
    },
    _removeObservers: function () {
        Notifier.removeObserver(BATTLE_UI_EVENTS.PLAY_SKILL, this);
    },
    _renderView: function () {
        var bg = new cc.Sprite("#battle/battle_bg.png");
        bg.setPosition(cc.director.getWinSize().width * 0.5, cc.director.getWinSize().height * 0.5);
        this.view().addChild(bg);

        // 初始化精灵model
        var pokemon1Id = parseInt(this.scene().getParameter("pokemon1"));
        var pokemon2Id = parseInt(this.scene().getParameter("pokemon2"));
        logBattle("Pokemon1: %d, Pokemon2: %d", pokemon1Id, pokemon2Id);
        var pokemon1Model = new Pokemon({
            id: pokemon1Id,
            level: Math.ceil(Math.random() * 100),
            catcher: DataCenter.getHero().getId(),
            owner: DataCenter.getHero().getId(),
        });
        var pokemon2Model = new Pokemon({
            id: pokemon2Id,
            level: Math.ceil(Math.random() * 100)
        });

        // 初始化BattleProcessor
        this.scene().initBattleProcessor(pokemon1Model, pokemon2Model);

        // 初始化精灵sprite
        this._pokemon1 = new BattlePokemonView(pokemon1Model, true);
        this._pokemon2 = new BattlePokemonView(pokemon2Model, false);
        this._pokemon1.setPosition(cc.director.getWinSize().width * 0.2, cc.director.getWinSize().height * 0.2);
        this.view().addChild(this._pokemon1);
        this._pokemon2.setPosition(cc.director.getWinSize().width * 0.8, cc.director.getWinSize().height * 0.6);
        this.view().addChild(this._pokemon2);

        // 初始化信息面板
        this._playerBoard = new BattlePlayerBoardView(pokemon1Model);
        this._playerBoard.setPosition(cc.director.getWinSize().width * 0.8, cc.director.getWinSize().height * 0.35);
        this.view().addChild(this._playerBoard);

        this._enemyBoard = new BattleEnemyBoardView(pokemon2Model);
        this._enemyBoard.setPosition(cc.director.getWinSize().width * 0.2, cc.director.getWinSize().height * 0.85);
        this.view().addChild(this._enemyBoard);
    },
    _onPlaySkill: function (pokemonModel, skillInfo, dmg) {
        var particle = new cc.ParticleSystem("particles/particle1.plist");
        particle.setAutoRemoveOnFinish(true);
        var duration = particle.getDuration();
        if (pokemonModel.ownBySelf()) {
            particle.setPosition(this._pokemon2.getContentSize().width * 0.5, this._pokemon2.getContentSize().height * 0.5);
            this._pokemon2.addChild(particle);
        } else {
            particle.setPosition(this._pokemon1.getContentSize().width * 0.5, this._pokemon1.getContentSize().height * 0.5);
            this._pokemon1.addChild(particle);
        }
        CallFunctionAsync(this, this._playSkillEnd, duration + 0.1, pokemonModel, dmg);
    },
    _playSkillEnd: function (pokemonModel, dmg) {
        var targetNode = pokemonModel.ownBySelf() ? this._pokemon2 : this._pokemon1;
        var hpBarAction = pokemonModel.ownBySelf() ? this._enemyBoard.getHpBarAction(dmg) : this._playerBoard.getHpBarAction(dmg);
        this.view().runAction(new cc.Sequence(
            new cc.TargetedAction(targetNode, new cc.Blink(0.5, 3)),
            hpBarAction,
            new cc.CallFunc(MakeScriptHandler(this, this._processNextBehavior))
        ));
    },
    _processNextBehavior: function () {
        this.scene().getBattleProcessor().process();
    },
    _pokemon1: null,
    _pokemon2: null,
    _playerBoard: null,
    _enemyBoard: null,
});
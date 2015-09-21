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
        this._musicId = ex.GameAudioEngine.getInstance().play2d("music/battle/giratina.mp3", true);
        this._renderView();
    },
    viewDidUnload: function () {
        ex.GameAudioEngine.getInstance().stop(this._musicId);
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
        Notifier.addObserver(BATTLE_EVENTS.ALL_ENDED, this, this._onAllEnded);
    },
    _removeObservers: function () {
        Notifier.removeObserver(BATTLE_UI_EVENTS.PLAY_SKILL, this);
        Notifier.removeObserver(BATTLE_EVENTS.ALL_ENDED, this);
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
            level: 100,
            catcher: DataCenter.getHero().getId(),
            owner: DataCenter.getHero().getId(),
        });
        var pokemon2Model = new Pokemon({
            id: pokemon2Id,
            level: 100,
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
    _onAllEnded: function () {
        cc.director.runScene(new cc.TransitionFade(0.5, new PlayScene()));
    },
    _onPlaySkill: function (pokemonModel, skillInfo, hurtInfo) {
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
        CallFunctionAsync(this, this._playSkillEnd, duration + 0.1, pokemonModel, hurtInfo);
    },
    _playSkillEnd: function (pokemonModel, hurtInfo) {
        var dmg = hurtInfo ? hurtInfo["hurt"] : 0;
        var attackerNode = pokemonModel.ownBySelf() ? this._pokemon1 : this._pokemon2;
        var defenderNode = pokemonModel.ownBySelf() ? this._pokemon2 : this._pokemon1;
        var attacker = attackerNode.getModel();
        var defender = defenderNode.getModel();
        this._currentAttacker = attacker;
        this._currentDefender = defender;
        var sequenceAry = [ new cc.TargetedAction(defenderNode, new cc.Blink(0.5, 3)) ];
        if (dmg > 0) {
            var hpBarAction = pokemonModel.ownBySelf() ? this._enemyBoard.getHpBarAction(dmg) : this._playerBoard.getHpBarAction(dmg);
            sequenceAry.push(hpBarAction);
            defender.hurt(dmg);
            if (defender.isDead()) {
                this._shouldInterupt = true;
                sequenceAry.push(new cc.CallFunc(function () {
                    defenderNode.stop();
                }));
            }
        }
        if (hurtInfo) {
            if (hurtInfo["criticalCorrection"] > 1.0) {
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(new cc.CallFunc(function () {
                    Notifier.notify(DIALOG_EVENTS.SHOW_DIALOG_WITHOUT_INDICE,
                        "命中要害", MakeScriptHandler(this, this._propertyCorrectionCallback, null, hurtInfo)); // 这里的null是因为cc.CallFunc传递的sender参数
                }.bind(this)))
            } else {
                sequenceAry.push(new cc.CallFunc(MakeScriptHandler(this, this._propertyCorrectionCallback, hurtInfo)))
            }
            this.view().runAction(new cc.Sequence(sequenceAry));
        } else {
            sequenceAry.push(new cc.CallFunc(MakeScriptHandler(this, this._processNextBehavior)));
            this.view().runAction(new cc.Sequence(sequenceAry));
        }
    },
    _propertyCorrectionCallback: function (sender, hurtInfo) {
        var endHandler = MakeScriptHandler(this, (this._shouldInterupt ? this._targetDeadCallback : this._processNextBehavior));
        if (hurtInfo["propertyCorrection"] != 1.0) {
            var action = new cc.Sequence(
                new cc.DelayTime(0.5),
                new cc.CallFunc(function () {
                    Notifier.notify(DIALOG_EVENTS.SHOW_DIALOG_WITHOUT_INDICE,
                        (hurtInfo["propertyCorrection"] > 1.0 ? "效果拔群" : "效果很小"),
                        endHandler);
                })
            );
            this.view().runAction(action);
        } else {
            this.view().runAction(
                new cc.CallFunc(endHandler)
            );
        }
    },
    _targetDeadCallback: function () {
        var action = new cc.Sequence(
            new cc.DelayTime(0.5),
            new cc.CallFunc(function () {
                var audioId = ex.GameAudioEngine.getInstance().play2d(cc.formatStr("sounds/cries/%s.wav", this._currentDefender.getFormatedId()));
                ex.GameAudioEngine.getInstance().setFinishCallback(audioId, function (id, name) {
                    ex.GameAudioEngine.getInstance().uncache(audioId);
                    this._targetDeadCallback2();
                }.bind(this));
            }.bind(this))
        );
        this.view().runAction(action);
    },
    _targetDeadCallback2: function () {
        var ownByPlayer = this._currentDefender.ownBySelf();
        var action = new cc.Sequence(
            new cc.CallFunc(function () {
                Notifier.notify(DIALOG_EVENTS.SHOW_DIALOG_WITHOUT_INDICE,
                    cc.formatStr("%s%s倒下了", (ownByPlayer ? "我方" : "敌方"), this._currentDefender.getInfo().getName()),
                    MakeScriptHandler(this, this._processNextBehavior));
            }.bind(this))
        );
        this.view().runAction(action);
    },
    _processNextBehavior: function () {
        if (this._shouldInterupt) {
            this.scene().getBattleProcessor().clear();
            this._shouldInterupt = false;
        }
        this._currentAttacker = this._currentDefender = this._currentDefenderSprite = null;
        this.view().runAction(new cc.Sequence(
            new cc.DelayTime(0.5),
            new cc.CallFunc(function () {
                this.scene().getBattleProcessor().process();
            }.bind(this))
        ));
    },
    _pokemon1: null,
    _pokemon2: null,
    _playerBoard: null,
    _enemyBoard: null,
    _shouldInterupt: false,
    _currentAttacker: null,
    _currentDefender: null,
    _musicId: -1,
});
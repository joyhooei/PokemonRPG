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

        this._musicId = -1;
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
        Notifier.addObserver(BATTLE_EVENTS.PROCESS_TURN, this, this._onProcessTurn);
        Notifier.addObserver(BATTLE_EVENTS.TURN_BEGAN, this, this._onTurnBegan);
        Notifier.addObserver(BATTLE_EVENTS.TURN_ENDED, this, this._onTurnEnded);
        Notifier.addObserver(BATTLE_EVENTS.BATTLE_ENDED, this, this._onBattleEnded);
    },
    _removeObservers: function () {
        Notifier.removeObserver(BATTLE_EVENTS.PROCESS_TURN, this);
        Notifier.removeObserver(BATTLE_EVENTS.TURN_BEGAN, this);
        Notifier.removeObserver(BATTLE_EVENTS.TURN_ENDED, this);
        Notifier.removeObserver(BATTLE_EVENTS.BATTLE_ENDED, this);
    },
    _renderView: function () {
        var bg = new cc.Sprite("#battle/battle_bg.png");
        bg.setPosition(cc.director.getWinSize().width * 0.5, cc.director.getWinSize().height * 0.5);
        this.view().addChild(bg);

        var battleProcessor = this.scene().getBattleProcessor();
        var pokemon1Model = battleProcessor.getFriendPokemon();
        var pokemon2Model = battleProcessor.getEnemyPokemon();

        // 初始化地形
        this._field1 = new cc.Sprite("#battle/battle_field1.png");
        this._field1.setPosition(cc.director.getWinSize().width * 0.2, cc.director.getWinSize().height * 0.3);
        this.view().addChild(this._field1);
        this._field2 = new cc.Sprite("#battle/battle_field1.png");
        this._field2.setPosition(cc.director.getWinSize().width * 0.8, cc.director.getWinSize().height * 0.6);
        this.view().addChild(this._field2);

        // 初始化精灵sprite
        this._pokemon1 = new BattlePokemonView(pokemon1Model, true);
        this._pokemon2 = new BattlePokemonView(pokemon2Model, false);
        this._pokemon1.setPosition(this._field1.getContentSize().width * 0.5, this._field1.getContentSize().height * 0.45);
        this._pokemon2.setPosition(this._field2.getContentSize().width * 0.5, this._field2.getContentSize().height * 0.45);
        this._field1.addChild(this._pokemon1);
        this._field2.addChild(this._pokemon2);

        // 初始化信息面板
        this._playerBoard = new BattlePlayerBoardView(pokemon1Model);
        this._playerBoard.setPosition(cc.director.getWinSize().width * 0.8, cc.director.getWinSize().height * 0.35);
        this.view().addChild(this._playerBoard);

        this._enemyBoard = new BattleEnemyBoardView(pokemon2Model);
        this._enemyBoard.setPosition(cc.director.getWinSize().width * 0.2, cc.director.getWinSize().height * 0.85);
        this.view().addChild(this._enemyBoard);
    },
    _onBattleEnded: function () {
        if (!this._pokemon1.getModel().isDead()) {
            this._pokemon1.getModel().leaveBattle();
        }
        if (!this._pokemon2.getModel().isDead()) {
            this._pokemon2.getModel().leaveBattle();
        }
        cc.director.runScene(new cc.TransitionFade(0.5, new PlayScene()));
    },
    _onTurnBegan: function () {
        var battleProcessor = this.scene().getBattleProcessor();
        battleProcessor.process();
    },
    _onTurnEnded: function (steps) {
        var sequenceAry = [];
        for (var i in steps) {
            var step = steps[i];
            this._processStep(step, sequenceAry);
        }
        sequenceAry.push(new cc.CallFunc(function () {
            this.scene().getViewControllerByIdentifier(BATTLE_OPERATION_VC_NAME).endTurn();
        }.bind(this)));

        this._play(sequenceAry);
    },
    _onProcessTurn: function (steps) {
        var sequenceAry = [];
        for (var i in steps) {
            var step = steps[i];
            this._processStep(step, sequenceAry);
        }
        this._processNextBehavior(sequenceAry);

        this._play(sequenceAry);
    },
    _processStep: function (step, sequenceAry) {
        logBattle("processing step: %s", step.name);
        if (step.name == "text") {
            var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
            sequenceAry.push(dialogVc.getTextAction(step.args.text));
        } else if (step.name == "skill_anim") {
            var skillData = step.args.skillData;
            var target = null;
            var animType = step.args.type;
            var targetType = skillData["targetType"];
            if (targetType == 1) {
                // 目标是精灵
                target = this._pokemon1.getModel() == skillData["defender"] ? this._pokemon1 : this._pokemon2;
            } else if (targetType == 2) {
                // 目标是场地
                target = skillData["isFriend"] ? this._field1 : this._field2;
            } else if (targetType == 3) {
                // 天气
                target = this.view();
            }

            if (animType == 1) {
                // 粒子
                sequenceAry.push(new cc.CallFunc(function () {
                    var particle = new cc.ParticleSystem(cc.formatStr("particles/%s.plist", step.args.params));
                    particle.setScale(1.5);
                    particle.setAutoRemoveOnFinish(true);
                    if (targetType == 3) {
                        particle.setPosition(cc.winSize.width * 0.5, cc.winSize.height);
                    } else {
                        particle.setPosition(target.getContentSize().width * 0.5, target.getContentSize().height * 0.5);
                    }
                    target.addChild(particle);
                }));
                var particle = new cc.ParticleSystem(cc.formatStr("particles/%s.plist", step.args.params));
                sequenceAry.push(new cc.DelayTime(particle.getDuration()));
            }
        } else if (step.name == "pokemon_state_anim") {
            this._getPokemonStateAction(step.state, step.target, sequenceAry);
        } else if (step.name == "battle_state_anim") {
            this._getBattleStateAction(step.state, step.target, sequenceAry);
        } else if (step.name == "hp_anim") {
            var target = step.args.target;
            var delta = step.args.delta;
            var board = target.ownBySelf() ? this._playerBoard : this._enemyBoard;
            sequenceAry.push(board.getHpBarAction(delta));
        } else if (step.name == "blink") {
            var target= step.args.target;
            var targetNode = target.ownBySelf() ? this._pokemon1 : this._pokemon2;
            sequenceAry.push(new cc.TargetedAction(targetNode, new cc.Blink(0.5, 3)));
        } else if (step.name == "die") {
            var target = step.args.target;
            sequenceAry.push(new cc.CallFunc(function () {
                var audioId = ex.GameAudioEngine.getInstance().play2d(cc.formatStr("sounds/cries/%s.wav", target.getFormatedId()));
                ex.GameAudioEngine.getInstance().setFinishCallback(audioId, function (id, name) {
                    ex.GameAudioEngine.getInstance().uncache(audioId);
                });
                target.leaveBattle();
                (target.ownBySelf() ? this._pokemon1 : this._pokemon2).stop();
            }.bind(this)));
            sequenceAry.push(new cc.DelayTime(2));
            sequenceAry.push((target.ownBySelf() ? this._pokemon1 : this._pokemon2).getDeadAction());
        } else if (step.name == "ability_level_anim") {
            var animType = step.args.type;
            var target = step.args.target;
            var targetNode = target.ownBySelf() ? this._pokemon1 : this._pokemon2;
            sequenceAry.push(new cc.CallFunc(function () {
                var particle = new cc.ParticleSystem(cc.formatStr("particles/particle%d.plist", animType));
                particle.setAutoRemoveOnFinish(true);
                particle.setPosition(targetNode.getContentSize().width * 0.5, targetNode.getContentSize().height * 0.5);
                targetNode.addChild(particle);
            }));
            sequenceAry.push(new cc.DelayTime(2));
        } else if (step.name == "weather_anim") {
            var weather = step.args.weather;
            sequenceAry.push(new cc.CallFunc(function () {
                var particle = new cc.ParticleSystem(cc.formatStr("particles/particle2%d.plist", weather));
                particle.setAutoRemoveOnFinish(true);
                particle.setPosition(cc.winSize.width * 0.5, cc.winSize.height);
                this.view().addChild(particle);
            }.bind(this)));
            sequenceAry.push(new cc.DelayTime(2));
        } else if (step.name == "prepare_anim") {
            var animationType = step.args.type;
            var target = this._pokemon1.getModel() == step.args.target ? this._pokemon1 : this._pokemon2;
            if (animationType == 1) {
                sequenceAry.push(new cc.CallFunc(function () {
                    var particle = new cc.ParticleSystem(cc.formatStr("particles/%s.plist", step.args.name));
                    particle.setAutoRemoveOnFinish(true);
                    particle.setPosition(target.getContentSize().width * 0.5, target.getContentSize().height * 0.5);
                    target.addChild(particle);
                }));
                sequenceAry.push(new cc.DelayTime(2));
            }
        }
        sequenceAry.push(new cc.DelayTime(0.5));
    },
    _getPokemonStateAction: function (state, pokemon, sequenceAry) {
        // 不包含文字动画
        var ownBySelf = pokemon.ownBySelf();
        var tgtBoard = ownBySelf ? this._playerBoard : this._enemyBoard;
        sequenceAry.push(new cc.CallFunc(function () {
            tgtBoard.updateState(state);
        }));
    },
    _getBattleStateAction: function (state, pokemon, sequenceAry) {
        // 包含文字动画
        var ownBySelf = pokemon.ownBySelf();
        var targetNode = ownBySelf ? this._pokemon1 : this._pokemon2;
        if (state == BATTLE_STATES.CONFUSED) {
            sequenceAry.push(new cc.CallFunc(function () {
                var dizzyGif = mw.GifSprite.createWithFile("gif/dizzy.gif");
                dizzyGif.setScale(0.2);
                dizzyGif.setPosition(targetNode.getContentSize().width * 0.5, targetNode.getContentSize().height);
                targetNode.addChild(dizzyGif, 0, 100);
            }));
            sequenceAry.push(new cc.DelayTime(1));
            sequenceAry.push(new cc.CallFunc(function () {
                targetNode.getChildByTag(100).removeFromParent();
            }));
        }
    },
    _processNextBehavior: function (sequenceAry) {
        sequenceAry.push(new cc.CallFunc(function () {
            var battleProcessor = this.scene().getBattleProcessor();
            battleProcessor.process();
        }.bind(this)));
    },
    _play: function (sequenceAry) {
        if (sequenceAry.length > 1) {
            this.view().runAction(new cc.Sequence(sequenceAry));
        } else if (sequenceAry.length > 0) {
            this.view().runAction(sequenceAry[0]);
        }
    },
    _pokemon1: null,
    _pokemon2: null,
    _field1: null,
    _field2: null,
    _playerBoard: null,
    _enemyBoard: null,
});
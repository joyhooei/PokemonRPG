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
    _onTurnEnded: function () {
        var battleProcessor = this.scene().getBattleProcessor();
        var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
        var sequenceAry = [];
        var dead = false;
        var pokemonStateInfo = battleProcessor.checkPokemonStateWhenTurnEnds(this._pokemon1.getModel());
        if (pokemonStateInfo["hurt"]) {
            sequenceAry.push(dialogVc.getTextAction(
                cc.formatStr("我方%s%s了", this._pokemon1.getModel().getInfo().getName(), POKEMON_STATE_NAMES[pokemonStateInfo["state"]])
            ));
            this._getPokemonStateAction(pokemonStateInfo["state"], this._pokemon1.getModel(), sequenceAry);
            sequenceAry.push(this._playerBoard.getHpBarAction(pokemonStateInfo["hurt"]));
            if (this._pokemon1.getModel().isDead()) {
                dead = true;
                this._getDeadAction(this._pokemon1.getModel(), sequenceAry);
            }
        }
        pokemonStateInfo = battleProcessor.checkPokemonStateWhenTurnEnds(this._pokemon2.getModel());
        if (pokemonStateInfo["hurt"]) {
            sequenceAry.push(dialogVc.getTextAction(
                cc.formatStr("敌方%s%s了", this._pokemon2.getModel().getInfo().getName(), POKEMON_STATE_NAMES[pokemonStateInfo["state"]])
            ));
            this._getPokemonStateAction(pokemonStateInfo["state"], this._pokemon2.getModel(), sequenceAry);
            sequenceAry.push(this._enemyBoard.getHpBarAction(pokemonStateInfo["hurt"]));
            if (this._pokemon2.getModel().isDead()) {
                dead = true;
                this._getDeadAction(this._pokemon2.getModel(), sequenceAry);
            }
        }
        if (dead) {
            sequenceAry.push(new cc.DelayTime(0.5));
            sequenceAry.push(new cc.CallFunc(function () {
                battleProcessor.endBattle();
            }));
        } else {
            // 天气
            var weather = battleProcessor.getWeather();
            var weatherTurns = battleProcessor.checkWeather();
            var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
            if (weatherTurns > 0) {
                var map = {
                    1: "正在下雨",
                    2: "烈日炎炎",
                    3: "正在下冰雹",
                    4: "很大的沙尘暴",
                };
                sequenceAry.push(new cc.CallFunc(function () {
                    var particle = new cc.ParticleSystem(cc.formatStr("particles/particle2%d.plist", weather));
                    particle.setAutoRemoveOnFinish(true);
                    particle.setPosition(cc.winSize.width * 0.5, cc.winSize.height);
                    this.view().addChild(particle);
                }.bind(this)));
                sequenceAry.push(new cc.DelayTime(2));
                sequenceAry.push(dialogVc.getTextAction(map[weather]));
                sequenceAry.push(new cc.DelayTime(0.5));
            } else if (weatherTurns == 0) {
                var map = {
                    1: "雨停了",
                    2: "阳光减弱了",
                    3: "冰雹停了",
                    4: "沙尘暴停了",
                };
                sequenceAry.push(dialogVc.getTextAction(map[weather]));
                sequenceAry.push(new cc.DelayTime(0.5));
            }
            sequenceAry.push(new cc.CallFunc(function () {
                this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME).clearText();
                this.scene().getViewControllerByIdentifier(BATTLE_OPERATION_VC_NAME).endTurn();
            }.bind(this)));
        }
        // 卧槽尼玛 被这个bug坑死了 Sequence的参数如果是数组而且只有一个 会同时执行两次
        if (sequenceAry.length > 1) {
            this.view().runAction(new cc.Sequence(sequenceAry));
        } else {
            this.view().runAction(sequenceAry[0]);
        }
    },
    _onProcessTurn: function (steps) {
        var sequenceAry = [];
        for (var i in steps) {
            var step = steps[i];
            this._processStep(step, sequenceAry);
        }
    },
    _processStep: function (step, sequenceAry) {
        if (step.name == "text") {
            var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
            sequenceAry.push(dialogVc.getTextAction(step.args.text));
        } else if (step.name == "skill_anim") {
            var skillData = step.skillData;
            var target = null;
            var animType = step.type;
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
                    particle.setAutoRemoveOnFinish(true);
                    if (targetType == 3) {
                        particle.setPosition(cc.winSize.width * 0.5, cc.winSize.height);
                    } else {
                        particle.setPosition(target.getContentSize().width * 0.5, target.getContentSize().height * 0.5);
                    }
                    target.addChild(particle);
                }));
                var particle = new cc.ParticleSystem(cc.formatStr("particles/%s.plist", step.args.params));
                sequenceAry.push(new cc.DelayTime(particle.getDuration() + 0.5));
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
    _processNextBehavior: function (sequenceAry) {
        sequenceAry.push(new cc.DelayTime(0.5));
        sequenceAry.push(new cc.CallFunc(function () {
            var battleProcessor = this.scene().getBattleProcessor();
            battleProcessor.process();
        }.bind(this)));
    },
    _pokemon1: null,
    _pokemon2: null,
    _field1: null,
    _field2: null,
    _playerBoard: null,
    _enemyBoard: null,
});
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

        this._shouldInterupt = false;
        this._musicId = -1;
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
        Notifier.addObserver(BATTLE_EVENTS.TURN_ENDED, this, this._onTurnEnded);
        Notifier.addObserver(BATTLE_EVENTS.BATTLE_ENDED, this, this._onBattleEnded);
    },
    _removeObservers: function () {
        Notifier.removeObserver(BATTLE_UI_EVENTS.PLAY_SKILL, this);
        Notifier.removeObserver(BATTLE_EVENTS.TURN_ENDED, this);
        Notifier.removeObserver(BATTLE_EVENTS.BATTLE_ENDED, this);
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
    _onPlaySkill: function (pokemonModel, skillInfo) {
        var battleProcessor = this.scene().getBattleProcessor();
        var playSkillFunc = function () {
            // 减少pp
            if (pokemonModel.getRepeat() == 0 && !pokemonModel.isPreparing()) {
                pokemonModel.reducePP(skillInfo.getId(), 1);
            }
            var skillResult = battleProcessor.analyzeSkill(pokemonModel, skillInfo);
            if (skillResult["notHit"]) {
                // 未命中
                var sequenceAry = [];
                var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction("技能没有命中"));
                this._processNextBehavior(sequenceAry);
                this.view().runAction(new cc.Sequence(sequenceAry));
            } else if (skillResult["noEffect"]) {
                // 没有效果
                var sequenceAry = [];
                var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction("貌似没有效果"));
                this._processNextBehavior(sequenceAry);
                this.view().runAction(new cc.Sequence(sequenceAry));
            } else if (skillResult["hasBuff"]) {
                // 场地buff重复
                var sequenceAry = [];
                var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction("但是没有作用"));
                this._processNextBehavior(sequenceAry);
                this.view().runAction(new cc.Sequence(sequenceAry));
            } else if (skillResult["isPreparing"]) {
                var sequenceAry = [];
                var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
                var animationType = skillResult["animType"];
                var target = this._pokemon1.getModel() == skillResult["attacker"] ? this._pokemon1 : this._pokemon2;
                if (animationType == 1) {
                    sequenceAry.push(new cc.CallFunc(function () {
                        var particle = new cc.ParticleSystem(cc.formatStr("particles/%s.plist", skillResult["animName"]));
                        particle.setAutoRemoveOnFinish(true);
                        particle.setPosition(target.getContentSize().width * 0.5, target.getContentSize().height * 0.5);
                        target.addChild(particle);
                    }));
                    sequenceAry.push(new cc.DelayTime(2));
                }
                sequenceAry.push(dialogVc.getTextAction(
                    cc.formatStr("%s%s%s", (pokemonModel.ownBySelf() ? "我方" : "敌方"), pokemonModel.getInfo().getName(), skillResult["string"])
                ));
                this._processNextBehavior(sequenceAry);
                this.view().runAction(new cc.Sequence(sequenceAry));
            } else if (skillInfo.getId() == 138 && skillResult["defender"].getState() != POKEMON_STATES.SLEEP) {
                // 食梦必须要对方睡着
                var sequenceAry = [];
                var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction("但是没有作用"));
                this._processNextBehavior(sequenceAry);
                this.view().runAction(new cc.Sequence(sequenceAry));
            } else {
                var animationParams = skillInfo.getAnimationParams().split(";");
                var animationType = parseInt(animationParams[0]);
                var target = null;
                if (skillResult["targetType"] == 1) {
                    // 目标是精灵
                    target = this._pokemon1.getModel() == skillResult["defender"] ? this._pokemon1 : this._pokemon2;
                } else if (skillResult["targetType"] == 2) {
                    // 目标是场地
                    target = skillResult["isFriend"] ? this._field1 : this._field2;
                }
                if (animationType == 1) {
                    // 粒子效果
                    var particle = new cc.ParticleSystem(cc.formatStr("particles/%s.plist", skillInfo.getAnimationParams().split(";")[1]));
                    particle.setAutoRemoveOnFinish(true);
                    var duration = particle.getDuration();
                    particle.setPosition(target.getContentSize().width * 0.5, target.getContentSize().height * 0.5);
                    target.addChild(particle);
                    CallFunctionAsync(this, this._playSkillEnd, duration + 0.1, skillResult);
                }
            }
        }.bind(this);

        var ownBySelf = pokemonModel.ownBySelf();
        var sequenceAry = [];
        var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
        // 检查精灵状态
        var pokemonStateInfo = battleProcessor.checkPokemonStateBeforeUseSkill(pokemonModel);
        if (pokemonStateInfo["eliminated"]) {
            var strMap = {
                2: "醒了",
            };
            this._getRemovePokemonStateAction(pokemonModel, sequenceAry);
            sequenceAry.push(dialogVc.getTextAction(
                cc.formatStr("%s%s%s", (ownBySelf ? "我方" : "敌方"), pokemonModel.getInfo().getName(), strMap[pokemonStateInfo["state"]])
            ));
            sequenceAry.push(new cc.DelayTime(0.5));
            sequenceAry.push(dialogVc.getTextAction(
                    cc.formatStr("%s%s使用了技能%s",
                        (ownBySelf ? "我方" : "敌方"),
                        pokemonModel.getInfo().getName(),
                        skillInfo.getName()))
            );
            sequenceAry.push(new cc.CallFunc(function () {
                playSkillFunc();
            }));
        } else if (pokemonStateInfo["skip"]) {
            // 会消除连续攻击效果
            pokemonModel.setRepeat(0);
            pokemonModel.setNextBattleState(null);

            var state = pokemonStateInfo["state"];
            this._getPokemonStateAction(state, pokemonModel, sequenceAry);
            var strMap = {
                2: "正在呼噜大睡",
                3: "麻痹了无法动弹",
                5: "被冻结了无法动弹",
            };
            sequenceAry.push(dialogVc.getTextAction(
                cc.formatStr("%s%s%s", (ownBySelf ? "我方" : "敌方"), pokemonModel.getInfo().getName(), strMap[state])
            ));
            // 继续下一个行为
            this._processNextBehavior(sequenceAry);
        } else {
            // 检查异常状态
            var battleStateInfo = battleProcessor.checkBattleStateBeforeUseSkill(pokemonModel);
            if (battleStateInfo && battleStateInfo["state"] != BATTLE_STATES.NORMAL) {
                if (battleStateInfo["eliminated"]) {
                    sequenceAry.push(dialogVc.getTextAction(
                            cc.formatStr("%s%s解除%s",
                                (ownBySelf ? "我方" : "敌方"),
                                pokemonModel.getInfo().getName(),
                                BATTLE_STATE_NAMES[battleStateInfo["state"]])
                        )
                    );
                    sequenceAry.push(dialogVc.getTextAction(
                            cc.formatStr("%s%s使用了技能%s",
                                (ownBySelf ? "我方" : "敌方"),
                                pokemonModel.getInfo().getName(),
                                skillInfo.getName()))
                    );
                    sequenceAry.push(new cc.CallFunc(function () {
                        playSkillFunc();
                    }));
                } else {
                    this._getBattleStateAction(battleStateInfo["state"], pokemonModel, sequenceAry);
                    if (battleStateInfo["hurt"]) {
                        // 混乱攻击自己 会消除连续攻击效果
                        pokemonModel.setRepeat(0);
                        pokemonModel.setNextBattleState(null);
                        var delta = pokemonModel.hurt(battleStateInfo["hurt"]);
                        sequenceAry.push(new cc.DelayTime(0.5));
                        sequenceAry.push(dialogVc.getTextAction(
                            cc.formatStr("%s%s攻击了自己", (ownBySelf ? "我方" : "敌方"), pokemonModel.getInfo().getName())
                        ));
                        sequenceAry.push(new cc.TargetedAction((ownBySelf ? this._pokemon1 : this._pokemon2), new cc.Blink(0.5, 3)));
                        var hpBarAction = ownBySelf ? this._playerBoard.getHpBarAction(delta) : this._enemyBoard.getHpBarAction(delta);
                        sequenceAry.push(hpBarAction);
                        if (pokemonModel.isDead()) {
                            this._getDeadAction(pokemonModel, sequenceAry);
                        }
                        // 继续下一个行为
                        this._processNextBehavior(sequenceAry);
                    } else if (battleStateInfo["skip"]) {
                        // 继续下一个行为
                        sequenceAry.push(dialogVc.getTextAction(
                            cc.formatStr("%s%s%s", (ownBySelf ? "我方" : "敌方"), pokemonModel.getInfo().getName(), BATTLE_STATE_SUFFIX[battleStateInfo["state"]])
                        ));
                        this._processNextBehavior(sequenceAry);
                    } else {
                        this._checkNewBattleState(pokemonModel, sequenceAry);
                        sequenceAry.push(dialogVc.getTextAction(
                                cc.formatStr("%s%s使用了技能%s",
                                    (ownBySelf ? "我方" : "敌方"),
                                    pokemonModel.getInfo().getName(),
                                    skillInfo.getName()))
                        );
                        sequenceAry.push(new cc.CallFunc(function () {
                            playSkillFunc();
                        }));
                    }
                }
            } else {
                sequenceAry.push(dialogVc.getTextAction(
                        cc.formatStr("%s%s使用了技能%s",
                            (ownBySelf ? "我方" : "敌方"),
                            pokemonModel.getInfo().getName(),
                            skillInfo.getName()))
                );
                sequenceAry.push(new cc.CallFunc(function () {
                    playSkillFunc();
                }));
            }
        }
        this.view().runAction(new cc.Sequence(sequenceAry));
    },
    _playSkillEnd: function (result) {
        var sequenceAry = [];
        var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
        if (result["isHurtSkill"]) {
            var attacker = result["attacker"];
            var defender = result["defender"];
            var attackerNode = this._pokemon1.getModel() == attacker ? this._pokemon1 : this._pokemon2;
            var defenderNode = this._pokemon2.getModel() == defender ? this._pokemon2 : this._pokemon1;
            // 闪烁动画
            sequenceAry.push(new cc.TargetedAction(defenderNode, new cc.Blink(0.5, 3)));
            // 血条动画
            var hpBarAction = defender.ownBySelf() ? this._playerBoard.getHpBarAction(result["delta"]) : this._enemyBoard.getHpBarAction(result["delta"]);
            sequenceAry.push(hpBarAction);
            // 是否有回复或损伤
            if ((result["heal"] !== undefined && result["heal"] > 0) || (result["selfHurt"] !== undefined && result["selfHurt"] > 0)) {
                var value = result["heal"] || result["selfHurt"];
                var otherHpBarAction = attacker.ownBySelf() ? this._playerBoard.getHpBarAction(value) : this._enemyBoard.getHpBarAction(value);
                sequenceAry.push(otherHpBarAction);
            }
            // 命中要害判断
            if (result["criticalCorrection"] > 1.0) {
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction("命中要害"));
            }
            // 效果判断
            if (result["propertyCorrection"] != 1.0) {
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction(result["propertyCorrection"] > 1.0 ? "效果拔群" : "效果很小"));
            }
            if (result["heal"] !== undefined) {
                sequenceAry.push(new cc.DelayTime(0.5));
                if (result["heal"] > 0) {
                    sequenceAry.push(dialogVc.getTextAction("回复了生命值"));
                } else {
                    sequenceAry.push(dialogVc.getTextAction("生命值已经满了"));
                }
            } else if (result["selfHurt"] !== undefined && result["selfHurt"] > 0) {
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction("受到了反冲伤害"));
            }
            if (defender.isDead() || attacker.isDead()) {
                if (defender.isDead()) {
                    this._getDeadAction(defender, sequenceAry);
                }
                if (attacker.isDead()) {
                    this._getDeadAction(attacker, sequenceAry);
                }
            } else {
                this._checkNewPokemonState(defender, sequenceAry);
                this._checkAbilityLevels(attacker, result, sequenceAry);
                this._checkNewBattleState(defender, sequenceAry);
            }
            this._checkNewBattleState(attacker, sequenceAry);
        } else if (result["isHealSkill"]) {
            var target = result["defender"];
            if (result["delta"] > 0) {
                var ownBySelf = target.ownBySelf();
                var targetBoard = ownBySelf ? this._playerBoard : this._enemyBoard;
                // 血条动画
                sequenceAry.push(targetBoard.getHpBarAction(result["delta"]));
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction(cc.formatStr("%s%s回复了生命值", (ownBySelf ? "我方" : "敌方"), target.getInfo().getName())));
            } else {
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(dialogVc.getTextAction("生命值已经满了"));
            }
            this._checkNewBattleState(target, sequenceAry);
            this._checkNewBattleState(result["skiller"], sequenceAry);
        } else if (result["isFieldSkill"]) {
            var buffId = result["buffId"];
            sequenceAry.push(new cc.DelayTime(0.5));
            sequenceAry.push(dialogVc.getTextAction(cc.formatStr("%s场地%s", (result["isFriend"] ? "我方" : "敌方"), FIELD_BUFF_TEXT[buffId])));
            this._checkNewBattleState(result["skiller"], sequenceAry);
        } else if (result["isVarianceSkill"]) {
            var attacker = result["attacker"];
            var defender = result["defender"];
            this._checkNewPokemonState(defender, sequenceAry);
            this._checkAbilityLevels(attacker, result, sequenceAry);
            this._checkNewBattleState(defender, sequenceAry);
            this._checkNewBattleState(attacker, sequenceAry);
        } else if (result["isKillSkill"]) {
            var attacker = result["attacker"];
            var defender = result["defender"];
            var attackerNode = this._pokemon1.getModel() == attacker ? this._pokemon1 : this._pokemon2;
            var defenderNode = this._pokemon2.getModel() == defender ? this._pokemon2 : this._pokemon1;
            // 闪烁动画
            sequenceAry.push(new cc.TargetedAction(defenderNode, new cc.Blink(0.5, 3)));
            // 血条动画
            var hpBarAction = defender.ownBySelf() ? this._playerBoard.getHpBarAction(result["delta"]) : this._enemyBoard.getHpBarAction(result["delta"]);
            sequenceAry.push(hpBarAction);
            sequenceAry.push(new cc.DelayTime(0.5));
            sequenceAry.push(dialogVc.getTextAction("一击必杀"));
            this._getDeadAction(defender, sequenceAry);
        }
        // 继续下一个行为
        this._processNextBehavior(sequenceAry);
        this.view().runAction(new cc.Sequence(sequenceAry));
    },
    _processNextBehavior: function (sequenceAry) {
        sequenceAry.push(new cc.DelayTime(0.5));
        sequenceAry.push(new cc.CallFunc(function () {
            var battleProcessor = this.scene().getBattleProcessor();
            if (this._shouldInterupt) {
                battleProcessor.clearBehaviorQueue();
                this._shouldInterupt = false;
                battleProcessor.endBattle();
            } else {
                battleProcessor.process();
            }
        }.bind(this)));
    },
    _checkAbilityLevels: function (skillUser, skillResult, sequenceAry) {
        var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
        var propMap = [ "攻击", "防御", "特攻", "特防", "速度" ];
        var levelMap = [ "迅速下降", "下降", "", "上升", "迅速上升" ];
        var ownBySelf = skillUser.ownBySelf();
        var attackerNode = (ownBySelf ? this._pokemon1 : this._pokemon2);
        var defenderNode = (ownBySelf ? this._pokemon2 : this._pokemon1);
        var enemyAbilityLevels = skillResult["targetAbilityLevels"];
        if (enemyAbilityLevels) {
            if (skillResult["enemyShouldPlay"]) {
                sequenceAry.push(new cc.CallFunc(function () {
                    var particle = new cc.ParticleSystem(cc.formatStr("particles/particle%d.plist", skillResult["enemyAnimationType"]));
                    particle.setAutoRemoveOnFinish(true);
                    particle.setPosition(defenderNode.getContentSize().width * 0.5, defenderNode.getContentSize().height * 0.5);
                    defenderNode.addChild(particle);
                }));
            }
            sequenceAry.push(new cc.DelayTime(2));
            for (var i in enemyAbilityLevels) {
                var data = enemyAbilityLevels[i];
                var prop = data[0];
                var delta = data[1];
                var canChange = data[2];
                //sequenceAry.push(new cc.DelayTime(0.5));
                if (!canChange) {
                    sequenceAry.push(dialogVc.getTextAction(
                        cc.formatStr("%s%s%s已经不能%s了",
                            (ownBySelf ? "敌方" : "我方"),
                            defenderNode.getModel().getInfo().getName(),
                            propMap[prop],
                            (delta > 0 ? "上升" : "下降")
                        )));
                } else {
                    sequenceAry.push(dialogVc.getTextAction(
                        cc.formatStr("%s%s%s%s",
                            (ownBySelf ? "敌方" : "我方"),
                            defenderNode.getModel().getInfo().getName(),
                            propMap[prop],
                            levelMap[delta + 2]
                        )));
                }
            }
        }
        var selfAbilityLevels = skillResult["selfAbilityLevels"];
        if (selfAbilityLevels) {
            if (skillResult["selfShouldPlay"]) {
                sequenceAry.push(new cc.CallFunc(function () {
                    var particle = new cc.ParticleSystem(cc.formatStr("particles/particle%d.plist", skillResult["selfAnimationType"]));
                    particle.setAutoRemoveOnFinish(true);
                    particle.setPosition(attackerNode.getContentSize().width * 0.5, attackerNode.getContentSize().height * 0.5);
                    attackerNode.addChild(particle);
                }));
            }
            sequenceAry.push(new cc.DelayTime(2));
            for (var i in selfAbilityLevels) {
                var data = selfAbilityLevels[i];
                var prop = data[0];
                var delta = data[1];
                var canChange = data[2];
                //sequenceAry.push(new cc.DelayTime(0.5));
                if (!canChange) {
                    sequenceAry.push(dialogVc.getTextAction(
                        cc.formatStr("%s%s%s已经不能%s了",
                            (ownBySelf ? "我方" : "敌方"),
                            attackerNode.getModel().getInfo().getName(),
                            propMap[prop],
                            (delta > 0 ? "上升" : "下降")
                        )));
                } else {
                    sequenceAry.push(dialogVc.getTextAction(
                        cc.formatStr("%s%s%s%s",
                            (ownBySelf ? "我方" : "敌方"),
                            attackerNode.getModel().getInfo().getName(),
                            propMap[prop],
                            levelMap[delta + 2]
                        )));
                }
            }
        }
    },
    _checkNewPokemonState: function (pokemon, sequenceAry) {
        var newState = pokemon.getNewState();
        if (newState) {
            var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
            var ownBySelf = pokemon.ownBySelf();
            sequenceAry.push(new cc.DelayTime(0.5));
            if (pokemon.getState() == POKEMON_STATES.NORMAL) {
                this._getPokemonStateAction(newState, pokemon, sequenceAry);
                sequenceAry.push(dialogVc.getTextAction(
                    cc.formatStr("%s%s%s了", (ownBySelf ? "我方" : "敌方"), pokemon.getInfo().getName(), POKEMON_STATE_NAMES[newState])
                ));
            } else {
                sequenceAry.push(dialogVc.getTextAction(
                    cc.formatStr("%s已经有异常状态了", (ownBySelf ? "我方" : "敌方"))
                ));
            }
            pokemon.refreshState();
        }
    },
    _checkNewBattleState: function (pokemon, sequenceAry) {
        var newState = pokemon.getNewBattleState();
        if (newState) {
            var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
            var ownBySelf = pokemon.ownBySelf();
            if (pokemon.hasBattleState(newState)) {
                sequenceAry.push(new cc.DelayTime(0.5));
                sequenceAry.push(
                    dialogVc.getTextAction(cc.formatStr("%s%s已经%s了", (ownBySelf ? "我方" : "敌方"), pokemon.getInfo().getName(), BATTLE_STATE_NAMES[newState])));
            } else {
                this._getBattleStateAction(newState, pokemon, sequenceAry);
            }
            pokemon.refreshBattleState();
        }
    },
    _getRemovePokemonStateAction: function (pokemon, sequenceAry) {
        sequenceAry.push(new cc.CallFunc(function () {
            var ownBySelf = pokemon.ownBySelf();
            (ownBySelf ? this._playerBoard : this._enemyBoard).updateState(POKEMON_STATES.NORMAL);
        }.bind(this)));
    },
    _getDeadAction: function (pokemon, sequenceAry) {
        var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
        sequenceAry.push(new cc.DelayTime(0.5));
        // 死亡叫声
        sequenceAry.push(new cc.CallFunc(function () {
            var audioId = ex.GameAudioEngine.getInstance().play2d(cc.formatStr("sounds/cries/%s.wav", pokemon.getFormatedId()));
            ex.GameAudioEngine.getInstance().setFinishCallback(audioId, function (id, name) {
                ex.GameAudioEngine.getInstance().uncache(audioId);
            });
            this._shouldInterupt = true;
            pokemon.leaveBattle();
            (pokemon.ownBySelf() ? this._pokemon1 : this._pokemon2).stop();
        }.bind(this)));
        sequenceAry.push(new cc.DelayTime(2));
        // 死亡动画 todo
        sequenceAry.push(dialogVc.getTextAction(cc.formatStr("%s%s倒下了", (pokemon.ownBySelf() ? "我方" : "敌方"), pokemon.getInfo().getName())));
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
        var dialogVc = this.scene().getViewControllerByIdentifier(BATTLE_DIALOG_VC_NAME);
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
            sequenceAry.push(dialogVc.getTextAction(cc.formatStr("%s%s%s", (ownBySelf ? "我方" : "敌方"), pokemon.getInfo().getName(), BATTLE_STATE_SUFFIX[state])));
        }
    },
    _pokemon1: null,
    _pokemon2: null,
    _field1: null,
    _field2: null,
    _playerBoard: null,
    _enemyBoard: null,
    _shouldInterupt: null,
    _musicId: null,
});
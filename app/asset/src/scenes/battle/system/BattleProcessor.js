/**
 * Created by Maple on 8/23/15.
 */

var BattleProcessor = cc.Class.extend({
    ctor: function (pokemon1, pokemon2, aiLevel) {
        if (!(pokemon1 instanceof Pokemon) || !(pokemon2 instanceof Pokemon)) {
            mw.error("不合法的参数 BattleProcessor创建失败");
            return;
        }
        aiLevel = aiLevel || BattleAI.AI_LEVELS.IDIOT;
        this._pokemon1 = pokemon1;
        this._pokemon2 = pokemon2;
        var com = MakeBindable(this._pokemon2).addComponent("BattleAI");
        logBattle("AI LEVEL: %d", aiLevel);
        com.setAILevel(aiLevel);

        this._field1BuffList = [];
        this._field2BuffList = [];
        this._behaviorQueue = [];
    },
    getFriendPokemon: function () {
        return this._pokemon1;
    },
    getEnemyPokemon: function () {
        return this._pokemon2;
    },
    prepareForTurn: function (behavior) {
        var enemyBehavior = this._pokemon2.getComponent("BattleAI").think();
        if (behavior.getPriority() >= enemyBehavior.getPriority()) {
            // 玩家先行动
            this._behaviorQueue.push(behavior);
            this._behaviorQueue.push(enemyBehavior);
        } else {
            // 敌人先行动
            this._behaviorQueue.push(enemyBehavior);
            this._behaviorQueue.push(behavior);
        }
    },
    battleBegin: function () {
        // 战斗开始
    },
    beginTurn: function () {
        // 回合开始
    },
    endTurn: function () {
        // 回合结束
        Notifier.notify(BATTLE_EVENTS.TURN_ENDED);
    },
    endBattle: function () {
        // 战斗结束
        Notifier.notify(BATTLE_EVENTS.BATTLE_ENDED);
    },
    process: function () {
        var behavior = this._behaviorQueue.shift();
        if (behavior) {
            behavior.process();
        } else {
            if (this._pokemon1.isDead() || this._pokemon2.isDead()) {
                this.endBattle();
            } else {
                this.endTurn();
            }
        }
    },
    clearBehaviorQueue: function () {
        this._behaviorQueue = [];
    },
    checkStateBeforeUseSkill: function (pokemon) {
        // 异常状态 todo
        // 战斗状态
        if (pokemon.checkBattleState(BATTLE_STATES.TIRED) > 0) {
            return {
                skip: true,
                state: BATTLE_STATES.TIRED,
            };
        }
        if (pokemon.checkBattleState(BATTLE_STATES.SCARED) > 0) {
            return {
                skip: true,
                state: BATTLE_STATES.SCARED,
            };
        }
        var battleStateInfo = { state: BATTLE_STATES.NORMAL };
        var turns = pokemon.checkBattleState(BATTLE_STATES.CONFUSED);
        if (turns >= 0) {
            battleStateInfo["state"] = BATTLE_STATES.CONFUSED;
            if (turns == 0) {
                battleStateInfo["eliminated"] = true;
            } else {
                // 50%概率攻击自己
                var rd = Math.ceil(Math.random() * 100);
                if (rd <= 50) {
                    // 随机对自身造成最大HP的10%-25%的伤害
                    var rdHurt = Math.floor((Math.floor(Math.random() * 16) + 10) / 100 * pokemon.getBasicValues()[0]);
                    battleStateInfo["hurt"] = rdHurt;
                }
            }
        } else {
            turns = pokemon.checkBattleState(BATTLE_STATES.CONFUSED);
            if (turns >= 0) {
                battleStateInfo["state"] == BATTLE_STATES.CONFUSED;
                if (turns == 0) {
                    battleStateInfo["eliminated"] = true;
                } else {
                    battleStateInfo["skip"] = true;
                }
            }
        }
        return { battleState: battleStateInfo };
    },
    analyzeSkill: function (skillUser, skillInfo) {
        var otherPokemon = skillUser.ownBySelf() ? this._pokemon2 : this._pokemon1;
        var targetType = skillInfo.getTarget();
        var target = null;
        // 暂未考虑混乱 todo
        if (targetType == SKILL_TARGET_TYPES.SINGLE_ENEMY) {
            target = otherPokemon;
        } else if (targetType == SKILL_TARGET_TYPES.ALL_ENEMIES) {
            target = otherPokemon;
        } else if (targetType == SKILL_TARGET_TYPES.SELF) {
            target = skillUser;
        } else if (targetType == SKILL_TARGET_TYPES.EXCEPT_SELF) {
            target = otherPokemon;
        } else if (targetType == SKILL_TARGET_TYPES.RANDOM_ENEMY) {
            target = otherPokemon;
        } else if (targetType == SKILL_TARGET_TYPES.SELF_FIELD) {
            target = this._field1BuffList;
        } else if (targetType == SKILL_TARGET_TYPES.ENEMY_FIELD) {
            target = this._field2BuffList;
        } else if (targetType == SKILL_TARGET_TYPES.FRIEND) {
            target = null;
        } else if (targetType == SKILL_TARGET_TYPES.WAITING) {
            target = null;
        } else if (targetType == SKILL_TARGET_TYPES.UNKNOWN) {
            target = null;
        } else if (targetType == SKILL_TARGET_TYPES.ANY) {
            target = null;
        }
        var handler = this["_skill" + skillInfo.getHandler()];
        cc.assert(handler instanceof Function, "未实现的技能逻辑处理函数");
        var result = handler.call(this, skillUser, target, skillInfo);

        return result;
    },
    _calculateHurt: function (attacker, defender, skillInfo) {
        var skillAtk = skillInfo.getAttack();
        if (skillAtk == null) {
            // 需要特殊处理 todo
            skillAtk = 40;
        }
        var skillProp = skillInfo.getProperty();
        var attackerAbilityLevels = attacker.getAbilityLevels();
        var defenderAbilityLevels = defender.getAbilityLevels();
        // 基础攻击
        var attackerAtk = skillInfo.getType() == SKILL_TYPES.PHYSICAL ? attacker.getBasicValues()[1] : attacker.getBasicValues()[3];
        // 基础防御
        var defenderDef = skillInfo.getType() == SKILL_TYPES.PHYSICAL ? defender.getBasicValues()[2] : defender.getBasicValues()[4];
        // 能力等级修正 如果防御方有天然特性跳过此步骤 todo
        var abilityAtkCorrection = 1 + (skillInfo.getType() == SKILL_TYPES.PHYSICAL ? attackerAbilityLevels[0] : attackerAbilityLevels[2]) * 0.1;
        var abilityDefCorrection = 1 + (skillInfo.getType() == SKILL_TYPES.PHYSICAL ? defenderAbilityLevels[1] : defenderAbilityLevels[3]) * 0.1;
        attackerAtk *= abilityAtkCorrection;
        defenderDef *= abilityDefCorrection;
        // 各种特性修正 todo
        // 基础伤害
        var basicHurt = Math.floor(((attacker.getLevel() * 2 / 5 + 2) * skillAtk * attackerAtk / defenderDef) / 50 + 2);
        // 天气修正 todo
        // 会心一击修正 todo
        var criticalCorrection = 1;
        // 暂定5%的会心率 还没有会心等级计算
        if (Math.ceil(Math.random() * 100) <= 5) {
            criticalCorrection = 1.5;
        }
        // 随机数修正
        var randomCorrection = (Math.ceil(Math.random() * 15) + 85) / 100;
        // 属性修正
        var defenderProps = defender.getInfo().getProperties();
        var propertyCorrection = 1;
        for (var index in defenderProps) {
            var prop = defenderProps[index];
            propertyCorrection *= PROPERTY_MULTIPLIER[skillProp][prop];
        }
        // 本系属性修正
        var pokemonPropCorrection = 1;
        var attackerProps = attacker.getInfo().getProperties();
        for (var i in attackerProps) {
            if (attackerProps[i] === skillProp) {
                pokemonPropCorrection = 1.2;
                break;
            }
        }
        // 烧伤修正 todo
        // 实际伤害修正 todo
        basicHurt = Math.floor(basicHurt * randomCorrection * criticalCorrection * propertyCorrection * pokemonPropCorrection);

        logBattle("会心一击修正: " + criticalCorrection.toString());
        logBattle("属性修正: " + propertyCorrection.toString());
        logBattle("本系属性修正: " + pokemonPropCorrection.toString());
        logBattle("伤害: %d", basicHurt);
        var hurtInfo = {
            hurt: basicHurt,
            criticalCorrection: criticalCorrection,
            propertyCorrection: propertyCorrection,
            didHit: true,
        };

        return hurtInfo;
    },
    _pokemon1: null,
    _pokemon2: null,
    _field1BuffList: null,
    _field2BuffList: null,
    _weather: null,
    _behaviorQueue: null,


    /**
     * 技能处理函数
     */
    // 攻击单体
    _skillAttackOne: function (skillUser, target, skillInfo) {
        var logicParams = skillInfo.getLogicParams();
        var params = null;
        if (logicParams && logicParams.length > 0) {
            params = logicParams.split(";");
        }
        if (params) {
            // 特殊情形 (逆鳞类似技能)
            if (params[0] == 1 && skillUser.getRepeat() == 0) {
                var args = params[1].split(",");
                var min = parseInt(args[0]);
                var max = parseInt(args[1]);
                var state = parseInt(args[2]);
                var rd = Math.floor(Math.random() * (max - min + 1));
                rd += min;
                skillUser.setRepeat(rd);
                skillUser.setNextBattleState(state);
            }
        }
        var hurtInfo = this._calculateHurt(skillUser, target, skillInfo);
        hurtInfo["attacker"] = skillUser;
        hurtInfo["defender"] = target;
        hurtInfo["delta"] = target.hurt(hurtInfo["hurt"]);
        hurtInfo["isHurtSkill"] = true;
        hurtInfo["targetType"] = 1;

        if (skillUser.getRepeat() > 0) {
            skillUser.reduceRepeat();
        }

        return hurtInfo;
    },
    // 攻击敌方全体
    _skillAttackEnemyAll: function (skillUser, target, skillInfo) {
        var logicParams = skillInfo.getLogicParams();
        var params = null;
        if (logicParams && logicParams.length > 0) {
            params = logicParams.split(";");
        }
        var hurtInfo = this._calculateHurt(skillUser, target, skillInfo);
        hurtInfo["attacker"] = skillUser;
        hurtInfo["defender"] = target;
        hurtInfo["delta"] = target.hurt(hurtInfo["hurt"]);
        hurtInfo["isHurtSkill"] = true;
        hurtInfo["targetType"] = 1;

        return hurtInfo;
    },
    // 单体回复HP
    _skillRecoverOne: function (skillUser, target, skillInfo) {
        var logicParams = skillInfo.getLogicParams();
    },
});
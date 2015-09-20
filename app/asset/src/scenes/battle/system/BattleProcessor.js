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
    endTurn: function () {
        Notifier.notify(BATTLE_EVENTS.TURN_ENDED);
    },
    process: function () {
        var behavior = this._behaviorQueue.shift();
        if (behavior) {
            // 如果是伤害技能需要计算伤害
            if (behavior.getType() == BATTLE_BEHAVIORS.BATTLE) {
                if (behavior.getSkill().getType() != SKILL_TYPES.VARIATION) {
                    // 伤害技能
                    var skillInfo = behavior.getSkill();
                    var hurtInfo = this._calculateHurt(behavior.getOwner(), skillInfo);
                    behavior.process(hurtInfo);
                } else {
                    // 变化技能
                    behavior.process();
                }
            } else {
                behavior.process();
            }
        } else {
            if (this._pokemon1.isDead() || this._pokemon2.isDead()) {
                Notifier.notify(BATTLE_EVENTS.ALL_ENDED);
            } else {
                this.endTurn();
            }
        }
    },
    clear: function () {
        this._behaviorQueue = [];
    },
    _calculateHurt: function (pokemon, skillInfo) {
        var skillAtk = skillInfo.getAttack();
        if (skillAtk == null) {
            // 需要特殊处理 todo
            skillAtk = 40;
        }
        var skillProp = skillInfo.getProperty();
        var attacker = pokemon;
        var defender = pokemon.ownBySelf() ? this._pokemon2 : this._pokemon1;
        var attackerAbilityLevels = attacker.ownBySelf() ? this._pokemon1AbilityLevels : this._pokemon2AbilityLevels;
        var defenderAbilityLevels = defender.ownBySelf() ? this._pokemon1AbilityLevels : this._pokemon2AbilityLevels;
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
        // 烧伤修正 todo
        // 实际伤害修正 todo
        basicHurt = Math.floor(basicHurt * randomCorrection * criticalCorrection * propertyCorrection);

        logBattle("会心一击修正: " + criticalCorrection.toString());
        logBattle("属性修正: " + propertyCorrection.toString());
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
    _pokemon1AbilityLevels: [ 0, 0, 0, 0, 0 ],     // [ 攻击, 防御, 特攻, 特防, 速度 ]
    _pokemon2AbilityLevels: [ 0, 0, 0, 0, 0 ],
    _pokemon1BattleState: BATTLE_STATES.NORMAL,
    _pokemon2BattleState: BATTLE_STATES.NORMAL,
    _weather: null,
    _behaviorQueue: [],
});
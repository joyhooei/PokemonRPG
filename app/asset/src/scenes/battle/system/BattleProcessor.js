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
                behavior.process(20);
            } else {
                behavior.process();
            }
        } else {
            this.endTurn();
        }
    },
    _pokemon1: null,
    _pokemon2: null,
    _pokemon1AbilityLevels: [ 0, 0, 0, 0, 0 ],     // [ 攻击, 防御, 特攻, 特防, 速度 ]
    _pokemon2AbilityLevels: [ 0, 0, 0, 0, 0 ],
    _pokemon1BattleState: BATTLE_STATES.NORMAL,
    _pokemon2BattleState: BATTLE_STATES.NORMAL,
    _behaviorQueue: [],
});
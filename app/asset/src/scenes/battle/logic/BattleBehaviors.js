/**
 * Created by Maple on 9/4/15.
 */

var BattleBehavior = cc.Class.extend({
    ctor: function (type, pokemon) {
        this._type = type;
        this._owner = pokemon;
    },
    getType: function () {
        return this._type;
    },
    getOwner: function () {
        return this._owner;
    },
    getPriority: function () {
        cc.assert(false, "Override me.");
    },
    process: function () {
        cc.assert(false, "Override me.");
    },
    _type: null,
    _owner: null,
});

var SkillBehavior = BattleBehavior.extend({
    ctor: function (pokemon, skillInfo) {
        this._super(BATTLE_BEHAVIORS.BATTLE, pokemon);

        this._skill = skillInfo;
    },
    getSkill: function () {
        return this._skill;
    },
    getPriority: function () {
        return 0 * 1000 + this._owner.getBasicValues()[5];
    },
    process: function () {
        logBattle("%d使用技能: %d", this._owner.getId(), this._skill.getId());
        if (this._owner.getRepeat() > 0) {
        } else {
            // 减去pp 压迫特性-2 todo
            this._owner.reducePP(this._skill.getId());
        }
        Notifier.notify(BATTLE_UI_EVENTS.PLAY_SKILL, this._owner, this._skill);
    },
    _skill: null,
});

var ChangePokemonBehavior = BattleBehavior.extend({
    ctor: function (pokemon, newPokemon) {
        this._super(BATTLE_BEHAVIORS.CHANGE_POKEMON, pokemon);

        this._newPokemon = newPokemon;
    },
    getNewPokemon: function () {
        return this._newPokemon;
    },
    getPriority: function () {
        return 100000;
    },
    _newPokemon: null,
});

var UseItemBehavior = BattleBehavior.extend({
    ctor: function (pokemon, item) {
        this._super(BATTLE_BEHAVIORS.USE_ITEM, pokemon);

        this._item = item;
    },
    getItem: function () {
        return this._item;
    },
    getPriority: function () {
        return 100000;
    },
    _item: null,
});

var EscapeBehavior = BattleBehavior.extend({
    ctor: function (pokemon) {
        this._super(BATTLE_BEHAVIORS.ESCAPE, pokemon);
    },
    getPriority: function () {
        return 100000;
    },
});
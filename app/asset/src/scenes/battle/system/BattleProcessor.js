/**
 * Created by Maple on 8/23/15.
 */

var BattleProcessor = cc.Class.extend({
    ctor: function (pokemon1, pokemon2) {
        if (!(pokemon1 instanceof Pokemon) || !(pokemon2 instanceof Pokemon)) {
            mw.error("不合法的参数 BattleProcessor创建失败");
            return;
        }
        this._pokemon1 = pokemon1;
        this._pokemon2 = pokemon2;
    },
    getFriendPokemon: function () {
        return this._pokemon1;
    },
    getEnemyPokemon: function () {
        return this._pokemon2;
    },
    _pokemon1: null,
    _pokemon2: null,
});
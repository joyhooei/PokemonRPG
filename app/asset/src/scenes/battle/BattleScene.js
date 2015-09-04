/**
 * Created by Maple on 8/15/15.
 */

var BattleScene = mw.GameScene.extend({
    ctor: function () {
        this._super();
    },
    onEnter: function () {
        this._super();

        Registry.addClass("BattleAI", BattleAI);
        this.loadViewController(new BattleUIViewController(), BATTLE_UI_VC_NAME);
        this.loadViewController(new BattleDialogViewController(new ModalViewSegue()), BATTLE_DIALOG_VC_NAME);
        this.loadViewController(new BattleOperationViewController(new ModalViewSegue()), BATTLE_OPERATION_VC_NAME);
    },
    onExit: function () {
        this._super();

        Registry.removeClass("BattleAI");
    },
    initBattleProcessor: function (pokemon1, pokemon2, aiLevel) {
        this._battleProcessor = new BattleProcessor(pokemon1, pokemon2, aiLevel);
    },
    getBattleProcessor: function () {
        return this._battleProcessor;
    },
    _battleProcessor: null,
});
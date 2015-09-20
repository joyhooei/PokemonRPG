/**
 * Created by Maple on 8/19/15.
 */

/**
 * 负责战斗对话框的控制 包括文字显示、对下一次文字的控制 等等
 */
var BattleDialogViewController = DialogBaseViewController.extend({
    ctor: function (segue) {
        this._super(segue);
    },
    viewDidLoad: function () {
        this._super();
    },
    viewDidUnload: function () {
        this._super();
    },
    didReceiveMemoryWarning: function () {
        this._super();
    },
    _addObservers: function () {
        this._super();

        Notifier.addObserver(DIALOG_EVENTS.SHOW_DIALOG_WITH_BATTLE_ANIMATION, this, this._onShowDialogWithBattleAnimation);
        Notifier.addObserver(BATTLE_EVENTS.TURN_ENDED, this, this._onTurnEnded);
    },
    _removeObservers: function () {
        this._super();

        Notifier.removeObserver(DIALOG_EVENTS.SHOW_DIALOG_WITH_BATTLE_ANIMATION, this);
        Notifier.removeObserver(BATTLE_EVENTS.TURN_ENDED, this);
    },
    _renderView: function () {
        this._super();
    },
    // event handlers
    _onShowDialogWithBattleAnimation: function (pokemonModel, skillInfo, dmg) {
        var text = cc.formatStr("%s%s使用了技能%s", (pokemonModel.ownBySelf() ? "我方" : "敌方"), pokemonModel.getInfo().getName(), skillInfo.getName());
        this._canSkip = false;
        this._showDialogWithCallback(text, function () {
            Notifier.notify(BATTLE_UI_EVENTS.PLAY_SKILL, pokemonModel, skillInfo, dmg);
        });
    },
    _onTurnEnded: function () {
        this.clearText();
    },
});
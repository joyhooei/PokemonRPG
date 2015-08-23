/**
 * Created by Maple on 8/19/15.
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
    },
    _renderView: function () {
        this._super();

        this.segue().setEnabled(false);
        mw.log("SIZE: %d", this._lblMsg.getString().length);
    },
});
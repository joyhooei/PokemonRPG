/**
 * Created by Maple on 8/9/15.
 */

var ModalViewSegue = mw.ViewSegue.extend({
    ctor: function () {
        this._super();
    },
    viewReadyToSegue: function (vc) {
    },
    viewDidSegue: function (vc) {
        var listener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: MakeScriptHandler(this, this.onTouchBegan),
        });
        cc.eventManager.addListener(listener, vc.view());
    },
    viewDidSegueBack: function (vc) {
    },
    onTouchBegan: function (touch, event) {
                                         mw.log("Segue Hook Touch");
        return true;
    }
});
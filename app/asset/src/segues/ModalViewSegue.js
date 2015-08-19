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
        this._listener = listener;
    },
    viewDidSegueBack: function (vc) {
    },
    setEnabled: function (isEnabled) {
        if (this._listener) {
            this._listener.setEnabled(isEnabled);
        }
    },
    isEnabled: function () {
        if (this._listener) {
            return this._listener.isEnabled();
        }
        return false;
    },
    onTouchBegan: function (touch, event) {
        return true;
    },
    _listener: null,
});
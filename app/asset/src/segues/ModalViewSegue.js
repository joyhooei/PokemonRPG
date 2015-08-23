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
            onTouchBegan: MakeScriptHandler(this, this._onTouchBegan),
            onTouchMoved: MakeScriptHandler(this, this._onTouchMoved),
            onTouchEnded: MakeScriptHandler(this, this._onTouchEnded),
            onTouchCancelled: MakeScriptHandler(this, this._onTouchCancelled),
        });
        cc.eventManager.addListener(listener, vc.view());
        this._listener = listener;
    },
    viewDidSegueBack: function (vc) {
    },
    setDelegate: function (delegate) {
        this._delegate = delegate;
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
    _onTouchBegan: function (touch, event) {
        if (this._delegate && this._delegate.onTouchBegan instanceof Function) {
            this._delegate.onTouchBegan(touch, event);
        }
        return true;
    },
    _onTouchMoved: function (touch, event) {
        if (this._delegate && this._delegate.onTouchMoved instanceof Function) {
            this._delegate.onTouchMoved(touch, event);
        }
    },
    _onTouchEnded: function (touch, event) {
        if (this._delegate && this._delegate.onTouchEnded instanceof Function) {
            this._delegate.onTouchEnded(touch, event);
        }
    },
    _onTouchCancelled: function (touch, event) {
        if (this._delegate && this._delegate.onTouchCancelled instanceof Function) {
            this._delegate.onTouchCancelled(touch, event);
        }
    },
    _listener: null,
    _delegate: null,
});
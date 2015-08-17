/**
 * Created by Maple on 7/20/15.
 */

mw.GameScene.extend = cc.Class.extend;
mw.ViewController.extend = cc.Class.extend;
mw.ViewSegue.extend = cc.Class.extend;
mw.NetHandler.extend = cc.Class.extend;

// _ctor初始化做init操作
mw.GameScene.prototype._ctor = function() {
    if (arguments.length == 0) {
        mw.GameScene.prototype.init.call(this);
    }
};

mw.ViewController.prototype._ctor = function() {
    if (arguments.length == 1) {
        mw.ViewController.prototype.init.apply(this, arguments);
    }
};

mw.ViewSegue.prototype._ctor = function() {
    if (arguments.length == 0) {
        mw.ViewSegue.prototype.init.call(this);
    }
};
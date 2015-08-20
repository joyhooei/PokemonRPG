/**
 * Created by Maple on 7/20/15.
 */

mw.GameScene.extend = cc.Class.extend;
mw.ViewController.extend = cc.Class.extend;
mw.ViewSegue.extend = cc.Class.extend;
mw.NetHandler.extend = cc.Class.extend;

var reportArgsError = function (className) {
    cc.assert(false, "Wrong number of arguments when creating " + className + ".");
};

// _ctor初始化做init操作
mw.GameScene.prototype._ctor = function() {
    if (arguments.length == 0) {
        mw.GameScene.prototype.init.call(this);
    } else {
        reportArgsError("mw.GameScene");
    }
};

mw.ViewController.prototype._ctor = function() {
    if (arguments.length >= 0 && arguments.length <= 1) {
        var segue = arguments[0];
        if (segue) {
            mw.ViewController.prototype.init.apply(this, arguments);
        }
    } else {
        reportArgsError("mw.ViewController");
    }
};

mw.ViewSegue.prototype._ctor = function() {
    if (arguments.length == 0) {
        mw.ViewSegue.prototype.init.call(this);
    } else {
        reportArgsError("mw.ViewSegue");
    }
};
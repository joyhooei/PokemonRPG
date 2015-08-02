/**
 * Created by Maple on 8/2/15.
 */

mw = mw || new Object();

var Observer = cc.Class.extend({
    ctor: function(sender, callback, args) {
        cc.assert(sender instanceof Object, "Invalid sender param.");
        cc.assert(callback instanceof Function, "Invalid callback param.");
        this._sender = sender;
        this._callback = callback;
        this._params = (args instanceof Array) || [];
    },
    call: function(args) {
        this._callback.apply(this._sender, this._params.concat(args));
    },
});

/**
 * 通知中心 需要定义好的event 观察者的对象 回调函数 以及自定义参数(缺省)
 * addObserver为某一事件添加一个观察者
 * removeObserver可以移除某个事件 某个对象的 一个或所有观察者
 * notify触发事件 并传递事件参数
 * @type {{addObserver: Function, removeObserver: Function, notify: Function, _observerMap: Object}|*}
 */
mw.Notifier = mw.Notifier || {
        addObserver: function() {
            cc.assert(arguments.length >= 3, "mw.Notifier.addObserver至少需要3个参数");
            var event = Array.prototype.shift.apply(arguments);
            var sender = Array.prototype.shift.apply(arguments);
            var callback = Array.prototype.shift.apply(arguments);
            var args = Array.prototype.slice.apply(arguments);
            cc.assert(typeof event == "string", "event必须是一个字符串");
            cc.assert(sender instanceof Object, "sender必须是一个对象");
            cc.assert(callback instanceof Function, "callback必须是一个函数");

            if (this._observerMap[event] == undefined) {
                this._observerMap[event] = [];
            }
            var ob = new Observer(sender, callback, args);
            this._observerMap[event].push(ob);
        },
        removeObserver: function() {
            cc.assert(arguments.length >= 2, "mw.Notifier.removeObserver至少需要2个参数");
            var event = Array.prototype.shift.apply(arguments);
            var sender = Array.prototype.shift.apply(arguments);
            var callback = Array.prototype.shift.apply(arguments);
            cc.assert(typeof event == "string", "event必须是一个字符串");
            cc.assert(sender instanceof Object, "sender必须是一个对象");
            cc.assert(callback instanceof Function, "callback必须是一个函数");

            if (this._observerMap[event] == undefined || this._observerMap[event].length <= 0) {
                return;
            }
            var i = 0;
            while (true) {
                var ob = this._observerMap[event][i];
                if (ob._sender == sender && (ob._callback == callback || callback == undefined)) {
                    this._observerMap[event].splice(i, 1);
                    --i;
                }
                ++i;
                if (i >= this._observerMap[event].length) {
                    break;
                }
            }
        },
        notify: function() {
            cc.assert(arguments.length >= 1, "mw.Notifier.notify至少需要1个参数");
            var event = Array.prototype.shift.apply(arguments);
            var args = Array.prototype.slice.apply(arguments);
            cc.assert(typeof event == "string", "event必须是一个字符串");
            for (var ev in this._observerMap) {
                if (ev == event) {
                    for (var i in this._observerMap[ev]) {
                        var ob = this._observerMap[ev][i];
                        ob.call(args);
                    }
                    break;
                }
            }
        },
        _observerMap: new Object(),
    };
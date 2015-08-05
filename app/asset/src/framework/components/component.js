/**
 * Created by Maple on 8/5/15.
 */

Registry = Registry || new Object();

var Component = cc.Class.extend({
    ctor: function (name, depends) {
        if (!depends || !(depends instanceof Array)) {
            depends = [];
        }
        this._name = name;
        this._depends = depends;
    },
    getName: function () {
        return this._name;
    },
    getDepends: function () {
        return this._depends;
    },
    getTarget: function () {
        return this._target;
    },
    exportMethods: function (methods) {
        if (!methods || !(methods instanceof Array)) {
            methods = [];
        }
        this._exportMethods = methods;
        for (var i in methods) {
            var methodName = methods[i];
            if (this._target[methodName]) {
                cc.assert(!this._target[methodName], "绑定组件失败 重复的组件函数");
            }
            var method = this[methodName];
            if (!(method instanceof Function)) {
                continue;
            }
            this._target[methodName] = function() {
                return method.apply(this, Array.prototype.slice.call(arguments));
            };
        }
        return this;
    },
    _bind: function (target) {
        this._target = target;
        for (var i in this._depends) {
            var depend = this._depends[i];
            if (!this._target.getComponent(depend)) {
                this._target.addComponent(depend);
            }
        }
        this.onBind();
    },
    _unbind: function () {
        for (var i in this._exportMethods) {
            var methodName = this._exportMethods[i];
            this._target[methodName] = undefined;
        }
        this.onUnbind();
    },
    onBind: function () {
    },
    onUnbind: function () {
    },
    _target: null,
    _name: null,
    _depends: null,
    _exportMethods: null,
});
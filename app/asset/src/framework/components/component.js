/**
 * Created by Maple on 8/5/15.
 */

/**
 * 组件基类 组件化编程的基础
 * 通过exportMethods返回函数名列表来使绑定组件的对象 获得组件的能力
 * 先通过MakeBindable函数使对象获得绑定组件的能力 再通过addComponent和removeComponent来控制绑定的组件
 * e.g.
 * var target = new cc.Node();
 * var com = MakeBindable(target).addComponent(COMPONENT_NAME);
 * com.COMPONENT_METHOD();
 * target.getComponent(COMPONENT_NAME).COMPONENT_METHOD();
 * @type {Function}
 */
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
    _bind: function (target) {
        this._target = target;
        for (var i in this._depends) {
            var depend = this._depends[i];
            if (!(this._target.getComponent(depend))) {
                this._target.addComponent(depend);
            }
        }
        this.onBind(target);
    },
    _unbind: function () {
        for (var i in this._exportMethods) {
            var methodName = this._exportMethods[i];
            this._target[methodName] = undefined;
        }
        this.onUnbind();
    },
    onBind: function (target) {
    },
    onUnbind: function () {
    },
    _target: null,
    _name: null,
    _depends: null,
});
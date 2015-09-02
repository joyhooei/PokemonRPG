/**
 * Created by Maple on 8/5/15.
 */

/**
 * 全局注册表
 * newObject只能是无参构造器
 * @type {Object|*}
 */
var Registry = {
    addClass: function (name, cls) {
        if (this._classes[name]) {
            cc.log("注册表中已存在该key");
            return;
        }
        this._classes[name] = cls;
    },
    removeClass: function (name) {
        this._classes[name] = undefined;
    },
    newObject: function (name) {
        if (this._classes[name] === undefined) {
            cc.log("注册表中不存在该key");
            return;
        }
        var obj = new this._classes[name]();
        return obj;
    },
    _classes: {},
};
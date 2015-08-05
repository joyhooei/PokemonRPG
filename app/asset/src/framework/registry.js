/**
 * Created by Maple on 8/5/15.
 */

/**
 * 全局注册表
 * @type {Object|*}
 */
Registry = new Object();

Registry.addDefinition = function (name, cls) {
    if (Registry[name]) {
        cc.log("注册表中已存在该key");
        return;
    }
    Registry[name] = cls;
};

Registry.removeDefinition = function (name) {
    Registry[name] = undefined;
};

Registry.newObject = function () {
    var name = Array.prototype.shift.call(arguments);
    var args = Array.prototype.slice.call(arguments);
    if (Registry[name] === undefined) {
        cc.log("注册表中不存在该key");
        return;
    }
    var obj = new Registry[name]();
    obj.ctor.apply(obj, args);
    return obj;
}
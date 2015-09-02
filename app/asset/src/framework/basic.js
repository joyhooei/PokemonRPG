/**
 * Created by Maple on 7/24/15.
 */

/**
 * 创建扩展回调函数
 * @param target 函数所属对象
 * @param selector 对象的成员函数
 * @param ... 自定义参数
 * @returns {Function}
 */
function MakeScriptHandler() {
    if (arguments.length < 2) {
        mw.error("Wrong parameters count of MakeScriptHandler");
        return null;
    }
    var target = Array.prototype.shift.call(arguments);
    var selector = Array.prototype.shift.call(arguments);
    if (typeof selector != "function") {
        mw.error("Invalid parameters of MakeScriptHandler");
        return null;
    }
    var args = Array.prototype.slice.call(arguments);

    return function() {
        var internalArgs = Array.prototype.slice.call(arguments);
        return selector.apply(target, internalArgs.concat(args));
    }
}

/**
 * 延迟一段时间后调用回调
 * @param target 函数所属对象
 * @param selector 对象的成员函数
 * @param delay 延迟(s)，0表示一帧间隔
 * @param ... 自定义参数
 */
function CallFunctionAsync() {
    if (arguments.length < 3) {
        mw.error("Wrong parameters count of CallFunctionAsync");
        return;
    }
    var target = Array.prototype.shift.call(arguments);
    var selector = Array.prototype.shift.call(arguments);
    var delay = Array.prototype.shift.call(arguments);
    if (typeof selector != "function" || typeof delay != "number") {
        mw.error("Invalid parameters of CallFunctionAsync");
        return;
    }
    if (delay < 0) {
        delay = 0;
    }
    var args = Array.prototype.slice.call(arguments);

    var scheduleSelector = function() {
        selector.apply(target, args);
    };
    cc.director.getScheduler().schedule(scheduleSelector, target, delay, 0, delay, false, mw.UUIDGenerator.getInstance().generateUUID());
}

/**
 * 将Json对象转换成js字面量对象
 * @param json mw.JsonObject/mw.JsonArray
 * @returns {*} 如果成功则返回js对象 否则返回null
 */
function JsonToJsObject(json) {
    if (!(json instanceof mw.JsonObject) && !(json instanceof mw.JsonArray)) {
        return null;
    }
    var jsObj = null;
    eval("var jsObj = " + json.toJsString() + ";");
    return jsObj;
}

/**
 * 使对象获得绑定组件的功能
 * @param target 绑定对象 必须是个Object
 * @returns 绑定对象
 */
function MakeBindable(target) {
    target._components = [];

    target.addComponent = function (name) {
        var component = Registry.newObject(name);
        this._components[name] = component;
        component._bind(this);
        return component;
    }.bind(target);
    target.removeComponent = function (name) {
        var component = this._components[name];
        if (component) {
            component._unbind();
        }
        this._components[name] = undefined;
    }.bind(target);
    target.getComponent = function (name) {
        return this._components[name];
    }.bind(target);
    return target;
}
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
    if (arguments.length < 2) {}
    var target = arguments.shift();
    var selector = arguments.shift();
    if (typeof selector != "function") {}
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
 * @returns scheduleId 计时器句柄
 */
function CallFunctionAsync() {
    if (arguments.length < 3) {}
    var target = arguments.shift();
    var selector = arguments.shift();
    var delay = arguments.shift();
    if (!target instanceof cc.Node || typeof selector != "function" || typeof delay != "number") {}
    if (delay < 0) {
        delay = 0;
    }
    var args = Array.prototype.slice.call(arguments);

    var scheduleId = 0;
    var scheduleSelector = function() {
        selector.apply(target, args);
        cc.Director.getInstance().getScheduler().unscheduleScriptEntry(scheduleId);
    }
    scheduleId = cc.Director.getInstance().getScheduler().scheduleScriptFunc(scheduleSelector, delay, false);

    return scheduleId;
}
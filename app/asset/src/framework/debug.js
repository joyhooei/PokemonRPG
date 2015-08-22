/**
 * Created by Maple on 8/2/15.
 */

mw = mw || new Object();

/**
 * 打印时间戳的log
 * e.g. mw.log("%d + %d = %d", 1, 2, 1 + 2);
 */
mw.log = function() {
    var fmt = Array.prototype.shift.apply(arguments);
    var args = Array.prototype.slice.apply(arguments);
    args.unshift(Date.now());
    args.unshift("[TIME_STAMP: %d]\t" + fmt);
    cc.log.apply(cc, args);
};

/**
 * 打印自定义tag的log
 * e.g. mw.logWithTag("winder", "%d + %d = %d", 1, 2, 1 + 2);
 */
mw.logWithTag = function() {
    var tag = Array.prototype.shift.apply(arguments);
    var fmt = Array.prototype.shift.apply(arguments);
    var args = Array.prototype.slice.apply(arguments);
    args.unshift(tag.toUpperCase());
    args.unshift("[%s]\t" + (fmt || ""));
    cc.log.apply(cc, args);
};

/**
 * 打印错误的log
 * mw.error("错误发生: %s", errorStr);
 */
mw.error = function() {
    var args = Array.prototype.slice.apply(arguments);
    args.unshift("error");
    mw.logWithTag.apply(mw, args);
};

/**
 * 打印js对象的字面量
 * @param obj 一般是Array或字面量对象 否则会出现非预期的结果
 */
mw.dump = function(obj) {
    if (!(obj instanceof Object)) {
        console.log(obj);
        return;
    }
    var __dump = function(data, prefix) {
        prefix = prefix || "";
        var prefix_next = prefix + "\t";
        var str = prefix + "{";
        for (var k in data) {
            var val = data[k];
            if (val instanceof Function) {
                continue;
            }
            str = str + "\n" + prefix_next + k + ": ";
            if (val instanceof Object) {
                str = str + "\n" +  __dump(val, prefix_next);
            } else {
                str = str + val.toString();
            }
        }
        str = str + "\n" + prefix + "}";
        return str;
    };
    console.log(__dump(obj));
};

/**
 * 定义作废的类
 * @param oldClass 作废的类名
 * @param newClass 替换的类名
 */
mw.deprecateClass = function(oldClass, newClass) {
    if (typeof oldClass != "string" && typeof newClass != "string") {
        return;
    }
    cc.assert(false, "作废的类: " + oldClass + "  请使用: " + newClass);
};

/**
 * 定义作废的方法
 * @param oldMethod 作废的方法名
 * @param newMethod 替换的方法名
 */
mw.deprecateMethod = function(oldMethod, newMethod) {
    if (typeof oldMethod != "string" && typeof newMethod != "string") {
        return;
    }
    cc.assert(false, "作废的方法: " + oldMethod + "  请使用: " + newMethod);
};
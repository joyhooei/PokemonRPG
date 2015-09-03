/**
 * Created by Maple on 9/4/15.
 */

/**
 * 各自模块的调试开关在这里控制 避免过多的log
 */

var BATTLE_DEBUG = true;

function logBattle() {
    if (BATTLE_DEBUG) {
        var args = Array.prototype.slice.call(arguments);
        args.unshift("battle");
        mw.logWithTag.apply(null, args);
    }
}

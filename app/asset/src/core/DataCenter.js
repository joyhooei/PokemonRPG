/**
 * Created by Maple on 8/7/15.
 */

/**
 * 数据中心 全局数据都保存在这
 * @type {Object}
 */
var DataCenter = new Object();

DataCenter.getHero = function () {
    if (this._hero === undefined) {
        this._hero = new Hero("我是一只鸭", GENDER.MALE);
    }
    return this._hero;
};
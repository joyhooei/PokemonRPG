/**
 * Created by Maple on 8/2/15.
 */

/**
 * MVC架构中的所有Model必须继承此类
 * 使用Model时要注意以下几点:
 * 1) 在自己的Model中需要调用this._defineScheme(scheme)来定义自己Model的结构
 *    scheme的结构如下: { 属性名: [属性类型, 默认值], ... }
 * 2) 所有涉及到scheme的属性 不能直接赋值 而是通过this._setProperties(props)来修改
 * 3) 和Model本身结构无关的字段 不要定义到scheme中 定义成成员变量即可
 *
 * e.g.
 * var MyModel = ModelBase.extend({
 *     ctor: function(id, name, age) {
 *         this._super(id);
 *         this._defineScheme({
 *             name: [ "string", null ],
 *             age: [ function(val) {
 *                 return typeof age == "number" && age >= 0;
 *             }, 0 ]
 *         });
 *         this._setProperties({
 *             name: name,
 *             age: age,
 *         });
 *     },
 *     getName: function() {
 *         return this._name
 *     },
 *     getAge: function() {
 *         return this._age
 *     },
 *     grow: function() {
 *         this._setProperties({ age = this._age + 1 });
 *     },
 *     changeName: function(newName) {
 *         this._setProperties({ name = newName });
 *     },
 * });
 *
 */
var ModelBase = cc.Class.extend({
    ctor: function (id) {
        this._scheme = {
            id: [ "string", null ],
        };
        this._setProperties({
            id: id,
        });
    },
    getId: function () {
        return this._id;
    },
    _defineScheme: function (scheme) {
        if (this._inited) {
            return;
        }
        scheme = scheme || {};
        this._scheme = { id: [ "string", null ] };
        for (var propName in scheme) {
            var propAttr = scheme[propName];
            var propType = propAttr[0];
            var propDef = propAttr[1];
            if (propType) {
                var attrName = "_" + propName;
                this._scheme[propName] = propAttr;
                this[attrName] = propDef;
            }
        }
        this._inited = true;
    },
    _setProperties: function (props) {
        for (var propName in this._scheme) {
            if (props[propName] != undefined) {
                var propAttr = this._scheme[propName];
                var propType = propAttr[0];
                var propValue = props[propName];
                if (propType == undefined) {
                    mw.error("Scheme中不存在的属性: %s", propName);
                } else if (propType instanceof Function && propType(propValue)) {
                    this["_" + propName] = propValue;
                } else if (propValue === null || typeof propValue == propType) {
                    this["_" + propName] = propValue;
                } else {
                    mw.error("属性%s类型不匹配", propName);
                }
            }
        }
    },
    _id: null,
    _scheme: null,
    _inited: false,
});
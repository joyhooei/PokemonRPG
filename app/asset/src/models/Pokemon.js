/**
 * Created by Maple on 8/19/15.
 */

var Pokemon = ModelBase.extend({
    ctor: function (pokemonId) {
        var formatId = pokemonId.toString();
        var formatIdLen = formatId.length;
        for (var i = 0; i < 3 - formatIdLen; ++i) {
            formatId = "0".concat(formatId);
        }
        this._super(formatId);

        // 定义model结构
        this._defineScheme({
            name: [ "string", null ],   // 名称
            gender: [function (val) {
                return typeof val == "number" && val >= GENDER.MALE && val <= GENDER.FEMALE;
            }, GENDER.MALE ], // 性别
            property: [function (val) {
                return val instanceof Array;
            }],     // 属性
            shiny: [ "boolean", false ],    // 闪光
        });

        var db = mw.SqliteDb.openDb(DB_PATH);
        var data = db.executeQuery("select * from [pet_info] where [id] = '" + this.getNumberId().toString() + "';")[0];

        // 初始化
        this._setProperties({
            name: data["name"],
            gender: Math.ceil(Math.random() * 2),
            properties: data["property"].split(","),
        });
    },
    getNumberId: function () {
        return parseInt(this.getId());
    },
    getName: function () {
        return this._name;
    },
    getGender: function () {
        return this._gender;
    },
    getProperty: function () {
        return this._property;
    },
    isShiny: function () {
        return this._shiny;
    },
});
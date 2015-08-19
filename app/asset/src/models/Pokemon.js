/**
 * Created by Maple on 8/19/15.
 */

var Pokemon = ModelBase.extend({
    ctor: function (pokemonId) {
        this._super(pokemonId.toString());

        // 定义model结构
        this._defineScheme({
            name: [ "string", null ],   // 名称
            gender: [function (val) {
                return typeof val == "number" && val >= GENDER.MALE && val <= GENDER.FEMALE;
            }, GENDER.MALE ], // 性别
            properties: [function (val) {
                return val instanceof Array;
            }],     // 属性
        });

        var db = mw.SqliteDb.openDb(DB_PATH);
        var data = db.executeQuery("select * from [pet_info] where [id] = " + this._id)[0];

        // 初始化
        this._setProperties({
            name: name,
            gender: Math.ceil(Math.random() * 2),
            properties: data["property"].split(","),
        });
    },
});
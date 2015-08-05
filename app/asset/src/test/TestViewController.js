/**
 * Created by Maple on 6/27/15.
 */

var Person = ModelBase.extend({
    ctor: function(id, name, age) {
        this._super(id);
        this._defineScheme({
            name: [ "string", null ],
            age: [ "number", 0 ],
        });
        this._setProperties({
            id: id,
            name: name,
            age: age,
        });
    },
    getName: function () {
        return this._name;
    },
    getAge: function () {
        return this._age;
    },
    grow: function() {
        this._setProperties({
            age: this._age + 1,
        });
    },
    changeName: function(newName) {
        this._setProperties({
            name: newName,
        });
    },
    showInfo: function() {
        mw.log("My ID is %s, My name is %s. I am %d years old.", this.getId(), this.getName(), this.getAge());
    }
});

var TestViewController = mw.ViewController.extend({
    ctor: function() {
        this._super();
    },
    viewDidLoad: function() {
        mw.logWithTag("test_begin", "Test ZipData and GifSprite...");
        var zipData = mw.ZipData.createWithExistingFile("res/GIF/pokemon_gif5.rc");
        zipData.beginUnzip();
        var data1 = zipData.getCompressedFileData("487_o.gif", "7ujm,lp-");
        var data2 = zipData.getCompressedFileData("493.gif", "7ujm,lp-");
        zipData.endUnzip();
        var gif1 = mw.GifSprite.createWithRawData(data1);
        var gif2 = mw.GifSprite.createWithRawData(data2);

        var dict = mw.Dictionary.create();
        dict.setObjectForKey("GIF1", gif1);
        dict.setObjectForKey("GIF2", gif2);
        var keys = dict.allKeys();
        for (var i = 0; i < keys.length; ++i) {
            var key = keys[i];
            var gif = dict.objectForKey(key);
            gif.setPosition(cc.winSize.width * (0.25 + i * 0.5), cc.winSize.height * 0.5);
            this.view().addChild(gif);
            mw.log("GIF%d added.", i + 1);
        }
        mw.logWithTag("test_end");

        mw.logWithTag("test_begin", "Test SvgSprite...");
        var svg = mw.SvgSprite.createWithFile("res/tiger.svg");
        svg.setVectorScale(0.5);
        svg.setPosition(cc.winSize.width * 0.5, cc.winSize.height * 0.5);
        this.view().addChild(svg);
        mw.log("SVG added.");
        mw.logWithTag("test_end");

        mw.logWithTag("test_begin", "Test Sqlite...");
        var db = mw.SqliteDb.openDb("res/icon.jpg");
        var data = db.executeQuery("select * from [pet_info] where id = '493';");
        mw.dump(data);
        mw.logWithTag("test_end");

        mw.logWithTag("test_begin", "Test json...");
        var jsonObj = mw.JsonObject.create();
        jsonObj.putNumber("NUMBER", 123);
        jsonObj.putString("STRING", "abc");
        var innerJson = mw.JsonObject.create();
        innerJson.putString("Name", "\"Winder\"");
        innerJson.putNumber("Age", 24);
        jsonObj.putJsonObject("JSON_OBJECT", innerJson);
        var innerAry = mw.JsonArray.create();
        innerAry.appendNumber(999);
        innerAry.appendString("Thank you!");
        innerAry.appendBoolean(false);
        jsonObj.putJsonArray("JSON_ARRAY", innerAry);
        mw.log(jsonObj.toPrettyString());
        mw.dump(JsonToJsObject(jsonObj));
        mw.logWithTag("test_end");

        mw.logWithTag("test_begin", "Test some utils...");
        var reachabilityStrMap = [ "No network.", "Wifi", "WWAN" ];
        mw.log("NetStatus: %s", reachabilityStrMap[mw.SystemHelper.getInstance().checkNetStatus()]);
        mw.log("Generate UUID: %s", mw.UUIDGenerator.getInstance().generateUUID());
        mw.logWithTag("test_end");

        mw.logWithTag("test_begin", "Test model...");
        var p = new Person("WANXIN", "Winder", 24);
        p.showInfo();
        p.grow();
        p.grow();
        p.changeName("HongYe");
        p.showInfo();
        p.changeName(123);
        p.showInfo();
        mw.logWithTag("test_end");

        CallFunctionAsync(this, this.showSchedulerResult, 1, 123, "abc", [ 3, 2, 1 ]);
        CallFunctionAsync(this, this.showSchedulerResult, 2, 321, "cba", [ 3, 2, 1 ]);
    },
    viewDidUnload: function() {
    },
    showSchedulerResult: function() {
        for (var i = 0; i < arguments.length; ++i) {
            mw.log(arguments[i]);
        }
    },
});
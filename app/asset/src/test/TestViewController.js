/**
 * Created by Maple on 6/27/15.
 */

var TestViewController = mw.ViewController.extend({
    ctor: function() {
        this._super();
    },
    viewDidLoad: function() {
        cc.log("Test ZipData and GifSprite...");
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
            cc.log("GIF%d added.", i + 1);
        }

        cc.log("Test SvgSprite...");
        var svg = mw.SvgSprite.createWithFile("res/tiger.svg");
        svg.setVectorScale(0.5);
        svg.setPosition(cc.winSize.width * 0.5, cc.winSize.height * 0.5);
        this.view().addChild(svg);
        cc.log("SVG added.");

        cc.log("Test Sqlite...");
        var db = mw.SqliteDb.openDb("res/icon.jpg");
        var data = db.executeQuery("select * from [pet_info] where id = '493';");
        for (var k in data[0]) {
            cc.log(k, data[0][k]);
        }

        cc.log("Test json...");
        var jsonObj = mw.JsonObject.create();
        jsonObj.putNumber("NUMBER", 123);
        jsonObj.putString("STRING", "abc");
        cc.log(jsonObj.toPrettyString());

        cc.log("Test some utils...");
        var reachabilityStrMap = [ "No network.", "Wifi", "WWAN" ];
        cc.log("NetStatus: %s", reachabilityStrMap[mw.SystemHelper.getInstance().checkNetStatus()]);
        cc.log("Generate UUID: %s", mw.UUIDGenerator.getInstance().generateUUID());
    },
    viewDidUnload: function() {
    },
});
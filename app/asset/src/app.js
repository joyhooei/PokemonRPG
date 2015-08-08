
var App = cc.Class.extend({
    ctor: function() {
        jsb.fileUtils.addSearchPath("res");
    },
    run: function() {
        var scene = new DemoScene();
        cc.director.runScene(scene);
    }
});
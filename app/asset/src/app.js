
var App = cc.Class.extend({
    ctor: function() {
        jsb.fileUtils.addSearchPath("res");
    },
    run: function() {
        var scene = new BattleScene();
        scene.addParameter("pokemon1", 644);
        scene.addParameter("pokemon2", 643);
        cc.director.runScene(scene);
    }
});
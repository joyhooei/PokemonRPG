
var App = cc.Class.extend({
    ctor: function() {
        jsb.fileUtils.addSearchPath("res");

        TextureManager.setPvrTexturesSupportPremultipliedAlpha(true);
    },
    run: function() {
        //var scene = new BattleScene();
        //scene.addParameter("pokemon1", "644");
        //scene.addParameter("pokemon2", "643");
        var scene=new DemoScene();
        cc.director.runScene(scene);
    }
});

var App = cc.Class.extend({
    ctor: function() {
        jsb.fileUtils.addSearchPath("res");

        TextureManager.setPvrTexturesSupportPremultipliedAlpha(true);
    },
    run: function() {
        var scene = new BattleScene();
        //scene.addParameter("pokemon1", "644");
        //scene.addParameter("pokemon2", "643");
        scene.addParameter("pokemon1", "637");
        scene.addParameter("pokemon2", "644");
        cc.director.runScene(new cc.TransitionFade(0.5, scene));
    }
});
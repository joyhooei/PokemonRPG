
var App = cc.Class.extend({
    ctor: function() {
        jsb.fileUtils.addSearchPath("res");

        ex.GameAudioEngine.getInstance().setMaxAudioInstance(10);
        TextureManager.setPvrTexturesSupportPremultipliedAlpha(true);
    },
    run: function() {
        var scene = new BattleScene();
        scene.addParameter("pokemon1", "644");
        scene.addParameter("pokemon2", "643");
        scene.addParameter("ai_level", "1");        // AI等级
        scene.addParameter("battle_type", "1");     // 野生精灵对战
        scene.addParameter("weather", "1");         // 天气
        cc.director.runScene(new cc.TransitionFade(0.5, scene));
    }
});
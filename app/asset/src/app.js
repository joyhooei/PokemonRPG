
var App = cc.Class.extend({
    ctor: function() {
    },
    run: function() {
        var scene = new TestScene();
        cc.director.runScene(scene);
    }
});
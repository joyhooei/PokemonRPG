/**
 * Created by Maple on 6/27/15.
 */

var TestScene = mw.GameScene.extend({
    ctor: function() {
        this._super();
        this.init();
    },
    onEnter: function() {
        this._super();
        this.loadViewController(new TestViewController(), "TEST_VIEW_CONTROLLER");
    },
    onExit: function() {
    	this._super();
    },
});
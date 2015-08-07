/**
 * Created by Maple on 8/7/15.
 */

var PlayScene = mw.GameScene.extend({
    ctor: function () {
        this._super();
    },
    onEnter: function() {
        this._super();
        this.loadViewController(new MapViewController(), "MAP_VIEW_CONTROLLER");
        this.loadViewController(new OperationViewController(), "OP_VIEW_CONTROLLER");
    },
    onExit: function() {
        this._super();
    }
});
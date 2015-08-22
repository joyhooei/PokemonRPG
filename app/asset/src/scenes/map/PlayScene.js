/**
 * Created by Maple on 8/7/15.
 */

var PlayScene = mw.GameScene.extend({
    ctor: function () {
        this._super();
    },
    onEnter: function() {
        this._super();
        this.loadViewController(new MapViewController(), MAP_VC_NAME);
        this.loadViewController(new OperationViewController(), OPERATION_VC_NAME);
    },
    onExit: function() {
        this._super();
    },
});
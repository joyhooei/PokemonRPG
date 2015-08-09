/**
 * Created by Maple on 8/7/15.
 */

/**
 * 玩家操作控制器 只负责一些玩家操作的逻辑
  */
var OperationViewController = mw.ViewController.extend({
    ctor: function (segue) {
        if (segue) {
            this._super(segue);
        } else {
            this._super();
        }
    },
    viewDidLoad: function () {
    },
    viewDidUnload: function () {
    }
});
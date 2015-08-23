/**
 * Created by Maple on 8/23/15.
 */

/**
 * 负责战斗用户操作 包括进行战斗、使用道具、更换精灵、逃跑 等等
 */
var BattleOperationViewController = mw.ViewController.extend({
    TEXTURES_TO_LOAD: {
        "common/common.plist": "common/common.pvr.ccz",
    },
    ctor: function (segue) {
        this._super(segue);
    },
    viewDidLoad: function () {
        this._loadTextures();
        this._addObservers();
        this._renderView();
    },
    viewDidUnload: function () {
        this._removeObservers();
        this._unloadTextures();
    },
    didReceiveMemoryWarning: function () {
    },
    _loadTextures: function () {
        for (var plist in this.TEXTURES_TO_LOAD) {
            var tex = this.TEXTURES_TO_LOAD[plist];
            TextureManager.loadTexture(plist, tex);
        }
    },
    _unloadTextures: function () {
        for (var plist in this.TEXTURES_TO_LOAD) {
            TextureManager.unloadTexture(plist);
        }
    },
    _addObservers: function () {
    },
    _removeObservers: function () {
    },
    _renderView: function () {
    },
});
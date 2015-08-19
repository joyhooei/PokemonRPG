/**
 * Created by Maple on 8/19/15.
 */

var BattleDialogViewController = mw.ViewController.extend({
    ctor: function (segue) {
        this._super(segue);
    },
    viewDidLoad: function () {
        this._loadTextures();
        this._renderView();
    },
    viewDidUnload: function () {
        this._unloadTextures();
    },
    _loadTextures: function () {
        var TEXTURES_TO_LOAD = {
        };
        for (var plist in TEXTURES_TO_LOAD) {
            var tex = TEXTURES_TO_LOAD[plist];
            TextureManager.loadTexture(plist, tex);
        }
    },
    _unloadTextures: function () {
        for (var plist in TEXTURES_TO_LOAD) {
            TextureManager.unloadTexture(plist);
        }
    },
    _renderView: function () {
    },
});
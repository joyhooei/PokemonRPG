/**
 * Created by Maple on 8/15/15.
 */

var TEXTURES_TO_LOAD = {

};

var BattleUIViewController = mw.ViewController.extend({
    ctor: function () {
        this._super();
    },
    viewDidLoad: function () {
        this._loadTextures();
        this._renderView();
    },
    viewDidUnload: function () {
        this._unloadTextures();
    },
    _loadTextures: function () {
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
/**
 * Created by Maple on 8/15/15.
 */

var BattleUIViewController = mw.ViewController.extend({
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
        this._pokemon1 = new Pokemon(this.scene().getNumberParameter("pokemon1"));
        this._pokemon2 = new Pokemon(this.scene().getNumberParameter("pokemon2"));


    },
});
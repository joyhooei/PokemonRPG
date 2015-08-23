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
    CCS_NAMES: {
        BG: "bg",
            BTN_BATTLE: "btn_battle",
            BTN_POKEMON: "btn_pokemon",
            BTN_ITEM: "btn_item",
            BTN_ESCAPE: "btn_escape",
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
        this._ccsNode = ccs.load("json/battle_board.json").node;
        this._ccsNode.setPosition(cc.director.getWinSize().width * 0.8, 80);
        this.view().addChild(this._ccsNode);

        var bg = this._ccsNode.getChildByName(this.CCS_NAMES.BG);
        var btnBattle = bg.getChildByName(this.CCS_NAMES.BTN_BATTLE);
        btnBattle.addClickEventListener(MakeScriptHandler(this, this._onBtnClicked));
        var btnPokemon = bg.getChildByName(this.CCS_NAMES.BTN_POKEMON);
        btnPokemon.addClickEventListener(MakeScriptHandler(this, this._onBtnClicked));
        var btnItem = bg.getChildByName(this.CCS_NAMES.BTN_ITEM);
        btnItem.addClickEventListener(MakeScriptHandler(this, this._onBtnClicked));
        var btnEscape = bg.getChildByName(this.CCS_NAMES.BTN_ESCAPE);
        btnEscape.addClickEventListener(MakeScriptHandler(this, this._onBtnClicked));
    },
    _onBtnClicked: function (sender) {
        mw.log("%s clicked.", sender.getName());
    },
    _ccsNode: null,
});
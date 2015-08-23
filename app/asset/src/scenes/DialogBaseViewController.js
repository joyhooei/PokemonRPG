/**
 * Created by Maple on 8/23/15.
 */

var DialogBaseViewController = mw.ViewController.extend({
    TEXTURES_TO_LOAD: {
        "common/common.plist": "common/common.pvr.ccz",
    },
    CCS_NAMES: {
        BG: "bg",
            MESSAGE: "message",
            INDICE: "indice",
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
        Notifier.addObserver(DIALOG_EVENTS.SHOW_DIALOG, this, this._onShowDialog);
    },
    _removeObservers: function () {
        Notifier.removeObserver(DIALOG_EVENTS.SHOW_DIALOG, this);
    },
    _renderView: function () {
        this._ccsNode = ccs.load("json/dialog_board.json").node;
        this._ccsNode.setPosition(cc.director.getWinSize().width * 0.5, 0);
        this.view().addChild(this._ccsNode);

        var bg = this._ccsNode.getChildByName(this.CCS_NAMES.BG);
        this._lblMsg = bg.getChildByName(this.CCS_NAMES.MESSAGE);
        this._indice = bg.getChildByName(this.CCS_NAMES.INDICE);

        var indiceAction = new cc.RepeatForever(new cc.Sequence(
            new cc.Show(),
            new cc.DelayTime(0.5),
            new cc.Hide(),
            new cc.DelayTime(0.5)
        ));
        this._indice.runAction(indiceAction);

        var listener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: MakeScriptHandler(this, this._onTouchBegan),
            onTouchEnded: MakeScriptHandler(this, this._onTouchEnded),
        });
        cc.eventManager.addListener(listener, this.view());
    },
    _onShowDialog: function (dialog) {
        this._showingDialog = dialog;
    },
    _onTouchBegan: function (touch, event) {
        return true;
    },
    _onTouchEnded: function (touch, event) {
    },
    _ccsNode: null,
    _lblMsg: null,
    _indice: null,
    _showingDialog: null,
});
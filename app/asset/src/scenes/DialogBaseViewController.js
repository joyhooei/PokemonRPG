/**
 * Created by Maple on 8/23/15.
 */

var DialogBaseViewController = mw.ViewController.extend({
    TEXTURES_TO_LOAD: {
        "texture/common.plist": "texture/common.pvr.ccz",
    },
    CCS_NAMES: {
        BG: "bg",
            MESSAGE: "message",
            INDICE: "indice",
    },
    DIALOG_SPEED: 0.125,
    DIALOG_SCHEDULE_KEY: "DIALOG_TICK",
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
        // 关闭计时器
        cc.director.getScheduler().unschedule(this.DIALOG_SCHEDULE_KEY, this.view());
    },
    didReceiveMemoryWarning: function () {
    },
    hide: function () {
        this._ccsNode.setVisible(false);
        this.segue().setEnabled(false);
    },
    show: function () {
        this._ccsNode.setVisible(true);
        this.segue().setEnable(true);
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

        this._lblMsg.setString("");
        this._indice.setVisible(false);

        var indiceAction = new cc.RepeatForever(new cc.Sequence(
            new cc.FadeIn(0.1),
            new cc.DelayTime(0.5),
            new cc.FadeOut(0.1),
            new cc.DelayTime(0.5)
        ));
        this._indice.runAction(indiceAction);

        this.segue().setDelegate(this);
    },
    _onShowDialog: function (dialog) {
        if (this._showingDialog) {
            mw.error("上次dialog尚未显示完成");
            return;
        }
        if (!this._ccsNode.isVisible()) {
            mw.error("需要先调用show才能执行以下操作");
            return;
        }
        this._showingDialog = dialog;
        this._indice.setVisible(false);
        var generatedDialogs = [];
        for (var i = 1; i <= this._showingDialog.length; ++i) {
            generatedDialogs.push(dialog.substr(0, i));
        }
        var index = 0;
        var onDialogTick = function (dt) {
            var text = generatedDialogs[index];
            this._lblMsg.setString(text);
            if (index == generatedDialogs.length - 1) {
                this._showingDialog = null;     // 置空
                this._indice.setVisible(true);
                // 关闭计时器
                cc.director.getScheduler().unschedule(this.DIALOG_SCHEDULE_KEY, this.view());
                return;
            }
            ++index;
        }.bind(this);
        // 开始积累游戏时间
        cc.director.getScheduler().schedule(onDialogTick, this.view(), this.DIALOG_SPEED, -1, 0, false, this.DIALOG_SCHEDULE_KEY);
    },
    onTouchEnded: function (touch, event) {
        if (this._showingDialog) {
            // 关闭计时器
            cc.director.getScheduler().unschedule(this.DIALOG_SCHEDULE_KEY, this.view());
            this._lblMsg.setString(this._showingDialog);
            this._indice.setVisible(true);
        } else {
            this._indice.setVisible(false);
            Notifier.notify(DIALOG_EVENTS.SHOW_NEXT_DIALOG);
        }
    },
    _ccsNode: null,
    _lblMsg: null,
    _indice: null,
    _showingDialog: null,
});
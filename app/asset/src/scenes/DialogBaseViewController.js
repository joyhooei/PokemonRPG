/**
 * Created by Maple on 8/23/15.
 */

var DialogBaseViewController = mw.ViewController.extend({
    TEXTURES_TO_LOAD: {
        "textures/common.plist": "textures/common.pvr.ccz",
    },
    CCS_NAMES: {
        BG: "bg",
            MESSAGE: "message",
            INDICE: "indice",
    },
    DIALOG_SPEED: 0.1,
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
    clearText: function () {
        this._lblMsg.setString("");
    },
    getTextAction: function (text) {
        var textList = [];
        for (var i = 1; i <= text.length; ++i) {
            textList.push(text.substr(0, i));
        }
        return new cc.TargetedAction(this._lblMsg, ex.UITextOneByOne.create(textList.length * this.DIALOG_SPEED, textList));
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
        Notifier.addObserver(DIALOG_EVENTS.SHOW_DIALOG_WITH_INDICE, this, this._onShowDialogWithIndice);
        Notifier.addObserver(DIALOG_EVENTS.SHOW_DIALOG_WITHOUT_INDICE, this, this._onShowDialogWithoutIndice);
    },
    _removeObservers: function () {
        Notifier.removeObserver(DIALOG_EVENTS.SHOW_DIALOG_WITH_INDICE, this);
        Notifier.removeObserver(DIALOG_EVENTS.SHOW_DIALOG_WITHOUT_INDICE, this);
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
    _showDialogWithCallback: function (dialog, callback) {
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
        var textAction = this.getTextAction(dialog);
        this._lblMsg.runAction(new cc.Sequence(
            textAction,
            new cc.CallFunc(function () {
                this._showingDialog = null;     // 置空
                if (callback instanceof Function) {
                    callback();
                }
            }.bind(this))
        ));
    },
    // segue delegate
    onTouchEnded: function (touch, event) {
        if (!this._canSkip) {
            return;
        }
        if (this._showingDialog) {
            this._lblMsg.stopAllActions();
            this._lblMsg.setString(this._showingDialog);
            this._indice.setVisible(true);
        } else {
            this._indice.setVisible(false);
            Notifier.notify(DIALOG_EVENTS.SHOW_NEXT_DIALOG);
        }
    },
    // event handlers
    _onShowDialogWithIndice: function (dialog) {
        this._canSkip = true;
        this._showDialogWithCallback(dialog, function () {
            this._indice.setVisible(true);
        }.bind(this));
    },
    _onShowDialogWithoutIndice: function (dialog, callback) {
        this._canSkip = false;
        this._showDialogWithCallback(dialog, callback);
    },
    _ccsNode: null,
    _lblMsg: null,
    _indice: null,
    _showingDialog: null,
    _canSkip: false,
});
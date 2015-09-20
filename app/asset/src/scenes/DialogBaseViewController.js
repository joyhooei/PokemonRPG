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
                // 关闭计时器
                cc.director.getScheduler().unschedule(this.DIALOG_SCHEDULE_KEY, this.view());
                if (callback instanceof Function) {
                    callback();
                }
                return;
            }
            ++index;
        }.bind(this);
        cc.director.getScheduler().schedule(onDialogTick, this.view(), this.DIALOG_SPEED, cc.REPEAT_FOREVER, 0, false, this.DIALOG_SCHEDULE_KEY);
    },
    // segue delegate
    onTouchEnded: function (touch, event) {
        if (!this._canSkip) {
            return;
        }
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
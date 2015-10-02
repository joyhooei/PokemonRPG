/**
 * Created by Maple on 8/19/15.
 */

var BattlePokemonView = cc.Node.extend({
    ctor: function (model, isFriend) {
        this._super();
        this._isFriend = isFriend;
        this.setModel(model);

        this.setAnchorPoint(0.5, 0);
    },
    getModel: function () {
        return this._model;
    },
    setModel: function (model) {
        cc.assert(model instanceof ModelBase, "不合法的model参数");
        if (this._model == model) {
            return;
        }
        this._model = model;
        this._update();
    },
    stop: function () {
        this._gif.stop();
    },
    getDeadAction: function () {
        return new cc.TargetedAction(this._gif, new cc.MoveBy(0.25, cc.p(0, -this.getContentSize().height)));
    },
    _update: function () {
        var suffix = "";
        if (this._isFriend) {
            if (this._model.isShiny()) {
                suffix = "_sb";
            } else {
                suffix = "_b";
            }
        } else if (this._model.isShiny()) {
            suffix = "_s";
        }

        if (this._gif) {
            this._gif.removeFromParent();
        }
        var gifPath = cc.formatStr("coredata/%s%s.gif", this._model.getFormatedId(), suffix);
        //mw.log(gifPath);
        this._gif = mw.GifSprite.createWithFile(gifPath);
        this._gif.setAnchorPoint(0.5, 0);
        this._gif.setSpeedRatio(1.5);
        this._gif.setScale(2.5);

        var scissor = ex.ScissorNode.create();
        scissor.setContentSize(this._gif.getBoundingBox().width, this._gif.getBoundingBox().height);
        this._gif.setPositionX(scissor.getContentSize().width * 0.5);
        scissor.addChild(this._gif);
        scissor.setAnchorPoint(cc.p(0, 0));
        this.addChild(scissor);

        this.setContentSize(scissor.getContentSize());
    },
    _model: null,
    _gif: null,
    _isFriend: false,
});
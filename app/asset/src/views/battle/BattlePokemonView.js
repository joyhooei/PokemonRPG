/**
 * Created by Maple on 8/19/15.
 */

var BattlePokemonView = cc.Node.extend({
    ctor: function (model, isFriend) {
        this._super();
        this._isFriend = isFriend;
        this.setModel(model);

        this.setScale(2.5);
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
        this._gif.setPositionX(this._gif.getContentSize().width * 0.5);
        this._gif.setAnchorPoint(0.5, 0);
        this._gif.setSpeedRatio(1.5);
        this.addChild(this._gif);

        this.setContentSize(this._gif.getContentSize().width, this._gif.getContentSize().height);
    },
    _model: null,
    _gif: null,
    _isFriend: false,
});
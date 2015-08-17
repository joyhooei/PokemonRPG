/**
 * Created by Maple on 8/11/15.
 */

var HeroView = cc.Node.extend({
    ctor: function (model) {
        this._super();

        this.setModel(model);

        var frameName = "trainers/hero" + model.getDirection() + "_1.png";
        this._sprite = new cc.Sprite("#" + frameName);
        this.setContentSize(this._sprite.getContentSize().width, this._sprite.getContentSize().height);
        this._sprite.setPosition(this.getContentSize().width * 0.5, this.getContentSize().height * 0.5);
        this.addChild(this._sprite);

        this.updateView();
    },
    setModel: function (model) {
        cc.assert(model instanceof ModelBase, "不合法的model参数");
        this._model = model;
    },
    updateView: function () {
        var frameName = "trainers/hero" + this._model.getDirection() + "_1.png";
        this._sprite.setSpriteFrame(cc.SpriteFrameCache.getInstance().getSpriteFrame(frameName));
    },
    _sprite: null,
});
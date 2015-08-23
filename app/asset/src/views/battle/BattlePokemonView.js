/**
 * Created by Maple on 8/19/15.
 */

var BattlePokemonView = cc.Node.extend({
    ctor: function (model, isFriend) {
        this._super();
        this.setModel(model);

        var suffix = "";
        if (isFriend) {
            if (model.isShiny()) {
                suffix = "_sb";
            } else {
                suffix = "_b";
            }
        } else if (model.isShiny()) {
            suffix = "_s";
        }

        var gifPath = cc.formatStr("coredata/%s%s.gif", model.getFormatedId(), suffix);
        //mw.log(gifPath);
        this._gif = mw.GifSprite.createWithFile(gifPath);
        this._gif.setAnchorPoint(0.5, 0);
        this._gif.setSpeedRatio(1.5);
        this.addChild(this._gif);

        this.setScale(2.5);
    },
    setModel: function (model) {
        cc.assert(model instanceof ModelBase, "不合法的model参数");
        this._model = model;
    },
    _model: null,
    _gif: null,
});
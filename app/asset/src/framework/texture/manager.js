/**
 * Created by Maple on 8/10/15.
 */

/**
 * TextureManager用来管理纹理资源 采取引用计数的方式去管理
 * 每次加载纹理时 该纹理引用计数会+1 只有该纹理未加载时才会真正加载该纹理
 * 每次卸载纹理时 该纹理引用计数会-1 只有该纹理引用计数变成0之后才会真正卸载该纹理
 * loadTexture: 加载纹理
 * unloadTexture: 卸载纹理
 * didLoadTexture: 是否加载了某个纹理
 * loadTextureAsync: 异步加载纹理
 * forceUnloadTexture: 强制卸载纹理
 * setPvrTexturesSupportPremultipliedAlpha: 设置PVR纹理是否支持alpha预乘
 * @type {{loadTexture: Function, unloadTexture: Function, _textureMap: Object}}
 */
var TextureManager = {
    loadTexture: function (plist, texture) {
        if (typeof plist != "string" || typeof texture != "string") {
            mw.error("参数错误");
            return;
        }
        if (this._textureMap[plist]) {
            ++this._textureMap[plist]["ref"];
        } else {
            cc.SpriteFrameCache.getInstance().addSpriteFrames(plist, texture);
            this._textureMap[plist] = {
                ref: 1,         // 引用计数
                texture: texture,   // 纹理key
            };
        }
        cc.log("Texture %s loaded, reference count: %d", plist, this._textureMap[plist]["ref"]);
    },
    unloadTexture: function (plist) {
        if (typeof plist != "string") {
            mw.error("参数错误");
            return;
        }
        if (!this.didLoadTexture(plist)) {
            mw.error("未加载的纹理: %s", plist);
            return;
        }
        --this._textureMap[plist]["ref"];
        cc.log("Texture %s unloaded, reference count: %d", plist, this._textureMap[plist]["ref"]);
        if (this._textureMap[plist]["ref"] <= 0) {
            cc.SpriteFrameCache.getInstance().removeSpriteFramesFromFile(plist);
            cc.director.getTextureCache().removeTextureForKey(this._textureMap[plist]["texture"]);
            this._textureMap[plist] = undefined;
        }
    },
    didLoadTexture: function (plist) {
        return this._textureMap[plist] !== undefined;
    },
    loadTextureAsync: function (plist, texture, callback) {
        if (typeof plist != "string" || typeof texture != "string" || !callback instanceof Function) {
            mw.error("参数错误");
            return;
        }
        if (this.didLoadTexture(plist)) {
            ++this._textureMap[plist]["ref"];
            callback.call();
        } else {
            var realCallback = function () {
                cc.SpriteFrameCache.getInstance().addSpriteFrames(plist, texture);
                this._textureMap[plist] = {
                    ref: 1,
                    texture: texture,
                };
                cc.log("Texture %s loaded, reference count: %d", plist, this._textureMap[plist]["ref"]);
                callback.call();
            }.bind(this);
            cc.director.getTextureCache().addImageAsync(texture, realCallback);
        }
    },
    forceUnloadTexture: function (plist) {
        if (typeof plist != "string") {
            mw.error("参数错误");
            return;
        }
        if (!this.didLoadTexture(plist)) {
            mw.error("未加载的纹理: %s", plist);
            return;
        }
        cc.SpriteFrameCache.getInstance().removeSpriteFramesFromFile(plist);
        cc.director.getTextureCache().removeTextureForKey(this._textureMap[plist]["texture"]);
        this._textureMap[plist] = undefined;
    },
    setPvrTexturesSupportPremultipliedAlpha: function (bSupport) {
        cc.Image.setPVRImagesHavePremultipliedAlpha(bSupport);
    },
    _textureMap: new Object(),
};
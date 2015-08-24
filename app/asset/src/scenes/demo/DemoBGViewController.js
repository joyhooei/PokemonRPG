/**
 * Created by ManonLoki1 on 15/8/8.
 */
var DemoBGViewController=mw.ViewController.extend({
    TEXTURES_TO_LOAD: {
        "textures/common.plist": "textures/common.pvr.ccz"
    },
    ctor:function(){
        this._super();
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

    viewDidLoad:function(){
        //加载文理
        this._loadTextures();


        //这里进行View的加载 VIEW可以是多种类型  Layer,Sprite等
        var bg=new cc.Sprite("res/bg.jpg");
        bg.setPosition(cc.director.getWinSize().width/2,cc.director.getWinSize().height/2);
        this.view().addChild(bg);

        var rocker=new Rocker("#common/controller_bg.png","#common/rocker.png");
        rocker.setPosition(200,200);
        rocker.setDelegate(MakeScriptHandler(this,this.rockerDirectionChanged));
        this.view().addChild(rocker);

    },
    viewDidUnload:function(){
        //卸载View
        mw.log("DemoBGViewController unload");
        this._unloadTextures();
    },


    rockerDirectionChanged:function(direction){
        switch(direction){
            case Rocker.DIRECTIONS.RESET:{
                cc.log("RESET");
                break;
            }
            case Rocker.DIRECTIONS.LEFT:{
                cc.log("LEFT");
                break;
            }
            case Rocker.DIRECTIONS.RIGHT:{
                cc.log("RIGHT");
                break;
            }
            case Rocker.DIRECTIONS.UP:{
                cc.log("UP");
                break;
            }
            case Rocker.DIRECTIONS.DOWN:{
                cc.log("DOWN");
                break;
            }
        }
    }
});
/**
 * Created by ManonLoki1 on 15/8/8.
 */
var DemoBGViewController=mw.ViewController.extend({
    ctor:function(){
        this._super();
    },
    viewDidLoad:function(){
        //加载View


        //这里进行View的加载 VIEW可以是多种类型  Layer,Sprite等
        var bg=new cc.Sprite("res/bg.jpg");
        bg.setPosition(cc.director.getWinSize().width/2,cc.director.getWinSize().height/2);
        this.view().addChild(bg);

        var rocker=new RockerController();
        rocker.setPosition(200,200);
        rocker.setDelegate(MakeScriptHandler(this,this.rockerDirectionChanged));
        this.view().addChild(rocker);

    },
    viewDidUnload:function(){
        //卸载View
        mw.log("DemoBGViewController unload");
    },
    rockerDirectionChanged:function(direction){
        switch(direction){
            case RockerController.ROCKER_DIRECTION.RESET:{
                cc.log("RESET");
                break;
            }
            case RockerController.ROCKER_DIRECTION.LEFT:{
                cc.log("LEFT");
                break;
            }
            case RockerController.ROCKER_DIRECTION.RIGHT:{
                cc.log("RIGHT");
                break;
            }
            case RockerController.ROCKER_DIRECTION.UP:{
                cc.log("UP");
                break;
            }
            case RockerController.ROCKER_DIRECTION.DOWN:{
                cc.log("DOWN");
                break;
            }
        }
    }
});
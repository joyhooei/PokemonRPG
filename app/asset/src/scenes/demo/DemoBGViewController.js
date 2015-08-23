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
        this.view().addChild(rocker);



    },
    viewDidUnload:function(){
        //卸载View
        mw.log("DemoBGViewController unload");
    }
});
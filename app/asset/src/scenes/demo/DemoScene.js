/**
 * Created by ManonLoki1 on 15/8/8.
 */
    //JSB
var DemoScene=mw.GameScene.extend({
    ctor:function(){
        this._super();
    },
    onEnter:function(){
        this._super();
        //这里初始化Controller
        this.loadViewController(new DemoBGViewController(),"DemoBG_ViewController");
        this.loadViewController(new DemoGameViewController(),"DemoGame_ViewController");
    },
    onExit:function(){
        mw.log("DemoScene onExit");
        /**
        这段代码是不需要的，因为我在cpp层做了(By Winder)
        */
        // this.unloadAllViewControllers();//卸载所有的ViewController
        this._super();
    }
});
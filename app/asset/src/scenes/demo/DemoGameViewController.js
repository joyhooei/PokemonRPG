/**
 * Created by ManonLoki1 on 15/8/8.
 */
//游戏层
var DemoGameViewController=mw.ViewController.extend({
    ctor:function(){
        this._super();
        this._defineName="DemoGameViewController";
    },
    viewDidLoad:function(){
        //加载View
        var player=new cc.Sprite("res/miao_player.jpg");
        player.setPosition(cc.director.getWinSize().width/2,cc.director.getWinSize().height/2);
        this.view().addChild(player);

        //为Player添加事件
        var touchListener=cc.EventListener.create({
            event:cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan:MakeScriptHandler(this,this.playTouchedBegan)
        });

        cc.eventManager.addListener(touchListener,player);
    },
    viewDidUnload:function() {
        //卸载View;
        mw.log("DemoViewController unload");
    },
    playTouchedBegan:function(sender,event){
        mw.log("Player TouchBegan with "+this._defineName);

        cc.eventManager.removeAllListeners();//移除所有的监听 因为要转场了

        cc.director.runScene(new AnotherScene());//转场
        return true;
    }
});
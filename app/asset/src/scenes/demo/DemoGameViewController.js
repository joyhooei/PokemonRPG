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
    playTouchedBegan:function(touch,event){

        mw.log("Player TouchBegan with "+this._defineName);

        //碰撞检测

        var target=event.getCurrentTarget();

        //转换为相Player的坐标点这样只需要考虑宽高
        var location=target.convertToNodeSpace( touch.getLocation());

        //用于碰撞检测的矩形
        var rect=cc.rect(0,0,target.getContentSize().width,target.getContentSize().height);

       if( cc.rectContainsPoint(rect,location)){
            mw.log("已碰撞");


           cc.eventManager.removeAllListeners();//移除所有的监听 因为要转场了

           cc.director.runScene(new AnotherScene());//转场


       }else{
           mw.log("未碰撞");
       }




        return true;
    }
});
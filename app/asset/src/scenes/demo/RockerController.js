/**
 * Created by ManonLoki1 on 15/8/23.
 */

/*
 * 摇杆控制器
 * */


//摇杆控制器
var RockerController = cc.Node.extend({
    _radius: 75,//摇杆半径
    _rocker_origin_point: cc.p(75, 75),//摇杆初始位置
    _rocker: null,//摇杆
    _rocker_bg: null,//摇杆背景图
    ctor: function () {
        this._super();
        this.setContentSize(150, 150);//固定大小

        //初始化摇杆背景与摇杆
        this._rocker_bg = new cc.Sprite("res/controller_bg.png");
        this._rocker_bg.setPosition(75, 75);
        this._rocker = new cc.Sprite("res/rocker.png");
        this._rocker.setPosition(75, 75);

        this.addChild(this._rocker_bg);
        this.addChild(this._rocker);


        //按钮
        var touchListener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,//只处理单点触摸
            swallowTouches: true,//
            onTouchBegan: MakeScriptHandler(this, this._onTouchBegan),
            onTouchMoved: MakeScriptHandler(this, this._onTouchMoved),
            onTouchEnded: MakeScriptHandler(this,this._onTouchEnded)
        });

        cc.eventManager.addListener(touchListener, this);

        return true;
    },

    //摇杆的触摸事件
    _onTouchBegan: function (touch, event) {
//做碰撞检测
        var collisionRect = cc.rect(-25, -25, 50, 50);//碰撞检测矩形 坐标固定
        //触摸开始的坐标 相对于容器
        var point = this._rocker_bg.convertToNodeSpaceAR(touch.getLocation());

        if (cc.rectContainsPoint(collisionRect, point)) {
            cc.log("touchBegan");
            //修正摇杆位置
            this.updateRocker(point);
            return true;
        } else {
            cc.log("touchMissed");
            return false;
        }
    },
    _onTouchMoved: function (touch, event) {
        cc.log("touchMoved");

        //修正移动后摇杆的位置
        var point = this._rocker_bg.convertToNodeSpaceAR(touch.getLocation());


        var x=Math.abs(point.x);
        var y=Math.abs(point.y);


        var touchRaidus=x*x+y*y;//触摸点距离摇杆原点的半径

        if (touchRaidus>this._radius*this._radius){
            //这里需要修正坐标
            cc.log("rocker move out range");

            var module=Math.sqrt(touchRaidus);


            var x=this._radius*point.x/module;
            var y=this._radius*point.y/module;


            this.updateRocker(cc.p(x,y));
        }else{
            this.updateRocker(point);
        }
    },
    _onTouchEnded: function (touch, event) {
        cc.log("touchEnded");
       this.updateRocker(cc.p(0,0));
    },
    //更新摇杆位置
    updateRocker: function (pos) {

        this._rocker.setPosition(cc.pAdd( pos,this._rocker_origin_point));

        //校验坐标
        if(pos===cc.p(0,0)){
            cc.log("Controller reset");
            //抛出事件
        }else{
            //判断方向

        }

    }
});
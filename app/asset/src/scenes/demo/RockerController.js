/**
 * Created by ManonLoki1 on 15/8/23.
 */

/*
 * 摇杆控制器
 * */


//摇杆控制器
var RockerController;

RockerController = cc.Node.extend({
        _radius: 75,//摇杆半径
        _rocker_origin_point: cc.p(75, 75),//摇杆初始位置
        _rocker: null,//摇杆
        _rocker_bg: null,//摇杆背景图
        _delegate: null,//事件委托
        _lastDirection: null,//最后一次的方向
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
                onTouchEnded: MakeScriptHandler(this, this._onTouchEnded)
            });

            cc.eventManager.addListener(touchListener, this);

            return true;
        }
        ,

//摇杆的触摸事件
        _onTouchBegan: function (touch, event) {
//做碰撞检测
            var collisionRect = cc.rect(-25, -25, 50, 50);//碰撞检测矩形 坐标固定
            //触摸开始的坐标 相对于容器
            var point = this._rocker_bg.convertToNodeSpaceAR(touch.getLocation());

            if (cc.rectContainsPoint(collisionRect, point)) {
                //修正摇杆位置
                this._updateRocker(point);
                return true;
            } else {

                return false;
            }
        }
        ,
        _onTouchMoved: function (touch, event) {

            //修正移动后摇杆的位置
            var point = this._rocker_bg.convertToNodeSpaceAR(touch.getLocation());


            var x = Math.abs(point.x);
            var y = Math.abs(point.y);


            var touchRaidus = x * x + y * y;//触摸点距离摇杆原点的半径

            if (touchRaidus > this._radius * this._radius) {
                //这里需要修正坐标
                var module = Math.sqrt(touchRaidus);


                var x = this._radius * point.x / module;
                var y = this._radius * point.y / module;


                this._updateRocker(cc.p(x, y));
            } else {
                this._updateRocker(point);
            }
        }
        ,
        _onTouchEnded: function (touch, event) {
            this._updateRocker(cc.p(0, 0));
        }
        ,
//更新摇杆位置
        _updateRocker: function (pos) {

            this._rocker.setPosition(cc.pAdd(pos, this._rocker_origin_point));

            //校验坐标
            if (pos.x===0&&pos.y===0) {
                cc.log("Controller reset");
                this._directionChanged(RockerController.ROCKER_DIRECTION.RESET);
                //抛出事件
            } else {
                var absX = Math.abs(pos.x);
                var absY = Math.abs(pos.y);
                if (absX > absY) {
                    //横向移动
                    if (pos.x > 0) {
                        this._directionChanged(RockerController.ROCKER_DIRECTION.RIGHT);
                    } else {
                        this._directionChanged(RockerController.ROCKER_DIRECTION.LEFT);
                    }
                }
                else if (absY > absX) {
                    //纵向移动
                    if (pos.y > 0) {
                        this._directionChanged(RockerController.ROCKER_DIRECTION.UP);
                    } else {
                        this._directionChanged(RockerController.ROCKER_DIRECTION.DOWN);
                    }
                }
            }
        }
        ,
        _directionChanged: function (direction) {
            if (this._delegate && this._delegate instanceof  Function && direction !== this._lastDirection) {
                this._lastDirection = direction;
                this._delegate(direction);
            }
        }
        ,
        setDelegate: function (delegate) {
            this._delegate = delegate;
        }

    });

RockerController.ROCKER_DIRECTION = {
    RESET: 0,
    UP: 1,
    LEFT: 2,
    DOWN: 3,
    RIGHT: 4
};//摇杆方向
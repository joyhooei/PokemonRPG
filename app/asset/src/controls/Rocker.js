/**
 * Created by ManonLoki1 on 15/8/24.
 */
//摇杆
var Rocker;
Rocker=cc.Node.extend({
    _radius:75,//摇杆的移动半径
    _collisionRect:cc.rect(-25,-25,50,50),//做碰撞检测的矩形 写死了 主要是省去计算步骤
    _rockerOriginPoint:cc.p(75,75),//摇杆距离屏幕的位置
    _rockerBG:null,//摇杆背景
    _rocker:null,//摇杆
    _lastDirection:0,//摇杆最后一次变化的方向 默认Reset
    _delegate:null,//摇杆事件的委托

    setDelegate:function(delegate){
        this._delegate=delegate;
    },//设置事件委托
    ctor:function(bgTexture,rockerTexture){
        this._super();
        this.setContentSize(150, 150);//固定大小

        //初始化摇杆背景与摇杆
        this._rocker_bg = new cc.Sprite(bgTexture);
        this._rocker = new cc.Sprite(rockerTexture);

        this._rocker_bg.setPosition(this._rockerOriginPoint);
        this._rocker.setPosition(this._rockerOriginPoint);

        this.addChild(this._rocker_bg);
        this.addChild(this._rocker);


        //处理事件
        var touchListener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,//只处理单点触摸
            swallowTouches: true,//
            onTouchBegan: MakeScriptHandler(this, this._onTouchBegan),
            onTouchMoved: MakeScriptHandler(this, this._onTouchMoved),
            onTouchEnded: MakeScriptHandler(this, this._onTouchEnded),
            onTouchCancelled:MakeScriptHandler(this,this._onTouchCancelled)
        });

        cc.eventManager.addListener(touchListener, this);

        return true;
    },//构造函数
    _onDirectionChanged:function(direction){
        if (this._delegate && this._delegate instanceof  Function && direction !== this._lastDirection) {
            this._lastDirection = direction;
            this._delegate(direction);
        }
    },//方向变化
    _updateRockerPosition:function(pos){
        this._rocker.setPosition(cc.pAdd(pos, this._rockerOriginPoint));

        //校验坐标
        if (pos.x === 0 && pos.y === 0) {
            //抛出事件
            this._onDirectionChanged(Rocker.DIRECTIONS.RESET);
        } else {
            var absX = Math.abs(pos.x);
            var absY = Math.abs(pos.y);
            if (absX > absY) {
                //横向移动
                if (pos.x > 0) {
                    this._onDirectionChanged(Rocker.DIRECTIONS.RIGHT);
                } else {
                    this._onDirectionChanged(Rocker.DIRECTIONS.LEFT);
                }
            }
            else if (absY > absX) {
                //纵向移动
                if (pos.y > 0) {
                    this._onDirectionChanged(Rocker.DIRECTIONS.UP);
                } else {
                    this._onDirectionChanged(Rocker.DIRECTIONS.DOWN);
                }
            }
        }
    },//更新摇杆坐标

    _onTouchBegan:function(touch,event){
        //触摸开始的坐标 相对于容器
        var pos = this._rocker_bg.convertToNodeSpaceAR(touch.getLocation());


        if (cc.rectContainsPoint(this._collisionRect, pos)) {

            //修正摇杆位置
            this._updateRockerPosition(pos);
            return true;
        } else {
            cc.log("2");
            return false;
        }
    },
    _onTouchMoved:function(touch,event) {
        //修正移动后摇杆的位置
        var pos = this._rocker_bg.convertToNodeSpaceAR(touch.getLocation());
        var x = Math.abs(pos.x);
        var y = Math.abs(pos.y);


        var touchRadius = x * x + y * y;//触摸点距离摇杆原点的半径

        if (touchRadius > this._radius * this._radius) {
            //这里需要修正坐标
            var module = Math.sqrt(touchRadius);
            var x = this._radius * pos.x / module;
            var y = this._radius * pos.y / module;
            //使用修正后的坐标
            this._updateRockerPosition(cc.p(x, y));
        } else {
            this._updateRockerPosition(pos);
        }
    },
    _onTouchEnded:function(){
        this._updateRockerPosition(cc.p(0, 0));
    },
    _onTouchCancelled:function(){
        this._updateRockerPosition(cc.p(0, 0));
    }

});

//为摇杆对象增加方向
Rocker.DIRECTIONS={
    RESET:0,
    UP:1,
    LEFT:2,
    DOWN:3,
    RIGHT:4
};
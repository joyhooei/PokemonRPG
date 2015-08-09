/**
 * Created by Maple on 8/7/15.
 */

var PLAYTIME_SCHEDULE_KEY = "PLAYTIME_TICK";

/**
 * 地图控制器 只处理地图逻辑
  */
var MapViewController = mw.ViewController.extend({
    ctor: function () {
        this._super();
    },
    viewDidLoad: function () {
        var hero = DataCenter.getHero();
        mw.logWithTag("heroinfo", "Hero ID: %s, Hero Name: %s", hero.getId(), hero.getName());

        var map = new cc.TMXTiledMap("tmx/demo_map.tmx");
        this.view().addChild(map);

        var listener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: MakeScriptHandler(this, this.onTouchBegan),
        });
        cc.eventManager.addListener(listener, this.view());

        // 开始积累游戏时间
        cc.director.getScheduler().schedule(MakeScriptHandler(this, this.addTime), this.view(), 1, -1, 1, false, PLAYTIME_SCHEDULE_KEY);
    },
    viewDidUnload: function () {
        // 关闭计时器
        cc.director.getScheduler().unschedule(PLAYTIME_SCHEDULE_KEY, this.view());
    },
    addTime: function () {
        var hero = DataCenter.getHero();
        hero.addPlayTime();
        mw.logWithTag("heroinfo", "Hero PlayTime: %d", hero.getPlayTime());
    },
    onTouchBegan: function (touch, event) {
        var pos = touch.getLocation();
        mw.logWithTag("touch", pos.x, pos.y);
        return true;
    }
});
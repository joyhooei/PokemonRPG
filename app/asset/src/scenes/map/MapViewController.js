/**
 * Created by Maple on 8/7/15.
 */

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

        // 开始积累游戏时间
        cc.director.getScheduler().schedule(MakeScriptHandler(this, this.addTime), this.view(), 1, -1, 1, false, "PLAYTIME_TICK");
    },
    viewDidUnload: function () {
        // 关闭计时器
        cc.director.getScheduler().unschedule("PLAYTIME_TICK", this.view());
    },
    addTime: function () {
        var hero = DataCenter.getHero();
        hero.addPlayTime();
        mw.logWithTag("heroinfo", "Hero PlayTime: %d", hero.getPlayTime());
    }
});
/**
 * Created by Maple on 8/7/15.
 */

var PLAYTIME_SCHEDULE_KEY = "PLAYTIME_TICK";

/**
 * 地图控制器 只处理地图逻辑
  */
var MapViewController = mw.ViewController.extend({
    TEXTURES_TO_LOAD: {
        "textures/trainers.plist": "textures/trainers.pvr.ccz",
    },
    ctor: function (segue) {
        this._super(segue);
    },
    viewDidLoad: function () {
        this._loadTextures();
        this._renderView();

        // 开始积累游戏时间
        cc.director.getScheduler().schedule(MakeScriptHandler(this, this._addTime), this.view(), 1, -1, 1, false, PLAYTIME_SCHEDULE_KEY);
    },
    viewDidUnload: function () {
        this._unloadTextures();
        // 关闭计时器
        cc.director.getScheduler().unschedule(PLAYTIME_SCHEDULE_KEY, this.view());
    },
    _loadTextures: function () {
        for (var plist in this.TEXTURES_TO_LOAD) {
            var tex = this.TEXTURES_TO_LOAD[plist];
            TextureManager.loadTexture(plist, tex);
        }
    },
    _unloadTextures: function () {
        for (var plist in this.TEXTURES_TO_LOAD) {
            TextureManager.unloadTexture(plist);
        }
    },
    _renderView: function () {
        var hero = DataCenter.getHero();
        mw.logWithTag("heroinfo", "Hero ID: %s, Hero Name: %s", hero.getId(), hero.getName());

        var map = new cc.TMXTiledMap("tmx/demo_map.tmx");
        this.view().addChild(map);

        this._hero = new HeroView(hero);
        this._hero.setPosition(cc.director.getWinSize().width * 0.5, cc.director.getWinSize().height * 0.5);
        this.view().addChild(this._hero);

        var listener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: MakeScriptHandler(this, this._onTouchBegan),
        });
        cc.eventManager.addListener(listener, this.view());
    },
    _addTime: function () {
        var hero = DataCenter.getHero();
        hero.addPlayTime();
        mw.logWithTag("heroinfo", "Hero PlayTime: %d", hero.getPlayTime());
    },
    _onTouchBegan: function (touch, event) {
        var pos = touch.getLocation();
        mw.logWithTag("touch", pos.x, pos.y);
        return true;
    },
    _hero: null,
});
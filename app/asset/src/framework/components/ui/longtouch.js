/**
 * Created by Maple on 9/2/15.
 */

/**
 * 长按处理组件 使用说明如下
 * 1) 必须绑定到cc.Node或其子类
 * 2) setLongTouchDelta设置长按间隔
 * 3) setDelegate设置长按事件的delegate, delegate包含:
 * - onLongTouchBegan(target, currentTouch, delta): 在target区域内, 长按时间到达后触发, 仅触发一次
 * - onClick(target): 在target区域内, 长按时间未到达时触发
 * - onLongTouchPressed(target, currentTouch, delta): 到达长按状态后, 只要还在target区域内, 每一帧都触发
 * - onLongTouchEnded(target, currentTouch, delta): 长按状态下松开屏幕时或移出target范围时触发
 * - onLongTouchCancelled(target, currentTouch, delta): 长按状态下收到TouchCancelled时触发
 */
var LongTouchComponent = Component.extend({
    // constants
    UPDATE_SCHEDULER_KEY: "longtouch_update_scheduler",
    DEFAULT_PRESS_TIME: 1000,      // ms
    ctor: function () {
        this._super("LongTouch");

        this._touchTs = this.DEFAULT_PRESS_TIME;
    },
    setLongTouchDelta: function (ts) {
        if (typeof ts != "number" || ts < 0) {
            mw.error("不合法的参数 ts必须是数字并且>=0");
            return;
        }
        this._touchTs = ts;
    },
    setDelegate: function (delegate) {
        if (!(delegate instanceof Object)) {
            mw.error("不合法的参数 delegate必须是object");
            return;
        }
        this._delegate = delegate;
    },
    exportMethods: function () {
        this._super([
            "setLongTouchDelta",
            "setDelegate",
        ]);
        return this._target;
    },
    onBind: function (target) {
        if (!(target instanceof cc.Node)) {
            mw.error("不合法的绑定对象 LongTouch组件必须绑定在cc.Node上");
            return;
        }
        var listener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: MakeScriptHandler(this, this._onTouchBegan),
            onTouchMoved: MakeScriptHandler(this, this._onTouchMoved),
            onTouchEnded: MakeScriptHandler(this, this._onTouchEnded),
            onTouchCancelled: MakeScriptHandler(this, this._onTouchCancelled),
        });
        cc.eventManager.addListener(listener, target);
        this._listener = listener;
    },
    onUnbind: function () {
        if (this._listener) {
            cc.eventManager.removeEventListener(this._listener);
            this._listener = null;
        }
    },
    _onTouchBegan: function (touch, event) {
        this._currentLoc = touch.getLocation();
        var bound = this._target.getBoundingBox();
        var worldPos = this._target.convertToWorldSpace(cc.p(0, 0));
        bound.x = worldPos.x;
        bound.y = worldPos.y;
        if (cc.rectContainsPoint(bound, this._currentLoc)) {
            this._beginTs = Date.now();
            this._scheduleUpdate();
            return true;
        }
        return false;
    },
    _onTouchMoved: function (touch, event) {
        this._currentLoc = touch.getLocation();
        if (!this._longTouching) {
            return;
        }
        var bound = this._target.getBoundingBox();
        var worldPos = this._target.convertToWorldSpace(cc.p(0, 0));
        bound.x = worldPos.x;
        bound.y = worldPos.y;
        if (!cc.rectContainsPoint(bound, this._currentLoc)) {
            this._unscheduleUpdate();
            this._longTouching = false;
            if (this._delegate && this._delegate.onLongTouchEnded instanceof Function) {
                this._delegate.onLongTouchEnded(this._target, this._currentLoc, Date.now() - this._beginTs);
            }
        }
    },
    _onTouchEnded: function (touch, event) {
        this._currentLoc = touch.getLocation();
        this._unscheduleUpdate();
        if (this._longTouching) {
            if (this._delegate && this._delegate.onLongTouchEnded instanceof Function) {
                this._delegate.onLongTouchEnded(this._target, this._currentLoc, Date.now() - this._beginTs);
            }
        } else {
            var bound = this._target.getBoundingBox();
            var worldPos = this._target.convertToWorldSpace(cc.p(0, 0));
            bound.x = worldPos.x;
            bound.y = worldPos.y;
            if (cc.rectContainsPoint(bound, touch.getLocation()) &&
                Date.now() - this._beginTs < this._touchTs &&
                this._delegate && this._delegate.onClick instanceof Function) {
                this._delegate.onClick(this._target);
            }
        }
        this._longTouching = false;
        this._beginTs = 0;
        this._currentLoc = null;
    },
    _onTouchCancelled: function (touch, event) {
        this._currentLoc = touch.getLocation();
        this._unscheduleUpdate();
        if (this._longTouching) {
            if (this._delegate && this._delegate.onLongTouchCancelled instanceof Function) {
                this._delegate.onLongTouchCancelled(this._target, this._currentLoc, Date.now() - this._beginTs);
            }
        }
        this._longTouching = false;
        this._beginTs = 0;
        this._currentLoc = null;
    },
    _update: function () {
        var delta = Date.now() - this._beginTs;
        if (delta >= this._touchTs) {
            if (this._longTouching && this._delegate && this._delegate.onLongTouchPressed instanceof Function) {
                this._delegate.onLongTouchPressed(this._target, this._currentLoc, delta);
            } else {
                this._longTouching = true;
                if (this._delegate && this._delegate.onLongTouchBegan instanceof Function) {
                    this._delegate.onLongTouchBegan(this._target, this._currentLoc, delta);
                }
            }
        }
    },
    _scheduleUpdate: function () {
        cc.director.getScheduler().schedule(MakeScriptHandler(this, this._update), this, 0, -1, 0, false, this.UPDATE_SCHEDULER_KEY);
    },
    _unscheduleUpdate: function () {
        cc.director.getScheduler().unschedule(this.UPDATE_SCHEDULER_KEY, this);
    },
    _touchTs: 0,
    _currentLoc: null,
    _listener: null,
    _longTouching: false,
    _delegate: null,
    _beginTs: 0,
    _endTs: 0,
});
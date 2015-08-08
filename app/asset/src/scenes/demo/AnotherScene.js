/**
 * Created by ManonLoki1 on 15/8/8.
 */
//另外一个场景，用来
var AnotherScene=mw.GameScene.extend({
    ctor:function() {
        this._super();

    },
    onEnter:function(){
        this._super();
        //
        mw.log("AnotherScene onEnter");
        this.loadViewController(new AnotherBGViewController(),"AnotherBG_ViewController");
    },
    onExit:function(){
        this._super();
        mw.log("AnotherScene onExit");
    }
});
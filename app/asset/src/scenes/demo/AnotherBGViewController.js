/**
 * Created by ManonLoki1 on 15/8/8.
 */
//另外一个场景
var AnotherBGViewController=mw.ViewController.extend({
    ctor:function(){
        this._super();
    },
    viewDidLoad:function(){
        //加载场景
        var bg=new cc.Sprite("res/another_bg.jpg");
        bg.setPosition(cc.director.getWinSize().width/2,cc.director.getWinSize().height/2);
        this.view().addChild(bg);

        mw.log("AnotherBGViewController viewDidLoad");
    },
    viewDidUnload:function(){
        //卸载场景
        mw.log("AnotherBGViewController viewDidUnLoad");
    }
});
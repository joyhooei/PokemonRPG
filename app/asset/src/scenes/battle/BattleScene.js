/**
 * Created by Maple on 8/15/15.
 */

var BattleScene = mw.GameScene.extend({
    ctor: function () {
        this._super();
    },
    onEnter: function () {
        this._super();

        Registry.addClass("BattleAI", BattleAI);
        var battleType = parseInt(this.getParameter("battle_type"));
        var pokemon1Id = parseInt(this.getParameter("pokemon1"));
        var pokemon2Id = parseInt(this.getParameter("pokemon2"));
        var aiLv = parseInt(this.getParameter("ai_level"));
        var weather = parseInt(this.getParameter("weather"));   // 0表示无天气

        // temp
        var pokemon1Model = new Pokemon({
            id: pokemon1Id,
            level: 100,
            catcher: DataCenter.getHero().getId(),
            owner: DataCenter.getHero().getId(),
        });
        var pokemon2Model = new Pokemon({
            id: pokemon2Id,
            level: 100,
        });

        this._battleProcessor = new BattleProcessor(battleType, pokemon1Model, pokemon2Model, aiLv, weather);

        this._musicId = ex.GameAudioEngine.getInstance().play2d("music/battle/giratina.mp3", true);

        this.loadViewController(new BattleUIViewController(), BATTLE_UI_VC_NAME);
        this.loadViewController(new BattleDialogViewController(new ModalViewSegue()), BATTLE_DIALOG_VC_NAME);
        this.loadViewController(new BattleOperationViewController(new ModalViewSegue()), BATTLE_OPERATION_VC_NAME);
    },
    onExit: function () {
        this._super();

        this._battleProcessor.cleanup();

        if (this._musicId) {
            ex.GameAudioEngine.getInstance().stop(this._musicId);
            this._musicId = null;
        };
        Registry.removeClass("BattleAI");
    },
    getBattleProcessor: function () {
        return this._battleProcessor;
    },
    _battleProcessor: null,
    _musicId: null,
});
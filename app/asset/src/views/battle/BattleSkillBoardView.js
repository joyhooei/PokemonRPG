/**
 * Created by Maple on 9/4/15.
 */

var SkillCellLongTouchDelegate = cc.Class.extend({
    ctor: function (detailBg, model, index) {
        this._detailBg = detailBg;
        this._model = model;
        this._index = index;
    },
    onLongTouchBegan: function (target, loc, delta) {
        if (!this._isVisible(target)) {
            return;
        }
        this._detailBg.setVisible(true);
    },
    onClick: function (target) {
        if (!this._isVisible(target)) {
            return;
        }
        var skills = this._model.getSkills();
        logBattle("使用技能: %d", skills[this._index][0]);
    },
    onLongTouchEnded: function (target, loc, delta) {
        if (!this._isVisible(target)) {
            return;
        }
        this._detailBg.setVisible(false);
    },
    _isVisible: function (node) {
        var visible = true;
        var current = node;
        do {
            if (!current.isVisible()) {
                visible = false;
                break;
            }
            current = current.getParent();
        } while (current);
        return visible;
    },
    _detailBg: null,
    _model: null,
    _index: null,
});

var BattleSkillBoardView = cc.Node.extend({
    SKILL_TYPE_MAP: {
        1: "物理",
        2: "特殊",
        3: "变化",
    },
    BOARD_CCS_NAMES: {
        BG: "bg",
            SKILL1: "skill_1",
            SKILL2: "skill_2",
            SKILL3: "skill_3",
            SKILL4: "skill_4",
    },
    CELL_CCS_NAMES: {
        SKILL_BG: "skill_bg",
            SKILL_NAME: "skill_name",
            PP_INFO: "pp_info",
            SKILL_TYPE: "skill_type",
        DETAIL_BG: "detail_bg",
            SKILL_DESC: "skill_desc",
    },
    ctor: function(model) {
        this._super();

        this._ccsNode = ccs.load("json/battle_skill_board.json").node;
        this.addChild(this._ccsNode);
        var bg = this._ccsNode.getChildByName(this.BOARD_CCS_NAMES.BG);
        this._skill1Node = bg.getChildByName(this.BOARD_CCS_NAMES.SKILL1);
        this._skill2Node = bg.getChildByName(this.BOARD_CCS_NAMES.SKILL2);
        this._skill3Node = bg.getChildByName(this.BOARD_CCS_NAMES.SKILL3);
        this._skill4Node = bg.getChildByName(this.BOARD_CCS_NAMES.SKILL4);

        //this.setContentSize(bg.getContentSize());
        //this._ccsNode.setPosition(this.getContentSize().width * 0.5, this.getContentSize().height * 0.5);

        // 绑定longtouch组件
        for (var i = 1; i <= 4; ++i) {
            var skillNode = this["_skill" + i.toString() + "Node"];
            var skillBg = skillNode.getChildByName(this.CELL_CCS_NAMES.SKILL_BG);
            var detailBg = skillNode.getChildByName(this.CELL_CCS_NAMES.DETAIL_BG);
            var com = MakeBindable(skillBg).addComponent("LongTouch").exportMethods();
            com.setDelegate(new SkillCellLongTouchDelegate(detailBg, model, i - 1));
        }

        this.setModel(model);
    },
    setModel: function (model) {
        if (!(model instanceof Pokemon)) {
            return;
        }
        this._model = model;
        this._update();
    },
    _update: function () {
        var skills = this._model.getSkills();
        for (var i = 0; i < 4; ++i) {
            var node = this["_skill" + (i + 1).toString() + "Node"];
            if (i < skills.length) {
                // 拥有的技能
                node.setVisible(true);
                var skillInfo = new SkillInfo(skills[i][0]);
                var skillBg = node.getChildByName(this.CELL_CCS_NAMES.SKILL_BG);
                skillBg.loadTexture(cc.formatStr("common/prop_bg_%d.png", skillInfo.getProperty()), ccui.Widget.PLIST_TEXTURE);
                var detailBg = node.getChildByName(this.CELL_CCS_NAMES.DETAIL_BG);
                skillBg.getChildByName(this.CELL_CCS_NAMES.SKILL_NAME).setString(skillInfo.getName());
                skillBg.getChildByName(this.CELL_CCS_NAMES.SKILL_TYPE).setString(this.SKILL_TYPE_MAP[skillInfo.getType()]);
                var ppLimit = skillInfo.getPP() * (1 + 0.2 * skills[i][2]);
                skillBg.getChildByName(this.CELL_CCS_NAMES.PP_INFO).setString(skills[i][1].toString() + " / " + ppLimit.toString());
                var lblDesc = detailBg.getChildByName(this.CELL_CCS_NAMES.SKILL_DESC);
                lblDesc.setString(skillInfo.getDescription());
                //var autoSize = lblDesc.getAutoRenderSize();
                //mw.dump(autoSize);
            } else {
                node.setVisible(false);
            }
        }
    },
    _ccsNode: null,
    _skill1Node: null,
    _skill2Node: null,
    _skill3Node: null,
    _skill4Node: null,
    _model: null,
});
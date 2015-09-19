/**
 * Created by Maple on 8/19/15.
 */

var Pokemon = ModelBase.extend({
    /**
     * properties必须拥有id 其他key值为缺省参数 列表如下:
     * id: pokemon id
     * gender: 性别
     * level: 等级
     * speciality: 特性
     * personality: 性格
     * skills: 学会的技能
     * shiny: 是否闪光
     * catcher: 捕获者id
     * owner: 拥有者id
     * @param properties
     */
    ctor: function (properties) {
        // 定义model结构
        this._defineScheme({
            id: [ "number", 0 ],        // id
            hp: [function (val) {
                return typeof val == "number" && val >= 0;
            }, 0],      // 当前hp
            gender: [function (val) {
                return (typeof val == "number" && val >= GENDER.MALE && val <= GENDER.FEMALE) || val === null;
            }, GENDER.MALE ],       // 性别
            level: [function (val) {
                return typeof val == "number" && val > 0;
            }, 1],     // 等级
            exp: [function (val) {
                return typeof val == "number" && val >= 0;
            }, 0],     // 经验值
            speciality: [ "number", 1 ],    // 特性
            skills: [function (val) {
                return val instanceof Array;
            }, []],     // 技能 [ [ 技能id, 技能pp, 技能pp上升次数 ], ... ]
            state: [function (val) {
                return val >= POKEMON_STATES.NORMAL && val <= POKEMON_STATES.DEAD;
            }, POKEMON_STATES.NORMAL ],     // 异常状态
            personality: [function (val) {
                return val >= POKEMON_PERSONALITIES.HARDY && val <= POKEMON_PERSONALITIES.CAREFUL;
            }, POKEMON_PERSONALITIES.HARDY ],     // 性格
            basicValues: [function (val) {
                return val instanceof Array;
            }, [ 0, 0, 0, 0, 0, 0 ]],     // 基础属性值
            talentValues: [function (val) {
                return val instanceof Array;
            }, [ 0, 0, 0, 0, 0, 0 ]],     // 个体值
            hardValues: [function (val) {
                return val instanceof Array;
            }, [ 0, 0, 0, 0, 0, 0 ]],     // 努力值
            shiny: [ "boolean", false ],    // 闪光
            catcher: [ "string", null ],   // 捕获者id
            owner: [ "string", null ],  // 拥有者id
        });

        // 需要先设置id
        this._setProperties({
            id: properties["id"],
        });
        // 保存格式化后的id
        var fmtId = this._id.toString();
        var len = fmtId.length;
        for (var i = 0; i < 3 - len; ++i) {
            fmtId = "0" + fmtId;
        }
        this._fmtId = fmtId;

        var rd = Math.ceil(Math.random() * 10000);
        var isShiny = rd == 1;
        var randomTalents = [];
        for (var i = 0; i < 6; ++i) {
            rd = Math.floor(Math.random() * 32);
            randomTalents.push(rd);
        }
        logBattle("随机个体值: %s", randomTalents.toString());

        // 初始化
        var lv = properties["level"] || 1;
        var exp = this._getExpAtLv(lv);
        var speciality = properties["speciality"] || this._randomSpeciality();
        var personality = properties["personality"] || this._randomPersonality();
        this._setProperties({
            gender: properties["gender"] || Math.ceil(Math.random() * 2),
            level: lv,
            exp: exp,
            speciality: speciality,
            personality: personality,
            talentValues: randomTalents,
            shiny: isShiny,
            owner: properties["owner"] || null,
            catcher: properties["catcher"] || null,
        });
        var skills = properties["skills"] || this._genSkills();
        var basicValues = this._genBasicValues(this._level);
        this._setProperties({
            basicValues: basicValues,
            skills: skills,
            hp: basicValues[0],
        });
    },
    getInfo: function () {
        if (!this._infoModel) {
            this._infoModel = new PokemonInfo(this._id);
        }
        return this._infoModel;
    },
    getFormatedId: function () {
        return this._fmtId;
    },
    getGender: function () {
        return this._gender;
    },
    getLevel: function () {
        return this._level;
    },
    getHp: function () {
        return this._hp;
    },
    getExp: function () {
        return this._exp;
    },
    getSpeciality: function () {
        return this._speciality;
    },
    getSkills: function () {
        return this._skills;
    },
    getState: function () {
        return this._state;
    },
    getPersonality: function () {
        return this._personality;
    },
    getBasicValues: function () {
        return this._basicValues;
    },
    getTalentValues: function () {
        return this._talentValues;
    },
    getHardValues: function () {
        return this._hardValues;
    },
    isShiny: function () {
        return this._shiny;
    },
    getCatcher: function () {
        return this._catcher;
    },
    getOwner: function () {
        return this._owner;
    },
    getHpPercent: function () {
        return this._hp / this._basicValues[0] * 100;
    },
    ownBySelf: function () {
        return this._owner == DataCenter.getHero().getId();
    },
    getExpPercent: function () {
        return (this._exp - this._getExpAtLv(this._level)) / (this._getExpAtLv(this._level + 1) - this._getExpAtLv(this._level)) * 100;
    },
    getRestExpToLvUp: function () {
        return this._getExpAtLv(this._level + 1) - this._exp;
    },
    hurt: function (dmg) {
        var newHp = this._hp - dmg;
        if (newHp < 0) {
            newHp = 0;
        }
        this._setProperties({
            hp: newHp
        });
    },
    _getExpAtLv: function (lv) {
        return lv * lv * lv;
    },
    _getPersonalityCorrection: function () {
        if (this._personalityCorrection === null) {
            var val = [1, 1, 1, 1, 1];
            if (this._personality > POKEMON_PERSONALITIES.QUIRKY) {
                var tmp = this._personality - 5;
                var addIndex = Math.floor(tmp / 4);
                var subIndex = tmp % 4 >= addIndex ? tmp % 4 + 1 : tmp % 4;
                val[addIndex] = 1.1;
                val[subIndex] = 0.9;
            }
            this._personalityCorrection = val;
        }
        logBattle("性格修正: %s", this._personalityCorrection.toString());
        return this._personalityCorrection;
    },
    _genBasicValues: function (lv) {
        var basicData = [];
        var racialValues = this.getInfo().getRacialValues();
        var personalityCorrection = this._getPersonalityCorrection();
        // calculate values
        var hp = Math.floor((racialValues[0] * 2 + this._talentValues[0] + this._hardValues[0] * 0.25) * lv * 0.01 + lv + 10);
        var patk = Math.floor(((racialValues[1] * 2 + this._talentValues[1] + this._hardValues[1] * 0.25) * lv * 0.01 + 5) * personalityCorrection[0]);
        var pdef = Math.floor(((racialValues[2] * 2 + this._talentValues[2] + this._hardValues[2] * 0.25) * lv * 0.01 + 5) * personalityCorrection[1]);
        var satk = Math.floor(((racialValues[3] * 2 + this._talentValues[3] + this._hardValues[3] * 0.25) * lv * 0.01 + 5) * personalityCorrection[2]);
        var sdef = Math.floor(((racialValues[4] * 2 + this._talentValues[4] + this._hardValues[4] * 0.25) * lv * 0.01 + 5) * personalityCorrection[3]);
        var agi = Math.floor(((racialValues[5] * 2 + this._talentValues[5] + this._hardValues[5] * 0.25) * lv * 0.01 + 5) * personalityCorrection[4]);
        basicData.push(hp);
        basicData.push(patk);
        basicData.push(pdef);
        basicData.push(satk);
        basicData.push(sdef);
        basicData.push(agi);
        logBattle("Lv.%d的基础值: %s", lv, basicData.toString());
        return basicData;
    },
    _randomSpeciality: function () {
        var info = this.getInfo();
        var len = info.getSpecialities().length;
        var rd = Math.floor(Math.random() * len);
        var speciality = info.getSpecialities()[rd];
        logBattle("随机特性: %d", speciality);

        return speciality;
    },
    _randomPersonality: function () {
        var personality = Math.floor(Math.random() * 25);
        logBattle("随机性格: %s", PERSONALITY_NAMES[personality]);
        return personality;
    },
    _genSkills: function () {
        var skills = [];
        var lvUpSkills = this.getInfo().getLevelUpSkills();
        var loaded = 0;
        // 优先选出最靠后的4个技能
        var lastLv = -1;
        for (var i = lvUpSkills.length - 1; i >= 0; --i) {
            var skillInfo = lvUpSkills[i];
            // 0级的技能只能学习最近的一个
            if (skillInfo[0] <= this._level && lastLv != 0) {
                lastLv = skillInfo[0];
                var skillData = [];     // [ 技能ID, 技能PP, 技能PP上升次数 ]
                skillData.push(skillInfo[1]);
                var sql = cc.formatStr("select [pp] from [skill_info] where [id] = '%d';", skillInfo[1]);
                var pp = parseInt(Sqlite3Helper.executeQuery(sql)[0]["pp"]);
                skillData.push(pp);
                skillData.push(0);
                skills.push(skillData);
                logBattle("生成技能: " + skillData.toString());
                ++loaded;
                if (loaded >= 4) {
                    break;
                }
            }
        }
        skills.reverse();
        return skills;
    },
    _infoModel: null,
    _personalityCorrection: null,
});
/**
 * Created by Maple on 8/23/15.
 */

var DIALOG_EVENTS = {
    // common
    SHOW_DIALOG_WITH_INDICE: "Dialog.ShowDialogWithIndice",
    SHOW_NEXT_DIALOG: "Dialog.ShowNextDialog",
    SHOW_DIALOG_WITHOUT_INDICE: "Dialog.ShowDialogWithoutIndice",

    // battle
    SHOW_DIALOG_WITH_BATTLE_ANIMATION: "Dialog.ShowDialogWithBattleAnimation",
};

var BATTLE_UI_EVENTS = {
    PLAY_SKILL: "BattleUI.PlaySkill",
};

var BATTLE_EVENTS = {
    SKILL_BEHAVIOR = "Battle.SkillBehavior",
    PROCESS_TURN: "Battle.ProcessTurn",
    TURN_BEGAN: "Battle.TurnBegan",
    TURN_ENDED: "Battle.TurnEnded",
    BATTLE_ENDED: "Battle.BattleEnded",
};
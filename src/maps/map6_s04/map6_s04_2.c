#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s04.h"
#include "maps/characters/alessa.h"
#include "maps/characters/dahlia.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800DD5B8

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800DD5CC

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800DD610

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800DD628

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800DD634

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800DD648

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800DD65C

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800DD670

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800DD764);

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800DDDC8

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800DDDDC

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800DDDF0

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800DDEEC

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800DDFEC

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800DE064

void Ai_Flauros_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800DE0C4
{
    s32         i;
    s32         var_s1;
    s_AnimInfo* animInfo;

    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        chara->model_0.anim_4.alpha_A = Q12(0.0f);
        chara->model_0.controlState_2        = 1;
        chara->model_0.stateStep_3    = 0;
        Character_AnimSet(chara, ANIM_STATUS(1, true), 0);
    }

    if (chara->model_0.anim_4.time_4 <= Q12(21.0f))
    {
        if (chara->model_0.anim_4.time_4 > Q12(13.0f))
        {
            var_s1 = (chara->model_0.anim_4.time_4 - Q12(13.0f)) >> 3;
        }
        else
        {
            var_s1 = 0;
        }
    }
    else
    {
        var_s1 = Q12(1.0f);
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &FLAUROS_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);

    for (i = 6; i < 11; i++)
    {
        func_800705E4(coords, i, var_s1, var_s1, var_s1);
    }
}

void Ai_Parasite_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800DE1CC
{
    s_AnimInfo* animInfo;

    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        chara->model_0.anim_4.alpha_A = Q12(0.0f);
        chara->model_0.controlState_2        = 1;
        chara->model_0.stateStep_3    = 0;
        Character_AnimSet(chara, ANIM_STATUS(1, true), 0);
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &PARASITE_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}

void func_800DE26C(void) {}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DE274);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DE350);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DE380);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DE5CC);

void func_800DE62C(void) // 0x800DE62C
{
    // TODO: Find which `FS_BUFFER_x` this is zeroing part of.
    memset((void*)0x801E8701, 0, 0x214);
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DE658);

void func_800DE8F0(MATRIX* mat, SVECTOR* arg1, SVECTOR3* result) // 0x800DE8F0
{
    s32 sxy;
    s32 unused;

    SetRotMatrix(mat);
    SetTransMatrix(mat);

    result->vz = RotTransPers(arg1, &sxy, &unused, &unused);
    result->vx = sxy;
    result->vy = sxy >> 16;
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DE95C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DEA4C);

void func_800DEA94(s32* arg0) // 0x800DEA94
{
    if (arg0 != NULL)
    {
        *arg0 = 0;
    }
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DEAA8);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DEB1C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DEC3C);

void func_800DED30(void) // 0x800DED30
{
    func_800DEAA8(0);
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DED50);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DEDEC);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DEF50);

void func_800DF134(void) // 0x800DF134
{
    func_800DEAA8(1);
    D_800ED588++;
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DF160);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DF2F0);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DF41C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DF5B0);

void func_800DF618(void) // 0x800DF618
{
    func_800DEAA8(2);
    func_800DE274();
    D_800ED588++;
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DF64C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DF670);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DF6C4);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DFA38);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DFB44);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DFBB0);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DFC94);

void func_800DFD08(void) // 0x800DFD08
{
    func_800DEAA8(4);
    func_800DE274();
    D_800ED588++;
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800DFD3C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E00F4);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0164);

void func_800E01F4(void) // 0x800E01F4
{
    D_800ED588 = 6;
}

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CB69C);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CB6AC);

// TODO: rodata mismatch
#ifdef NON_MATCHING
void func_800E0204(void) // 0x800E0204
{
    if (D_800ED588 == 0)
    {
        if (!Fs_QueueDoThingWhenEmpty())
        {
            return;
        }

        D_800ED588++;
        func_800DE274();
    }

    switch (D_800ED588)
    {
        case 1:
        case 2:
        case 6:
            break;

        case 3:
            func_800DE95C();
            func_800E0164();
            func_800DFB44();
            break;

        case 4:
            func_800DE95C();
            func_800E0164();
            func_800DE5CC();
            break;

        case 5:
            func_800DE95C();
            func_800E0164();
            func_800E00F4();
            break;
    }
}
#else
INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0204);
#endif

void func_800E02E0(void) // 0x800E02E0
{
    D_800ED588 = 0;
    func_800DE26C();
    func_800DF64C();
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E030C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0358);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E03C4);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E05C8);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E068C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0878);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E08B8);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0BB0);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0C58);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0CCC);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0D8C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0DC4);

s32 func_800E0F28(q19_12 val0, q19_12 val1) // 0x800E0F28
{
    s32 integer;
    s32 fraction;

    integer  = Q12_MULT_PRECISE(val0, val1) / 0x1000;
    fraction = Q12_MULT_PRECISE(val0, val1) % 0x1000;

    if ((Rng_Rand16() / 8) < fraction)
    {
        integer++;
    }

    return integer;
}

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CB728);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E0FAC);

void func_800E10F8(void) // 0x800E10F8
{
    D_800ED58C = 0;
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E1104

#include "maps/shared/sharedFunc_800E1114_6_s04.h" // 0x800E1114

#include "maps/shared/sharedFunc_800E1258_6_s04.h" // 0x800E1258

#include "maps/shared/sharedFunc_800E1290_6_s04.h" // 0x800E1290

#include "maps/shared/sharedFunc_800E12D0_6_s04.h" // 0x800E12D0

// TODO: Might be part of shared block above with `map6_s05::func_800CCBFC`
void func_800E155C(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800E1564

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E15FC);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E1CA0);

void func_800E1D48(void) {}

// TODO: rodata used in a bunch of funcs, can't be inserted properly until they're all decomped.
extern char D_800CC4C4[]; // "HERO"
extern char D_800CC4CC[]; // "LIGHT"
extern char D_800CC4D4[]; // "L_INT"
extern char D_800CC4DC[]; // "MSB"

void func_800E1D50(void) // 0x800E1D50
{
    typedef enum _EventState
    {
        EventState_Skip = 3
    } e_EventState;

    VECTOR3  lintPos;
    SVECTOR3 lintRot;
    q19_12   rotX;
    q19_12   rotZ;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < EventState_Skip)
    {
        SysWork_StateStepSet(0, EventState_Skip);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800ED5AC = 0;
            D_800ED5B0 = 0;
            g_SysWork.flags_22A4 |= SysFlag2_4;

            Game_TurnFlashlightOn();
            func_800E1CA0();
            func_8007E860();
            Fs_QueueStartRead(FILE_ANIM_HBM6_S4B_ANM, FS_BUFFER_4);
            Fs_QueueStartRead(FILE_ANIM_PARK_DMS, FS_BUFFER_14);

            D_800A9938 = 0x38630;

            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_14);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            Anim_CharaTypeAnimInfoClear();
            Chara_Load(0, Chara_MonsterCybil, g_SysWork.npcCoords_FC0, -1, NULL, NULL);

            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 113, false);
            SysWork_StateStepIncrement(0);
            break;

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(0.0f), Q12(19.0f), false, true);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            D_800ED5B0 = NO_VALUE;

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_MonsterCybil, 0, Q12(26.5f), Q12(108.5f), Q12(0.03125f), 3);
            func_800E15FC(&g_SysWork.playerWork_4C, &g_SysWork.npcs_1A0[0], true);
            Savegame_EventFlagSet(EventFlag_441);
            break;
    }

    if (D_800ED5B0 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, D_800CC4C4, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &lintRot, D_800CC4CC, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        Dms_CharacterGetPosRot(&lintPos, &lintRot, D_800CC4D4, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);

        rotX = Q12_TO_Q6(lintPos.vx - g_SysWork.pointLightPosition_2360.vx);
        rotZ = Q12_TO_Q6(lintPos.vz - g_SysWork.pointLightPosition_2360.vz);

        g_SysWork.pointLightRot_2370.vx = -ratan2(lintPos.vy - g_SysWork.pointLightPosition_2360.vy, Q6_TO_Q12(SquareRoot0(SQUARE(rotX) + SQUARE(rotZ))));
        g_SysWork.pointLightRot_2370.vy = ratan2(lintPos.vx - g_SysWork.pointLightPosition_2360.vx, lintPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = FP_ANGLE(0.0f);
    }
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tGotta'_go_find_Cybil! ~N\n\tNo_time_to_go_back. ~E ",
    "~J0(10)\t~E ",
    "~J0(10)\tCybil! ~E ",
    "~J0(2.3)\tWake_up!_Snap_out_of_it! ~E ",
    "~J0(1.0)\tCybil! ~E ",
    "~J0(4.7)\t...Harry? ~N\n\t\t\t...What...happened? ",
    "~J0(3.3)\tDon't_talk. ~N\n\t\t\tI'll_take_care_of_you. ~E ",
    "~J1(4.8)\tHarry... ~N\n\t\t\tWhy_did_they_take_your_daughter? ",
    "~J1(2.3)\tWhy_her? ",
    "~J1(3.0)\tI'm_not_sure,_myself. ",
    "~J1(4.3)\tBut_you_know,_Cheryl_isn't ~N\n\t\t\tmy_biological_daughter. ",
    "~J1(3.0)\tI_actually_haven't_told_her_yet. ",
    "~J1(3.3)\tShe_probably_already_knows ~N\n\t\t\tanyway,_though. ~E ",
    "~J1(3.9)\tWe_found_her_abandoned ~N\n\t\t\ton_the_side_of_the_highway. ",
    "~J1(3.3)\tNobody_knew ~N\n\t\t\twhere_she_came_from. ",
    "~J1(3.3)\tWe_didn't_have_any_kids ~N\n\t\t\tof_our_own. ",
    "~J1(2.4)\tMy_wife_was_sick, ",
    "~J1(3.4)\tand_it_didn't_look_like ~N\n\t\t\tshe_was_getting_any_better. ",
    "~J1(2.7)\tSo_we_took_Cheryl_in. ~E ",
    "~J1(3.1)\tSo_in_that_case... ",
    "~J1(5.2)\tThere_might_be_some_connection ~N\n\t\t\tbetween_Cheryl_and_this_town. ~E ",
    "~J1(3.4)\tSo_what_do_you_do_now? ",
    "~J1(3.5)\tCheryl_is_my_daughter. ~N\n\t\t\tI_will_save_her. ",
    "~J1(4.5)\tNo_matter_what. ~E ",
    "~J0(7.3)\t~E ",
    "~J0(7.0)\t~E ",
    "~J0(6.0)\tWhat_in_the_hell... ~N\n\t\t\tHow_could_this_have_happened? ~E ",
    "~J1(1.7)\tI_figured_you'd_show. ",
    "~J1(1.6)\tHold_it_right_there. ",
    "~J1(4.0)\tI_don't_know_who_you_are, ~N\n\t\t\twhat_you_are_trying_to_do, ~N\n\t\t\tand_I_don't_care. ",
    "~J1(1.6)\tJust_one_thing. ",
    "~J1(3.1)\tLet_Cheryl_go. ~N\n\t\t\tThat's_all_I_ask. ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(1.0)\tDamn! ~E ",
    "~J0(1.2)\tHuh? ~E ",
    "~J0(1.5)\tWhat_is_this? ~E ",
    "~J0(1.4)\t~E ",
    "~J1(1.6)\tWhere's_Cheryl? ",
    "~J1(2.0)\tGive_me_back_my_daughter. ~E ",
    "~J0(3.2)\tWe_meet_at_last,_Alessa. ",
    "~J0(1.2)\t.......! ~E ",
    "~J1(1.8)\tDahlia_Gillespie...... ",
    "~J1(2.0)\tWhere's_Cheryl? ~N\n\t\t\tWhere_is_she!? ~E ",
    "~J1(1.2)\tAlessa. ",
    "~J1(4.0)\tThis_is_the_end_of ~N\n\t\t\tyour_little_game. ",
    "~J1(1.2)\tMama... ",
    "~J1(2.7)\tHuh? ~N\n\t\t\tCould_she_be...? ~E ",
    "~J1(4.6)\tYou've_been_a_ghastly_little_pest, ~N\n\t\t\thaven't_you?__Alessa? ",
    "~J1(2.0)\tI_was_careless. ",
    "~J1(3.5)\tThinking_you_couldn't_escape ~N\n\t\t\tfrom_our_spell. ",
    "~J1(4.5)\tBut_Mommy_didn't_know ~N\n\t\t\thow_much_you'd_grown. ",
    "~J1(4.3)\tThat's_why_I_couldn't_catch_you ~N\n\t\t\tall_by_myself. ",
    "~J1(2.8)\tBut_what_a_pity,_yes? ",
    "~J1(5.0)\tNow_you're_half_indebted ~N\n\t\t\tto_this_man_for_his_help. ",
    "~J1(2.7)\tHey! ~N\n\t\t\tWhat_are_you_talking_about? ",
    "~J1(6.9)\tAlessa._My_dear_little_girl... ~N\n\t\t\tThere_is_one_thing_left ~N\n\t\t\tI_need_you_to_do_for_me. ~E ",
    "~J0(2.3)\tNo. ~N\n\t\t\tGet_away_from_me. ",
    "~J0(1.8)\tBad_girl. ",
    "~J0(5.1)\tEverything_is_ready. ~N\n\t\t\tLet's_go_home_now. ~E ",
    "~J0(1.7)\tWhat's_going_on_here!? ~E ",
    "~J0(1.2)\t~E "
};

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC424);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4A4);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4C4);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4CC);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4D4);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4DC);

void func_800E219C(void) // 0x800E219C
{
    VECTOR3  lightIntPos;
    SVECTOR3 unused;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 8)
    {
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Game_TurnFlashlightOn();

            D_800ED5AC = 0;
            Savegame_EventFlagSet(EventFlag_461);
            D_800ED5B0 = Q12(21.0f);

            SysWork_StateStepIncrement(0);
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;

        case 1:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 168, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(21.0f), Q12(68.0f), false, true);
            break;

        case 3:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 10, false);
            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(69.0f), Q12(80.0f), false, true);
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 6:
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 167, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(81.0f), Q12(95.0f), true, true);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        default:
            D_800ED5B0 = NO_VALUE;

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(25.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(100.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(337.5f);

            // Warp NPC.
            g_SysWork.npcs_1A0[0].position_18.vx = Q12(24.0f);
            g_SysWork.npcs_1A0[0].position_18.vz = Q12(102.0f);
            g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(157.5f);

            // TODO: Wrong properties union field.
            g_SysWork.npcs_1A0[0].properties_E4.player.afkTimer_E8                      = Q12(0.0f);
            g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[1].val16[0] = 1;
            g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[1].val16[1] = 1;

            vcReturnPreAutoCamWork(true);
            func_800E15FC(&g_SysWork.playerWork_4C, &g_SysWork.npcs_1A0[0], true);
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);

            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            Savegame_EventFlagSet(EventFlag_443);

            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            func_800D8A90(&g_SysWork.npcs_1A0[0]);
            func_8003A16C();

            Savegame_EventFlagSet(EventFlag_467);
            break;
    }

    if (D_800ED5B0 >= Q12(0.0f))
    {
        // Get "HERO" position.
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, D_800CC4C4, D_800ED5B0, FS_BUFFER_14);

        // Get "MSB" position
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CC4DC, D_800ED5B0, FS_BUFFER_14);

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);

        // "LIGHT", cutscene light position?
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, D_800CC4CC, D_800ED5B0, FS_BUFFER_14);

        // "L_INT", interior light or intersection point?
        Dms_CharacterGetPosRot(&lightIntPos, &unused, D_800CC4D4, D_800ED5B0, FS_BUFFER_14);

        // Set light rotation.
        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy =  ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = FP_ANGLE(0.0f);
    }
}

void func_800E2724(void) // 0x800E2724
{
    s32 curStateStep;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= SysFlag2_4;

            func_800E1CA0();
            func_8007E860();
            Fs_QueueStartRead(FILE_ANIM_HBM6_S4B_ANM, FS_BUFFER_4);

            D_800A9938 = 0x38630;

            Anim_CharaTypeAnimInfoClear();

            // Load Monster Cybil character.
            Chara_Load(0, Chara_MonsterCybil, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_MonsterCybil, 0, Q12(26.5f), Q12(108.5f), FP_ANGLE(11.3f), 3);

            // Warp camera to start position.
            Camera_PositionSet(NULL, Q12(25.27f), Q12(-2.4f), Q12(98.43f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(23.78f), Q12(-1.04f), Q12(101.88f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            // Warp player to start position.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(25.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(100.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(337.5f);

            // Warp Monster Cybil character to start position.
            g_SysWork.npcs_1A0[0].position_18.vx = Q12(24.0f);
            g_SysWork.npcs_1A0[0].position_18.vz = Q12(102.0f);
            g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(157.5f);

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            curStateStep = g_SysWork.sysStateStep_C[0];

            // TODO: `Chara_MonsterCybil` properties
            g_SysWork.npcs_1A0[0].properties_E4.player.afkTimer_E8                      = Q12(0.0f);
            g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[1].val16[0] = curStateStep;
            g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[1].val16[1] = curStateStep;
            func_800D8A90(&g_SysWork.npcs_1A0[0]);

            Savegame_EventFlagSet(EventFlag_467);

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            vcReturnPreAutoCamWork(true);
            func_800E15FC(&g_SysWork.playerWork_4C, &g_SysWork.npcs_1A0[0], true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void func_800E2950(void) // 0x800E2950
{
    VECTOR3 camPos;
    VECTOR3 camLookAt;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            func_8007FD4C(true);
            sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);

            g_SysWork.field_30 = 20;

            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            Game_TurnFlashlightOn();

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(23.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(103.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(135.0f);

            // Warp NPC.
            g_SysWork.npcs_1A0[0].position_18.vx = Q12(18.0f);
            g_SysWork.npcs_1A0[0].position_18.vz = Q12(96.0f);
            g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(135.0f);

            // Warp camera.
            Math_Vector3Set(&camPos, Q12(18.0f), Q12(-1.5f), Q12(94.5f));
            Math_Vector3Set(&camLookAt, Q12(18.0f), Q12(-1.3f), Q12(96.0f));
            Camera_PositionSet(&camPos, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(&camLookAt, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            func_8008D438();

            g_SysWork.field_236C = NULL;

            g_SysWork.pointLightRot_2370.vx = -ratan2(camLookAt.vy - camPos.vy, Math_Vector2MagCalc(camLookAt.vx - camPos.vx, camLookAt.vz - camPos.vz));
            g_SysWork.pointLightRot_2370.vy = ratan2(camLookAt.vx - camPos.vx, camLookAt.vz - camPos.vz);
            g_SysWork.pointLightRot_2370.vz = FP_ANGLE(0.0f);

            g_SysWork.field_235C = NULL;

            g_SysWork.pointLightPosition_2360.vx = camPos.vx;
            g_SysWork.pointLightPosition_2360.vy = MAX(Q12(-1.5f), camPos.vy);
            g_SysWork.pointLightPosition_2360.vz = camPos.vz;

            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 4, false);

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085EB8(2, &g_SysWork.npcs_1A0[0], 0, false);
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 2:
            func_80085EB8(3, &g_SysWork.npcs_1A0[0], 0, false);
            SysWork_StateStepIncrement(0);
            break;

        case 3:
            func_80085EB8(1, &g_SysWork.npcs_1A0[0], 0, false);
            break;

        default:
            vcReturnPreAutoCamWork(true);
            func_800E15FC(&g_SysWork.playerWork_4C, &g_SysWork.npcs_1A0[0], true);
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            Savegame_EventFlagSet(EventFlag_445);
            break;
    }
}

void MapEvent_CutsceneCybilDeath(void) // 0x800E2CA0
{
    VECTOR3         lightIntPos;
    SVECTOR3        unused;
    s_SubCharacter* player;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] == 7)
    {
        SysWork_StateStepSet(0, 8);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            D_800EBA30 = 0;
            D_800ED5B6 = 0;

            Game_TurnFlashlightOn();
            func_8003D03C();
            Sd_SfxStop(Sfx_Unk1617);
            Player_ControlFreeze();

            g_SysWork.npcs_1A0[0].health_B0 = NO_VALUE;

            D_800ED5AC           = 0;
            D_800ED5B0           = Q12(96.0f);
            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);
            break;

        case 3:
            SD_Call(16);
            SD_Call(19);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 162, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(96.0f), Q12(131.0f), false, false);

            // Possible inline?
            player = &g_SysWork.playerWork_4C.player_0;
            if (player->model_0.anim_4.keyframeIdx_8 > 1282)
            {
                func_80085EB8(2, player, 0, false);
            }

            SysWork_StateStepIncrement(0);

        case 5:
            // Possible inline?
            player = &g_SysWork.playerWork_4C.player_0;
            if (player->model_0.anim_4.keyframeIdx_8 > 1282)
            {
                func_80085EB8(2, player, 0, false);
            }

            SysWork_StateStepIncrement(0);

        case 6:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(131.0f), Q12(195.0f), false, false);
            MapMsg_DisplayAndHandleSelection(false, 41, 0, 0, 0, false);

            if (g_SysWork.sysStateStep_C[0] != 7)
            {
                Savegame_EventFlagSet(EventFlag_463);
            }
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.5f), false);
            break;

        default:
            D_800ED5B0 = NO_VALUE;
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_447);
            Savegame_EventFlagSet(EventFlag_450);

            vcReturnPreAutoCamWork(true);
            func_8008D448();
            Game_FlashlightAttributesFix();
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            SD_Call(19);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            break;
    }

    if (D_800ED5B0 > Q12(96.0f))
    {
        // Get "HERO" position.
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, D_800CC4C4, D_800ED5B0, FS_BUFFER_14);

        // Get "MSB" position
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CC4DC, D_800ED5B0, FS_BUFFER_14);

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);

        // "LIGHT", cutscene light position?
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, D_800CC4CC, D_800ED5B0, FS_BUFFER_14);

        // "L_INT", interior light or intersection point?
        Dms_CharacterGetPosRot(&lightIntPos, &unused, D_800CC4D4, D_800ED5B0, FS_BUFFER_14);

        // Set light rotation.
        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy =  ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = FP_ANGLE(0.0f);
    }
}

void func_800E3244(void) // 0x800E3244
{
    typedef enum _EventState
    {
        EventState_Skip = 28
    } e_EventState;

    VECTOR3  lintPos;
    SVECTOR3 lintRot;
    q19_12   posX;
    q19_12   lookAtX;
    q19_12   rotX;
    q19_12   rotZ;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 27)
    {
        if (g_SysWork.sysStateStep_C[0] != 20 &&
            g_SysWork.sysStateStep_C[0] != 22)
        {
            SysWork_StateStepSet(0, EventState_Skip);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            D_800EBA30 = 0;
            D_800ED5B6 = 0;

            Sd_SfxStop(Sfx_Unk1617);
            Player_ControlFreeze();
            sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);

            g_SysWork.npcs_1A0[0].health_B0 = NO_VALUE;

            Game_TurnFlashlightOn();
            D_800ED5B0 = 0;
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            D_800ED5AC = 0;

            Fs_QueueStartRead(FILE_ANIM_AMUSE1_DMS, FS_BUFFER_14);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_14);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(0.5f);

            Chara_Load(1, Chara_Parasite, &g_SysWork.npcCoords_FC0[30], 0, NULL, NULL);

            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            WorldGfx_PlayerHeldItemSet(InventoryItemId_CutscenePlasticBottle);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 170, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(0.0f), Q12(24.0f), false, true);
            func_800E73B4(D_800ED5B0);
            break;

        case 3:
            SysWork_StateStepIncrement(0);

        case 4:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 185, false);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(25.0f), Q12(58.0f), false, true);
            break;

        case 6:
            D_800ED5B0 = Q12(59.0f);

            Chara_ProcessLoads();
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 160, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            Savegame_EventFlagSet(EventFlag_462);

            func_800E7944(0);
            Map_MessageWithAudio(39, &D_800ED5AC, D_800EBA34);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(59.0f), Q12(139.0f), false, true);
            func_800E7944(2);
            break;

        case 8:
            Chara_Spawn(Chara_Parasite, 0, Q12(20.0f), Q12(100.0f), 0, 3);
            func_8005DC1C(Sfx_Unk1625, &g_SysWork.npcs_1A0[1].position_18, 32, 0);
            func_8005DC1C(Sfx_Unk1624, &g_SysWork.npcs_1A0[1].position_18, 32, 0);
            func_800E7944(1);
            SysWork_StateStepIncrement(0);

        case 9:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(140.0f), Q12(183.0f), false, true);
            func_8005DE0C(Sfx_Unk1624, &g_SysWork.npcs_1A0[1].position_18, 32, Q12(16.0f), 0);
            func_800E7944(2);
            break;

        case 10:
            SD_Call(19);

            D_800ED5B0 = Q12(186.0f);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 163, false);
            func_800E7944(3);
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(5.0f), Q12(186.0f), Q12(193.0f), false, true);
            func_8005DE0C(Sfx_Unk1624, &g_SysWork.npcs_1A0[1].position_18, 32, Q12(16.0f), 0);
            break;

        case 12:
            D_800ED5B0 = Q12(195.0f);

            ModelAnim_StatusIncrement(&g_SysWork.npcs_1A0[1].model_0.anim_4);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 151, false);
            SysWork_StateStepIncrement(0);

        case 13:
            if (D_800ED5B0 < Q12(202.0f))
            {
                func_8005DE0C(Sfx_Unk1624, &g_SysWork.npcs_1A0[1].position_18, 32, Q12(16.0f), 0);
            }
            else
            {
                Sd_SfxStop(Sfx_Unk1624);
            }

            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(195.0f), Q12(213.0f), false, true);
            break;

        case 14:
            D_800ED5B0 = Q12(216.0f);

            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 161, false);
            SysWork_StateStepIncrement(0);

        case 15:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(216.0f), Q12(243.0f), false, true);

            if (D_800ED5B0 >= Q12(219.0f))
            {
                Map_MessageWithAudio(17, &D_800ED5AC, D_800EBA34);
            }
            break;

        case 16:
            SysWork_StateStepIncrement(0);

        case 17:
            Map_MessageWithAudio(18, &D_800ED5AC, D_800EBA34); // "Wake up! Snap out of it!"
            break;

        case 18:
            Map_MessageWithAudio(19, &D_800ED5AC, D_800EBA34); // "Cybil!"

            if (g_SysWork.sysStateStep_C[0] != 18)
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            }
            break;

        case 19:
            Map_MessageWithAudio(20, &D_800ED5AC, D_800EBA34); // "...Harry? What... happened?"
            break;

        case 20:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.0f), false);
            break;

        case 21:
            D_800ED5B4 = -0x7A;

            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, (1<<1));
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            D_800ED5B0 = NO_VALUE;

            func_8008D438();

            g_SysWork.pointLightIntensity_2378 = Q12(0.3594f);
            D_800ED5B8 = 1;

            SysWork_StateStepIncrement(0);

        case 22:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
            break;

        case 23:
            Map_MessageWithAudio(22, &D_800ED5AC, D_800EBA34);
            break;

        case 24:
            Map_MessageWithAudio(28, &D_800ED5AC, D_800EBA34);
            break;

        case 25:
            Map_MessageWithAudio(34, &D_800ED5AC, D_800EBA34);
            break;

        case 26:
            Map_MessageWithAudio(36, &D_800ED5AC, D_800EBA34);
            break;

        case 27:
            SD_Call(19);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.8f), false);
            break;

        case EventState_Skip:
            SD_Call(19);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            func_800E7944(3);

            D_800ED5B0 = NO_VALUE;

            sharedFunc_800D2EF4_0_s00();
            WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            sharedFunc_800D88C0_0_s00(&g_SysWork.npcs_1A0[0], false);
            vcReturnPreAutoCamWork(true);
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            Savegame_EventFlagSet(EventFlag_449);
            Savegame_EventFlagSet(EventFlag_450);

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);

            Sd_SfxStop(Sfx_Unk1625);
            Sd_SfxStop(Sfx_Unk1624);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, (1<<1));
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 22 && g_SysWork.sysStateStep_C[0] <= 27)
    {
        posX = FP_FROM(Math_Sin(D_800ED5B6) * Q12(5.2f), Q12_SHIFT) + Q12(20.0f);
        Camera_PositionSet(NULL, posX, Q12(-2.0f), FP_FROM(Math_Cos(D_800ED5B6) * Q12(5.2f), Q12_SHIFT) + Q12(100.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

        lookAtX = FP_FROM(Math_Sin(D_800ED5B6 - Q12(0.172f)) * Q12(3.7f), Q12_SHIFT) + Q12(20.0f);
        Camera_LookAtSet(NULL, lookAtX, Q12(-1.0f), FP_FROM(Math_Cos(D_800ED5B6 - 704) * Q12(3.7f), Q12_SHIFT) + Q12(100.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

        Math_Vector3Set(&g_SysWork.pointLightPosition_2360, FP_FROM(Math_Sin(D_800ED5B6 - Q12(0.2188f)) * Q12(4.8f), Q12_SHIFT) + Q12(20.0f),
                        Q12(-1.0f),
                        FP_FROM(Math_Cos(D_800ED5B6 - Q12(0.2188f)) * Q12(4.8f), Q12_SHIFT) + Q12(100.0f));
        Math_SetSVectorFast(&g_SysWork.pointLightRot_2370, FP_ANGLE(-39.4f), (D_800ED5B6 + FP_ANGLE(182.9f)), FP_ANGLE(0.0f));
        func_800E74C4();
    }

    if (D_800ED5B0 > Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, D_800CC4C4, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CC4DC, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "ICU", D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);

        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &lintRot, D_800CC4CC, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        Dms_CharacterGetPosRot(&lintPos, &lintRot, D_800CC4D4, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);

        rotX = Q12_TO_Q6(lintPos.vx - g_SysWork.pointLightPosition_2360.vx);
        rotZ = Q12_TO_Q6(lintPos.vz - g_SysWork.pointLightPosition_2360.vz);

        g_SysWork.pointLightRot_2370.vx = -ratan2(lintPos.vy - g_SysWork.pointLightPosition_2360.vy, Q6_TO_Q12(SquareRoot0(SQUARE(rotX) + SQUARE(rotZ))));
        g_SysWork.pointLightRot_2370.vy = ratan2(lintPos.vx - g_SysWork.pointLightPosition_2360.vx, lintPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = FP_ANGLE(0.0f);
    }
}

void func_800E3EF4(void) // 0x800E3EF4
{
    typedef struct
    {
        SPRT*     sprt_0;
        DR_TPAGE* tpage_4;
        DR_STP*   stp_8;
        u8        unk_C[4];
        u8        unk_10[4];
        s32       activeBufferIdx_14;
    } g_GteScratchData_func_800DD2D4;

    g_GteScratchData_func_800DD2D4* scratchData;

    VECTOR3       lightIntPos;
    SVECTOR3      unused;
    s_FsImageDesc sp30;
    s32           i;

    scratchData = PSX_SCRATCH_ADDR(0);

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 4 && g_SysWork.sysStateStep_C[0] < 63)
    {
        func_800E01F4();
        SysWork_StateStepSet(0, 65);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800ED5AD = 1;
            D_800ED5AC = 0;

            Fs_QueueStartRead(FILE_ANIM_AMUSE2_DMS, FS_BUFFER_14);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_14);
            WorldObject_ModelNameSet(&g_WorldObject_SFlauros.object_0, "SFLAU_HI");

            D_800ED5B0 = 0;
            D_800EBB60 = 0;
            D_800EBB61 = 0;

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_8008D438();

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            sharedFunc_800D2EB4_0_s00();
            func_8003D03C();
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80087EDC(36);
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 4:
            Map_MessageWithAudio(42, &D_800ED5AC, &D_800EBA64);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 4, false);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(1.0f), Q12(24.0f), false, true);
            break;

        case 7:
            Map_MessageWithAudio(47, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(1.0f), Q12(39.0f), false, true);
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 149, false);

            D_800EBAA8 = 1;

            func_800892A4(8);
            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(47, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(1.0f), Q12(59.0f), false, false);
            break;

        case 10:
            Chara_Load(1, Chara_Flauros, &g_SysWork.npcCoords_FC0[30], 0, NULL, NULL);
            D_800EBAA8 = 0;
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(1.0f), Q12(59.0f), false, true);
            break;

        case 12:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, false);
            SysWork_StateStepIncrement(0);

        case 13:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(1.0f), Q12(79.0f), true, true);
            break;

        case 14:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(80.0f), Q12(104.0f), true, true);
            g_SysWork.pointLightIntensity_2378 = Q12(2.0f);
            Savegame_EventFlagSet(EventFlag_452);
            break;

        case 15:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 150, false);
            func_800DFC94(&D_800ED5B0);

            g_SysWork.pointLightIntensity_2378 = Q12(0.8f);

            SysWork_StateStepIncrement(0);

        case 16:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(105.0f), Q12(114.0f), false, true);
            break;

        case 17:
            Map_MessageWithAudio(48, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(105.0f), Q12(162.0f), true, false);
            break;

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(105.0f), Q12(162.0f), true, true);
            break;

        case 19:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 152, false);
            func_800DFD08();
            func_800DEC3C(&g_WorldObject_SFlauros.position_1C, &g_WorldObject_SFlauros.rotation_28);

            D_800EBB61 = 3;
            Savegame_EventFlagSet(EventFlag_464);
            g_SysWork.pointLightIntensity_2378 = Q12(0.7f);

            SysWork_StateStepIncrement(0);

        case 20:
            Map_MessageWithAudio(49, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(163.0f), Q12(199.0f), true, false);
            break;

        case 21:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(163.0f), Q12(199.0f), true, true);
            break;

        case 22:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 188, false);

            g_SysWork.pointLightIntensity_2378 = Q12(0.6f);
            D_800EBB61           = 1;

            func_8005DC1C(Sfx_Unk1635, NULL, Q8_CLAMPED(1.0f), 3);
            SysWork_StateStepIncrement(0);

        case 23:
            Map_MessageWithAudio(50, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(200.0f), Q12(229.0f), true, false);
            break;

        case 24:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(200.0f), Q12(229.0f), true, true);
            break;

        case 25:
            Chara_ProcessLoads();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            func_8005DC1C(Sfx_Unk1636, NULL, Q8_CLAMPED(1.0f), 3);
            func_800DED30();
            func_800DEF50(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcCoords_FC0[30], &D_800ED5B0);
            Chara_Spawn(Chara_Flauros, 0, g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(1.0f), g_SysWork.playerWork_4C.player_0.position_18.vz, Q8_CLAMPED(0.5f), 3);

            D_800EBB61 = 2;

            SysWork_StateStepIncrement(0);

        case 26:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(230.0f), Q12(299.0f), true, true);
            break;

        case 27:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 3, false);
            SysWork_StateStepIncrement(0);

        case 28:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(300.0f), Q12(310.0f), true, true);
            break;

        case 29:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);

            D_800EBB61 = 1;

            SysWork_StateStepIncrement(0);

        case 30:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(311.0f), Q12(357.0f), false, true);
            break;

        case 31:
            Sd_SfxStop(Sfx_Unk1636);
            Sd_SfxStop(Sfx_Unk1635);
            func_8005DC1C(Sfx_Unk1634, NULL, Q8_CLAMPED(1.0f), 3);
            SysWork_StateStepIncrement(0);

        case 32:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(311.0f), Q12(365.0f), false, true);
            break;

        case 33:
            Map_MessageWithAudio(51, &D_800ED5AC, &D_800EBA64);
            func_800DF134();

            D_800EBB70.vx = g_SysWork.npcs_1A0[0].position_18.vx;
            D_800EBB70.vy = g_SysWork.npcs_1A0[0].position_18.vy - Q12(1.0f);
            D_800EBB70.vz = g_SysWork.npcs_1A0[0].position_18.vz;

            func_800DF5B0(&g_WorldObject_SFlauros.position_1C, &D_800EBB70);
            SysWork_StateStepIncrement(0);

        case 34:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 35:
            func_8005DC1C(Sfx_Unk1633, NULL, Q8_CLAMPED(1.0f), 3);
            SysWork_StateStepIncrement(0);

        case 36:
            func_80085EB8(1, &g_SysWork.npcs_1A0[0], 0, false);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(311.0f), Q12(386.0f), true, false);
            break;

        case 37:
            SysWork_StateStepIncrement(0);

        case 38:
            func_80086C58(&g_SysWork.npcs_1A0[0], 5);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(387.0f), Q12(431.0f), true, false);
            break;

        case 39:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 53, false);
            func_800DF618();
            D_800EBB61 = 0;
            SysWork_StateStepIncrement(0);

        case 40:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(432.0f), Q12(454.0f), true, true);
            break;

        case 41:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            g_SysWork.pointLightIntensity_2378 = Q12(0.6f);
            SysWork_StateStepIncrement(0);

        case 42:
            Map_MessageWithAudio(52, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(455.0f), Q12(455.0f), true, false);

            if (g_SysWork.sysStateStep_C[0] != 42)
            {
                SD_Call(19);
            }
            break;

        case 43:
            if (!Sd_AudioStreamingCheck())
            {
                D_800ED5B0 = NO_VALUE;

                Chara_FsImageCalc(&sp30, Chara_Dahlia, 2);
                Chara_Load(1, Chara_Dahlia, &g_SysWork.npcCoords_FC0[30], 2, NULL, &sp30);
                Fs_QueueStartRead(FILE_ANIM_AMUSE2B_DMS, FS_BUFFER_14);
                SysWork_StateStepIncrement(0);
            }
            else
            {
                break;
            }

        case 44:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 45:
            DmsHeader_FixOffsets(FS_BUFFER_14);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Dahlia, 0, Q12(-40.0f), Q12(-40.0f), FP_ANGLE(0.0f), 3);
            Savegame_EventFlagClear(EventFlag_452);
            Savegame_EventFlagSet(EventFlag_465);

            g_SysWork.pointLightIntensity_2378 = Q12(0.6f);

            SysWork_StateStepIncrement(0);
            break;

        case 46:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 14, false);
            D_800EBB60 = 1;
            SysWork_StateStepIncrement(0);

        case 47:
            Map_MessageWithAudio(54, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(0.0f), Q12(10.0f), false, true);
            break;

        case 48:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            SysWork_StateStepIncrement(0);

        case 49:
            Map_MessageWithAudio(54, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(0.0f), Q12(30.0f), true, false);
            break;

        case 50:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 12, false);

            D_800ED5B0 = Q12(31.0f);

            SysWork_StateStepIncrement(0);

        case 51:
            Map_MessageWithAudio(56, &D_800ED5AC, &D_800EBA64);
            break;

        case 52:
            Map_MessageWithAudio(58, &D_800ED5AC, &D_800EBA64);
            break;

        case 53:
            Map_MessageWithAudio(62, &D_800ED5AC, &D_800EBA64);
            break;

        case 54:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 13, false);
            g_SysWork.pointLightIntensity_2378 = Q12(0.7f);
            SysWork_StateStepIncrement(0);

        case 55:
            Map_MessageWithAudio(71, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(32.0f), Q12(80.0f), false, true);
            break;

        case 56:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            SysWork_StateStepIncrement(0);

        case 57:
            Map_MessageWithAudio(71, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(32.0f), Q12(110.0f), true, false);
            break;

        case 58:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(32.0f), Q12(110.0f), true, true);
            break;

        case 59:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 123, false);
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            SysWork_StateStepIncrement(0);

        case 60:
            Map_MessageWithAudio(74, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(111.0f), Q12(145.0f), true, false);
            break;

        case 61:
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.5f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 62:
            Map_MessageWithAudio(75, &D_800ED5AC, &D_800EBA64);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(111.0f), Q12(145.0f), true, false);
            break;

        case 63:
            SysWork_StateStepIncrement(0);
            Sd_SfxStop(Sfx_Unk1636);

        case 64:
            SysWork_StateStepIncrement(0);

        case 65:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 66:
            if (g_SysWork.npcs_1A0[1].model_0.charaId_0 == Chara_Flauros)
            {
                func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);
            }

            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            ScreenFade_ResetTimestep();

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);

            Savegame_EventFlagSet(EventFlag_451);

            Player_ItemRemove(InventoryItemId_Flauros, 1);

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            D_800A9938 = 190000;

            SD_Call(19);
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378  = Q12(1.0f);
            g_SysWork.flags_22A4 &= ~SysFlag2_4;
            break;
    }

    if (D_800EBAA8 != 0)
    {
        scratchData->activeBufferIdx_14 = g_ActiveBufferIdx;
        scratchData->sprt_0             = (SPRT*)GsOUT_PACKET_P;
        for (i = 0; i < 2; i++)
        {
            setCodeWord(scratchData->sprt_0, PRIM_RECT | RECT_BLEND | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
            setXY0Fast(scratchData->sprt_0, ((i << 8) - 160), -112);
            scratchData->sprt_0->u0 = 0;
            scratchData->sprt_0->v0 = (scratchData->activeBufferIdx_14 == 0) ? 32 : 0;
            setWH(scratchData->sprt_0, (i == 0) ? 256 : 64, 224);
            addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->sprt_0, 4);

            scratchData->sprt_0++;
            scratchData->tpage_4 = (DR_TPAGE*)scratchData->sprt_0;
            setDrawTPage(scratchData->tpage_4, 0, 0, getTPageFromBuffer(2, 0, scratchData->activeBufferIdx_14, i));

            AddPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->tpage_4);
            scratchData->tpage_4++;
            scratchData->sprt_0 = (SPRT*)scratchData->tpage_4;
        }

        scratchData->stp_8 = (DR_STP*)scratchData->sprt_0;
        SetDrawStp(scratchData->stp_8, 1);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratchData->stp_8);
        scratchData->stp_8++;
        SetDrawStp(scratchData->stp_8, 0);
        addPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[0], scratchData->stp_8);
        scratchData->stp_8++;
        GsOUT_PACKET_P = (PACKET*)scratchData->stp_8;
    }

    if (D_800ED5B0 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, &D_800CC4C4, D_800ED5B0, FS_BUFFER_14);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, &D_800CC4CC, D_800ED5B0, FS_BUFFER_14);
        Dms_CharacterGetPosRot(&lightIntPos, &unused, &D_800CC4D4, D_800ED5B0, FS_BUFFER_14);

        // Set light rotation.
        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy =  ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = FP_ANGLE(0.0f);

        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "ARSIA", D_800ED5B0, FS_BUFFER_14);

        if (D_800EBB60 != 0)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "DARIA", D_800ED5B0, FS_BUFFER_14);
        }

        if (D_800EBB61 == 3)
        {
            Dms_CharacterGetPosRot(&g_WorldObject_SFlauros.position_1C, &g_WorldObject_SFlauros.rotation_28, "SFLAU", D_800ED5B0, FS_BUFFER_14);
        }
        else if (D_800EBB61 == 1)
        {
            Dms_CharacterGetPosRot(&g_WorldObject_SFlauros.position_1C, &g_WorldObject_SFlauros.rotation_28, "SFLAU", D_800ED5B0, FS_BUFFER_14);
            Savegame_EventFlagSet(EventFlag_454);
        }
        else
        {
            Savegame_EventFlagClear(EventFlag_454);
        }

        if (D_800EBB61 == 2)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "BFLAU", D_800ED5B0, FS_BUFFER_14);
        }
    }

    if (g_SysWork.sysStateStep_C[0] >= 48)
    {
        func_800E0FAC(D_800ED5B0);
    }
}

void func_800E558C(void) // 0x800E558C
{
    typedef struct
    {
        SPRT*     sprt_0;
        DR_TPAGE* tpage_4;
        DR_STP*   stp_8;
        u8        unk_C[4];
        u8        unk_10[4];
        s32       activeBufferIdx_14;
    } g_GteScratchData_func_800DD2D4;

    g_GteScratchData_func_800DD2D4* scratchData;
    s32                             i;

    scratchData = PSX_SCRATCH_ADDR(0);

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 6)
    {
        SysWork_StateStepSet(0, 6);
    }

    D_800ED5F0 += Q12_MULT_PRECISE(g_DeltaTime0, 64);
    if (D_800ED5F0 >= 128)
    {
        D_800ED5F0 = 128;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Savegame_EventFlagSet(EventFlag_453);

            Fs_QueueStartRead(FILE_ANIM_HBM6_S4C_ANM, FS_BUFFER_4);
            Fs_QueueStartRead(FILE_ANIM_LOOKAR_DMS, FS_BUFFER_14);
            Fs_QueueWaitForEmpty();

            DmsHeader_FixOffsets(FS_BUFFER_14);
            ScreenFade_ResetTimestep();

            g_SysWork.field_30    = 20;
            D_800ED5B0            = NO_VALUE;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Anim_CharaTypeAnimInfoClear();
            Chara_Load(0, Chara_Alessa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);

            D_800ED5AD = 2;

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 53, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            SysWork_StateStepIncrement(0);

        case 2:
            g_DeltaTime0 = Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.65f);
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(0.0f), Q12(22.0f), true, true);
            break;

        case 3:
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Alessa, 0, g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(1.0f), g_SysWork.playerWork_4C.player_0.position_18.vz, FP_ANGLE(11.3f), 3);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 70, false);

            g_SysWork.pointLightIntensity_2378 = Q12(2.5f);

            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(3.5f), Q12(23.0f), Q12(33.0f), true, true);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 7:
            if (g_SysWork.npcs_1A0[0].model_0.charaId_0 != Chara_Alessa)
            {
                Chara_ProcessLoads();
                Chara_Spawn(Chara_Alessa, 0, g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(1.0f), g_SysWork.playerWork_4C.player_0.position_18.vz, FP_ANGLE(11.3f), 3);
            }

            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_468);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            D_800ED5F0 = 0;
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 4)
    {
        scratchData->activeBufferIdx_14 = g_ActiveBufferIdx;
        scratchData->sprt_0             = (SPRT*)GsOUT_PACKET_P;
        for (i = 0; i < 2; i++)
        {
            setCodeWord(scratchData->sprt_0, PRIM_RECT | RECT_BLEND | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
            setXY0Fast(scratchData->sprt_0, ((i << 8) - 160), -112);
            scratchData->sprt_0->u0 = 0;
            scratchData->sprt_0->v0 = (scratchData->activeBufferIdx_14 == 0) ? 32 : 0;
            setWH(scratchData->sprt_0, (i == 0) ? 256 : 64, 224);
            addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->sprt_0, 4);

            scratchData->sprt_0++;
            scratchData->tpage_4 = (DR_TPAGE*)scratchData->sprt_0;
            setDrawTPage(scratchData->tpage_4, 0, 0, getTPageFromBuffer(2, 0, scratchData->activeBufferIdx_14, i));

            AddPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->tpage_4);
            scratchData->tpage_4++;
            scratchData->sprt_0 = (SPRT*)scratchData->tpage_4;
        }

        scratchData->stp_8 = (DR_STP*)scratchData->sprt_0;
        SetDrawStp(scratchData->stp_8, 1);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratchData->stp_8);
        scratchData->stp_8++;
        SetDrawStp(scratchData->stp_8, 0);
        addPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[0], scratchData->stp_8);
        scratchData->stp_8++;
        GsOUT_PACKET_P = (PACKET*)scratchData->stp_8;
    }

    if (D_800ED5B0 >= 0)
    {
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);

        if (g_SysWork.sysStateStep_C[0] >= 4)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "ARSIA", D_800ED5B0, FS_BUFFER_14);
            Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, D_800CC4C4, D_800ED5B0, FS_BUFFER_14);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy += FP_ANGLE(22.5f);
        }
        else
        {
            Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, D_800CC4C4, D_800ED5B0, FS_BUFFER_14);
        }
    }
}

void func_800E5D44(void) // 0x800E5D44
{
    D_800ED841 = 0;
    D_800ED5F0 = 0;
    D_800ED840 = 0;
    D_800ED5AD = 0;
    D_800ED5B4 = 0;
    D_800ED5B8 = 0;
    D_800ED740.vx = Q12(20.0f);
    D_800ED740.vy = Q12(0.0f);
    D_800ED740.vz = Q12(100.0f);
    D_800ED5B6 = 0;

    WorldObject_ModelNameSet(&g_WorldObject0[0], "UMA1_HID");
    WorldObject_ModelNameSet(&g_WorldObject0[1], "UMA2_HID");
    WorldObject_ModelNameSet(&g_WorldObject1[0], "MGR_KOYA");
    WorldObject_ModelNameSet(&g_WorldObject1[1], "MGR_STR_");
    WorldObject_ModelNameSet(&g_WorldObject1[2], "SAKU2_BA");
    WorldObject_ModelNameSet(&g_WorldObject2,    "SAK_POL_");
    WorldObject_ModelNameSet(&g_WorldObject3,    "ROT_POL2");
    WorldObject_ModelNameSet(&g_WorldObject4[0], "MGR_DRL_");
    WorldObject_ModelNameSet(&g_WorldObject4[1], "DRL2_ILI");
    WorldObject_ModelNameSet(&g_WorldObject5,    "CHAIR_HI");
    WorldObject_ModelNameSet(&g_WorldObject6[0], "FW1_BACK");
    WorldObject_ModelNameSet(&g_WorldObject6[1], "FW2_BACK");
    WorldObject_ModelNameSet(&g_WorldObject6[2], "FW3WIR_H");
    WorldObject_ModelNameSet(&g_WorldObject7[0], "FWBOX1_B");
    WorldObject_ModelNameSet(&g_WorldObject7[1], "FWBOX2_B");
    WorldObject_ModelNameSet(&g_WorldObject8,    "WHEEL_BA");

    WorldObjectInit(&g_WorldObject9, D_800A99E4.savePadName_4, -13.6f, -1.0f, -28.3f, 0.0f, -165.0f, 0.0f);
    func_800E02E0();
    func_800E10F8();

    g_SysWork.npcId_2280 = 3;
}

// rodata at the bottom of this file. TODO: Inline once all users are decomped.
extern VECTOR3 D_800CC7C0;
extern VECTOR3 D_800CC7CC;

void func_800E5F54(void) // 0x800E5F54
{
    s32 cellZ0;
    s32 cellX0;
    s32 projCellZ0;
    s32 projCellX0;
    u16 flags;

    flags = 0;

    if (!Savegame_EventFlagGet(EventFlag_466))
    {
        Savegame_EventFlagSet(EventFlag_466);
        func_8003A16C();
    }

    cellZ0 = g_SysWork.playerWork_4C.player_0.position_18.vz / CHUNK_CELL_SIZE;
    cellX0 = g_SysWork.playerWork_4C.player_0.position_18.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(0.0f))
    {
        projCellX0 = cellX0 + 17;
    }
    else
    {
        projCellX0 = cellX0 + 15;
    }

    if (g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(0.0f))
    {
        projCellZ0 = cellZ0 + 17;
    }
    else
    {
        projCellZ0 = cellZ0 + 15;
    }

    switch (PACKED_CELL_XZ(projCellX0, projCellZ0))
    {
        case PACKED_CELL_XZ(17, 19):
            func_800E636C();

            if (Savegame_EventFlagGet(EventFlag_443))
            {
                flags = 1 << 1;

                if (g_SysWork.sysState_8 != SysState_EventCallFunc)
                {
                    func_800E15FC(&g_SysWork.playerWork_4C, &g_SysWork.npcs_1A0[0], false);
                }
            }

            if (D_800ED840)
            {
                Sd_SfxStop(Sfx_Unk1616);
                Sd_SfxStop(Sfx_Unk1615);
                D_800ED840 = 0;
            }
            break;

        case PACKED_CELL_XZ(15, 15):
            WorldGfx_ObjectAdd(&g_WorldObject9.object_0, &g_WorldObject9.position_1C, &g_WorldObject9.rotation_28);

        default:
            if (!Savegame_EventFlagGet(EventFlag_452) &&
                PLAYER_NEAR_POS(vx, 8.0f, 20.0f) && PLAYER_NEAR_POS(vz, -28.0f, 22.0f) &&
                Vw_AabbVisibleInScreenCheck(Q12(7.0f), Q12(11.0f), Q12(-14.0f), Q12(0.0f), Q12(-36.0f), Q12(-20.0f)))
            {
                func_800E6CB8();
            }
            else if (!Savegame_EventFlagGet(EventFlag_453))
            {
                if (PLAYER_NEAR_POS(vx, -16.0f, 20.0f) && PLAYER_NEAR_POS(vz, -64.0f, 20.0f))
                {
                    if (Vw_AabbVisibleInScreenCheck(Q12(-22.0f), Q12(-9.0f), Q12(-8.0f), Q12(0.0f), Q12(-69.0f), Q12(-58.0f)))
                    {
                        func_800E7204();
                    }
                }
            }

            if (Savegame_EventFlagGet(EventFlag_454))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_SFlauros.object_0, &g_WorldObject_SFlauros.position_1C, &g_WorldObject_SFlauros.rotation_28);
            }

            if (!D_800ED840)
            {
                SD_Call(Sfx_Unk1616);
                SD_Call(Sfx_Unk1615);
                D_800ED840++;
            }

            func_800E75B8(Sfx_Unk1616, &D_800CC7C0, D_800ED5F0, Q12(32.0f), D_800ED5AD);
            func_8005DE0C(Sfx_Unk1615, &D_800CC7CC, Q8(0.5f), Q12(32.0f), 0);
    }

    func_80069844(0xFFFF);
    func_8006982C(flags);
    func_800E0204();
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E636C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E6CB8);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E7204);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E73B4);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E74C4);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E75B8);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04_2", func_800E7944);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC7C0);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC7CC);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04_2", D_800CC7D8);

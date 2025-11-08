#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s04.h"
#include "maps/characters/Chara_Alessa.h"
#include "maps/characters/Chara_Dahlia.h"

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

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.alpha_A = Q12(0.0f);
        chara->model_0.state_2        = 1;
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

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.alpha_A = Q12(0.0f);
        chara->model_0.state_2        = 1;
        chara->model_0.stateStep_3    = 0;
        Character_AnimSet(chara, ANIM_STATUS(1, true), 0);
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &PARASITE_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}

void func_800DE26C() {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE274);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE350);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE380);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE5CC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE62C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE658);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE8F0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE95C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEA4C);

void func_800DEA94(s32* arg0) // 0x800DEA94
{
    if (arg0 != NULL)
    {
        *arg0 = 0;
    }
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEAA8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEB1C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEC3C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DED30);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DED50);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEDEC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEF50);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF134);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF160);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF2F0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF41C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF5B0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF618);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF64C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF670);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF6C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFA38);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFB44);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFBB0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFC94);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFD08);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFD3C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E00F4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0164);

void func_800E01F4(void) // 0x800E01F4
{
    D_800ED588 = 6;
}

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CB69C);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CB6AC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0204);

void func_800E02E0(void) // 0x800E02E0
{
    D_800ED588 = 0;
    func_800DE26C();
    func_800DF64C();
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E030C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0358);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E03C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E05C8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E068C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0878);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E08B8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0BB0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0C58);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0CCC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0D8C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0DC4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0F28);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0FAC);

void func_800E10F8(void) // 0x800E10F8
{
    D_800ED58C = 0;
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E1104

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E1114);

void func_800E1258(s32 arg0) // 0x800E1258
{
    (arg0 == 1) ? func_800E1290() : func_800E12D0();
}

void func_800E1290(void) // 0x800E1290
{
    func_8003640C(Savegame_EventFlagGet(EventFlag_440) ? 39 : 37);
}

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CB728);

void func_800E12D0(void)
{
    s32 dist0;
    s32 flags;
    s32 fArg1;
    s32 soundCmd;
    s32 distance;
    u8* dataPtr;
    s8 roomIdx;

    fArg1 = Q12(0.2f);
    soundCmd = g_GameWork.soundCmd_5B2;
    if (soundCmd == 36)
    {
        dataPtr = &D_800EB738;
        fArg1 = Q12(0.1f);
        if (Savegame_EventFlagGet(EventFlag_465))
        {
            flags = 0x20;
        }
        else if (!Savegame_EventFlagGet(EventFlag_464))
        {
            fArg1 = Q12(240.0f);
            flags = 2;
        }
        else
        {
            flags = 0x10;
        }
    }
    else if (soundCmd== 39)
    {
        dataPtr = D_800EB740;
        if (Savegame_EventFlagGet(EventFlag_445))
        {
            if (Savegame_EventFlagGet(EventFlag_448))
            {
                flags = 0x100;
                if (Savegame_EventFlagGet(EventFlag_462))
                {
                    flags = 0x110;
                }
            }
            else if (Savegame_EventFlagGet(EventFlag_470))
            {
                D_800EB740[1] = 0x80;
                fArg1 = Q12(0.5f);
                if (!Savegame_EventFlagGet(EventFlag_447))
                {
                    flags = 0x102;
                    if (Savegame_EventFlagGet(EventFlag_463))
                    {
                        flags = 0x101;
                    }
                }
                else
                {
                    fArg1 = Q12(240.0f);
                    flags = 0x101;
                }
            }
            else if (Savegame_EventFlagGet(EventFlag_446))
            {
                D_800EB740[1] = 0;
                fArg1 = Q12(240.0f);
                flags = 0x101;
            } 
            else 
            {
                D_800EB740[1] = 0x60;
                flags = 0x10A;
            }
        }
        else
        {
            D_800EB740[1] = 0x60;
            if (Savegame_EventFlagGet(EventFlag_443))
            {
                flags = 0x108;
                if (!Savegame_EventFlagGet(EventFlag_444))
                {
                    if (Savegame_EventFlagGet(EventFlag_455))
                    {
                        flags = 0x10A;
                    }
                } 
                else 
                {
                    flags = 0x10A;
                }
            } 
            else 
            {
                fArg1 = Q12(240.0f);
                flags = 0x301;
                if (Savegame_EventFlagGet(EventFlag_461))
                {
                    flags = 0x104;
                }
            }
        }
    } 
    else 
    {
        distance = 0;
        dataPtr = &D_800EB748;
        roomIdx = g_SavegamePtr->mapRoomIdx_A5 - 1;
        switch (roomIdx)
        {
            case 2:
                flags = 4;
                distance = Math_Distance2dGet(&g_SysWork.player_4C.chara_0.position_18, &D_800EB750);
                if (distance < Q12(10.0f))
                {
                    distance = Q12(0.03125f);
                } 
                else 
                {
                    distance = Q12(0.03125f) - FP_MULTIPLY_PRECISE(distance - Q12(10.0f), Q12(0.004f), Q12_SHIFT);
                    if (distance < 0) 
                    {
                        distance = 0;
                    }
                }
                break;
            case 0:
            case 1:
            case 3:
            case 4:
                flags = 2;
                break;
            default:
                flags = 1;
                break;
        }
        D_800EB74A = distance;
    }
    func_80035F4C(flags, fArg1, dataPtr);
}

void func_800E155C() {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800E1564

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E15FC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E1CA0);

void func_800E1D48() {}

void func_800E1D50(void) // 0x800E1D50
{
    #define STATE_SKIP 3

    VECTOR3  lintPos;
    SVECTOR3 lintRot;
    q19_12   rotX;
    q19_12   rotZ;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < STATE_SKIP)
    {
        SysWork_StateStepSet(0, STATE_SKIP);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            D_800ED5AC = 0;
            D_800ED5B0 = 0;
            g_SysWork.flags_22A4 |= 1 << 4;

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
            g_SysWork.field_2378 = Q12(1.0f);

            func_800348C0();
            Chara_Load(0, Chara_MonsterCybil, g_SysWork.npcCoords_FC0, -1, NULL, NULL);

            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= 1 << 3;

            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 113, false);
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

            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            func_80088D0C();
            Chara_Spawn(Chara_MonsterCybil, 0, Q12(26.5f), Q12(108.5f), Q12(0.03125f), 3);
            func_800E15FC(&g_SysWork.player_4C.chara_0, &g_SysWork.npcs_1A0[0], 1);
            Savegame_EventFlagSet(EventFlag_441);
            break;
    }

    if (D_800ED5B0 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC4C4, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.field_2360, &lintRot, &D_800CC4CC, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        Dms_CharacterGetPosRot(&lintPos, &lintRot, &D_800CC4D4, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);

        rotX = Q12_TO_Q6(lintPos.vx - g_SysWork.field_2360.vx);
        rotZ = Q12_TO_Q6(lintPos.vz - g_SysWork.field_2360.vz);

        g_SysWork.field_2370.vx = -ratan2(lintPos.vy - g_SysWork.field_2360.vy, Q6_TO_Q12(SquareRoot0(SQUARE(rotX) + SQUARE(rotZ))));
        g_SysWork.field_2370.vy = ratan2(lintPos.vx - g_SysWork.field_2360.vx, lintPos.vz - g_SysWork.field_2360.vz);
        g_SysWork.field_2370.vz = FP_ANGLE(0.0f);
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

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC424);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4A4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4C4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4CC);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4D4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC4DC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E219C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E2724);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E2950);

void func_800E2CA0(void) // 0x800E2CA0
{
    // TODO: rodata used in a bunch of funcs, can't be inserted properly until they're all decomped.
    extern s8 D_800CC4C4; // "HERO"
    extern s8 D_800CC4CC; // "LIGHT"
    extern s8 D_800CC4D4; // "L_INT"
    extern s8 D_800CC4DC; // "MSB"

    VECTOR3         lightIntPos;
    SVECTOR3        unused;
    s_SubCharacter* player;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 && g_SysWork.sysStateStep_C[0] == 7)
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
            func_8004690C(Sfx_Unk1617);
            sharedFunc_800D20E4_0_s00();

            g_SysWork.npcs_1A0[0].health_B0 = NO_VALUE;

            D_800ED5AC           = 0;
            D_800ED5B0           = Q12(96.0f);
            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.field_2378 = Q12(1.0f);

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
            Sd_EngineCmd(16);
            Sd_EngineCmd(19);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 162, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(96.0f), Q12(131.0f), false, false);

            // Possible inline?
            player = &g_SysWork.player_4C.chara_0;
            if (player->model_0.anim_4.keyframeIdx_8 > 1282)
            {
                func_80085EB8(2, player, 0, false);
            }

            SysWork_StateStepIncrement(0);

        case 5:
            // Possible inline?
            player = &g_SysWork.player_4C.chara_0;
            if (player->model_0.anim_4.keyframeIdx_8 > 1282)
            {
                func_80085EB8(2, player, 0, false);
            }

            SysWork_StateStepIncrement(0);

        case 6:
            func_80085EB8(3, &g_SysWork.player_4C.chara_0, 0, false);
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
            sharedFunc_800D2244_0_s00(false);

            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_447);
            Savegame_EventFlagSet(EventFlag_450);

            vcReturnPreAutoCamWork(true);
            func_8008D448();
            func_8003EBA0();
            g_SysWork.field_2378 = Q12(1.0f);
            Sd_EngineCmd(19);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            break;
    }

    if (D_800ED5B0 > Q12(96.0f))
    {
        // Get "HERO" position.
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC4C4, D_800ED5B0, FS_BUFFER_14);

        // Get "MSB" position
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, &D_800CC4DC, D_800ED5B0, FS_BUFFER_14);

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);

        // "LIGHT", cutscene light position? (TODO: rename g_SysWork.field_2360?)
        Dms_CharacterGetPosRot(&g_SysWork.field_2360, &unused, &D_800CC4CC, D_800ED5B0, FS_BUFFER_14);

        // "L_INT", interior light or intersection point?
        Dms_CharacterGetPosRot(&lightIntPos, &unused, &D_800CC4D4, D_800ED5B0, FS_BUFFER_14);

        // Light angle? (TODO: rename g_SysWork.field_2370?)
        g_SysWork.field_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.field_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.field_2360.vx, lightIntPos.vz - g_SysWork.field_2360.vz));
        g_SysWork.field_2370.vy = ratan2(lightIntPos.vx - g_SysWork.field_2360.vx, lightIntPos.vz - g_SysWork.field_2360.vz);
        g_SysWork.field_2370.vz = 0;
    }
}

void func_800E3244(void) // 0x800E3244
{
    #define STATE_SKIP 28

    VECTOR3  lintPos;
    SVECTOR3 lintRot;
    q19_12   posX;
    q19_12   lookAtX;
    q19_12   rotX;
    q19_12   rotZ;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] >= 2)
        {
            if (g_SysWork.sysStateStep_C[0] < 27 &&
                g_SysWork.sysStateStep_C[0] != 20 &&
                g_SysWork.sysStateStep_C[0] != 22)
            {
                SysWork_StateStepSet(0, STATE_SKIP);
            }
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            D_800EBA30 = 0;
            D_800ED5B6 = 0;

            func_8004690C(Sfx_Unk1617);
            sharedFunc_800D20E4_0_s00();
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
            g_SysWork.field_2378 = Q12(0.5f);

            Chara_Load(1, Chara_Parasite, &g_SysWork.npcCoords_FC0[30], 0, NULL, NULL);

            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= 1 << 3;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            WorldGfx_PlayerHeldItemSet(InventoryItemId_CutscenePlasticBottle);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);
            
        case 1:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 170, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(0.0f), Q12(24.0f), false, true);
            func_800E73B4(D_800ED5B0);
            break;

        case 3:
            SysWork_StateStepIncrement(0);

        case 4:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 185, false);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(25.0f), Q12(58.0f), false, true);
            break;

        case 6:
            D_800ED5B0 = Q12(59.0f);

            func_80088D0C();
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 160, false);
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
            Sd_EngineCmd(19);

            D_800ED5B0 = Q12(186.0f);

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 163, false);
            func_800E7944(3);
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(5.0f), Q12(186.0f), Q12(193.0f), false, true);
            func_8005DE0C(Sfx_Unk1624, &g_SysWork.npcs_1A0[1].position_18, 32, Q12(16.0f), 0);
            break;

        case 12:
            D_800ED5B0 = Q12(195.0f);

            ModelAnim_StatusIncrement(&g_SysWork.npcs_1A0[1].model_0.anim_4);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 151, false);
            SysWork_StateStepIncrement(0);

        case 13:
            if (D_800ED5B0 < Q12(202.0f))
            {
                func_8005DE0C(Sfx_Unk1624, &g_SysWork.npcs_1A0[1].position_18, 32, Q12(16.0f), 0);
            }
            else
            {
                func_8004690C(Sfx_Unk1624);
            }

            SysWork_StateStepIncrementAfterTime(&D_800ED5B0, Q12(10.0f), Q12(195.0f), Q12(213.0f), false, true);
            break;

        case 14:
            D_800ED5B0 = Q12(216.0f);

            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 161, false);
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

            Model_AnimFlagsClear(&g_SysWork.player_4C.chara_0.model_0, (1<<1));
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            D_800ED5B0 = NO_VALUE;

            func_8008D438();

            g_SysWork.field_2378 = 0x5C0;
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
            Sd_EngineCmd(19);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.8f), false);
            break;

        case STATE_SKIP:
            Sd_EngineCmd(19);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            func_800E7944(3);

            D_800ED5B0 = NO_VALUE;

            sharedFunc_800D2EF4_0_s00();
            func_8003CD6C(&g_SysWork.playerCombatInfo_38);
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);

            sharedFunc_800D88C0_0_s00(&g_SysWork.npcs_1A0[0], false);
            vcReturnPreAutoCamWork(true);
            func_8008D448();
            func_8003EBA0();

            g_SysWork.field_2378 = Q12(1.0f);
            g_SavegamePtr->eventFlags_168[14] |= 0x6;

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);

            func_8004690C(Sfx_Unk1625);
            func_8004690C(Sfx_Unk1624);
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, (1<<1));
            break;
    }
    
    if (g_SysWork.sysStateStep_C[0] >= 22 && g_SysWork.sysStateStep_C[0] <= 27)
    {
        posX = FP_FROM(Math_Sin(D_800ED5B6) * Q12(5.2f), Q12_SHIFT) + Q12(20.0f);
        Camera_PositionSet(NULL, posX, Q12(-2.0f), FP_FROM(Math_Cos(D_800ED5B6) * Q12(5.2f), Q12_SHIFT) + Q12(100.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

        lookAtX = FP_FROM(Math_Sin(D_800ED5B6 - Q12(0.172f)) * Q12(3.7f), Q12_SHIFT) + Q12(20.0f);
        Camera_LookAtSet(NULL, lookAtX, -Q12(1.0f), FP_FROM(Math_Cos(D_800ED5B6 - 704) * Q12(3.7f), Q12_SHIFT) + Q12(100.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

        Math_Vector3Set(&g_SysWork.field_2360, FP_FROM(Math_Sin(D_800ED5B6 - Q12(0.2188f)) * Q12(4.8f), Q12_SHIFT) + Q12(20.0f),
                                              -Q12(1.0f),
                                               FP_FROM(Math_Cos(D_800ED5B6 - Q12(0.2188f)) * Q12(4.8f), Q12_SHIFT) + Q12(100.0f)
        );

        Math_SetSVectorFast(&g_SysWork.field_2370, FP_ANGLE(-39.4f), (D_800ED5B6 + FP_ANGLE(182.9f)), FP_ANGLE(0.0f));
        func_800E74C4();
    }

    if (D_800ED5B0 > Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC4C4, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, &D_800CC4DC, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "ICU", D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800ED590, &D_800ED5A0, NULL, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14));
        vcUserCamTarget(&D_800ED590, NULL, true);
        vcUserWatchTarget(&D_800ED5A0, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.field_2360, &lintRot, &D_800CC4CC, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);
        Dms_CharacterGetPosRot(&lintPos, &lintRot, &D_800CC4D4, D_800ED5B0, (s_DmsHeader*)FS_BUFFER_14);

        rotX = Q12_TO_Q6(lintPos.vx - g_SysWork.field_2360.vx);
        rotZ = Q12_TO_Q6(lintPos.vz - g_SysWork.field_2360.vz);

        g_SysWork.field_2370.vx = -ratan2(lintPos.vy - g_SysWork.field_2360.vy, Q6_TO_Q12(SquareRoot0(SQUARE(rotX) + SQUARE(rotZ))));
        g_SysWork.field_2370.vy = ratan2(lintPos.vx - g_SysWork.field_2360.vx, lintPos.vz - g_SysWork.field_2360.vz);
        g_SysWork.field_2370.vz = FP_ANGLE(0.0f);
    }
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E3EF4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC5B0);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC5B8);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC5C0);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC5C8);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", jtbl_800CC5D0); // TODO: Why is this here?

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E558C);

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

    WorldObjectPoseInit(&g_WorldObject9.position_1C, -13.6f, -1.0f, -28.3f, 0.0f, -165.0f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject9.object_0, D_800A99E4.savePadName_4);
    func_800E02E0();
    func_800E10F8();

    g_SysWork.field_2280 = 3;
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E5F54);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E636C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E6CB8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E7204);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E73B4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E74C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E75B8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E7944);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC7C0);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC7CC);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04_2", D_800CC7D8);

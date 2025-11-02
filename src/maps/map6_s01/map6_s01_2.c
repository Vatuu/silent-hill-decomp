#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s01.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D0358

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D036C

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D03B0

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D03C8

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D03D4

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D03E8

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D03FC

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D0410

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D04C8

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D0B2C

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D0B40

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D0B54

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D0C50

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D0D34

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D0D70

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D0DD0

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D0DE0

void func_800D0E78(s32 arg0) // 0x800D0E78
{
    if (arg0 != 0)
    {
        func_800D0EAC();
    }
    else
    {
        sharedFunc_800CE934_0_s02();
    }
}

void func_800D0EAC(void) // 0x800D0EAC
{
    if (!Savegame_EventFlagGet(EventFlag_424) || (Savegame_EventFlagGet(EventFlag_425) && !Savegame_EventFlagGet(EventFlag_426)))
    {
        func_8003640C(23);
    }
    else
    {
        func_8003640C(20);
    }
}

#include "maps/shared/sharedFunc_800CE934_0_s02.h" // 0x800D0EF8

void func_800D1184(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D118C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D1220

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.0)\tCybil! ~E ",
    "~J1(1.1)\tHarry! ",
    "~J1(1.6)\tHow_did_you_get_back_here?  ",
    "~J1(1.6)\tI_followed_the_sewer. ",
    "~J1(1.9)\tWere_you_the_one ~N\n\t\t\twho_cut_the_fence? ",
    "~J1(1.0)\tYeah. ",
    "~J1(3.0)\tI'm_glad_you_made_it. ~N\n\t\t\tI_was_worried_about_you. ~E ",
    "~J1(3.6)\tYou_were_worried!? ~N\n\t\t\tWhere_did_you_disappear_to? ",
    "~J1(1.0)\tNever_mind. ",
    "~J1(2.1)\tI_want_to_know ~N\n\t\t\twhat's_going_on_here. ",
    "~J1(2.4)\tWhat_is_with_this_town?  ~E ",
    "~J1(3.5)\tThis_may_sound_really_off ~N\n\t\t\tthe_wall,_but_listen_to_me. ",
    "~J1(1.8)\tYou've_got_to_believe_me. ",
    "~J1(3.2)\tI_haven't_gone_crazy, ~N\n\t\t\tand_I'm_not_fooling_around. ~E ",
    "~J1(3.7)\tAt_first,_I_thought_I_was ~N\n\t\t\tlosing_my_mind. ",
    "~J1(2.3)\tBut_now_I_know_I'm_not. ",
    "~J1(3.0)\tIt's_not_me. ~N\n\t\t\tThis_whole_town... ",
    "~J1(2.5)\tit's_being_invaded ~N\n\t\t\tby_the_Otherworld. ",
    "~J1(4.0)\tBy_a_world_of_someone's ~N\n\t\t\tnightmarish_delusions ~N\n\t\t\tcome_to_life... ",
    "~J1(2.9)\tLittle_by_little ~N\n\t\t\tthe_invasion_is_spreading... ",
    "~J1(2.8)\tTrying_to_swallow_up ~N\n\t\t\teverything_in_darkness. ",
    "~J1(4.2)\tI_think_I'm_finally_beginning ~N\n\t\t\tto_understand_what_that_lady ~N\n\t\t\twas_talking_about. ~E ",
    "~J1(4.6)\tHarry. ~N\n\t\t\tHold_on_a_minute. ~N\n\t\t\tI_don't_get_it? ",
    "~J1(3.1)\tLook,_I_don't_understand ~N\n\t\t\tit_all_myself. ",
    "~J1(1.8)\tI_guess_I_can't_explain_it. ",
    "~J1(2.2)\tWell,_what's_making ~N\n\t\t\tthis_happen? ",
    "~J1(1.6)\tI_don't_know_that_either. ",
    "~J1(2.8)\tBut,_I_do_know ~N\n\t\t\tCheryl_is_[there]. ",
    "~J1(1.0)\t[There]...? ",
    "~J1(3.1)\tUnder_whoever_created ~N\n\t\t\tthis_darkness. ",
    "~J1(3.2)\tCheryl_is_somewhere. ~N\n\t\t\tAnd_she_needs_my_help. ~E ",
    "~J1(1.0)\tHarry. ",
    "~J1(2.8)\tThis_whole_thing's_been ~N\n\t\t\ta_major_blow_to_you. ",
    "~J1(1.8)\tYou_need_to_rest. ",
    "~J1(1.5)\tCybil,_I... ~E ",
    "~J1(5.2)\tThe_demon_is_awakening! ~N\n\t\t\tSpreading_those_wings. ",
    "~J1(1.7)\tDahlia_Gillespie... ~E ",
    "~J1(2.9)\tWas_it_not_as_I_said? ",
    "~J1(4.4)\tI_see_it_all,_now. ~N\n\t\t\tYes,_everything. ",
    "~J1(4.9)\tHungry_for_sacrifice, ~N\n\t\t\tthe_demon_will_swallow_up ~N\n\t\t\tthe_land. ",
    "~J1(3.1)\tI_knew_this_day_would_come. ",
    "~J1(3.9)\tAnd_what's_more, ~N\n\t\t\tthe_task_is_almost_finished. ",
    "~J1(2.5)\tThere's_only_two_left. ",
    "~J1(5.3)\tTo_seal_this_town_to_the_abyss, ~N\n\t\t\tthe_mark_of_Samael. ",
    "~J1(3.6)\tWhen_it_is_completed,_all_is_lost. ",
    "~J1(4.6)\tEven_in_daytime, ~N\n\t\t\tdarkness_will_cover_the_sun. ",
    "~J1(5.8)\tThe_dead_will_walk, ~N\n\t\t\tand_martyrs_will_burn ~N\n\t\t\tin_the_fires_of_hell. ",
    "~J1(3.1)\tEveryone_will_die. ~E ",
    "~J0(3.5)\tSo_what_am_I_supposed_to_do? ~N\n\t\t\tI've_got_to_save_Cheryl. ",
    "~J1(3.6)\tIt_is_simple. ~N\n\t\t\tStop_the_demon. ",
    "~J1(4.6)\tThe_demon, ~N\n\t\t\tthe_demon_taking_that ~N\n\t\t\tchild's_form. ",
    "~J1(3.7)\tStop_it_before_your_daughter ~N\n\t\t\tbecomes_a_sacrifice. ",
    "~J1(2.6)\tBefore_it_is_too_late. ",
    "~J1(3.0)\tStop_it._Stop_it. ",
    "~J1(1.6)\tWhat_do_I_do? ",
    "~J1(3.0)\tGo_to_the_lighthouse ~N\n\t\t\ton_the_lake, ",
    "~J1(3.5)\tand_to_the_center_of ~N\n\t\t\tthe_amusement_park. ",
    "~J1(3.5)\tMake_haste. ~N\n\t\t\tYou_are_the_only_hope. ~E ",
    "~J0(1.1)\tLook_Harry. ",
    "~J0(2.1)\tI_really_don't_get ~N\n\t\t\twhat's_going_on. ",
    "~J0(4.4)\tBut_if_there's_a_chance ~N\n\t\t\twe_can_save_your_daughter, ~N\n\t\t\tI'm_in. ",
    "~J0(1.9)\tI'll_check_out ~N\n\t\t\tthe_amusement_park. ",
    "~J0(1.7)\tYou_go_to_the_lighthouse. ~E ",
    "~J0(2.5)\tCybil..._Thanks. ~E ",
    "~J0(2.1)\tYou_will_need_to_use_it. ~E ",
    "~J0(1.2)\tUse_what? ",
    "~J0(1.7)\tThe_Flauros. ",
    "~J0(3.2)\tOnly_with_that_can_you ~N\n\t\t\tstop_it. ~E ",
    "~J0(2.0)\tWhat_about_Cybil!? ~E ",
    "~J0(2.0)\tCybil_hasn't_come_back. ~E ",
    "~J0(3.5)\tThat_creep's_sure_to_show_up ~N\n\t\t\tat_the_Amusement_Park ~N\n\t\t\tpretty_soon. ",
    "~J0(2.0)\tLet_me_be_on_time. ~E ",
    "\tThere's_a_ship's_wheel. ~N\n\tDon't_worry_about_that_now, ~N\n\tthough. ~E ",
    "\tThere's_a_body_stuck ~N\n\tto_the_bulkhead. ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E "
};

void func_800D12B4(void) // 0x800D12B4
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 13:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M6S01_RifleShells;
            break;

        case 14:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M6S01_HandgunBullets;
            break;

        case 15:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S01_HealthDrink;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D1340

// TODO: Move into funcs once all have been decomped.
const static VECTOR3 D_800CB988   = { Q12(-21.3f), Q12(-1.2f), Q12(58.7f) };
const static VECTOR3 D_800CB994   = { Q12(-19.95f), Q12(-1.2f), Q12(60.7f) };

void func_800D13D8(void) // 0x800D13D8
{
    s_FsImageDesc charaTex;
    VECTOR3       pos;
    SVECTOR3      rot;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 && g_SysWork.sysStateStep_C[0] >= 3)
    {
        if (g_SysWork.sysStateStep_C[0] < 52)
        {
            SysWork_StateStepSet(0, 53);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= 1 << 3;

            Chara_Load(0, Chara_Cybil, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Fs_QueueStartRead(FILE_ANIM_SIP_DMS, FS_BUFFER_15);
            func_80088D0C();
            Chara_Spawn(Chara_Cybil, 0, Q12(-19.0f), Q12(58.0f), FP_ANGLE(0.0f), 3);

            DmsHeader_FixOffsets(FS_BUFFER_15);

            D_800D4070 = 0;
            D_800D5370 = 0;
            D_800D416C = 1;
            D_800D416D = 0;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.field_2378 = Q12(0.6f);

            func_8003ED74(16, 16);
            func_8008D438();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 113, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 14, false);
            SysWork_StateStepIncrement(0);

        case 3:
            Map_MessageWithAudio(15, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(9.5f), Q12(0.0f), Q12(21.0f), true, false);
            break;

        case 4:
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(9.5f), Q12(0.0f), Q12(21.0f), true, true);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            D_800D4070 = Q12(22.0f);
            SysWork_StateStepIncrement(0);

        case 6:
            Map_MessageWithAudio(16, &D_800D5370, &D_800D4074);
            break;

        case 7:
            Map_MessageWithAudio(22, &D_800D5370, &D_800D4074);
            break;

        case 8:
            D_800D4070 = Q12(23.0f);
            Map_MessageWithAudio(26, &D_800D5370, &D_800D4074);
            break;

        case 9:
            Map_MessageWithAudio(29, &D_800D5370, &D_800D4074);
            break;

        case 10:
            D_800D4070 = Q12(24.0f);
            Map_MessageWithAudio(37, &D_800D5370, &D_800D4074);
            break;

        case 11:
            Chara_FsImageCalc(&charaTex, Chara_Dahlia, 2);
            Chara_Load(1, Chara_Dahlia, &g_SysWork.npcCoords_FC0[30], 0, (s_LmHeader*)0x8019E600, &charaTex);
            SysWork_StateStepIncrement(0);

        case 12:
            if (Fs_QueueDoThingWhenEmpty() != false)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 13:
            func_80088D0C();
            SysWork_StateStepIncrement(0);

        case 14:
            Map_MessageWithAudio(46, &D_800D5370, &D_800D4074);
            break;

        case 15:
            func_8005DC1C(Sfx_Unk1604, &D_800CB988, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 16:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 17:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 70, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 17, false);
            func_8005DC1C(Sfx_Unk1605, &D_800CB988, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(25.0f), Q12(34.0f), true, true);
            break;

        case 19:
            Chara_Spawn(Chara_Dahlia, 0, Q12(-19.0f), Q12(58.0f), FP_ANGLE(0.0f), 3);

            D_800D416D = 1;

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 5, false);
            Savegame_EventFlagSet(EventFlag_427);

            D_800D4070 = Q12(35.0f);

            SysWork_StateStepIncrement(0);

        case 20:
            Map_MessageWithAudio(50, &D_800D5370, &D_800D4074);
            break;

        case 21:
            D_800D4070 = Q12(36.0f);
            Map_MessageWithAudio(52, &D_800D5370, &D_800D4074);
            break;

        case 22:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 113, false);
            SysWork_StateStepIncrement(0);

        case 23:
            Map_MessageWithAudio(63, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(37.0f), Q12(49.0f), true, false);
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 24:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 131, false);
            SysWork_StateStepIncrement(0);

        case 25:
            Map_MessageWithAudio(63, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(37.0f), Q12(49.0f), true, false);
            break;

        case 26:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 16, false);

            D_800D4070 = Q12(50.0f);
            D_800D5345 = 1;

            Model_AnimFlagsClear(&g_SysWork.npcs_1A0[1].model_0, 2);
            SysWork_StateStepIncrement(0);

        case 27:
            Map_MessageWithAudio(73, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 28:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 71, false);
            SysWork_StateStepIncrement(0);

        case 29:
            Map_MessageWithAudio(73, &D_800D5370, &D_800D4074);
            break;

        case 30:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 13, false);

            D_800D5345 = 0;

            Model_AnimFlagsSet(&g_SysWork.npcs_1A0[1].model_0, 2);
            SysWork_StateStepIncrement(0);

        case 31:
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(6.0f), Q12(51.0f), Q12(60.0f), true, true);
            break;

        case 32:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            SysWork_StateStepIncrement(0);

        case 33:
            Map_MessageWithAudio(78, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(6.0f), Q12(61.0f), Q12(97.0f), true, false);
            break;

        case 34:
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(6.0f), Q12(61.0f), Q12(97.0f), true, true);
            break;

        case 35:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_8005DC1C(Sfx_Unk1609, &D_800CB994, Q8_CLAMPED(0.5f), 0);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 113, false);
            SysWork_StateStepIncrement(0);

        case 36:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);

            if (g_SysWork.sysStateStep_C[0] != 36)
            {
                func_8005DC1C(Sfx_Unk1610, &D_800CB994, Q8_CLAMPED(0.5f), 0);
            }

        case 37:
            if (g_SysWork.sysStateStep_C[0] == 37)
            {
                func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            }

            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(98.0f), Q12(121.0f), true, false);
            break;

        case 38:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 131, false);
            SysWork_StateStepIncrement(0);

        case 39:
            Map_MessageWithAudio(79, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(98.0f), Q12(121.0f), true, false);
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 40:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 132, false);
            SysWork_StateStepIncrement(0);

        case 41:
            Map_MessageWithAudio(79, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(98.0f), Q12(121.0f), true, false);
            break;

        case 42:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 8, false);
            Model_AnimFlagsClear(&g_SysWork.player_4C.chara_0.model_0, 2);
            SysWork_StateStepIncrement(0);

        case 43:
            Map_MessageWithAudio(80, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(122.0f), Q12(142.0f), true, false);
            break;

        case 44:
            SysWork_StateStepIncrement(0);

        case 45:
            Map_MessageWithAudio(83, &D_800D5370, &D_800D4074);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(122.0f), Q12(157.0f), true, false);
            break;

        case 46:
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);
            func_8005DC1C(Sfx_Unk1604, &D_800CB988, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 47:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 48:
            func_8005DC1C(Sfx_Unk1605, &D_800CB988, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 49:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 50:
            func_80086C58(&g_SysWork.player_4C.chara_0, 71);
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, 2);
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(10.0f), Q12(158.0f), Q12(168.0f), true, false);
            break;

        case 51:
            D_800D4070 = Q12(169.0f);
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 52:
            SysWork_StateStepIncrement(0);
            break;

        case 53:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 54:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);

            D_800D4070 = Q12(169.0f);

            SysWork_StateStepIncrement(0);

            D_800D5345 = 0;
            break;

        default:
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_TurnFlashlightOn();
            func_8003ED74(7, 4);
            func_8008D448();
            func_8003EBA0();

            g_SysWork.field_2378 = Q12(1.0f);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);

            D_800D4070 = NO_VALUE;

            Sd_EngineCmd(19);
            Savegame_EventFlagSet(EventFlag_424);
            Savegame_MapMarkingSet(MapMarkFlag_ResortTown_LighthouseCircle);

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, 2);
            break;
    }

    if (D_800D4070 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, "HERO", D_800D4070, FS_BUFFER_15);
        if (D_800D416C != 0)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "SIBYL", D_800D4070, FS_BUFFER_15);
        }
        if (D_800D416D != 0)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "DARIA", D_800D4070, FS_BUFFER_15);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D5354, &D_800D5364, NULL, D_800D4070, FS_BUFFER_15));
        vcUserCamTarget(&D_800D5354, NULL, true);
        vcUserWatchTarget(&D_800D5364, NULL, true);

        Dms_CharacterGetPosRot(&g_SysWork.field_2360, &rot, "LIGHT", D_800D4070, FS_BUFFER_15);
        Dms_CharacterGetPosRot(&pos, &rot, "L_INT", D_800D4070, FS_BUFFER_15);

        g_SysWork.field_2370.vx = -ratan2(pos.vy - g_SysWork.field_2360.vy, Math_Vector2MagCalc(pos.vx - g_SysWork.field_2360.vx, pos.vz - g_SysWork.field_2360.vz));
        g_SysWork.field_2370.vy = ratan2(pos.vx - g_SysWork.field_2360.vx, pos.vz - g_SysWork.field_2360.vz);
        g_SysWork.field_2370.vz = 0;
    }
}

void func_800D236C(void) // 0x800D236C
{
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) && g_SysWork.sysStateStep_C[0] >= 3)
    {
        if (g_SysWork.sysStateStep_C[0] < 8)
        {
            SysWork_StateStepSet(0, 8);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            D_800D416E = 0;
            ScreenFade_ResetTimestep();
            g_SysWork.field_30 = 20;

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-20.98);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(58.67f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(90.0f);

            Camera_PositionSet(NULL, Q12(-18.7f), Q12(-5.59f), Q12(57.22f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-19.46f), Q12(-1.92f), Q12(58.62f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_8005DC1C(Sfx_Unk1604, &D_800CB988, 128, 0);

            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 2:
            func_8005DC1C(Sfx_Unk1605, &D_800CB988, 128, 0);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.5f), false);
            break;

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 5:
            Map_MessageWithAudio(84, &D_800D416E, &D_800D4100);
            break;

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);
            break;

        case 7:
            Map_MessageWithAudio(85, &D_800D416E, &D_800D4100);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            Savegame_EventFlagSet(EventFlag_426);
            Savegame_MapMarkingSet(MapMarkFlag_ResortTown_ThemeParkArrow);
            break;
    }
}

void func_800D2658(void) // 0x800D2658
{
    const static SVECTOR EMPTY_ROT = {};
    const static VECTOR3 UNK_POS   = { Q12(-23.37f), Q12(-1.25f), Q12(19.28f) };

    s32 temp_a0_4;
    s32 temp_s0;
    s32 temp_s1;
    s32 var_s4;
    s32 i;

    // @unused Maybe some removed debug print.
    temp_s0 = D_800D41B4;
    temp_s1 = temp_s0 >> 1;
    Math_Cos(temp_s1);
    Math_Sin(temp_s0 >> 4);
    Math_Sin(Math_Sin(temp_s1 * 2));

    D_800D41B4 += g_DeltaTime0;

    if (g_SysWork.sysStateStep_C[0] >= 10)
    {
        D_800D41B0 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
        if (D_800D41B0 < Q12(0.0f))
        {
            D_800D41B0 = Q12(0.0f);
        }
        func_800463C0(Sfx_Unk1467, 0, ~(D_800D41B0 >> 4), 0);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800D41B0 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
        if (D_800D41B0 > Q12(0.9961f))
        {
            D_800D41B0 = Q12(0.9961f);
        }
        func_800463C0(Sfx_Unk1467, 0, ~(D_800D41B0 >> 4), 0);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            D_800D5370 = 0;

            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800D410C);
            Fs_QueueStartRead(FILE_ANIM_UFO4_DMS, FS_BUFFER_13);
            D_800D4070 = NO_VALUE;

            ScreenFade_ResetTimestep();
            Sd_EngineCmd(Sfx_Unk1467);
            func_800463C0(Sfx_Unk1467, 0, 255, 0);

            D_800D41B0 = 0;
            D_800D41B4 = 0;

            for (i = 0; i < 5; i++)
            {
                D_800D4174[i].vx = FP_FROM(D_800D4114[i].vx * Math_Sin(FP_TO(i, Q12_SHIFT) / 5), Q12_SHIFT) - Q12(23.0f);
                D_800D4174[i].vy = FP_FROM(D_800D4114[i].vx * Math_Cos(FP_TO(i, Q12_SHIFT) / 5), Q12_SHIFT) - Q12(1.0f);
                D_800D4174[i].vz = Q12(18.0f);
            }

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            D_800D4070 = 0;

            SysWork_StateStepIncrementAfterFade(0, true, 3, Q12(0.0f), false);
            DmsHeader_FixOffsets(FS_BUFFER_13);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);

        case 5:
            Map_MessageWithAudio(89, &D_800D5370, &D_800D4108);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800D4070, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);

            for (i = 0; i < 5; i++)
            {
                sharedFunc_800CE5D4_1_s03(&D_800D4174[i], Q12(0.5f), Q12(0.05f), 0);
            }
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 90, 0, 0, 0, false);

            for (i = 0; i < 5; i++)
            {
                sharedFunc_800CE5D4_1_s03(&D_800D4174[i], Q12(0.5f), Q12(0.05f), 0);
            }
            break;

        case 8:
            func_80080B58(&g_SysWork.playerBoneCoords_890[2], &EMPTY_ROT, &UNK_POS);

            for (i = 0; i < 5; i++)
            {
                sharedFunc_800CE5D4_1_s03(&D_800D4174[i], Q12(0.5f), Q12(0.05f), i == 0);
            }

            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 9:
            if (g_SysWork.field_28 > Q12(0.8f))
            {
                var_s4 = (g_SysWork.field_28 - Q12(0.8f)) >> 2;
                if (var_s4 > Q12(0.25f))
                {
                    var_s4 = Q12(0.25f);
                }

                var_s4 = Q12(1.0f) - Math_Cos(var_s4);

                for (i = 0; i < 5; i++)
                {
                    temp_a0_4         = FP_MULTIPLY_PRECISE(var_s4, D_800D4114[i].vy, Q12_SHIFT) + D_800D4114[i].vy;
                    temp_a0_4         = FP_MULTIPLY_FLOAT_PRECISE(temp_a0_4, 1.2f, Q12_SHIFT);
                    D_800D4174[i].vx += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_MULTIPLY(temp_a0_4, Math_Sin(FP_TO(i, Q12_SHIFT) / 5), 12), Q12_SHIFT);
                    D_800D4174[i].vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_MULTIPLY(temp_a0_4, Math_Cos(FP_TO(i, Q12_SHIFT) / 5), 12), Q12_SHIFT);
                }
            }

            for (i = 0; i < 5; i++)
            {
                sharedFunc_800CE5D4_1_s03(&D_800D4174[i], Q12(0.5f), Q12(0.05f), 0);
            }

            g_SysWork.field_28 += g_DeltaTime0;
            if (g_SysWork.field_28 > Q12(1.8f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);

            Savegame_EventFlagSet(EventFlag_459);
            func_80086470(3, InventoryItemId_ChannelingStone, 1, false);

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            D_800D4070 = NO_VALUE;
            func_8004690C(Sfx_Unk1467);
            break;
    }

    if (D_800D4070 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, "HERO", D_800D4070, FS_BUFFER_13);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D5354, &D_800D5364, NULL, D_800D4070, FS_BUFFER_13));
        vcUserCamTarget(&D_800D5354, NULL, true);
        vcUserWatchTarget(&D_800D5364, NULL, true);
    }
}

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D2E6C);

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D30DC);

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01_2", D_800CBB54);

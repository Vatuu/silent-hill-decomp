#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s01.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D10C0

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D10D4

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D1118

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D1130

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D113C

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D1150

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D1164

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D1178

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D1214

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D1878

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D188C

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D18A0

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D199C

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D1A50

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D1A70

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D1AD0

#include "maps/shared/Map_RoomIdxGet.h"

void func_800D1B78(s32 arg0) // 0x800D1B78
{
    (arg0 != 0) ? sharedFunc_800CE8B8_0_s02() : sharedFunc_800CE934_0_s02();
}

#include "maps/shared/sharedFunc_800CE8B8_0_s02.h"

#include "maps/shared/sharedFunc_800CE934_0_s02.h" // 0x800D1C28

void func_800D1EB4(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D1EBC

void Event_DoorJammed(void) // 0x800D1F54
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Map_MessageWithSfx(MapMsgIdx_DoorJammed, Sfx_Unk1541, &sfxPos);
}

void func_800D1FE8(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.6)\tWhat's_this? ~E ",
    "~J0(1.0)\tHarry! ",
    "~J0(1.0)\tCybil? ~E ",
    "~J0(2.8)\tI'm_glad_you're_OK. ",
    "~J1(4.0)\tI_shouldn't_have_left_you. ~N\n\t\t\tThings_are_worse_than_I_thought. ",
    "~J1(1.4)\tIt's_nuts! ~E ",
    "~J1(3.0)\tWhat_are_you_doing_here? ~N\n\t\t\tI_thought_you_left_town. ",
    "~J1(2.8)\tI_saw_you_go_in_here, ~N\n\t\t\tso_I_followed_you. ",
    "~J1(1.8)\tI_couldn't_get_out. ",
    "~J1(2.0)\tAll_the_roads_out_of_town ~N\n\t\t\tare_blocked. ",
    "~J1(2.2)\tCars_have_completely ~N\n\t\t\tstopped_running. ",
    "~J1(2.4)\tThe_phones_and_radios ~N\n\t\t\tare_still_out,_too. ~E ",
    "~J1(2.7)\tWhat_about_my_daughter? ~N\n\t\t\tDid_you_see_her? ",
    "~J1(1.9)\tI_did_see_a_girl. ",
    "~J1(1.4)\tWas_it_Cheryl? ",
    "~J1(2.6)\tI_only_caught_a_glimpse_of_her ~N\n\t\t\tthrough_the_fog. ",
    "~J1(2.4)\tI_went_after_her, ~N\n\t\t\tbut_she_vanished. ",
    "~J1(2.7)\tI_don't_know_about ~N\n\t\t\tyour_daughter,_but... ~E ",
    "~J1(3.5)\tAnd_you_just_let_her_go!? ~N\n\t\t\tWhere_was_it? ",
    "~J1(3.4)\tOn_Bachman_Road. ~N\n\t\t\tShe_was_heading_towards_the_lake. ",
    "~J1(2.0)\tNow_don't_get_excited. ",
    "~J1(2.5)\tIt_wasn't_like_she_ran_off ~N\n\t\t\texactly. ",
    "~J1(4.8)\tThere_was_no_place_for_her_to_go. ~N\n\t\t\tThe_road_has_been_obliterated. ~E ",
    "~J1(3.0)\tWhat!? ~N\n \t\t\tSo_then_Cheryl... ",
    "~J1(3.6)\tIt_was_like_she_was_walking ~N\n\t\t\ton_thin_air. ",
    "~J1(2.0)\t~E ",
    "~J1(3.0)\tWhat_about_you?__Anything? ",
    "~J1(3.0)\tYeah... ~N\n\t\t\tI_met_this_bizarre_woman. ",
    "~J1(4.0)\tHer_name's_Dahlia_Gillespie. ~N\n\t\t\tDo_you_know_her? ",
    "~J1(1.8)\tDahlia_Gillespie? ",
    "~J1(1.0)\tNo. ",
    "~J1(1.2)\tAnd? ~E ",
    "~J1(4.0)\tShe_said_something_about ~N\n\t\t\tthe_town_being_devoured ~N\n\t\t\tby_darkness.",
    "~J1(1.8)\tGibberish_like_that. ",
    "~J1(2.0)\tAny_idea_what_it_means? ~E ",
    "~J1(2.9)\tDarkness_devouring_the_town? ",
    "~J1(1.6)\tMust_be_on_drugs. ",
    "~J1(2.0)\tThey_sell_'em_to_the_tourists. ",
    "~J1(2.8)\tThe_force_still_can't_figure_out ~N\n\t\t\twho's_behind_it. ",
    "~J1(2.2)\tNone_of_our_leads ~N\n\t\t\thave_panned_out, ",
    "~J1(2.5)\tand_the_investigation_is_stalled. ",
    "~J1(3.5)\tWhat_could_drug_trafficking ~N\n\t\t\thave_to_do_with_all_this? ",
    "~J1(3.2)\tI_really_don't_know. ",
    "~J1(3.6)\tBut,_maybe_that's_the_darkness ~N\n\t\t\tshe_was_talking_about. ",
    "~J1(1.8)\tThat's_all_I_can_think_of. ",
    "~J1(2.0)\t~E ",
    "~J1(1.2)\tWhat's_this? ",
    "~J1(1.5)\tJust_discovered_it. ",
    "~J1(1.8)\tMaybe_there's_something ~N\n\t\t\tback_there. ",
    "~J1(1.4)\tLet's_have_a_look. ",
    "~J1(1.0)\tWait. ",
    "~J1(4.0)\tWe_don't_know_what's_back_there. ~N\n\t\t\tI'd_better_check_it_out_first. ",
    "~J1(2.2)\tI'm_a_cop.__I_should_go. ",
    "~J1(3.0)\tNo.__I'm_going. ",
    "~J1(0.9)\tAlright. ",
    "~J1(1.5)\tI'll_cover_you_from_here. ",
    "~J1(1.7)\tBe_careful. ",
    "~J1(3.6)\tIf_anything_looks_fishy, ~N\n\t\t\tget_back_here_on_the_double. ~E ",
    "~J0(0.8)  \tOkay. ~E ",
    "~J0(1.0)\tCybil. ",
    "~J0(0.9)\tYes? ~E ",
    "~J1(2.2)\tDo_you_know_anything_about... ",
    "~J1(6.2)\tWell...like_some_other_world... ~N\n\t\t\tIt's_like_some_kind_of_bad_dream...? ",
    "~J1(1.9)\tWhat_are_you_talking_about? ",
    "~J1(1.7)\tI'm_not_quite_sure. ",
    "~J1(3.7)\tI_try_to_make_sense_of_it, ~N\n\t\t\tbut_then_my_mind_goes_blank. ",
    "~J1(4.0)\tEverything's_dark_there, ~N\n\t\t\tand_I_hear_sirens_in_the_distance. ",
    "~J1(2.7)\tI_met_this_nurse..._Lisa. ",
    "~J1(3.7)\tIt's_like_I_was_there, ~N\n\t\t\tbut_not_really. ",
    "~J1(4.2)\tIt's_all_a_blur. ~N\n\t\t\tLike_some_kind_of_hallucination, ~N\n\t\t\tyou_know? ",
    "~J1(3.0)\tI_have_no_idea_what ~N\n\t\t\tyou're_talking_about,_Harry. ~E ",
    "~J1(1.8)\tOh... ",
    "~J1(4.5)\tI_was_just_wondering. ~N\n\t\t\tNever_mind. ",
    "~J1(1.0)\tHarry. ",
    "~J1(2.5)\tYou're_tired. ~E ",
    "~J0(2.4)\tYeah,_maybe... ~E ",
    "~J1(4.1)\tWhat's_this...? ~N\n\t\t\tSome_kind_of_altar...? ",
    "~J1(2.6)\tNever_seen_anything ~N\n\t\t\tlike_this_before. ",
    "~J1(2.5)\tMaybe_this_is ~N\n\t\t\t[the_other_church.] ~E ",
    "\t\t\tSome_kind_of_powder ~N\n\t\t\tis_left_in_the_chalice. ~E ",
    "~J0(1.5)\t",
    "~J2(1.5)\tWhat_the...!? ~E ",
    "~J0(4.2)\tHarry? ~N\n\t\t\tAre_you_OK? ~E ",
    "~J0(1.0)\tHarry? ~E ",
    "~J0(2.3)\tHarry? ~E ",
    "\tThere_is_a_trace_on_the_floor ~N\n\tthat_somebody_moved_the_cabinet. ",
    "\tDo_you_want_to_push ~N\n\tthe_cabinet? ~S4 ",
    "~J0(2.0)\tWas_that_another_dream? ~E ",
    "~J0(2.0)\tDid_I_pass_out_again? ~E ",
    "~J0(2.0)\tI_don't_want_to_think_so, ",
    "~J0(3.0)\tbut_maybe_this_is_all_just ~N\n\t\t\tgoing_on_in_my_head. ",
    "~J0(4.0)\tI_could_have_had_a_car_accident, ~N\n\t\t\tand_now_I'm_lying_unconscious ~N\n\t\t\tin_a_hospital_bed...",
    "~J0(2.0)\tI_don't_know ~N\n\t\t\twhat's_real_anymore... ~E ",
    "~J0(1.0)\t_ ",
    "~J0(3.0)\tCybil_said_Cheryl_was_heading ~N\n\t\t\ttowards_the_lake. ",
    "~J0(2.2)\tBut,_the_road_to_the_lake ~N\n\t\t\tis_blocked... ",
    "~J0(2.0)\tAren't_there_any_other_roads? ",
    "~J0(2.0)\tLisa_would_probably_know... ~E ",
    "\tThere_is_an_ ~C2 Axe ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_clock. ~N\n\tNothing_special. ~E ",
    "\tNo_need_to_go_back. ~E ",
    "\tNone_of_this_stuff_is_of_any_use. ~E ",
    "\tLooks_like_an_altar. ~N\n\tWonder_what_they_worship? ~E "
};

void func_800D1FF0(void) // 0x800D1FF0
{
    s32 tmp;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(true, 100, 3, -1, 0, false); // "Do you want to push the cabinet?"
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 5:
            Camera_PositionSet(NULL, Q12(179.35f), Q12(-1.5f), Q12(61.0098f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(176.98f), Q12(-0.49f), Q12(64.07f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Sd_EngineCmd(Sfx_Unk1538);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 105, false);

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(178.3f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(61.9f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(0.0f);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            func_8003CDA0(InventoryItemId_Handgun);
            Chara_Load(0, Chara_Cybil, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Savegame_EventFlagSet(EventFlag_302);
            SysWork_StateStepIncrement(0);

        case 6:
            tmp = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.22f), Q12_SHIFT);

            g_SysWork.player_4C.chara_0.position_18.vz += tmp;
            WorldObject_D_800D7FF0.position_1C.vz += tmp;

            D_800D5AE8 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(2.0f), Q12_SHIFT);
            if (D_800D5AE8 > Q12(1.0f))
            {
                D_800D5AE8 = Q12(1.0f);
            }

            if (WorldObject_D_800D7FF0.position_1C.vz > Q12(63.6814f))
            {
                tmp = WorldObject_D_800D7FF0.position_1C.vz - Q12(63.6814f);
                g_SysWork.player_4C.chara_0.position_18.vz -= tmp;
                WorldObject_D_800D7FF0.position_1C.vz -= tmp;

                SysWork_StateStepIncrement(0);
            }

            func_8005DE0C(Sfx_Unk1538, &WorldObject_D_800D7FF0.position_1C, D_800D5AE8 >> 5, Q12(12.0f), 0);
            break;

        case 7:
            D_800D5AE8 -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(2.0f), Q12_SHIFT);
            if (D_800D5AE8 < Q12(0.0f))
            {
                D_800D5AE8 = Q12(0.0f);
            }

            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(3.0f), false);
            func_8005DE0C(Sfx_Unk1538, &WorldObject_D_800D7FF0.position_1C, D_800D5AE8 >> 5, Q12(12.0f), 0);
            break;

        default:
            if (Savegame_EventFlagGet(EventFlag_302))
            {
                func_8004690C(Sfx_Unk1538);
                SysWork_StateSetNext(SysState_Gameplay);
                SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
                break;
            }

            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

// TODO: Replace these strings and vector once all users are decompiled.
extern const VECTOR3 D_800CBF88;
extern const char* D_800CBF94;
extern const char* D_800CBF9C;
extern const char* D_800CBFA4;
extern const char* D_800CBFAC;

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01_2", D_800CBF88);

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01_2", D_800CBF94);

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01_2", D_800CBF9C);

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01_2", D_800CBFA4);

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01_2", D_800CBFAC);

void func_800D2408(void) // 0x800D2408
{
    #define CUTSCENE_SKIP_STATE 43
    
    VECTOR3  sp18;
    SVECTOR3 sp28;
    s32      x;
    s32      z;

    #define playerChara &g_SysWork.player_4C.chara_0
    #define cybilChara  &g_SysWork.npcs_1A0[0]

    //static const VECTOR3 soundPos = VECTOR3(182.0f, -1.2f, 58.9f);
    #define soundPos D_800CBF88

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 41)
    {
        SysWork_StateStepSet(0, CUTSCENE_SKIP_STATE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            g_MapMsgSoundIdx = 0;
            D_800D5AEB = 0;

            Fs_QueueStartRead(FILE_ANIM_AQSH1_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);

            g_Timer0 = 0;

            func_80085EB8(0, playerChara, 0x33, false);

            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= 1 << 3;

            func_8008D438();

            g_SysWork.field_235C = 0;
            g_SysWork.field_236C = 0;
            g_SysWork.field_2378 = 0x1000;

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 2:
            func_80088D0C();
            SysWork_StateStepIncrement(0);

        case 3:
            Map_MessageWithAudio(15, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1309, &soundPos, 0x80, 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 6:
            func_80085EB8(0, playerChara, 0x76, false);
            func_8005DC1C(Sfx_Unk1310, &soundPos, 0x80, 0);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 8:
            Chara_Spawn(Chara_Cybil, 0, Q12(183.0f), Q12(61.0f), 0, 3);

            D_800D5AEB = 1;

            func_80085EB8(0, cybilChara, 5, false);
            func_8003D01C();
            SysWork_StateStepIncrement(0);

        case 9:
            func_80085EB8(1, playerChara, 0, false);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(0.0f), Q12(28.0f), true, false);
            break;

        case 10:
            Map_MessageWithAudio(16, &g_MapMsgSoundIdx, g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(0.0f), Q12(28.0f), true, false);
            break;

        case 11:
            func_80086C58(playerChara, 119);
            break;

        case 12:
            func_80085EB8(0, playerChara, 51, false);
            func_80085EB8(0, cybilChara, 1, false);
            func_8003D03C();
            Savegame_EventFlagSet(EventFlag_311);
            SysWork_StateStepIncrement(0);

        case 13:
            Map_MessageWithAudio(18, &g_MapMsgSoundIdx, g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(16.0f), Q12(29.0f), Q12(56.0f), true, true);
            break;

        case 14:
            func_80085EB8(0, cybilChara, 5, false);

            g_Timer0 = Q12(57.0f);
            g_SysWork.field_2378 = 0xB33;

            SysWork_StateStepIncrement(0);

        case 15:
            Map_MessageWithAudio(18, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 16:
            Map_MessageWithAudio(21, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 17:
            Map_MessageWithAudio(27, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 18:
            g_Timer0 = Q12(58.0f);
            g_SysWork.field_2378 = 0x1000;

            Map_MessageWithAudio(33, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 19:
            Map_MessageWithAudio(38, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 20:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 21:
            Map_MessageWithAudio(41, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 22:
            g_Timer0 = Q12(59.0f);
            g_SysWork.field_2378 = 0xB33;

            Map_MessageWithAudio(47, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 23:
            Map_MessageWithAudio(50, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 24:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 25:
            func_80085EB8(0, playerChara, 0x48, false);
            func_80085EB8(0, cybilChara, 1, false);
            SysWork_StateStepIncrement(0);

        case 26:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(59.0f), Q12(64.0f), true, true);
            break;

        case 27:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(16.0f), Q12(65.0f), Q12(83.0f), true, true);
            g_SysWork.field_2378 = 0x1000;
            break;

        case 28:
            func_80085EB8(3, playerChara, 0, false);
            func_80085EB8(0, playerChara, 0x33, false);
            func_80085EB8(0, cybilChara, 5, false);

            g_Timer0 = Q12(87.0f);
            g_SysWork.field_2378  = 0x800;

            SysWork_StateStepIncrement(0);

        case 29:
            Map_MessageWithAudio(0x3D, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 30:
            func_80085EB8(0, playerChara, 140, false);
            g_SysWork.field_2378  = 0x1000;
            SysWork_StateStepIncrement(0);

        case 31:
            g_Timer0 = Q12(88.0f);
            Map_MessageWithAudio(73, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 32:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 33:
            Map_MessageWithAudio(74, &g_MapMsgSoundIdx, g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(88.0f), Q12(121.0f), true, false);
            break;

        case 34:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(88.0f), Q12(121.0f), true, true);
            break;

        case 35:
            g_Timer0 = Q12(122.0f);
            D_800D8018 = 1;
            g_SysWork.field_2378 = 0x1333;

            func_80085EB8(0U, playerChara, 51, false);
            SysWork_StateStepIncrement(0);

        case 36:
            Map_MessageWithAudio(76, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 37:
            Map_MessageWithAudio(86, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 38:
            func_80085EB8(0, playerChara, 130, false);

            D_800D8018 = 0;
            g_SysWork.field_2378 = 0x1000;

            SysWork_StateStepIncrement(0);

        case 39:
            Map_MessageWithAudio(90, &g_MapMsgSoundIdx, g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(123.0f), Q12(139.0f), true, false);
            break;

        case 40:
            func_80086C58(playerChara, 0x78);

            g_SysWork.field_2378 = 0x1666;

            Savegame_EventFlagSet(EventFlag_313);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(140.0f), Q12(165.0f), true, false);
            break;

        case 41:
            sharedFunc_800D2EF4_0_s00();
            func_8003CD6C(&g_SysWork.playerCombatInfo_38);
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 42:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);

            if (g_SysWork.sysStateStep_C[0] != 42)
            {
                sharedFunc_800D2EF4_0_s00();
                SysWork_StateStepReset();
            }
            break;

        case CUTSCENE_SKIP_STATE:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 44:
            sharedFunc_800D2EF4_0_s00();
            func_8003CD6C(&g_SysWork.playerCombatInfo_38);
            SysWork_StateStepIncrement(0);

        default:
            sharedFunc_800D2244_0_s00(false);

            g_Timer0 = NO_VALUE;

            SysWork_StateSetNext(SysState_Gameplay);

            D_800D8018 = 0;

            func_80088F94(cybilChara, 0, 0);
            Fs_QueueWaitForEmpty();
            func_8003D01C();
            Sd_EngineCmd(19);
            Savegame_EventFlagSet(EventFlag_303);
            func_8008D448();
            func_8003EBA0();

            g_SysWork.field_2378 = 0x1000;
            Savegame_EventFlagClear(EventFlag_313);
            g_SysWork.field_30 = 0;
            break;
    }

    if (g_Timer0 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(playerChara.position_18, playerChara.rotation_24, &D_800CBF94, g_Timer0, (s_DmsHeader*)FS_BUFFER_11);

        if (D_800D5AEB != 0)
        {
            Dms_CharacterGetPosRot(cybilChara.position_18, cybilChara.rotation_24, &D_800CBF9C, g_Timer0, (s_DmsHeader*)FS_BUFFER_11);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPosition, &g_CutsceneCameraLookAt, NULL, g_Timer0, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPosition, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAt, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.field_2360, &sp28, &D_800CBFA4, g_Timer0, (s_DmsHeader*)FS_BUFFER_11);
        Dms_CharacterGetPosRot(&sp18, &sp28, &D_800CBFAC, g_Timer0, (s_DmsHeader*)FS_BUFFER_11);

        x = Q12_TO_Q6(sp18.vx - g_SysWork.field_2360.vx);
        z = Q12_TO_Q6(sp18.vz - g_SysWork.field_2360.vz);
        g_SysWork.field_2370.vx = -ratan2(sp18.vy - g_SysWork.field_2360.vy, Q6_TO_Q12(SquareRoot0(SQUARE(x) + SQUARE(z))));
        g_SysWork.field_2370.vy = ratan2(sp18.vx - g_SysWork.field_2360.vx, sp18.vz - g_SysWork.field_2360.vz);
        g_SysWork.field_2370.vz = 0;
    }
}

void func_800D2F74(void) // 0x800D2F74
{
    #define CUTSCENE_SKIP_STATE 10

    #define playerChara &g_SysWork.player_4C.chara_0

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 10)
    {
        SysWork_StateStepSet(0, CUTSCENE_SKIP_STATE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Fs_QueueStartRead(FILE_ANIM_AQRM_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);

            g_SysWork.field_30 = 20;

            ScreenFade_ResetTimestep();

            g_MapMsgSoundIdx1 = 0;
            g_Timer1 = Q12(0.0f);
            g_SysWork.flags_22A4 |= 1 << 3;

            func_80085EB8(0, playerChara, 0x79, false);
            Game_TurnFlashlightOn();
            sharedFunc_800D2EB4_0_s00();
            func_8003D03C();
            SysWork_StateStepIncrement(0);

            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= (1<<3);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementAfterTime(&g_Timer1, Q12(10.0f), Q12(0.0f), 0x22000, true, true);
            break;

        case 4:
            func_80086C58(playerChara, 116);
            SysWork_StateStepIncrementAfterTime(&g_Timer1, Q12(10.0f), Q12(35.0f), Q12(71.0f), true, false);
            break;

        case 5:
            func_80085EB8(0, playerChara, 53, false);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementAfterTime(&g_Timer1, Q12(15.0f), Q12(72.0f), Q12(93.0f), true, true);
            break;

        case 7:
            SysWork_StateStepIncrement(0);
            break;

        case 8:
            func_80085EB8(0, playerChara, 0x33, false);

            g_Timer1 = Q12(95.0f);

            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(0x5B, &g_MapMsgSoundIdx1, g_MapMsgSounds1);
            break;

        case CUTSCENE_SKIP_STATE:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);

            if (g_SysWork.sysStateStep_C[0] != 10)
            {
                g_Timer1 = Q12(95.0f);
            }
            break;

        default:
            g_Timer1 = NO_VALUE;

            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_305);
            vcReturnPreAutoCamWork(true);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            Sd_EngineCmd(19);
            sharedFunc_800D2EF4_0_s00();
            func_8003D01C();
            break;
    }

    if (g_Timer1 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(playerChara.position_18, playerChara.rotation_24, &D_800CBF94, g_Timer1, (s_DmsHeader*)FS_BUFFER_11);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPosition, &g_CutsceneCameraLookAt, NULL, g_Timer1, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPosition, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAt, NULL, true);
    }
}

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01_2", D_800CC09C);

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01_2", func_800D3420);

void func_800D4410(void) // 0x800D4410
{
    #define CUTSCENE_SKIP_STATE 14

    #define playerChara &g_SysWork.player_4C.chara_0

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 13)
    {
        Sd_EngineCmd(19);
        g_SysWork.sysStateStep_C[0] = CUTSCENE_SKIP_STATE;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            g_SysWork.field_30 = 20;

            ScreenFade_ResetTimestep();

            g_SysWork.flags_22A4 |= 1 << 3;

            Fs_QueueStartRead(FILE_ANIM_SQSU_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);

            g_Timer2 = Q12(0.0f);
            g_MapMsgSoundIdx2 = 0;

            func_80085EB8(0, playerChara, 124, false);
            func_80085EB8(2, playerChara, 0, false);
            func_8008D438();

            g_SysWork.field_2360.vx = Q12(19.6f);
            g_SysWork.field_2360.vy = Q12(2.0f);
            g_SysWork.field_2370.vx = Q12(0.25f);
            g_SysWork.field_235C = NULL;
            g_SysWork.field_2360.vz = Q12(62.0f);
            g_SysWork.field_236C = NULL;
            g_SysWork.field_2370.vy = 0;
            g_SysWork.field_2370.vz = 0;
            g_SysWork.field_2378 = 0x1000;

            func_8003ED74(14, 14);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.5f), false);
            break;

        case 2:
            func_80085EB8(3, playerChara, 0, false);
            Map_MessageWithAudio(102, &g_MapMsgSoundIdx2, g_MapMsgSounds2);
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(10.0f), Q12(0.0f), Q12(106.0f), true, false);
            break;

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(10.0f), Q12(0.0f), Q12(106.0f), true, false);
            break;

        case 4:
            Map_MessageWithAudio(103, &g_MapMsgSoundIdx2, g_MapMsgSounds2);
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(10.0f), Q12(0.0f), Q12(106.0f), true, false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(10.0f), Q12(0.0f), Q12(106.0f), true, true);
            break;

        case 6:
            func_80085EB8(0, playerChara, 153, false);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(10.0f), Q12(107.0f), Q12(128.0f), true, true);
            break;

        case 8:
            MapMsg_DisplayAndHandleSelection(false, 104, 0, 0, 0, false);
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(3.8f), Q12(129.0f), Q12(228.0f), true, false);
            break;

        case 9:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(3.8f), Q12(129.0f), Q12(228.0f), true, false);
            break;

        case 10:
            MapMsg_DisplayAndHandleSelection(false, 108, 0, 0, 0, false);
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(3.8f), Q12(129.0f), Q12(228.0f), true, false);
            break;

        case 11:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(3.8f), Q12(129.0f), Q12(228.0f), true, false);
            break;

        case 12:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.0f), false);
            SysWork_StateStepIncrementAfterTime(&g_Timer2, Q12(3.8f), Q12(129.0f), Q12(228.0f), true, false);
            break;

        case 13:
            SysWork_StateStepReset();
            break;

        case CUTSCENE_SKIP_STATE:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_309);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            func_8003ED74(7, 4);
            func_8008D448();
            func_8003EBA0();

            g_SysWork.field_2378 = 0x1000;

            Game_TurnFlashlightOn();

            g_Timer2 = NO_VALUE;

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    if (g_Timer2 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(playerChara.position_18, playerChara.rotation_24, &D_800CBF94, g_Timer2, (s_DmsHeader*)FS_BUFFER_11);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPosition, &g_CutsceneCameraLookAt, NULL, g_Timer2, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPosition, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAt, NULL, true);
    }
}

void func_800D496C(void) // 0x800D496C
{
    Event_ItemTake(InventoryItemId_Axe, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M4S01_PickupAxe, 113);
}

void func_800D4998(void) // 0x800D4998
{
    func_80087360(FILE_TIM_CLOCKATQ_TIM, Q12(0.0f), Q12(0.0f), 114);
}

void func_800D49C4(void) // 0x800D49C4
{
    Math_Vector3Set(&WorldObject_D_800D7FF0.position_1C, Q12(178.2681f), Q12(-0.387f), Q12(63.6814f));
    WorldObject_ModelNameSet(&WorldObject_D_800D7FF0.object_0, "MOV1_HID");

    Math_Vector3Set(&WorldObject_D_800D8020.position_1C.position_0, Q12(174.81f), Q12(-1.4197f), Q12(21.3344f));
    WorldObject_ModelNameSet(&WorldObject_D_800D8020.object_0, "MOV1_HID");

    if (!Savegame_EventFlagGet(EventFlag_302))
    {
        WorldObject_D_800D7FF0.position_1C.vz = Q12(62.7466f);
    }

    WorldObject_ModelNameSet(&WorldObject_D_800D8050.object_0, D_800A99E4.savePadName_4);

    WorldObjectPoseInit(&WorldObject_D_800D8070, 183.3833f, -1.2673f, 60.951f, 0.0f, 66.01, 0.0f);
    WorldObjectPoseInit(&WorldObject_D_800D8090, 23.4f, -0.91f, 60.8f, 0.0f, 90.4f, 0.0f);

    Math_Vector3Set(&WorldObject_D_800D80B0.position_1C.position_0, Q12(181.22f), 0, Q12(61.2015f));
    WorldObject_ModelNameSet(&WorldObject_D_800D80B0.object_0, "WALLX_HI");

    Math_Vector3Set(&WorldObject_D_800D80E0[0].position_1C, Q12(180.5647f), Q12(-0.502f), Q12(63.8853f));
    WorldObject_ModelNameSet(&WorldObject_D_800D80E0[0].object_0, "CUBE90_H");

    Math_Vector3Set(&WorldObject_D_800D80E0[1].position_1C, Q12(180.5647f), Q12(-0.502f), Q12(63.8853f));
    WorldObject_ModelNameSet(&WorldObject_D_800D80E0[1].object_0, "CUBE9_HI");
    D_800D8018 = 0;
}

void func_800D4BA4(void) // 0x800D4BA4
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (Savegame_EventFlagGet(EventFlag_302))
        {
            func_80069844(0xFFFF);
        }
        else
        {
            func_8006982C(2);
        }

        g_WorldGfx_ObjectAdd(&WorldObject_D_800D7FF0.object_0, &WorldObject_D_800D7FF0.position_1C, &(SVECTOR3){});
        g_WorldGfx_ObjectAdd(&WorldObject_D_800D8050.object_0, &WorldObject_D_800D8070.position_0, &WorldObject_D_800D8070.rotation_C);

        if (Savegame_EventFlagGet(EventFlag_313))
        {
            g_WorldGfx_ObjectAdd(&WorldObject_D_800D80B0.object_0, &WorldObject_D_800D80B0.position_1C.position_0, &(SVECTOR3){});
        }

        g_WorldGfx_ObjectAdd(&WorldObject_D_800D80E0[D_800D8018].object_0, &WorldObject_D_800D80E0[D_800D8018].position_1C, &(SVECTOR3){});
    }
    else
    {
        func_80069844(0xFFFF);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S01_PickupAxe))
        {
            g_WorldGfx_ObjectAdd(&WorldObject_D_800D8020.object_0, &WorldObject_D_800D8020.position_1C.position_0, &(SVECTOR3){});
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        g_WorldGfx_ObjectAdd(&WorldObject_D_800D8050.object_0, &WorldObject_D_800D8090.position_0, &WorldObject_D_800D8090.rotation_C);
    }
}

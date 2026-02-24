#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map4/map4_s01.h"
#include "maps/characters/cybil.h"

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

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D1AE0

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D1B78

#include "maps/shared/Map_RoomBgmInit_0_s02_CondTrue.h" // 0x800D1BAC

#include "maps/shared/Map_RoomBgmInit_0_s02_CondFalse.h" // 0x800D1C28

void func_800D1EB4(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D1EBC

void MapEvent_DoorJammed(void) // 0x800D1F54
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

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
            Player_ControlFreeze();
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
            SD_Call(Sfx_Unk1538);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 105, false);

            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(178.3f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(61.9f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(0.0f);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            WorldGfx_PlayerHeldItemSet(InventoryItemId_Handgun);
            Chara_Load(0, Chara_Cybil, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Savegame_EventFlagSet(EventFlag_302);
            SysWork_StateStepIncrement(0);

        case 6:
            tmp = Q12_MULT_PRECISE(g_DeltaTime, Q12(0.22f));

            g_SysWork.playerWork_4C.player_0.position_18.vz += tmp;
            WorldObject_D_800D7FF0.position_1C.vz += tmp;

            D_800D5AE8 += Q12_MULT_PRECISE(g_DeltaTime, Q12(2.0f));
            if (D_800D5AE8 > Q12(1.0f))
            {
                D_800D5AE8 = Q12(1.0f);
            }

            if (WorldObject_D_800D7FF0.position_1C.vz > Q12(63.6814f))
            {
                tmp = WorldObject_D_800D7FF0.position_1C.vz - Q12(63.6814f);
                g_SysWork.playerWork_4C.player_0.position_18.vz -= tmp;
                WorldObject_D_800D7FF0.position_1C.vz -= tmp;

                SysWork_StateStepIncrement(0);
            }

            func_8005DE0C(Sfx_Unk1538, &WorldObject_D_800D7FF0.position_1C, D_800D5AE8 >> 5, Q12(12.0f), 0);
            break;

        case 7:
            D_800D5AE8 -= Q12_MULT_PRECISE(g_DeltaTime, Q12(2.0f));
            if (D_800D5AE8 < Q12(0.0f))
            {
                D_800D5AE8 = Q12(0.0f);
            }

            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(3.0f), false);
            func_8005DE0C(Sfx_Unk1538, &WorldObject_D_800D7FF0.position_1C, D_800D5AE8 >> 5, Q12(12.0f), 0);
            break;

        default:
            // Return to gameplay.
            if (Savegame_EventFlagGet(EventFlag_302))
            {
                Sd_SfxStop(Sfx_Unk1538);

                SysWork_StateSetNext(SysState_Gameplay);
                SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
                break;
            }

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D2408(void) // 0x800D2408
{
    #define soundPos QVECTOR3(182.0f, -1.2f, 58.9f)

    typedef enum _EventState
    {
        EventState_Skip = 43
    } e_EventState;

    VECTOR3  lightIntPos;
    SVECTOR3 unused;

    #define playerChara &g_SysWork.playerWork_4C.player_0
    #define cybilChara  &g_SysWork.npcs_1A0[0]

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 41)
    {
        SysWork_StateStepSet(0, EventState_Skip);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            g_MapMsgSoundIdx = 0;
            D_800D5AEB = 0;

            Fs_QueueStartRead(FILE_ANIM_AQSH1_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);

            g_Timer0 = Q12(0.0f);

            func_80085EB8(0, playerChara, 51, false);

            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_8008D438();

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 2:
            Chara_ProcessLoads();
            SysWork_StateStepIncrement(0);

        case 3:
            Map_MessageWithAudio(15, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 4:
            func_8005DC1C(Sfx_DoorOpen0, &soundPos, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 6:
            func_80085EB8(0, playerChara, 118, false);
            func_8005DC1C(Sfx_DoorClose0, &soundPos, Q8_CLAMPED(0.5f), 0);
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
            g_SysWork.pointLightIntensity_2378 = Q12(0.7f);

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
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

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
            g_SysWork.pointLightIntensity_2378 = Q12(0.7f);

            Map_MessageWithAudio(47, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 23:
            Map_MessageWithAudio(50, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 24:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 25:
            func_80085EB8(0, playerChara, 72, false);
            func_80085EB8(0, cybilChara, 1, false);
            SysWork_StateStepIncrement(0);

        case 26:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(59.0f), Q12(64.0f), true, true);
            break;

        case 27:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(16.0f), Q12(65.0f), Q12(83.0f), true, true);
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            break;

        case 28:
            func_80085EB8(3, playerChara, 0, false);
            func_80085EB8(0, playerChara, 51, false);
            func_80085EB8(0, cybilChara, 5, false);

            g_Timer0 = Q12(87.0f);
            g_SysWork.pointLightIntensity_2378  = Q12(0.5f);

            SysWork_StateStepIncrement(0);

        case 29:
            Map_MessageWithAudio(0x3D, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 30:
            func_80085EB8(0, playerChara, 140, false);
            g_SysWork.pointLightIntensity_2378  = Q12(1.0f);
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
            g_SysWork.pointLightIntensity_2378 = Q12(1.2f);

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
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            SysWork_StateStepIncrement(0);

        case 39:
            Map_MessageWithAudio(90, &g_MapMsgSoundIdx, g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(123.0f), Q12(139.0f), true, false);
            break;

        case 40:
            func_80086C58(playerChara, 0x78);

            g_SysWork.pointLightIntensity_2378 = Q12(1.4f);

            Savegame_EventFlagSet(EventFlag_313);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(10.0f), Q12(140.0f), Q12(165.0f), true, false);
            break;

        case 41:
            sharedFunc_800D2EF4_0_s00();
            WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 42:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 42)
            {
                sharedFunc_800D2EF4_0_s00();
                SysWork_StateStepReset();
            }
            break;

        case EventState_Skip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 44:
            sharedFunc_800D2EF4_0_s00();
            WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);

            g_Timer0 = NO_VALUE;

            SysWork_StateSetNext(SysState_Gameplay);

            D_800D8018 = 0;

            func_80088F94(cybilChara, 0, 0);
            Fs_QueueWaitForEmpty();
            func_8003D01C();
            SD_Call(19);
            Savegame_EventFlagSet(EventFlag_303);
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            Savegame_EventFlagClear(EventFlag_313);
            g_SysWork.field_30 = 0;
            break;
    }

    if (g_Timer0 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(playerChara.position_18, playerChara.rotation_24, "HERO", g_Timer0, (s_DmsHeader*)FS_BUFFER_11);

        if (D_800D5AEB != 0)
        {
            Dms_CharacterGetPosRot(cybilChara.position_18, cybilChara.rotation_24, "SIBYL", g_Timer0, (s_DmsHeader*)FS_BUFFER_11);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPosition, &g_CutsceneCameraLookAt, NULL, g_Timer0, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPosition, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAt, NULL, true);

        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, "LIGHT", g_Timer0, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&lightIntPos, &unused, "L_INT", g_Timer0, FS_BUFFER_11);
        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy = ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = 0;
    }

    #undef soundPos
}

void func_800D2F74(void) // 0x800D2F74
{
    typedef enum _EventState
    {
        EventState_Skip = 10
    } e_EventState;

    #define playerChara &g_SysWork.playerWork_4C.player_0

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 10)
    {
        SysWork_StateStepSet(0, EventState_Skip);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Fs_QueueStartRead(FILE_ANIM_AQRM_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);

            g_SysWork.field_30 = 20;

            ScreenFade_ResetTimestep();

            g_MapMsgSoundIdx1 = 0;
            g_Timer1 = Q12(0.0f);
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_80085EB8(0, playerChara, 121, false);
            Game_TurnFlashlightOn();
            sharedFunc_800D2EB4_0_s00();
            func_8003D03C();
            SysWork_StateStepIncrement(0);

            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
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
            func_80085EB8(0, playerChara, 51, false);

            g_Timer1 = Q12(95.0f);

            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(0x5B, &g_MapMsgSoundIdx1, g_MapMsgSounds1);
            break;

        case EventState_Skip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 10)
            {
                g_Timer1 = Q12(95.0f);
            }
            break;

        default:
            g_Timer1 = NO_VALUE;

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_305);
            vcReturnPreAutoCamWork(true);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SD_Call(19);
            sharedFunc_800D2EF4_0_s00();
            func_8003D01C();
            break;
    }

    if (g_Timer1 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(playerChara.position_18, playerChara.rotation_24, "HERO", g_Timer1, (s_DmsHeader*)FS_BUFFER_11);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPosition, &g_CutsceneCameraLookAt, NULL, g_Timer1, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPosition, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAt, NULL, true);
    }
}

void func_800D3420(void) // 0x800D3420
{
    typedef enum _EventState
    {
        EventState_Skip = 30
    } e_EventState;

    typedef struct
    {
        SPRT*     sprt_0;
        DR_TPAGE* tpage_4;
        DR_STP*   stp_8;
        u8        unk_C[4];
        u8        unk_10[4];
        s32       activeBufferIdx_14;
    } g_GteScratchData_func_800DD2D4;

    VECTOR3                         lightIntPos;
    SVECTOR3                        unused;
    s32                             i;
    g_GteScratchData_func_800DD2D4* scratchData;

    #define playerChara &g_SysWork.playerWork_4C.player_0
    #define cybilChara  &g_SysWork.npcs_1A0[0]

    scratchData = PSX_SCRATCH_ADDR(0);

    // Skip.
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 29)
    {
        SysWork_StateStepSet(0, EventState_Skip);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800D5B06         = 0;
            g_SysWork.field_30 = 20;
            D_800D5AFC         = Q12(96.0f);

            sharedData_800D8568_1_s05.field_1  = 3;
            sharedData_800D8568_1_s05.flags_0  = (1 << 4) | (1 << 0);
            sharedData_800D8568_1_s05.field_C  = 0xFA;
            sharedData_800D8568_1_s05.field_12 = -0x2333;
            sharedData_800D8568_1_s05.field_14 = -0x1333;
            sharedData_800D8568_1_s05.field_1C = 0x400;
            sharedData_800D8568_1_s05.field_E  = -0x800;
            sharedData_800D8568_1_s05.field_3  = 0x40;
            sharedData_800D8568_1_s05.field_4  = 0x80;
            sharedData_800D8568_1_s05.field_5  = 0xFF;
            sharedData_800D8568_1_s05.field_8  = 0x80;
            sharedData_800D8568_1_s05.field_20 = 0xB04B0;
            sharedData_800D8568_1_s05.field_24 = 0x132CE;
            sharedData_800D8568_1_s05.field_6  = 0x14;
            sharedData_800D8568_1_s05.field_A  = 0x1000;
            sharedData_800D8568_1_s05.field_2  = 8;

            g_SysWork.flags_22A4 |= SysFlag2_3;

            sharedFunc_800CAAD0_1_s05();

            g_SysWork.field_235C = NULL;
            Math_Vector3Set(&g_SysWork.pointLightPosition_2360, sharedData_800D8568_1_s05.field_20, Q12(-2.0f), sharedData_800D8568_1_s05.field_24 + 0x1800);
            g_SysWork.field_236C = NULL;
            Math_SetSVectorFast(&g_SysWork.pointLightRot_2370, Q12_ANGLE(-90.0f), Q12_ANGLE(0.0f), Q12_ANGLE(0.0f));

            Gfx_MapEffectsUpdate(11, 11, PrimitiveType_S32, &D_800D5B00, 0, Q12(100.0f));
            D_800D5B00 = 0;
            func_8008D438();

            g_SysWork.pointLightIntensity_2378                       = Q12(2.5f);
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(180.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.0f);

            Ipd_CloseRangeChunksInit();
            SD_Call(Sfx_Unk1540);

            D_800D5B04 = Q12(0.2f);
            D_800D5AF9 = 1;

            Savegame_EventFlagSet(EventFlag_312);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085EB8(0, playerChara, 142, false);
            D_800D5B06 = 1;
            SysWork_StateStepIncrement(0);

        case 2:
            D_800D5B00 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 12.0f);

            Map_MessageWithAudio(95, &D_800D5AF8, &D_800D5ACC);
            SysWork_StateStepIncrementAfterTime(&D_800D5AFC, Q12(5.0f), Q12(96.0f), Q12(115.0f), true, false);

            D_800D5B04 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 1.5f);
            if (D_800D5B04 > Q12(1.0f))
            {
                D_800D5B04 = Q12(1.0f);
            }
            break;

        case 3:
            SysWork_StateStepIncrementAfterTime(&D_800D5AFC, Q12(5.0f), Q12(96.0f), Q12(115.0f), true, true);
            D_800D5B00 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 12.0f);

            D_800D5B04 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 1.5f);
            if (D_800D5B04 > Q12(1.0f))
            {
                D_800D5B04 = Q12(1.0f);
            }
            break;

        case 4:
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrement(0);

        case 6:
            func_80085EB8(0, playerChara, 51, false);
            SysWork_StateStepIncrement(0);

        case 7:
            D_800D5AFC  = Q12(139.0f);

            D_800D5B00 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 12.0f);
            if (D_800D5B00 >= Q12(100.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            D_800D5B04 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.8f);
            if (D_800D5B04 < 0)
            {
                D_800D5B04 = 0;
            }

            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.5f), false);
            break;

        case 9:
            D_800D5B06 = 0;

            for (i = ARRAY_SIZE(sharedData_800DFB7C_0_s00) - 1; i >= 0; i--)
            {
                sharedData_800DFB7C_0_s00[i].field_A = 0;
            }

            D_800D5AF9 = 0;
            Sd_SfxStop(Sfx_Unk1540);
            D_800D5AFC = Q12(140.0f);
            Gfx_MapInitMapEffectsUpdate(7, 4);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(178.8f), Q12(0.0f), Q12(62.8f));
            Math_SetSVectorFast(&g_SysWork.pointLightRot_2370, Q12_ANGLE(30.0f), Q12_ANGLE(-90.0f), Q12_ANGLE(0.0f));

            SysWork_StateStepIncrement(0);
            break;

        case 10:
            Chara_Spawn(Chara_Cybil, 0, Q12(183.0f), Q12(61.0f), Q12_ANGLE(0.0f), 3);
            Model_AnimFlagsClear(&(playerChara)->model_0, 2);
            SysWork_StateStepIncrement(0);
            break;

        case 11:
            func_80085EB8(0, cybilChara, 18, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);
            break;

        case 12:
            func_80085EB8(2, cybilChara, 0, false);
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 13:
            func_80085EB8(3, cybilChara, 0, false);
            SysWork_StateStepIncrement(0);

        case 14:
            Map_MessageWithAudio(97, &D_800D5AF8, &D_800D5ACC);
            SysWork_StateStepIncrementAfterTime(&D_800D5AFC, Q12(10.0f), Q12(140.0f), Q12(200.0f), true, false);
            break;

        case 15:
            SysWork_StateStepIncrementAfterTime(&D_800D5AFC, Q12(10.0f), Q12(140.0f), Q12(200.0f), true, true);
            break;

        case 16:
            func_80085EB8(0, cybilChara, 19, false);
            SysWork_StateStepIncrement(0);

        case 17:
            Map_MessageWithAudio(98, &D_800D5AF8, &D_800D5ACC);
            SysWork_StateStepIncrementAfterTime(&D_800D5AFC, Q12(2.0f), Q12(201.0f), Q12(216.0f), true, false);
            break;

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800D5AFC, Q12(2.0f), Q12(201.0f), Q12(216.0f), true, true);
            break;

        case 19:
            func_80085EB8(1, cybilChara, 0, false);
            break;

        case 20:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 21:
            func_80085EB8(0, cybilChara, 20, false);
            Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(175.9f), Q12(-1.0f), Q12(22.8f));
            Math_SetSVectorFast(&g_SysWork.pointLightRot_2370, Q12_ANGLE(0.0f), Q12_ANGLE(60.0f), Q12_ANGLE(0.0f));

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            D_800D5AFC           = Q12(217.0f);

            SysWork_StateStepIncrement(0);
            break;

        case 22:
            func_80085EB8(2, cybilChara, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);

        case 23:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 24:
            func_80085EB8(3, cybilChara, 0, false);
            SysWork_StateStepIncrement(0);

        case 25:
            Map_MessageWithAudio(99, &D_800D5AF8, &D_800D5ACC);
            SysWork_StateStepIncrementAfterTime(&D_800D5AFC, Q12(8.0f), Q12(217.0f), Q12(259.0f), true, false);
            break;

        case 26:
            SysWork_StateStepIncrementAfterTime(&D_800D5AFC, Q12(8.0f), Q12(217.0f), Q12(259.0f), true, true);
            break;

        case 27:
            SysWork_StateStepIncrementDelayed(Q12(1.4f), false);
            break;

        case 28:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.5f), false);
            break;

        case 29:
            SysWork_StateStepSet(0, -1);
            break;

        case 30:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            D_800D5B06 = 0;
            for (i = ARRAY_SIZE(sharedData_800DFB7C_0_s00) - 1; i >= 0; i--)
            {
                sharedData_800DFB7C_0_s00[i].field_A = 0;
            }

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            D_800D5AFC = NO_VALUE;
            SD_Call(19);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_306);

            Model_AnimFlagsSet(&(playerChara)->model_0, 2);
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    if (D_800D5AF9 != 0)
    {
        func_8005DE0C(Sfx_Unk1540, &QVECTOR3(176.3f, -1.5f, 19.18f), Q8_CLAMPED(0.5f) - FP_MULTIPLY_PRECISE(D_800D7F30, 128, 12), Q12(16.0f), 0);
    }

    if (D_800D5AFC >= 0)
    {
        Dms_CharacterGetPosRot(playerChara.position_18, playerChara.rotation_24, "HERO", D_800D5AFC, FS_BUFFER_11);
        if (g_SysWork.sysStateStep_C[0] >= 10)
        {
            Dms_CharacterGetPosRot(cybilChara.position_18, cybilChara.rotation_24, "SIBYL", D_800D5AFC, FS_BUFFER_11);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPosition, &g_CutsceneCameraLookAt, NULL, D_800D5AFC, FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPosition, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAt, NULL, true);

        if (g_SysWork.sysStateStep_C[0] >= 21)
        {
            Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, "LIGHT", D_800D5AFC, FS_BUFFER_11);
            Dms_CharacterGetPosRot(&lightIntPos, &unused, "L_INT", D_800D5AFC, FS_BUFFER_11);
            g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
            g_SysWork.pointLightRot_2370.vy = ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
            g_SysWork.pointLightRot_2370.vz = 0;
        }
    }

    if (D_800D5B06 != 0)
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
            setDrawTPage(scratchData->tpage_4, 0, 0, getTPage(2, 0, ((scratchData->activeBufferIdx_14 << 4) + (i << 2)) << 6, (((scratchData->activeBufferIdx_14 << 4) >> 4) & 1) << 8));

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
}

void func_800D4410(void) // 0x800D4410
{
    typedef enum _EventState
    {
        EventState_Skip = 14
    } e_EventState;

    #define playerChara &g_SysWork.playerWork_4C.player_0

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 13)
    {
        SD_Call(19);
        g_SysWork.sysStateStep_C[0] = EventState_Skip;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.field_30 = 20;

            ScreenFade_ResetTimestep();

            g_SysWork.flags_22A4 |= SysFlag2_3;

            Fs_QueueStartRead(FILE_ANIM_SQSU_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);

            g_Timer2 = Q12(0.0f);
            g_MapMsgSoundIdx2 = 0;

            func_80085EB8(0, playerChara, 124, false);
            func_80085EB8(2, playerChara, 0, false);
            func_8008D438();

            g_SysWork.field_235C = NULL;
            g_SysWork.pointLightPosition_2360.vx = Q12(19.6f);
            g_SysWork.pointLightPosition_2360.vy = Q12(2.0f);
            g_SysWork.pointLightPosition_2360.vz = Q12(62.0f);
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightRot_2370.vx = Q12_ANGLE(90.0f);
            g_SysWork.pointLightRot_2370.vy = Q12_ANGLE(0.0f);
            g_SysWork.pointLightRot_2370.vz = Q12_ANGLE(0.0f);
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            Gfx_MapInitMapEffectsUpdate(14, 14);
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

        case EventState_Skip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_309);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Gfx_MapInitMapEffectsUpdate(7, 4);
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            Game_TurnFlashlightOn();

            g_Timer2 = NO_VALUE;

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    if (g_Timer2 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(playerChara.position_18, playerChara.rotation_24, "HERO", g_Timer2, (s_DmsHeader*)FS_BUFFER_11);
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
    MapMsg_DisplayWithTexture(FILE_TIM_CLOCKATQ_TIM, Q12(0.0f), Q12(0.0f), 114);
}

void Map_WorldObjectsInit(void) // 0x800D49C4
{
    WorldObjectNoRotInit(&WorldObject_D_800D7FF0, "MOV1_HID", 178.2681f, -0.387f, 63.6814f);

    WorldObjectNoRotInit(&WorldObject_D_800D8020, "MOV1_HID", 174.81f, -1.4197f, 21.3344f);

    if (!Savegame_EventFlagGet(EventFlag_302))
    {
        WorldObject_D_800D7FF0.position_1C.vz = Q12(62.7466f);
    }

    WorldObject_ModelNameSet(&WorldObject_D_800D8050.object_0, D_800A99E4.savePadName_4);

    WorldObjectPoseInit(&WorldObject_D_800D8070, 183.3833f, -1.2673f, 60.951f, 0.0f, 66.01, 0.0f);
    WorldObjectPoseInit(&WorldObject_D_800D8090, 23.4f, -0.91f, 60.8f, 0.0f, 90.4f, 0.0f);

    WorldObjectNoRotInit(&WorldObject_D_800D80B0, "WALLX_HI", 181.22f, 0.0f, 61.2015f);

    WorldObjectNoRotInit(&WorldObject_D_800D80E0[0], "CUBE90_H", 180.5647f, -0.502f, 63.8853f);

    WorldObjectNoRotInit(&WorldObject_D_800D80E0[1], "CUBE9_HI", 180.5647f, -0.502f, 63.8853f);
    D_800D8018 = 0;
}

void Map_WorldObjectsUpdate(void) // 0x800D4BA4
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

        WorldGfx_ObjectAdd(&WorldObject_D_800D7FF0.object_0, &WorldObject_D_800D7FF0.position_1C, &(SVECTOR3){ 0, 0, 0 });
        WorldGfx_ObjectAdd(&WorldObject_D_800D8050.object_0, &WorldObject_D_800D8070.position_0, &WorldObject_D_800D8070.rotation_C);

        if (Savegame_EventFlagGet(EventFlag_313))
        {
            WorldGfx_ObjectAdd(&WorldObject_D_800D80B0.object_0, &WorldObject_D_800D80B0.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }

        WorldGfx_ObjectAdd(&WorldObject_D_800D80E0[D_800D8018].object_0, &WorldObject_D_800D80E0[D_800D8018].position_1C, &(SVECTOR3){ 0, 0, 0 });
    }
    else
    {
        func_80069844(0xFFFF);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S01_PickupAxe))
        {
            WorldGfx_ObjectAdd(&WorldObject_D_800D8020.object_0, &WorldObject_D_800D8020.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        WorldGfx_ObjectAdd(&WorldObject_D_800D8050.object_0, &WorldObject_D_800D8090.position_0, &WorldObject_D_800D8090.rotation_C);
    }
}

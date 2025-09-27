#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"

const char* MAP_MESSAGES[] =
{
    #include "maps/shared/mapMsg_common.h"
    "~J0(2.0)\tWas_I_dreaming?  ~E ",
    "~J0(2.5)\tHow_do_you_feel? ~E ",
    "~J0(6.0)\tLike_I've_been ~N\n\t\t\trun_over_by_a_truck, ~N\n\t\t\tbut_I'm_all_right,_I_guess. ~E ",
    "~J0(1.5)\tGlad_to_hear_it.",
    "~J0(5.0)\tYou_from_around_here? ~N\n\t\t\tWhy_don't_you ~N\n\t\t\ttell_me_what_happened? ",
    "~J0(3.0)\tWait_a_second. ~N\n\t\t\tI'm_just_a_tourist. ",
    "~J0(5.2)\tI_came_here_for_a_vacation. ~N\n\t\t\tI_just_got_here... ",
    "~J0(4.2)\tI_don't_know_what_happened. ",
    "~J0(4.0)\tI'd_like_to_find_out_myself. ",
    "~J0(2.0)\tUh-huh? ~E ",
    "~J0(3.0)\tHave_you_seen_a_little_girl? ",
    "~J0(4.0)\tJust_turned_seven_last_month... ~N\n\t\t\tShort,_black_hair... ",
    "~J0(1.5)\tMy_daughter. ",
    "~J0(1.0)\tSorry. ",
    "~J0(3.0)\tThe_only_person_I've_seen ~N\n\t\t\tin_this_town_is_you. ",
    "~J0(2.5)\tWhere_is_everybody? ",
    "~J0(3.5)\tI'd_tell_you_if_I_knew,~N\n\t\t\tbelieve_me. ",
    "~J0(5.5)\tBut,_from_what_I_can_tell, ~N\n\t\t\tsomething_bizarre_is_going_on. ",
    "~J0(2.5)\tThat's_all_I_know. ",
    "~J0(2.0)\tHmmm... ~E ",
    "~J0(2.0)\tWhat's_your_name? ",
    "~J0(1.0)\tHarry... ",
    "~J0(2.0)\tHarry_Mason. ",
    "~J0(2.0)\tCybil_Bennett. ",
    "~J0(4.0)\tI'm_a_police_officer ~N\n\t\t\tfrom_Brahms, ~N\n\t\t\tthe_next_town_over. ",
    "~J0(3.0)\tThe_phones_are_all_dead, ~N\n\t\t\tand_the_radio,_too. ",
    "~J0(4.0)\tI'm_going_back_to_call ~N\n\t\t\tin_some_reinforcements. ",
    "~J0(1.5)\tHmph. ~E ",
    "~D\t~J0(4.0)\tHold_it! ~N\n\t\t\tWhere_do_you_think ~N\n\t\t\tyou're_going? ~E ",
    "~J0(4.0)\tMy_daughter... ~N\n\t\t\tI've_gotta_find_her! ~E ",
    "~D\t~J0(1.5)\tNo_way! ~E ",
    "~J0(3.0)\tIt's_dangerous_out_there. ",
    "~J0(5.0)\tIn_that_case, ~N\n\t\t\tI_need_to_find_her_now! ~N\n\t\t\tCheryl's_my_little_girl. ",
    "~J0(3.0)\tI_can't_just_leave_her_out ~N\n\t\t\tthere_by_herself. ~E ",
    "~J0(2.5)\tHave_you_got_a_gun? ",
    "~J0(3.0)\tUmmm..._no. ~E ",
    "~J0(5.0)\tTake_this. ~N\n\t\t\tAnd_hope_you_don't ~N\n\t\t\thave_to_use_it. ",
    "~J0(1.5)\tNow_listen_to_me, ",
    "~J0(4.5)\tbefore_you_pull_the_trigger, ~N\n\t\t\tknow_who_you're_shooting. ",
    "~J0(3.0)\tAnd_don't_do_it ~N\n\t\t\tunless_you_have_to. ~E ",
    "~J0(3.0)\tAnd_don't_go_blasting_me ~N\n\t\t\tby_mistake. ",
    "~J0(2.5)\tGot_it? ~E ",
    "~J0(2.5)\tYeah._Thanks. ~E ",
    "~J0(5.0)\tYou'd_do_best_to_stay_nearby. ~N\n\t\t\tI'll_be_back_with ~N\n\t\t\thelp_as_quick_as_I_can. ~E ",
    "~H There_is_a_ ~C5 Residential_area_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Kitchen_knife ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Flashlight ~C7 . ~N\n\tTake_it? ~S4 ",
    "~J0(1.1)\tWhat's_that? ~E ",
    "~J0(4.5)\tHuh?_Radio? ~N\n\t\t\tWhat's_going_on_with_that_radio? ~E ",
    "\tThere_is_a_ ~C2 Pocket_radio ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tA_radio... is_it_broken? ~N\n\tCan't_hear_anything. ~E ",
    " ",
    "\tMaybe_I_should_check_for ~N\n\tsomething_useful_before_leaving. ~E ",
    "~J0(4.3)\tThis_is_not_a_dream! ~N\n\tWhat's_happening_to_this_place!? ~E ",
    "\tI'll_worry_about_the_radio_later, ~N\n\tI_have_more_important_stuff ~N\n\tto_do. ~E ",
    "\tI've_got_to_beat_that_monster! ~E ",
    "\tThe_radio_may_be ~N\n\tuseful_for_something. ",
    "\tI_better_take_it_with_me. ~E ",
    "\tPinball_machine. ~N\n\tNothing_unusual. ~E ",
    "\tCan't_turn_on_the_TV. ~N\n\tNo_power? ~E ",
    "\tI_have_more_important_stuff_to_do. ~E "
};

void MapEvent_CafeCutscene() // 0x800DA980
{
    #define CUTSCENE_SKIP_STATE 52

    const static VECTOR3 D_800CC8FC = {0x00000CCC, 0xFFFFECCD, 0x0010D800};

    u8              temp_s0_5;
    s_SubCharacter* chara0;
    s_SubCharacter* chara1;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] > 5 && g_SysWork.sysStateStep_C[0] < 47)
    {
        SysWork_NextStateStepSet(CUTSCENE_SKIP_STATE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            
            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= 1 << 3;
            g_SavegamePtr->flags_AC &= ~(1 << 0);
            g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);
            g_MapMsgSoundIdx = 0;
            D_800DE250 = 0;
            D_800DE251 = 0;
            
            Fs_QueueStartRead(FILE_ANIM_CAFE_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);
            Chara_Load(0, Chara_Cybil, &g_SysWork.npcCoords_FC0[0], NO_VALUE, NULL, NULL);
            func_80088D0C();
            Chara_Spawn(Chara_Cybil, 0, Q12(4.4f), Q12(269.9f), FP_ANGLE(0.0f), 2);
            
            g_Timer0 = 0;
            SysWork_StateStepIncrement();
        
        case 1:
            func_80087EDC(9);
            break;
        
        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 77, false);
            func_8008616C(0, false, 0, Q12(0.0f), false);
            func_800D2054();
            SysWork_StateStepIncrement();
            break;
        
        case 3:
            func_80085EB8(2, &g_SysWork.player_4C.chara_0, NULL, false);
            SysWork_StateStepIncrement();
        
        case 4:
            func_8008616C(1, false, 0, Q12(0.0f), false);
            break;
        
        case 5:
            func_80085EB8(3, &g_SysWork.player_4C.chara_0, NULL, false);
            SysWork_StateStepIncrement();
        
        case 6:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(7.8f), Q12(0.0f), Q12(5.0f), false, true);
            break;
        
        case 7:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(7.8f), Q12(0.0f), Q12(26.0f), true, false);
            Map_MessageWithAudio(15, &g_MapMsgSoundIdx, g_MapMsgSounds); // "Was I dreaming?"
            break;
        
        case 8:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(7.8f), Q12(0.0f), Q12(26.0f), true, true);
            break;
        
        case 9:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 78, false);
            D_800DE250 = 1;
            SysWork_StateStepIncrement();
        
        case 10:
        case 11:
        case 12:
        case 13:
            switch (g_SysWork.sysStateStep_C[0])
            {
                case 10:
                    Map_MessageWithAudio(16, &g_MapMsgSoundIdx, g_MapMsgSounds); // "How do you feel?"
                    break;

                case 11:
                    Map_MessageWithAudio(17, &g_MapMsgSoundIdx, g_MapMsgSounds); // "Like I've been hit..."
                    break;

                case 12:
                    if (g_Timer0 == Q12(48.0f) && D_800DE251 == 2)
                    {
                        SysWork_NextStateStepSet(13);
                    }
                    break;

                case 13:
                    Map_MessageWithAudio(18, &g_MapMsgSoundIdx, g_MapMsgSounds); // "Glad to hear it."
                    break;
            }

            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(4.0f), Q12(27.0f), Q12(48.0f), true, false);

            if (D_800DE251 == 0 && g_Timer0 > Q12(38.0f))
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 10, false);
                func_80085EB8(0, &g_SysWork.player_4C.chara_0, 110, false);
                
                D_800DE251++;
            }

            temp_s0_5 = D_800DE251;
            if (D_800DE251 == 1 && sharedFunc_800D8964_0_s00(&g_SysWork.npcs_1A0[0]) == temp_s0_5)
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);
                D_800DE251++;
            }
            break;

        case 14:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(3.0f), Q12(49.0f), Q12(139.0f), true, false);
            Map_MessageWithAudio(25, &g_MapMsgSoundIdx, g_MapMsgSounds); // "Have you seen a little girl?"
            break;

        case 15:
            g_Timer0 = Q12(140.0f);
            SysWork_StateStepIncrement();

        case 16:
            Map_MessageWithAudio(35, &g_MapMsgSoundIdx, g_MapMsgSounds); // "What's your name?"
            break;

        case 17:
            func_80085E6C(Q12(1.2f), false);
            break;

        case 18:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 93, false);
            SysWork_StateStepIncrement();

        case 19:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(141.0f), Q12(152.0f), false, true);
            break;

        case 20:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            SysWork_StateStepIncrement();

        case 21:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(141.0f), Q12(159.0f), true, true);
            func_8004729C(4108);
            break;

        case 22:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            Sd_EngineCmd(4108);
            SysWork_StateStepIncrement();

        case 23:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(160.0f), Q12(173.0f), true, false);
            MapMsg_DisplayAndHandleSelection(false, 43, 0, 0, 0, false);
            Gfx_DebugStringPosition(30, 30);
            break;

        case 24:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x47, false);
            SysWork_StateStepIncrement();

        case 25:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(174.0f), Q12(184.0f), true, false);
            Map_MessageWithAudio(44, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 26:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, 0);
            SysWork_StateStepIncrement();

        case 27:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(185.0f), Q12(194.0f), true, false);
            Map_MessageWithAudio(45, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 28:
            g_Timer0 = Q12(195.0f);

            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            SysWork_StateStepIncrement();

        case 29:
            Map_MessageWithAudio(46, &g_MapMsgSoundIdx, g_MapMsgSounds); // "It's dangerous out there."
            break;

        case 30:
            func_80085E6C(Q12(1.5f), false);
            break;

        case 31:
            Map_MessageWithAudio(49, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 32:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement();

        case 33:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(20.0f), Q12(207.0f), Q12(222.0f), true, true);
            break;

        case 34:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            SysWork_StateStepIncrement();

        case 35:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(5.0f), Q12(223.0f), Q12(251.0f), true, false);
            Map_MessageWithAudio(51, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 36:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(5.0f), Q12(223.0f), Q12(251.0f), true, false);
            func_80085E6C(Q12(0.6f), false);
            break;

        case 37:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(5.0f), Q12(223.0f), Q12(251.0f), true, false);
            Map_MessageWithAudio(55, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 38:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x4C, false);
            SysWork_StateStepIncrement();

        case 39:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(252.0f), Q12(280.0f), true, false);
            Map_MessageWithAudio(57, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 40:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(252.0f), Q12(280.0f), true, true);
            break;

        case 41:
            func_80085EB8(0, g_SysWork.npcs_1A0, 5, false);
            SysWork_StateStepIncrement();

        case 42:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(281.0f), Q12(296.0f), true, true);
            break;

        case 43:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x33, false);
            g_Timer0 = Q12(297.0f);
            SysWork_StateStepIncrement();

        case 44:
            Map_MessageWithAudio(58, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 45:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 90, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement();

        case 46:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, Q12(10.0f), Q12(298.0f), Q12(308.0f), true, true);
            break;

        case 47:
            D_800DE250 = 0;

            func_8005DC1C(Sfx_Unk1357, &D_800CC8FC, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement();

        case 48:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            Sd_EngineCmd(19);
            Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0[0], NO_VALUE, 0, 0);
            func_80086470(3, InventoryItemId_Handgun, HANDGUN_AMMO_PICKUP_ITEM_COUNT, false);
            SysWork_StateStepIncrement();

        case 49:
            func_8008616C(2, true, 0, Q12(0.0f), false);
            break;

        case 50:
            g_Timer0 = Q12(308.0);
            func_80085E6C(Q12(0.5f), false);
            break;

        case 51:
            SysWork_StateStepReset();
            break;

        case CUTSCENE_SKIP_STATE:
            func_8008616C(2, true, 0, Q12(0.0f), false);
            break;

        case 53:
            //SysWork_NextStateStepSet(48); // TODO: Doesn't match?
            g_SysWork.sysStateStep_C[0] = 48;
            g_SysWork.field_28          = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C          = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);

            vcReturnPreAutoCamWork(1);
            func_8008616C(0, false, 2, Q12(0.0f), false);
            func_8008616C(0, false, 0, Q12(0.0f), false);
            Sd_EngineCmd(23);

            Savegame_EventFlagSet(EventFlag_49);
            g_Timer0 = NO_VALUE;
            break;
    }

    if (g_Timer0 >= Q12(0.0f))
    {
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, g_Timer0, FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, "HERO", g_Timer0, FS_BUFFER_11);

        if (D_800DE250 != 0)
        {
            chara0 = &g_SysWork.npcs_1A0[0];
            chara0->model_0.anim_4.flags_2 |= AnimFlag_Visible;
            Dms_CharacterGetPosRot(&chara0->position_18, &chara0->rotation_24, "SIBYL", g_Timer0, FS_BUFFER_11);
            return;
        }

        chara1 = &g_SysWork.npcs_1A0[0];
        chara1->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
    }
}

void MapEvent_ToBeContinued(void) // 0x800DB790
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(0, true, 0, Q12(0.0f), false);
            func_800862F8(0, FILE_TIM_CONTINUE_TIM, false);
            SysWork_StateStepIncrement();

        case 2:
            func_8008616C(1, true, 0, Q12(0.0f), false);
            return;

        case 3:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            return;

        case 4:
            func_8008616C(0, false, 0, Q12(2.0f), false);
            SysWork_StateStepIncrement();

        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement();
            }

            func_80085E6C(Q12(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 7)
            {
                g_SysWork.sysStateStep_C[0] = 6;
            }
            break;

        case 7:
            func_800862F8(7, FILE_TIM_COMESOON_TIM, false);
            break;

        case 8:
            func_8008616C(0, false, 0, Q12(1.5f), false);
            func_8004690C(Sfx_Unk1321);
            func_8004690C(Sfx_Unk1322);
            SysWork_StateStepIncrement();

        case 9:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement();
            }

            func_80085E6C(Q12(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 11)
            {
                g_SysWork.sysStateStep_C[0] = 10;
                break;
            }
            break;

        case 6:
        case 10:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            func_8008616C(2, true, 0, Q12(1.5f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_WarmBoot();

            g_SysWork.field_22A0 |= 1 << 0;
            break;
    }
}

const VECTOR3 D_800CCA1C =
{
    0x00000CCC,
    0xFFFFE99A,
    0x0010BB33,
};

const VECTOR3 D_800CCA28 =
{
    0x000004CC,
    0xFFFFE99A,
    0x0010BB33,
};

const VECTOR3 D_800CCA34 =
{
    0x00000CCC,
    0xFFFFE334,
    0x0010BB33,
};

const VECTOR3 D_800CCA40 =
{
    0x00000CCC,
    0xFFFFE99A,
    0x00111E66,
};

const VECTOR3 D_800CCA4C =
{
    0x000004CC,
    0xFFFFE99A,
    0x00111E66,
};

const VECTOR3 D_800CCA58 =
{
    0x00000CCC,
    0xFFFFE334,
    0x00108199,
};

void MapEvent_AirScreamerIntroCutscene() // 0x800DBAA0
{
    q19_12 time;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8003A16C();

            Savegame_EventFlagSet(EventFlag_50);

            Sd_EngineCmd(1321);
            Sd_EngineCmd(1322);

            Savegame_EventFlagSet(EventFlag_52);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(1.3f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(269.7f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(5.0f);

            g_Timer0 = Q12(26.0f);

            func_8008616C(0, true, 3, Q12(0.0f), false);

            g_MapMsgSoundIdx = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_80087EDC(30);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 91, 0);
            SysWork_StateStepIncrement();

        case 4:
            time     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(time, Q12(37.0f));
            if (g_Timer0 >= Q12(37.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 5:
            Map_MessageWithAudio(62, &g_MapMsgSoundIdx, &D_800DE124); // "What's that?"
            break;

        case 6:
            func_80085E6C(Q12(0.5f), false);
            break;

        case 7:
            Map_MessageWithAudio(63, &g_MapMsgSoundIdx, &D_800DE124); // "Huh? Radio?"
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 92, false);
            SysWork_StateStepIncrement();

        case 9:
            time = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(time, Q12(52.0f));
            if (g_Timer0 >= Q12(52.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 10:
            g_Timer0 = MAX(g_Timer0, Q12(53.0f));
            D_800E23A1 = 0x80;
            Savegame_EventFlagSet(EventFlag_45);

            func_80085E6C(Q12(1.5f), false);
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            SysWork_StateStepIncrement();

        case 12:
            time = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(time, Q12(75.0f));

            if (g_Timer0 >= Q12(75.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 13:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 89, false);

            D_800E23A1 = 0xE0;
            Savegame_EventFlagSet(EventFlag_46);
            g_Timer0 = Q12(76.0f);

            SysWork_StateStepIncrement();

        case 14:
            time   = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(time, Q12(115.0f));
            if (g_Timer0 >= Q12(115.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 15:
            func_800CCB8C(&D_800CCA1C, &D_800CCA28, 0x2800, 0xCC, 0x999, 0x666, 0x199, 0);
            func_8005DC1C(Sfx_Unk1373, &D_800CCA34, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement();

        case 16:
            time = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(time, Q12(146.0f));
            if (g_Timer0 >= Q12(146.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 17:
            func_800CCB8C(&D_800CCA40, &D_800CCA4C, 0x3000, 0x147, 0x666, 0x666, 0xED, 0);
            func_8005DC1C(Sfx_Unk1374, &D_800CCA58, Q8_CLAMPED(0.5f), 0);
            func_8005DC1C(Sfx_Unk1375, &D_800CCA58, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement();

        case 18:
            time = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(time, Q12(147.0f));
            if (g_Timer0 >= Q12(147.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 19:
            func_800D3AC0(&g_SysWork.npcs_1A0[0]);
            SysWork_StateStepIncrement();

        case 20:
            time     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(time, Q12(154.0f));
            if (g_Timer0 >= Q12(154.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 21:
            Savegame_EventFlagSet(EventFlag_47);
            func_800D39F4(&g_SysWork.npcs_1A0[0]);
            func_8008616C(0, false, 2, Q12(0.0f), false);

            g_Timer0 = NO_VALUE;

            vcReturnPreAutoCamWork(true);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Player_FallBackward();

            g_SysWork.flags_22A4 &= ~(1 << 5);
            g_SysWork.flags_22A4 &= ~(1 << 9);
            break;
    }

    if (g_Timer0 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, "HERO", g_Timer0, FS_BUFFER_11);

        if (g_SysWork.sysStateStep_C[0] >= 20)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "BIRD", g_Timer0, FS_BUFFER_11);
            g_SysWork.npcs_1A0[0].position_18.vx += FP_MULTIPLY(Math_Sin(g_SysWork.npcs_1A0[0].rotation_24.vy), Q12(0.2f), Q12_SHIFT);
            g_SysWork.npcs_1A0[0].position_18.vz += FP_MULTIPLY(Math_Cos(g_SysWork.npcs_1A0[0].rotation_24.vy), Q12(0.2f), Q12_SHIFT);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, g_Timer0, FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);
    }
}

void MapEvent_PocketRadioItemTake() // 0x800DC34C
{
    Event_ItemTake(InventoryItemId_PocketRadio, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupPocketRadio, 64);
    g_SavegamePtr->flags_AC |= 1 << 0;
}

void MapEvent_FlashlightItemTake() // 0x800DC394
{
    Event_ItemTake(InventoryItemId_Flashlight, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupFlashlight, 61);
    Game_TurnFlashlightOff();
}

void MapEvent_MapItemTake() // 0x800DC3C8
{
    static const RECT IMG_BUFFER_RECT = { 320, 256, 160, 240 };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            DrawSync(0);
            StoreImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B5, FS_BUFFER_2, &g_MapImg);
            Screen_Init(SCREEN_WIDTH, true);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            func_8008616C(0, false, 0, Q12(0.0f), false);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement();

        case 3:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            MapMsg_DisplayAndHandleSelection(true, 59, 6, 4, 0, false);
            break;

        case 5:
            LoadImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Screen_Init(SCREEN_WIDTH, false);
            func_8008616C(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepReset();
            break;

        case 6:
            g_SavegamePtr->hasMapsFlags_164 |= 1 << 1;

            Fs_QueueStartRead(FILE_ANIM_CAFE2_DMS, FS_BUFFER_11);
            SysWork_StateStepIncrement();

        case 4:
        case 7:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            func_8008616C(2, true, 0, Q12(0.0f), false);
            break;

        case 8:
            LoadImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Screen_Init(SCREEN_WIDTH, false);
            func_8008616C(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement();

        case 9:
            func_80088D0C();
            SysWork_StateStepIncrement();

        case 10:
            // Set cutscene character.
            Chara_Spawn(Chara_AirScreamer, 0, Q12(0.0f), Q12(0.0f), FP_ANGLE(0.0f), 12);
            DmsHeader_FixOffsets(FS_BUFFER_11);
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "BIRD", 0, FS_BUFFER_11);

            // Set camera.
            vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, 0, FS_BUFFER_11));
            vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
            vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(4.585938f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(267.285156f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(90.0f);

            // Set flags.
            g_SysWork.field_2290             |= 1 << 0;
            g_SysWork.field_228C             |= 1 << 0;
            Savegame_EventFlagSet(EventFlag_M0S01_PickupMap);

            SysWork_StateStepIncrement();

        case 11:
            func_8008616C(1, false, 0, Q12(0.0f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_KitchenKnifeItemTake() // 0x800DC830
{
    Event_ItemTake(InventoryItemId_KitchenKnife, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupKitchenKnife, 60);
}

/** Presumably a pickup function. Maybe debug or something unused and commented out. */
void MapEvent_EmptyFunction() {}

void MapEvent_CommonItemTake() // 0x800DC864
{
    s32 eventFlagIdx;
    u32 pickupType;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 13:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S01_HealthDrink0;
            break;

        case 14:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S01_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void MapEvent_AirScreamerDeath() // 0x800DC8C8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8004690C(Sfx_Unk1321);
            func_8004690C(Sfx_Unk1322);

            Savegame_EventFlagClear(EventFlag_52);
            g_MapMsgSoundIdx = 0;
            SysWork_StateStepIncrement();

        case 1:
            Map_MessageWithAudio(68, &g_MapMsgSoundIdx, &D_800DE128); // "This is not a dream!"
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_51);
            break;
    }
}

void Map_WorldObjectsInit() // 0x800DC9C8
{
    D_800E23A1 = 224;
    Math_Vector3Set(&g_CutscenePosition, Q12(0.0f), Q12(0.0f), Q12(280.0f));

    WorldObject_ModelNameSet(&D_800E23B0[0], "IN_BLD1_");
    WorldObject_ModelNameSet(&D_800E23D0[0], "IN1_HIDE");
    WorldObject_ModelNameSet(&D_800E23F0[0], "BRK_BLD1");
    WorldObject_ModelNameSet(&D_800E23F0[1], "BRK_GLS1");
    WorldObject_ModelNameSet(&D_800E23F0[2], "BRK_GLS2");
    WorldObject_ModelNameSet(&D_800E2450[0], "OUT1_HID");
    WorldObject_ModelNameSet(&D_800E2450[1], "OUT_BLD_");

    WorldObjectPositionInit(&g_EventThing_KitchenKnife.position_1C, 5.09f, -1.01f, 274.12f, 0.0f, 32.0f, 0.0f); 
    WorldObject_ModelNameSet(&g_EventThing_KitchenKnife.object_0, "KNIFE_HI");

    WorldObjectPositionInit(&g_EventThing_Flashlight.position_1C, 5.18f, -1.0f, 267.28f, -3.0f, 111.0f, 0.0f);
    WorldObject_ModelNameSet(&g_EventThing_Flashlight.object_0, "FLASH_HI");

    WorldObjectPositionInit(&g_EventThing_Map.position_1C, 5.24f, -1.0f, 267.21f, 0.0f, 57.0f, 0.0f);
    WorldObject_ModelNameSet(&g_EventThing_Map.object_0, "MAP_HIDE");

    WorldObjectPositionInit(&g_EventThing_PocketRadio.position_1C, 2.31f, -0.6f, 273.95f, 0.0f, 147.0f, 0.0f);
    WorldObject_ModelNameSet(&g_EventThing_PocketRadio.object_0, "RADIO_HI");

    if (Savegame_EventFlagGet(EventFlag_40) && !Savegame_EventFlagGet(EventFlag_47))
    {
        g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);

        Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0[0], NO_VALUE, NULL, NULL);

        if (Savegame_EventFlagGet(EventFlag_M0S01_PickupMap))
        {
            func_80088D0C();
            Chara_Spawn(Chara_AirScreamer, 0, Q12(1048566.0f), Q12(280.0f), FP_ANGLE(0.0f), 12);
            func_800D3A3C(&g_SysWork.npcs_1A0[0]);

            Fs_QueueStartRead(FILE_ANIM_CAFE2_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
        }
    }

    if (Savegame_EventFlagGet(EventFlag_159) && !Savegame_EventFlagGet(EventFlag_134))
    {
        func_8003ED74(6, 3);
    }

    g_Timer0 = Q12(0.0f);
    D_800E2560 = 0;

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800DCCF4
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();
    s32  temp_a1;
    s32  var_a2;
    s32* ptr;

    if (!Savegame_EventFlagGet(EventFlag_M0S01_PickupMap))
    {
        g_WorldGfx_ObjectAdd(&g_EventThing_Map.object_0, &g_EventThing_Map.position_1C.position_0, &g_EventThing_Map.position_1C.rotation_C);
    }

    if (!Savegame_EventFlagGet(EventFlag_M0S01_PickupFlashlight))
    {
        g_WorldGfx_ObjectAdd(&g_EventThing_Flashlight.object_0, &g_EventThing_Flashlight.position_1C.position_0, &g_EventThing_Flashlight.position_1C.rotation_C);
    }

    if (!Savegame_EventFlagGet(EventFlag_M0S01_PickupPocketRadio))
    {
        g_WorldGfx_ObjectAdd(&g_EventThing_PocketRadio.object_0, &g_EventThing_PocketRadio.position_1C.position_0, &g_EventThing_PocketRadio.position_1C.rotation_C);
    }

    if (!Savegame_EventFlagGet(EventFlag_M0S01_PickupKitchenKnife))
    {
        g_WorldGfx_ObjectAdd(&g_EventThing_KitchenKnife.object_0, &g_EventThing_KitchenKnife.position_1C.position_0, &g_EventThing_KitchenKnife.position_1C.rotation_C);
    }

    if (Savegame_EventFlagGet(EventFlag_M0S01_PickupKitchenKnife) && Savegame_EventFlagGet(EventFlag_M0S01_PickupMap))
    {
        Savegame_EventFlagSet(EventFlag_43);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_43);
    }

    if (Savegame_EventFlagGet(EventFlag_47))
    {
        CutsceneObjects_Add(2);
    }
    else if (Savegame_EventFlagGet(EventFlag_45) && !Savegame_EventFlagGet(EventFlag_46))
    {
        CutsceneObjects_Add(1);
    }
    else
    {
        CutsceneObjects_Add(0);
    }

    if (Savegame_EventFlagGet(EventFlag_M0S01_PickupMap) && !Savegame_EventFlagGet(EventFlag_42))
    {
        if (Savegame_EventFlagGet(EventFlag_41))
        {
            temp_a1 = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Model_AnimDurationGet(&g_SysWork.npcs_1A0[0].model_0), Q12_SHIFT);

            ptr = &g_Timer0;
            if (temp_a1 < Q12(25.0f))
            {
                var_a2 = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Model_AnimDurationGet(&g_SysWork.npcs_1A0[0].model_0), Q12_SHIFT);
            }
            else
            {
                var_a2 = Q12(25.0f);
            }
            *ptr = var_a2;

            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "BIRD",
                                   g_Timer0, (s_DmsHeader*)FS_BUFFER_11);

            if (g_Timer0 >= Q12(25.0f) ||
                ABS(g_SysWork.player_4C.chara_0.position_18.vx - Q12(4.586f)) > Q12(0.7f) ||
                ABS(g_SysWork.player_4C.chara_0.position_18.vz - Q12(267.2852f)) > Q12(0.7f))
            {
                Savegame_EventFlagSet(EventFlag_42);
                vcReturnPreAutoCamWork(1);

                g_SysWork.npcs_1A0[0].position_18.vy = Q12(-10.0f);
                g_SysWork.npcs_1A0[0].position_18.vz = Q12(280.0f);
            }
        }
        else if (g_SysWork.player_4C.chara_0.position_18.vx != Q12(4.586f) ||
                 g_SysWork.player_4C.chara_0.position_18.vz != Q12(267.2852f) ||
                 g_SysWork.player_4C.chara_0.rotation_24.vy != FP_ANGLE(90.0f) ||
                 D_800E2560 > Q12(7.5f))
        {
            Savegame_EventFlagSet(EventFlag_41);
            func_800D3AC0(&g_SysWork.npcs_1A0[0]);
        }
        else
        {
            D_800E2560 += g_DeltaTime0;
        }
    }

    if (Savegame_EventFlagGet(EventFlag_47))
    {
        if (g_SysWork.npcs_1A0[0].model_0.charaId_0 == Chara_AirScreamer && g_SysWork.npcs_1A0[0].health_B0 == NO_VALUE)
        {
            Savegame_EventFlagSet(EventFlag_48);
            Savegame_EventFlagClear(EventFlag_49);
            Savegame_EventFlagClear(EventFlag_50);
        }
    }

    if (Savegame_EventFlagGet(EventFlag_52))
    {
        if (g_SysWork.field_22A0 & (1 << 6))
        {
            Sd_EngineCmd(Sfx_Unk1321);
            Sd_EngineCmd(Sfx_Unk1322);
        }

        func_8005DE0C(Sfx_Unk1321, &D_800DE154, D_800E23A1, 0x10000, 0);
        func_8005DE0C(Sfx_Unk1322, &D_800DE154, D_800E23A1, 0x10000, 0);

        Savegame_EventFlagSet(EventFlag_52);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 7, -1, 7))
    {
        if (!Savegame_EventFlagGet(EventFlag_M0S01_HealthDrink0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &D_800DE12C.position_0, &D_800DE12C.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 7, -1, 7))
    {
        if (!Savegame_EventFlagGet(EventFlag_M0S01_HealthDrink1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &D_800DE140.position_0, &D_800DE140.rotation_C);
        }
    }
}

void CutsceneObjects_Add(s32 arg0) // 0x800DD2EC
{
    static const SVECTOR3 DEFAULT_ROT = {};

    s32 i;

    if (arg0 == 0)
    {
        for (i = 0; i < 1; i++)
        {
            g_WorldGfx_ObjectAdd(&D_800E23D0[i], &g_CutscenePosition, &DEFAULT_ROT);
        }

        for (i = 0; i < 1; i++)
        {
            g_WorldGfx_ObjectAdd(&D_800E23B0[i], &g_CutscenePosition, &DEFAULT_ROT);
        }

        return;
    }

    if (arg0 == 1)
    {
        for (i = 0; i < 2; i++)
        {
            g_WorldGfx_ObjectAdd(&D_800E2450[i], &g_CutscenePosition, &DEFAULT_ROT);
        }

        return;
    }

    for (i = 0; i < 1; i++)
    {
        g_WorldGfx_ObjectAdd(&D_800E23D0[i], &g_CutscenePosition, &DEFAULT_ROT);
    }

    for (i = 0; i < 3; i++)
    {
        g_WorldGfx_ObjectAdd(&D_800E23F0[i], &g_CutscenePosition, &DEFAULT_ROT);
    }
}

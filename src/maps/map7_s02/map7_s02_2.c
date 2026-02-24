#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map7/map7_s02.h"
#include "maps/characters/bloody_lisa.h"
#include "maps/characters/dahlia.h"
#include "maps/characters/ghost_child_alessa.h"
#include "maps/characters/kaufmann.h"
#include "maps/characters/lisa.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D8C74

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D8C88

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D8CCC

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D8CE4

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D8CF0

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D8D04

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D8D18

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D8D2C

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D8E38

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D949C

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D94B0

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D94C4

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D95C0

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D9654

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D96F4

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D9754

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D9764

void func_800D97FC(s32 arg0) // 0x800D97FC
{
    (arg0 != 0) ? func_800D9864() : sharedFunc_800D0110_7_s00();
}

void func_800D9830(s32 arg0) // 0x800D9830
{
    (arg0 != 0) ? func_800D98E4() : sharedFunc_800D0110_7_s00();
}

void func_800D9864(void) // 0x800D9864
{
    s32 var;

    if (g_SavegamePtr->mapRoomIdx_A5 == 3)
    {
        var = 15;
    }
    else if (Savegame_EventFlagGet(EventFlag_481))
    {
        if (!Savegame_EventFlagGet(EventFlag_574))
        {
            Savegame_EventFlagSet(EventFlag_574);
            var = 1;
        }
        else
        {
            var = 22;
        }
    }
    else
    {
        var = 14;
    }

    Bgm_TrackChange(var);
}

void func_800D98E4(void) // 0x800D98E4
{
    Bgm_TrackChange(Savegame_EventFlagGet(EventFlag_391) ? 40 : 35);
}

#include "maps/shared/sharedFunc_800D0110_7_s00.h" // 0x800D9924

void func_800DA1A8(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800DA1B0

const char* MAP_MESSAGES[] = {
#include "maps/shared/mapMsg_common.h"
    "\t\tSame_thing... ~E ",
    "~L4 ~C3 Investigation_stalled. ~N\n\t[PTV]_dealers_still_at_large. ~N\n\t~N\n\tSuspicious_deaths_continue. ~N\n\tLike_anti-drug_Mayor, ~N\n\tnarcotics_officer_dies_of ~N\n\tsudden_heart_failure_of ~N\n\tunknown_origin. ~E ",
    "\t\tAre_there_others? ~N\n\t\tIt's_pretty_old... ",
    "~L4 ~C3 Fire_broke_out_in_town. ~N\n\t6_homes_destroyed. ~N\n\t~N\n\tCharred_body ~N\n\tof_Alessa_Gillespie(7) ~N\n\tfound_in_aftermath. ~N\n\t~N\n\tCause_of_fire_currently_under ~N\n\tinvestigation. ",
    "~L4 ~C3 Investigations_show_source ~N\n\tas_basement_of_Gillespie_home. ~N\n\tBlaze_now_believed_caused_by ~N\n\tmalfunction_of_antiquated ~N\n\tboiler. ~E ",
    "\tThe_date_of_the_blaze... ",
    "\tit's_the_same_day ~N\n\twe_found_Cheryl! ~E ",
    "\tThere's_a_place_mark ~N\n\tin_the_book.. ~E ",
    "~L4 ~C3 WHITE_CLAUDIA. ~N\n\t~N\n\tPerennial_herb_found_near_water. ~N\n\tReaches_height_of_10_to_15_in. ~N\n\tOblong_leaves,_white_blossoms. ",
    "~L4 ~C3 Seeds_contain_hallucinogen. ~N\n\tAncient_records_show_it_was ~N\n\tused_for_religious_ceremonies. ~N\n\tThe_hallucinogenic_effect ~N\n\twas_key. ~E ",
    "~L4 ~C3 Ask_doctor_to_let_me_quit_being ~N\n\tin_charge_of_that_patient. ~N\n\t~N\n\tIt's_too_weird. ~E ",
    "~L4 ~C3 The_room_is_filled_with_insects. ~N\n\t~N\n\tEven_with_doors ~N\n\tand_windows_shut ~N\n\tthey_get_in_to_spite_me. ~N\n\t~N\n\tTo_the_hospital... ~E ",
    "~L4 ~C3 Still_alive, ~N\n\tbut_with_wounds_that_won't_heal. ~E ",
    "~L4 ~C3 Blood_and_pus_flow_from ~N\n\tthe_bathroom_faucet. ~N\n\t~N\n\tI_try_to_stop_it, ~N\n\tbut_it_won't_turn_off. ~E ",
    "~L4 ~C3 Feeling_bad. ~N\n\tNeed_to_throw_up. ~N\n\tBut_nothing_comes_out. ~N\n\tVomiting_only_bile. ~E ",
    "~L4 ~C3\tNeed_drug. ~E ",
    "~L4 ~C3 Told_the_doctor_I_quit. ~N\n\tWon't_work_at_that ~N\n\thospital_anymore. ~E ",
    "~J0(0.7)\t_ ",
    "~J2(1.5)\tWhat_is_it? ",
    "~J2(2.7)\tStill_has_an_unusually ~N\n\t\t\thigh_fever... ",
    "~J2(2.6)\tEyes_don't_open... ~N\n\t\t\tgetting_a_pulse... ",
    "~J2(2.8)\tBut_just_barely_breathing. ",
    "~J2(2.3)\tHer_skin_is_all_charred! ",
    "~J2(1.2)\tEven_when_I_change ~N\n\t\t\tthe_bandages, ",
    "~J2(3.8)\tthe_blood_and_pus_just_start ~N\n\t\t\toozing_through! ",
    "~J2(5.9)\tWhy... ~N\n\t\t\tWhat_is_keeping_that_child_alive? ",
    "~J2(2.8)\tI..._can't_stand_it ~N\n\t\t\tany_longer... ",
    "~J2(3.3)\tI_won't_tell_a_soul ~N\n\t\t\t...promise. ",
    "~J2(2.0)\tSo_please... ",
    "~J2(1.0)\t_ ~E ",
    "~J0(1.3)\t",
    "~J0(3.3)\t~E ",
    "~J1(6.4)\tEverything_is_going ~N\n\t\t\taccording_to_plan. ~N\n\t\t\tSheltered_in_the_womb. ",
    "~J1(1.8)\tBut_it's_not_done_yet. ",
    "~J1(4.5)\tHalf_the_soul_is_lost. ~N\n\t\t\tThat_is_why_the_seed ~N\n\t\t\tlies_dormant. ",
    "~J1(3.6)\tAnd_what_soul_remains ~N\n\t\t\tcaptured_in_that_husk, ",
    "~J1(3.7)\tis_buried_deep_down ~N\n\t\t\tin_the_subconscious. ",
    "~J1(2.6)\tAre_you_trying_to_say ~N\n\t\t\tit_won't_work!? ",
    "~J1(2.0)\tThat_wasn't_our_agreement! ",
    "~J1(4.0)\tNo,_no. ~N\n\t\t\tThese_are_just_stalling_tactics. ",
    "~J1(4.4)\tIf_we_lend_a_hand, ~N\n\t\t\twe_will_be_able_to_get_power. ",
    "~J1(5.4)\tNever_fear. ~N\n\t\t\tThe_promise_shall_not_be_broken. ",
    "~J1(5.0)\tBut_the_power_we_could ~N\n\t\t\tdraw_now_would_be ~N\n\t\t\tvery_weak;_almost_nothing. ",
    "~J1(3.2)\tUnless_we_get_the_other ~N\n\t\t\thalf_of_the_soul... ",
    "~J1(3.1)\tWe'll_use_a_magical_spell. ",
    "~J1(6.0)\tFeeling_this_child's_pain, ~N\n\t\t\tit's_sure_to_come. ",
    "~J1(2.8)\tBut_that_will_take_time... ~E ",
    "~J0(2.9)\t",
    "~J0(3.0)\tNo! ~N\n\t\t\tI_don't_want_to! ",
    "~J0(2.7)\tDo_what_mommy_tells_you,_now. ",
    "~J0(6.3)\tI_just_want_you_to_lend_me ~N\n\t\t\ta_teeny_bit_of_your_power. ~N\n\t\t\tThat's_all. ",
    "~J2(1.2)\tNo! ~E ",
    "~J0(2.0)\tI_don't_want_to_do_it! ~E ",
    "~J1(5.8)\tIt_will_make_everyone_happy... ~N\n\t\t\tand_it's_for_your_own_good,_too. ",
    "~J1(4.3)\tOh,_but_mommy. ~N\n\t\t\tI_just_want_to_be_with_you. ",
    "~J1(4.3)\tJust_two_of_us. ~N\n\t\t\tPlease_understand. ~E ",
    "~J1(7.1)\tOh,_yes,_I_see... ~N\n\t\t\tMaybe_mommy_has_been_wrong. ",
    "~J1(1.3)\tMommy... ",
    "~J1(5.3)\tWhy_didn't_I_see_this_before? ~N\n\t\t\tThere's_no_reason_to_wait... ",
    "~J1(7.2)\tHerein_lies_the_mother's_womb, ~N\n\t\t\tcontaining_the_power ~N\n\t\t\tto_create_life. ",
    "~J1(4.2)\tI_could_have_done_it_all_myself. ",
    "~J1(1.6)\tMommy? ~E ",
    "\tUsed_the_ ~C2 Key_of_[Bethor] ~C7 . ~E ",
    "\tUsed_the_ ~C2 Key_of_[Aratron] ~C7 . ~E ",
    "\tThere_is_a_ ~C2 Key_of_[Bethor] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Key_of_[Aratron] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_an_ ~C2 Ankh ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Dagger_of_Melchior ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Disk_of_Ouroboros ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThe_generator_is_working. ~N\n\tDo_you_want_to_press_the_switch? ~S4 ",
    "\tThe_generator_is_stopped. ~N\n\tDo_you_want_to_press_the_switch? ~S4 ",
    "\tIt's_locked. ",
    "\tThe_word,_[Bethor] ~N\n\tis_carved_on_the_door. ~E ",
    "\tIt's_locked. ",
    "\tThe_word,_[Aratron] ~N\n\tis_carved_on_the_door. ~E ",
    "\tJelly_beans. ~N\n\tDo_you_want_to_open_the_bag? ~S4 ",
    "\tThe_chain_is_missing_a_link. ~E ",
    "\tThe_chain_is_fixed ~N\n\twith_the_ring. ~E ",
    "\tThere_is_a_ ~C2 Ring_of_contract ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Screwdriver ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Camera ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_an_ ~C2 Amulet_of_Solomon ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Crest_of_Mercury ~C7 . ~N\n\tTake_it? ~S4 ",
    "~C3\tGo_home. ",
    "~C3\tThief. ",
    "~C3\tDrop_dead. ~E ",
    "\t_ ~E ",
    "~C3 Names_engraved ~N\n\tOn_a_lithograph. ~N\n\tThe_Grim_Reaper's_list. ",
    "~C3 Yes,_the_headcount_is_set ~N\n\tYoung_and_old_lined_up ~N\n\tIn_order_of_age. ",
    "~C3 Then,_the_pathway_opens ~N\n\tAwaiting_them,_the_frenzied ~N\n\tUproar,_the_feast_of_death! ~E ",
    "\tThere_is_a_key. ",
    "\tElectricity_is_flowing_to_the_key. ~N\n\tI'll_get_shocked_if_I_grab_it_now. ~E ",
    "~C3\tThe_light_to_the_future. ~E ",
    "~C3\tThe_light_illuminating ~N\n\t\t_the_darkness. ~E ",
    "\tBird_cage._It's_empty. ~E ",
    "\tA_steel_plate ~N\n\tis_screwed_to_the_wall. ~E ",
    "~J0(1.2)\tHarry? ~E ",
    "~J1(2.6)\tLisa... ~N\n\t\t\tWhat's_the_matter_with_you? ",
    "~J1(1.8)\tI_get_it_now... ",
    "~J1(4.0)\tWhy_I'm_still_alive_even ~N\n\t\t\tthough_everyone_else's_dead. ",
    "~J1(4.0)\tI'm_not_the_only_one ~N\n\t\t\twho's_still_walking_around. ",
    "~J1(1.7)\tI'm_the_same_as_them. ",
    "~J1(2.8)\tI_just_hadn't_noticed_it_before. ~E ",
    "~J1(1.3)\tLisa? ",
    "~J1(3.6)\tStay_by_me,_Harry. ~N\n\t\t\tPlease. ",
    "~J1(3.3)\tI'm_so_scared. ~N\n\t\t\tHelp_me... ~E ",
    "~J0(2.4)\tSave_me_from_them. ",
    "~J0(4.0)\tPlease...__Harry... ~E ",
    "~J0(8.9)\t~E ",
    "\t[Alessa] ~E ",
    "\tUsed_the_ ~C2 Amulet_of_Solomon ~C7 . ~E ",
    "\tUsed_the_ ~C2 Crest_of_Mercury ~C7 . ~E ",
    "\tUsed_the_ ~C2 Ankh ~C7 . ~E ",
    "\tUsed_the_ ~C2 Dagger_of_Melchior ~C7 . ~E ",
    "\tUsed_the_ ~C2 Disk_of_Ouroboros ~C7 . ~E ",
    "~C3 thou_possess_them ~N\n\tto_guard_thy_spirit ~N\n\tevoke_five_rites ~N\n\tunveil_thy_fate ~E ",
    "\tThere's_a_severed_power_line. ~N\n\tNothing_special_here_either. ~E ",
    "\tThe_elevator_doesn't ~N\n\tappear_to_be_working. ~E ",
    "\tThere's_a_clock ~N\n\twith_a_broken face. ~E ",
    "\tUsed_the_ ~C2 Ring_of_contract ~C7 . ~E ",
    "\tNone_of_this_stuff_is_of_any_use. ~E ",
    "\tJust_a_wall. ~E ",
    "\tThere_are_specimen_of ~N\n\tbutterflies_and_moths ~N\n\thanging_on_the_wall. ~E ",
    "\tA_girl's_clothing_hangs ~N\n\ton_the_wall. ",
    "\tSix,_maybe_seven... ~N\n\tMust_be_a_kid_about_that_age. ~E ",
    "\tCards_are_scattered ~N\n\ton_the_floor. ~E ",
    "\tThere_are_dolls_on_the_floor. ~E ",
    "\tA_child's_drawings_are_scattered ~N\n\ton_the_floor. ~E ",
    "\tNothing_unusual. ~E ",
    "\tThere_are_old_fairy_tales, ~N\n\tpicture_books_of_animals, ~N\n\tand_plants_on_the_shelf. ~E ",
    "\tNone_of_this_stuff_is_of_any_use. ~E ",
    "~L4 ~C3 Help_me... ~E ",
    "\tThere_is_a_diary_on_the_floor. ~E ",
    "\tNothing_helpful. ~E ",
    "\tLooks_like_an_altar. ~N\n\tWonder_what_they_worship? ~E ",
    "\tThe_floors_and_walls_are_covered ~N\n\twith_graffiti. ~E ",
    "\tVCR._It's_old_but_usable. ~E ",
    "\tA_body_is_laid_out_on_the_bed. ~N\n\tDon't_feel_like_checking_this_out. ~E ",
    "\tThere's_a_bottle_filled ~N\n\twith_some_kind_of_drug. ~N\n\tBetter_leave_it. ~E ",
    "\tThere_are_some_empty_bottles. ~E ",
    "\tNothing_special_in_the_box. ~N\n\tNothing_to_worry_about. ~E ",
    "\tNothing_inside. ~E ",
    "\tNothing_useful_in_the_boxes. ~E ",
    "\tThere's_a_botanical ~N\n\treference_book. ~N\n\tDon't_need_to_read_it_now. ~E "
};

void func_800DA248(void) // 0x800DA248
{
    s_FsImageDesc charaTex;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 4 && g_SysWork.sysStateStep_C[0] <= 20)
    {
        SysWork_StateStepSet(0, 22);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800EB6B0 = 0;

            Fs_QueueStartRead(FILE_ANIM_HBM7_SLS_ANM, FS_BUFFER_4);
            Fs_QueueStartRead(FILE_ANIM_NURSE1_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();

            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
            D_800EB6B4 = 0;
            Anim_CharaTypeAnimInfoClear();

            Chara_Load(0, Chara_Lisa, g_SysWork.npcCoords_FC0, CHARA_FORCE_FREE_ALL, NULL, NULL);

            ScreenFade_ResetTimestep();

            g_SysWork.field_30    = 20;
            g_SysWork.pointLightIntensity_2378  = Q12(0.8f);
            g_SysWork.flags_22A4 |= SysFlag2_3;

            Game_TurnFlashlightOn();
            D_800E9ECC = 0;
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            sharedFunc_800D2EB4_0_s00();
            func_8003D03C();
            Bgm_TrackChange(4);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80087EDC(4);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
            break;

        case 3:
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Lisa, 0, Q12(130.0f), Q12(-70.0f), Q12_ANGLE(0.0f), 3);
            SysWork_StateStepIncrement(0);

        case 4:
            Map_MessageWithAudio(111, &D_800EB6B0, &D_800E9CE4);
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(20.0f), true, false);
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 72, false);
            SysWork_StateStepIncrement(0);

        case 6:
            Map_MessageWithAudio(111, &D_800EB6B0, &D_800E9CE4);
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(20.0f), true, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(20.0f), true, true);
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            D_800EB6B4 = Q12(21.0f);
            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(112, &D_800EB6B0, &D_800E9CE4);
            break;

        case 10:
            Map_MessageWithAudio(118, &D_800EB6B0, &D_800E9CE4);
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 17, false);
            SysWork_StateStepIncrement(0);

        case 12:
            Map_MessageWithAudio(121, &D_800EB6B0, &D_800E9CE4);
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(22.0f), Q12(97.0f), false, false);
            break;

        case 13:
            SysWork_StateStepIncrement(0);

        case 14:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(22.0f), Q12(97.0f), false, true);
            break;

        case 15:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 155, false);
            SD_Call(Sfx_XaAudio568);
            SysWork_StateStepIncrement(0);

        case 16:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(22.0f), Q12(132.0f), true, true);
            break;

        case 17:
            func_80085EB8(0, g_SysWork.npcs_1A0, 18, false);
            Savegame_EventFlagSet(EventFlag_570);
            SysWork_StateStepIncrement(0);

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(133.0f), Q12(157.0f), true, true);
            break;

        case 19:
            Chara_FsImageCalc(&charaTex, Chara_BloodyLisa, 2);
            Chara_Load(1, Chara_BloodyLisa, &g_SysWork.npcCoords_FC0[30], 0, LM_BUFFER_2, &charaTex);

            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(180.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-100.0f);

            Ipd_CloseRangeChunksInit();
            SysWork_StateStepIncrement(0);

        case 20:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.5f), false);
            break;

        case 21:
            SysWork_StateStepReset();
            break;

        case 22:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 23:
            Savegame_EventFlagSet(EventFlag_571);
            SysWork_StateStepIncrement(0);

        case 24:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(180.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-100.0f);

            Ipd_CloseRangeChunksInit();
            Chara_FsImageCalc(&charaTex, Chara_BloodyLisa, 2);
            Chara_Load(1, Chara_BloodyLisa, &g_SysWork.npcCoords_FC0[30], 0, LM_BUFFER_2, &charaTex);
            Chara_ProcessLoads();
            SysWork_StateStepIncrement(0);

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_482);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            Chara_ProcessLoads();
            SD_Call(19);
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "LISA\0\0\0\0", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800EB694, &D_800EB6A4, NULL, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&D_800EB694, NULL, true);
        vcUserWatchTarget(&D_800EB6A4, NULL, true);
    }
}

void func_800DAA4C(void) // 0x800DAA4C
{
    VECTOR3  pos;
    SVECTOR3 rot;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] <= 15)
    {
        SysWork_StateStepSet(0, 17);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Fs_QueueStartRead(FILE_ANIM_NURSE2_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
            Chara_Spawn(Chara_BloodyLisa, 0, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(1.0f), 0, 3);

            D_800EB6B4 = 0;
            D_800EB6B0 = 0;
            D_800E9ECD = 0;

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 156, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(43.0f), true, true);
            break;

        case 3:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(44.0f), Q12(59.0f), true, true);
            break;

        case 4:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 157, false);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            func_8008D438();
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(60.0f), Q12(76.0f), true, true);
            Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &rot, "LIGHT", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
            Dms_CharacterGetPosRot(&pos, &rot, "L_INT", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);

            g_SysWork.pointLightRot_2370.vx = -ratan2(pos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(pos.vx - g_SysWork.pointLightPosition_2360.vx, pos.vz - g_SysWork.pointLightPosition_2360.vz));
            g_SysWork.pointLightRot_2370.vy = ratan2(pos.vx - g_SysWork.pointLightPosition_2360.vx, pos.vz - g_SysWork.pointLightPosition_2360.vz);
            g_SysWork.pointLightRot_2370.vz = Q12_ANGLE(0.0f);
            break;

        case 6:
            D_800E9ECD = 1;

            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(0.8f);

            func_8005DC1C(Sfx_Unk1336, &g_WorldObject_Door.position_1C, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(77.0f), Q12(100.0f), true, true);
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 158, false);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_8005DC1C(Sfx_Unk1337, &g_WorldObject_Door.position_1C, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 9:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(101.0f), Q12(152.0f), true, false);
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 10:
            SD_Call(4662);
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(101.0f), Q12(142.0f), false, true);
            break;

        case 12:
            SysWork_StateStepIncrement(0);

        case 13:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(101.0f), Q12(152.0f), true, false);
            SysWork_StateStepIncrementAfterFade(2, true, false, Q12(0.25f), false);
            break;

        case 14:
            if (Sd_AudioStreamingCheck())
            {
                break;
            }

            SysWork_StateStepIncrement(0);

        case 15:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 16:
            SysWork_StateStepSet(0, 19);
            break;

        case 17:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 18:
            SD_Call(19);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            SysWork_StateStepIncrement(0);
            break;

        case 19:
            GameFs_PlayerMapAnimLoad(g_SavegamePtr->mapOverlayId_A4);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            D_800EB6B4 = NO_VALUE;

            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_484);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            Game_TurnFlashlightOn();
            sharedFunc_800D2EF4_0_s00();
            func_8003D01C();
            Anim_CharaTypeAnimInfoClear();
            SysWork_StateStepIncrementAfterFade(0, false, false, Q12(1.0f), false);
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "BLS", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);

        if (D_800E9ECD != 0)
        {
            Dms_CharacterGetPosRot(&g_WorldObject_Door.position_1C, &g_WorldObject_Door.rotation_28, "ADOOR", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800EB694, &D_800EB6A4, NULL, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&D_800EB694, NULL, true);
        vcUserWatchTarget(&D_800EB6A4, NULL, true);
    }
}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800DB21C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800DB2B0

#include "maps/shared/MapEvent_DoorUnlocked.h" // 0x800DB344

void MapEvent_CommonItemTake(void) // 0x800DB3D8
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 212:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M7S01_RifleShells;
            break;

        case 213:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M7S01_HandgunBullets0;
            break;

        case 214:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M7S01_HealthDrink0;
            break;

        case 215:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M7S01_HandgunBullets1;
            break;

        case 216:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M7S01_ShotgunShells;
            break;

        case 217:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M7S01_FirstAidKit;
            break;

        case 218:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M7S01_HandgunBullets2;
            break;

        case 219:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M7S01_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800DB498(void) // 0x800DB498
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(86, Sfx_DoorLocked, &sfxPos);
}

void func_800DB52C(void) // 0x800DB52C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(88, Sfx_DoorLocked, &sfxPos);
}

void MapEvent_KeyOfBethorUse(void) // 0x800DB5C0
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_KeyOfBethor, 1);
    Map_MessageWithSfx(77, Sfx_UseKey, &sfxPos);
    Savegame_EventFlagSet(EventFlag_533);
}

void MapEvent_KeyOfAratronUse(void) // 0x800DB67C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_KeyOfAratron, 1);
    Map_MessageWithSfx(78, Sfx_UseKey, &sfxPos);
    Savegame_EventFlagSet(EventFlag_534);
}

void func_800DB738(void) // 0x800DB738
{
    const static VECTOR3 SFX_POS = { Q12(97.4f), Q12(-0.5f), Q12(-59.0f) };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_LISAVTR_TIM, false);

            D_800EB6B0 = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 146, false);
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);

            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(97.61f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-59.59f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12(0.8915f);

            Camera_PositionSet(NULL, Q12(100.56f), Q12(-1.06f), Q12(-61.53f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(97.61f), Q12(-0.73f), Q12(-59.2f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1526, &SFX_POS, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(1, 0, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_800862F8(2, 0, false);
            break;

        case 8:
            Map_MessageWithAudio(32, &D_800EB6B0, &D_800E9CFC);
            func_800862F8(2, 0, false);

            if (g_SysWork.sysStateStep_C[0] == 8 &&
                g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.skip_4 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SD_Call(19);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            func_800862F8(2, 0, false);
            break;

        case 10:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 147, false);
            SysWork_StateStepIncrement(0);
            break;

        case 11:
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 13:
            func_8005DC1C(Sfx_Unk1526, &SFX_POS, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 14:
            func_80086D04(&g_SysWork.playerWork_4C.player_0);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            func_80086470(3, InventoryItemId_VideoTape, 1, false);
            break;
    }
}

void func_800DBB34(void) // 0x800DBB34
{
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 1 && g_SysWork.sysStateStep_C[0] <= 13)
    {
        SysWork_StateStepSet(0, 14);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Anim_CharaTypeAnimInfoClear();
            Chara_Load(0, Chara_GhostChildAlessa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);

            g_SysWork.field_30 = 20;

            ScreenFade_ResetTimestep();
            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);
            func_8008D438();
            Camera_PositionSet(NULL, Q12(20.09f), Q12(-0.9f), Q12(-97.78f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(18.5f), Q12(0.2f), Q12(-101.28f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 2:
            func_800868DC(3);
            func_800868DC(4);
            func_800868DC(5);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 4:
            Camera_LookAtSet(NULL,
                             func_800868F4(Q12(-0.7901f), Q12(3.0f), 3) + Q12(18.5f),
                             func_800868F4(Q12(-2.1299f), Q12(3.0f), 4) + Q12(0.2f),
                             func_800868F4(Q12(0.45f), Q12(3.0f), 5) + Q12(-101.28f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
            SysWork_StateStepIncrementDelayed(Q12(3.0f), false);
            break;

        case 5:
            func_800868DC(3);
            func_800868DC(4);
            func_800868DC(5);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_GhostChildAlessa, 0, Q12(21.2f), Q12(-100.5f), Q12_ANGLE(180.0f), 3);
            SysWork_StateStepIncrement(0);
            break;

        case 6:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);
            SD_Call(Sfx_XaAudio603);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 8:
            Camera_LookAtSet(NULL,
                             func_800868F4(Q12(3.74f), Q12(3.4f), 3) + Q12(17.71f),
                             func_800868F4(Q12(0.3902f), Q12(3.4f), 4) + Q12(-1.93f),
                             func_800868F4(Q12(-0.6602f), Q12(3.4f), 5) + Q12(-100.83f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
            SysWork_StateStepIncrementDelayed(Q12(3.4f), false);
            break;

        case 9:
            func_800868DC(3);
            func_800868DC(4);
            func_800868DC(5);
            SysWork_StateStepIncrement(0);
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 11:
            Camera_LookAtSet(NULL,
                             func_800868F4(Q12(-0.1302f), Q12(0.6f), 3) + Q12(21.45f),
                             func_800868F4(Q12(1.21f), Q12(0.6f), 4) + Q12(-1.54f),
                             func_800868F4(Q12(-0.05f), Q12(0.6f), 5) + Q12(-101.49f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 12:
            g_SysWork.npcs_1A0[0].timer_C6 += Q12_MULT_PRECISE(Q12(0.25f), g_DeltaTime);
            if (g_SysWork.npcs_1A0[0].timer_C6 > Q12(1.0f))
            {
                func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 13:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 13)
            {
                SysWork_StateStepReset();
            }
            break;

        case 14:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 15:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            SD_Call(19);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_548);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);
            func_8008D448();
            Anim_CharaTypeAnimInfoClear();
            break;
    }
}

void MapEvent_AnkhTake(void) // 0x800DC120
{
    Event_ItemTake(InventoryItemId_Ankh, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S02_PickupAnkh, 81);
}

void func_800DC14C(void) // 0x800DC14C
{
    s32 i;
    s32 floorHitCount;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_JELYBEAN_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            func_800862F8(1, 0, false);
            break;

        case 3:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(true, 90, 7, 5, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 7:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 8:
            Savegame_EventFlagSet(EventFlag_556);
            g_SysWork.field_30 = 20;
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 143, false);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(61.9627f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-60.9957f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);
            SysWork_StateStepIncrement(0);
            break;

        case 9:
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(59.74f), Q12(-1.22f), Q12(-60.36f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(63.67f), Q12(-1.02f), Q12(-61.05f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 11:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(4.5f), false);
            break;

        case 13:
            D_800E9ED4 = Q12(-1.294f);
            D_800E9ED0 = 0;
            func_8005DC1C(Sfx_Unk1662, &QVECTOR3(62.3f, -1.45f, -61.07f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 14:
            D_800E9ED0 += g_GravitySpeed;
            if (D_800E9ED0 > Q12(5.0f))
            {
                D_800E9ED0 = Q12(5.0f);
            }

            floorHitCount = 0;
            for (i = 0; i < 16; i++)
            {
                g_WorldObject_Beans[i].position_1C.vy += Q12_MULT_PRECISE(g_DeltaTime, D_800E9ED0 + FP_FROM(D_800EBA14[i] * Math_Sin(D_800EB9F4[i]), Q12_SHIFT));
                g_WorldObject_Beans[i].position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime, FP_FROM(D_800EBA14[i] * Math_Cos(D_800EB9F4[i]), Q12_SHIFT));

                if (g_WorldObject_Beans[i].position_1C.vy > 0)
                {
                    g_WorldObject_Beans[i].position_1C.vy = 0;
                    floorHitCount++;
                }

                WorldGfx_ObjectAdd(&g_WorldObject_Beans[i].object_0, &g_WorldObject_Beans[i].position_1C, &g_WorldObject_Beans[i].rotation_28);
            }

            if (D_800E9ED4 < 0)
            {
                D_800E9ED4 += Q12_MULT_PRECISE(g_DeltaTime, D_800E9ED0);
                if (D_800E9ED4 > 0)
                {
                    func_8005DC1C(Sfx_Unk1651, &QVECTOR3(62.3f, 0.0f, -61.07f), Q8_CLAMPED(0.5f), 0);
                }
            }

            if (floorHitCount == 16)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 15:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            break;
    }
}

void func_800DC778(void) // 0x800DC778
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_KeyOfBethor, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            func_80086470(1, InventoryItemId_KeyOfBethor, 0, false);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_M7S02_PickupKeyOfBethor);

            if (Gfx_PickupItemAnimate(InventoryItemId_KeyOfBethor))
            {
                MapMsg_DisplayAndHandleSelection(true, 79, 5, 6, 0, false);
            }
            break;

        case 5:
            func_80086470(3, InventoryItemId_KeyOfBethor, 1, false);
            SysWork_StateStepSet(0, 7);
            break;

        case 6:
            Savegame_EventFlagClear(EventFlag_M7S02_PickupKeyOfBethor);
            SysWork_StateStepIncrement(0);

        case 7:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DC94C(void) {}

void func_800DC954(void) // 0x800DC954
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_CHAINRF1_TIM, false);
            D_800E9ED6 = 0;
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            func_800862F8(1, 0, false);
            break;

        case 3:
            func_800862F8(3, 0, false);
            SysWork_StateStepIncrementAfterFade(false, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            func_800862F8(8, FILE_TIM_CHAINRF2_TIM, false);
            func_800862F8(2, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(true, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 7:
            Sd_PlaySfx(Sfx_Unk1669, 0, Q8_CLAMPED(0.5f));
            SysWork_StateStepIncrement(0);

        case 8:
            Gfx_BackgroundSpritesTransition(&g_ItemInspectionImg, &D_800A9A04, g_SysWork.field_28);

            g_SysWork.field_28 += Q12(0.0625f);
            if (g_SysWork.field_28 > Q12(1.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 9:
            MapMsg_DisplayAndHandleSelection(false, 134, 0, 0, 0, false);
            func_800862F8(5, 0, false);
            break;

        case 10:
            func_800862F8(5, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            func_800862F8(6, 0, false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_552);
            SysWork_StateStepIncrementAfterFade(false, false, 0, Q12(0.0f), false);
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 4 && g_SysWork.sysStateStep_C[0] < 11)
    {
        if (D_800E9ED6 == 0 && !Savegame_EventFlagGet(EventFlag_555))
        {
            Sd_PlaySfx(Sfx_Unk1664, 0, Q8_CLAMPED(0.875f));
            D_800E9ED6 = Rng_GenerateInt(Q12(1.2f), Q12(2.8f) - 1);
        }
        else
        {
            D_800E9ED6 = MAX(0, D_800E9ED6 - g_DeltaTime);
        }
        return;
    }

    Sd_SfxStop(Sfx_Unk1664);
}

void func_800DCD00(void) // 0x800DCD00
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            if (Savegame_EventFlagGet(EventFlag_552))
            {
                func_800862F8(0, FILE_TIM_CHAINRF2_TIM, false);
            }
            else
            {
                func_800862F8(0, FILE_TIM_CHAINRF1_TIM, false);
            }

            D_800E9ED8 = 0;
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            func_800862F8(1, 0, false);
            break;

        case 3:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);

            if (D_800E9ED8 == 0 && !Savegame_EventFlagGet(EventFlag_555))
            {
                Sd_PlaySfx(Sfx_Unk1664, 0, 224);
                D_800E9ED8 = Rng_GenerateInt(Q12(1.2f), Q12(2.8f) - 1);
            }
            else
            {
                D_800E9ED8 = (D_800E9ED8 - g_DeltaTime) >= 0 ? D_800E9ED8 - (s16)g_DeltaTime : 0;
            }
            break;

        case 4:
            Sd_PlaySfx(Sfx_Unk1665, 0, 128);
            SysWork_StateStepIncrement(0);

        case 5:
            if (Savegame_EventFlagGet(EventFlag_552))
            {
                MapMsg_DisplayAndHandleSelection(false, 92, 0, 0, 0, false);
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 91, 0, 0, 0, false);
            }

            func_800862F8(2, 0, false);

            if (D_800E9ED8 == 0 && !Savegame_EventFlagGet(EventFlag_555))
            {
                Sd_PlaySfx(Sfx_Unk1664, 0, 224);
                D_800E9ED8 = Rng_GenerateInt(Q12(1.2f), Q12(2.8f) - 1);
            }
            else
            {
                D_800E9ED8 = (D_800E9ED8 - g_DeltaTime) >= 0 ? D_800E9ED8 - (s16)g_DeltaTime : 0;
            }
            break;

        case 6:
            func_800862F8(2, 0, false);
            func_8008605C(EventFlag_M7S02_PickupDaggerOfMelchior, 14, 7, false);
            break;

        case 7:
            func_80086470(0, InventoryItemId_DaggerOfMelchior, 0, false);
            SysWork_StateStepIncrement(0);

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

            if (D_800E9ED8 == 0 && !Savegame_EventFlagGet(EventFlag_555))
            {
                Sd_PlaySfx(Sfx_Unk1664, 0, 224);
                D_800E9ED8 = Rng_GenerateInt(Q12(1.2f), Q12(2.8f) - 1);
            }
            else
            {
                D_800E9ED8 = (D_800E9ED8 - g_DeltaTime) >= 0 ? D_800E9ED8 - (s16)g_DeltaTime : 0;
            }

            if (g_SysWork.sysStateStep_C[0] != 8)
            {
                Sd_SfxStop(Sfx_Unk1664);
            }
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 10:
            func_80086470(1, InventoryItemId_DaggerOfMelchior, 0, false);
            break;

        case 11:
            if (Gfx_PickupItemAnimate(InventoryItemId_DaggerOfMelchior) != false)
            {
                MapMsg_DisplayAndHandleSelection(true, 82, 12, 13, 0, false);
            }

            Savegame_EventFlagSet(EventFlag_M7S02_PickupDaggerOfMelchior);
            break;

        case 12:
            func_80086470(3, InventoryItemId_DaggerOfMelchior, 1, false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 13:
            Savegame_EventFlagClear(EventFlag_M7S02_PickupDaggerOfMelchior);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 14:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

            if (D_800E9ED8 == 0 && !Savegame_EventFlagGet(EventFlag_555))
            {
                Sd_PlaySfx(Sfx_Unk1664, 0, 224);
                D_800E9ED8 = Rng_GenerateInt(Q12(1.2f), Q12(2.8f) - 1);
            }
            else
            {
                D_800E9ED8 = (D_800E9ED8 - g_DeltaTime) >= 0 ? D_800E9ED8 - (s16)g_DeltaTime : 0;
            }
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Sd_SfxStop(Sfx_Unk1664);
            break;
    }
}

void func_800DD2D4(void) // 0x800DD2D4
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

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8005DC1C(Sfx_Unk1667, &QVECTOR3(21.1f, -1.5f, -60.75f), Q8_CLAMPED(0.5f), 0);
            Fs_QueueStartRead(FILE_ANIM_KITCHEN1_DMS, FS_BUFFER_11);
            Savegame_EventFlagSet(EventFlag_557);

            D_800EB6B4 = NO_VALUE;

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
            DmsHeader_FixOffsets(FS_BUFFER_11);
            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            Anim_CharaTypeAnimInfoClear();
            Chara_Load(0, Chara_Bloodsucker, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 144, false);

            D_800EB6B4 = 0;

            SysWork_StateStepIncrement(0);

        case 4:
            if (g_SysWork.playerWork_4C.player_0.model_0.anim_4.status_0 & 1)
            {
                D_800EB6B4 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - Q12(Player_AnimGetSomething());
                if (D_800EB6B4 > Q12(29.0f))
                {
                    D_800EB6B4 = Q12(29.0f);
                    SysWork_StateStepIncrement(0);
                }
            }
            break;

        case 5:
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Bloodsucker, 64, Q12(21.5f), Q12(-60.8f), Q12_ANGLE(-90.0f), 17);
            SD_Call(Sfx_Unk1668);
            Savegame_EventFlagSet(EventFlag_573);

            g_WorldObject_Dor[0].rotation_28.vy = Q12_ANGLE(25.0f);
            g_WorldObject_Dor[1].rotation_28.vy = Q12_ANGLE(58.0f);
            g_WorldObject_Dor[2].rotation_28.vy = Q12_ANGLE(-50.0f);
            g_WorldObject_Dor[3].rotation_28.vy = Q12_ANGLE(-15.0f);

            SysWork_StateStepIncrement(0);

        case 6:
            D_800EB6B4 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - Q12(Player_AnimGetSomething());

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

            if (D_800EB6B4 > Q12(39.0f))
            {
                D_800EB6B4 = Q12(39.0f);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 7:
            D_800EB6B4 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - Q12(Player_AnimGetSomething());
            if (D_800EB6B4 > Q12(96.0f))
            {
                SD_Call(Sfx_XaAudio635);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.0f), false);
            D_800EB6B4 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - Q12(Player_AnimGetSomething());
            break;

        case 9:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            SysWork_StateSetNext(SysState_GameOver);
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 6)
    {
        g_SysWork.npcs_1A0[0].properties_E4.player.afkTimer_E8 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - Q12(Player_AnimGetSomething());
    }

    if (D_800EB6B4 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800EB6B4, FS_BUFFER_11);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800EB694, &D_800EB6A4, NULL, D_800EB6B4, FS_BUFFER_11));
        vcUserCamTarget(&D_800EB694, NULL, true);
        vcUserWatchTarget(&D_800EB6A4, NULL, true);
    }
}

void func_800DD9E8(void) // 0x800DD9E8
{
    if (g_SysWork.sysStateStep_C[0] >= 0 && g_SysWork.sysStateStep_C[0] <= 6)
    {
        if (D_800E9EDA == 0)
        {
            func_8005DC1C(Sfx_Unk1666, &QVECTOR3(21.1f, -1.5f, -60.75f), Q8_CLAMPED(0.5f), 0);

            if (g_SysWork.sysStateStep_C[0] == 6)
            {
                D_800E9EDA = Rng_GenerateInt(Q12(0.1f), Q12(0.2f) - 2);
            }
            else
            {
                D_800E9EDA = Rng_GenerateInt(Q12(0.4f), Q12(1.2f) - 2);
            }
        }
        else
        {
            D_800E9EDA = (D_800E9EDA - g_DeltaTime) >= 0 ? D_800E9EDA - (s16)g_DeltaTime : 0;
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800E9EDA = 0;
            Savegame_EventFlagSet(EventFlag_557);
            g_SysWork.field_30 = 20;
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 144, false);
            Camera_PositionSet(NULL, Q12(20.98f), Q12(-4.08f), Q12(-59.9f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(18.56f), Q12(-1.07f), Q12(-60.94f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(19.2f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-61.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 4:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);
            Camera_PositionSet(NULL, Q12(16.37f), Q12(-2.56f), Q12(-60.41f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(20.18f), Q12(-1.4f), Q12(-60.76f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            func_800868DC(0);
            func_800868DC(2);
            func_800868DC(3);
            func_800868DC(5);
            Savegame_EventFlagSet(EventFlag_573);
            SysWork_StateStepIncrement(0);
            break;

        case 5:
            Camera_PositionSet(NULL,
                               func_800868F4(Q12(1.7701f), Q12(2.0f), 0) + Q12(16.37f),
                               Q12(-2.56f),
                               func_800868F4(Q12(-0.16f), Q12(2.0f), 2) - Q12(60.41f),
                               Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);

            Camera_LookAtSet(NULL,
                             func_800868F4(Q12(1.7801f), Q12(2.0f), 0) + Q12(20.18f),
                             Q12(-1.4f),
                             func_800868F4(Q12(-0.0301f), Q12(2.0f), 2) - Q12(60.76f),
                             Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);

            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(2.4f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_555);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            func_8008D448();
            Game_FlashlightAttributesFix();
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            break;
    }
}

void func_800DDEC8(void) // 0x800DDEC8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_8008605C(EventFlag_549, 3, 7, false);
            break;

        case 3:
            g_SysWork.silentYesSelection_2350_4 = true;
            MapMsg_DisplayAndHandleSelection(true, 85, 4, -1, 0, false);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1494, &(VECTOR3){ Q12(180.5f), Q12(-0.5f), Q12(-60.6f) }, Q8_CLAMPED(0.5f), 0);
            SD_Call(Sfx_Unk1495);
            Savegame_EventFlagClear(EventFlag_549);

            D_800EBAF4 = 1;

            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 7:
            g_SysWork.silentYesSelection_2350_4 = true;
            MapMsg_DisplayAndHandleSelection(true, 84, 8, -1, 0, false);
            break;

        case 8:
            func_8005DC1C(Sfx_Unk1494, &(VECTOR3){ Q12(180.5f), Q12(-0.5f), Q12(-60.6f) }, Q8_CLAMPED(0.5f), 0);
            Savegame_EventFlagSet(EventFlag_549);

            D_800EBAF4 = 0;

            SysWork_StateStepIncrement(0);

        case 9:
            func_8005DE0C(Sfx_Unk1495, &D_800E9D00, (Q12(4.0f) - g_SysWork.field_28) >> 7, Q12(16.0f), 0);
            func_8005DE0C(Sfx_Unk1503, &D_800E9D00, (Q12(4.0f) - g_SysWork.field_28) >> 7, Q12(16.0f), 0);

            g_SysWork.field_28 += g_DeltaTime;
            if (g_SysWork.field_28 > Q12(3.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            Sd_SfxStop(Sfx_Unk1495);
            Sd_SfxStop(Sfx_Unk1503);
            func_8005DC1C(Sfx_Unk1497, &D_800E9D00, Q8_CLAMPED(0.5f), 0);

        case 6:
            SysWork_StateStepReset();
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    if (!Savegame_EventFlagGet(EventFlag_549))
    {
        func_800894B8((g_SysWork.sysStateStep_C[0] >= 4 && g_SysWork.sysStateStep_C[0] <= 5) ? 0x90 : 0x60); // Hex?
    }
}

void func_800DE1FC(void) // 0x800DE1FC
{
    typedef struct
    {
        SPRT*      sprt_0;
        DR_TPAGE*  tpage_4;
        DR_AREA*   drawArea_8;
        DR_OFFSET* drawOffset_C;
        DR_STP*    stp_10;
    } s_ScratchData;

    VECTOR3        sp18;
    SVECTOR3       sp28;
    s_FsImageDesc  charaTex;
    s32            i;
    s32            temp;
    s32            colorBase;
    s32            tpageBase;
    s32            vOffset;
    s32            barPhase;
    s_ScratchData* scratch;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 8)
    {
        SD_Call(0x13);
        SysWork_StateStepSet(0, 9);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800EA484 = g_SysWork.playerWork_4C.player_0.position_18;
            D_800EB6B0 = 0;
            D_800E9EDC = Q12(1.0f);

            Fs_QueueStartRead(FILE_ANIM_HIDDEN1_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);

            D_800EB6B4 = 0;

            Anim_CharaTypeAnimInfoClear();
            Chara_Load(0, Chara_GhostDoctor, &D_800E9EE4, -1, NULL, NULL);
            Chara_Load(1, Chara_Dahlia, g_SysWork.npcCoords_FC0, 0, NULL, NULL);
            Chara_FsImageCalc(&charaTex, Chara_Kaufmann, 2);
            Chara_Load(2, Chara_Kaufmann, &g_SysWork.npcCoords_FC0[30], 0, LM_BUFFER_2, &charaTex);
            Chara_ProcessLoads();

            Chara_Spawn(Chara_Kaufmann, 0, Q12(140.0f), Q12(-60.0f), 0, 3);
            Chara_Spawn(Chara_Dahlia, 0, Q12(140.0f), Q12(-60.0f), 0, 3);
            Chara_Spawn(Chara_GhostDoctor, 0, Q12(140.0f), Q12(-60.0f), 0, 3);
            Chara_Spawn(Chara_GhostDoctor, 1, Q12(140.0f), Q12(-60.0f), 0, 3);
            ScreenFade_ResetTimestep();

            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= 1 << 3;

            func_8008D438();

            g_SysWork.field_235C               = NULL;
            g_SysWork.field_236C               = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(0.6f);

            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 5, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[2], 0, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[3], 0, false);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            ClearImage(&D_800E9D1C, 0, 0, 0);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            WorldGfx_ObjectAdd(&g_WorldObject_Cover.object_0, &g_WorldObject_Cover.position_1C, &(SVECTOR3){ 0, 0, 0 });
            break;

        case 3:
            Map_MessageWithAudio(47, &D_800EB6B0, &D_800E9D30);
            WorldGfx_ObjectAdd(&g_WorldObject_Cover.object_0, &g_WorldObject_Cover.position_1C, &(SVECTOR3){ 0, 0, 0 });
            break;

        case 4:
            WorldGfx_ObjectAdd(&g_WorldObject_Cover.object_0, &g_WorldObject_Cover.position_1C, &(SVECTOR3){ 0, 0, 0 });

            scratch             = PSX_SCRATCH;
            scratch->drawArea_8 = (DR_AREA*)GsOUT_PACKET_P;

            SetDrawArea(scratch->drawArea_8, (g_ActiveBufferIdx == 0) ? &D_800E9D0C[1] : &D_800E9D0C[0]);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->drawArea_8);
            scratch->drawArea_8++;

            scratch->drawOffset_C = scratch->drawArea_8;
            SetDrawOffset(scratch->drawOffset_C, (g_ActiveBufferIdx == 0) ? &D_800E9D24[2] : &D_800E9D24[0]);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->drawOffset_C);
            scratch->drawOffset_C++;

            scratch->stp_10 = scratch->drawOffset_C;
            SetDrawStp(scratch->stp_10, 0);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->stp_10);

            scratch->stp_10++;
            scratch->sprt_0 = scratch->stp_10;

            for (i = 0; i < 2; i++)
            {
                setCodeWord(scratch->sprt_0, PRIM_RECT | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
                setXY0Fast(scratch->sprt_0, ((i << 8) - 160), -112);

                scratch->sprt_0->u0 = 0;
                scratch->sprt_0->v0 = (g_ActiveBufferIdx != 0) << 5;

                setWH(scratch->sprt_0, i != 0 ? 64 : 256, 224);

                addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->sprt_0, 4);

                scratch->sprt_0++;
                scratch->tpage_4 = (DR_TPAGE*)scratch->sprt_0;

                temp = 4;
                setDrawTPage(scratch->tpage_4, 0, 0,
                             getTPage(2, 0, ((i * temp + (g_ActiveBufferIdx == 0) * 16) & 0xF) << 6, ((g_ActiveBufferIdx == 0)) << 8));

                AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->tpage_4);
                scratch->tpage_4++;
                scratch->sprt_0 = (SPRT*)scratch->tpage_4;
            }

            scratch->drawArea_8 = (DR_AREA*)scratch->sprt_0;
            SetDrawArea(scratch->drawArea_8, &D_800E9D1C);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->drawArea_8);
            scratch->drawArea_8++;

            scratch->drawOffset_C = scratch->drawArea_8;
            SetDrawOffset(scratch->drawOffset_C, &D_800E9D2C);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->drawOffset_C);
            scratch->drawOffset_C++;

            scratch->stp_10 = scratch->drawOffset_C;
            SetDrawStp(scratch->stp_10, 1);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->stp_10);
            scratch->stp_10++;

            GsOUT_PACKET_P = scratch->stp_10;
            SysWork_StateStepIncrement(0);
            break;

        case 5:
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[2], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[3], 0, 0);
            SysWork_StateStepIncrement(0);

        case 6:
            WorldGfx_ObjectAdd(&g_WorldObject_Bed3.object_0, &g_WorldObject_Bed3.position_1C, &g_WorldObject_Bed3.rotation_28);

            colorBase       = D_800E9EDC >> 5;
            scratch         = PSX_SCRATCH;
            scratch->sprt_0 = GsOUT_PACKET_P;
            vOffset         = 0;
            barPhase        = 1;
            tpageBase       = 21;

            for (i = 0; i < 6; i++)
            {
                if (i == 2)
                {
                    barPhase  = 2;
                    vOffset   = (g_ActiveBufferIdx != 0) << 5;
                    tpageBase = !(g_ActiveBufferIdx) * 16;
                }
                else if (i == 4)
                {
                    colorBase = 0x80;
                    barPhase  = 0;
                    vOffset   = (g_ActiveBufferIdx == 0) << 5;
                    tpageBase = g_ActiveBufferIdx * 16;
                }

                setRGBC0(scratch->sprt_0, colorBase, colorBase, colorBase, PRIM_RECT | RECT_BLEND | RECT_TEXTURE);
                setXY0Fast(scratch->sprt_0, ((i & 1) << 8) - 160, -112);

                scratch->sprt_0->u0 = 0;
                scratch->sprt_0->v0 = vOffset;

                setWH(scratch->sprt_0, (i & 0x1) ? 64 : 256, 224);

                if (i < 4)
                {
                    addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->sprt_0, 4);
                }
                else
                {
                    addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratch->sprt_0, 4);
                }

                scratch->sprt_0++;
                scratch->tpage_4 = (DR_TPAGE*)scratch->sprt_0;

                setDrawTPage(scratch->tpage_4, 0, 0,
                             getTPage(2, barPhase, (tpageBase + ((i & 1) * 4)) << 6, ((tpageBase >> 4) & (1 << 0)) << 8));

                if (i < 4)
                {
                    AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->tpage_4);
                }
                else
                {
                    AddPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratch->tpage_4);
                }

                scratch->tpage_4++;
                scratch->sprt_0 = scratch->tpage_4;
            }

            scratch->stp_10 = (DR_STP*)scratch->sprt_0;
            SetDrawStp(scratch->stp_10, 1);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[0x7FF], scratch->stp_10);
            scratch->stp_10++;

            SetDrawStp(scratch->stp_10, 0);
            addPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[0], scratch->stp_10);
            scratch->stp_10++;

            GsOUT_PACKET_P = scratch->stp_10;

            D_800E9EDC -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
            if (D_800E9EDC < 0)
            {
                SysWork_StateStepIncrement(0);
                Savegame_EventFlagSet(EventFlag_551);
                func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            }
            break;

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 8:
            SysWork_StateStepSet(0, NO_VALUE);
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 10:
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[2], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[3], 0, 0);

            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            Savegame_EventFlagSet(EventFlag_551);
            SysWork_StateStepIncrement(0);

        default:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            D_800EB6B4                         = NO_VALUE;

            Anim_CharaTypeAnimInfoClear();
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        g_DeltaTime >>= 1;

        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "DARIA", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "KAU", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[2].position_18, &g_SysWork.npcs_1A0[2].rotation_24, "DOC1", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[3].position_18, &g_SysWork.npcs_1A0[3].rotation_24, "DOC2", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &sp28, "LIGHT", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&sp18, &sp28, "L_INT", D_800EB6B4, FS_BUFFER_11);

        g_SysWork.pointLightRot_2370.vx = -ratan2(sp18.vy - g_SysWork.pointLightPosition_2360.vy,
                                                  Math_Vector2MagCalc(sp18.vx - g_SysWork.pointLightPosition_2360.vx,
                                                                      sp18.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy = ratan2(sp18.vx - g_SysWork.pointLightPosition_2360.vx, sp18.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = 0;

        func_800401CC();
    }
}

void func_800DF1E8(void) {}

void MapEvent_DiskOfOuroborosTake(void) // 0x800DF1F0
{
    Event_ItemTake(InventoryItemId_DiskOfOuroboros, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S02_PickupDiskOfOuroboros, 83);
}

void func_800DF21C(void) // 0x800DF21C
{
    s_FsImageDesc charaTex;
    VECTOR3       lightIntPos;
    SVECTOR3      unused;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 11)
    {
        SysWork_StateStepSet(0, 11);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800EB6B0 = 0;
            Game_TurnFlashlightOn();
            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= SysFlag2_3;
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            Fs_QueueStartRead(FILE_ANIM_HALLWAY_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);

            D_800EB6B4 = 0;

            Anim_CharaTypeAnimInfoClear();
            Chara_Load(0, Chara_GhostChildAlessa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Chara_FsImageCalc(&charaTex, Chara_Dahlia, 2);
            Chara_Load(1, Chara_Dahlia, &g_SysWork.npcCoords_FC0[30], 0, LM_BUFFER_2, &charaTex);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_GhostChildAlessa, 0, Q12(100.0f), Q12(-100.0f), 0, 3);
            Chara_Spawn(Chara_Dahlia, 0, Q12(100.0f), Q12(-100.0f), 0, 3);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(0.8f);

            Savegame_EventFlagSet(EventFlag_560);
            Map_MessageWithAudio(62, &D_800EB6B0, &D_800E9D50);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 25, false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);

            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);

            Map_MessageWithAudio(62, &D_800EB6B0, &D_800E9D50);
            SysWork_StateStepIncrement(0);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.6f), false);
            SysWork_StateStepIncrement(0);

        case 3:
            Map_MessageWithAudio(62, &D_800EB6B0, &D_800E9D50);
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(5.0f), Q12(0.0f), Q12(32.0f), true, false);
            break;

        case 4:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 27, false);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);
            SysWork_StateStepIncrement(0);

        case 5:
            Map_MessageWithAudio(67, &D_800EB6B0, &D_800E9D50);
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(5.0f), Q12(33.0f), Q12(59.0f), true, false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(5.0f), Q12(33.0f), Q12(59.0f), true, true);
            break;

        case 7:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 10, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 12, false);

            D_800EB6B4 = Q12(60.0f);

            Savegame_EventFlagClear(EventFlag_560);
            SysWork_StateStepIncrement(0);

        case 8:
            Map_MessageWithAudio(68, &D_800EB6B0, &D_800E9D50);
            break;

        case 9:
            D_800EB6B4 = Q12(61.0f);
            Savegame_EventFlagSet(EventFlag_560);
            Map_MessageWithAudio(71, &D_800EB6B0, &D_800E9D50);
            break;

        case 10:
            g_SysWork.npcs_1A0[1].timer_C6 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
            g_SysWork.npcs_1A0[0].timer_C6 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
            if (g_SysWork.npcs_1A0[0].timer_C6 > Q12(1.0f))
            {
                g_SysWork.npcs_1A0[0].timer_C6 = Q12(1.0f);
                g_SysWork.npcs_1A0[1].timer_C6 = Q12(1.0f);

                SysWork_StateStepReset();
            }
            break;

        case 11:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 12:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);
            Anim_CharaTypeAnimInfoClear();
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            D_800EB6B4 = NO_VALUE;

            SD_Call(19);
            Savegame_EventFlagSet(EventFlag_560);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800EB6B4, FS_BUFFER_11);

        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "ALESSA", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "DAHLIA", D_800EB6B4, FS_BUFFER_11);

        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, "LIGHT", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&lightIntPos, &unused, "L_INT", D_800EB6B4, FS_BUFFER_11);

        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy = ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = 0;

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800EB694, &D_800EB6A4, NULL, D_800EB6B4, FS_BUFFER_11));
        vcUserCamTarget(&D_800EB694, NULL, true);
        vcUserWatchTarget(&D_800EB6A4, NULL, true);

        g_SysWork.playerWork_4C.player_0.rotation_24.vy += Q12_ANGLE(16.88f);
    }
}

void func_800DFA54(void) // 0x800DFA54
{
    MapMsg_DisplayWithTexture(FILE_TIM_ABUSEDSK_TIM, Q12(0.0f), Q12(0.0f), 98);
}

void MapEvent_ScrewdriverTake(void) // 0x800DFA80
{
    Event_ItemTake(InventoryItemId_Screwdriver, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupScrewdriver, 94);
}

void func_800DFAAC(void) // 0x800DFAAC
{
    g_BackgroundColor = 104;
    MapMsg_DisplayWithTexture(FILE_TIM_LITHGRPH_TIM, Q12(0.0f), Q12(0.0f), 101);
}

void func_800DFAE4(void) // 0x800DFAE4
{
    g_BackgroundColor = 104;
    MapMsg_DisplayWithTexture(FILE_TIM_LITHGR_3_TIM, Q12(0.0f), Q12(0.0f), 102);
}

void MapEvent_AmuletOfSolomonTake(void) // 0x800DFB1C
{
    Event_ItemTake(InventoryItemId_AmuletOfSolomon, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupAmuletOfSolomon, 96);
}

void func_800DFB48(void) // 0x800DFB48
{
    g_BackgroundColor = 0x48;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_LISDIARY_TIM, false);

            D_800EA490 = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 147, 0, 0, 0, false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_800862F8(2, 0, false);
            break;

        case 7:
            SD_Call(Sfx_MenuMap);
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            func_800862F8(2, 0, false);
            break;

        case 9:
            MapMsg_DisplayAndHandleSelection(false, D_800E9D6C[D_800EA490], 0, 0, 0, false);
            func_800862F8(2, 0, false);
            break;

        case 10:
            func_800862F8(2, 0, false);

            D_800EA490++;
            if (D_800EA490 >= 8)
            {
                SysWork_StateStepIncrement(0);
                break;
            }

            SysWork_StateStepSet(0, 7);
            break;

        case 11:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            func_800862F8(2, 0, false);
            break;

        case 12:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 13:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DFDDC(void) // 0x800DFDDC
{
    // @note Mirror any changes to `map7_s01::func_800D9C9C` (likely copy-pasted func with some small differences).
    s32       i;
    s32       j;
    s32       temp_a0;
    s32       temp_a3;
    s32       temp_t0;
    s32       temp_v0_2;
    s32       temp_v0_3;
    s32       temp_v1;
    s32       var_v0_3;
    s32       var_v0_4;
    s32       var_v0;
    SPRT*     sprt;
    DR_TPAGE* tPage;

    if (D_800E9D8E != 0)
    {
        if ((g_SysWork.sysStateStep_C[0] >= 8 && g_SysWork.sysStateStep_C[0] <= 10) || g_SysWork.sysStateStep_C[0] == 15)
        {
            sprt = (SPRT*)GsOUT_PACKET_P;
            setCodeWord(sprt, PRIM_RECT | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
            setXY0Fast(sprt, (((D_800E9D8E - 1) % 3) * 35) - 42, (((D_800E9D8E - 1) / 3) * 35) - 32);
            setUV0(sprt, 64, 16);
            setWH(sprt, 14, 14);
            sprt->clut = 0x38E; // TODO: Is this calculated from something?

            addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[1], sprt, 4);

            sprt++;

            tPage = (DR_TPAGE*)sprt;
            setDrawTPage(tPage, 0, 0, 135);
            AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[1], tPage);

            tPage++;

            GsOUT_PACKET_P = (PACKET*)tPage;
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800E9D8E         = 0;
            D_800EA494.field_0 = 0;

            while (true)
            {
                if (Savegame_EventFlagGet(EventFlag_500 + D_800EA494.field_0))
                {
                    break;
                }
                D_800EA494.field_0++;
            }

            func_800862F8(0, D_800E9D80[D_800EA494.field_0], false);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

        case 2:
            func_800862F8(1, 0, false);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_800862F8(2, 0, false);
            break;

        case 4:
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0 ||
                g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                if (!Savegame_EventFlagGet(EventFlag_487) && (D_800EA494.field_0 == 1 || D_800EA494.field_0 == 5 || D_800EA494.field_0 == 6))
                {
                    SysWork_StateStepSet(0, 5);
                }
                else
                {
                    SysWork_StateStepSet(0, 15);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SysWork_StateStepSet(0, 15);
            }

            func_800862F8(2, 0, false);
            break;

        case 6:
            func_800862F8(7, FILE_TIM_HS_PANEL_TIM, false);
            break;

        case 7:
            if (D_800EA494.field_0 == 1)
            {
                var_v0 = EventFlag_507;
            }
            else if (D_800EA494.field_0 == 5)
            {
                var_v0 = EventFlag_511;
            }
            else
            {
                var_v0 = EventFlag_515;
            }

            for (i = 0; i < 4; i++)
            {
                if (Savegame_EventFlagGet(var_v0 + i))
                {
                    D_800E9D8E += 1 << i;
                }
            }

            sharedData_800E2CA8_7_s01 = 0;
            sharedData_800E2CAC_7_s01 = 0;
            SysWork_StateStepIncrement(0);

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 9:
            func_800862F8(2, 0, false);

            sharedData_800E2CA8_7_s01 += (g_Controller0->sticks_24.sticks_0.leftX * 16384) / 75;
            sharedData_800E2CA8_7_s01  = CLAMP_RANGE(sharedData_800E2CA8_7_s01, Q12(-80.0f), Q12(80.0f));

            sharedData_800E2CAC_7_s01 += (g_Controller0->sticks_24.sticks_0.leftY * 16384) / 75;
            sharedData_800E2CAC_7_s01  = CLAMP_RANGE(sharedData_800E2CAC_7_s01, Q12(-80.0f), Q12(80.0f));

            Game_TimerUpdate();

            // TODO: Should `Gfx_CursorDraw` first args be `s16`?
            Gfx_CursorDraw((s16)(FP_FROM(sharedData_800E2CA8_7_s01, 12) + 8), (s16)FP_FROM(sharedData_800E2CAC_7_s01, 12) + 8, 8, 8, 0, 0x40, 0x20, 0x20, 0x80, 0xC0, 0, 0xC);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SysWork_StateStepSet(0, 15);
                break;
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        // TODO: Not sure what's with these multiplies/subtractions, something to do with menu selections?
                        temp_t0  = j * 35;
                        var_v0_3 = temp_t0 - 46; // Only matches as separate var, TODO: add another for `- 24`?
                        temp_a3  = FP_FROM(sharedData_800E2CA8_7_s01, 12);
                        if (temp_a3 < var_v0_3 || temp_a3 > (temp_t0 - 24))
                        {
                            continue;
                        }

                        temp_a0 = i * 35;
                        var_v0_4  = temp_a0 - 37;
                        temp_v1   = FP_FROM(sharedData_800E2CAC_7_s01, 12);
                        if (temp_v1 < var_v0_4 || temp_v1 > (temp_a0 - 15))
                        {
                            continue;
                        }

                        temp_v0_2 = temp_a3 + 35;
                        temp_v0_2 = temp_t0 - temp_v0_2;

                        temp_v0_3 = temp_v1 + 26;
                        temp_v0_3 = temp_a0 - temp_v0_3;

                        if (SQUARE(temp_v0_2) + SQUARE(temp_v0_3) < 122)
                        {
                            D_800E9D8E = j + (i * 3) + 1;
                            SD_Call(Sfx_Base);

                            // @hack Maybe not meant to reuse `temp_a0_2`, but that helps it to match.
                            if (D_800EA494.field_0 == 1)
                            {
                                temp_a0 = EventFlag_507;
                            }
                            else if (D_800EA494.field_0 == 5)
                            {
                                temp_a0 = EventFlag_511;
                            }
                            else
                            {
                                temp_a0 = EventFlag_515;
                            }

                            // @bug This is overwriting `i` from the outer loop?
                            for (i = 0; i < 4; i++)
                            {
                                if ((D_800E9D8E >> i) & 1)
                                {
                                    Savegame_EventFlagSet(temp_a0 + i);
                                }
                                else
                                {
                                    Savegame_EventFlagClear(temp_a0 + i);
                                }
                            }

                            for (i = 0, j = 0; i < 12; i++)
                            {
                                if (Savegame_EventFlagGet(EventFlag_507 + i))
                                {
                                    j += 1 << i;
                                }
                            }

                            if (D_800E9D7C == j)
                            {
                                SysWork_StateStepSet(0, 10);
                            }
                        }
                    }
                }
            }
            break;

        case 11:
            g_SysWork.field_30 = 20;
            D_800EA492         = 0;

            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);
            func_8008D438();
            Camera_PositionSet(NULL, Q12(-138.15f), Q12(-1.71f), Q12(-138.77f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-140.56f), Q12(-1.03f), Q12(-141.88f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            WorldObject_ModelNameSet(&D_800EBB64.object_0, "STONE2_H");
            SysWork_StateStepIncrement(0);

        case 12:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 13:
            switch (g_SysWork.sysStateStep_C[1])
            {
                case 0:
                    SD_Call(Sfx_Base);

                case 1:
                    g_SysWork.field_28 += g_DeltaTime;
                    if (g_SysWork.field_28 > Q12(2.0f))
                    {
                        g_SysWork.field_28 = Q12(2.0f);

                        WorldObject_ModelNameSet(&D_800EBB64.object_0, "STONE3_H");
                        Sd_SfxStop(Sfx_Base);

                        SysWork_StateStepIncrement(1);
                    }

                    D_800EBB64.position_1C.vz = ((g_SysWork.field_28 * Q12(0.1f)) / Q12(2.0f)) - Q12(140.6f);
                    break;

                case 2:
                    D_800EA492 += g_GravitySpeed >> 1;

                    if (D_800EBB64.position_1C.vy < Q12(-1.05f))
                    {
                        D_800EBB64.position_1C.vy += Q12_MULT_PRECISE(g_DeltaTime, D_800EA492);
                        if (D_800EBB64.position_1C.vy > Q12(-1.05f))
                        {
                            D_800EBB64.position_1C.vy = Q12(-1.05f);

                            SysWork_StateStepIncrement(1);
                            g_SysWork.field_28 = Q12(0.0f);
                            D_800EA492         = 0;

                            SD_Call(Sfx_Base);
                        }
                    }
                    break;

                case 3:
                    D_800EBB64.rotation_28.vz += Q12_MULT_PRECISE(g_DeltaTime, Q12(-0.0694f));
                    D_800EBB64.position_1C.vy  = Q12_MULT(Math_Cos(D_800EBB64.rotation_28.vz), Q12(0.15f)) - (Q12(1.2f) - 1); // TODO: Why `- 1`?
                    D_800EBB64.position_1C.vz  = Q12_MULT(Math_Sin(D_800EBB64.rotation_28.vz), Q12(-0.15f)) - Q12(140.5f);

                    g_SysWork.field_28 += g_DeltaTime;
                    if (g_SysWork.field_28 > Q12(0.5f))
                    {
                        SysWork_StateStepIncrement(1);
                        g_SysWork.field_28 = Q12(0.0f);
                    }
                    break;

                case 4:
                    D_800EA492                += g_GravitySpeed;
                    D_800EBB64.rotation_28.vz += Q12_MULT_PRECISE(g_DeltaTime, Q12(-0.3333f));
                    D_800EBB64.position_1C.vy += Q12_MULT_PRECISE(D_800EA492, g_DeltaTime);
                    D_800EBB64.position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.3f));

                    if (D_800EBB64.position_1C.vy > 0)
                    {
                        SysWork_StateStepIncrement(1);
                    }
                    break;

                case 5:
                    SD_Call(Sfx_Base);

                    D_800EBB64.position_1C.vx = Q12(-139.5f);
                    D_800EBB64.position_1C.vy = Q12(-0.05f);
                    D_800EBB64.position_1C.vz = Q12(-140.0f);
                    D_800EBB64.rotation_28.vz = Q12(-0.25f);

                    SysWork_StateStepIncrement(0);
                    break;
            }
            break;

        case 14:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            func_8008D448();
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);
            Savegame_EventFlagClear(EventFlag_500 + D_800EA494.field_0);
            Savegame_EventFlagSet(EventFlag_487);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            break;

        case 5:
        case 10:
        case 15:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Savegame_EventFlagClear(EventFlag_500 + D_800EA494.field_0);
            break;
    }
}

void MapEvent_CrestOfMercuryTake(void) // 0x800E0C30
{
    Event_ItemTake(InventoryItemId_CrestOfMercury, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupCrestOfMercury, 97);
}

void MapEvent_RingOfContractTake(void) // 0x800E0C5C
{
    Event_ItemTake(InventoryItemId_RingOfContract, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupRingOfContract, 93);
}

void MapEvent_CameraTake(void) // 0x800E0C88
{
    Event_ItemTake(InventoryItemId_Camera, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupCamera, 95);
}

void func_800E0CB4(void) // 0x800E0CB4
{
    const static VECTOR3 SFX_POS_0 = { Q12(-63.2f), Q12(-1.45f), Q12(-139.05f) };
    const static VECTOR3 SFX_POS_1 = { Q12(-62.9f), Q12(0.0f), Q12(-139.1f) };

    s16* var_s0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            Fs_QueueStartRead(FILE_ANIM_DRIVR_DMS, (void*)FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 148, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            D_800EA494.field_2 = Q12(0.3f);
            D_800EB6B4         = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(31.0f), false, true);

            // TODO: Possible inline?
            var_s0 = &D_800EA494.field_2;
            if (*var_s0 == 0)
            {
                func_8005DC1C(Sfx_Unk1656, &SFX_POS_0, Q8_CLAMPED(0.5f), 0);
                *var_s0 = Q12(1.2f);
            }
            else
            {
                *var_s0 -= g_DeltaTime;
                if (*var_s0 < 0)
                {
                    *var_s0 = 0;
                }
            }
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(32.0f), true, false);

            // TODO: Possible inline?
            var_s0 = &D_800EA494.field_2;
            if (*var_s0 == 0)
            {
                func_8005DC1C(Sfx_Unk1656, &SFX_POS_0, Q8_CLAMPED(0.5f), 0);
                *var_s0 = Q12(1.2f);
            }
            else
            {
                *var_s0 -= g_DeltaTime;
                if (*var_s0 < 0)
                {
                    *var_s0 = 0;
                }
            }
            break;

        case 3:
            func_8005DC1C(Sfx_Unk1655, &SFX_POS_1, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);

            D_800EB6B4 = NO_VALUE;

            Savegame_EventFlagSet(EventFlag_486);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800EB694, &D_800EB6A4, NULL, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&D_800EB694, NULL, true);
        vcUserWatchTarget(&D_800EB6A4, NULL, true);
    }
}

void func_800E0FF0(void) // 0x800E0FF0
{
    if (Savegame_EventFlagGet(EventFlag_486) && Savegame_EventFlagGet(EventFlag_549))
    {
        g_BackgroundColor = 120;

        switch (g_SysWork.sysStateStep_C[0])
        {
            case 0:
                Player_ControlFreeze();
                SysWork_StateStepIncrement(0);

            case 1:
                func_80086DA8(FILE_TIM_ELCWIRE2_TIM, 0);
                break;

            case 2:
                SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
                SysWork_StateStepIncrement(0);

            case 3:
                SysWork_StateStepIncrement(0);

            case 4:
                func_800862F8(2, 0, false);
                SysWork_StateStepIncrementAfterFade(1, false, 0, Q12(0.0f), false);
                break;

            case 5:
                func_800862F8(2, 0, false);
                MapMsg_DisplayAndHandleSelection(true, 80, 6, 7, 0, false);
                break;

            case 6:
                func_80086470(3, InventoryItemId_KeyOfAratron, 1, false);
                Savegame_EventFlagSet(EventFlag_M7S02_PickupKeyOfAratron);
                SysWork_StateStepIncrement(0);

            case 7:
                func_80086F44(0, 0);
                break;

            default:
                Player_ControlUnfreeze(false);
                SysWork_StateSetNext(SysState_Gameplay);
                break;
        }
    }
    else
    {
        if (Savegame_EventFlagGet(EventFlag_486))
        {
            MapMsg_DisplayWithTexture(FILE_TIM_ELCWIRE1_TIM, 0, 0, 105);
            if (g_SysWork.sysStateStep_C[1] >= 3 && g_SysWork.sysStateStep_C[1] <= 5)
            {
                // Plays SFX after random time between 0.2f - 2.2f?
                if (D_800EBB94 != Q12(0.0f))
                {
                    D_800EBB94 -= g_DeltaTime;
                    if (D_800EBB94 < Q12(0.0f))
                    {
                        D_800EBB94 = Q12(0.0f);
                    }
                }
                else
                {
                    SD_Call(Sfx_Unk1653);
                    D_800EBB94 = Rng_GenerateInt(Q12(0.2f), Q12(2.2f) - 1);
                }
            }
        }
        else
        {
            g_BackgroundColor = 112;
            MapMsg_DisplayWithTexture(FILE_TIM_ELCWIRE0_TIM, 0, 0, 110);
        }
    }
}

void func_800E12E4(void) // 0x800E12E4
{
    if (Savegame_EventFlagGet(EventFlag_496))
    {
        if (Savegame_EventFlagGet(EventFlag_498))
        {
            MapMsg_DisplayWithTexture(FILE_TIM_3X3HINT2_TIM, 0, 0, 108);
        }
        else
        {
            MapMsg_DisplayWithTexture(FILE_TIM_3X3PICT2_TIM, 0, 0, 108);
        }
    }
    else
    {
        if (Savegame_EventFlagGet(EventFlag_499))
        {
            MapMsg_DisplayWithTexture(FILE_TIM_3X3HINT1_TIM, 0, 0, 107);
        }
        else
        {
            MapMsg_DisplayWithTexture(FILE_TIM_3X3PICT1_TIM, 0, 0, 107);
        }
    }

    Savegame_EventFlagClear(EventFlag_496);
    Savegame_EventFlagClear(EventFlag_497);
}

void func_800E1398(void) // 0x800E1398
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            if (Savegame_EventFlagGet(EventFlag_496))
            {
                func_800862F8(0, FILE_TIM_3X3HINT2_TIM, false);
                Savegame_EventFlagSet(EventFlag_498);
            }
            else
            {
                func_800862F8(0, FILE_TIM_3X3HINT1_TIM, false);
                Savegame_EventFlagSet(EventFlag_499);
            }

            ScreenFade_Reset();
            g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;

            SD_Call(0x679U);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 1, Q12(2.5f), false);
            g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
            break;

        case 2:
            func_800862F8(1, 0, false);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 1, Q12(0.4f), false);
            func_800862F8(2, 0, false);
            break;

        case 4:
            if (Savegame_EventFlagGet(EventFlag_496))
            {
                MapMsg_DisplayAndHandleSelection(false, 108, 0, 0, 0, false);
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 107, 0, 0, 0, false);
            }

            func_800862F8(2, 0, false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            func_800862F8(2, 0, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagClear(EventFlag_496);
            Savegame_EventFlagClear(EventFlag_497);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            func_80086470(3, InventoryItemId_Camera, 1, false);
            break;
    }
}

#include "maps/shared/sharedFunc_800DB60C_7_s01.h" // 0x800E15D4

void func_800E1DAC(void) // 0x800E1DAC
{
    const static VECTOR3 SFX_POS = { Q12(100.8f), Q12(-1.0f), Q12(-20.0f) };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800EB6B0 = 0;

            func_800862F8(0, FILE_TIM_NEWSP3_TIM, false);
            func_8005DC1C(Sfx_Unk1654, &SFX_POS, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            func_800862F8(1, 0, false);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_800862F8(2, 0, false);
            break;

        case 4:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 15, 0, 0, 0, false);
            break;

        case 5:
            g_BackgroundColor = 48;

            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false);
            break;

        case 6:
            SD_Call(Sfx_Unk1654);
            SysWork_StateStepIncrement(0);

        case 7:
            g_BackgroundColor = 48;

            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 17, 0, 0, 0, false);
            break;

        case 8:
            g_BackgroundColor = 48;

            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false);
            break;

        case 9:
            g_BackgroundColor = 48;

            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void func_800E1FF4(void) // 0x800E1FF4
{
    const static VECTOR3 SFX_POS = { Q12(97.8f), Q12(-1.0f), Q12(-19.2f) };

    if (g_SysWork.sysStateStep_C[1] == 0)
    {
        func_8005DC1C(Sfx_Unk1464, &SFX_POS, Q8_CLAMPED(0.5f), 0);
    }

    MapMsg_DisplayWithTexture1(FILE_TIM_PLANTBK_TIM, Q12(0.0f), Q12(0.0f), 22, 23);
}

const VECTOR3 sharedData_800CB094_3_s01 = { 0xFFF9B19A, 0xFFFFE000, 0xFFFC319A };

#include "maps/shared/sharedFunc_800D15F0_3_s01.h" // 0x800E204C

void func_800E2DC0(void) // 0x800E2DC0
{
    MapMsg_DisplayWithTexture(FILE_TIM_ALESSA_TIM, Q12(0.0f), Q12(0.0f), 124);
}

void func_800E2DEC(void) // 0x800E2DEC
{
    VECTOR3 playerPosBackup;
    s32     i;

    g_BackgroundColor = 104;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            for (i = 0; i < 5; i++)
            {
                if (Savegame_EventFlagGet(EventFlag_564 + i))
                {
                    break;
                }
            }

            if (i != 5)
            {
                D_800EA4A9 = i;
                Savegame_EventFlagSet(EventFlag_540 + D_800EA4A9);

                for (i = 0; i < 5; i++)
                {
                    if (!Savegame_EventFlagGet(EventFlag_540 + i))
                    {
                        break;
                    }
                }

                if (i == 5)
                {
                    Savegame_EventFlagSet(EventFlag_545);
                }

                playerPosBackup                            = g_SysWork.playerWork_4C.player_0.position_18;
                g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(101.0f);
                g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-98.8f);
                Ipd_CloseRangeChunksInit();
                g_SysWork.playerWork_4C.player_0.position_18 = playerPosBackup;

                SysWork_StateStepSet(0, 3);
            }
            else
            {
                SysWork_StateStepSet(0, 7);
            }
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 125 + D_800EA4A9, 0, 0, 0, false);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1663, &QVECTOR3(60.0f, -1.2f, -96.0f), Q8_CLAMPED(0.5f), 0);

            if (!Savegame_EventFlagGet(EventFlag_545))
            {
                Savegame_EventFlagClear(EventFlag_564 + D_800EA4A9);
                Player_ControlUnfreeze(false);
                SysWork_StateSetNext(SysState_Gameplay);
            }
            else
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.7f), false);
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1343, &QVECTOR3(60.0f, -1.2f, -96.0f), Q8_CLAMPED(0.5f), 0);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 7:
            func_8005DC1C(Sfx_DoorLocked, &QVECTOR3(60.0f, -1.2f, -96.0f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 8:
            MapMsg_DisplayAndHandleSelection(false, 12, 0, 0, 0, false);
            break;

        case 9:
            for (i = 0; i < 5; i++)
            {
                if (Savegame_EventFlagGet(EventFlag_540 + i))
                {
                    break;
                }
            }

            if (i != 5)
            {
                Player_ControlUnfreeze(false);
                SysWork_StateSetNext(SysState_Gameplay);
            }
            else
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            func_800862F8(0, FILE_TIM_LASTDOOR_TIM, false);
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 12:
            func_800862F8(1, 0, false);
            break;

        case 13:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 14:
            MapMsg_DisplayAndHandleSelection(false, 130, 0, 0, 0, false);
            func_800862F8(2, 0, false);
            break;

        case 15:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void func_800E32E0(void) // 0x800E32E0
{
    s32 i;
    s32 j;
    s32 temp;
    s16 cursorX;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);

            sharedData_800E2CAC_7_s01 = 0;
            sharedData_800E2CA8_7_s01 = 0;

            for (i = 0; i < ARRAY_SIZE(D_800EA4AC); i++)
            {
                D_800EA4AC[i] = 26;
            }

            SysWork_StateStepIncrement(0);

        case 1:
            func_800862F8(7, FILE_TIM_ALERTDOR_TIM, false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, false, false, false);
            func_800862F8(2, 0, false);
            break;

        case 4:
            func_800862F8(2, 0, false);

            sharedData_800E2CA8_7_s01 += (g_Controller0->sticks_24.sticks_0.leftX * 16384) / 75;
            sharedData_800E2CA8_7_s01  = CLAMP_RANGE(sharedData_800E2CA8_7_s01, Q12(-120.0f), Q12(120.0f));

            sharedData_800E2CAC_7_s01 += (g_Controller0->sticks_24.sticks_0.leftY * 16384) / 75;
            sharedData_800E2CAC_7_s01  = CLAMP_RANGE(sharedData_800E2CAC_7_s01, Q12(-120.0f), Q12(120.0f));

            Game_TimerUpdate();

            cursorX = FP_FROM(sharedData_800E2CA8_7_s01, Q12_SHIFT) + 8;
            Gfx_CursorDraw(cursorX, FP_FROM(sharedData_800E2CAC_7_s01, Q12_SHIFT) + 8, 8, 8, 0, 64, 32, 32, 128, 192, 0, 12);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SysWork_StateStepSet(0, 8);
                break;
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                for (i = 0; i < ARRAY_SIZE(D_800E9DE8); i++)
                {
                    if ((D_800E9DE8[i][0] - 174) > FP_FROM(sharedData_800E2CA8_7_s01, Q12_SHIFT) ||
                        (D_800E9DE8[i][0] - 146) < FP_FROM(sharedData_800E2CA8_7_s01, Q12_SHIFT) ||
                        (D_800E9DE8[i][1] - 134) > FP_FROM(sharedData_800E2CAC_7_s01, Q12_SHIFT) ||
                        (D_800E9DE8[i][1] - 106) < FP_FROM(sharedData_800E2CAC_7_s01, Q12_SHIFT))
                    {
                        continue;
                    }

                    temp = D_800E9DE8[i][0] - 160 - FP_FROM(sharedData_800E2CA8_7_s01, Q12_SHIFT);
                    j    = SQUARE(temp);
                    temp = SQUARE(D_800E9DE8[i][1] - 120 - FP_FROM(sharedData_800E2CAC_7_s01, Q12_SHIFT));

                    if (j + temp >= 197)
                    {
                        continue;
                    }

                    SD_Call(Sfx_Unk1650);

                    for (j = 0; j < (ARRAY_SIZE(D_800EA4AC) - 1); j++)
                    {
                        D_800EA4AC[j] = D_800EA4AC[j + 1];
                    }

                    D_800EA4AC[4] = i;

                    for (j = 0; j < ARRAY_SIZE(D_800EA4AC); j++)
                    {
                        if (D_800EA4AC[j] != D_800E9E1C[j])
                        {
                            break;
                        }
                    }

                    if (j == ARRAY_SIZE(D_800EA4AC))
                    {
                        Savegame_EventFlagSet(EventFlag_488);

                        SysWork_StateStepSet(0, 5);
                    }
                }
            }
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            func_800862F8(2, 0, false);
            break;

        case 6:
            SD_Call(Sfx_Unk1343);
            SysWork_StateStepIncrement(0);

        case 7:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void Map_WorldObjectsInit(void) // 0x800E3804
{
    char beanObjName[] = "BEAN0_HI\0";
    s32  i;

    D_800EBB94 = 0;

    WorldObjectInit(&g_WorldObject_Diary, "DIARY_HI", -180.0f, 0.0f, -140.755f, 0.0f, 180.0f, 0.0f);

    WorldObject_ModelNameSet(&g_WorldObject_SavePad, D_800A99E4.savePadName_4);

    WorldObjectPoseInit(&g_WorldObject_UnkPose0, -16.6226f, -1.2396f, -59.0691f, 0.0f, 105.21f, 0.0f);

    WorldObjectPoseInit(&g_WorldObject_UnkPose1, 58.9993f, -0.82f, -99.0521f, 0.0f, -86.1f, 0.0f);

    WorldObject_ModelNameSet(&g_WorldObject_KaigaR[0], "KAIGAR_H");
    WorldObject_ModelNameSet(&g_WorldObject_KaigaR[1], "KAIGAR2_");

    Math_Vector3Set(&g_WorldObject_UnkPos0, Q12(56.0f), Q12(-1.9f), Q12(-19.25f));

    WorldObject_ModelNameSet(&g_WorldObject_KaigaL[0], "KAIGAL_H");
    WorldObject_ModelNameSet(&g_WorldObject_KaigaL[1], "KAIGAL2_");

    Math_Vector3Set(&g_WorldObject_UnkPos1, Q12(56.0f), Q12(-1.9f), Q12(-21.45f));

    Math_SetSVectorFast(&g_WorldObject_UnkRot0, Q12_ANGLE(0.0f), Q12_ANGLE(180.0f), Q12_ANGLE(0.0f));

    WorldObjectInit(&g_WorldObject_Bed3, "BED3_HID", 139.6f, 0.0f, -59.6f, 0.0f, 90.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject_Cover, "COVER_HI", 139.71f, 0.3f, -59.55f);

    WorldObjectNoRotInit(&g_WorldObject_Ank, "ANK_HIDE", 21.5767f, -1.3956f, -100.8592f);

    WorldObjectNoRotInit(&g_WorldObject_Ref[0], "REF1_HID", 20.3f, 0.0f, -60.75f);
    WorldObjectNoRotInit(&g_WorldObject_Ref[1], "REF2_HID", 20.3f, 0.0f, -60.75f);

    WorldObjectInit(&g_WorldObject_Dor[0], "DOR1_HID", 21.15f, -0.8f, -60.0f, 0.0f, 0.0f, 0.0f);
    WorldObjectInit(&g_WorldObject_Dor[1], "DOR2_HID", 21.15f, -0.1f, -60.0f, 0.0f, 0.0f, 0.0f);
    WorldObjectInit(&g_WorldObject_Dor[2], "DOR3_HID", 21.15f, -0.1f, -61.5f, 0.0f, 0.0f, 0.0f);
    WorldObjectInit(&g_WorldObject_Dor[3], "DOR4_HID", 21.15f, -0.8f, -61.5f, 0.0f, 0.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject_Chain1[0], "CHAIN1_N", 20.3f, 0.31f, -60.75f);
    WorldObjectNoRotInit(&g_WorldObject_Chain1[1], "CHAIN1_H", 20.3f, 0.0206f, -60.75f);

    WorldObjectNoRotInit(&g_WorldObject_Sword, "SWORD_HI", 20.3f, 0.0f, -60.75f);

    WorldObjectInit(&g_WorldObject_Jelly, "JELLY_NE", 62.55f, -0.9f, -61.05f, 0.0f, 90.0f, 0.0f);

    for (i = 0; i < ARRAY_SIZE(g_WorldObject_Beans); i++)
    {
        beanObjName[4] = (i >> 1) + '1';
        WorldObject_ModelNameSet(&g_WorldObject_Beans[i], beanObjName);
        g_WorldObject_Beans[i].position_1C.vx = Q12(62.3f);
        g_WorldObject_Beans[i].position_1C.vy = Rng_GenerateInt(Q12(-1.45f), Q12(-1.3501f) - 1);
        g_WorldObject_Beans[i].position_1C.vz = Rng_GenerateInt(Q12(-61.07f), Q12(-60.93f) - 1);
        g_WorldObject_Beans[i].rotation_28.vx = Rng_GenerateUInt(0, 4095);
        g_WorldObject_Beans[i].rotation_28.vy = Rng_GenerateUInt(0, 4095);
        g_WorldObject_Beans[i].rotation_28.vz = Rng_GenerateUInt(0, 4095);
        D_800EB9F4[i]                         = Rng_GenerateUInt(0, 4095);
        D_800EBA14[i]                         = FP_FROM(Math_Sin(Rng_GenerateUInt(0, 511) | 0x200) * Q12(2.2f), Q12_SHIFT);
    }

    WorldObjectInit(&g_WorldObject_Key0, "KEY_HIDE", 62.2f, 0.0f, -61.1f, 0.0f, 0.0f, 90.0f);

    WorldObjectNoRotInit(&g_WorldObject_Wall9, "WALL9_HI", 103.9f, 0.0f, -99.5f);

    WorldObjectNoRotInit(&g_WorldObject_Door9, "DOOR9_HI", 104.0f, -1.6f, -100.2f);

    WorldObjectNoRotInit(&g_WorldObject_Gofu, "GOFU_HID", 17.072f, -1.6f, -19.2f);

    WorldObjectNoRotInit(&g_WorldObject_Driver, "DRIVER_H", -19.2f, 0.0f, -97.45f);

    WorldObjectNoRotInit(&g_WorldObject_Zukan, "ZUKAN_HI", 99.8f, 0.0f, -20.0f);

    WorldObjectNoRotInit(&g_WorldObject_Scrap, "SCRAP_HI", 100.0f, 0.0f, -20.0f);

    WorldObject_ModelNameSet(&g_WorldObject_Key1, "KEY_HIDE");

    WorldObject_ModelNameSet(&g_WorldObject_Futa[0], "FUTA1_HI");
    WorldObject_ModelNameSet(&g_WorldObject_Futa[1], "FUTA2_HI");

    WorldObjectPoseInit(&g_WorldObject_UnkPose2, -60.0f, 0.0f, -140.8f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Camera, "CAMERA_H", -19.6f, -0.8f, -142.2f, 0.0f, 126.7f, 0.0f);

    WorldObjectInit(&g_WorldObject_Door, "DOOR_HID", 182.5247f, 0.0f, -106.064f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Ring, "RING_NEA", -178.381f, -0.5716f, -98.846f, 0.0f, 0.0f, -32.5f);

    WorldObjectInit(&g_WorldObject_Gofu_B, "GOFU_B_H", -181.9f, -0.57f, -101.2f, 0.0f, 59.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[0], "DR1L_HID", -100.9f, 0.0f, -60.9f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[1], "DR1R_HID", -100.9f, 0.0f, -60.9f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[2], "DR3L_HID", -100.9f, 0.0f, -60.9f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[3], "DR3R_HID", -100.9f, 0.0f, -60.9f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[4], "DR2L_HID", -100.9f, 0.0f, -60.9f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[5], "DR2R_HID", -100.9f, 0.0f, -60.9f);

    WorldObjectNoRotInit(&g_WorldObject_Mov1, "MOV1_HID", -21.7317f, -0.387f, -57.2073f);

    WorldObjectNoRotInit(&g_WorldObject_Key2, "KEY_HIDE", 140.6558f, -0.81f, -58.937f);

    WorldObjectInit(&g_WorldObject_GofuA[0], "GOFUA_HI", 59.7776f, -1.8433f, -96.1695f, 0.0f, 90.0f, 0.0f);
    WorldObjectInit(&g_WorldObject_GofuA[1], "GOFUB_HI", 59.77f, -1.2757f, -95.924f, 90.0f, 180.0f, 0.0f);
    WorldObjectInit(&g_WorldObject_GofuA[2], "GOFUC_HI", 60.2471f, -1.8104f, -95.917f, 0.0f, 90.0f, 0.0f);
    WorldObjectInit(&g_WorldObject_GofuA[3], "GOFUD_HI", 59.9993f, -1.5943f, -95.9087f, 90.0f, 0.0f, 0.0f);
    WorldObjectInit(&g_WorldObject_GofuA[4], "GOFUE_HI", 60.2496f, -1.2691f, -95.9105f, 90.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_KeyX2, "KEYX2_HI", -16.6692f, -1.23f, -61.6f, 90.9f, 90.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Stone, "STONE_HI", -16.6692f, -0.71f, -61.533f, 0.0f, 90.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Window, "WINDOW_H", -16.666f, -1.235f, -61.503f, 0.0f, 90.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject_Kubomi, "KUBOMI_H", -139.5f, 0.0f, -138.1f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        func_80088FF4(Chara_Stalker, 5, 0);
        func_80088FF4(Chara_Stalker, 7, 0);
        func_80088FF4(Chara_Stalker, 8, 0);
    }
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        func_80088FF4(Chara_Stalker, 9, 11);
        func_80088FF4(Chara_Stalker, 12, 3);
        func_80088FF4(Chara_Stalker, 13, 3);
        func_80088FF4(Chara_Stalker, 14, 3);
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

static const VECTOR3 D_800CDC4C = { Q12(-63.3f), Q12(-1.6f), Q12(-139.2f) };
static const VECTOR3 D_800CDC58 = { Q12(140.0f), Q12(-1.2f), Q12(-23.5f) };

void Map_WorldObjectsUpdate(void) // 0x800E4528
{
    s32 cellZ0;
    s32 cellX0;
    s32 i;
    s32 projCellZ0;
    s32 projCellX0;

    MAP_CHUNK_CHECK_VARIABLE_DECL();

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
        case PACKED_CELL_XZ(11, 12):
            if (Savegame_EventFlagGet(EventFlag_569))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Diary.object_0, &g_WorldObject_Diary.position_1C, &g_WorldObject_Diary.rotation_28);
            }
            break;

        case PACKED_CELL_XZ(18, 15):
            WorldGfx_ObjectAdd(&g_WorldObject_KaigaR[Savegame_EventFlagGet(EventFlag_498) ? 1 : 0], &g_WorldObject_UnkPos0, &g_WorldObject_UnkRot0);
            WorldGfx_ObjectAdd(&g_WorldObject_KaigaL[Savegame_EventFlagGet(EventFlag_499) ? 1 : 0], &g_WorldObject_UnkPos1, &g_WorldObject_UnkRot0);
            break;

        case PACKED_CELL_XZ(15, 14):
            WorldGfx_ObjectAdd(&g_WorldObject_Stone.object_0, &g_WorldObject_Stone.position_1C, &g_WorldObject_Stone.rotation_28);
            WorldGfx_ObjectAdd(&g_WorldObject_Window.object_0, &g_WorldObject_Window.position_1C, &g_WorldObject_Window.rotation_28);
            WorldGfx_ObjectAdd(&g_WorldObject_SavePad, &g_WorldObject_UnkPose0.position_0, &g_WorldObject_UnkPose0.rotation_C);
            WorldGfx_ObjectAdd(&g_WorldObject_KeyX2.object_0, &g_WorldObject_KeyX2.position_1C, &g_WorldObject_KeyX2.rotation_28);
            break;

        case PACKED_CELL_XZ(20, 14):
            if (Savegame_EventFlagGet(EventFlag_551))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Bed3.object_0, &g_WorldObject_Bed3.position_1C, &g_WorldObject_Bed3.rotation_28);
                if (!Savegame_EventFlagGet(EventFlag_M7S02_PickupDiskOfOuroboros))
                {
                    WorldGfx_ObjectAdd(&g_WorldObject_Key2.object_0, &g_WorldObject_Key2.position_1C, &(SVECTOR3){ 0, 0, 0 });
                }
            }
            break;

        case PACKED_CELL_XZ(17, 13):
            if (!Savegame_EventFlagGet(EventFlag_M7S02_PickupAnkh))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Ank.object_0, &g_WorldObject_Ank.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
            break;

        case PACKED_CELL_XZ(17, 14):
            if (Savegame_EventFlagGet(EventFlag_557))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Ref[1].object_0, &g_WorldObject_Ref[1].position_1C, &(SVECTOR3){ 0, 0, 0 });
                for (i = 0; i < 4; i++)
                {
                    WorldGfx_ObjectAdd(&g_WorldObject_Dor[i].object_0, &g_WorldObject_Dor[i].position_1C, &g_WorldObject_Dor[i].rotation_28);
                }
            }
            else
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Ref->object_0, &g_WorldObject_Ref->position_1C, &(SVECTOR3){ 0, 0, 0 });
                if (!Savegame_EventFlagGet(EventFlag_M7S02_PickupDaggerOfMelchior))
                {
                    WorldGfx_ObjectAdd(&g_WorldObject_Sword.object_0, &g_WorldObject_Sword.position_1C, &(SVECTOR3){ 0, 0, 0 });
                }
            }

            if (Savegame_EventFlagGet(EventFlag_552))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Chain1[1].object_0, &g_WorldObject_Chain1[1].position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
            else
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Chain1[0].object_0, &g_WorldObject_Chain1[0].position_1C, &(SVECTOR3){ 0, 0, 0 });
            }

            if (Savegame_EventFlagGet(EventFlag_M7S02_PickupDaggerOfMelchior))
            {
                if (Savegame_EventFlagGet(EventFlag_552))
                {
                    Savegame_EventFlagSet(EventFlag_554);
                    Savegame_EventFlagClear(EventFlag_553);
                }
                else
                {
                    Savegame_EventFlagSet(EventFlag_553);
                    Savegame_EventFlagClear(EventFlag_554);
                }
            }
            else
            {
                Savegame_EventFlagClear(EventFlag_553);
                Savegame_EventFlagClear(EventFlag_554);
            }
            break;

        case PACKED_CELL_XZ(18, 14):
            if (!Savegame_EventFlagGet(EventFlag_556))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Jelly.object_0, &g_WorldObject_Jelly.position_1C, &g_WorldObject_Jelly.rotation_28);
            }
            else if (!Savegame_EventFlagGet(EventFlag_M7S02_PickupKeyOfBethor))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Key0.object_0, &g_WorldObject_Key0.position_1C, &g_WorldObject_Key0.rotation_28);
            }
            break;

        case PACKED_CELL_XZ(19, 13):
            if (Savegame_EventFlagGet(EventFlag_560))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Wall9.object_0, &g_WorldObject_Wall9.position_1C, &(SVECTOR3){ 0, 0, 0 });
                WorldGfx_ObjectAdd(&g_WorldObject_Door9.object_0, &g_WorldObject_Door9.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
            break;

        case PACKED_CELL_XZ(17, 15):
            if (!Savegame_EventFlagGet(EventFlag_M7S01_PickupAmuletOfSolomon))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Gofu.object_0, &g_WorldObject_Gofu.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
            break;

        case PACKED_CELL_XZ(15, 13):
            if (!Savegame_EventFlagGet(EventFlag_M7S01_PickupScrewdriver))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Driver.object_0, &g_WorldObject_Driver.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
            break;

        case PACKED_CELL_XZ(19, 15):
            WorldGfx_ObjectAdd(&g_WorldObject_Zukan.object_0, &g_WorldObject_Zukan.position_1C, &(SVECTOR3){ 0, 0, 0 });
            if (Savegame_EventFlagGet(EventFlag_M5S03_SeenSecondNewspaper))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Scrap.object_0, &g_WorldObject_Scrap.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
            break;

        case PACKED_CELL_XZ(14, 12):
            if (Savegame_EventFlagGet(EventFlag_486))
            {
                if (!Savegame_EventFlagGet(EventFlag_M7S02_PickupKeyOfAratron))
                {
                    WorldGfx_ObjectAdd(&g_WorldObject_Key1, &g_WorldObject_UnkPose2.position_0, &g_WorldObject_UnkPose2.rotation_C);
                }
                WorldGfx_ObjectAdd(&g_WorldObject_Futa[1], &g_WorldObject_UnkPose2.position_0, &g_WorldObject_UnkPose2.rotation_C);
            }
            else
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Futa[0], &g_WorldObject_UnkPose2.position_0, &g_WorldObject_UnkPose2.rotation_C);
            }

            if (Savegame_EventFlagGet(EventFlag_486) && !Savegame_EventFlagGet(EventFlag_549))
            {
                if (D_800EBB94)
                {
                    D_800EBB94 -= g_DeltaTime;
                    if (D_800EBB94 < 0)
                    {
                        D_800EBB94 = 0;
                    }
                }
                else
                {
                    func_8005DC1C(Sfx_Unk1653, &D_800CDC4C, 0x20, 0);
                    D_800EBB94 = (Rng_Rand16() % 0x2000) + 0x333;
                }
            }
            break;

        case PACKED_CELL_XZ(12, 12):
            WorldGfx_ObjectAdd(&g_WorldObject_Kubomi.object_0, &g_WorldObject_Kubomi.position_1C, &(SVECTOR3){ 0, 0, 0 });
            break;

        case PACKED_CELL_XZ(15, 12):
            if (!Savegame_EventFlagGet(EventFlag_M7S01_PickupCamera))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Camera.object_0, &g_WorldObject_Camera.position_1C, &g_WorldObject_Camera.rotation_28);
            }
            break;

        case PACKED_CELL_XZ(21, 13):
            WorldGfx_ObjectAdd(&g_WorldObject_Door.object_0, &g_WorldObject_Door.position_1C, &g_WorldObject_Door.rotation_28);
            break;

        case PACKED_CELL_XZ(15, 15):
        case PACKED_CELL_XZ(13, 14):
            for (i = 0; i < 6; i++)
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Dr[i].object_0, &g_WorldObject_Dr[i].position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
            break;

        case PACKED_CELL_XZ(11, 13):
            if (!Savegame_EventFlagGet(EventFlag_M7S01_PickupRingOfContract))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Ring.object_0, &g_WorldObject_Ring.position_1C, &g_WorldObject_Ring.rotation_28);
            }
            if (!Savegame_EventFlagGet(EventFlag_M7S01_PickupCrestOfMercury))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Gofu_B.object_0, &g_WorldObject_Gofu_B.position_1C, &g_WorldObject_Gofu_B.rotation_28);
            }
            break;

        case PACKED_CELL_XZ(18, 13):
            if (Savegame_EventFlagGet(EventFlag_540))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_GofuA[0].object_0, &g_WorldObject_GofuA[0].position_1C, &g_WorldObject_GofuA->rotation_28);
            }

            if (Savegame_EventFlagGet(EventFlag_541))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_GofuA[1].object_0, &g_WorldObject_GofuA[1].position_1C, &g_WorldObject_GofuA[1].rotation_28);
            }

            if (Savegame_EventFlagGet(EventFlag_542))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_GofuA[2].object_0, &g_WorldObject_GofuA[2].position_1C, &g_WorldObject_GofuA[2].rotation_28);
            }

            if (Savegame_EventFlagGet(EventFlag_543))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_GofuA[3].object_0, &g_WorldObject_GofuA[3].position_1C, &g_WorldObject_GofuA[3].rotation_28);
            }

            if (Savegame_EventFlagGet(EventFlag_544))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_GofuA[4].object_0, &g_WorldObject_GofuA[4].position_1C, &g_WorldObject_GofuA[4].rotation_28);
            }

            WorldGfx_ObjectAdd(&g_WorldObject_SavePad, &g_WorldObject_UnkPose1.position_0, &g_WorldObject_UnkPose1.rotation_C);
            break;

        case PACKED_CELL_XZ(12, 15):
            if (!Savegame_EventFlagGet(EventFlag_478) && g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-19.0f))
            {
                Savegame_EventFlagSet(EventFlag_478);
                func_8005DC1C(Sfx_Unk1528, &D_800CDC58, 0xFF, 2);
            }
            break;
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_549))
        {
            if (!D_800EBAF4)
            {
                SD_Call(Sfx_Unk1503);
                D_800EBAF4++;
            }
            else if (D_800EBAF4 == 1)
            {
                func_8005DE0C(Sfx_Unk1495, &D_800E9D00, Q8(0.5f), Q12(16.0f), 0);
                func_8005DE0C(Sfx_Unk1503, &D_800E9D00, Q8(0.5f), Q12(16.0f), 0);
            }
        }
    }
    else
    {
        if (D_800EBAF4 == 1)
        {
            Sd_SfxStop(Sfx_Unk1495);
            Sd_SfxStop(Sfx_Unk1503);

            D_800EBAF4 = 0;
        }
    }

    func_80069844(0xFFFF);
    func_8006982C(0);

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M7S01_RifleShells))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M7S01_HandgunBullets0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M7S01_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M7S01_HandgunBullets1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M7S01_ShotgunShells))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M7S01_FirstAidKit))
        {
            WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[5].position_0, &g_CommonWorldObjectPoses[5].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M7S01_HandgunBullets2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[6].position_0, &g_CommonWorldObjectPoses[6].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M7S01_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[7].position_0, &g_CommonWorldObjectPoses[7].rotation_C);
        }
    }
}

void func_800E5628(void) // 0x800E5628
{
    if (D_800A9945 != 7 || !func_80040B74(Chara_Stalker))
    {
        Anim_CharaTypeAnimInfoClear();
        Chara_Load(0, 7, g_SysWork.npcCoords_FC0, NO_VALUE, NULL, NULL);
        Chara_ProcessLoads();
    }

    if (Savegame_EventFlagGet(EventFlag_M7S02_PickupKeyOfAratron))
    {
        func_80088FF4(Chara_Stalker, 3, 3);

        if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
        {
            func_80088FF4(Chara_Stalker, 10, 0xB);
            func_80088FF4(Chara_Stalker, 10, 3);
        }
    }

    if (Savegame_EventFlagGet(EventFlag_549))
    {
        Savegame_EventFlagClear(EventFlag_420);
    }
    else
    {
        Savegame_EventFlagSet(EventFlag_420);
    }
}

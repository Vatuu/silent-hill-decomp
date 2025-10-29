#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s02.h"

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
    (arg0 != 0) ? func_800D9864() : func_800D9924();
}

void func_800D9830(s32 arg0) // 0x800D9830
{
    (arg0 != 0) ? func_800D98E4() : func_800D9924();
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

    func_8003640C(var);
}

void func_800D98E4(void) // 0x800D98E4
{
    func_8003640C(Savegame_EventFlagGet(EventFlag_391) ? 40 : 35);
}

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800D9924);

void func_800DA1A8() {}

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

// TODO: Move to funcs after other users are decompiled.
const char D_800CD42C[] = "HERO";

void func_800DA248(void) // 0x800DA248
{
    s_FsImageDesc charaTex;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] >= 4)
        {
            if (g_SysWork.sysStateStep_C[0] <= 20)
            {
                SysWork_StateStepSet(0, 22);
            }
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            D_800EB6B0 = 0;

            Fs_QueueStartRead(FILE_ANIM_HBM7_SLS_ANM, FS_BUFFER_4);
            Fs_QueueStartRead(FILE_ANIM_NURSE1_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();

            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
            D_800EB6B4 = 0;
            func_800348C0();

            Chara_Load(0, Chara_Lisa, g_SysWork.npcCoords_FC0, CHARA_FORCE_FREE_ALL, NULL, NULL);

            ScreenFade_ResetTimestep();

            g_SysWork.field_30    = 20;
            g_SysWork.field_2378  = Q12(0.8f);
            g_SysWork.flags_22A4 |= 1 << 3;

            Game_TurnFlashlightOn();
            D_800E9ECC = 0;
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            sharedFunc_800D2EB4_0_s00();
            func_8003D03C();
            func_8003640C(4);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80087EDC(4);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
            break;

        case 3:
            func_80088D0C();
            Chara_Spawn(Chara_Lisa, 0, Q12(130.0f), Q12(-70.0f), FP_ANGLE(0.0f), 3);
            SysWork_StateStepIncrement(0);

        case 4:
            Map_MessageWithAudio(111, &D_800EB6B0, &D_800E9CE4);
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(20.0f), true, false);
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 72, false);
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
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
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
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 155, false);
            Sd_EngineCmd(Sfx_Unk4664);
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
            Chara_Load(1, Chara_BloodyLisa, &g_SysWork.npcCoords_FC0[30], 0, (s_LmHeader*)0x8019E600, &charaTex);

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(180.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-100.0f);

            func_8003C3AC();
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
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(180.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-100.0f);

            func_8003C3AC();
            Chara_FsImageCalc(&charaTex, Chara_BloodyLisa, 2);
            Chara_Load(1, Chara_BloodyLisa, &g_SysWork.npcCoords_FC0[30], 0, (s_LmHeader*)0x8019E600, &charaTex);
            func_80088D0C();
            SysWork_StateStepIncrement(0);

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_482);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088D0C();
            Sd_EngineCmd(19);
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CD42C, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "LISA\0\0\0\0", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800EB694, &D_800EB6A4, NULL, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&D_800EB694, NULL, true);
        vcUserWatchTarget(&D_800EB6A4, NULL, true);
    }
}

// TODO: Move to funcs after other users are decompiled.
const char D_800CD4A4[] = "LIGHT";
const char D_800CD4AC[] = "L_INT";

void func_800DAA4C(void) // 0x800DAA4C
{
    VECTOR3  pos;
    SVECTOR3 rot;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] >= 2)
        {
            if (g_SysWork.sysStateStep_C[0] <= 15)
            {
                SysWork_StateStepSet(0, 17);
            }
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Fs_QueueStartRead(FILE_ANIM_NURSE2_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
            Chara_Spawn(Chara_BloodyLisa, 0, g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz + Q12(1.0f), 0, 3);

            D_800EB6B4 = 0;
            D_800EB6B0 = 0;
            D_800E9ECD = 0;

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 156, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            SysWork_StateStepIncrementAfterFade(0, false, false, false, false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(43.0f), true, true);
            break;

        case 3:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(44.0f), Q12(59.0f), true, true);
            break;

        case 4:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 157, false);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.field_2378 = Q12(1.0f);

            func_8008D438();
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(60.0f), Q12(76.0f), true, true);
            Dms_CharacterGetPosRot(&g_SysWork.field_2360, &rot, D_800CD4A4, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
            Dms_CharacterGetPosRot(&pos, &rot, D_800CD4AC, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);

            g_SysWork.field_2370.vx = -ratan2(pos.vy - g_SysWork.field_2360.vy, Math_Vector2MagCalc(pos.vx - g_SysWork.field_2360.vx, pos.vz - g_SysWork.field_2360.vz));
            g_SysWork.field_2370.vy = ratan2(pos.vx - g_SysWork.field_2360.vx, pos.vz - g_SysWork.field_2360.vz);
            g_SysWork.field_2370.vz = 0;
            break;

        case 6:
            D_800E9ECD = 1;

            func_8008D448();
            func_8003EBA0();

            g_SysWork.field_2378 = Q12(0.8f);

            func_8005DC1C(Sfx_Unk1336, &D_800EB6E0.position_0, 128, 0);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(77.0f), Q12(100.0f), true, true);
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 158, false);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_8005DC1C(Sfx_Unk1337, &D_800EB6E0.position_0, 128, 0);
            SysWork_StateStepIncrement(0);

        case 9:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(101.0f), Q12(152.0f), true, false);
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 10:
            Sd_EngineCmd(4662);
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
            if (func_80045B28())
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
            SysWork_StateStepIncrementAfterFade(2, true, false, false, false);
            break;

        case 18:
            Sd_EngineCmd(19);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            SysWork_StateStepIncrement(0);
            break;

        case 19:
            GameFs_PlayerMapAnimLoad(g_SavegamePtr->mapOverlayId_A4);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);

            D_800EB6B4 = NO_VALUE;

            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_484);
            SysWork_StateStepIncrementAfterFade(0, false, 2, false, false);
            func_8008D448();
            func_8003EBA0();

            g_SysWork.field_2378 = Q12(1.0f);

            Game_TurnFlashlightOn();
            sharedFunc_800D2EF4_0_s00();
            func_8003D01C();
            func_800348C0();
            SysWork_StateStepIncrementAfterFade(0, false, false, Q12(1.0f), false);
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, D_800CD42C, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "BLS", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);

        if (D_800E9ECD != 0)
        {
            Dms_CharacterGetPosRot(&D_800EB6E0.position_0, &D_800EB6E0.rotation_C, "ADOOR", D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800EB694, &D_800EB6A4, NULL, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&D_800EB694, NULL, true);
        vcUserWatchTarget(&D_800EB6A4, NULL, true);
    }
}

#include "maps/shared/Event_DoorJammed.h" // 0x800DB21C

#include "maps/shared/Event_DoorLocked.h" // 0x800DB2B0

#include "maps/shared/Event_DoorUnlocked.h" // 0x800DB344

void func_800DB3D8(void) // 0x800DB3D8
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
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
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Map_MessageWithSfx(86, Sfx_DoorLocked, &sfxPos);
}

void func_800DB52C(void) // 0x800DB52C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Map_MessageWithSfx(88, Sfx_DoorLocked, &sfxPos);
}

void func_800DB5C0(void) // 0x800DB5C0
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_8004EE94(81, 1);
    Map_MessageWithSfx(77, Sfx_Unk1335, &sfxPos);
    Savegame_EventFlagSet(EventFlag_533);
}

void func_800DB67C(void) // 0x800DB67C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_8004EE94(82, 1);
    Map_MessageWithSfx(78, Sfx_Unk1335, &sfxPos);
    Savegame_EventFlagSet(EventFlag_534);
}

void func_800DB738(void) // 0x800DB738
{
    const static VECTOR3 SFX_POS = { Q12(97.4f), Q12(-0.5f), Q12(-59.0f) };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_800862F8(0, FILE_TIM_LISAVTR_TIM, false);

            D_800EB6B0 = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 146, false);
            SysWork_StateStepIncrementAfterFade(0, true, 2, 0, false);

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(97.61f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-59.59f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = Q12(0.8915f);

            Camera_PositionSet(NULL, Q12(100.56f), Q12(-1.06f), Q12(-61.53f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(97.61f), Q12(-0.73f), Q12(-59.2f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1526, &SFX_POS, 128, 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 6:
            func_800862F8(1, 0, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            func_800862F8(2, 0, false);
            break;

        case 8:
            Map_MessageWithAudio(32, &D_800EB6B0, &D_800E9CFC);
            func_800862F8(2, 0, false);

            if (g_SysWork.sysStateStep_C[0] == 8 &&
                g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.skip_4 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                Sd_EngineCmd(19);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            func_800862F8(2, 0, false);
            break;

        case 10:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 147, false);
            SysWork_StateStepIncrement(0);
            break;

        case 11:
            func_80085EB8(2, &g_SysWork.player_4C.chara_0, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            SysWork_StateStepIncrement(0);

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 13:
            func_8005DC1C(Sfx_Unk1526, &SFX_POS, 128, 0);
            SysWork_StateStepIncrement(0);

        case 14:
            func_80086D04(&g_SysWork.player_4C.chara_0);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
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
            sharedFunc_800D20E4_0_s00();
            func_800348C0();
            Chara_Load(0, Chara_GhostChildAlessa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);

            g_SysWork.field_30 = 20;

            ScreenFade_ResetTimestep();
            Model_AnimFlagsClear(&g_SysWork.player_4C.chara_0.model_0, 1 << 1);
            func_8008D438();
            Camera_PositionSet(NULL, Q12(20.09f), Q12(-0.9f), Q12(-97.78f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(18.5f), Q12(0.2f), Q12(-101.28f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
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
            func_80088D0C();
            Chara_Spawn(Chara_GhostChildAlessa, 0, Q12(21.2f), Q12(-100.5f), FP_ANGLE(180.0f), 3);
            SysWork_StateStepIncrement(0);
            break;

        case 6:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);
            Sd_EngineCmd(Sfx_Unk4699);
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
            g_SysWork.npcs_1A0[0].timer_C6 += FP_MULTIPLY_PRECISE(Q12(0.25f), g_DeltaTime0, Q12_SHIFT);
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
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 15:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            Sd_EngineCmd(19);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            SysWork_StateStepIncrement(0);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_548);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, 1 << 1);
            func_8008D448();
            func_800348C0();
            break;
    }
}

void func_800DC120(void) // 0x800DC120
{
    Event_ItemTake(InventoryItemId_Ankh, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S02_PickupAnkh, 81);
}

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02_2", D_800CD5C0);

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02_2", D_800CD5CC);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800DC14C);

void func_800DC778(void) // 0x800DC778
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0, InventoryItemId_KeyOfBethor, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
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
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DC94C(void) {}

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800DC954);

void func_800DCD00(void) // 0x800DCD00
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

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
                D_800E9ED8 = Rng_GenerateInt(Rng_Rand16(), Q12(1.2f), Q12(2.8f) - 1);
            }
            else
            {
                D_800E9ED8 = (D_800E9ED8 - g_DeltaTime0) >= 0 ? D_800E9ED8 - (s16)g_DeltaTime0 : 0;
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
                D_800E9ED8 = Rng_GenerateInt(Rng_Rand16(), Q12(1.2f), Q12(2.8f) - 1);
            }
            else
            {
                D_800E9ED8 = (D_800E9ED8 - g_DeltaTime0) >= 0 ? D_800E9ED8 - (s16)g_DeltaTime0 : 0;
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
                D_800E9ED8 = Rng_GenerateInt(Rng_Rand16(), Q12(1.2f), Q12(2.8f) - 1);
            }
            else
            {
                D_800E9ED8 = (D_800E9ED8 - g_DeltaTime0) >= 0 ? D_800E9ED8 - (s16)g_DeltaTime0 : 0;
            }

            if (g_SysWork.sysStateStep_C[0] != 8)
            {
                func_8004690C(Sfx_Unk1664);
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
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 13:
            Savegame_EventFlagClear(EventFlag_M7S02_PickupDaggerOfMelchior);
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 14:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

            if (D_800E9ED8 == 0 && !Savegame_EventFlagGet(EventFlag_555))
            {
                Sd_PlaySfx(Sfx_Unk1664, 0, 224);
                D_800E9ED8 = Rng_GenerateInt(Rng_Rand16(), Q12(1.2f), Q12(2.8f) - 1);
            }
            else
            {
                D_800E9ED8 = (D_800E9ED8 - g_DeltaTime0) >= 0 ? D_800E9ED8 - (s16)g_DeltaTime0 : 0;
            }
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            func_8004690C(Sfx_Unk1664);
            break;
    }
}

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02_2", D_800CD6A4);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800DD2D4);

// TODO: Move this rodata inside funcs once both usages are decomped.
extern VECTOR3 D_800CD6A4;

void func_800DD9E8(void) // 0x800DD9E8
{
    if (g_SysWork.sysStateStep_C[0] >= 0 && g_SysWork.sysStateStep_C[0] <= 6)
    {
        if (D_800E9EDA == 0)
        {
            func_8005DC1C(Sfx_Unk1666, &D_800CD6A4, 128, 0);
            if (g_SysWork.sysStateStep_C[0] == 6)
            {
                D_800E9EDA = Rng_GenerateInt(Rng_Rand16(), Q12(0.1f), Q12(0.2f) - 2);
            }
            else
            {
                D_800E9EDA = Rng_GenerateInt(Rng_Rand16(), Q12(0.4f), Q12(1.2f) - 2);
            }
        }
        else
        {
            D_800E9EDA = (D_800E9EDA - g_DeltaTime0) >= 0 ? D_800E9EDA - (s16)g_DeltaTime0 : 0;
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            D_800E9EDA = 0;
            Savegame_EventFlagSet(EventFlag_557);
            g_SysWork.field_30 = 20;
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 144, false);
            Camera_PositionSet(NULL, Q12(20.98f), Q12(-4.08f), Q12(-59.9f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(18.56f), Q12(-1.07f), Q12(-60.94f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(19.2f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-61.0f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(-90.0f);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 4:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(90.0f);
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
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_555);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            func_8008D448();
            func_8003EBA0();
            g_SysWork.field_2378 = Q12(1.0f);
            break;
    }
}

void func_800DDEC8(void) // 0x800DDEC8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_8008605C(EventFlag_549, 3, 7, false);
            break;

        case 3:
            g_SysWork.silentYesSelection_2350_4 = 1;
            MapMsg_DisplayAndHandleSelection(true, 85, 4, -1, 0, false);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1494, &(VECTOR3){ Q12(180.5f), Q12(-0.5f), Q12(-60.6f) }, 128, 0);
            Sd_EngineCmd(Sfx_Unk1495);
            Savegame_EventFlagClear(EventFlag_549);
            D_800EBAF4 = 1;
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 7:
            g_SysWork.silentYesSelection_2350_4 = 1;
            MapMsg_DisplayAndHandleSelection(true, 84, 8, -1, 0, false);
            break;

        case 8:
            func_8005DC1C(Sfx_Unk1494, &(VECTOR3){ Q12(180.5f), Q12(-0.5f), Q12(-60.6f) }, 128, 0);
            Savegame_EventFlagSet(EventFlag_549);
            D_800EBAF4 = 0;
            SysWork_StateStepIncrement(0);

        case 9:
            func_8005DE0C(Sfx_Unk1495, &D_800E9D00, (Q12(4.0f) - g_SysWork.field_28) >> 7, Q12(16.0f), 0);
            func_8005DE0C(Sfx_Unk1503, &D_800E9D00, (Q12(4.0f) - g_SysWork.field_28) >> 7, Q12(16.0f), 0);

            g_SysWork.field_28 += g_DeltaTime0;
            if (g_SysWork.field_28 > Q12(3.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            func_8004690C(Sfx_Unk1495);
            func_8004690C(Sfx_Unk1503);
            func_8005DC1C(Sfx_Unk1497, &D_800E9D00, 128, 0);

        case 6:
            SysWork_StateStepReset();
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    if (!Savegame_EventFlagGet(EventFlag_549))
    {
        func_800894B8((g_SysWork.sysStateStep_C[0] >= 4 && g_SysWork.sysStateStep_C[0] <= 5) ? 0x90 : 0x60); // Hex?
    }
}

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02_2", D_800CD734);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800DE1FC);

void func_800DF1E8(void) {}

void func_800DF1F0(void) // 0x800DF1F0
{
    Event_ItemTake(InventoryItemId_DiskOfOuroboros, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S02_PickupDiskOfOuroboros, 83);
}

void func_800DF21C(void) // 0x800DF21C
{
    s_FsImageDesc charaTex;
    VECTOR3       lightIntPos;
    SVECTOR3      unused;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) && g_SysWork.sysStateStep_C[0] >= 3)
    {
        if (g_SysWork.sysStateStep_C[0] < 11)
        {
            SysWork_StateStepSet(0, 11);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            D_800EB6B0 = 0;
            Game_TurnFlashlightOn();
            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= 1 << 3;
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            Fs_QueueStartRead(FILE_ANIM_HALLWAY_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);

            D_800EB6B4 = 0;

            func_800348C0();
            Chara_Load(0, Chara_GhostChildAlessa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Chara_FsImageCalc(&charaTex, Chara_Dahlia, 2);
            Chara_Load(1, Chara_Dahlia, &g_SysWork.npcCoords_FC0[30], 0, (s_LmHeader*)0x8019E600, &charaTex);
            func_80088D0C();
            Chara_Spawn(Chara_GhostChildAlessa, 0, Q12(100.0f), Q12(-100.0f), 0, 3);
            Chara_Spawn(Chara_Dahlia, 0, Q12(100.0f), Q12(-100.0f), 0, 3);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.field_2378 = Q12(0.8f);

            Savegame_EventFlagSet(EventFlag_560);
            Map_MessageWithAudio(62, &D_800EB6B0, &D_800E9D50);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 25, false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            Model_AnimFlagsClear(&g_SysWork.player_4C.chara_0.model_0, 2);
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
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, 2);
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
            g_SysWork.npcs_1A0[1].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
            g_SysWork.npcs_1A0[0].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
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
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80088F94(&g_SysWork.npcs_1A0[1], 0, 0);
            func_800348C0();
            func_8008D448();
            func_8003EBA0();

            g_SysWork.field_2378 = Q12(1.0f);

            D_800EB6B4 = NO_VALUE;

            Sd_EngineCmd(19);
            Savegame_EventFlagSet(EventFlag_560);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, 2);
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        // TODO: D_800CD42C -> `HERO`
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, D_800CD42C, D_800EB6B4, FS_BUFFER_11);

        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "ALESSA", D_800EB6B4, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "DAHLIA", D_800EB6B4, FS_BUFFER_11);

        // TODO: D_800CD4A4 -> `LIGHT`
        Dms_CharacterGetPosRot(&g_SysWork.field_2360, &unused, D_800CD4A4, D_800EB6B4, FS_BUFFER_11);

        // TODO: D_800CD4AC -> `L_INT`
        Dms_CharacterGetPosRot(&lightIntPos, &unused, D_800CD4AC, D_800EB6B4, FS_BUFFER_11);

        g_SysWork.field_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.field_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.field_2360.vx, lightIntPos.vz - g_SysWork.field_2360.vz));
        g_SysWork.field_2370.vy = ratan2(lightIntPos.vx - g_SysWork.field_2360.vx, lightIntPos.vz - g_SysWork.field_2360.vz);
        g_SysWork.field_2370.vz = 0;

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800EB694, &D_800EB6A4, NULL, D_800EB6B4, FS_BUFFER_11));
        vcUserCamTarget(&D_800EB694, NULL, true);
        vcUserWatchTarget(&D_800EB6A4, NULL, true);

        g_SysWork.player_4C.chara_0.rotation_24.vy += FP_ANGLE(16.88f);
    }
}

void func_800DFA54(void) // 0x800DFA54
{
    func_80087360(FILE_TIM_ABUSEDSK_TIM, Q12(0.0f), Q12(0.0f), 98);
}

void func_800DFA80(void) // 0x800DFA80
{
    Event_ItemTake(InventoryItemId_Screwdriver, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupScrewdriver, 94);
}

void func_800DFAAC(void) // 0x800DFAAC
{
    g_BackgroundColor = 104;
    func_80087360(FILE_TIM_LITHGRPH_TIM, Q12(0.0f), Q12(0.0f), 101);
}

void func_800DFAE4(void) // 0x800DFAE4
{
    g_BackgroundColor = 104;
    func_80087360(FILE_TIM_LITHGR_3_TIM, Q12(0.0f), Q12(0.0f), 102);
}

void func_800DFB1C(void) // 0x800DFB1C
{
    Event_ItemTake(InventoryItemId_AmuletOfSolomon, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupAmuletOfSolomon, 96);
}

void func_800DFB48(void) // 0x800DFB48
{
    g_BackgroundColor = 0x48;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_800862F8(0, FILE_TIM_LISDIARY_TIM, false);

            D_800EA490 = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 147, 0, 0, 0, false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            func_800862F8(2, 0, false);
            break;

        case 7:
            Sd_EngineCmd(Sfx_Unk1308);
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
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            func_800862F8(2, 0, false);
            break;

        case 12:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 13:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
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
            sharedFunc_800D20E4_0_s00();
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

            D_800EB68C = 0;
            D_800EB690 = 0;
            SysWork_StateStepIncrement(0);

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 9:
            func_800862F8(2, 0, false);

            D_800EB68C += (g_Controller0->sticks_24.sticks_0.leftX * 16384) / 75;
            D_800EB68C  = CLAMP_RANGE(D_800EB68C, Q12(-80.0f), Q12(80.0f));

            D_800EB690 += (g_Controller0->sticks_24.sticks_0.leftY * 16384) / 75;
            D_800EB690  = CLAMP_RANGE(D_800EB690, Q12(-80.0f), Q12(80.0f));

            Game_TimerUpdate();

            // TODO: Should `func_800881B8` first args be `s16`?
            func_800881B8((s16)(FP_FROM(D_800EB68C, 12) + 8), (s16)FP_FROM(D_800EB690, 12) + 8, 8, 8, 0, 0x40, 0x20, 0x20, 0x80, 0xC0, 0, 0xC);

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
                        temp_a3  = FP_FROM(D_800EB68C, 12);
                        if (temp_a3 < var_v0_3 || temp_a3 > (temp_t0 - 24))
                        {
                            continue;
                        }

                        temp_a0 = i * 35;
                        var_v0_4  = temp_a0 - 37;
                        temp_v1 = FP_FROM(D_800EB690, 12);
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
                            Sd_EngineCmd(Sfx_Base);

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

            Model_AnimFlagsClear(&g_SysWork.player_4C.chara_0.model_0, 2);
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
                    Sd_EngineCmd(Sfx_Base);

                case 1:
                    g_SysWork.field_28 += g_DeltaTime0;
                    if (g_SysWork.field_28 > Q12(2.0f))
                    {
                        g_SysWork.field_28 = Q12(2.0f);

                        WorldObject_ModelNameSet(&D_800EBB64.object_0, "STONE3_H");
                        func_8004690C(Sfx_Base);

                        SysWork_StateStepIncrement(1);
                    }

                    D_800EBB64.position_1C.position_0.vz = ((g_SysWork.field_28 * Q12(0.1f)) / Q12(2.0f)) - Q12(140.6f);
                    break;

                case 2:
                    D_800EA492 += g_DeltaTime2 >> 1;

                    if (D_800EBB64.position_1C.position_0.vy < Q12(-1.05f))
                    {
                        D_800EBB64.position_1C.position_0.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, D_800EA492, 12);
                        if (D_800EBB64.position_1C.position_0.vy > Q12(-1.05f))
                        {
                            D_800EBB64.position_1C.position_0.vy = Q12(-1.05f);

                            SysWork_StateStepIncrement(1);
                            g_SysWork.field_28 = 0;
                            D_800EA492         = 0;

                            Sd_EngineCmd(Sfx_Base);
                        }
                    }
                    break;

                case 3:
                    D_800EBB64.position_1C.rotation_C.vz += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(-0.0694f), 12);
                    D_800EBB64.position_1C.position_0.vy  = FP_MULTIPLY(Math_Cos(D_800EBB64.position_1C.rotation_C.vz), Q12(0.15f), 0xC) - (Q12(1.2f) - 1); // TODO: Why `- 1`?
                    D_800EBB64.position_1C.position_0.vz  = FP_MULTIPLY(Math_Sin(D_800EBB64.position_1C.rotation_C.vz), -Q12(0.15f), 0xC) - Q12(140.5f);

                    g_SysWork.field_28 += g_DeltaTime0;
                    if (g_SysWork.field_28 > Q12(0.5f))
                    {
                        SysWork_StateStepIncrement(1);
                        g_SysWork.field_28 = 0;
                    }
                    break;

                case 4:
                    D_800EA492                           += g_DeltaTime2;
                    D_800EBB64.position_1C.rotation_C.vz += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(-0.3333f), 12);
                    D_800EBB64.position_1C.position_0.vy += FP_MULTIPLY_PRECISE(D_800EA492, g_DeltaTime0, 12);
                    D_800EBB64.position_1C.position_0.vz += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.3f), 12);

                    if (D_800EBB64.position_1C.position_0.vy > 0)
                    {
                        SysWork_StateStepIncrement(1);
                    }
                    break;

                case 5:
                    Sd_EngineCmd(Sfx_Base);

                    D_800EBB64.position_1C.position_0.vx = Q12(-139.5f);
                    D_800EBB64.position_1C.position_0.vy = Q12(-0.05f);
                    D_800EBB64.position_1C.position_0.vz = Q12(-140.0f);
                    D_800EBB64.position_1C.rotation_C.vz = Q12(-0.25f);

                    SysWork_StateStepIncrement(0);
                    break;
            }
            break;

        case 14:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            func_8008D448();
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, 2);
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
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Savegame_EventFlagClear(EventFlag_500 + D_800EA494.field_0);
            break;
    }
}

void func_800E0C30(void) // 0x800E0C30
{
    Event_ItemTake(InventoryItemId_CrestOfMercury, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupCrestOfMercury, 97);
}

void func_800E0C5C(void) // 0x800E0C5C
{
    Event_ItemTake(InventoryItemId_RingOfContract, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M7S01_PickupRingOfContract, 93);
}

void func_800E0C88(void) // 0x800E0C88
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
            sharedFunc_800D20E4_0_s00();

            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= 1 << 3;

            Fs_QueueStartRead(FILE_ANIM_DRIVR_DMS, (void*)FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 148, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);

            D_800EA494.field_2 = Q12(0.3f);
            D_800EB6B4         = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(31.0f), false, true);

            // TODO: Possible inline?
            var_s0 = &D_800EA494.field_2;
            if (*var_s0 == 0)
            {
                func_8005DC1C(Sfx_Unk1656, &SFX_POS_0, 128, 0);
                *var_s0 = Q12(1.2f);
            }
            else
            {
                *var_s0 -= g_DeltaTime0;
                if (*var_s0 < 0)
                {
                    *var_s0 = 0;
                }
            }
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            SysWork_StateStepIncrementAfterTime(&D_800EB6B4, Q12(10.0f), Q12(0.0f), Q12(32.0f), true, false);

            // TODO: Possible inline?
            var_s0 = &D_800EA494.field_2;
            if (*var_s0 == 0)
            {
                func_8005DC1C(Sfx_Unk1656, &SFX_POS_0, 128, 0);
                *var_s0 = Q12(1.2f);
            }
            else
            {
                *var_s0 -= g_DeltaTime0;
                if (*var_s0 < 0)
                {
                    *var_s0 = 0;
                }
            }
            break;

        case 3:
            func_8005DC1C(Sfx_Unk1655, &SFX_POS_1, 128, 0);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);

            D_800EB6B4 = NO_VALUE;

            Savegame_EventFlagSet(EventFlag_486);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            break;
    }

    if (D_800EB6B4 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, D_800CD42C, D_800EB6B4, (s_DmsHeader*)FS_BUFFER_11);
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
                sharedFunc_800D20E4_0_s00();
                SysWork_StateStepIncrement(0);

            case 1:
                func_80086DA8(FILE_TIM_ELCWIRE2_TIM, 0);
                break;

            case 2:
                SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
                SysWork_StateStepIncrement(0);

            case 3:
                SysWork_StateStepIncrement(0);

            case 4:
                func_800862F8(2, 0, false);
                SysWork_StateStepIncrementAfterFade(1, false, 0, 0, false);
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
                sharedFunc_800D2244_0_s00(false);
                SysWork_StateSetNext(SysState_Gameplay);
                break;
        }
    }
    else
    {
        if (Savegame_EventFlagGet(EventFlag_486))
        {
            func_80087360(FILE_TIM_ELCWIRE1_TIM, 0, 0, 105);
            if (g_SysWork.sysStateStep_C[1] >= 3 && g_SysWork.sysStateStep_C[1] <= 5)
            {
                // Plays SFX after random time between 0.2f - 2.2f?
                if (D_800EBB94 != Q12(0.0f))
                {
                    D_800EBB94 -= g_DeltaTime0;
                    if (D_800EBB94 < Q12(0.0f))
                    {
                        D_800EBB94 = Q12(0.0f);
                    }
                }
                else
                {
                    Sd_EngineCmd(Sfx_Unk1653);
                    D_800EBB94 = Rng_GenerateInt(Rng_Rand16(), Q12(0.2f), Q12(2.2f) - 1);
                }
            }
        }
        else
        {
            g_BackgroundColor = 112;
            func_80087360(FILE_TIM_ELCWIRE0_TIM, 0, 0, 110);
        }
    }
}

void func_800E12E4(void) // 0x800E12E4
{
    if (Savegame_EventFlagGet(EventFlag_496))
    {
        if (Savegame_EventFlagGet(EventFlag_498))
        {
            func_80087360(FILE_TIM_3X3HINT2_TIM, 0, 0, 108);
        }
        else
        {
            func_80087360(FILE_TIM_3X3PICT2_TIM, 0, 0, 108);
        }
    }
    else
    {
        if (Savegame_EventFlagGet(EventFlag_499))
        {
            func_80087360(FILE_TIM_3X3HINT1_TIM, 0, 0, 107);
        }
        else
        {
            func_80087360(FILE_TIM_3X3PICT1_TIM, 0, 0, 107);
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
            sharedFunc_800D20E4_0_s00();

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
            g_SysWork.sysFlags_22A0 |= 1 << 0;

            Sd_EngineCmd(0x679U);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 1, Q12(2.5f), false);
            g_SysWork.sysFlags_22A0 |= 1 << 0;
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
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            func_800862F8(2, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagClear(EventFlag_496);
            Savegame_EventFlagClear(EventFlag_497);

            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            func_80086470(3, InventoryItemId_Camera, 1, false);
            break;
    }
}

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800E15D4);

void func_800E1DAC(void) // 0x800E1DAC
{
    const static VECTOR3 D_800CD904 = { Q12(100.8f), Q12(-1.0f), Q12(-20.0f) };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            D_800EB6B0 = 0;
            func_800862F8(0, FILE_TIM_NEWSP3_TIM, false);
            func_8005DC1C(Sfx_Unk1654, &D_800CD904, 0x80, 0);
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
            g_BackgroundColor = 0x30;
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false);
            break;

        case 6:
            Sd_EngineCmd(Sfx_Unk1654);
            SysWork_StateStepIncrement(0);

        case 7:
            g_BackgroundColor = 0x30;
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 17, 0, 0, 0, false);
            break;

        case 8:
            g_BackgroundColor = 0x30;
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false);
            break;

        case 9:
            g_BackgroundColor = 0x30;
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void func_800E1FF4(void) // 0x800E1FF4
{
    const static VECTOR3 D_800CD938 = { Q12(97.8f), Q12(-1.0f), Q12(-19.2f) };

    if (g_SysWork.sysStateStep_C[1] == 0)
    {
        func_8005DC1C(Sfx_Unk1464, &D_800CD938, 128, 0);
    }

    func_80087540(FILE_TIM_PLANTBK_TIM, Q12(0.0f), Q12(0.0f), 22, 23);
}

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02_2", D_800CD944);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800E204C);

void func_800E2DC0(void) // 0x800E2DC0
{
    func_80087360(FILE_TIM_ALESSA_TIM, Q12(0.0f), Q12(0.0f), 124);
}

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02_2", D_800CD998);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800E2DEC);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800E32E0);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800E3804);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800E4528);

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02_2", func_800E5628);

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02_2", D_800CDC4C);

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02_2", D_800CDC58);

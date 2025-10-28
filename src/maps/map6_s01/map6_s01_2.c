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

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D118C);

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D1220);

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

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800D1340

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01_2", D_800CB988);

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01_2", D_800CB994);

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01_2", D_800CB9A0);

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D13D8);

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D236C);

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01_2", D_800CBACC);

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01_2", D_800CBAD4);

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D2658);

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D2E6C);

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01_2", func_800D30DC);

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01_2", D_800CBB54);

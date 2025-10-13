#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map5/map5_s03.h"

INCLUDE_RODATA("asm/maps/map5_s03/nonmatchings/map5_s03", D_800C9578);

INCLUDE_RODATA("asm/maps/map5_s03/nonmatchings/map5_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB8F4

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CBD8C

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CBE64

#include "maps/shared/Particle_Update.h" // 0x800CC170

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", sharedFunc_800CEB24_0_s00); // 0x800CC78C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CCC04

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", sharedFunc_800CEFD0_1_s02); // 0x800CCD54

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CD11C

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CD248

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CD250

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CD308

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CD390

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CD548

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD6C8

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD780

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CD918

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CD938

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CE1B0

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800CE59C);

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CEE78

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CF2C8

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CF304

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CF310

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CF470

s32 func_800CF648()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CF650

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CF700

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CF718

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CF740

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CF758

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CF780

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CF824

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CF834

void func_800CF840(void) {}

void func_800CF848(void) {}

void func_800CF850(void) {}

void func_800CF858(void) {}

void func_800CF860(void) {}

s32 func_800CF868()
{
    return 0;
}

void func_800CF870(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CF878

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CF888

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CF8C8

#include "maps/shared/Ai_Kaufmann_Update.h" // 0x800CF8DC

#include "maps/shared/sharedFunc_800CF290_3_s00.h" // 0x800CF950

#include "maps/shared/sharedFunc_800CF2D8_3_s00.h" // 0x800CF998

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", sharedSymbol_800CF470_3_s00); // 0x800CFB30

#include "maps/shared/Ai_Kaufmann_Init.h" // 0x800D0510

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D054C

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D0560

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D05A4

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D05BC

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D05C8

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D05DC

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D05F0

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D0604

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D06A0

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D0D04

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D0D18

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D0D2C

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D0E28

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D0EF0

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D0EFC

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D0F5C

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D0F6C);

void func_800D1004(s32 arg0) // 0x800D1004
{
    if (arg0 != 0)
    {
        func_800D1038();
    }
    else
    {
        sharedFunc_800CE934_0_s02();
    }
}

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D1038);

#include "maps/shared/sharedFunc_800CE934_0_s02.h" // 0x800D10B4

void func_800D1340(void) {}

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800D1348

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D13E0);

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D1474);

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D1508);

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tI've_got_a_ ~C2 Motorcycle_key ~C7 . ~E ",
    "\tThere's_a_crack. ~E ",
    "\tThere's_a_crack. ~N\n\tSomething_glints_inside. ",
    "\tThe_crack_is_too_small ~N\n\tto_reach_in. ~E ",
    "\tAn_old_motorcycle. ",
    "\tLooks_like_it's_been_sitting ~N\n\there_for_years. ",
    "\t~J1(1.5) ",
    "\tThat's_weird. ",
    "\tThe_dust_is_wiped_away ~N\n\tjust_around_the_gas_tank_cap. ~E ",
    "\tA_small_glass_vial, ~N\n\twrapped_in_a_plastic_bag. ",
    "\tWhat's_this? ~E ",
    "\tIt's_like_the_busted_vial ~N\n\tI_found_in_the_director's_office ~N\n\tat_the_hospital. ~E ",
    "~J0(1.3)\tGive_me_that! ",
    "~J0(1.2)\tWhat_is_this? ~E ",
    "~J1(2.0)\tThat's_none_of_your_business! ",
    "~J1(3.3)\tInstead_of_messing_with_that, ~N\n\t\t\thow_about_coming_up_with_a_way ~N\n\t\t\tto_get_out_of_here? ",
    "~J1(0.9)\tHumph. ~E ",
    "~J1(2.6)\tYou_shouldn't_be_hanging ~N\n\t\t\taround_here_goofing_off! ",
    "~J1(1.3)\tWhat_do_you_think ~N\n\t\t\tyou_are_doing? ",
    "~J1(3.0)\tYou_want_to_get_yourself_killed!? ~N\n\t\t\tGet_outta_here! ",
    "~J1(1.9)\tOkay,_take_it_easy. ~E ",
    "~J1(3.2)\tUnless_you_want_to_die, ~N\n\t\t\tkeep_your_mind_on_business. ",
    "~J1(0.8)\tGot_it? ~E ",
    "~J1(3.3)\tThat_guy's_gotta_be_involved ~N\n\t\t\tin_the_local_drug_racket. ",
    "~J1(3.1)\tMan,_was_he_pissed. ~N\n\t\t\tAnd_in_such_a_rush,_too. ",
    "~J1(1.8)\tThat_was_probably_dope ~N\n\t\t\tin_the_bottle. ",
    "~J1(3.9)\tAnyway,_better_let_him_do_as_he ~N\n\t\t\tpleases._There's_more_than ~N\n\t\t\tmy_life_at_stake. ~E ",
    "~J1(2.0)\tI_guess_I_wasted_my_time. ",
    "~J1(2.0)\tBetter_hurry.... ~N\n\t\t\tI'm_worried_about_Cheryl. ~E ",
    "~J1(3.1)\tMan,_was_he_pissed. ~N\n\t\t\tAnd_in_such_a_rush,_too. ~E ",
    "\tThere_is_a_newspaper. ~E ",
    "\tNewspaper. ",
    "\tIt's_the_same_date_as ~N\n\tthe_one_in_the_hospital... ~E ",
    "~L4 ~C3 Investigation_stalled. ~N\n\t[PTV]_dealers_still_at_large. ~N\n\t~N\n\tSuspicious_deaths_continue. ~N\n\tLike_the_anti-drug_mayor, ~N\n\ta_narcotics_officer_dies_of ~N\n\ta_sudden_heart_failure_of ~N\n\tunknown_origin. ~E ",
    "~C3\tSeptember_10 ",
    "~C3\tTook_package. ~N\n\t\tTold_to_sit_on_it_awhile. ",
    "~C3\tDon't_want_to_get_involved, ~N\n\t\tbut_can't_disobey... ",
    "~C3\tHe's_probably_linked_to_the_death ~N\n\t\tof_the_mayor_and_others. ~E ",
    "\tThere_is_a_ ~C2 Magnet ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tUsed_the_ ~C2 Motorcycle_key ~C7 . ~E ",
    "\tBatteries,_oil_cans, ~N\n\tand_other_items_line_the_shelves. ",
    "\tA_fine_layer_of_~N\n\tdust_covers_everything, ~N\n\tas_if_long_abandoned. ~E ",
    "\tThere's_a_radio ~N\n\ton_top_of_the_cabinet. ",
    "\tIt's_completely_dead. ~N\n\tMaybe_it's_broken. ~E ",
    "\tA_poster_is_on_the_wall. ~N\n\tDon't_look_at_that_now,_though. ~E ",
    "\tThere's_a_TV_set. ",
    "\tThe_power_must_be_out. ~N\n\tIt_doesn't_work. ~E ",
    "\tThere's_a_guest_register. ~N\n\tNothing_special_written_here. ~E ",
    "\tNothing_special. ~E ",
    "\tThere's_a_vending_machine. ~N\n\tIt_doesn't_work. ~E ",
    "\tNobody_inside. ~E ",
    "\tDo_you_want_to_push ~N\n\tthe_shelf? ~S4 ",
    "\tAn_old_motorcycle. ~E "
};

void func_800D159C(void) // 0x800D159C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 37:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S03_HealthDrink0;
            break;

        case 38:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M5S03_ShotgunShells;
            break;

        case 39:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S03_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

INCLUDE_RODATA("asm/maps/map5_s03/nonmatchings/map5_s03", D_800CB7A4);

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D1628);

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D1904);

void func_800D1A84(void) // 0x800D1A84
{
    func_80087360(FILE_TIM_DIARYMTL_TIM, Q12(2.5f), Q12(2.0f), 49);
    Savegame_EventFlagSet(EventFlag_398);
}

void func_800D1ACC(void) // 0x800D1ACC
{
    Event_ItemTake(InventoryItemId_Magnet, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M5S03_PickupMagnet, 53);
}

INCLUDE_RODATA("asm/maps/map5_s03/nonmatchings/map5_s03", D_800CB7F8);

INCLUDE_RODATA("asm/maps/map5_s03/nonmatchings/map5_s03", D_800CB804);

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D1AF8);

void func_800D2640(void) // 0x800D2640
{
    func_80087540(FILE_TIM_NEWSP2_TIM, Q12(0.0f), Q12(0.0f), 46, 48);
}

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D2674);

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D2A04);

INCLUDE_ASM("asm/maps/map5_s03/nonmatchings/map5_s03", func_800D2B68);

INCLUDE_RODATA("asm/maps/map5_s03/nonmatchings/map5_s03", D_800CB8EC);

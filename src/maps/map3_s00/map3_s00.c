#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s00.h"

INCLUDE_RODATA("asm/maps/map3_s00/nonmatchings/map3_s00", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s00/nonmatchings/map3_s00", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB408

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB9D4

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CBAAC

#include "maps/shared/Particle_Update.h" // 0x800CBDB8

INCLUDE_ASM("asm/maps/map3_s00/nonmatchings/map3_s00", sharedFunc_800CEB24_0_s00); // 0x800CC388

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC844

INCLUDE_ASM("asm/maps/map3_s00/nonmatchings/map3_s00", sharedFunc_800CEFD0_1_s02); // 0x800CC994

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CCD5C

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CCE88

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CCE90

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CCF48

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CCFD0

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CD188

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD308

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD3C0

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CD558

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CD578

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CDDF0

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CE1DC

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CE7DC

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CEC08

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CEC44

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CEC50

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CEDB0

s32 func_800CEF88() // 0x800CEF88
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CEF90

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CF040

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CF058

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CF080

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CF098

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CF0C0

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CF164

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CF174

void func_800CF180() {}

void func_800CF188() {}

void func_800CF190() {}

void func_800CF198() {}

void func_800CF1A0() {}

s32 func_800CF1A8() // 0x800CF1A8
{
    return 0;
}

void func_800CF1B0() {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CF1B8

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CF1C8

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CF208

#include "maps/shared/Ai_Kaufmann_Update.h" // 0x800CF21C

#include "maps/shared/sharedFunc_800CF290_3_s00.h" // 0x800CF290

#include "maps/shared/sharedFunc_800CF2D8_3_s00.h" // 0x800CF2D8

#include "maps/shared/sharedSymbol_800CF470_3_s00.h" // 0x800CF470

#include "maps/shared/Ai_Kaufmann_Init.h" // 0x800CFE48

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CFE84

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CFE98

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CFEDC

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CFEF4

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CFF00

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CFF14

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CFF28

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CFF3C

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CFFD8

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D063C

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D0650

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D0664

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D0760

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D0828

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D0848

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D08A8

INCLUDE_ASM("asm/maps/map3_s00/nonmatchings/map3_s00", func_800D08B8);

void func_800D0960(s32 arg0) // 0x800D0960
{
    if (arg0 != 0)
    {
        sharedFunc_800D0994_3_s00();
        return;
    }

    sharedFunc_800D09D4_3_s00();
}

#include "maps/shared/sharedFunc_800D0994_3_s00.h" // 0x800D0994

#include "maps/shared/sharedFunc_800D09D4_3_s00.h" // 0x800D0994

void func_800D0B74() {}

INCLUDE_ASM("asm/maps/map3_s00/nonmatchings/map3_s00", func_800D0B7C);

INCLUDE_ASM("asm/maps/map3_s00/nonmatchings/map3_s00", func_800D0C10);

void func_800D0CA4() {}

void func_800D0CAC() // 0x800D0CAC
{
    Event_CommonItemTake(CommonPickupItemId_FirstAidKit, EventFlag_M3S00_FirstAidKit);
}

void func_800D0CD0(void) // 0x800D0CD0
{
    Event_MapTake(17, EventFlag_M3S00_PickupMap, 48);
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.0)\tHold_it... ~E ",
    "~J0(0.6)\t~E ",
    "~J0(1.7)\tStop! ~N\n\t\t\tDon't_shoot! ",
    "~J0(2.4)\tWait..._I'm_not_here_to_fight. ",
    "~J0(3.4)\tMy_name_is_Harry_Mason. ~N\n\t\t\tI'm_in_town_on_vacation. ~E ",
    "~J1(2.8)\tThank_God. ~N\n\t\t\tAnother_human_being. ",
    "~J1(1.5)\tDo_you_work_here? ",
    "~J1(3.6)\tI'm_Dr._Michael_Kaufmann. ~N\n\t\t\tI_work_at_this_hospital. ~E ",
    "~J1(2.5)\tSo_maybe_you_can_tell_me ~N\n\t\t\twhat's_going_on? ",
    "~J1(1.5)\tI_really_can't_say. ",
    "~J1(4.5)\tI_was_taking_a_nap ~N\n\t\t\tin_the_staff_room. ~N\n\t\t\tWhen_I_woke_up,_it_was_like_this. ",
    "~J1(2.3)\tEveryone_seems_to ~N\n\t\t\thave_disappeared. ",
    "~J1(3.0)\tAnd_it's_snowing_out. ~N\n\t\t\tThis_time_of_year. ",
    "~J1(2.6)\tSomething's_gone ~N\n\t\t\tseriously_wrong. ",
    "~J1(2.2)\tDid_you_see_those_monsters? ",
    "~J1(2.4)\tHave_you_ever_seen ~N\n\t\t\tsuch_aberrations? ",
    "~J1(2.0)\tEver_even_heard_of_such_things? ",
    "~J1(3.5)\tYou_and_I_both_know, ~N\n\t\t\tcreatures_like_that_don't_exist! ",
    "~J1(1.5)\tYeah... ~E ",
    "~J1(2.4)\tHave_you_seen ~N\n\t\t\ta_little_girl_anywhere? ",
    "~J1(1.6)\tI'm_looking_for_my_daughter. ",
    "~J1(3.0)\tShe's_only_seven. ~N\n\t\t\tShort,_black_hair. ",
    "~J1(2.8)\tShe's_missing? ~N\n\t\t\tI'm_sorry. ",
    "~J1(4.0)\tBut_with_all_those ~N\n\t\t\tmonsters_around, ~N\n\t\t\tI_highly_doubt_that_she's... ",
    "~J1(1.7)\t",
    "~J1(2.8)\tSorry, ~N\n\t\t\tI_didn't_mean_to_alarm_you. ~E ",
    "~J0(2.6)\tYour_wife,_she's_here_with_you? ",
    "~J0(5.0)\tShe_died_four_years_ago. ~N\n\t\t\tNow,_it's_just_me_and_my_daughter. ",
    "~J0(2.6)\tI_see... ~N\n\t\t\tI'm_sorry. ~E ",
    "~J0(2.3)\tWell,_I'd_better_be_going. ",
    "~J0(2.7)\tI_can't_just_sit ~N\n\t\t\taround_here_doing_nothing. ",
    "~J0(2.8)\tSo_long. ~N\n\t\t\tGood_luck_out_there. ~E ",
    "\tI_should_search_the_hospital. ~E ",
    "~H\tThere_is_a_ ~C5 Hospital_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThese_are_phones_and_phonebooks. ~N\n\tNo_need_to_examine_this. ~E ",
    "\tNothing_unusual. ~E ",
    "\tNothing_helpful. ~E "
};

INCLUDE_RODATA("asm/maps/map3_s00/nonmatchings/map3_s00", D_800CB2E4);

INCLUDE_RODATA("asm/maps/map3_s00/nonmatchings/map3_s00", D_800CB2F0);

INCLUDE_RODATA("asm/maps/map3_s00/nonmatchings/map3_s00", D_800CB2FC);

INCLUDE_RODATA("asm/maps/map3_s00/nonmatchings/map3_s00", D_800CB308);

INCLUDE_ASM("asm/maps/map3_s00/nonmatchings/map3_s00", func_800D0CF8);

INCLUDE_ASM("asm/maps/map3_s00/nonmatchings/map3_s00", func_800D18DC);

INCLUDE_ASM("asm/maps/map3_s00/nonmatchings/map3_s00", func_800D1A98);

INCLUDE_RODATA("asm/maps/map3_s00/nonmatchings/map3_s00", D_800CB3F4);

INCLUDE_RODATA("asm/maps/map3_s00/nonmatchings/map3_s00", D_800CB3FC);

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CB37C);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CB4E4

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CB664

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CB71C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CB880

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CB8A0

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CC118

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CC504);

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CCB10

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CCF60

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CCF9C

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CCFA8

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CD108

s32 func_800CD2E0()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CD2E8

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CD398

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CD3B0

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CD3D8

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CD3F0

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CD418

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CD4BC

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CD4CC

void func_800CD4D8(void) {}

void func_800CD4E0(void) {}

void func_800CD4E8(void) {}

void func_800CD4F0(void) {}

void func_800CD4F8(void) {}

s32 func_800CD500()
{
    return 0;
}

void func_800CD508(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CD510

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CD520

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CD560

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800CD574

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800CD6BC

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800CD7E4

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800CD804

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CD844);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CD8B8);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CD908);

#include "maps/shared/sharedFunc_800CDA88_3_s03.h" // 0x800CD94C

#include "maps/shared/Ai_PuppetNurse_UpdateMain.h" // 0x800CD97C

#include "maps/shared/Ai_PuppetNurse_Init.h" // 0x800CDA20

#include "maps/shared/Ai_PuppetNurse_Update.h" // 0x800CDBF4

#include "maps/shared/Ai_PuppetDoctor_Update.h" // 0x800CDC50

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CDCAC);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CDF24_3_s03); // 0x800CDDE8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CDFA8);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CE25C);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CE3CC_3_s03); // 0x800CE290

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CE500_3_s03); // 0x800CE3C4

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CE5E4_3_s03); // 0x800CE4A8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CE68C);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CEA64_3_s03); // 0x800CE928

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CEB90_3_s03); // 0x800CEA54

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CEC88_3_s03); // 0x800CEB4C

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CED70);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CEDA4);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CEF78);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CF158);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CF3AC_3_s03); // 0x800CF270

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CF4C4);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CF6B8);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CF7D0);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CF9F8_3_s03); // 0x800CF8BC

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CFD18_3_s03); // 0x800CFBDC

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CFDD4_3_s03); // 0x800CFC98

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D0110_3_s03); // 0x800CFFD4

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CA618);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CA61C);

#include "maps/shared/Ai_PuppetNurse_Control.h" // 0x800D0094

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D02E4_3_s03); // 0x800D01A8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D03E4_3_s03); // 0x800D02A8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D06AC_3_s03); // 0x800D0570

#include "maps/shared/sharedFunc_800D0828_3_s03.h" // 0x800D06EC

#include "maps/shared/sharedFunc_800D0968_3_s03.h" // 0x800D082C

#include "maps/shared/Ai_Lisa_Update.h" // 0x800D0888

#include "maps/shared/sharedFunc_800D08FC_3_s04.h" // 0x800D08FC

#include "maps/shared/sharedFunc_800D0944_3_s04.h" // 0x800D0944

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedSymbol_800D0ADC_3_s04); // 0x800D0ADC

#include "maps/shared/Ai_Lisa_Init.h" // 0x800D1350

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D1374

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D1388

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D13CC

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D13E4

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D13F0

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D1404

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D1418

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D142C

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D14C8

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D1B2C

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D1B40

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D1B54

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D1C50

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D1CFC

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D1D1C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D1D7C

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D1D8C);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D1E24);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D1E58);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CA72C);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D1E98);

void func_800D2128(void) {}

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D2130);

const char* MAP_MESSAGES[] =
{
    #include "maps/shared/mapMsg_common.h"
    "~J1(3.6)\tFinally. ~N\n\t\t\tSomeone_else_who's_OK. ",
    "~J1(1.0)\tWho_are_you? ",
    "~J1(3.1)\tMy_name's_Lisa_Garland. ~N\n\t\t\tWhat's_yours? ",
    "~J1(1.2)\tHarry_Mason. ~E ",
    "~J0(4.7)\tHarry,_tell_me ~N\n\t\t\twhat's_happening_here? ~N\n\t\t\tWhere_is_everybody? ",
    "~J0(2.7)\tI_must_have_gotten_knocked_out. ",
    "~J0(3.2)\tWhen_I_came_to, ~N\n\t\t\teveryone_was_gone. ",
    "~J0(1.3)\tIt's_awful... ~E ",
    "~J1(3.8)\tSo_you_don't_know ~N\n\t\t\tanything_either.__Great. ",
    "~J1(2.5)\tI_just_don't_get_it. ~E ",
    "~J1(4.0)\tIt's_like_this_is ~N\n\t\t\tall_some_kind_of_bad_dream. ",
    "~J1(2.8)\tYeah. ~N\n\t\t\tA_living_nightmare. ~E ",
    "~J1(3.6)\tLet_me_ask_you,_have_you_seen ~N\n\t\t\ta_little_girl_around_here? ",
    "~J1(2.8)\tShort,_black_hair. ~N\n\t\t\tSeven_years_old. ",
    "~J1(3.8)\tA_seven-year-old_girl? ~N\n\t\t\tWhat?_She's_your_daughter? ",
    "~J1(1.2)\tYes. ",
    "~J1(3.0)\tA_seven-year-old_girl... ",
    "~J1(4.8)\tI_can't_say_that_I_have. ~N\n\t\t\tI_was_unconscious_all_this_time. ",
    "~J1(1.3)\tI'm_sorry. ~E ",
    "~J1(2.2)\tThat's_alright. ",
    "~J1(3.8)\tDo_you_know_anything_about_all ~N\n\t\t\tthat_weird_stuff_in_the_basement? ",
    "~J1(3.8)\tNo.__Why? ~N\n\t\t\tIs_there_something_down_there? ",
    "~J1(2.7)\tYou_don't_know? ~N\n\t\t\tDon't_you_work_here? ",
    "~J1(4.0)\tWe're_under_strict_orders_never_to ~N\n\t\t\tenter_the_basement_storeroom. ",
    "~J1(2.0)\tSo_I_really_don't_know. ~E ",
    "~J1(2.0)\tWhat_did_you_say_was_down_there? ",
    "~J1(1.7)\tWell,_it's... ~E ",
    "~J0(0.8)\t~E ",
    "~J0(2.5)\tDamn! ~N\n\t\t\tMy_head...  ",
    "~J0(2.5)\tWhat's_wrong? ~N\n\t\t\tHarry...? ~E ",
    "~J0(2.6)\tHarry, ~N\n\t\t\tlet_me_help_you. ~E ",
    "~J0(1.0)\t~E ",
    "\tThere_is_ a_ ~C2 Plate_of_[Queen] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tUsed_the_ ~C2 Examination_room_key ~C7 . ~E ",
    "\tThere_is_a_broken ~N\n\tvending_machine. ~E ",
    "\tNothing_unusual. ~E ",
    "\tThe_refrigerator_is_empty. ~E ",
    "\tNothing_helpful. ~E ",
    "\tNothing_useful ~N\n\tin_the_desk_drawer. ~E ",
    "\tA_sound_is_heard ~N\n\tfrom_beyond_the_door. ~E "
};

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CB1E0);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D21C4);

void func_800D2470(void) // 0x800D2470
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 52:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S04_HealthDrink0;
            break;

        case 53:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S04_HealthDrink1;
            break;

        case 54:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S04_HealthDrink2;
            break;

        case 55:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S04_HealthDrink3;
            break;

        case 56:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M3S04_HandgunBullets;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D250C);

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800D25D0

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D2668);

void func_800D2E58(void) // 0x800D2E58
{
    Event_ItemTake(InventoryItemId_PlateOfQueen, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S04_PickupPlateOfQueen, 47);
}

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CB2A8);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CB2B4);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D2E84);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D3BD0);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D3DA4);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800D43B8);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CB35C);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CB364);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CB370);

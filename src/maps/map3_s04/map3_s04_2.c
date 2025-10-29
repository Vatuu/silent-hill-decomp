#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s04.h"

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

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D1D8C

void func_800D1E24(s32 arg0) // 0x800D1E24
{
    (arg0 != 0) ? func_800D1E58() : func_800D1E98();
}

void func_800D1E58(void) // 0x800D1E58
{
    func_8003640C(!Savegame_EventFlagGet(EventFlag_237) ? 8 : 2);
}

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04_2", D_800CA72C);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04_2", func_800D1E98);

void func_800D2128(void) {}

#include "maps/shared/Event_DoorJammed.h" // 0x800D2130

const char* MAP_MESSAGES[] = {
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

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04_2", D_800CB1E0);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04_2", func_800D21C4);

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

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04_2", func_800D250C);

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D25D0

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04_2", func_800D2668);

void func_800D2E58(void) // 0x800D2E58
{
    Event_ItemTake(InventoryItemId_PlateOfQueen, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S04_PickupPlateOfQueen, 47);
}

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04_2", D_800CB2A8);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04_2", D_800CB2B4);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04_2", func_800D2E84);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04_2", func_800D3BD0);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04_2", func_800D3DA4);

void func_800D43B8(void) // 0x800D43B8
{
    if (Savegame_EventFlagGet(EventFlag_300))
    {
        func_80088FF4(Chara_PuppetDoctor, 2, 1);
        func_80088FF4(Chara_PuppetDoctor, 3, 1);
    }
}

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04_2", D_800CB35C);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04_2", D_800CB364);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04_2", D_800CB370);

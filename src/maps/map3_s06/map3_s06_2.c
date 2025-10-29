#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s06.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CFCD8

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CFCEC

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CFD30

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CFD48

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CFD54

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CFD68

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CFD7C

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CFD90

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CFE2C

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D0490

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D04A4

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D04B8

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D05B4

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D0668

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D0688

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D06E8

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D06F8

void func_800D07A0(s32 arg0) // 0x800D07A0
{
    (arg0 != 0) ? sharedFunc_800D0994_3_s00() : sharedFunc_800D09D4_3_s00();
}

#include "maps/shared/sharedFunc_800D0994_3_s00.h" // 0x800D07D4

#include "maps/shared/sharedFunc_800D09D4_3_s00.h" // 0x800D0814

void func_800D09B4(void) {}

#include "maps/shared/Event_DoorJammed.h" // 0x800D09BC

#include "maps/shared/Event_DoorLocked.h" // 0x800D0A50

void func_800D0AE4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.5)\tWas_I_dreaming? ~E ",
    "~J0(2.6)\tYou_were_too_late. ~E ",
    "~J0(1.2)\tIt's_you... ~E ",
    "~J0(3.4)\tYes.__Dahlia_Gillespie. ~E ",
    "~J1(3.0)\tTell_me_everything_you_know. ~N\n\t\t\tWhat's_going_on? ",
    "~J1(1.5)\tDarkness. ",
    "~J1(3.9)\tThe_town_is_being_devoured ~N\n\t\t\tby_darkness. ",
    "~J1(5.8)\tStrength_must_overcome ~N\n\t\t\tpetty_desire. ~N\n\t\t\tChildish_sleep_talk. ",
    "~J1(3.4)\tI_knew_this_day_would_come. ",
    "~J1(4.0)\tWhat_are_you_talking_about? ~N\n\t\t\tI_don't_understand_a_word_of_this. ~E ",
    "~J0(3.8)\tBelieve_the_evidence ~N\n\t\t\tof_your_eyes. ",
    "~J0(5.3)\tThe_other_church_in_this_town. ~N\n\t\t\tThat_is_your_destination. ",
    "~J0(6.5)\tThis_is_beyond_my_abilities. ~N\n\t\t\tOnly_you_can_stop_it_now. ~E ",
    "~J0(5.0)\tHave_you_not_seen ~N\n\t\t\tthe_crest_marked ~N\n\t\t\ton_the_ground_all_over_town? ",
    "~J0(3.2)\tSo_that's_what_I_saw ~N\n\t\t\tin_the_schoolyard. ",
    "~J0(1.2)\tWhat_does_it_mean? ",
    "~J0(3.1)\tIt_is_the_mark_of_Samael... ",
    "~J0(2.8)\tDon't_let_it_be_completed. ~E ",
    "~J0(1.8)\tHey!__Wait! ~E ",
    "\tThe_elevator_doesn't ~N\n\tappear_to_be_working. ~E ",
    "~H\tThere_is_a_ ~C5 Hospital_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_an_ ~C2 Antique_shop_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThese_are_phones_and_phonebooks. ~N\n\tNo_need_to_examine_this. ~E ",
    "\tThese_are_phones_and_phonebooks. ",
    "\tI'll_copy_the_location_of ~N\n\tthe_antique_shop_to_the_map. ~E ",
    "\tThere's_a_vending_machine. ~N\n\tIt_doesn't_work. ~E ",
    "\tThere_is_a_newspaper. ",
    "\tThis_article's_been ~N\n\tclipped_out... ~E ",
    "\tNothing_unusual. ~E ",
    "\tThere's_a_white_board. ~N\n\tNothing_special_written_here. ~E ",
    "\tNothing_helpful. ~E ",
    "\tThe_phone's_out. ~N\n\tCan't_get_a_dial_tone. ~E "
};

void func_800D0AEC(void) // 0x800D0AEC
{
    Event_CommonItemTake(CommonPickupItemId_FirstAidKit, EventFlag_M3S00_FirstAidKit);
}

void func_800D0B10(void) // 0x800D0B10
{
    const static VECTOR3 D_800CB21C = { Q12(61.72f), Q12(-0.8f), Q12(100.51f) };

    if (g_SysWork.sysStateStep_C[1] == 0)
    {
        func_8005DC1C(Sfx_Unk1308, &D_800CB21C, 128, 0);
    }

    func_80087360(FILE_TIM_NEWSP1_TIM, Q12(0.0f), Q12(0.0f), 41);
    Savegame_EventFlagSet(EventFlag_203);
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D0B7C

INCLUDE_ASM("asm/maps/map3_s06/nonmatchings/map3_s06_2", func_800D0C14);

void func_800D17B0(void) // 0x800D17B0
{
    Event_MapTake(17, EventFlag_M3S00_PickupMap, 35);
}

void func_800D17D8(void) // 0x800D17D8
{
    Event_ItemTake(InventoryItemId_AntiqueShopKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S06_PickupAntiqueShopKey, 36);
}

INCLUDE_ASM("asm/maps/map3_s06/nonmatchings/map3_s06_2", func_800D1804);

INCLUDE_ASM("asm/maps/map3_s06/nonmatchings/map3_s06_2", func_800D197C);

INCLUDE_RODATA("asm/maps/map3_s06/nonmatchings/map3_s06_2", D_800CB2D4);

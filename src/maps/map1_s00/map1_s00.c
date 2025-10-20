#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s00.h"

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB7A8

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CBC34

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CBD0C

#include "maps/shared/Particle_Update.h" // 0x800CC018

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800CEB24_0_s00); // 0x800CC59C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC914

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800CEFD0_1_s02); // 0x800CCA64

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800CFFF8_0_s00); // 0x800CCE2C

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CCF40

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CCF48

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CD000

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CD088

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD208

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD2C0

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CD458

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CD478

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CDCF0

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CE0DC

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CE610

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CEA3C

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CEA78

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CEA84

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CEBE4

s32 func_800CEDBC()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CEDC4

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CEE74

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CEE8C

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CEEB4

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CEECC

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CEEF4

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CEF98

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CEFA8

void func_800CEFB4(void) {}

void func_800CEFBC(void) {}

void func_800CEFC4(void) {}

void func_800CEFCC(void) {}

void func_800CEFD4(void) {}

s32 func_800CEFDC()
{
    return 0;
}

void func_800CEFE4(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CEFEC

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CEFFC

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CF03C

#include "maps/shared/Ai_LarvalStalker_Update.h" // 0x800CF050

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800CF168_1_s00); // 0x800CF168

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D140C_1_s00); // 0x800D140C

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D1524_1_s00); // 0x800D1524

#include "maps/shared/Ai_LarvalStalker_Init.h" // 0x800D16FC

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D17BC_1_s00); // 0x800D17BC

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D1DBC_1_s00); // 0x800D1DBC

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D24F8

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D268C

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D3308_0_s00); // 0x800D28F8

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D3134

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D34E4

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D4924_0_s00); // 0x800D34EC

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D492C_0_s00); // 0x800D40BC

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D4828

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D54A8_0_s00); // 0x800D4C38

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D52D8

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D5C64_0_s00); // 0x800D53F4

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D575C

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D5B60

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D5CDC

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D5CE4

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D5E9C

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D5F8C

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D6970_0_s00); // 0x800D6100

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D70C4_0_s00); // 0x800D6854

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D7378

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D7594

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D7748

#include "maps/shared/sharedFunc_800D7758_1_s00.h" // 0x800D7758

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D77F8);

void func_800D7864(void) {}

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D786C);

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D7900);

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D7994);

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tThe_tower_door_is_locked. ~E ",
    "\tThe_hands_are_stopped_at_10:00. ~E ",
    "\tThe_hands_are_stopped_at_12:00. ~E ",
    "\tThe_hands_are_stopped_at_5:00. ~E ",
    "\t~C3 A_Golden_Sun ~E ",
    "\t~C3 A_Silver_Moon ~E ",
    "\tThe_door_won't_open. ~E ",
    "~L4 ~M ~C3 10:00 ~N\n\t[Alchemy_laboratory] ~N\n\t~N\n\tGold_in_an_old_man's_palm. ~N\n\tThe_future_hidden_in_his_fist. ~N\n\tExchange_for_sage's_water. ~E ",
    "~L4 ~M ~C3 12:00 ~N\n\t[A_place_with_songs_and_sound] ~N\n\t~N\n\tA_silver_guidepost_is ~N\n\tuntapped_in_lost_tongues. ~N\n\tAwakening_at_the_ordained_order. ~E ",
    "~L4 ~M ~C3 5:00 ~N\n\t[Darkness_that_brings ~N\n\tthe_choking_heat] ~N\n\t~N\n\tFlames_render_the_silence, ~N\n\tawakening_the_hungry_beast. ~N\n\tOpen_time's_door_to_beckon_prey. ~E ",
    "\tIt's_written_in_blood. ~E ",
    "\tCheryl_might_be_here. ~N\n\tI_should_search_for_her. ~E ",
    "\tA_picture_of_a_door. ",
    "\tI_don't_know_who_drew_it, ~N\n\tbut_it_is_certainly_in_bad_taste. ~E ",
    "\tThere_is_a_switch. ~N\n\tDo_you_want_to_press_the_switch? ~S4 ",
    "\tNothing_appears_to_happen. ~E ",
    "\tThe_boiler_is_working. ~E ",
    "\tIt_appears_to_be_broken. ~E ",
    "\tThe_valve_is_tightly_shut. ~N\n\tCan't_move_it. ",
    "\tDon't_know_what_it_is_for, ~N\n\tbetter_leave_it_alone. ~E ",
    "\tNothing_special_is_written. ~E ",
    "\tNothing_useful ~N\n\tin_the_desk_drawer. ~E ",
    "~H\tThere_is_a_ ~C5 School_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tMoore,_Ranaldo,_Gordon... ~N\n\tThis_must_be_the_list_of_teachers. ~E ",
    "\tNothing_inside. ~E "
};

void func_800D7A28(void) // 0x800D7A28
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 94:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S00_HandgunBullets0;
            break;

        case 95:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S00_HandgunBullets1;
            break;

        case 96:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S00_HandgunBullets2;
            break;

        case 97:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S00_HealthDrink;
            break;

        case 98:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M1S00_FirstAidKit;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D7AC4(void) // 0x800D7AC4
{
    g_DeltaTime0 = 0;
    func_80087360(FILE_TIM_GOLD1_TIM, Q12(2.5f), Q12(2.0f), 19);
}

void func_800D7AF8(void) // 0x800D7AF8
{
    g_DeltaTime0 = 0;
    func_80087360(FILE_TIM_GOLD2_TIM, Q12(2.5f), Q12(2.0f), 19);
}

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D7B2C);

void func_800D7E48(void) // 0x800D7E48
{
    g_DeltaTime0 = 0;
    func_80087360(FILE_TIM_SILVER1_TIM, Q12(2.5f), Q12(2.0f), 20);
}

void func_800D7E7C(void) // 0x800D7E7C
{
    g_DeltaTime0 = 0;
    func_80087360(FILE_TIM_SILVER2_TIM, Q12(2.5f), Q12(2.0f), 20);
}

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D7EB0);

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D81CC);

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D8354);

void func_800D853C(void) // 0x800D853C
{
    func_80087540(FILE_TIM_PAPER1_TIM, Q12(2.5f), Q12(1.5f), 25, 22);
}

void func_800D8570(void) // 0x800D8570
{
    func_80087540(FILE_TIM_PAPER2_TIM, Q12(2.5f), Q12(1.5f), 25, 23);
}

void func_800D85A4(void) // 0x800D85A4
{
    func_80087540(FILE_TIM_PAPER3_TIM, Q12(2.5f), Q12(1.5f), 25, 24);
}

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D85D8);

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D8948);

void func_800D8CC4(void) // 0x800D8CC4
{
    func_80087360(FILE_TIM_RECEPPIC_TIM, Q12(0.0f), Q12(0.0f), 27);
}

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", D_800CB670);

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", D_800CB67C);

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", D_800CB684);

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D8CF0);

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D8FE0);

void func_800D9148(void) // 0x800D9148
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 31, 0, 0, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    func_800894B8(0x60); // Hex?
}

void func_800D922C(void) // 0x800D922C
{
    Event_MapTake(6, EventFlag_M1S00_PickupMap, 37);
}

void func_800D9254(void) // 0x800D9254
{
    g_BackgroundColor = 104;
    func_80087360(FILE_TIM_USCBOOK_TIM, Q12(0.0f), Q12(0.0f), 38);
}

void func_800D928C(void) // 0x800D928C
{
    sharedFunc_800D20E4_0_s00();
    sharedFunc_800D2244_0_s00(false);
    SysWork_StateSetNext(SysState_Gameplay);
}

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D92D8);

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", func_800D9764);

void func_800DA3FC(void) // 0x800DA3FC
{
    if (Savegame_EventFlagGet(EventFlag_M1S01_PickupSilverMedallion))
    {
        func_80088FF4(Chara_GreyChild, 0, 3);
        func_80088FF4(Chara_GreyChild, 1, 3);
    }
}

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", D_800CB784);

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", D_800CB790);

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", D_800CB79C);

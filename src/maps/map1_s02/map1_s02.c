#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s02.h"

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800CBA4C);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800CBC98);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800CBD58);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800CBDA8);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800CCE60);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CDA4C

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CDE40

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CDF18

#include "maps/shared/Particle_Update.h" // 0x800CE234

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800CEFF4_0_s00); // 0x800CE844

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CEF34

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CEFD0

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800CFFF8_0_s00); // 0x800CF2B4

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF374

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF37C

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF434

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CF4F4

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CF69C

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CF754

#include "maps/shared/sharedFunc_800D0CB8_0_s00.h" // 0x800CF8F4

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CFA40

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CFA60

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800D02D8

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800D06C4

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800D1624

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D1AAC

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D1AE8

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D1AF4

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D1C54

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800D1E2C);

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D26BC

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D276C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D2784

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D27AC

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D27C4

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D27EC

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D2890

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D28A0

void func_800D28AC(void) {}

void func_800D28B4(void) {}

void func_800D28BC(void) {}

void func_800D28C4(void) {}

void func_800D28CC(void) {}

s32 func_800D28D4()
{
    return 0;
}

void func_800D28DC(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D28E4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D28F4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D2934

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D2948

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D2ADC

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D3308_0_s00); // 0x800D2D48

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D3584

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D3934

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D4924_0_s00); // 0x800D393C

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D492C_0_s00); // 0x800D450C

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D4C78

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D54A8_0_s00); // 0x800D5088

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D5728

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D5C64_0_s00); // 0x800D5844

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D5BAC

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D5FB0

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D612C

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6134

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D62EC

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D63DC

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D6970_0_s00); // 0x800D6550

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D70C4_0_s00); // 0x800D6CA4

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D77C8

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D79E4

#include "maps/shared/Ai_Creaper_Update.h" // 0x800D7B98

#include "maps/shared/Ai_Creaper_Init.h" // 0x800D7C28

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D7EE8_1_s02); // 0x800D7EE8

#include "maps/shared/sharedFunc_800D8244_1_s02.h" // 0x800D8244

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D82F0_1_s02);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D8684_1_s02);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D8F30_1_s02);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D9528_1_s02);

#include "maps/shared/sharedFunc_800D9774_1_s02.h" // 0x800D9774

#include "maps/shared/sharedFunc_800D983C_1_s02.h" // 0x800D983C

#include "maps/shared/sharedFunc_800D9960_1_s02.h" // 0x800D9960

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D99D0_1_s02); // 0x800D99D0

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D9E0C

#include "maps/shared/sharedFunc_800D7758_1_s00.h" // 0x800D9E1C

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800D9EBC);

void func_800DA018(void) {}

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DA020);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DA0B4);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DA16C);

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.2)\tWhere_am_I? ~E ",
    "~J0(2.0)\tHave_I_been_here_before? ~E ",
    "~J0(3.8)\tI_don't_remember ~N\n\t\t\tthis_being_here_before... ~E ",
    "\tThe_tower_door_is_locked. ~E ",
    "\t",
    "\t",
    "\t~C5 A_Golden_Sun ~C7 ~E ",
    "\t~C5 A_Silver_Moon ~C7 ~E ",
    "\tWhat? ~N\n\tIs_this_a_door? ",
    "\tIf_it_is,_there's_no_keyhole, ~N\n\tor_even_a_knob... ",
    "\tIf_I_push_it,_it_moves_a_bit, ~N\n\tbut_it_certainly_won't_open. ~E ",
    "\tWhat's_this? ~E ",
    "\tIn_the_center_of_the_door_is ~N\n\ta_horizontal_slot. ",
    "\tWhat_is_it_for? ~E ",
    "\tThere_is_a_ ~C2 Picture_card ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tSlid_the_ ~C2 Picture_card ~C7 ~N\n\tinto_the_slot. ~E ",
    "~J0(0.9)\t_ ",
    "~J0(3.0)\tDaddy==_help_me=== ",
    "~J0(3.0)\t==Daddy==where_are_you==? ",
    "~D ~J0(2.0)\n\tCheryl! ~E ",
    "~J1(2.4)\n\tThat_was_Cheryl's_voice. ~N\n\tI_know_it. ",
    "~J1(2.0)\n\tWhere_is_she? ~N\n\tCheryl... ~E ",
    "\tThere_is_a_ ~C2 Rubber_ball ~C7 . ~N\n\tTake_it? ~S4 ",
    "\t~C5 Leonard_Rhine ~N\n\tThe_Monster_Lurks ~C7 ",
    "\tThe_monster_lurks... ~N\n\tWhat's_that_supposed_to_mean? ~E ",
    "\tThere_is_a_ ~C2 Shotgun ~C7 . ~N\n\tTake_it? ~S4 ",
    "\t_ ~S3 ",
    "\tTurn_the_valve_left. ",
    "\tTurn_the_valve_right. ",
    "\tStop_turning_the_valve. ",
    "\tCards_are_scattered... ~E ",
    "\tA_wheelchair? ~N\n\tAt_an_elementary_school? ~E ",
    "\tLocker_is_locked. ~E ",
    "\tA_huge_fan_is_rotating. ",
    "\tIf_approached_carelessly, ~N\n\tI_may_be_sucked_in. ~E ",
    "\tCan't_use_the_phone. ~E ",
    "\tThere_is_a_ ~C2 Classroom_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tA_hanging_body... ~N\n\tWhy_would_somebody... ~E ",
    "\tA_doll_is_on_the_floor. ~E ",
    "\tA_headless_doll_is_stuck ~N\n\tto_the_wall. ~E "
};

void func_800DA200(void) // 0x800DA200
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 107:
            pickupType   = CommonPickupItemId_Ampoule;
            eventFlagIdx = EventFlag_M1S02_Ampoule0;
            break;

        case 108:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M1S02_ShotgunShells0;
            break;

        case 109:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M1S02_ShotgunShells1;
            break;

        case 110:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M1S02_FirstAidKit0;
            break;

        case 111:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S02_HandgunBullets0;
            break;

        case 112:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S02_HandgunBullets1;
            break;

        case 113:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S02_HandgunBullets2;
            break;

        case 114:
            pickupType   = CommonPickupItemId_Ampoule;
            eventFlagIdx = EventFlag_M1S02_Ampoule1;
            break;

        case 115:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S02_HealthDrink0;
            break;

        case 116:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M1S02_FirstAidKit1;
            break;

        case 117:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S02_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DA2E4);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DA384);

void func_800DA8F8(void) // 0x800DA8F8
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
            MapMsg_DisplayAndHandleSelection(false, 0x12, 0, 0, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DA9D4(void) // 0x800DA9D4
{
    func_80087360(FILE_TIM_GOLD2_TIM, Q12(3.0f), Q12(2.5f), 21);
}

void func_800DAA00(void) // 0x800DAA00
{
    func_80087360(FILE_TIM_SILVER2_TIM, Q12(3.0f), Q12(2.5f), 22);
}

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DAA2C);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DAD2C);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CB854);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CB860);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DB058);

void func_800DB310(void) // 0x800DB310
{
    Event_ItemTake(InventoryItemId_PictureCard, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M1S02_PickupPictureCard, 29);
}

void func_800DB33C(void) // 0x800DB33C
{
    Event_ItemTake(InventoryItemId_RubberBall, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M1S02_PickupRubberBall, 37);
}

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DB368);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DBB7C);

void func_800DBF88(void) // 0x800DBF88
{
    Savegame_EventFlagSet(EventFlag_97);
    func_80087360(FILE_TIM_LVTRYMSG_TIM, Q12(0.0f), Q12(0.0f), 38);
}

void func_800DBFC8(void) // 0x800DBFC8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0, InventoryItemId_Shotgun, 0, false);
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 59, false);
            SysWork_StateStepIncrement();

        case 3:
            func_80086470(1, InventoryItemId_Shotgun, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            break;

        case 5:
            if (Gfx_PickupItemAnimate(InventoryItemId_Shotgun))
            {
                MapMsg_DisplayAndHandleSelection(true, 40, 6, 7, 0, false);
            }

            Savegame_EventFlagSet(EventFlag_M1S02_PickupShotgun);
            break;

        case 6:
            func_80086470(3, InventoryItemId_Shotgun, SHOTGUN_AMMO_PICKUP_ITEM_COUNT, false);
            SysWork_NextStateStepSet(8);
            break;

        case 7:
            Savegame_EventFlagClear(EventFlag_M1S02_PickupShotgun);
            SysWork_StateStepIncrement();

        case 8:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CB934);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CB940);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CB94C);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DC1E0);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DCF00);

void func_800DD208(void) // 0x800DD208
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0, InventoryItemId_ClassroomKey, 0, false);
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 59, false);
            SysWork_StateStepIncrement();

        case 3:
            func_80086470(1, InventoryItemId_ClassroomKey, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            break;

        case 5:
            if (Gfx_PickupItemAnimate(InventoryItemId_ClassroomKey))
            {
                MapMsg_DisplayAndHandleSelection(true, 51, 6, 7, 0, false);
            }

            Savegame_EventFlagSet(EventFlag_M1S02_PickupClassroomKey);
            break;

        case 6:
            func_80086470(3, InventoryItemId_ClassroomKey, 1, false);
            SysWork_NextStateStepSet(8);
            break;

        case 7:
            Savegame_EventFlagClear(EventFlag_M1S02_PickupClassroomKey);
            SysWork_StateStepIncrement();

        case 8:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}
void func_800DD420(void) // 0x800DD420
{
    sharedFunc_800D08B8_0_s00(6, 127);

    sharedFunc_800CB6B0_0_s00(0, g_SavegamePtr->mapOverlayId_A4, 0);

    Savegame_EventFlagClear(EventFlag_225);

    SysWork_StateSetNext(SysState_Gameplay);
}

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DD494);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DDA84);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DEC88);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CBA44);

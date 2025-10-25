#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
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

void Event_Boiler0(void)
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 1:
            func_80085DF0();
            break;
        case 2:
            g_SysWork.silentYesSelection_2350_4 = 1;
            MapMsg_DisplayAndHandleSelection(true, 29, 3, -1, 0, false); // Do you want to press the switch?
            break;
        case 3:
            func_8005DC1C(Sfx_Unk1420, &QV3(20.5f, -1.2f, -17.5f), 0x80, 0);
            Savegame_EventFlagSet(EventFlag_83);
            SysWork_StateStepIncrement();
    
            /* fallthrough */
        case 4:
            func_80085E6C(Q12(1.0f), false);
            break;
        case 5:
            D_800DD718 += g_DeltaTime0;
            if ((D_800DD718 % Q12(0.8499f)) < Q12(0.45f))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObj0.object_0, &g_WorldObj0.position_1C, &(SVECTOR3){});
            }
            if (D_800DD718 > Q12(3.5f))
            {
                SysWork_StateStepIncrement();
            }
            break;
        case 6:
            func_8005DC1C(Sfx_Unk1422, &QV3(18.8f, 4.0f, -17.5f), 0x80, 0);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 7:
            Savegame_EventFlagSet(EventFlag_73);
            func_80085E6C(Q12(1.5f), false);
            break;
        case 8:
            SysWork_NextStateStepSet(NO_VALUE);
            Savegame_EventFlagSet(EventFlag_84);
            break;
        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    if (Savegame_EventFlagGet(EventFlag_73))
    {
        func_800894B8(0x70);
    }
    else if (Savegame_EventFlagGet(EventFlag_83))
    {
        func_800894B8(0x90);
    }
}

void Event_Boiler1(void)
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 1:
            func_80085DF0();
            break;
        case 2:
            g_SysWork.silentYesSelection_2350_4 = 1;
            MapMsg_DisplayAndHandleSelection(true, 29, 3, -1, 0, false); // Do you want to press the switch?
            break;
        case 3:
            func_8005DC1C(Sfx_Unk1420, &QV3(20.5f, -1.2f, -17.5f), 0x80, 0);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 4:
            func_80085E6C(Q12(0.5f), false);
            break;
        case 5:
            MapMsg_DisplayAndHandleSelection(false, 30, 0, 0, 0, false); // Nothing appears to happen.
            break;
        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_Boiler2(void) // 0x800D9148
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
            MapMsg_DisplayAndHandleSelection(false, 31, 0, 0, 0, false); // The boiler is working.
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

void Map_WorldObjectsInit(void)
{
    D_800E1180 = 0;
    D_800E1182 = 0;
    WorldObjectPositionInit(&g_WorldObj9.position_1C, 133.294f, -0.8614f, 19.04f, 0.0f, 162.6f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObj9.object_0, "PICT00_H");

    Math_Vector3Set(&g_WorldObj1[0].position_1C, Q12(133.63f), Q12(-0.816f), Q12(17.089f));
    WorldObject_ModelNameSet(&g_WorldObj1[0].object_0, "PAPER1_H");

    Math_Vector3Set(&g_WorldObj1[1].position_1C, Q12(133.991f), Q12(-0.8f), Q12(16.307f));
    WorldObject_ModelNameSet(&g_WorldObj1[1].object_0, "NOTE_HID");

    Math_Vector3Set(&g_WorldObj1[2].position_1C, Q12(133.6f), Q12(-1.7f), Q12(16.0f));
    WorldObject_ModelNameSet(&g_WorldObj1[2].object_0, "TINORI1_");

    Math_Vector3Set(&g_WorldObj1[3].position_1C, Q12(133.6f), Q12(-1.19f), Q12(18.2f));
    WorldObject_ModelNameSet(&g_WorldObj1[3].object_0, "TINORI2_");

    Math_Vector3Set(&g_WorldObj1[4].position_1C, Q12(134.486f), Q12(-1.19f), Q12(18.2f));
    WorldObject_ModelNameSet(&g_WorldObj1[4].object_0, "TINORI3_");

    Math_Vector3Set(&g_WorldObj1[5].position_1C, Q12(134.4f), Q12(-0.91f), Q12(17.9568f));
    WorldObject_ModelNameSet(&g_WorldObj1[5].object_0, "GRID2_HI");

    Math_Vector3Set(&g_WorldObj2.position_1C, Q12(-12.2f), Q12(-1.0999f), Q12(-67.88f));
    WorldObject_ModelNameSet(&g_WorldObj2.object_0, "GOLD_HID");

    Math_Vector3Set(&g_WorldObj3.position_1C, Q12(-13.5198f), Q12(-1.0999f), Q12(-69.0999f));
    WorldObject_ModelNameSet(&g_WorldObj3.object_0, "SILVER_H");

    Math_Vector3Set(&g_WorldObj4.position_1C, Q12(-12.72f), Q12(-1.0f), Q12(-68.5999f));
    WorldObject_ModelNameSet(&g_WorldObj4.object_0, "ANA3_HID");

    Math_Vector3Set(&g_WorldObj5.position_1C, Q12(-12.7898f), Q12(-1.0f), Q12(-69.6199f));
    WorldObject_ModelNameSet(&g_WorldObj5.object_0, "ANA2_HID");

    Math_Vector3Set(&g_WorldObj6[0].position_1C, Q12(20.4568f), Q12(-0.8345f), Q12(-17.97f));
    WorldObject_ModelNameSet(&g_WorldObj6[0].object_0, "REDX_HID");

    Math_Vector3Set(&g_WorldObj6[1].position_1C, Q12(19.5799f), Q12(0.0f), Q12(-18.3f));
    WorldObject_ModelNameSet(&g_WorldObj6[1].object_0, "R_HIDE_I");

    Math_Vector3Set(&g_WorldObj0.position_1C, Q12(19.5799f), Q12(0.0f), Q12(-18.3f));
    WorldObject_ModelNameSet(&g_WorldObj0.object_0, "G_HIDE_I");

    WorldObjectPositionInit(&g_WorldObj7.position_1C, 61.8531f, -0.805f, 140.6099f, 0.0f, 92.9f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObj7.object_0, D_800A99E4.savePadName_4);

    WorldObjectPositionInit(&g_WorldObj8.position_1C, 96.9405f, -0.3365f, 21.0918f, 0.0f, 66.8f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObj8.object_0, "MAP_HIDE");

    func_8004EE94(InventoryItemId_NoteToSchool, 1);
    Savegame_EventFlagSet(EventFlag_147);
    if (g_SavegamePtr->gameDifficulty_260 == -1)
    {
        func_80088FF4(Chara_GreyChild, 3, 0);
        func_80088FF4(Chara_GreyChild, 9, 0);
    }
    if (g_SavegamePtr->gameDifficulty_260 == 1)
    {
        func_80088FF4(Chara_GreyChild, 10, 11);
        func_80088FF4(Chara_GreyChild, 11, 3);
        func_80088FF4(Chara_GreyChild, 12, 3);
        func_80088FF4(Chara_GreyChild, 13, 3);
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void)
{
    s32 i;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (!Savegame_EventFlagGet(EventFlag_226))
    {
        Savegame_EventFlagSet(EventFlag_226);
        func_8003A16C(g_SavegamePtr);
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (Savegame_EventFlagGet(EventFlag_71))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj2.object_0, &g_WorldObj2.position_1C, &(SVECTOR3){});
        }
        else
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj4.object_0, &g_WorldObj4.position_1C, &(SVECTOR3){});
        }
        
        if (Savegame_EventFlagGet(EventFlag_72))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj3.object_0, &g_WorldObj3.position_1C, &(SVECTOR3){});
        }
        else
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj5.object_0, &g_WorldObj5.position_1C, &(SVECTOR3){});
        }
        
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!D_800E1180)
        {
            D_800E1180 = 1;
            Sd_PlaySfx(Sfx_Unk1359, 0, 232);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (D_800E1180 == 1)
        {
            D_800E1180 = 2;
            Sd_PlaySfx(Sfx_Unk1359, 0, 216);
        }
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObj7.object_0, &g_WorldObj7.position_1C.position_0, &g_WorldObj7.position_1C.rotation_C);
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (Savegame_EventFlagGet(EventFlag_72))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj6[1].object_0, &g_WorldObj6[1].position_1C, &(SVECTOR3){});
            func_80064F04(&QV3(20.58f, -1.14f, -17.41f), 0, 0x385);
        }
        else
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj6->object_0, &g_WorldObj6->position_1C, &(SVECTOR3){});
        }
        if (Savegame_EventFlagGet(EventFlag_73))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj0.object_0, &g_WorldObj0.position_1C, &(SVECTOR3){});
        }
        if (Savegame_EventFlagGet(EventFlag_72))
        {
            if (D_800E1182 == 0)
            {
                Sd_EngineCmd(Sfx_Unk1430);
            }
            if (!Savegame_EventFlagGet(EventFlag_84))
            {
                if (Savegame_EventFlagGet(EventFlag_83))
                {
                    D_800E1182 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.15f), Q12_SHIFT);
                    if (D_800E1182 > Q12(1.0f))
                    {
                        D_800E1182 = Q12(1.0f);
                    }
                }
                else
                {
                    D_800E1182 = Q12(0.0999f);
                }
            }
            else
            {
                D_800E1182 = Q12(1.0f);
            }
            func_8005DE0C(Sfx_Unk1430, &QV3(18.8f, -1.0f, -17.5f), D_800E1182 >> 5, Q12(24.0f), 0);
        }
    }

    else if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (Savegame_EventFlagGet(EventFlag_84))
        {
            if (!D_800E1182)
            {
                Sd_EngineCmd(Sfx_Unk1430);
            }
            D_800E1182 = Q12(0.2f);
            func_8005DE0C(Sfx_Unk1430, &QV3(52.0f, -1.0f, -16.0f), 25, Q12(16.0f), 0);
        }
    }
    else
    {
        if (D_800E1182)
        {
            func_8004690C(Sfx_Unk1430);
        }
        D_800E1182 = 0;
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObj9.object_0, &g_WorldObj9.position_1C.position_0, &g_WorldObj9.position_1C.rotation_C);
        for (i = 0; i < 6; i++)
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj1[i].object_0, &g_WorldObj1[i].position_1C, &(SVECTOR3){});
        }
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_PickupMap))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj8.object_0, &g_WorldObj8.position_1C.position_0, &g_WorldObj8.position_1C.rotation_C);
        }
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_HandgunBullets0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectsPos[0].position_0, &g_CommonWorldObjectsPos[0].rotation_C);
        }     
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_HandgunBullets1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectsPos[1], &g_CommonWorldObjectsPos[1].rotation_C);
        }
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_HandgunBullets2))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectsPos[2], &g_CommonWorldObjectsPos[2].rotation_C);
        }
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_HealthDrink))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectsPos[3], &g_CommonWorldObjectsPos[3].rotation_C);
        }
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_FirstAidKit))
        {
            g_WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectsPos[4], &g_CommonWorldObjectsPos[4].rotation_C);
        }
    }
}

void func_800DA3FC(void) // 0x800DA3FC
{
    if (Savegame_EventFlagGet(EventFlag_M1S01_PickupSilverMedallion))
    {
        func_80088FF4(Chara_GreyChild, 0, 3);
        func_80088FF4(Chara_GreyChild, 1, 3);
    }
}

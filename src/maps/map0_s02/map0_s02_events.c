#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tThere_is_a_ ~C2 Chain_saw ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tSome_oil_cans_are_on_the_shelf. ~E ",
    "\tA_car_engine. ~N\n\tNo_problem_there. ~E ",
    "\tThere's_a_TV_set. ~N\n\tIt_doesn't_turn_on. ~E ",
    "\tThere_is_a_ ~C2 Gasoline_tank ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Katana ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Channeling_stone ~C7 . ~N\n\tTake_it? ~S4 "
};

void MapEvent_CommonItemTake(void) // 0x800CEBC8
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;
    switch (g_MapEventParam->field_5)
    {
        case 29:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M0S02_FirstAidKit;
            break;

        case 30:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S02_HealthDrink0;
            break;
            
        case 31:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S02_HealthDrink1;
            break;

        case 32:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S02_HealthDrink2;
            break;

        case 33:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M0S02_HandgunBullets;
            break;

        case 34:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S02_HealthDrink3;
            break;

        case 35:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S02_HealthDrink4;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void MapEvent_EmptyFunction(void) {}

void MapEvent_GasolineTankItemTake(void) // 0x800CEC84
{
    Event_ItemTake(InventoryItemId_GasolineTank, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S02_PickupGasolineTank, 19);
}

void MapEvent_KatanaItemTake(void) // 0x800CECB0
{
    Event_ItemTake(InventoryItemId_Katana, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S02_PickupKatana, 20);
}

void MapEvent_ChannelingStoneItemTake(void) // 0x800CECDC
{
    Event_ItemTake(InventoryItemId_ChannelingStone, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S02_PickupChannelingStone, 21);
}

extern s_WorldObject_0 g_WorldObj_Winr[8];
extern VECTOR3 g_WorldObj_Pos_Winr;
extern s_WorldObject_0 g_WorldObj_SavePad;
extern s_WorldObjectPos g_WorldObj_Pos_SavePad0;
extern s_WorldObjectPos g_WorldObj_Pos_SavePad1;
extern s_WorldObjectPos g_WorldObj_Pos_SavePad2;
extern s_WorldObjectDesc g_WorldObject_Gas;
extern s_WorldObjectDesc g_WorldObject_Katana;
extern s8 D_800D3474;
extern s_WorldObjectDesc g_WorldObject_Cosmo;
extern s_WorldObject_0 g_CommonWorldObjects[6];

void Map_WorldObjectsInit(void)
{
    D_800D3474 = 0;
    if (!Savegame_EventFlagGet(EventFlag_131) && Savegame_EventFlagGet(EventFlag_159))
    {
        func_8003ED74(7, 4);
    }

    WorldObject_ModelNameSet(&g_WorldObj_Winr[0], "WINR_0_N");
    WorldObject_ModelNameSet(&g_WorldObj_Winr[2], "WINR_1_H");
    WorldObject_ModelNameSet(&g_WorldObj_Winr[4], "WINR_2_H");
    WorldObject_ModelNameSet(&g_WorldObj_Winr[6], "WINR_4_N");
    WorldObject_ModelNameSet(&g_WorldObj_Winr[1], "WINU_0_N");
    WorldObject_ModelNameSet(&g_WorldObj_Winr[3], "WINU_1_H");
    WorldObject_ModelNameSet(&g_WorldObj_Winr[5], "WINU_2_H");
    WorldObject_ModelNameSet(&g_WorldObj_Winr[7], "WINU_4_N");

    Math_Vector3Set(&g_WorldObj_Pos_Winr, Q12(-100.0f), Q12(0.0f), Q12(20.0f));
    WorldObject_ModelNameSet(&g_WorldObj_SavePad, D_800A99E4.savePadName_4);

    WorldObjectPositionInit(&g_WorldObj_Pos_SavePad0, -100.47f, -1.575f, 22.22f, 0.0f, -75.8f, 0.0f);
    WorldObjectPositionInit(&g_WorldObj_Pos_SavePad1, -178.08f, -0.705f, 22.0298f, 0.0f, 12.1f, 0.0f);
    WorldObjectPositionInit(&g_WorldObj_Pos_SavePad2, -146.4248f, -0.911f, 21.325f, 0.0f, 8.0f, 0.0f);


    WorldObjectPositionInit(&g_WorldObject_Gas.position_1C, -177.2998f, -1.2522f, 21.125f, 0.0f, -145.55f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject_Gas.object_0, "GAS_HIDE");

    Math_Vector3Set(&g_WorldObject_Katana.position_1C.position_0, Q12(-140.8628f), Q12(-0.5511f), Q12(62.3404f));
    WorldObject_ModelNameSet(&g_WorldObject_Katana.object_0, "KATANA1_");

    WorldObjectPositionInit(&g_WorldObject_Cosmo.position_1C, -145.75f, -0.92f, 18.3274f, 0.0f, -55.1f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject_Cosmo.object_0, "COSMO_HI");

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02_events", func_800CEFD4);

INCLUDE_RODATA("asm/maps/map0_s02/nonmatchings/map0_s02_events", D_800CACE8);

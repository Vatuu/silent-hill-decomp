#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"

const char* g_MapMessages[] =
{
    #include "maps/shared/mapMsg_common.h"
    "\tThere_is_a_ ~C2 Chain_saw ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tSome_oil_cans_are_on_the_shelf. ~E ",
    "\tA_car_engine. ~N\n\tNo_problem_there. ~E ",
    "\tThere's_a_TV_set. ~N\n\tIt_doesn't_turn_on. ~E ",
    "\tThere_is_a_ ~C2 Gasoline_tank ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Katana ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Channeling_stone ~C7 . ~N\n\tTake_it? ~S4 ",
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

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02_events", func_800CED08);

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02_events", func_800CEFD4);

INCLUDE_RODATA("asm/maps/map0_s02/nonmatchings/map0_s02_events", D_800CACE8);

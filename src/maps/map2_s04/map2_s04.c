#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s04.h"

INCLUDE_RODATA("asm/maps/map2_s04/nonmatchings/map2_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map2_s04/nonmatchings/map2_s04", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map2_s04/nonmatchings/map2_s04", func_800CABCC);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CAD34

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CAEB4

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CAF6C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CB0D0

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CB0F0

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CB968

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CBD54

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CC048

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CC474

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CC4B0

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CC4BC

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CC61C

s32 func_800CC7F4()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CC7FC

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CC8AC

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CC8C4

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CC8EC

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CC904

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CC92C

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CC9D0

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CC9E0

void func_800CC9EC(void) {}

void func_800CC9F4(void) {}

void func_800CC9FC(void) {}

void func_800CCA04(void) {}

void func_800CCA0C(void) {}

s32 func_800CCA14()
{
    return 0;
}

void func_800CCA1C(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CCA24

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CCA34

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CCA74

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CCA88

INCLUDE_ASM("asm/maps/map2_s04/nonmatchings/map2_s04", func_800CCA98);

INCLUDE_ASM("asm/maps/map2_s04/nonmatchings/map2_s04", func_800CCB30);

INCLUDE_ASM("asm/maps/map2_s04/nonmatchings/map2_s04", func_800CCB64);

#include "maps/shared/sharedFunc_800CE934_0_s02.h" // 0x800CCBE0

void func_800CCE6C(void) {}

INCLUDE_ASM("asm/maps/map2_s04/nonmatchings/map2_s04", func_800CCE74);

INCLUDE_ASM("asm/maps/map2_s04/nonmatchings/map2_s04", func_800CCF08);

const char* MAP_MESSAGES[] =
{
    #include "maps/shared/mapMsg_common.h"
    "\tThere's_a_memo_on_the_desk. ",
    "~C3\tCoroner_Seals_called. ",
    "~C3\tOfficer_Gucci_is_unlikely_to ~N\n\t\tbe_murdered._He_apparently ~N\n\t\tdied_naturally. ",
    "~C3\tBut,_medical_records_show ~N\n\t\tOfficer_Gucci_had_no_prior ~N\n\t\tsymptoms_of_heart_disease. ~E ",
    "\tThere's_something_on_it. ",
    "~C3\tProduct_only_available_in ~N\n\t\tselected_areas_of_Silent_Hill. ",
    "~C3\tRaw_material_is_White_Claudia, ~N\n\t\ta_plant_peculiar_to_the_region. ",
    "~C3\tManufactured_here? ~N\n\t\tDealer_*_manufacturer? ~E ",
    "~H\tThere_is_a_ ~C5 Shopping_district_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_helpful. ~E ",
    "\tThe_desk_is_messy. ~E ",
    "\tThere_is_a_ ~C2 Shotgun ~C7 . ~N\n\tTake_it? ~S4 "
};

void func_800CCF9C(void) // 0x800CCF9C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 24:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M2S04_ShotgunShells0;
            break;

        case 25:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S04_HandgunBullets0;
            break;

        case 26:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S04_HandgunBullets1;
            break;

        case 27:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M2S04_ShotgunShells1;
            break;

        case 28:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S04_HandgunBullets2;
            break;

        case 29:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S04_HandgunBullets3;
            break;

        case 30:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M2S04_RifleShells;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800CD050(void) // 0x800CD050
{
    g_BackgroundColor = 0x50;
    func_80087360(FILE_TIM_PLCSMEMO_TIM, Q12(0.0f), Q12(0.0f), 15);
}

void func_800CD088(void) // 0x800CD088
{
    func_80087360(FILE_TIM_PLCSBORD_TIM, Q12(0.0f), Q12(0.0f), 19);
    Savegame_EventFlagSet(EventFlag_145);
}

void func_800CD0D0(void) // 0x800CD0D0
{
    Event_MapTake(2, EventFlag_M2S00_PickupMap, 23);
}

void func_800CD0F8(void) // 0x800CD0F8
{
    Event_ItemTake(InventoryItemId_Shotgun, SHOTGUN_AMMO_PICKUP_ITEM_COUNT, EventFlag_M2S04_PickupShotgun, 26);
}

INCLUDE_ASM("asm/maps/map2_s04/nonmatchings/map2_s04", func_800CD124);

INCLUDE_ASM("asm/maps/map2_s04/nonmatchings/map2_s04", func_800CD2AC);

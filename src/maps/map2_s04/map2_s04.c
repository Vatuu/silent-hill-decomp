#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s04.h"

INCLUDE_RODATA("asm/maps/map2_s04/nonmatchings/map2_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map2_s04/nonmatchings/map2_s04", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CABCC

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

s32 func_800CC7F4() // 0x800CC7F4
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

s32 func_800CCA14() // 0x800CCA14
{
    return 0;
}

void func_800CCA1C(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CCA24

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CCA34

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CCA74

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CCA88

#include "maps/shared/Map_RoomIdxGet.h"

void func_800CCB30(s32 arg0) // 0x800CCB30
{
    (arg0 != 0) ? sharedFunc_800CE8B8_0_s02() : sharedFunc_800CE934_0_s02();
}

#include "maps/shared/sharedFunc_800CE8B8_0_s02.h"

#include "maps/shared/sharedFunc_800CE934_0_s02.h" // 0x800CCBE0

void func_800CCE6C(void) {}

void func_800CCE74(void) // 0x800CCE74
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Map_MessageWithSfx(11, Sfx_Unk1334, &sfxPos);
}

void func_800CCF08(void) // 0x800CCF08
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Map_MessageWithSfx(12, Sfx_Unk1344, &sfxPos);
}

const char* MAP_MESSAGES[] = {
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
    g_BackgroundColor = 80;
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
    Event_ItemTake(InventoryItemId_Shotgun, SHOTGUN_AMMO_PICKUP_ITEM_COUNT, EventFlag_M1S02_PickupShotgun, 26);
}

extern u8 D_800CF280;
extern s_WorldObject_0 g_CommonWorldObjects[8];
extern s_WorldObjectDesc g_WorldObject_Map;
extern s_WorldObjectDesc g_WorldObject_SavePad0;
extern s_WorldObjectDesc g_WorldObject_SavePad1;
extern s_WorldObjectDesc g_WorldObject_Shotgun;
extern s_WorldObjectPose g_CommonWorldObjectPoses[7];

void Map_WorldObjectsInit(void)
{
    D_800CF280 = 0;

    WorldObjectPositionInit(&g_WorldObject_SavePad0.pose_1C, -60.9976f, -0.8289f, 20.1067f, 0.0f, -100.7f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject_SavePad0.object_0, D_800A99E4.savePadName_4);

    WorldObjectPositionInit(&g_WorldObject_Map.pose_1C, -20.0f, 0.0f, 20.45f, 0, 180.0f, 0);
    WorldObject_ModelNameSet(&g_WorldObject_Map.object_0, "MAP_HIDE");

    WorldObjectPositionInit(&g_WorldObject_SavePad1.pose_1C, -102.8699f, -1.25f, 57.15f, 0, -117.55f, 0);
    WorldObject_ModelNameSet(&g_WorldObject_SavePad1.object_0, D_800A99E4.savePadName_4);

    WorldObjectPositionInit(&g_WorldObject_Shotgun.pose_1C, -59.484f, -0.8443f, 18.1517f, 0, -23.3f, 0);
    WorldObject_ModelNameSet(&g_WorldObject_Shotgun.object_0, "SHOTGUN_");

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void)
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObject_SavePad0.object_0, &g_WorldObject_SavePad0.pose_1C.position_0, &g_WorldObject_SavePad0.pose_1C.rotation_C);
        if (!Savegame_EventFlagGet(EventFlag_M1S02_PickupShotgun))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Shotgun.object_0, &g_WorldObject_Shotgun.pose_1C.position_0, &g_WorldObject_Shotgun.pose_1C.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupMap))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Map.object_0, &g_WorldObject_Map.pose_1C.position_0, &g_WorldObject_Map.pose_1C.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!D_800CF280)
        {
            func_8003ED74(7, 4);
            D_800CF280++;
        }

        g_WorldGfx_ObjectAdd(&g_WorldObject_SavePad1.object_0, &g_WorldObject_SavePad1.pose_1C.position_0, &g_WorldObject_SavePad1.pose_1C.rotation_C);
    }
    else
    {
        D_800CF280 = 0;
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_ShotgunShells0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_HandgunBullets0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_HandgunBullets1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_ShotgunShells1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_HandgunBullets2))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_HandgunBullets3))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[5].position_0, &g_CommonWorldObjectPoses[5].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_RifleShells))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[6].position_0, &g_CommonWorldObjectPoses[6].rotation_C);
        }
    }
}

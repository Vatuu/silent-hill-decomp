#include "bodyprog/bodyprog.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/map2/map2_s04.h"
#include "maps/particle.h"
#include "maps/characters/player.h"

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CCA88

#include "maps/shared/Map_RoomIdxGet.h"

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800CCB30

#include "maps/shared/Map_RoomBgmInit_0_s02_CondTrue.h" // 0x800CCB64

#include "maps/shared/Map_RoomBgmInit_0_s02_CondFalse.h" // 0x800CCBE0

void GameBoot_LoadScreen_StageString(void) {} // 0x800CCE6C

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800CCE74

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800CCF08

const char* MAP_MESSAGES[] = {
    #include "maps/shared/map_msg_common.h"
    /* 15 */ "\tThere's_a_memo_on_the_desk. ",
    /* 16 */ "~C3\tCoroner_Seals_called. ",
    /* 17 */ "~C3\tOfficer_Gucci_is_unlikely_to ~N\n\t\tbe_murdered._He_apparently ~N\n\t\tdied_naturally. ",
    /* 18 */ "~C3\tBut,_medical_records_show ~N\n\t\tOfficer_Gucci_had_no_prior ~N\n\t\tsymptoms_of_heart_disease. ~E ",
    /* 19 */ "\tThere's_something_on_it. ",
    /* 20 */ "~C3\tProduct_only_available_in ~N\n\t\tselected_areas_of_Silent_Hill. ",
    /* 21 */ "~C3\tRaw_material_is_White_Claudia, ~N\n\t\ta_plant_peculiar_to_the_region. ",
    /* 22 */ "~C3\tManufactured_here? ~N\n\t\tDealer_*_manufacturer? ~E ",
    /* 23 */ "~H\tThere_is_a_ ~C5 Shopping_district_map ~C7 . ~N\n\tTake_it? ~S4 ",
    /* 24 */ "\tNothing_helpful. ~E ",
    /* 25 */ "\tThe_desk_is_messy. ~E ",
    /* 26 */ "\tThere_is_a_ ~C2 Shotgun ~C7 . ~N\n\tTake_it? ~S4 "
};

void func_800CCF9C(void) // 0x800CCF9C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx)
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
    g_Screen_BackgroundImgGamma = Q8(10.0f / 32.0f);
    MapMsg_DisplayWithTexture(FILE_TIM_PLCSMEMO_TIM, Q12(0.0f), Q12(0.0f), 15);
}

void func_800CD088(void) // 0x800CD088
{
    MapMsg_DisplayWithTexture(FILE_TIM_PLCSBORD_TIM, Q12(0.0f), Q12(0.0f), 19);
    Savegame_EventFlagSet(EventFlag_145);
}

void MapEvent_MapTake(void) // 0x800CD0D0
{
    Event_MapTake(2, EventFlag_M2S00_PickupMap, 23);
}

void MapEvent_ShotgunTake(void) // 0x800CD0F8
{
    Event_ItemTake(InvItemId_Shotgun, SHOTGUN_AMMO_PICKUP_ITEM_COUNT, EventFlag_M1S02_PickupShotgun, 26);
}

extern u8 D_800CF280;
extern s_WorldObjectModel g_CommonWorldObjects[8];
extern s_WorldObjectPose g_WorldObject_Map;
extern s_WorldObjectPose g_WorldObject_SavePad0;
extern s_WorldObjectPose g_WorldObject_SavePad1;
extern s_WorldObjectPose g_WorldObject_Shotgun;
extern s_Pose g_CommonWorldObjectPoses[7];

void Map_WorldObjectsInit(void)
{
    D_800CF280 = 0;

    WorldObject_Init(&g_WorldObject_SavePad0, D_800A99E4[1], -60.9976f, -0.8289f, 20.1067f, 0.0f, -100.7f, 0.0f);

    WorldObject_Init(&g_WorldObject_Map, "MAP_HIDE", -20.0f, 0.0f, 20.45f, 0, 180.0f, 0);

    WorldObject_Init(&g_WorldObject_SavePad1, D_800A99E4[1], -102.8699f, -1.25f, 57.15f, 0, -117.55f, 0);

    WorldObject_Init(&g_WorldObject_Shotgun, "SHOTGUN_", -59.484f, -0.8443f, 18.1517f, 0, -23.3f, 0);

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4[2]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4[3]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4[4]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4[5]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4[6]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4[7]);
}

void Map_WorldObjectsUpdate(void)
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        WorldGfx_ObjectAdd(&g_WorldObject_SavePad0.object, &g_WorldObject_SavePad0.position, &g_WorldObject_SavePad0.rotation);

        if (!Savegame_EventFlagGet(EventFlag_M1S02_PickupShotgun))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Shotgun.object, &g_WorldObject_Shotgun.position, &g_WorldObject_Shotgun.rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupMap))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Map.object, &g_WorldObject_Map.position, &g_WorldObject_Map.rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!D_800CF280)
        {
            Gfx_MapInitMapEffectsUpdate(7, 4);
            D_800CF280++;
        }

        WorldGfx_ObjectAdd(&g_WorldObject_SavePad1.object, &g_WorldObject_SavePad1.position, &g_WorldObject_SavePad1.rotation);
    }
    else
    {
        D_800CF280 = 0;
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_ShotgunShells0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[0].position, &g_CommonWorldObjectPoses[0].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_HandgunBullets0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position, &g_CommonWorldObjectPoses[1].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_HandgunBullets1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2].position, &g_CommonWorldObjectPoses[2].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_ShotgunShells1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[3].position, &g_CommonWorldObjectPoses[3].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_HandgunBullets2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[4].position, &g_CommonWorldObjectPoses[4].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_HandgunBullets3))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[5].position, &g_CommonWorldObjectPoses[5].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S04_RifleShells))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[6].position, &g_CommonWorldObjectPoses[6].rotation);
        }
    }
}

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/map2/map2_s02.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/groaner.h"
#include "maps/characters/player.h"
#include "maps/characters/romper.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("maps/map2_s02/nonmatchings/map2_s02", D_800CA7F0);

INCLUDE_RODATA("maps/map2_s02/nonmatchings/map2_s02", D_800CA7F4);

INCLUDE_RODATA("maps/map2_s02/nonmatchings/map2_s02", D_800CA800);

INCLUDE_RODATA("maps/map2_s02/nonmatchings/map2_s02", D_800CA818);

INCLUDE_RODATA("maps/map2_s02/nonmatchings/map2_s02", D_800CA830);

INCLUDE_RODATA("maps/map2_s02/nonmatchings/map2_s02", D_800CA848);

INCLUDE_RODATA("maps/map2_s02/nonmatchings/map2_s02", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
#include "../src/maps/characters/air_screamer.c" // 0x800D0728

// TODO: Move this line into separate `Chara_Groaner` split.
#include "../src/maps/characters/groaner.c" // 0x800E1760

// TODO: Move this line into separate `Chara_Romper` split.
#include "../src/maps/characters/romper.c" // 0x800E5D38

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E992C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800E993C

#include "maps/shared/Map_RoomBgmInit_2_s02.h" // 0x800E9B38

void func_800E9C24(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800E9C2C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800E9CC0

void func_800E9D54(void) // 0x800E9D54
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_AntiqueShopKey, 1);
    Map_MessageWithSfx(15, Sfx_UseKey, &sfxPos);
    Savegame_EventFlagSet(EventFlag_M2S02_AntiqueShopOpen);
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tUsed_the_ ~C2 Antique_shop_key ~C7 . ~E ",
    "~C3\tAlchemilla_Hospital ~E ",
    "~C3\tgreen_lion ~E "
};

void func_800E9E10(void) // 0x800E9E10
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 41:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S02_HealthDrink0;
            break;

        case 42:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S02_HealthDrink1;
            break;

        case 43:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S02_HandgunBullets0;
            break;

        case 44:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S02_HandgunBullets1;
            break;

        case 45:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S02_HealthDrink2;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800E9EAC(void) // 0x800E9EAC
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            g_Screen_FadeStatus = 12; // TODO: Can't be created with `ScreenFade_Start` macro?
            Sd_SfxStop(Sfx_Unk1522);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(0, false, 1, Q12(0.25f), false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_191);
            Game_TurnFlashlightOff();
            func_8003A16C();
            break;
    }
}

void func_800E9FDC(void) // 0xfunc_800E9FDC
{
    g_DeltaTime = Q12(0.0f);

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);

        case 1:
            if (Sd_AmbientSfxInit())
            {
                break;
            }

            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_189);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void Map_WorldObjectsInit(void) // 0x800EA0E0
{
    if (Savegame_MapMarkingGet(MapMarkFlag_FogCentralTown_AntiqueWholeSign))
    {
        Savegame_MapMarkingSet(MapMarkFlag_AltCentralTown_AntiqueWholeSign);
    }

    D_800F0B2C = Q12(0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 2;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcId_2280 = 3;
    }
    else
    {
        g_SysWork.npcId_2280 = 4;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800EA1C4
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    func_80069844(0xFFFF);

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (Savegame_EventFlagGet(EventFlag_346))
        {
            func_8006982C(4);
            func_80069844(2);

            if (g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-68.0f))
            {
                Savegame_EventFlagClear(EventFlag_346);
            }
        }
        else
        {
            func_80069844(4);
            func_8006982C(2);
        }
    }

    if (Savegame_EventFlagGet(EventFlag_191) && !Savegame_EventFlagGet(EventFlag_194))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
        {
                if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-116.0f))
                {
                    if (g_SysWork.playerWork_4C.player_0.position_18.vy > Q12(0.0f))
                    {
                        if (g_ScreenFadeTimestep > Q12(0.0f))
                        {
                            g_ScreenFadeTimestep = MIN(g_ScreenFadeTimestep + g_DeltaTime, Q12(3.0f));
                        }
                    }
                }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -6, -1, -6) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
            Game_TurnFlashlightOff();
    }

    if (!Savegame_EventFlagGet(EventFlag_192))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
        {
            if (D_800F0B2C == Q12(0.0f))
            {
                if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(96.0f),
                                        g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(89.0f)) < Q12(4.0f))
                {
                    func_8005DC1C(Sfx_Unk1492, &D_800ED938, Q8_CLAMPED(0.766f), 2);
                    D_800F0B2C = Q12(0.3f);
                }
            }
        }

        if (D_800F0B2C > Q12(0.0f))
        {
            D_800F0B2C -= g_DeltaTime;
            if (D_800F0B2C < Q12(0.0f))
            {
                Savegame_EventFlagSet(EventFlag_192);
                func_8005DC1C(Sfx_Unk1492, &D_800ED938, Q8_CLAMPED(0.766f), 2);
            }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HandgunBullets0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HandgunBullets1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HealthDrink2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }
}

void func_800EAA50(void) // 0x800EAA50
{
    if (Savegame_EventFlagGet(EventFlag_191))
    {
        if (!Savegame_EventFlagGet(EventFlag_194))
        {
            Savegame_EventFlagSet(EventFlag_194);
            Sd_AmbientSfxInit();
        }
    }
}

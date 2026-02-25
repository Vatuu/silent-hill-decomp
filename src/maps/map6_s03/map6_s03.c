#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map6/map6_s03.h"
#include "maps/particle.h"
#include "maps/characters/hanged_scratcher.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Stalker` split.
#include "../src/maps/characters/stalker.c" // 0x800CEFCC

// TODO: Move this line into separate `Chara_HangedScratcher` split.
#include "../src/maps/characters/hanged_scratcher.c" // 0x800D4264

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D7F14

u8 Map_RoomIdxGet(s32 x, s32 z) // 0x800D7F24
{
    s32 ret;

    if (x < Q12(27.0f))
    {
        ret = 17;
        if (x <= Q12(13.0f))
        {
            ret = 15;
            if (x > Q12(-13.0f))
            {
                ret = 16;
            }
        }
    }
    else if (x < Q12(56.0f))
    {
        ret = 18;
    }
    else
    {
        if (x < Q12(72.0f))
        {
            ret = 19;
        }
        else
        {
            ret = 20;
        }
    }

    return ret;
}

void func_800D7F98(void) // 0x800D7F98
{
    q19_12 dist0;
    q19_12 dist1;
    q19_12 dist2;
    s32    fArg1;
    s32    roomIdx;
    s32    flags;

    roomIdx = g_SavegamePtr->mapRoomIdx_A5;
    fArg1 = 0x400;

    if (Savegame_EventFlagGet(EventFlag_435))
    {
        flags = 1 << 0;
        if (Savegame_EventFlagGet(EventFlag_437))
        {
            fArg1 = 0x547;
        }
        else
        {
            flags = D_800DBCE4[roomIdx];

            switch (roomIdx)
            {
                case 15:
                case 16:
                    D_800DBCDC[5] = 0;
                    D_800DBCDC[6] = 0;
                    D_800DBCDC[7] = 0;
                    break;

                case 17:
                    // VECTOR3 D_800DBD10 = VECTOR3(23.0f, 0.0f, 20.0f); // in .data
                    dist0 = Math_Distance2dGet(&g_SysWork.playerWork_4C.player_0.position_18, &D_800DBD10);
                    if (dist0 < Q12(5.0f))
                    {
                        dist0 = Q8(0.313f);
                    }
                    else
                    {
                        dist0 = Q8(0.313f) - Q12_MULT_PRECISE((dist0 - Q12(5.0f)), 3);
                        if (dist0 < Q12(0.0f))
                        {
                            dist0 = Q12(0.0f);
                        }
                    }

                    D_800DBCDC[5] = dist0;
                    D_800DBCDC[6] = Q12(0.0f);
                    D_800DBCDC[7] = Q12(0.0f);
                    break;

                case 18:
                case 19:
                case 20:
                    D_800DBCDC[5] = Q8(0.313f);

                    dist1 = Q12(64.0f) - g_SysWork.playerWork_4C.player_0.position_18.vx;
                    if (dist1 < Q12(0.0f))
                    {
                        dist1 = Q8(0.313f);
                    }
                    else
                    {
                        dist1 = Q8(0.313f) - Q12_MULT_PRECISE(dist1, 3);
                        if (dist1 < Q12(0.0f))
                        {
                            dist1 = Q12(0.0f);
                        }
                    }

                    D_800DBCDC[6] = dist1;

                    dist2 = Q12(80.0f) - g_SysWork.playerWork_4C.player_0.position_18.vx;
                    if (dist2 < Q12(0.0f))
                    {
                        dist2 = Q8(0.313f);
                    }
                    else
                    {
                        dist2 = Q8(0.313f) - Q12_MULT_PRECISE(dist2, 5);
                        if (dist2 < Q12(0.0f))
                        {
                            dist2 = Q12(0.0f);
                        }
                    }

                    D_800DBCDC[7] = dist2;
                    break;
            }
        }
    }
    else
    {
        flags = (1 << 1) | (1 << 2);
        if (!Savegame_EventFlagGet(EventFlag_431))
        {
            fArg1 = 0x547;
            flags = 1 << 1;
        }
    }

    Bgm_Update(flags, fArg1, &D_800DBCDC);
}

void Gfx_LoadingScreen_StageString(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~H\tThere_is_a_ ~C5 Sewer_map ~N\n\t(connecting_to_amusement_park) ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tGotta'_go_find_Cybil! ~N\n\tNo_time_to_go_back. ~E "
};

void MapEvent_CommonItemTake(void) // 0x800D81AC
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 10:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S03_HealthDrink0;
            break;

        case 11:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M6S03_HandgunBullets;
            break;

        case 12:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S03_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D822C(void) // 0x800D822C
{
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] == 3)
        {
            SysWork_StateStepSet(0, 4);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-20.0486f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-4.07f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(24.7134f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.0f);

            // Turn on flashlight.
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-19.66f), Q12(0.17f), Q12(26.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-20.49f), Q12(-3.23f), Q12(24.37f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 88, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 3:
            g_SysWork.playerWork_4C.player_0.position_18.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.4f);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 4:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.4f);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_431);
            func_8003A16C();
            break;
    }
}

void func_800D84EC(void) // 0x800D84EC
{
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] == 4)
        {
            SysWork_StateStepSet(0, 5);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_437);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(89.9092f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-0.0733f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(18.8875f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);
            Game_TurnFlashlightOn();
            Camera_PositionSet(NULL, Q12(88.92f), Q12(-1.64f), Q12(20.16f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(90.98f), Q12(-4.45f), Q12(18.2f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            func_80085EB8(0U, &g_SysWork.playerWork_4C.player_0, 87, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.415f, 12);
            SysWork_StateStepIncrementDelayed(Q12(5.0f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.41f, 12);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_433);
            break;
    }
}

void MapEvent_MapTake(void) // 0x800D87F0
{
    Event_MapTake(15, EventFlag_M6S03_PickupMap, 15);
}

void Map_WorldObjectsInit(void) // 0x800D8818
{
    D_800DFEF5 = 0;
    D_800DFEF4 = 0;
    D_800DFEF2 = 0;
    D_800DFEF0 = 0;

    WorldObject_ModelNameSet(&g_WorldObject0[0], "YUKABFO1");
    WorldObject_ModelNameSet(&g_WorldObject0[1], "YUKAAFT1");
    Math_Vector3Set(&g_WorldObjectPos0, Q12(-20.0f), Q12(0.0f), Q12(34.0f));

    WorldObjectInit(&g_WorldObject1, "SITAI_NE", 75.0f, 0.5f, 19.7f, 0.0f, 180.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject2, "MP_DRNBK", -22.0f, 0.0f, 26.4f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 3;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

static const SVECTOR3 D_800CB258 = { 0, 0, 0 };
static const VECTOR3  D_800CB260 = { Q12(-41.6f), Q12(0.0f), Q12(20.0f) };

void Map_WorldObjectsUpdate(void) // 0x800D89A0
{
    s32  temp_s0_2;
    s32  var_v0_2;
    s32  temp_s0;
    s32  flags;
    s32  temp_a0;
    s32  i;
    s16* ptr;

    MAP_CHUNK_CHECK_VARIABLE_DECL();
    MAP_CHUNK_CHECK_VARIABLE_DECL_2();

    if (!Savegame_EventFlagGet(EventFlag_429) && Savegame_EventFlagGet(EventFlag_432))
    {
        Savegame_EventFlagSet(EventFlag_429);
        func_8003A16C();
    }

    func_80069844(0xFFFF);

    if (PLAYER_IN_MAP_CHUNK_2(vx, 1, 0, -1, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_430) && Savegame_EventFlagGet(EventFlag_435))
        {
            func_8005DC1C(Sfx_Unk1614, &g_WorldObjectPos0, Q8(0.5f), 0);
            Savegame_EventFlagSet(EventFlag_430);

            for (i = 0; i < 6; i++)
            {
                if (g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_None &&
                    g_SysWork.npcs_1A0[i].position_18.vz < Q12(36.5f))
                {
                    g_SysWork.npcs_1A0[i].model_0.charaId_0 = Chara_None;
                    Savegame_EnemyStateUpdate(&g_SysWork.npcs_1A0[i]);
                }
            }
        }

        temp_s0 = (g_SavegamePtr->eventFlags_168[13] >> 19) & 0x1;
        WorldGfx_ObjectAdd(&g_WorldObject0[temp_s0], &g_WorldObjectPos0, &D_800CB258);
        if (temp_s0 != 0)
        {
            flags = (1 << 2) | (1 << 3);
        }
        else
        {
            flags = 1 << 1;
        }

        func_8006982C(flags);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        temp_a0 = (Rng_Rand16() & 0x1F) + 0x20;
        if (D_800DFEF4 > 0 && D_800DFEF0 > 0 && temp_a0 < D_800DFEF0)
        {
            D_800DFEF4 = -(Rng_Rand16() & 0x1) - 1;
        }
        else if (D_800DFEF4 < 0 && D_800DFEF0 < 0 && temp_a0 < -D_800DFEF0)
        {
            D_800DFEF4 = (Rng_Rand16() & 0x1) + 1;
        }
        else if (!D_800DFEF4 || !(Rng_Rand16() & 0x1F))
        {
            D_800DFEF4 = (Rng_Rand16() % 5) - 2;
        }

        ptr       = &D_800DFEF0;
        temp_s0_2 = D_800DFEF0;
        if ((Rng_Rand16() & 0xFF) < ((ABS(D_800DFEF4) << 6) + 0x40))
        {
            if (D_800DFEF4 <= 0)
            {
                var_v0_2 = temp_s0_2 - 1;
            }
            else
            {
                var_v0_2 = temp_s0_2 + 1;
            }
        }
        else
        {
            var_v0_2 = temp_s0_2;
        }
        *ptr = var_v0_2;

        g_WorldObject1.rotation_28.vy = D_800DFEF0 + 0x800;
        temp_a0                       = (Rng_Rand16() & 0x1F) + 0x10;
        if (D_800DFEF5 > 0 && temp_a0 < (D_800DFEF2 + ABS(D_800DFEF0 >> 1)))
        {
            D_800DFEF5 = -(Rng_Rand16() & 0x1) - 1;
        }
        else if (D_800DFEF5 == 0 || !(Rng_Rand16() & 0x3F))
        {
            D_800DFEF5 = (Rng_Rand16() % 5) - 2;
        }

        ptr       = &D_800DFEF2;
        temp_s0_2 = D_800DFEF2;
        temp_a0   = Rng_Rand16() & 0xFF;

        if (temp_a0 < ((ABS(D_800DFEF5) << 6) + 0x60))
        {
            if (D_800DFEF5 <= 0)
            {
                var_v0_2 = temp_s0_2 - 1;
            }
            else
            {
                var_v0_2 = temp_s0_2 + 1;
            }
        }
        else
        {
            var_v0_2 = temp_s0_2;
        }
        *ptr = var_v0_2;

        D_800DFEF2                    = MAX(0, D_800DFEF2);
        g_WorldObject1.position_1C.vz = D_800DFEF2 + Q12(19.7f);
        WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M6S03_PickupMap))
        {
            WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &D_800CB258);
        }
    }

    if (!Savegame_EventFlagGet(EventFlag_439) && g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(48.0f))
    {
        if (!Vw_AabbVisibleInScreenCheck(40, 44, -2, 0, 18, 22))
        {
            Savegame_EventFlagSet(EventFlag_439);

            for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
            {
                if (g_SysWork.npcs_1A0[i].position_18.vx < Q12(32.0f) &&
                    g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_None)
                {
                    func_80088F94(&g_SysWork.npcs_1A0[i], 0, 0);
                }
            }

            Chara_Spawn(Chara_HangedScratcher, 9, Q12(42.2f), Q12(20.9), Q12_ANGLE(90.0f), 6u);
            func_80088FF4(Chara_HangedScratcher, 9, 6);
            Chara_Spawn(Chara_HangedScratcher, 10, Q12(41.1f), Q12(19.0f), Q12_ANGLE(90.0f), 6u);
            func_80088FF4(Chara_HangedScratcher, 10, 6);
            func_8005DC1C(Sfx_Unk1585, &D_800CB260, Q8_CLAMPED(1.0f), 2);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M6S03_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M6S03_HandgunBullets))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M6S03_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }
}

void func_800D936C(void) {}

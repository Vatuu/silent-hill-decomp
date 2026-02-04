#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "bodyprog/credits.h"
#include "bodyprog/demo.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

u8 g_SysState_GameOver_TipIdx;

s8 pad_bss_800BCD81[3];

s32 g_DeltaTimeCpy;

s32 pad_bss_800BCD88[2];

s_EventParam* g_ItemTriggerEvents[];

s32 pad_bss_800BCD94[5];

s_800BCDA8 D_800BCDA8[2];

s_MapPoint2d D_800BCDB0;

s32 pad_bss_800BCDD0;

s32 g_ItemTriggerItemIds[5];

u8 D_800BCDD4;

s8 pad_bss_800BCDD5[3];

s_EventParam* g_MapEventParam;

// ========================================
// RADIO SFX
// ========================================

void func_80037154(void) // 0x80037154
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800BCDA8[i].field_2 = NO_VALUE;
        D_800BCDA8[i].field_1 = NO_VALUE;
        D_800BCDA8[i].field_3 = 0;
    }
}

void Game_RadioSoundStop(void) // 0x80037188
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800BCDA8[i].field_0 = NO_VALUE;
    }

    for (i = 0; i < 2; i++)
    {
        Sd_SfxStop(Sfx_RadioInterferenceLoop + i);
    }
}

// ========================================
// COLLISIONS RELATED?
// ========================================

void Chara_PositionSet(s_MapPoint2d* mapPoint) // 0x800371E8
{
    s32 rotY;

    rotY = FP_ANGLE_FROM_PACKED(mapPoint->data.areaLoad.rotationY_4_16);
    Math_SVectorSet(&g_SysWork.playerWork_4C.player_0.rotation_24, FP_ANGLE(0.0f), rotY, FP_ANGLE(0.0f));

    g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.position_18.vx = mapPoint->positionX_0;
    g_SysWork.playerWork_4C.player_0.position_18.vz = mapPoint->positionZ_8;

    if (mapPoint->data.areaLoad.field_4_24 >= 2)
    {
        g_SysWork.playerWork_4C.player_0.position_18.vx += Q12_MULT_FLOAT_PRECISE(Math_Sin(rotY), 0.4f);
        g_SysWork.playerWork_4C.player_0.position_18.vz += Q12_MULT_FLOAT_PRECISE(Math_Cos(rotY), 0.4f);
    }

    g_SysWork.loadingScreenIdx_2281 = mapPoint->data.areaLoad.loadingScreenId_4_9;

    if (mapPoint->data.areaLoad.mapIdx_4_0 == 24) // TODO: Demagic 24.
    {
        g_SavegamePtr->paperMapIdx_A9 = PaperMapIdx_OtherPlaces;
    }
    else if (mapPoint->data.areaLoad.mapIdx_4_0 != PaperMapIdx_OtherPlaces)
    {
        g_SavegamePtr->paperMapIdx_A9 = mapPoint->data.areaLoad.mapIdx_4_0;
    }

    g_SysWork.cameraAngleY_237A = rotY;

    func_8007E9C4();
    Savegame_MapRoomIdxUpdate();
}

void Game_PlayerHeightUpdate(void) // 0x80037334
{
    s_Collision coll;

    if (g_MapOverlayHeader.worldObjectsUpdate_40 != NULL)
    {
        g_MapOverlayHeader.worldObjectsUpdate_40();
    }

    Collision_Get(&coll, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
    g_SysWork.playerWork_4C.player_0.position_18.vy = coll.groundHeight_0;
}

void Event_Update(bool disableButtonEvents) // 0x800373CC
{
    s_MapPoint2d* mapPoint;
    s_EventParam* mapEvent;
    q19_12        pointPosX;
    q19_12        pointPosZ;
    q19_12        pointRadiusX;
    q19_12        pointRadiusZ;
    s32           i;

    void Event_ItemTriggersClear() // 0x80037388
    {
        s32 i;

        for (i = 0; i < 5; i++)
        {
            g_ItemTriggerItemIds[i] = NO_VALUE;
            g_ItemTriggerEvents[i]  = NULL;
        }
    }

    // `lastUsedItem_28` is set by `Inventory_ItemUse` when player uses an item that matches one of the item trigger events.
    // If it's set, find its index in `g_ItemTriggerItemIds` and use that to get the corresponding `s_EventParam` from `g_ItemTriggerEvents`.
    // After processing, the field is cleared and item trigger IDs are reset.
    // (Multi-item events likely repopulate the trigger IDs below based on whichever events are still active?)
    if (g_SysWork.playerWork_4C.extra_128.lastUsedItem_28 != InventoryItemId_Unequipped)
    {
        for (i = 0; g_SysWork.playerWork_4C.extra_128.lastUsedItem_28 != g_ItemTriggerItemIds[i]; i++);

        g_MapEventParam        = g_ItemTriggerEvents[i];
        g_MapEventLastUsedItem = g_SysWork.playerWork_4C.extra_128.lastUsedItem_28;
        g_MapEventSysState     = g_MapEventParam->sysState_8_0;
        g_MapEventIdx          = g_MapEventParam->pointOfInterestIdx_8_5;

        g_SysWork.playerWork_4C.extra_128.lastUsedItem_28 = InventoryItemId_Unequipped;
        Event_ItemTriggersClear();
        return;
    }

    Event_ItemTriggersClear();

    g_MapEventLastUsedItem = InventoryItemId_Unequipped;

    mapEvent = &g_MapOverlayHeader.mapEvents_24[-1];

    while (true)
    {
        s32 disabledEventFlag_temp;
        s16 disabledEventFlag;
        s16 requiredEventFlag;

        mapEvent++;

        if (mapEvent->triggerType_4_0 == NO_VALUE)
        {
            break;
        }

        // `requiredEventFlag`: if set, EventFlag that must be set for event to trigger?
        // `disabledEventFlag`: if set, EventFlag that must not be set for event to trigger?
        // TODO: Can this s32 temp be removed? Trying to set `disabledEventFlag` directly results in `lhu` instead?
        requiredEventFlag      = mapEvent->requiredEventFlag_0;
        disabledEventFlag_temp = mapEvent->disabledEventFlag_2;
        disabledEventFlag      = disabledEventFlag_temp;

        if (requiredEventFlag != 0 && !Savegame_EventFlagGet(requiredEventFlag))
        {
            continue;
        }

        if (disabledEventFlag != 0 && Savegame_EventFlagGet(disabledEventFlag) &&
            (disabledEventFlag < 867 || mapEvent->activationType_4_4 == TriggerActivationType_Exclusive || mapEvent->sysState_8_0 == SysState_EventSetFlag))
        {
            continue;
        }

        // `TriggerType_None` skips any trigger/activation check and always executes.
        // Maybe used for map-load events, and events that should run every frame?
        // Returns before processing other events until flag checks above disable it.
        if (mapEvent->triggerType_4_0 == TriggerType_None)
        {
            g_MapEventParam    = mapEvent;
            g_MapEventSysState = mapEvent->sysState_8_0;
            g_MapEventIdx      = mapEvent->pointOfInterestIdx_8_5;
            return;
        }

        // `TriggerActivationType_Button`: Only continue processing event when action button is pressed and `Player_IsBusy` returns false.
        if (mapEvent->activationType_4_4 == TriggerActivationType_Button &&
            (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.action_6) || disableButtonEvents || Player_IsBusy()))
        {
            continue;
        }

        // TODO: This uses `field_5` as the map point index, but there is also a separate `pointOfInterestIdx_8_5` field.
        mapPoint = &g_MapOverlayHeader.mapPointsOfInterest_1C[mapEvent->field_5];

        switch (mapEvent->triggerType_4_0)
        {
            case TriggerType_TouchAabb:
                pointPosX    = mapPoint->positionX_0;
                pointPosZ    = mapPoint->positionZ_8;
                pointRadiusX = mapPoint->data.touchAabb.radiusX_4_16 * Q12(0.25f);
                pointRadiusZ = mapPoint->data.touchAabb.radiusZ_4_24 * Q12(0.25f);

                if (ABS(g_SysWork.playerWork_4C.player_0.position_18.vx - pointPosX) > pointRadiusX)
                {
                    continue;
                }

                if (ABS(g_SysWork.playerWork_4C.player_0.position_18.vz - pointPosZ) > pointRadiusZ)
                {
                    continue;
                }
                break;

            case TriggerType_TouchFacing:
                if (!Event_CollideFacingCheck(mapPoint))
                {
                    continue;
                }
                break;

            case TriggerType_TouchObbFacing:
                if (!Event_CollideObbFacingCheck(mapPoint))
                {
                    continue;
                }
                break;

            case TriggerType_TouchObb:
                if (!Event_CollideObbCheck(mapPoint))
                {
                    continue;
                }
                break;
        }

        // Trigger checks have passed. Check activation type.

        // `TriggerActivationType_Exclusive`: Skip processing any other events if this event is active.
        if (mapEvent->activationType_4_4 == TriggerActivationType_Exclusive && mapEvent == g_MapEventParam)
        {
            g_MapEventSysState = SysState_Invalid;
            return;
        }

        // `TriggerActivationType_Item`: When trigger check has passed (player is in the trigger area).
        // Required item ID for event is stored into `g_ItemTriggerItemIds` and event pointer at `g_ItemTriggerEvents`
        // Once player uses an item in the inventory screen, it compares the ID against the ones stored at `g_ItemTriggerItemIds`.
        // If used item ID matches one that event has requested, `extra_128.lastUsedItem_28` gets set to the item ID.
        // At the start of this function, if `extra_128.lastUsedItem_28` is set, it will locate the `s_EventParam` for it from `g_ItemTriggerEvents` and run the event.
        if (mapEvent->activationType_4_4 == TriggerActivationType_Item)
        {
            for (i = 0; g_ItemTriggerItemIds[i] != NO_VALUE; i++);

            g_ItemTriggerEvents[i]  = mapEvent;
            g_ItemTriggerItemIds[i] = mapEvent->requiredItemId_6;
            continue;
        }

        // `TriggerActivationType_Button`: Only allow button activated events when area is lit up?
        if (mapEvent->activationType_4_4 == TriggerActivationType_Button)
        {
            if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 2) && !g_SysWork.field_2388.isFlashlightOn_15 &&
                ((g_SysWork.field_2388.field_1C[0].effectsInfo_0.field_0.s_field_0.field_0 & 1) || (g_SysWork.field_2388.field_1C[1].effectsInfo_0.field_0.s_field_0.field_0 & 1)))
            {
                if (mapEvent->sysState_8_0 != SysState_LoadOverlay &&
                    (mapEvent->sysState_8_0 != SysState_LoadRoom && mapEvent->pointOfInterestIdx_8_5 > 1))
                {
                    continue;
                }
            }
        }

        // Trigger and activation checks passed. Run event.

        // If this is `EventSetFlag`, handle setting the flag here and skip running it.
        // (Same as `SysState_EventSetFlag_Update`.)
        if (mapEvent->sysState_8_0 == SysState_EventSetFlag)
        {
            Savegame_EventFlagSetAlt(mapEvent->disabledEventFlag_2);
            break;
        }

        // Set `g_MapEventSysState` to the SysState needed for the event to be ran on next tick (`SysState_ReadMessage`/`SaveMenu`/`EventCallFunc`/etc.).
        g_MapEventParam    = mapEvent;
        g_MapEventSysState = mapEvent->sysState_8_0;
        g_MapEventIdx      = mapEvent->pointOfInterestIdx_8_5;
        return;
    }

    g_MapEventParam    = NULL;
    g_MapEventSysState = SysState_Invalid;
    g_MapEventIdx      = 0;
}

bool Event_CollideFacingCheck(s_MapPoint2d* mapPoint) // 0x800378D4
{
    q19_12 deltaX;
    q19_12 deltaZ;
    q3_12  rotY;
    q19_12 deltaRotY;

    if (g_MainLoop_FrameCount > D_800A9A20)
    {
        rotY       = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
        D_800A9A24 = g_SysWork.playerWork_4C.player_0.position_18.vx - (Math_Sin(rotY) >> 3); // `/ 8`.
        D_800A9A28 = g_SysWork.playerWork_4C.player_0.position_18.vz - (Math_Cos(rotY) >> 3); // `/ 8`.
        D_800A9A20 = g_MainLoop_FrameCount;
    }

    deltaX = mapPoint->positionX_0 - D_800A9A24;
    if (ABS(deltaX) > Q12(0.8f))
    {
        return false;
    }

    deltaZ = mapPoint->positionZ_8 - D_800A9A28;
    if (ABS(deltaZ) > Q12(0.8f))
    {
        return false;
    }

    if ((SQUARE(deltaX) + SQUARE(deltaZ)) > SQUARE(Q12(0.8f)))
    {
        return false;
    }

    deltaRotY = g_SysWork.playerWork_4C.player_0.rotation_24.vy - ratan2(deltaX, deltaZ);
    if (deltaRotY >= FP_ANGLE(180.0f))
    {
        deltaRotY -= FP_ANGLE(360.0f);
    }

    if (FP_ANGLE(30.0f) < ABS(deltaRotY))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Event_CollideObbFacingCheck(s_MapPoint2d* mapPoint) // 0x80037A4C
{
    s32    temp_a0_2;
    s32    temp_a2;
    q19_12 halfCosPlayerRotY;
    s32    temp_s2;
    s32    halfSinRotY;
    s32    temp_s4;
    q19_12 deltaX;
    q19_12 deltaZ;
    s32    temp_v1;
    q19_12 clampedHalfCosPlayerRotY;
    bool   cond;
    s32    scaledSinPlayerRotY;
    s32    scaledCosRotY;

    halfSinRotY   = Math_Sin(g_SysWork.playerWork_4C.player_0.rotation_24.vy) >> 1; // `/ 2`.
    scaledCosRotY = -Math_Cos(FP_ANGLE_FROM_PACKED(mapPoint->data.areaLoad.rotationY_4_16)) * mapPoint->data.areaLoad.field_4_24;

    clampedHalfCosPlayerRotY = halfSinRotY;

    temp_a0_2 = scaledCosRotY >> 4; // `/ 16`.
    deltaX    = mapPoint->positionX_0 - g_SysWork.playerWork_4C.player_0.position_18.vx;
    temp_s2   = deltaX - temp_a0_2;
    temp_s4   = deltaX + temp_a0_2;

    clampedHalfCosPlayerRotY = MAX(halfSinRotY, 0);

    if (temp_s4 >= temp_s2)
    {
        cond = clampedHalfCosPlayerRotY < temp_s2;
    }
    else
    {
        cond = clampedHalfCosPlayerRotY < temp_s4;
    }

    if (!cond)
    {
        if (MIN(halfSinRotY, 0) <= MAX(temp_s2, temp_s4))
        {
            halfCosPlayerRotY   = Math_Cos(g_SysWork.playerWork_4C.player_0.rotation_24.vy) >> 1; // `/ 2`.
            scaledSinPlayerRotY = Math_Sin(FP_ANGLE_FROM_PACKED(mapPoint->data.areaLoad.rotationY_4_16)) * mapPoint->data.areaLoad.field_4_24;

            clampedHalfCosPlayerRotY = halfCosPlayerRotY;

            temp_a0_2 = scaledSinPlayerRotY >> 4; // `/ 16`.
            deltaZ    = mapPoint->positionZ_8 - g_SysWork.playerWork_4C.player_0.position_18.vz;
            temp_v1   = deltaZ - temp_a0_2;
            temp_a2   = deltaZ + temp_a0_2;

            clampedHalfCosPlayerRotY = MAX(halfCosPlayerRotY, 0);

            if (temp_a2 >= temp_v1)
            {
                cond = clampedHalfCosPlayerRotY < temp_v1;
            }
            else
            {
                cond = clampedHalfCosPlayerRotY < temp_a2;
            }

            if (!cond)
            {
                if (MIN(halfCosPlayerRotY, 0) <= MAX(temp_v1, temp_a2) &&
                   (((temp_s2 * halfCosPlayerRotY) - (halfSinRotY * temp_v1)) <= 0) && ((temp_s4 * halfCosPlayerRotY) - (halfSinRotY * temp_a2)) >= 0 &&
                   ((-temp_s2 * (temp_a2 - temp_v1)) + ((temp_s4 - temp_s2) * temp_v1)) >= 0)
                {
                    return (((halfSinRotY - temp_s2) * (temp_a2 - temp_v1)) -
                            ((temp_s4 - temp_s2) * (halfCosPlayerRotY - temp_v1))) < 1;
                }
            }
        }
    }

    return false;
}

bool Event_CollideObbCheck(s_MapPoint2d* mapPoint) // 0x80037C5C
{
    q19_12 sinAngle;
    q19_12 cosAngle;
    q19_12 angle;
    q19_12 deltaX;
    q19_12 deltaZ;
    s32    shift8Field_7;
    s32    temp_v0;
    s32    scale;
    u32    temp;

    shift8Field_7 = mapPoint->data.areaLoad.field_4_24 << 8;

    deltaX = g_SysWork.playerWork_4C.player_0.position_18.vx - mapPoint->positionX_0;
    if (mapPoint->data.areaLoad.field_4_24 << 9 < ABS(deltaX))
    {
        return false;
    }

    deltaZ = g_SysWork.playerWork_4C.player_0.position_18.vz - mapPoint->positionZ_8;
    scale  = 2;
    if ((shift8Field_7 * scale) < ABS(deltaZ))
    {
        return false;
    }

    // TODO: Odd packed angle conversion method. `FP_ANGLE_FROM_PACKED` doesn't match here.
    angle    = -(mapPoint->data.areaLoad.rotationY_4_16 << 20) >> 16;
    sinAngle = Math_Sin(angle);

    temp = FP_FROM((-deltaX * sinAngle) + (deltaZ * Math_Cos(angle)), Q12_SHIFT);
    if (temp > Q12(4.0f))
    {
        return false;
    }

    cosAngle = Math_Cos(angle);
    temp_v0  = FP_FROM((deltaX * cosAngle) + (deltaZ * Math_Sin(angle)), Q12_SHIFT);
    if (shift8Field_7 < ABS(temp_v0))
    {
        return false;
    }
    else
    {
        return true;
    }
}

// ========================================
// NPC RELATED - UPDATES
// ========================================

void Savegame_EnemyStateUpdate(s_SubCharacter* chara) // 0x80037DC4
{
    if (g_SavegamePtr->gameDifficulty_260 <= GameDifficulty_Normal || Rng_RandQ12() >= FP_ANGLE(108.0f))
    {
        g_SavegamePtr->ovlEnemyStates[g_SavegamePtr->mapOverlayId_A4] &= ~(1 << chara->field_40);
    }
}

void Chara_DamageFlagUpdate(s_SubCharacter* chara) // 0x80037E40
{
    if (chara->damage_B4.amount_C > Q12(0.0f))
    {
        chara->flags_3E |= CharaFlag_Unk6;
    }
    else
    {
        chara->flags_3E &= ~CharaFlag_Unk6;
    }
}

void func_80037E78(s_SubCharacter* chara) // 0x80037E78
{
    s8  idx;
    s32 cond;

    // TODO: Strange `chara->headingAngle_3C` access.
    if (chara->health_B0 <= Q12(0.0f) && (*(s32*)&chara->headingAngle_3C & 0x600000) == 0x200000)
    {
        idx = chara->attackReceived_41;
        if (idx < 39)
        {
            cond = D_800AD4C8[idx].field_10 == 3;
            func_800914C4(cond, func_8009146C(cond) + 1);
        }

        chara->flags_3E |= CharaFlag_Unk7;
    }
}

void Game_NpcRoomInitSpawn(bool cond) // 0x80037F24
{
    s_Collision     coll;
    s32             charaId0;
    s32             charaId1;
    s32             npcIdx;
    s32             i;
    s32*            ovlEnemiesStatePtr;
    s_MapPoint2d*   curCharaSpawn;
    s_SubCharacter* chara;
    VECTOR3*        pos;

    npcIdx             = 0;
    curCharaSpawn      = g_MapOverlayHeader.charaSpawns_24C[0];
    ovlEnemiesStatePtr = &g_SavegamePtr->ovlEnemyStates[g_SavegamePtr->mapOverlayId_A4];

    if (cond == false)
    {
        func_80037154();

        if (g_MapOverlayHeader.func_48 != NULL)
        {
            g_MapOverlayHeader.func_48();
        }
    }

    charaId0 = g_MapOverlayHeader.charaGroupIds_248[0];
    charaId1 = g_MapOverlayHeader.charaGroupIds_248[1];

    for (i = 0; i < 32 && g_VBlanks < 4; i++, curCharaSpawn++)
    {
        if (g_SysWork.npcFlags_2290 == ((1 << g_SysWork.npcId_2280) - 1)) // TODO: Macro for this check?
        {
            break;
        }

        pos = (VECTOR3*)curCharaSpawn;

        if (!(g_SysWork.flags_22A4 & SysFlag2_4) && HAS_FLAG(ovlEnemiesStatePtr, i) && !HAS_FLAG(g_SysWork.field_228C, i) &&
            curCharaSpawn->data.spawnInfo.flags_6 != 0 && g_SavegamePtr->gameDifficulty_260 >= curCharaSpawn->data.spawnInfo.field_7_0 &&
            func_8008F914(curCharaSpawn->positionX_0, curCharaSpawn->positionZ_8) &&
            !Math_Distance2dCheck(&g_SysWork.playerWork_4C.player_0.position_18, pos, Q12(22.0f)) &&
            (!cond || Math_Distance2dCheck(&g_SysWork.playerWork_4C.player_0.position_18, pos, Q12(20.0f))))
        {
            while (HAS_FLAG(&g_SysWork.npcFlags_2290, npcIdx))
            {
                npcIdx++;
            }

            bzero(&g_SysWork.npcs_1A0[npcIdx], sizeof(s_SubCharacter));

            if (curCharaSpawn->data.spawnInfo.charaId_4 > Chara_None)
            {
                g_SysWork.npcs_1A0[npcIdx].model_0.charaId_0 = curCharaSpawn->data.spawnInfo.charaId_4;
            }
            else
            {
                g_SysWork.npcs_1A0[npcIdx].model_0.charaId_0 = (i < 16) ? charaId0 : charaId1;
            }

            g_SysWork.npcs_1A0[npcIdx].field_40               = i;
            g_SysWork.npcs_1A0[npcIdx].model_0.controlState_2 = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[npcIdx].model_0.stateStep_3    = curCharaSpawn->data.spawnInfo.flags_6;
            g_SysWork.npcs_1A0[npcIdx].position_18.vx         = curCharaSpawn->positionX_0;
            g_SysWork.npcs_1A0[npcIdx].position_18.vz         = curCharaSpawn->positionZ_8;

            Collision_Get(&coll, curCharaSpawn->positionX_0, curCharaSpawn->positionZ_8);

            g_SysWork.npcs_1A0[npcIdx].position_18.vy = coll.groundHeight_0;
            g_SysWork.npcs_1A0[npcIdx].rotation_24.vy = curCharaSpawn->data.spawnInfo.rotationY_5 * 16;

            SET_FLAG(&g_SysWork.npcFlags_2290, npcIdx);
            SET_FLAG(g_SysWork.field_228C, i);

            chara                          = &g_SysWork.npcs_1A0[npcIdx];
            chara->model_0.anim_4.flags_2 |= AnimFlag_Visible;
        }
    }
}

void Game_NpcUpdate(void) // 0x80038354
{
    typedef struct
    {
        s8      bitIdx_0;
        u8      unk_1[3];
        s32     field_4;
        VECTOR3 field_8;
    } s_func_800382EC_0;

    s_func_800382EC_0  field_0[3];
    u32                field_40;
    s32                posZShift6;
    s32                posXShift6;
    s32                temp_t1;
    s32                m;
    u8                 var_a2_2;
    s32                j;
    s32                var_s3;
    s32                k;
    s32                var_t5;
    s32                var_v0_4;
    s32                var_v1_3;
    s32                temp_s0_2;
    s32                temp_s0_4;
    s8                 temp_s1;
    s32                temp_v0_4;
    s32                var_v0_5;
    u32                temp_t3;
    u8                 temp_a2;
    u32                new_var;
    s32                l;
    s32                animDataInfoIdx;
    s32                temp2;
    GsCOORDINATE2*     coord;
    s_SubCharacter*    npc;
    s_func_800382EC_0* temp_s0_3;

    // GCC extension funcs.
    s32 func_800382B0(s32 arg0)
    {
        s32 i;

        for (i = 0; i < 2; i++)
        {
            if (arg0 == field_0[i].bitIdx_0)
            {
                return i;
            }
        }

        return NO_VALUE;
    }

    s32 func_800382EC()
    {
        s32 i;

        for (i = 0; i < 2; i++)
        {
            if (field_0[i].bitIdx_0 == NO_VALUE)
            {
                break;
            }

            if ((field_40 & (1 << field_0[i].bitIdx_0)) == 0)
            {
                field_40 |= (1 << field_0[i].bitIdx_0);
                return i;
            }
        }

        return NO_VALUE;
    }

    posXShift6 = g_SysWork.playerWork_4C.player_0.position_18.vx >> 6;
    posZShift6 = g_SysWork.playerWork_4C.player_0.position_18.vz >> 6;

    Demo_DemoRandSeedBackup();
    Demo_DemoRandSeedRestore();

    for (j = 0; j < ARRAY_SIZE(field_0); j++)
    {
        field_0[j].bitIdx_0   = NO_VALUE;
        field_0[j].field_4    = Q12(0.25f);
        field_0[j].field_8.vy = 0;
    }

    for (k = 0, npc = g_SysWork.npcs_1A0; k < ARRAY_SIZE(g_SysWork.npcs_1A0); k++, npc++)
    {
        if (npc->model_0.charaId_0 != Chara_None && npc->model_0.charaId_0 != Chara_Padlock)
        {
            if (npc->model_0.charaId_0 <= Chara_MonsterCybil)
            {
                temp_t3 = FP_SQUARE_PRECISE((npc->position_18.vx >> 6) - posXShift6, Q12_SHIFT) +
                          FP_SQUARE_PRECISE((npc->position_18.vz >> 6) - posZShift6, Q12_SHIFT);
                var_t5 = 0;

                if (g_MapOverlayHeader.mapInfo_0->flags_6 & MapFlag_Interior)
                {
                    var_t5 = (g_MapOverlayHeader.mapInfo_0->flags_6 & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)) > 0;
                }

                for (j = 0; j < 3; j++)
                {
                    if (npc->health_B0 <= Q12(0.0f) || npc->flags_3E & CharaFlag_Unk9 || temp_t3 >= field_0[j].field_4)
                    {
                        continue;
                    }

                    if (var_t5 != 0)
                    {
                        s32 playerCell = (g_SysWork.playerWork_4C.player_0.position_18.vx + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        s32 npcCell    = (npc->position_18.vx                        + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        if (npcCell != playerCell)
                        {
                            continue;
                        }

                        // TODO: Unique vars for these.
                        playerCell = (g_SysWork.playerWork_4C.player_0.position_18.vz + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        npcCell    = (npc->position_18.vz                        + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        if (npcCell != playerCell)
                        {
                            continue;
                        }
                    }

                    for (m = 2; j < m; m--)
                    {
                        field_0[m].bitIdx_0   = field_0[m - 1].bitIdx_0;
                        field_0[m].field_4    = field_0[m - 1].field_4;
                        field_0[m].field_8.vx = field_0[m - 1].field_8.vx;
                        field_0[m].field_8.vz = field_0[m - 1].field_8.vz;
                    }

                    temp_t1 = (u32)npc - (u32)g_SysWork.npcs_1A0;
                    temp2   = ((((temp_t1 * 0x7E8) - (temp_t1 * 0xFD)) * 4) + temp_t1) * -0x3FFFF;

                    field_0[j].bitIdx_0   = temp2 >> 3;
                    field_0[j].field_4    = temp_t3;
                    field_0[j].field_8.vx = npc->position_18.vx;
                    field_0[j].field_8.vz = npc->position_18.vz;
                    break;
                }

                new_var = temp_t3;

                if (new_var > ((var_t5 == 0 && npc->health_B0 < Q12(0.0f)) ? SQUARE(24) : SQUARE(40)))
                {
                    npc->model_0.charaId_0 = Chara_None;
                    SysWork_NpcFlagClear(k);
                    CLEAR_FLAG(g_SysWork.field_228C, npc->field_40);
                    continue;
                }

                if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 0x2 && temp_t3 > SQUARE(15)) ||
                    (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 0x2) &&
                     Camera_Distance2dGet(&npc->position_18) > SQUARE(15)))
                {
                    npc->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
                }
                else
                {

                    npc->model_0.anim_4.flags_2 |= AnimFlag_Visible;
                }
            }

            npc->model_0.anim_4.flags_2 |= AnimFlag_Unlocked;

            animDataInfoIdx = g_CharaAnimInfoIdxs[npc->model_0.charaId_0];
            coord           = g_CharaTypeAnimInfo[animDataInfoIdx].npcCoords_14;

            func_8008A384(npc);
            Chara_DamageFlagUpdate(npc);
            func_8003BD48(npc);

            g_MapOverlayHeader.charaUpdateFuncs_194[npc->model_0.charaId_0](npc, g_CharaTypeAnimInfo[animDataInfoIdx].animFile1_8, coord);

            func_8003BE28();
            func_80037E78(npc);
            func_8008A3AC(npc);

            if (npc->model_0.anim_4.flags_2 & AnimFlag_Visible)
            {
                func_8003DA9C(npc->model_0.charaId_0, coord, 1, npc->timer_C6, (s8)npc->model_0.paletteIdx_1);
            }
        }
    }

    for (k = 2; k >= 0; k--)
    {
        if (field_0[k].bitIdx_0 != NO_VALUE)
        {
            break;
        }
    }

    g_RadioPitchState = k + 1;

    if (!(g_SavegamePtr->itemToggleFlags_AC & ItemToggleFlag_RadioOn))
    {
        return;
    }

    field_40 = 0;

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        temp_s0_2 = D_800BCDA8[l].field_1;
        if (temp_s0_2 == NO_VALUE)
        {
            var_v0_4 = NO_VALUE;
        }
        else
        {
            var_v0_4 = func_800382B0(temp_s0_2);
        }

        if (var_v0_4 >= 0)
        {
            D_800BCDA8[l].field_2 = var_v0_4;
            field_40             |= 1 << temp_s0_2;
        }
        else
        {
            D_800BCDA8[l].field_1 = NO_VALUE;
        }
    }

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        temp_s1 = D_800BCDA8[l].field_1;
        if (temp_s1 == NO_VALUE)
        {
            temp_v0_4 = func_800382EC();
            if (temp_v0_4 != temp_s1)
            {
                var_v0_5 = field_0[temp_v0_4].bitIdx_0;
            }
            else
            {
                var_v0_5 = NO_VALUE;
            }

            D_800BCDA8[l].field_2 = temp_v0_4;
            D_800BCDA8[l].field_1 = var_v0_5;
        }
    }

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        if (D_800BCDA8[l].field_0 == NO_VALUE)
        {
            if (D_800BCDA8[l].field_1 >= 0)
            {
                SD_Call((u16)(Sfx_RadioInterferenceLoop + l));
            }
        }
        else
        {
            var_s3 = 0;
            if (!(g_MapOverlayHeader.mapInfo_0->flags_6 & MapFlag_Interior) ||
                !(g_MapOverlayHeader.mapInfo_0->flags_6 & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)))
            {
                var_s3 = 1;
            }

            if (D_800BCDA8[l].field_1 >= 0)
            {
                temp_s0_3 = &field_0[D_800BCDA8[l].field_2];
                temp_s0_4 = Sound_StereoBalanceGet(&temp_s0_3->field_8);

                var_v1_3 = SquareRoot12(temp_s0_3->field_4 << Q12_SHIFT) >> 8;
                if (var_s3 != 0)
                {
                    var_v1_3 >>= 1;
                }

                var_a2_2 = CLAMP(var_v1_3, 0, 0xFF);

                Sd_SfxAttributesUpdate(Sfx_RadioInterferenceLoop + l, temp_s0_4, var_a2_2, 0);
            }
            else
            {
                Sd_SfxStop(Sfx_RadioInterferenceLoop + l);
            }
        }

        D_800BCDA8[l].field_0 = D_800BCDA8[l].field_1;
    }
}

bool Math_Distance2dCheck(const VECTOR3* posFrom, const VECTOR3* posTo, q19_12 radius) // 0x80038A6C
{
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 radiusSqr;
    q19_12 sum;

    // Check rough radius intersection on X axis.
    deltaX = posFrom->vx - posTo->vx;
    if (radius < deltaX)
    {
        return true;
    }
    if (radius < -deltaX)
    {
        return true;
    }

    // Check rough radius intersection on Z axis.
    deltaZ = posFrom->vz - posTo->vz;
    if (radius < deltaZ)
    {
        return true;
    }
    if (radius < -deltaZ)
    {
        return true;
    }

    // Check distance.
    sum       = Q12_MULT_PRECISE(deltaX, deltaX) + Q12_MULT_PRECISE(deltaZ, deltaZ);
    radiusSqr = Q12_MULT_PRECISE(radius, radius);
    return sum > radiusSqr;
}

s32 Camera_Distance2dGet(const VECTOR3* pos) // 0x80038B44
{
    VECTOR3 camPos; // Q19.12
    q25_6   deltaX;
    q25_6   deltaZ;

    vwGetViewPosition(&camPos);
    deltaX = Q12_TO_Q6(camPos.vx - pos->vx);
    deltaZ = Q12_TO_Q6(camPos.vz - pos->vz);
    return Q12_MULT_PRECISE(deltaX, deltaX) + Q12_MULT_PRECISE(deltaZ, deltaZ);
}

// ========================================
// GAME STATES UPDATERS
// ========================================

const s32 pad_rodata_800252B8 = 0;

/** @brief SFX pairs.
 * 
 * @note Used when loading areas. Maybe facilitates things like the
 * opening and closing door SFX when the player moves between rooms. */
s_AreaLoadSfx const SfxPairs[25] = {
    { Sfx_Base, Sfx_Base },
    { Sfx_DoorOpen0, Sfx_DoorClose0 },
    { Sfx_Unk1323, Sfx_Unk1324 },
    { Sfx_Unk1418, Sfx_Base },
    { Sfx_Unk1354, Sfx_Base },
    { Sfx_Unk1387, Sfx_Base },
    { Sfx_Unk1391, Sfx_Base },
    { Sfx_Unk1521, Sfx_Base },
    { Sfx_Unk1458, Sfx_Unk1459 },
    { Sfx_Unk1604, Sfx_Unk1605 },
    { Sfx_Unk1609, Sfx_Unk1610 },
    { Sfx_Unk1396, Sfx_Unk1397 },
    { Sfx_Unk1336, Sfx_Unk1337 },
    { Sfx_Unk1338, Sfx_Unk1339 },
    { Sfx_Unk1340, Sfx_Unk1341 },
    { Sfx_Unk1601, Sfx_Unk1602 },
    { Sfx_Unk1490, Sfx_Unk1491 },
    { Sfx_Unk1431, Sfx_Unk1432 },
    { Sfx_Unk1398, Sfx_Unk1399 },
    { Sfx_Unk1504, Sfx_Unk1505 },
    { Sfx_DoorOpen0, Sfx_Base },
    { Sfx_Unk1323, Sfx_Base },
    { Sfx_Base, Sfx_Unk1324 },
    { Sfx_Unk1351, Sfx_Unk1352 },
    { Sfx_Unk1487, Sfx_Base }
};


// These are referenced by pointers at `0x800A99E8`, which are then used by `Map_WorldObjectsInit`.
// Maybe meant to be separate .c file with .h externs.
const char g_80025320[] = "SHOT_NEA";
const char g_8002532C[] = "SHELL_NE";
const char g_80025338[] = "BULLET_N";
const char g_80025344[] = "AMPULE_N";
const char g_80025350[] = "DRINK_NE";
const char g_8002535C[] = "AIDKIT_N";
const char g_80025368[] = "PAD_NEAR";

void GameState_InGame_Update(void) // 0x80038BD4
{
    s_SubCharacter* player;

    Demo_DemoRandSeedBackup();

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            ScreenFade_Start(true, true, false);
            g_ScreenFadeTimestep            = Q12(3.0f);
            g_GameWork.gameStateStep_598[0] = 1;

        case 1:
            DrawSync(SyncMode_Wait);
            func_80037154();
            Savegame_MapRoomIdxUpdate();
            func_800892A4(1);

            g_IntervalVBlanks = 2;
            g_GameWork.gameStateStep_598[0]++;
            g_SysWork.sysFlags_22A0 |= SysFlag_6;
            break;
    }

    if (g_SysWork.sysState_8 != SysState_Gameplay && g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
    {
        SysWork_StateSetNext(SysState_Gameplay);
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        g_DeltaTimeCpy = g_DeltaTime0;
    }
    else
    {
        g_DeltaTimeCpy = g_DeltaTime1;
    }

    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        g_SysWork.isMgsStringSet_18 = 0;
        g_SysStateFuncs[SysState_Gameplay]();
    }
    else
    {
        g_DeltaTime0 = 0;
        g_SysStateFuncs[g_SysWork.sysState_8]();

        if (g_SysWork.sysState_8 == SysState_Gameplay)
        {
            Event_Update(true);

            if (g_MapEventSysState != SysState_Invalid)
            {
                SysWork_StateSetNext(g_MapEventSysState);
            }
        }
    }
    Demo_DemoRandSeedRestore();

    D_800A9A0C = ScreenFade_IsFinished() && Fs_QueueDoThingWhenEmpty();

    if (!(g_SysWork.sysFlags_22A0 & SysFlag_Freeze) && g_MapOverlayHeader.worldObjectsUpdate_40 != NULL)
    {
        g_MapOverlayHeader.worldObjectsUpdate_40();
    }

    Screen_CutsceneCameraStateUpdate();
    Bgm_TrackUpdate(false);
    Demo_DemoRandSeedRestore();
    Demo_DemoRandSeedRestore();

    if (!(g_SysWork.sysFlags_22A0 & SysFlag_Freeze))
    {
        func_80040014();
        vcMoveAndSetCamera(false, false, false, false, false, false, false, false);

        if (g_MapOverlayHeader.func_44 != NULL)
        {
            g_MapOverlayHeader.func_44();
        }

        Demo_DemoRandSeedRestore();

        player = &g_SysWork.playerWork_4C.player_0;
        Player_Update(player, FS_BUFFER_0, g_SysWork.playerBoneCoords_890);

        Demo_DemoRandSeedRestore();
        Gfx_FlashlightUpdate();

        if (g_SavegamePtr->mapOverlayId_A4 != MapOverlayId_MAP7_S03)
        {
            g_MapOverlayHeader.particlesUpdate_168(0, g_SavegamePtr->mapOverlayId_A4, 1);
        }

        Demo_DemoRandSeedRestore();

        if (player->model_0.anim_4.flags_2 & AnimFlag_Visible)
        {
            func_8003DA9C(Chara_Harry, g_SysWork.playerBoneCoords_890, 1, g_SysWork.playerWork_4C.player_0.timer_C6, 0);
            func_8008A384(&g_SysWork.playerWork_4C.player_0);
            Player_CombatUpdate(&g_SysWork.playerWork_4C, g_SysWork.playerBoneCoords_890);
            func_8008A3AC(&g_SysWork.playerWork_4C.player_0);
        }

        Demo_DemoRandSeedRestore();
        Game_NpcRoomInitSpawn(true);
        Game_NpcUpdate();
        func_8005E89C();
        Ipd_CloseRangeChunksInit();
        Gfx_InGameDraw(1);
        Demo_DemoRandSeedAdvance();
    }
}

void SysState_Gameplay_Update(void) // 0x80038BD4
{
    s_SubCharacter* player;

    player = &g_SysWork.playerWork_4C.player_0;

    Event_Update(player->attackReceived_41 != NO_VALUE);
    Savegame_MapRoomIdxUpdate();

    switch (FP_ROUND_SCALED(player->health_B0, 10, Q12_SHIFT))
    {
        case 0:
            func_800892A4(17);
            break;

        case 1:
        case 2:
            func_800892A4(16);
            break;

        case 3:
            func_800892A4(15);
            break;

        case 4:
            func_800892A4(14);
            break;

        case 5:
            func_800892A4(13);
            break;

        case 6:
            func_800892A4(12);
            break;
    }

    if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
    {
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.light_A &&
        g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1))
    {
        Game_FlashlightToggle();
    }

    if (g_MapEventSysState != SysState_Invalid)
    {
        SysWork_StateSetNext(g_MapEventSysState);
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        SysWork_StateSetNext(SysState_GamePaused);
    }
    else if (Player_IsAttacking() == true)
    {
        return;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
    {
        SysWork_StateSetNext(SysState_StatusMenu);
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18)
    {
        SysWork_StateSetNext(SysState_MapScreen);
        g_SysWork.isMgsStringSet_18 = 0;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A)
    {
        SysWork_StateSetNext(SysState_OptionsMenu);
    }

    if (g_SysWork.sysState_8 == SysState_OptionsMenu ||
        g_SysWork.sysState_8 == SysState_StatusMenu ||
        g_SysWork.sysState_8 == SysState_MapScreen)
    {
        g_SysWork.flags_22A4 |= SysFlag2_MenuOpen;
    }
    else if (ScreenFade_IsNone())
    {
        g_SysWork.flags_22A4 &= ~SysFlag2_MenuOpen;
    }
}

void SysState_GamePaused_Update(void) // 0x800391E8
{
    D_800A9A68 += g_DeltaTime1;
    if (!((D_800A9A68 >> 11) & (1 << 0)))
    {
        Gfx_StringSetPosition(SCREEN_POSITION_X(39.25f), SCREEN_POSITION_Y(43.5f));
        Gfx_StringDraw("\x07PAUSED", DEFAULT_MAP_MESSAGE_LENGTH);
    }

    func_80091380();
    Game_TimerUpdate();

    if (g_SysWork.sysStateStep_C[0] == 0)
    {
        SD_Call(3);
        g_SysWork.sysStateStep_C[0]++;
    }

    // Debug button combo to bring up save screen from pause screen.
    // DPad-Left + L2 + L1 + LS-Left + RS-Left + L3
    if ((g_Controller0->btnsHeld_C == (ControllerFlag_L3 |
                                       ControllerFlag_DpadLeft |
                                       ControllerFlag_L2 |
                                       ControllerFlag_L1 |
                                       ControllerFlag_LStickLeft2 |
                                       ControllerFlag_RStickLeft |
                                       ControllerFlag_LStickLeft)) &&
        (g_Controller0->btnsClicked_10 & ControllerFlag_L3))
    {
        D_800A9A68 = 0;
        SD_Call(4);
        g_MapEventIdx = 0;
        SysWork_StateSetNext(SysState_SaveMenu1);
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        D_800A9A68 = 0;
        SD_Call(4);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

void SysState_OptionsMenu_Update(void) // 0x80039344
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            ScreenFade_Start(true, false, false);
            g_ScreenFadeTimestep        = Q12(0.0f);
            g_SysWork.sysStateStep_C[0] = 1;

        case 1:
            if (Ipd_ChunkInitCheck() != 0)
            {
                SD_Call(19);
                GameFs_OptionBinLoad();

                g_SysWork.sysStateStep_C[0]++;
            }
            break;
    }

    if (D_800A9A0C != 0)
    {
        Game_StateSetNext(GameState_OptionScreen);
    }
}

void func_8003943C(void) // 0x8003943C
{
    s32 roundedVal0;
    s32 roundedVal1;
    s32 val0;
    s32 val1;

    func_8008B3E4(0);

    if (g_SysWork.field_275C > Q12(256.0f))
    {
        val0        = g_SysWork.field_275C - Q12(256.0f);
        roundedVal0 = FP_ROUND_TO_ZERO(val0, Q12_SHIFT);
        func_8008B438(g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap), roundedVal0, 0);

        if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
        {
            val1        = g_SysWork.field_2764 - Q12(256.0f);
            roundedVal1 = FP_ROUND_TO_ZERO(val1, Q12_SHIFT);
            func_8008B40C(roundedVal1, 0);
        }
    }
    else
    {
        func_8008B438(g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap), 0, 0);

        if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
        {
            func_8008B40C(0, 0);
        }
    }
    
    switch (g_SavegamePtr->mapOverlayId_A4)
    {
        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S04:
        case MapOverlayId_MAP1_S05:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S03:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S04:
        case MapOverlayId_MAP4_S05:
        case MapOverlayId_MAP4_S06:
        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
        case MapOverlayId_MAP6_S05:
        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
        case MapOverlayId_MAP7_S02:
            break;

        case MapOverlayId_MAP3_S03:
            Sd_SfxStop(Sfx_Unk1525);
            Sd_SfxStop(Sfx_Unk1527);
            break;

        case MapOverlayId_MAP0_S00:
            Sd_SfxStop(Sfx_Unk1358);
            break;
    }
}

void SysState_StatusMenu_Update(void) // 0x80039568
{
    e_GameState gameState;

    gameState = g_GameWork.gameState_594;

    g_GameWork.gameState_594 = GameState_LoadStatusScreen;
    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = gameState;
    g_GameWork.gameStatePrev_590    = gameState;
    g_GameWork.gameStateStep_598[0] = 0;
}

void GameState_LoadStatusScreen_Update(void) // 0x800395C0
{
    s_Savegame* save;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(SyncMode_Wait);
        g_IntervalVBlanks   = 1;
        ScreenFade_Reset();

        func_8003943C();

        if (Sd_AudioStreamingCheck())
        {
            SD_Call(19);
        }

        save = g_SavegamePtr;
        func_800540A4(save->mapOverlayId_A4);
        GameFs_MapItemsTextureLoad(save->mapOverlayId_A4);

        g_GameWork.gameStateStep_598[0]++;
    }

    Gfx_2dBackgroundMotionBlur(SyncMode_Wait2);

    if (Fs_QueueDoThingWhenEmpty())
    {
        Game_StateSetNext(GameState_InventoryScreen);
    }
}

void SysState_MapScreen_Update(void) // 0x800396D4
{
    if (!HAS_MAP(g_SavegamePtr->paperMapIdx_A9))
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18 ||
            Gfx_MapMsg_Draw(MapMsgIdx_NoMap) > MapMsgState_Idle)
        {
            SysWork_StateSetNext(SysState_Gameplay);
        }
    }
    else if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) && !g_SysWork.field_2388.isFlashlightOn_15 &&
             ((g_SysWork.field_2388.field_1C[0].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)) ||
              (g_SysWork.field_2388.field_1C[1].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))))
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18 ||
            Gfx_MapMsg_Draw(MapMsgIdx_TooDarkForMap) > MapMsgState_Idle)
        {
            SysWork_StateSetNext(SysState_Gameplay);
        }
    }
    else
    {
        if (g_SysWork.sysStateStep_C[0] == 0)
        {
            if (g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9] != NO_VALUE)
            {
                Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);
            }

            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[g_SavegamePtr->paperMapIdx_A9]);

            ScreenFade_Start(true, false, false);
            g_ScreenFadeTimestep = Q12(0.0f);
            g_SysWork.sysStateStep_C[0]++;
        }

        if (D_800A9A0C != 0)
        {
            Game_StateSetNext(GameState_MapScreen);
        }
    }
}

void GameState_LoadMapScreen_Update(void) // 0x8003991C
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(SyncMode_Wait);
        g_IntervalVBlanks = 1;

        func_8003943C();
        func_80066E40();

        if (g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9] != NO_VALUE)
        {
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);
        }

        Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_2, &g_PaperMapImg);
        g_GameWork.gameStateStep_598[0]++;
    }

    Gfx_2dBackgroundMotionBlur(SyncMode_Wait2);

    if (Fs_QueueDoThingWhenEmpty())
    {
        Game_StateSetNext(GameState_MapScreen);
    }
}

void SysState_Fmv_Update(void) // 0x80039A58
{
    #define BASE_AUDIO_FILE_IDX FILE_XA_ZC_14392

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            ScreenFade_Start(false, false, false);
            D_800A9A0C                  = 0;
            g_SysWork.sysStateStep_C[0] = 1;

        case 1:
            if (Ipd_ChunkInitCheck() != 0)
            {
                GameFs_StreamBinLoad();
                g_SysWork.sysStateStep_C[0]++;
            }
            break;
    }

    if (D_800A9A0C == 0)
    {
        return;
    }

    // Copy framebuffer into `IMAGE_BUFFER_0` before movie playback.
    DrawSync(SyncMode_Wait);
    StoreImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(SyncMode_Wait);

    func_800892A4(0);
    func_80089128();

    // Start playing movie. File to play is based on file ID `BASE_AUDIO_FILE_IDX - g_MapEventIdx`.
    // Blocks until movie has finished playback or user has skipped it.
    open_main(BASE_AUDIO_FILE_IDX - g_MapEventIdx, g_FileTable[BASE_AUDIO_FILE_IDX - g_MapEventIdx].blockCount_0_19);

    func_800892A4(1);

    // Restore copied framebuffer from `IMAGE_BUFFER_0`.
    GsSwapDispBuff();
    LoadImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(SyncMode_Wait);

    // Set savegame flag based on `g_MapEventParam->disabledEventFlag_2` flag ID.
    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);

    // Return to game.
    Game_StateSetNext(GameState_InGame);

    // If flag is set, returns to `GameState_InGame` with `gameStateStep[0]` = 1.
    if (g_MapEventParam->flags_8_13 & EventParamUnkState_1)
    {
        g_GameWork.gameStateStep_598[0] = 1;
    }
}

void SysState_LoadArea_Update(void) // 0x80039C40
{
    u32           var1;
    s_MapPoint2d* mapPoint;

    g_SysWork.field_229C            = 0;
    g_SysWork.loadingScreenIdx_2281 = D_800BCDB0.data.areaLoad.loadingScreenId_4_9;
    g_SysWork.field_2283            = g_MapEventParam->field_8_19;
    g_SysWork.field_2282            = g_MapEventParam->flags_8_13;

    SD_Call(SfxPairs[g_SysWork.field_2283].sfx_0);

    if (g_SysWork.field_2283 == 7)
    {
        D_800BCDD4            = 0;
        g_SysWork.flags_22A4 |= SysFlag2_10;
    }

    D_800BCDB0 = g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventParam->pointOfInterestIdx_8_5];

    if (D_800BCDB0.data.areaLoad.field_4_24 == 1)
    {
        mapPoint                = &g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventParam->field_5];
        var1                    = g_SysWork.playerWork_4C.player_0.position_18.vz - mapPoint->positionZ_8;
        D_800BCDB0.positionX_0 += g_SysWork.playerWork_4C.player_0.position_18.vx - mapPoint->positionX_0;
        D_800BCDB0.positionZ_8 += var1;
    }

    if (g_SysWork.sysState_8 == SysState_LoadOverlay)
    {
        g_SysWork.processFlags_2298    = SysWorkProcessFlag_OverlayTransition;
        g_SavegamePtr->mapOverlayId_A4 = g_MapEventParam->mapOverlayIdx_8_25;
        GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);
    }
    else
    {
        g_SysWork.processFlags_2298 = SysWorkProcessFlag_RoomTransition;
        Bgm_TrackChange(g_MapEventParam->mapOverlayIdx_8_25);

        if (g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventParam->pointOfInterestIdx_8_5].data.areaLoad.field_4_5 != 0)
        {
            g_SysWork.field_2349 = g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventParam->pointOfInterestIdx_8_5].data.areaLoad.field_4_5 - 1;
        }
    }

    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);

    if (g_MapEventParam->field_8_24)
    {
        g_SysWork.flags_22A4 |= SysFlag2_6;
    }
    else
    {
        g_SysWork.flags_22A4 &= ~SysFlag2_6;
    }

    g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    Game_StateSetNext(GameState_MainLoadScreen);
    Gfx_2dBackgroundMotionBlur(SyncMode_Immediate);
}

// ========================================
// MAP EVENTS RELATED
// ========================================

void AreaLoad_UpdatePlayerPosition(void) // 0x80039F30
{
    Chara_PositionSet(&D_800BCDB0);
}

void AreaLoad_TransitionSound(void) // 0x80039F54
{
    SD_Call(SfxPairs[g_SysWork.field_2283].sfx_2);
}

s8 func_80039F90(void) // 0x80039F90
{
    if (g_SysWork.processFlags_2298 & (SysWorkProcessFlag_RoomTransition | SysWorkProcessFlag_OverlayTransition))
    {
        return g_SysWork.field_2282;
    }

    return 0;
}

void SysState_ReadMessage_Update(void) // 0x80039FB8
{
    s32 i;
    void (**unfreezePlayerFunc)(bool);
	
	// When `SysState_ReadMessage_Update` is called, the game world freezes.
	// The following conditions unfreeze:
	// - A specific event related flag is disenabled.
	// - A specific camera related flag is disenabled.
	// - There is no alive enemy.
    if (!(g_MapEventParam->flags_8_13 & EventParamUnkState_0) && !(g_SysWork.flags_22A4 & SysFlag2_5))
    {
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry && g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil &&
                g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f))
            {
                break;
            }
        }

        if (i == ARRAY_SIZE(g_SysWork.npcs_1A0))
        {
            g_DeltaTime0 = g_DeltaTimeCpy;
        }
    }
    else
    {
        g_DeltaTime0 = g_DeltaTimeCpy;
    }

    if (g_SysWork.isMgsStringSet_18 == 0)
    {
        g_MapOverlayHeader.playerControlFreeze_C8();
    }

    switch (Gfx_MapMsg_Draw(g_MapEventIdx)) 
    {
        case MapMsgState_Finish:
            break;

        case MapMsgState_Idle:
            break;

        case MapMsgState_SelectEntry0:
            Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);

            unfreezePlayerFunc = &g_MapOverlayHeader.playerControlUnfreeze_CC;

            SysWork_StateSetNext(SysState_Gameplay);

            (*unfreezePlayerFunc)(false);
            break;
    }
}

void SysWork_SavegameUpdatePlayer(void) // 0x8003A120
{
    s_Savegame* save;

    save = g_SavegamePtr;

    save->locationId_A8       = g_MapEventIdx;
    save->playerPositionX_244 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    save->playerPositionZ_24C = g_SysWork.playerWork_4C.player_0.position_18.vz;
    save->playerRotationY_248 = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    save->playerHealth_240    = g_SysWork.playerWork_4C.player_0.health_B0;
}

void func_8003A16C(void) // 0x8003A16C
{
    if (!(g_SysWork.flags_22A4 & SysFlag2_1))
    {
        // Update `savegame_30C` with player info.
        SysWork_SavegameUpdatePlayer();

        g_GameWork.autosave_90 = g_GameWork.savegame_30C;
    }
}

void SysWork_SavegameReadPlayer(void) // 0x8003A1F4
{
    g_SysWork.playerWork_4C.player_0.position_18.vx = g_SavegamePtr->playerPositionX_244;
    g_SysWork.playerWork_4C.player_0.position_18.vz = g_SavegamePtr->playerPositionZ_24C;
    g_SysWork.playerWork_4C.player_0.rotation_24.vy = g_SavegamePtr->playerRotationY_248;
    g_SysWork.playerWork_4C.player_0.health_B0      = g_SavegamePtr->playerHealth_240;
}

void SysState_SaveMenu_Update(void) // 0x8003A230
{
    s32 gameState;

    func_80033548();

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            SysWork_SavegameUpdatePlayer();

            if (Savegame_EventFlagGet(EventFlag_SeenSaveScreen) || g_SavegamePtr->locationId_A8 == SaveLocationId_NextFear || g_MapEventIdx == 0)
            {
                GameFs_SaveLoadBinLoad();

                ScreenFade_Start(true, false, false);
                SysWork_StateStepIncrement(0);
            }
            else if (Gfx_MapMsg_Draw(MapMsgIdx_SaveGame) == MapMsgState_SelectEntry0)
            {
                Savegame_EventFlagSet(EventFlag_SeenSaveScreen);

                GameFs_SaveLoadBinLoad();

                ScreenFade_Start(true, false, false);
                SysWork_StateStepIncrement(0);
            }
            break;
        
        case 1:
            if (D_800A9A0C != 0)
            {
                ScreenFade_Start(true, true, false);

                func_8003943C();

                gameState = g_GameWork.gameState_594;

                g_GameWork.gameState_594 = GameState_SaveScreen;

                g_SysWork.timer_1C = 0;
                g_SysWork.timer_20 = 0;

                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                SysWork_StateSetNext(SysState_Gameplay);

                g_GameWork.gameStateStep_598[0] = gameState;
                g_GameWork.gameStatePrev_590    = gameState;
                g_GameWork.gameStateStep_598[0] = 0;
            }
            break;
    }
}

void SysState_EventCallFunc_Update(void) // 0x8003A3C8
{
    if (g_MapEventParam->flags_8_13 != EventParamUnkState_None)
    {
        Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);
    }

    g_DeltaTime0 = g_DeltaTimeCpy;
    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventIdx]();
}

void SysState_EventSetFlag_Update(void) // 0x8003A460
{
    g_DeltaTime0 = g_DeltaTimeCpy;
    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);
    g_SysWork.sysState_8 = SysState_Gameplay;
}

void SysState_EventPlaySound_Update(void) // 0x8003A4B4
{
    g_DeltaTime0 = g_DeltaTimeCpy;

    SD_Call(((u16)g_MapEventIdx + Sfx_Base) & 0xFFFF);

    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);
    g_SysWork.sysState_8 = SysState_Gameplay;
}

void SysState_GameOver_Update(void) // 0x8003A52C
{
    #define TIP_COUNT 15

    u16  seenTipIdxs[1];
    s32  tipIdx;
    s32  randTipVal;
    u16* temp_a0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            g_MapOverlayHeader.playerControlFreeze_C8();
            g_SysWork.field_28 = Q12(0.0f);

            if (g_GameWork.autosave_90.continueCount_27B < 99)
            {
                g_GameWork.autosave_90.continueCount_27B++;
            }

            MainMenu_SelectedOptionIdxReset();

            // If every game over tip has been seen, reset flag bits.
            if (g_GameWork.config_0.seenGameOverTips_2E[0] == SHRT_MAX)
            {
                g_GameWork.config_0.seenGameOverTips_2E[0] = 0;
            }

            randTipVal = 0;

            seenTipIdxs[0] = g_GameWork.config_0.seenGameOverTips_2E[0];
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) && (tipIdx - 13) >= 2u) ||
                        ( (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) && (tipIdx - 13) <  2u))
                    {
                        randTipVal += 3;
                    }
                    else
                    {
                        randTipVal++;
                    }
                }
            }

            randTipVal = Rng_GenerateInt(0, randTipVal - 1);

            // `randTipVal` seems to go unused after loop, gets checked during loop and can cause early exit,
            // thereby affecting what `tipIdx` will contain.
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) && (tipIdx - 13) >= 2u) ||
                        ( (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) && (tipIdx - 13) <  2u))
                    {
                        if (randTipVal < 3)
                        {
                            break;
                        }

                        randTipVal -= 3;
                    }
                    else
                    {
                        if (randTipVal <= 0)
                        {
                            break;
                        }

                        randTipVal--;
                    }
                }
            }

            // Store current shown `tipIdx`, later `sysStateStep_C == 7` will set it inside `seenGameOverTips_2E`.
            g_SysState_GameOver_TipIdx = tipIdx;

            Fs_QueueStartReadTim(FILE_TIM_TIPS_E01_TIM + tipIdx, FS_BUFFER_1, &g_DeathTipImg);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.5f), false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.5f), false);
            SysWork_StateStepIncrement(0);

        case 3:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw("\aGAME_OVER", DEFAULT_MAP_MESSAGE_LENGTH);
            g_SysWork.field_28++;

            if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                  g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
                g_SysWork.field_28 > Q12(1.0f / 17.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 4:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw("\aGAME_OVER", DEFAULT_MAP_MESSAGE_LENGTH);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            break;

        case 5:
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
            {
                SysWork_StateStepReset();
                break;
            }
            else
            {
                Fs_QueueWaitForEmpty();
                Game_RadioSoundStop();
                SysWork_StateStepIncrement(0);
            }

        case 6:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(2.0f), false);
            g_SysWork.field_28 = Q12(0.0f);
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);
            break;

        case 7:
            g_SysWork.field_28++;
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);

            if (!(g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                   g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
            {
                if (g_SysWork.field_28 <= 480)
                {
                    break;
                }
            }

            // TODO: some inline FlagSet func? couldn't get matching ver, but pretty sure temp_a0 can be removed somehow
            temp_a0 = &g_GameWork.config_0.seenGameOverTips_2E[(g_SysState_GameOver_TipIdx >> 5)];
            *temp_a0 |= (1 << 0) << (g_SysState_GameOver_TipIdx & 0x1F);

            SysWork_StateStepIncrement(0);
            break;

        case 8:
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            break;

        default:
            g_MapOverlayHeader.playerControlUnfreeze_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_WarmBoot();
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 2 || g_GameWork.gameState_594 != GameState_InGame)
    {
        g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    }
}

void GameState_MapEvent_Update(void) // 0x8003AA4C
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_IntervalVBlanks               = 1;
        ScreenFade_Start(true, true, false);
        g_GameWork.gameStateStep_598[0] = 1;
    }

    D_800A9A0C = ScreenFade_IsFinished() && Fs_QueueDoThingWhenEmpty();

    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);

    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventIdx]();

    Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
}

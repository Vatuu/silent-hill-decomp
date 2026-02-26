#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

// ========================================
// COLLISIONS RELATED?
// ========================================

void Chara_PositionSet(s_MapPoint2d* mapPoint) // 0x800371E8
{
    s32 rotY;

    rotY = Q12_ANGLE_FROM_Q8(mapPoint->triggerParam0_4_16);
    Math_SVectorSet(&g_SysWork.playerWork_4C.player_0.rotation_24, Q12_ANGLE(0.0f), rotY, Q12_ANGLE(0.0f));

    g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.position_18.vx = mapPoint->positionX_0;
    g_SysWork.playerWork_4C.player_0.position_18.vz = mapPoint->positionZ_8;

    if (mapPoint->triggerParam1_4_24 >= 2)
    {
        g_SysWork.playerWork_4C.player_0.position_18.vx += Q12_MULT_FLOAT_PRECISE(Math_Sin(rotY), 0.4f);
        g_SysWork.playerWork_4C.player_0.position_18.vz += Q12_MULT_FLOAT_PRECISE(Math_Cos(rotY), 0.4f);
    }

    g_SysWork.loadingScreenIdx_2281 = mapPoint->loadingScreenId_4_9;

    if (mapPoint->mapIdx_4_0 == 24) // TODO: Demagic 24.
    {
        g_SavegamePtr->paperMapIdx_A9 = PaperMapIdx_OtherPlaces;
    }
    else if (mapPoint->mapIdx_4_0 != PaperMapIdx_OtherPlaces)
    {
        g_SavegamePtr->paperMapIdx_A9 = mapPoint->mapIdx_4_0;
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
    s_EventData*  mapEvent;
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
    // If it's set, find its index in `g_ItemTriggerItemIds` and use that to get the corresponding `s_EventData` from `g_ItemTriggerEvents`.
    // After processing, the field is cleared and item trigger IDs are reset.
    // (Multi-item events likely repopulate the trigger IDs below based on whichever events are still active?)
    if (g_SysWork.playerWork_4C.extra_128.lastUsedItem_28 != InventoryItemId_Unequipped)
    {
        for (i = 0; g_SysWork.playerWork_4C.extra_128.lastUsedItem_28 != g_ItemTriggerItemIds[i]; i++);

        g_MapEventData         = g_ItemTriggerEvents[i];
        g_MapEventLastUsedItem = g_SysWork.playerWork_4C.extra_128.lastUsedItem_28;
        g_MapEventSysState     = g_MapEventData->sysState_8_0;
        g_MapEventParam        = g_MapEventData->eventParam_8_5;

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

        if (requiredEventFlag != EventFlag_None && !Savegame_EventFlagGet(requiredEventFlag))
        {
            continue;
        }

        if (disabledEventFlag != EventFlag_None && Savegame_EventFlagGet(disabledEventFlag) &&
            (disabledEventFlag < 867 || mapEvent->activationType_4_4 == TriggerActivationType_Exclusive || mapEvent->sysState_8_0 == SysState_EventSetFlag))
        {
            continue;
        }

        // `TriggerType_None` skips any trigger/activation check and always executes.
        // Maybe used for map-load events, and events that should run every frame?
        // Returns before processing other events until flag checks above disable it.
        if (mapEvent->triggerType_4_0 == TriggerType_None)
        {
            g_MapEventData     = mapEvent;
            g_MapEventSysState = mapEvent->sysState_8_0;
            g_MapEventParam    = mapEvent->eventParam_8_5;
            return;
        }

        // `TriggerActivationType_Button`: Only continue processing event when action button is pressed and `Player_IsBusy` returns false.
        if (mapEvent->activationType_4_4 == TriggerActivationType_Button &&
            (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.action_6) || disableButtonEvents || Player_IsBusy()))
        {
            continue;
        }

        mapPoint = &g_MapOverlayHeader.mapPointsOfInterest_1C[mapEvent->pointOfInterestIdx_5];

        switch (mapEvent->triggerType_4_0)
        {
            case TriggerType_TouchAabb:
                pointPosX    = mapPoint->positionX_0;
                pointPosZ    = mapPoint->positionZ_8;
                pointRadiusX = mapPoint->triggerParam0_4_16 * Q12(0.25f);
                pointRadiusZ = mapPoint->triggerParam1_4_24 * Q12(0.25f);

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
        if (mapEvent->activationType_4_4 == TriggerActivationType_Exclusive && mapEvent == g_MapEventData)
        {
            g_MapEventSysState = SysState_Invalid;
            return;
        }

        // `TriggerActivationType_Item`: When trigger check has passed (player is in the trigger area).
        // Required item ID for event is stored into `g_ItemTriggerItemIds` and event pointer at `g_ItemTriggerEvents`
        // Once player uses an item in the inventory screen, it compares the ID against the ones stored at `g_ItemTriggerItemIds`.
        // If used item ID matches one that event has requested, `extra_128.lastUsedItem_28` gets set to the item ID.
        // At the start of this function, if `extra_128.lastUsedItem_28` is set, it will locate the `s_EventData` for it from `g_ItemTriggerEvents` and run the event.
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
                    (mapEvent->sysState_8_0 != SysState_LoadRoom && mapEvent->eventParam_8_5 > 1))
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
        g_MapEventData     = mapEvent;
        g_MapEventSysState = mapEvent->sysState_8_0;
        g_MapEventParam    = mapEvent->eventParam_8_5;
        return;
    }

    g_MapEventData     = NULL;
    g_MapEventSysState = SysState_Invalid;
    g_MapEventParam    = 0;
}

bool Event_CollideFacingCheck(s_MapPoint2d* mapPoint) // 0x800378D4
{
    q19_12     deltaX;
    q19_12     deltaZ;
    q3_12      rotY;
    q19_12     deltaRotY;
    static s32 D_800A9A20 = 0;
    static s32 D_800A9A24 = 0;
    static s32 D_800A9A28 = 0;

    if (g_TickCount > D_800A9A20)
    {
        rotY       = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
        D_800A9A24 = g_SysWork.playerWork_4C.player_0.position_18.vx - (Math_Sin(rotY) >> 3); // `/ 8`.
        D_800A9A28 = g_SysWork.playerWork_4C.player_0.position_18.vz - (Math_Cos(rotY) >> 3); // `/ 8`.
        D_800A9A20 = g_TickCount;
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
    if (deltaRotY >= Q12_ANGLE(180.0f))
    {
        deltaRotY -= Q12_ANGLE(360.0f);
    }

    if (Q12_ANGLE(30.0f) < ABS(deltaRotY))
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
    scaledCosRotY = -Math_Cos(Q12_ANGLE_FROM_Q8(mapPoint->triggerParam0_4_16)) * mapPoint->triggerParam1_4_24;

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
            scaledSinPlayerRotY = Math_Sin(Q12_ANGLE_FROM_Q8(mapPoint->triggerParam0_4_16)) *
                                  mapPoint->triggerParam1_4_24;

            clampedHalfCosPlayerRotY = halfCosPlayerRotY;

            temp_a0_2 = scaledSinPlayerRotY >> 4; // `/ 16`.
            deltaZ    = mapPoint->positionZ_8 - g_SysWork.playerWork_4C.player_0.position_18.vz;
            temp_v1   = deltaZ - temp_a0_2;
            temp_a2   = deltaZ + temp_a0_2;

            clampedHalfCosPlayerRotY = MAX(halfCosPlayerRotY, Q12(0.0f));

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

    shift8Field_7 = mapPoint->triggerParam1_4_24 << 8;

    deltaX = g_SysWork.playerWork_4C.player_0.position_18.vx - mapPoint->positionX_0;
    if (mapPoint->triggerParam1_4_24 << 9 < ABS(deltaX))
    {
        return false;
    }

    deltaZ = g_SysWork.playerWork_4C.player_0.position_18.vz - mapPoint->positionZ_8;
    scale  = 2;
    if ((shift8Field_7 * scale) < ABS(deltaZ))
    {
        return false;
    }

    // TODO: Odd packed angle conversion method. `Q12_ANGLE_FROM_Q8` doesn't match here.
    angle    = -(mapPoint->triggerParam0_4_16 << 20) >> 16;
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

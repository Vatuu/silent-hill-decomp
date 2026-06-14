#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[24] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M6S00_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M6S00_ShotgunShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 23,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M6S00_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 24,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_402,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800EB11C`
    },
    // [4]
    {
        .requiredEventFlag = EventFlag_402,
        .completeEventFlag = EventFlag_403,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 2,
    },
    // [5]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 3,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP6_S01,
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_410,
        .completeEventFlag = EventFlag_425,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 17,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 6,
        .mapIdx            = MapIdx_MAP6_S01,
    },
    // [7]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 5,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 6,
        .sfxPairIdx_8_19 = SfxPairIdx_9,
        .mapIdx          = MapIdx_MAP6_S01,
    },
    // [8]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 7,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 8,
        .sfxPairIdx_8_19 = SfxPairIdx_15,
        .mapIdx          = MapIdx_MAP6_S02,
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_426,
        .completeEventFlag = EventFlag_411,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 24,
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_424,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 24,
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_426,
        .completeEventFlag = EventFlag_411,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 24,
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_424,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 24,
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_426,
        .completeEventFlag = EventFlag_411,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 24,
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_424,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 24,
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_426,
        .completeEventFlag = EventFlag_411,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 24,
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_424,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 24,
    },
    // [17]
    {
        .requiredEventFlag = EventFlag_411,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 11,
        .mapIdx            = MapIdx_MAP6_S03,
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 26,
    },
    // [19]
    {
        .completeEventFlag = EventFlag_MapMark_ResortTown_EastGarageRightCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 18,
        .sysState          = SysState_EventSetFlag,
    },
    // [20]
    {
        .completeEventFlag = EventFlag_MapMark_ResortTown_EastGarageBotCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 19,
        .sysState          = SysState_EventSetFlag,
    },
    // [21]
    {
        .completeEventFlag = EventFlag_MapMark_ResortTown_SandfordStLeftBigCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 20,
        .sysState          = SysState_EventSetFlag,
    },
    // [22]
    {
        .completeEventFlag = EventFlag_MapMark_ResortTown_SandfordStRightCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 21,
        .sysState          = SysState_EventSetFlag,
    },
    // [23]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

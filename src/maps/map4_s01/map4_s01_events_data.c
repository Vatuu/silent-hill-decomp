#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[25] = {
    // [0]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 10,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
        .mapIdx          = MapIdx_MAP2_S02,
    },
    // [1]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 11,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .mapIdx          = MapIdx_MAP4_S02,
    },
    // [2]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 15,
    },
    // [3]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 13,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 15,
    },
    // [4]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 21,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 15,
    },
    // [5]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 22,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 15,
    },
    // [6]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 15,
    },
    // [7]
    {
        .completeEventFlag = EventFlag_302,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D1FF0`
    },
    // [8]
    {
        .completeEventFlag = EventFlag_302,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D1FF0`
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_302,
        .completeEventFlag = EventFlag_303,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D2408`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_303,
        .completeEventFlag = EventFlag_315,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 18,
    },
    // [11]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 18,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 115,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [12]
    {
        .completeEventFlag = EventFlag_304,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .transitionFlags   = AreaTransitionFlag_SkipFadeIn,
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_304,
        .completeEventFlag = EventFlag_305,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D2F74`
    },
    // [14]
    {
        .completeEventFlag = EventFlag_307,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 94,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [15]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 7,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 94,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [16]
    {
        .completeEventFlag = EventFlag_M4S01_PickupAxe,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `func_800D496C`
    },
    // [17]
    {
        .completeEventFlag = EventFlag_306,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D3420`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [18]
    {
        .requiredEventFlag = EventFlag_306,
        .completeEventFlag = EventFlag_337,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 14,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
        .mapIdx            = MapIdx_MAP4_S04,
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_308,
        .completeEventFlag = EventFlag_309,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800D4410`
    },
    // [20]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 15,
        .sysState       = SysState_EventCallback,
        .eventParam     = 9, // `func_800D4998`
    },
    // [21]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 16,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [22]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 19,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 116,
    },
    // [23]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 20,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 117,
    },
    // [24]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

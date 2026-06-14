#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[13] = {
    // [0]
    {
        .completeEventFlag = EventFlag_476,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 6,
        .flags_8_13        = 2,
    },
    // [1]
    {
        .requiredEventFlag = EventFlag_476,
        .completeEventFlag = EventFlag_471,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D0B64`
    },
    // [2]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 22,
    },
    // [3]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 1,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [4]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 2,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [5]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 3,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .mapIdx          = MapIdx_MAP3_S00,
    },
    // [6]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 4,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 3,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .mapIdx          = MapIdx_MAP3_S00,
    },
    // [7]
    {
        .completeEventFlag = EventFlag_472,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D1604`
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_472,
        .completeEventFlag = EventFlag_473,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 6,
        .mapIdx            = MapIdx_MAP7_S01,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 7,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 47,
    },
    // [10]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 8,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 48,
    },
    // [11]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 9,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 48,
    },
    // [12]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

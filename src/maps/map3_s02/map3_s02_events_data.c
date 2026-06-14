#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[21] = {
    // [0]
    {
        .completeEventFlag = EventFlag_237,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D0608`
    },
    // [1]
    {
        .requiredEventFlag = EventFlag_237,
        .completeEventFlag = EventFlag_238,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 1,
        .mapIdx            = MapIdx_MAP0_S02,
    },
    // [2]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 6,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [3]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 7,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [4]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 8,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [5]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 9,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [6]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [7]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 13,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_233,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .flags_8_13        = 1,
    },
    // [10]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 3,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [11]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 4,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 3,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_234,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .flags_8_13        = 1,
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_236,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 11,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_236,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 5,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [15]
    {
        .completeEventFlag = EventFlag_235,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 11,
        .flags_8_13        = 2,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_235,
        .completeEventFlag = EventFlag_236,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D03FC`
    },
    // [17]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 14,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 15,
        .mapIdx      = MapIdx_MAP3_S03,
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 1,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [19]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 2,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [20]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

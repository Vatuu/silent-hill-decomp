#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[13] = {
    {
        .disabledEventFlag = EventFlag_476,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 6,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag = EventFlag_476,
        .disabledEventFlag = EventFlag_471,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 3, // `func_800D0B64`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 22,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 1,
        .sysState         = SysState_EventCallback,
        .flags_8_13           = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_EventCallback,
        .flags_8_13           = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 3,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .mapIdx   = MapIdx_MAP3_S00,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 3,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .mapIdx   = MapIdx_MAP3_S00,
    },
    {
        .disabledEventFlag  = EventFlag_472,
        .triggerType      = TriggerType_TouchAabb,
        .pointOfInterestIdx = 5,
        .sysState         = SysState_EventCallback,
        .eventParam       = 4, // `func_800D1604`
    },
    {
        .requiredEventFlag = EventFlag_472,
        .disabledEventFlag = EventFlag_473,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 6,
        .mapIdx  = MapIdx_MAP7_S01,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 7,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 47,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 8,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 48,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 9,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 48,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

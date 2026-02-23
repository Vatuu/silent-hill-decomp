#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[13] = {
    {
        .disabledEventFlag_2 = EventFlag_476,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventParam_8_5      = 6,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag_0 = EventFlag_476,
        .disabledEventFlag_2 = EventFlag_471,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 3, // `func_800D0B64`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 22,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 1,
        .sysState_8_0         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 3,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 4,
        .field_8_19           = 12,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP3_S00,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 3,
        .field_8_19           = 12,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP3_S00,
    },
    {
        .disabledEventFlag_2  = EventFlag_472,
        .triggerType_4_0      = TriggerType_TouchAabb,
        .pointOfInterestIdx_5 = 5,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800D1604`
    },
    {
        .requiredEventFlag_0 = EventFlag_472,
        .disabledEventFlag_2 = EventFlag_473,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadOverlay,
        .eventParam_8_5      = 6,
        .mapOverlayIdx_8_25  = MapOverlayId_MAP7_S01,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 7,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 47,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 8,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 48,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 9,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 48,
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

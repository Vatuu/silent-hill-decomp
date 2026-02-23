#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[12] = {
    {
        .requiredEventFlag_0  = EventFlag_416,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 5,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 20,
    },
    {
        .requiredEventFlag_0  = EventFlag_416,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 20,
    },
    {
        .requiredEventFlag_0  = EventFlag_416,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 7,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 20,
    },
    {
        .requiredEventFlag_0  = EventFlag_416,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 1,
        .field_8_19           = 15,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP6_S00,
    },
    {
        .requiredEventFlag_0 = EventFlag_405,
        .disabledEventFlag_2 = EventFlag_409,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadRoom,
        .eventParam_8_5      = 3,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag_0 = EventFlag_405,
        .disabledEventFlag_2 = EventFlag_406,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadRoom,
        .eventParam_8_5      = 3,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag_0 = EventFlag_407,
        .disabledEventFlag_2 = EventFlag_408,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadRoom,
        .eventParam_8_5      = 4,
    },
    {
        .requiredEventFlag_0 = EventFlag_409,
        .disabledEventFlag_2 = EventFlag_410,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 3, // `func_800CF0B8`
    },
    {
        .requiredEventFlag_0 = EventFlag_588,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 6, // `func_800D32D0`
    },
    {
        .disabledEventFlag_2  = EventFlag_460,
        .triggerType_4_0      = TriggerType_TouchAabb,
        .activationType_4_4   = TriggerActivationType_Item,
        .pointOfInterestIdx_5 = 8,
        .requiredItemId_6     = InventoryItemId_ChannelingStone,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800CFC34`
    },
    {
        .requiredEventFlag_0 = EventFlag_469,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 5, // `func_800D0500`
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

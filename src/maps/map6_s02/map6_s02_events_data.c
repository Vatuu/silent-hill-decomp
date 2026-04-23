#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[12] = {
    {
        .requiredEventFlag  = EventFlag_416,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 5,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 20,
    },
    {
        .requiredEventFlag  = EventFlag_416,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 20,
    },
    {
        .requiredEventFlag  = EventFlag_416,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 7,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 20,
    },
    {
        .requiredEventFlag  = EventFlag_416,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_15,
        .mapIdx   = MapIdx_MAP6_S00,
    },
    {
        .requiredEventFlag = EventFlag_405,
        .disabledEventFlag = EventFlag_409,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 3,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag = EventFlag_405,
        .disabledEventFlag = EventFlag_406,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 3,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag = EventFlag_407,
        .disabledEventFlag = EventFlag_408,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 4,
    },
    {
        .requiredEventFlag = EventFlag_409,
        .disabledEventFlag = EventFlag_410,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 3, // `func_800CF0B8`
    },
    {
        .requiredEventFlag = EventFlag_588,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 6, // `func_800D32D0`
    },
    {
        .disabledEventFlag  = EventFlag_460,
        .triggerType      = TriggerType_TouchAabb,
        .activationType   = TriggerActivationType_Item,
        .pointOfInterestIdx = 8,
        .requiredItemId     = InvItemId_ChannelingStone,
        .sysState         = SysState_EventCallback,
        .eventParam       = 4, // `func_800CFC34`
    },
    {
        .requiredEventFlag = EventFlag_469,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 5, // `func_800D0500`
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

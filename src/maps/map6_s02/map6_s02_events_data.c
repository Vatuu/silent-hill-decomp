#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[12] = {
    // [0]
    {
        .requiredEventFlag = EventFlag_416,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_SaveMenu1,
        .eventParam        = 20,
    },
    // [1]
    {
        .requiredEventFlag = EventFlag_416,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_SaveMenu1,
        .eventParam        = 20,
    },
    // [2]
    {
        .requiredEventFlag = EventFlag_416,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_SaveMenu1,
        .eventParam        = 20,
    },
    // [3]
    {
        .requiredEventFlag = EventFlag_416,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 1,
        .sfxPairIdx_8_19   = SfxPairIdx_15,
        .mapIdx            = MapIdx_MAP6_S00,
    },
    // [4]
    {
        .requiredEventFlag = EventFlag_405,
        .completeEventFlag = EventFlag_409,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 3,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_405,
        .completeEventFlag = EventFlag_406,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 3,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_407,
        .completeEventFlag = EventFlag_408,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_409,
        .completeEventFlag = EventFlag_410,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800CF0B8`
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_588,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D32D0`
    },
    // [9]
    {
        .completeEventFlag = EventFlag_460,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 8,
        .requiredItemId    = InvItemId_ChannelingStone,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800CFC34`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_469,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D0500`
    },
    // [11]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

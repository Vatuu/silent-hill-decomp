#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[13] = {
    // [0]
    {
        .requiredEventFlag = EventFlag_587,
        .completeEventFlag = EventFlag_588,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800E9AC8`
    },
    // [1]
    {
        .requiredEventFlag = EventFlag_583,
        .completeEventFlag = EventFlag_589,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 3,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [2]
    {
        .requiredEventFlag = EventFlag_584,
        .completeEventFlag = EventFlag_590,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800E3E84`
    },
    // [3]
    {
        .requiredEventFlag = EventFlag_585,
        .completeEventFlag = EventFlag_590,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 2,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [4]
    {
        .requiredEventFlag = EventFlag_586,
        .completeEventFlag = EventFlag_590,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 1,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_590,
        .completeEventFlag = EventFlag_589,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_589,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `func_800E9C28`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_577,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800E3390`
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_578,
        .completeEventFlag = EventFlag_579,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800E3B6C`
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_579,
        .completeEventFlag = EventFlag_580,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 4,
        .transitionFlags   = AreaTransitionFlag_SkipFadeIn,
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_580,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800E3C48`
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_582,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800E3D18`
    },
    // [12]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

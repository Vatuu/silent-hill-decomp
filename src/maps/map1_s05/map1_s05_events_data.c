#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[4] = {
    // [0]
    {
        .completeEventFlag = EventFlag_130,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D49AC`
    },
    // [1]
    {
        .requiredEventFlag = EventFlag_131,
        .completeEventFlag = EventFlag_132,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D4D1C`
    },
    // [2]
    {
        .requiredEventFlag = EventFlag_132,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 1,
        .flags_8_13        = 4,
        .mapIdx            = MapIdx_MAP1_S06,
    },
    // [3]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

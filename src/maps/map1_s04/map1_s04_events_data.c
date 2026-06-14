#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[3] = {
    // [0]
    {
        .completeEventFlag = EventFlag_59,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 15,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [1]
    {
        .triggerType = TriggerType_Tick,
        .sysState    = SysState_EventCallback,
        .eventParam  = 1, // `func_800CCA2C`
        .transitionFlags  = AreaTransitionFlag_0,
    },
    // [2]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

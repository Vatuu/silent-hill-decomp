#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[2] = {
    // [0]
    {
        .triggerType = TriggerType_Tick,
        .sysState    = SysState_ReadMessage,
        .eventParam  = 15,
        .transitionFlags  = AreaTransitionFlag_0,
    },
    // [1]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

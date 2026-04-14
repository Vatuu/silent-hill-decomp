#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[2] = {
    {
        .triggerType = TriggerType_None,
        .sysState    = SysState_ReadMessage,
        .eventParam  = 15,
        .flags_8_13      = 1,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

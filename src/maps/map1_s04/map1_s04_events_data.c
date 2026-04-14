#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[3] = {
    {
        .disabledEventFlag = EventFlag_59,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 15,
        .flags_8_13          = 1,
    },
    {
        .triggerType = TriggerType_None,
        .sysState    = SysState_EventCallFunc,
        .eventParam  = 1, // `func_800CCA2C`
        .flags_8_13      = 1,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

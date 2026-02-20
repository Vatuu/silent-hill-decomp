#include "bodyprog/bodyprog.h"

s_EventParam D_800CD014[3] = {
    {
        .disabledEventFlag_2 = EventFlag_59,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_ReadMessage,
        .eventData_8_5       = 15,
        .flags_8_13          = 1,
    },
    {
        .triggerType_4_0 = TriggerType_None,
        .sysState_8_0    = SysState_EventCallFunc,
        .eventData_8_5   = 1, // `func_800CCA2C`
        .flags_8_13      = 1,
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

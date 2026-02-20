#include "bodyprog/bodyprog.h"

s_EventParam D_800D5C7C[4] = {
    {
        .disabledEventFlag_2 = EventFlag_130,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 2, // `func_800D49AC`
    },
    {
        .requiredEventFlag_0 = EventFlag_131,
        .disabledEventFlag_2 = EventFlag_132,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 3, // `func_800D4D1C`
    },
    {
        .requiredEventFlag_0 = EventFlag_132,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadOverlay,
        .eventData_8_5       = 1,
        .flags_8_13          = 4,
        .mapOverlayIdx_8_25  = MapOverlayId_MAP1_S06,
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[4] = {
    {
        .disabledEventFlag = EventFlag_130,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 2, // `func_800D49AC`
    },
    {
        .requiredEventFlag = EventFlag_131,
        .disabledEventFlag = EventFlag_132,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 3, // `func_800D4D1C`
    },
    {
        .requiredEventFlag = EventFlag_132,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 1,
        .flags_8_13          = 4,
        .mapIdx  = MapIdx_MAP1_S06,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

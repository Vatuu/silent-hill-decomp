#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[13] = {
    {
        .requiredEventFlag = EventFlag_587,
        .disabledEventFlag = EventFlag_588,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 7, // `func_800E9AC8`
    },
    {
        .requiredEventFlag = EventFlag_583,
        .disabledEventFlag = EventFlag_589,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 3,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag = EventFlag_584,
        .disabledEventFlag = EventFlag_590,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 6, // `func_800E3E84`
    },
    {
        .requiredEventFlag = EventFlag_585,
        .disabledEventFlag = EventFlag_590,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 2,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag = EventFlag_586,
        .disabledEventFlag = EventFlag_590,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 1,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag = EventFlag_590,
        .disabledEventFlag = EventFlag_589,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag = EventFlag_589,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 8, // `func_800E9C28`
    },
    {
        .disabledEventFlag = EventFlag_577,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 2, // `func_800E3390`
    },
    {
        .requiredEventFlag = EventFlag_578,
        .disabledEventFlag = EventFlag_579,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 3, // `func_800E3B6C`
    },
    {
        .requiredEventFlag = EventFlag_579,
        .disabledEventFlag = EventFlag_580,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 4,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag = EventFlag_580,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 4, // `func_800E3C48`
    },
    {
        .requiredEventFlag = EventFlag_582,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 5, // `func_800E3D18`
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

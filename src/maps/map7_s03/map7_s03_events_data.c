#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[13] = {
    {
        .requiredEventFlag_0 = EventFlag_587,
        .disabledEventFlag_2 = EventFlag_588,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 7, // `func_800E9AC8`
    },
    {
        .requiredEventFlag_0 = EventFlag_583,
        .disabledEventFlag_2 = EventFlag_589,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventParam_8_5      = 3,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag_0 = EventFlag_584,
        .disabledEventFlag_2 = EventFlag_590,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 6, // `func_800E3E84`
    },
    {
        .requiredEventFlag_0 = EventFlag_585,
        .disabledEventFlag_2 = EventFlag_590,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventParam_8_5      = 2,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag_0 = EventFlag_586,
        .disabledEventFlag_2 = EventFlag_590,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventParam_8_5      = 1,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag_0 = EventFlag_590,
        .disabledEventFlag_2 = EventFlag_589,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag_0 = EventFlag_589,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 8, // `func_800E9C28`
    },
    {
        .disabledEventFlag_2 = EventFlag_577,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 2, // `func_800E3390`
    },
    {
        .requiredEventFlag_0 = EventFlag_578,
        .disabledEventFlag_2 = EventFlag_579,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 3, // `func_800E3B6C`
    },
    {
        .requiredEventFlag_0 = EventFlag_579,
        .disabledEventFlag_2 = EventFlag_580,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventParam_8_5      = 4,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag_0 = EventFlag_580,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 4, // `func_800E3C48`
    },
    {
        .requiredEventFlag_0 = EventFlag_582,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 5, // `func_800E3D18`
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

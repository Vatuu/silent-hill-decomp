#include "bodyprog/bodyprog.h"

s_EventParam D_800EB94C[19] = {
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 5,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventData_8_5        = 16,
    },
    {
        .disabledEventFlag_2  = EventFlag_440,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 9,
        .sysState_8_0         = SysState_LoadRoom,
        .eventData_8_5        = 7,
        .flags_8_13           = 1,
        .field_8_19           = 23,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP7_S00,
    },
    {
        .disabledEventFlag_2  = EventFlag_440,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_LoadRoom,
        .eventData_8_5        = 7,
        .flags_8_13           = 1,
        .field_8_19           = 23,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP7_S00,
    },
    {
        .requiredEventFlag_0 = EventFlag_451,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadOverlay,
        .eventData_8_5       = 8,
        .mapOverlayIdx_8_25  = MapOverlayId_MAP7_S00,
    },
    {
        .requiredEventFlag_0 = EventFlag_440,
        .disabledEventFlag_2 = EventFlag_441,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 3, // `func_800E1D50`
    },
    {
        .requiredEventFlag_0 = EventFlag_441,
        .disabledEventFlag_2 = EventFlag_442,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventData_8_5       = 8,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag_0 = EventFlag_442,
        .disabledEventFlag_2 = EventFlag_443,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 4, // `func_800E219C`
    },
    {
        .requiredEventFlag_0 = EventFlag_443,
        .disabledEventFlag_2 = EventFlag_467,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 5, // `func_800E2724`
    },
    {
        .requiredEventFlag_0 = EventFlag_444,
        .disabledEventFlag_2 = EventFlag_445,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 6, // `func_800E2950`
    },
    {
        .requiredEventFlag_0 = EventFlag_446,
        .disabledEventFlag_2 = EventFlag_470,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventData_8_5       = 7,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag_0 = EventFlag_470,
        .disabledEventFlag_2 = EventFlag_447,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 7, // `MapEvent_CutsceneCybilDeath`
    },
    {
        .requiredEventFlag_0 = EventFlag_448,
        .disabledEventFlag_2 = EventFlag_449,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 8, // `func_800E3244`
    },
    {
        .requiredEventFlag_0 = EventFlag_450,
        .disabledEventFlag_2 = EventFlag_468,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 10, // `func_800E558C`
    },
    {
        .requiredEventFlag_0 = EventFlag_468,
        .disabledEventFlag_2 = EventFlag_451,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventData_8_5       = 9, // `func_800E3EF4`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 1,
        .sysState_8_0         = SysState_ReadMessage,
        .eventData_8_5        = 15,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_ReadMessage,
        .eventData_8_5        = 15,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 3,
        .sysState_8_0         = SysState_ReadMessage,
        .eventData_8_5        = 15,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_ReadMessage,
        .eventData_8_5        = 15,
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

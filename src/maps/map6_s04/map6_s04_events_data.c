#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[19] = {
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 5,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 16,
    },
    {
        .disabledEventFlag  = EventFlag_440,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 9,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 7,
        .flags_8_13           = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_23,
        .mapIdx   = MapIdx_MAP7_S00,
    },
    {
        .disabledEventFlag  = EventFlag_440,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 7,
        .flags_8_13           = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_23,
        .mapIdx   = MapIdx_MAP7_S00,
    },
    {
        .requiredEventFlag = EventFlag_451,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 8,
        .mapIdx  = MapIdx_MAP7_S00,
    },
    {
        .requiredEventFlag = EventFlag_440,
        .disabledEventFlag = EventFlag_441,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 3, // `func_800E1D50`
    },
    {
        .requiredEventFlag = EventFlag_441,
        .disabledEventFlag = EventFlag_442,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 8,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag = EventFlag_442,
        .disabledEventFlag = EventFlag_443,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 4, // `func_800E219C`
    },
    {
        .requiredEventFlag = EventFlag_443,
        .disabledEventFlag = EventFlag_467,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 5, // `func_800E2724`
    },
    {
        .requiredEventFlag = EventFlag_444,
        .disabledEventFlag = EventFlag_445,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 6, // `func_800E2950`
    },
    {
        .requiredEventFlag = EventFlag_446,
        .disabledEventFlag = EventFlag_470,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 7,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag = EventFlag_470,
        .disabledEventFlag = EventFlag_447,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 7, // `MapEvent_CutsceneCybilDeath`
    },
    {
        .requiredEventFlag = EventFlag_448,
        .disabledEventFlag = EventFlag_449,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 8, // `func_800E3244`
    },
    {
        .requiredEventFlag = EventFlag_450,
        .disabledEventFlag = EventFlag_468,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 10, // `func_800E558C`
    },
    {
        .requiredEventFlag = EventFlag_468,
        .disabledEventFlag = EventFlag_451,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 9, // `func_800E3EF4`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 1,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 15,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 15,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 3,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 15,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 15,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

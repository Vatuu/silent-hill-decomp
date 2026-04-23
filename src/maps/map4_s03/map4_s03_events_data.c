#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[31] = {
    {
        .disabledEventFlag  = EventFlag_M4S03_FirstAidKit,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 27,
        .sysState         = SysState_EventCallback,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M4S03_RifleShells0,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 28,
        .sysState         = SysState_EventCallback,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M4S03_RifleShells1,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 29,
        .sysState         = SysState_EventCallback,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_330,
        .triggerType      = TriggerType_TouchAabb,
        .pointOfInterestIdx = 24,
        .sysState         = SysState_EventCallback,
        .eventParam       = 6, // `func_800D8FC0`
    },
    {
        .requiredEventFlag = EventFlag_330,
        .disabledEventFlag = EventFlag_331,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 11,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag = EventFlag_331,
        .disabledEventFlag = EventFlag_332,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 7, // `func_800D960C`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 22,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 13,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 23,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 13,
    },
    {
        .disabledEventFlag  = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 11,
        .sysState         = SysState_EventCallback,
        .eventParam       = 3, // `func_800D6704`
    },
    {
        .disabledEventFlag  = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 12,
        .sysState         = SysState_EventCallback,
        .eventParam       = 3, // `func_800D6704`
    },
    {
        .disabledEventFlag  = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 13,
        .sysState         = SysState_EventCallback,
        .eventParam       = 3, // `func_800D6704`
    },
    {
        .disabledEventFlag  = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 14,
        .sysState         = SysState_EventCallback,
        .eventParam       = 3, // `func_800D6704`
    },
    {
        .disabledEventFlag  = EventFlag_320,
        .triggerType      = TriggerType_TouchAabb,
        .activationType   = TriggerActivationType_Exclusive,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_EventSetFlag,
    },
    {
        .requiredEventFlag = EventFlag_321,
        .disabledEventFlag = EventFlag_323,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 1,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag = EventFlag_323,
        .disabledEventFlag = EventFlag_324,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 4, // `func_800D6774`
    },
    {
        .requiredEventFlag = EventFlag_335,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 8, // `func_800D9824`
    },
    {
        .requiredEventFlag = EventFlag_326,
        .disabledEventFlag = EventFlag_327,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 5, // `func_800D6F24`
    },
    {
        .triggerType      = TriggerType_TouchAabb,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 3,
    },
    {
        .triggerType      = TriggerType_TouchAabb,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 5,
    },
    {
        .triggerType      = TriggerType_TouchAabb,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 7,
    },
    {
        .triggerType      = TriggerType_TouchAabb,
        .pointOfInterestIdx = 8,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 9,
    },
    {
        .triggerType      = TriggerType_TouchAabb,
        .pointOfInterestIdx = 15,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 16,
        .mapIdx   = MapIdx_MAP4_S02,
    },
    {
        .triggerType      = TriggerType_TouchAabb,
        .pointOfInterestIdx = 17,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 18,
        .mapIdx   = MapIdx_MAP4_S02,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 19,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 20,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 20,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 19,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 21,
        .sysState         = SysState_EventCallback,
        .flags_8_13           = 1,
    },
    {
        .requiredEventFlag  = EventFlag_332,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 25,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 19,
    },
    {
        .requiredEventFlag  = EventFlag_332,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 26,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 19,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 25,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 18,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 26,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 18,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

#include "bodyprog/bodyprog.h"

s_EventData D_800DB654[31] = {
    {
        .disabledEventFlag_2  = EventFlag_M4S03_FirstAidKit,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 27,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M4S03_RifleShells0,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 28,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M4S03_RifleShells1,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 29,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_330,
        .triggerType_4_0      = TriggerType_TouchAabb,
        .pointOfInterestIdx_5 = 24,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 6, // `func_800D8FC0`
    },
    {
        .requiredEventFlag_0 = EventFlag_330,
        .disabledEventFlag_2 = EventFlag_331,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventParam_8_5      = 11,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag_0 = EventFlag_331,
        .disabledEventFlag_2 = EventFlag_332,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 7, // `func_800D960C`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 22,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 13,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 23,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 13,
    },
    {
        .disabledEventFlag_2  = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 11,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 3, // `func_800D6704`
    },
    {
        .disabledEventFlag_2  = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 12,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 3, // `func_800D6704`
    },
    {
        .disabledEventFlag_2  = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 13,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 3, // `func_800D6704`
    },
    {
        .disabledEventFlag_2  = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 14,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 3, // `func_800D6704`
    },
    {
        .disabledEventFlag_2  = EventFlag_320,
        .triggerType_4_0      = TriggerType_TouchAabb,
        .activationType_4_4   = TriggerActivationType_Exclusive,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_EventSetFlag,
    },
    {
        .requiredEventFlag_0 = EventFlag_321,
        .disabledEventFlag_2 = EventFlag_323,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadRoom,
        .eventParam_8_5      = 1,
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag_0 = EventFlag_323,
        .disabledEventFlag_2 = EventFlag_324,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 4, // `func_800D6774`
    },
    {
        .requiredEventFlag_0 = EventFlag_335,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 8, // `func_800D9824`
    },
    {
        .requiredEventFlag_0 = EventFlag_326,
        .disabledEventFlag_2 = EventFlag_327,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 5, // `func_800D6F24`
    },
    {
        .triggerType_4_0      = TriggerType_TouchAabb,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 3,
    },
    {
        .triggerType_4_0      = TriggerType_TouchAabb,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 5,
    },
    {
        .triggerType_4_0      = TriggerType_TouchAabb,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 7,
    },
    {
        .triggerType_4_0      = TriggerType_TouchAabb,
        .pointOfInterestIdx_5 = 8,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 9,
    },
    {
        .triggerType_4_0      = TriggerType_TouchAabb,
        .pointOfInterestIdx_5 = 15,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 16,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP4_S02,
    },
    {
        .triggerType_4_0      = TriggerType_TouchAabb,
        .pointOfInterestIdx_5 = 17,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 18,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP4_S02,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 19,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 20,
        .field_8_19           = 12,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 20,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 19,
        .field_8_19           = 12,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 21,
        .sysState_8_0         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .requiredEventFlag_0  = EventFlag_332,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 25,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 19,
    },
    {
        .requiredEventFlag_0  = EventFlag_332,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 26,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 19,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 25,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 18,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 26,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 18,
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

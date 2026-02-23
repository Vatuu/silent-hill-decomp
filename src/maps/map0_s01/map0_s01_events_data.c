#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[23] = {
    {
        .disabledEventFlag_2  = EventFlag_M0S01_HealthDrink0,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 13,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M0S01_HealthDrink1,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 14,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2 = EventFlag_M0S01_FmvStarted,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventParam_8_5      = 15,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag_0 = EventFlag_M0S01_FmvStarted,
        .disabledEventFlag_2 = EventFlag_M0S01_CafeCutsceneStarted,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 3, // `MapEvent_CafeCutscene`
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag_0  = EventFlag_M0S01_PickedUpKnifeAndMap,
        .disabledEventFlag_2  = EventFlag_M0S01_AirScreamerIntroCutsceneStarted,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 5, // `MapEvent_AirScreamerIntroCutscene`
    },
    {
        .requiredEventFlag_0 = EventFlag_M0S01_AirScreamerDied,
        .disabledEventFlag_2 = EventFlag_M0S01_AirScreamerDeathPlayed,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 11, // `MapEvent_AirScreamerDeath`
    },
    {
        .requiredEventFlag_0  = EventFlag_M0S01_PickupPocketRadio,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 7,
        .field_8_19           = 1,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP2_S00,
    },
    {
        .requiredEventFlag_0  = EventFlag_M0S01_AirScreamerDied,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 71,
        .flags_8_13           = 1,
    },
    {
        .requiredEventFlag_0  = EventFlag_50,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 70,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 67,
        .flags_8_13           = 1,
    },
    {
        .disabledEventFlag_2  = EventFlag_M0S01_PickupKitchenKnife,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 1,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 6, // `MapEvent_KitchenKnifeItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M0S01_PickupFlashlight,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 7, // `MapEvent_FlashlightItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M0S01_PickupMap,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 3,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 8, // `MapEvent_MapItemTake`
    },
    {
        .requiredEventFlag_0  = EventFlag_M0S01_AirScreamerDied,
        .disabledEventFlag_2  = EventFlag_M0S01_PickupPocketRadio,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 9, // `MapEvent_PocketRadioItemTake`
    },
    {
        .requiredEventFlag_0  = EventFlag_50,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 69,
    },
    {
        .requiredEventFlag_0  = EventFlag_49,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 65,
        .flags_8_13           = 1,
    },
    {
        .requiredEventFlag_0  = EventFlag_50,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 75,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_SaveMenu0,
        .eventParam_8_5       = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 8,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 73,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 11,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 73,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 12,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 73,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 9,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 74,
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

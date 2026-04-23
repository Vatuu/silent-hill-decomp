#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[23] = {
    {
        .disabledEventFlag  = EventFlag_M0S01_HealthDrink0,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 13,
        .sysState         = SysState_EventCallback,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M0S01_HealthDrink1,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 14,
        .sysState         = SysState_EventCallback,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag = EventFlag_M0S01_FmvStarted,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 15,
        .flags_8_13          = 2,
    },
    {
        .requiredEventFlag = EventFlag_M0S01_FmvStarted,
        .disabledEventFlag = EventFlag_M0S01_CafeCutsceneStarted,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 3, // `MapEvent_CafeCutscene`
        .flags_8_13          = 1,
    },
    {
        .requiredEventFlag  = EventFlag_M0S01_PickedUpKnifeAndMap,
        .disabledEventFlag  = EventFlag_M0S01_AirScreamerIntroCutsceneStarted,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_EventCallback,
        .eventParam       = 5, // `MapEvent_AirScreamerIntroCutscene`
    },
    {
        .requiredEventFlag = EventFlag_M0S01_AirScreamerDied,
        .disabledEventFlag = EventFlag_M0S01_AirScreamerDeathPlayed,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 11, // `MapEvent_AirScreamerDeath`
    },
    {
        .requiredEventFlag  = EventFlag_M0S01_PickupPocketRadio,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 7,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
        .mapIdx   = MapIdx_MAP2_S00,
    },
    {
        .requiredEventFlag  = EventFlag_M0S01_AirScreamerDied,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 71,
        .flags_8_13           = 1,
    },
    {
        .requiredEventFlag  = EventFlag_50,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 70,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 67,
        .flags_8_13           = 1,
    },
    {
        .disabledEventFlag  = EventFlag_M0S01_PickupKitchenKnife,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 1,
        .sysState         = SysState_EventCallback,
        .eventParam       = 6, // `MapEvent_KitchenKnifeItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M0S01_PickupFlashlight,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_EventCallback,
        .eventParam       = 7, // `MapEvent_FlashlightItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M0S01_PickupMap,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 3,
        .sysState         = SysState_EventCallback,
        .eventParam       = 8, // `MapEvent_MapItemTake`
    },
    {
        .requiredEventFlag  = EventFlag_M0S01_AirScreamerDied,
        .disabledEventFlag  = EventFlag_M0S01_PickupPocketRadio,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_EventCallback,
        .eventParam       = 9, // `MapEvent_PocketRadioItemTake`
    },
    {
        .requiredEventFlag  = EventFlag_50,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 69,
    },
    {
        .requiredEventFlag  = EventFlag_49,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 65,
        .flags_8_13           = 1,
    },
    {
        .requiredEventFlag  = EventFlag_50,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 75,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_SaveMenu0,
        .eventParam       = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 8,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 73,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 11,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 73,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 12,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 73,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 9,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 74,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

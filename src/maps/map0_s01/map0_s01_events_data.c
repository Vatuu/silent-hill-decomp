#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[23] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M0S01_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M0S01_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M0S01_FmvStarted,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 15,
        .transitionFlags        = AreaTransitionFlag_SkipFadeIn,
    },
    // [3]
    {
        .requiredEventFlag = EventFlag_M0S01_FmvStarted,
        .completeEventFlag = EventFlag_M0S01_CafeCutsceneStarted,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CafeCutscene`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [4]
    {
        .requiredEventFlag = EventFlag_M0S01_PickedUpKnifeAndMap,
        .completeEventFlag = EventFlag_M0S01_AirScreamerIntroCutsceneStarted,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_AirScreamerIntroCutscene`
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_M0S01_AirScreamerDied,
        .completeEventFlag = EventFlag_M0S01_AirScreamerDeathPlayed,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `MapEvent_AirScreamerDeath`
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_M0S01_PickupPocketRadio,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP2_S00,
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_M0S01_AirScreamerDied,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 71,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_50,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 70,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 6,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 67,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [10]
    {
        .completeEventFlag = EventFlag_M0S01_PickupKitchenKnife,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 1,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_KitchenKnifeItemTake`
    },
    // [11]
    {
        .completeEventFlag = EventFlag_M0S01_PickupFlashlight,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_FlashlightItemTake`
    },
    // [12]
    {
        .completeEventFlag = EventFlag_M0S01_PickupMap,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `MapEvent_MapItemTake`
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_M0S01_AirScreamerDied,
        .completeEventFlag = EventFlag_M0S01_PickupPocketRadio,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `MapEvent_PocketRadioItemTake`
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_50,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 69,
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_49,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 65,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_50,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 75,
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_SaveMenu0,
        .eventParam     = 1,
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 8,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 73,
    },
    // [19]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 73,
    },
    // [20]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 73,
    },
    // [21]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 9,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 74,
    },
    // [22]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

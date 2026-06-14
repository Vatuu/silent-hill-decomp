#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[31] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M4S03_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M4S03_RifleShells0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M4S03_RifleShells1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_330,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 24,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D8FC0`
    },
    // [4]
    {
        .requiredEventFlag = EventFlag_330,
        .completeEventFlag = EventFlag_331,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 11,
        .transitionFlags        = AreaTransitionFlag_SkipFadeIn,
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_331,
        .completeEventFlag = EventFlag_332,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800D960C`
    },
    // [6]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 22,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 13,
    },
    // [7]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 13,
    },
    // [8]
    {
        .completeEventFlag = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D6704`
    },
    // [9]
    {
        .completeEventFlag = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D6704`
    },
    // [10]
    {
        .completeEventFlag = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D6704`
    },
    // [11]
    {
        .completeEventFlag = EventFlag_M4S03_PickupHuntingRifle,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D6704`
    },
    // [12]
    {
        .completeEventFlag = EventFlag_320,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventSetFlag,
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_321,
        .completeEventFlag = EventFlag_323,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 1,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_323,
        .completeEventFlag = EventFlag_324,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D6774`
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_335,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `func_800D9824`
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_326,
        .completeEventFlag = EventFlag_327,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D6F24`
    },
    // [17]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 2,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 3,
    },
    // [18]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 4,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 5,
    },
    // [19]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 6,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 7,
    },
    // [20]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 8,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 9,
    },
    // [21]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 15,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 16,
        .mapIdx      = MapIdx_MAP4_S02,
    },
    // [22]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 17,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 18,
        .mapIdx      = MapIdx_MAP4_S02,
    },
    // [23]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 19,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 20,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [24]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 20,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 19,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [25]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 21,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [26]
    {
        .requiredEventFlag = EventFlag_332,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 19,
    },
    // [27]
    {
        .requiredEventFlag = EventFlag_332,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 19,
    },
    // [28]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 25,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 18,
    },
    // [29]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 26,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 18,
    },
    // [30]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

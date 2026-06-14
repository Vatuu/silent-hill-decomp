#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[17] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M3S00_FirstAidKit,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_FirstAidKitTake`
    },
    // [1]
    {
        .requiredEventFlag = EventFlag_195,
        .completeEventFlag = EvnetFlag_196,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 13,
        .transitionFlags        = AreaTransitionFlag_SkipFadeIn,
    },
    // [2]
    {
        .requiredEventFlag = EvnetFlag_196,
        .completeEventFlag = EventFlag_197,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D0CF8`
    },
    // [3]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 10,
    },
    // [4]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 4,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 47,
    },
    // [5]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_KitchenArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [6]
    {
        .completeEventFlag = EventFlag_195,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 2,
        .sfxPairIdx_8_19   = SfxPairIdx_20,
        .mapIdx            = MapIdx_MAP6_S01,
    },
    // [7]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 3,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [8]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_CorridorMidBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 1,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [9]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_RightEntranceBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 6,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [10]
    {
        .completeEventFlag = EventFlag_M3S00_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_PaperMapTake`
    },
    // [11]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 15,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 49,
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 8,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 50,
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 9,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 50,
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 51,
    },
    // [15]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 51,
    },
    // [16]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

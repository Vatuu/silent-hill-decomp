#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[29] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M0S02_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M0S02_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M0S02_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 31,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M0S02_HealthDrink2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 32,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M0S02_HandgunBullets,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 33,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_M0S02_HealthDrink3,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [6]
    {
        .completeEventFlag = EventFlag_M0S02_HealthDrink4,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_M0S02_UnlockedChannelingStone,
        .completeEventFlag = EventFlag_M0S02_PickupChannelingStone,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_ChannelingStoneItemTake`
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_M0S02_UnlockedChannelingStone,
        .completeEventFlag = EventFlag_M0S02_PickupChannelingStone,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_ChannelingStoneItemTake`
    },
    // [9]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 24,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 26,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
        .mapIdx          = MapIdx_MAP2_S00,
    },
    // [10]
    {
        .completeEventFlag = EventFlag_M0S02_PickupKatana,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_KatanaItemTake`
    },
    // [11]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 3,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_5,
        .mapIdx          = MapIdx_MAP2_S00,
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 5,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 2,
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 21,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 3,
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 22,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 3,
    },
    // [15]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 6,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 7,
        .sfxPairIdx_8_19 = SfxPairIdx_21,
        .mapIdx          = MapIdx_MAP2_S00,
    },
    // [16]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 13,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 14,
        .sfxPairIdx_8_19 = SfxPairIdx_24,
        .mapIdx          = MapIdx_MAP2_S00,
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 8,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 8,
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 9,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 8,
    },
    // [19]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 8,
    },
    // [20]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 8,
    },
    // [21]
    {
        .requiredEventFlag = EventFlag_M0S02_UnlockedGasolineTank,
        .completeEventFlag = EventFlag_M0S02_PickupGasolineTank,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 23,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `MapEvent_GasolineTankItemTake`
    },
    // [22]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 15,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 16,
    },
    // [23]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 17,
    },
    // [24]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 17,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 17,
    },
    // [25]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 18,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 17,
    },
    // [26]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 19,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 17,
    },
    // [27]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 20,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 18,
    },
    // [28]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

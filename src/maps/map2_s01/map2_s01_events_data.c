#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[28] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M2S01_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800CED44`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_181,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 12,
        .flags_8_13        = 2,
    },
    // [2]
    {
        .requiredEventFlag = EventFlag_181,
        .completeEventFlag = EventFlag_179,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800CED88`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M2S01_PickupFlauros,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 1,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800CF798`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M2S01_PickupDrawbridgeKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 1,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800CF7C4`
    },
    // [5]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 8,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
        .flags_8_13     = 1,
    },
    // [6]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 9,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
        .flags_8_13     = 1,
    },
    // [7]
    {
        .completeEventFlag = EventFlag_MapMark_OldTown_BalkanChurchCheck,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .mapIdx            = MapIdx_MAP2_S00,
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 7,
    },
    // [9]
    {
        .completeEventFlag = EventFlag_180,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `func_800CEC30`
        .flags_8_13        = 1,
    },
    // [10]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 2,
        .sysState       = SysState_EventCallback,
        .eventParam     = 1, // `func_800CEC30`
        .flags_8_13     = 1,
    },
    // [11]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 3,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 4,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 41,
    },
    // [15]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 13,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
    },
    // [16]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 14,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 15,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
    },
    // [19]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 17,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
    },
    // [20]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 18,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
    },
    // [21]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 19,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [22]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 20,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [23]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 21,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [24]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 22,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [25]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [26]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 24,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [27]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

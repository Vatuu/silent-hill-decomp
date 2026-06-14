#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[19] = {
    // [0]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 5,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 16,
    },
    // [1]
    {
        .completeEventFlag = EventFlag_440,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 7,
        .flags_8_13        = 1,
        .sfxPairIdx_8_19   = SfxPairIdx_23,
        .mapIdx            = MapIdx_MAP7_S00,
    },
    // [2]
    {
        .completeEventFlag = EventFlag_440,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 7,
        .flags_8_13        = 1,
        .sfxPairIdx_8_19   = SfxPairIdx_23,
        .mapIdx            = MapIdx_MAP7_S00,
    },
    // [3]
    {
        .requiredEventFlag = EventFlag_451,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 8,
        .mapIdx            = MapIdx_MAP7_S00,
    },
    // [4]
    {
        .requiredEventFlag = EventFlag_440,
        .completeEventFlag = EventFlag_441,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800E1D50`
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_441,
        .completeEventFlag = EventFlag_442,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 8,
        .flags_8_13        = 2,
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_442,
        .completeEventFlag = EventFlag_443,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800E219C`
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_443,
        .completeEventFlag = EventFlag_467,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800E2724`
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_444,
        .completeEventFlag = EventFlag_445,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800E2950`
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_446,
        .completeEventFlag = EventFlag_470,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 7,
        .flags_8_13        = 2,
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_470,
        .completeEventFlag = EventFlag_447,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_CutsceneCybilDeath`
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_448,
        .completeEventFlag = EventFlag_449,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `func_800E3244`
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_450,
        .completeEventFlag = EventFlag_468,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `func_800E558C`
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_468,
        .completeEventFlag = EventFlag_451,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `func_800E3EF4`
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 1,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [15]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 2,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [16]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 3,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 4,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [18]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

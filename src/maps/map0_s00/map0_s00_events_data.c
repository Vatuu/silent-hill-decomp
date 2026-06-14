#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[72] = {
    // [0]
    {
        .completeEventFlag = EventFlag_1,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CutsceneOpening`
        .flags_8_13        = 1,
    },
    // [1]
    {
        .completeEventFlag = EventFlag_2,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 7,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CutsceneCherylFootsteps0`
        .flags_8_13        = 1,
    },
    // [2]
    {
        .completeEventFlag = EventFlag_2,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 8,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `MapEvent_CutsceneCherylFootsteps1`
        .flags_8_13        = 1,
    },
    // [3]
    {
        .completeEventFlag = EventFlag_2,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 9,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CutsceneCherylFootsteps2`
        .flags_8_13        = 1,
    },
    // [4]
    {
        .completeEventFlag = EventFlag_2,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CutsceneCherylFootsteps2`
        .flags_8_13        = 1,
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_2,
        .completeEventFlag = EventFlag_3,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 16,
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_3,
        .completeEventFlag = EventFlag_4,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_CutsceneCherylSpotted`
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_4,
        .completeEventFlag = EventFlag_12,
        .triggerType       = TriggerType_TouchObb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventSetFlag,
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_12,
        .completeEventFlag = EventFlag_13,
        .triggerType       = TriggerType_TouchObb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_CutsceneCherylRedirect0`
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_4,
        .completeEventFlag = EventFlag_12,
        .triggerType       = TriggerType_TouchObb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 12,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `MapEvent_CutsceneCherylRedirect1`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_4,
        .completeEventFlag = EventFlag_12,
        .triggerType       = TriggerType_TouchObb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `MapEvent_CutsceneCherylRedirect2`
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_4,
        .completeEventFlag = EventFlag_12,
        .triggerType       = TriggerType_TouchObb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `MapEvent_CutsceneCherylRedirect3`
    },
    // [12]
    {
        .completeEventFlag = EventFlag_7,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 15,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `MapEvent_CutsceneCherylIntoTheAlley`
    },
    // [13]
    {
        .completeEventFlag = EventFlag_7,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 16,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `MapEvent_CutsceneCherylIntoTheAlley`
    },
    // [14]
    {
        .completeEventFlag = EventFlag_7,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 17,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `func_800DB26C`
    },
    // [15]
    {
        .completeEventFlag = EventFlag_13,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 19,
        .sfxPairIdx_8_19   = SfxPairIdx_4,
    },
    // [16]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 19,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 24,
        .flags_8_13     = 1,
    },
    // [17]
    {
        .completeEventFlag = EventFlag_14,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 20,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_4,
    },
    // [18]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 22,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 21,
        .sfxPairIdx_8_19 = SfxPairIdx_4,
    },
    // [19]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 21,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 22,
        .sfxPairIdx_8_19 = SfxPairIdx_4,
    },
    // [20]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [21]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 24,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [22]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 25,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [23]
    {
        .requiredEventFlag = EventFlag_15,
        .completeEventFlag = EventFlag_17,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `MapEven_CutsceneAlleyGetsDarker`
    },
    // [24]
    {
        .requiredEventFlag = EventFlag_14,
        .completeEventFlag = EventFlag_19,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 27,
        .sysState          = SysState_EventCallback,
        .eventParam        = 14, // `func_800DB870`
        .flags_8_13        = 1,
    },
    // [25]
    {
        .requiredEventFlag = EventFlag_19,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 69,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 26,
        .flags_8_13        = 1,
    },
    // [26]
    {
        .requiredEventFlag = EventFlag_19,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 70,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 26,
        .flags_8_13        = 1,
    },
    // [27]
    {
        .requiredEventFlag = EventFlag_16,
        .completeEventFlag = EventFlag_24,
        .triggerType       = TriggerType_TouchObb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 26,
        .sysState          = SysState_EventCallback,
        .eventParam        = 15, // `MapEvent_CutsceneAlleyNightmare`
        .flags_8_13        = 1,
    },
    // [28]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 28,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 29,
        .flags_8_13     = 1,
    },
    // [29]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 29,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 29,
        .flags_8_13     = 1,
    },
    // [30]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 30,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 29,
        .flags_8_13     = 1,
    },
    // [31]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 31,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 29,
        .flags_8_13     = 1,
    },
    // [32]
    {
        .requiredEventFlag = EventFlag_25,
        .completeEventFlag = EventFlag_26,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 16, // `func_800DBE00`
        .flags_8_13        = 1,
    },
    // [33]
    {
        .requiredEventFlag = EventFlag_26,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 4,
        .mapIdx            = MapIdx_MAP0_S01,
    },
    // [34]
    {
        .completeEventFlag = EventFlag_20,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 32,
        .sysState          = SysState_EventSetFlag,
    },
    // [35]
    {
        .completeEventFlag = EventFlag_21,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 33,
        .sysState          = SysState_EventSetFlag,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_22,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 34,
        .sysState          = SysState_EventSetFlag,
    },
    // [37]
    {
        .completeEventFlag = EventFlag_23,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 35,
        .sysState          = SysState_EventSetFlag,
    },
    // [38]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 36,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 31,
    },
    // [39]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 37,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 31,
    },
    // [40]
    {
        .requiredEventFlag = EventFlag_24,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 32,
    },
    // [41]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 39,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
        .flags_8_13     = 1,
    },
    // [42]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 40,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
        .flags_8_13     = 1,
    },
    // [43]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 41,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
        .flags_8_13     = 1,
    },
    // [44]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 42,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [45]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 43,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [46]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 44,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [47]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 45,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [48]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 46,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [49]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 47,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [50]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 48,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [51]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 49,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [52]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 50,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [53]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 51,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [54]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 52,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
        .flags_8_13     = 1,
    },
    // [55]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 53,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
        .flags_8_13     = 1,
    },
    // [56]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 54,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
        .flags_8_13     = 1,
    },
    // [57]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 55,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [58]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 56,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [59]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 57,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [60]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 58,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [61]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 59,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [62]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 60,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [63]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 61,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [64]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 62,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [65]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 63,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [66]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 64,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [67]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 65,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [68]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 66,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [69]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 67,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [70]
    {
        .completeEventFlag = EventFlag_MapMark_OldTown_BachmanRdTopCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 68,
        .sysState          = SysState_EventSetFlag,
    },
    // [71]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

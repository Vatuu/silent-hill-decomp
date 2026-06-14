#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[21] = {
    // [0]
    {
        .requiredEventFlag = EventFlag_337,
        .completeEventFlag = EventFlag_338,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D1910`
    },
    // [1]
    {
        .requiredEventFlag = EventFlag_338,
        .completeEventFlag = EventFlag_308,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 11,
        .mapIdx            = MapIdx_MAP4_S01,
    },
    // [2]
    {
        .requiredEventFlag = EventFlag_339,
        .completeEventFlag = EventFlag_340,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D23E4`
    },
    // [3]
    {
        .requiredEventFlag = EventFlag_340,
        .completeEventFlag = EventFlag_341,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 1,
    },
    // [4]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 10,
    },
    // [5]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_WomensBathroomBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [6]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_WomensBathroomBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [7]
    {
        .completeEventFlag = EventFlag_1472,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [8]
    {
        .completeEventFlag = EventFlag_339,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 1,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 6,
        .sfxPairIdx_8_19   = SfxPairIdx_20,
    },
    // [9]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 6,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [10]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 1,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 6,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_340,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 9,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .mapIdx            = MapIdx_MAP4_S05,
    },
    // [12]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 2,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP4_S02,
    },
    // [13]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_StairsArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [14]
    {
        .completeEventFlag = EventFlag_1476,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [15]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 80,
    },
    // [16]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 13,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 80,
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 14,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 80,
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 15,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 80,
    },
    // [19]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 81,
    },
    // [20]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

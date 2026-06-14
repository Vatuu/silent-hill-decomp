#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[53] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M3S04_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 52,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D2470`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M3S04_HealthDrink1,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 53,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D2470`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M3S04_HealthDrink2,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 54,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D2470`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M3S04_HealthDrink3,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D2470`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M3S04_HandgunBullets,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 56,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D2470`
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_292,
        .completeEventFlag = EventFlag_293,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 10,
        .flags_8_13        = 2,
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_293,
        .completeEventFlag = EventFlag_294,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D2668`
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_294,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 39,
        .flags_8_13        = 4,
        .mapIdx            = MapIdx_MAP3_S06,
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 38,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 12,
    },
    // [9]
    {
        .completeEventFlag = EventFlag_M3S04_PickupPlateOfQueen,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D2E58`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_258,
        .completeEventFlag = EventFlag_292,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .mapIdx            = MapIdx_MAP5_S02,
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_M3S05_PickupExaminationRoomKey,
        .completeEventFlag = EventFlag_258,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D250C`
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_M3S05_PickupExaminationRoomKey,
        .completeEventFlag = EventFlag_258,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 5,
        .requiredItemId    = InvItemId_ExaminationRoomKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D250C`
    },
    // [13]
    {
        .completeEventFlag = EventFlag_1474,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `func_800D21C4`
        .flags_8_13        = 1,
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 40,
        .sysState       = SysState_EventCallback,
        .eventParam     = 6, // `sharedFunc_800D15F0_3_s01`
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_216,
        .completeEventFlag = EventFlag_220,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 43,
        .mapIdx            = MapIdx_MAP3_S05,
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_217,
        .completeEventFlag = EventFlag_221,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 17,
    },
    // [17]
    {
        .requiredEventFlag = EventFlag_218,
        .completeEventFlag = EventFlag_222,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 41,
        .mapIdx            = MapIdx_MAP3_S03,
    },
    // [18]
    {
        .requiredEventFlag = EventFlag_219,
        .completeEventFlag = EventFlag_223,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 42,
        .mapIdx            = MapIdx_MAP3_S03,
    },
    // [19]
    {
        .completeEventFlag = EventFlag_213,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 36,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [20]
    {
        .completeEventFlag = EventFlag_213,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 36,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [21]
    {
        .completeEventFlag = EventFlag_1477,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 26,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [22]
    {
        .completeEventFlag = EventFlag_1477,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 6,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [23]
    {
        .completeEventFlag = EventFlag_1479,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 24,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [24]
    {
        .completeEventFlag = EventFlag_1479,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 24,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [25]
    {
        .completeEventFlag = EventFlag_1481,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 23,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [26]
    {
        .completeEventFlag = EventFlag_1481,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 23,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_1482,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [28]
    {
        .completeEventFlag = EventFlag_1485,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 21,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [29]
    {
        .completeEventFlag = EventFlag_1485,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 12,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [30]
    {
        .completeEventFlag = EventFlag_1487,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 20,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [31]
    {
        .completeEventFlag = EventFlag_1487,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 20,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 13,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [32]
    {
        .completeEventFlag = EventFlag_1489,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 19,
        .sfxPairIdx_8_19   = SfxPairIdx_14,
        .field_8_24        = 1,
    },
    // [33]
    {
        .completeEventFlag = EventFlag_1489,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 19,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_14,
    },
    // [34]
    {
        .completeEventFlag = EventFlag_1491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 30,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [35]
    {
        .completeEventFlag = EventFlag_1491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 25,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospitalBF_StairsArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [37]
    {
        .completeEventFlag = EventFlag_1494,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 32,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [38]
    {
        .completeEventFlag = EventFlag_1496,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 31,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [39]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_StairsArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 33,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [40]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 34,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 35,
        .mapIdx      = MapIdx_MAP3_S03,
    },
    // [41]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 15,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 16,
        .mapIdx      = MapIdx_MAP3_S05,
    },
    // [42]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 2,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [43]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 3,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [44]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 44,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 49,
    },
    // [45]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 46,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 50,
    },
    // [46]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 45,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 50,
    },
    // [47]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 47,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 51,
    },
    // [48]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 48,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 53,
    },
    // [49]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 49,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 52,
    },
    // [50]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 50,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 50,
    },
    // [51]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 51,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 50,
    },
    // [52]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

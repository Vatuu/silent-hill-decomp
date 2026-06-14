#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[111] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M3S01_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 101,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D14BC`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M3S00_FirstAidKit,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 100,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D1500`
    },
    // [2]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 67,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 10,
    },
    // [3]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 75,
        .sysState       = SysState_EventCallback,
        .eventParam     = 13, // `func_800D2A88`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M3S01_PickupUnknownLiquid,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 57,
        .requiredItemId    = InvItemId_PlasticBottle,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_UseBottleOnLiquid`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_M3S01_PickupUnknownLiquid,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 58,
        .requiredItemId    = InvItemId_PlasticBottle,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_UseBottleOnLiquid`
    },
    // [6]
    {
        .completeEventFlag = EventFlag_M3S01_PickupUnknownLiquid,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 59,
        .requiredItemId    = InvItemId_PlasticBottle,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_UseBottleOnLiquid`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_M3S01_PickupUnknownLiquid,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 60,
        .requiredItemId    = InvItemId_PlasticBottle,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_UseBottleOnLiquid`
    },
    // [8]
    {
        .completeEventFlag = EventFlag_M3S01_PickupUnknownLiquid,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 57,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_UnknownLiquidInteract`
    },
    // [9]
    {
        .completeEventFlag = EventFlag_M3S01_PickupUnknownLiquid,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 58,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_UnknownLiquidInteract`
    },
    // [10]
    {
        .completeEventFlag = EventFlag_M3S01_PickupUnknownLiquid,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 59,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_UnknownLiquidInteract`
    },
    // [11]
    {
        .completeEventFlag = EventFlag_M3S01_PickupUnknownLiquid,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 60,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_UnknownLiquidInteract`
    },
    // [12]
    {
        .triggerType     = TriggerType_TouchAabb,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 57,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 20,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [13]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 58,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 20,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [14]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 59,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 20,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [15]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 60,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 20,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [16]
    {
        .completeEventFlag = EventFlag_M3S01_PickupPlasticBottle,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 62,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `MapEvent_PlasticBottleTake`
    },
    // [17]
    {
        .completeEventFlag = EventFlag_M3S01_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 63,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `MapEvent_PaperMapTake1`
    },
    // [18]
    {
        .completeEventFlag = EventFlag_M3S01_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 64,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `MapEvent_PaperMapTake1`
    },
    // [19]
    {
        .completeEventFlag = EventFlag_M3S01_PickupBasementKey,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 65,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800D279C`
    },
    // [20]
    {
        .completeEventFlag = EventFlag_M3S01_GeneratorOn,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_Generator0`
    },
    // [21]
    {
        .requiredEventFlag = EventFlag_M3S01_GeneratorOn,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_EventCallback,
        .eventParam        = 14, // `func_800D29A4`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [22]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 55,
        .sysState       = SysState_EventCallback,
        .eventParam     = 5, // `sharedFunc_800D15F0_3_s01`
    },
    // [23]
    {
        .requiredEventFlag = EventFlag_M3S01_GeneratorOn,
        .completeEventFlag = EventFlag_212,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [24]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 37,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [25]
    {
        .requiredEventFlag = EventFlag_M3S01_GeneratorOn,
        .completeEventFlag = EventFlag_212,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 36,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [26]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 36,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [27]
    {
        .requiredEventFlag = EventFlag_216,
        .completeEventFlag = EventFlag_220,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 36,
    },
    // [28]
    {
        .requiredEventFlag = EventFlag_M3S01_GeneratorOn,
        .completeEventFlag = EventFlag_213,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [29]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [30]
    {
        .requiredEventFlag = EventFlag_M3S01_GeneratorOn,
        .completeEventFlag = EventFlag_213,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [31]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 15,
    },
    // [32]
    {
        .requiredEventFlag = EventFlag_217,
        .completeEventFlag = EventFlag_221,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 11,
    },
    // [33]
    {
        .completeEventFlag = EventFlag_214,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [34]
    {
        .completeEventFlag = EventFlag_214,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [35]
    {
        .requiredEventFlag = EventFlag_218,
        .completeEventFlag = EventFlag_222,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 38,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital2F_OperatingPrepRoomArrow,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [37]
    {
        .completeEventFlag = EventFlag_215,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [38]
    {
        .completeEventFlag = EventFlag_215,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [39]
    {
        .requiredEventFlag = EventFlag_219,
        .completeEventFlag = EventFlag_223,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 41,
    },
    // [40]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital2F_CorridorMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [41]
    {
        .requiredEventFlag = EventFlag_224,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 56,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
        .mapIdx            = MapIdx_MAP3_S02,
    },
    // [42]
    {
        .requiredEventFlag = EventFlag_M3S01_PickupBasementKey,
        .completeEventFlag = EventFlag_M3S01_BasementDoorOpen,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D1524`
    },
    // [43]
    {
        .requiredEventFlag = EventFlag_M3S01_PickupBasementKey,
        .completeEventFlag = EventFlag_M3S01_BasementDoorOpen,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 10,
        .requiredItemId    = InvItemId_BasementKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D1524`
    },
    // [44]
    {
        .requiredEventFlag = EventFlag_MapMark_585,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 15,
        .sfxPairIdx_8_19   = SfxPairIdx_19,
    },
    // [45]
    {
        .requiredEventFlag = EventFlag_MapMark_585,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 10,
        .sfxPairIdx_8_19   = SfxPairIdx_19,
        .field_8_24        = 1,
    },
    // [46]
    {
        .completeEventFlag = EventFlag_1448,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [47]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 31,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 29,
    },
    // [48]
    {
        .completeEventFlag = EventFlag_M3S00_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 68,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `MapEvent_PaperMapTake0`
    },
    // [49]
    {
        .completeEventFlag = EventFlag_1435,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 25,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [50]
    {
        .completeEventFlag = EventFlag_1435,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 3,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [51]
    {
        .completeEventFlag = EventFlag_1452,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [52]
    {
        .completeEventFlag = EventFlag_1436,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [53]
    {
        .completeEventFlag = EventFlag_1438,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [54]
    {
        .completeEventFlag = EventFlag_1443,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 20,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [55]
    {
        .completeEventFlag = EventFlag_1443,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 20,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [56]
    {
        .completeEventFlag = EventFlag_1445,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 19,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [57]
    {
        .completeEventFlag = EventFlag_1445,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 19,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [58]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_CorridorLeftBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 18,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [59]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_CorridorLeftBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 9,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [60]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_ExaminationMedicineArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [61]
    {
        .completeEventFlag = EventFlag_1441,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [62]
    {
        .completeEventFlag = EventFlag_1441,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 21,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [63]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_RightEntranceBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 27,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [64]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_RightEntranceBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 26,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [65]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_CorridorMidBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 34,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [66]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_CorridorMidBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 28,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [67]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 32,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 35,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [68]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 32,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [69]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 30,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [70]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 29,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [71]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_KitchenArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 33,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [72]
    {
        .completeEventFlag = EventFlag_1513,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 49,
        .sfxPairIdx_8_19   = SfxPairIdx_19,
        .field_8_24        = 1,
    },
    // [73]
    {
        .completeEventFlag = EventFlag_1513,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 49,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 44,
        .sfxPairIdx_8_19   = SfxPairIdx_19,
    },
    // [74]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospitalBF_MorgueArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 47,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [75]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospitalBF_StoreroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 48,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [76]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospitalBF_BoilerRoomBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 50,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 53,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [77]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospitalBF_BoilerRoomBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 53,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 50,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [78]
    {
        .completeEventFlag = EventFlag_1520,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [79]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 16,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 46,
    },
    // [80]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 45,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 17,
    },
    // [81]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 69,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 30,
    },
    // [82]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 70,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 31,
    },
    // [83]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 71,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 32,
    },
    // [84]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 72,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [85]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 73,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
    },
    // [86]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 76,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 38,
    },
    // [87]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 77,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [88]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 78,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
    },
    // [89]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 79,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [90]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 80,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [91]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 81,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
    },
    // [92]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 82,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [93]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 83,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [94]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 84,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [95]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 85,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [96]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 86,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [97]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 87,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [98]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 88,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [99]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 89,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [100]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 90,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [101]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 91,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [102]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 92,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [103]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 93,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [104]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 94,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [105]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 95,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [106]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 96,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
    },
    // [107]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 97,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [108]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 98,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [109]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 99,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [110]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

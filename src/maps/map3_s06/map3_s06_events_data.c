#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[50] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M3S00_FirstAidKit,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 59,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 2,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 10,
    },
    // [2]
    {
        .requiredEventFlag = EventFlag_297,
        .completeEventFlag = EventFlag_M3S06_PickupAntiqueShopKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D17D8`
    },
    // [3]
    {
        .requiredEventFlag = EventFlag_297,
        .completeEventFlag = EventFlag_M3S06_PickupAntiqueShopKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D17D8`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_295,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D0C14`
    },
    // [5]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 41,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D0B10`
    },
    // [6]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
    },
    // [7]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
    },
    // [8]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 31,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP2_S02,
    },
    // [9]
    {
        .completeEventFlag = EventFlag_M3S00_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 36,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_PaperMapTake`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_317,
        .completeEventFlag = EventFlag_MapMark_FogCentralTown_AntiqueWholeSign,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 38,
    },
    // [11]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 39,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 40,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 40,
    },
    // [13]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_ExaminationRoomLeftArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [14]
    {
        .completeEventFlag = EventFlag_1435,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 25,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [15]
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
    // [16]
    {
        .completeEventFlag = EventFlag_1452,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [17]
    {
        .completeEventFlag = EventFlag_1436,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [18]
    {
        .completeEventFlag = EventFlag_1438,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [19]
    {
        .completeEventFlag = EventFlag_1442,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [20]
    {
        .completeEventFlag = EventFlag_1444,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [21]
    {
        .completeEventFlag = EventFlag_1446,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [22]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital1F_ExaminationMedicineArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [23]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_RightEntranceBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 27,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [24]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_RightEntranceBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 26,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [25]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_CorridorMidBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 34,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [26]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_CorridorMidBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 28,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 32,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 35,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [28]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 32,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [29]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 30,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [30]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_StairsLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 29,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP3_S01,
    },
    // [31]
    {
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_KitchenArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 33,
        .sysState          = SysState_EventCallback,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [32]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 42,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [33]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 43,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [34]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 44,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [35]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 45,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [36]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 46,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [37]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 47,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 43,
    },
    // [38]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 48,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 44,
    },
    // [39]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 49,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 44,
    },
    // [40]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 50,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [41]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 51,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [42]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 52,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [43]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 53,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 46,
    },
    // [44]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 54,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 44,
    },
    // [45]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 55,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [46]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 56,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [47]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 57,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [48]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 58,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [49]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

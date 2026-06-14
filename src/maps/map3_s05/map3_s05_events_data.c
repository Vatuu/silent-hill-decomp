#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[104] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M3S05_Ampoule,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 96,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D5934`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M3S05_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 97,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D5934`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M3S05_HandgunBullets,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 98,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D5934`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M3S05_ShotgunShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 99,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D5934`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_212,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 36,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [5]
    {
        .completeEventFlag = EventFlag_212,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 36,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [6]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 92,
        .sysState       = SysState_EventCallback,
        .eventParam     = 16, // `sharedFunc_800D15F0_3_s01`
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_216,
        .completeEventFlag = EventFlag_220,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 2,
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_217,
        .completeEventFlag = EventFlag_221,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 95,
        .mapIdx            = MapIdx_MAP3_S04,
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_218,
        .completeEventFlag = EventFlag_222,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 93,
        .mapIdx            = MapIdx_MAP3_S03,
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_219,
        .completeEventFlag = EventFlag_223,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 94,
        .mapIdx            = MapIdx_MAP3_S03,
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_284,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 19,
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_M3S05_AlcoholPouredOnVines,
        .completeEventFlag = EventFlag_284,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 18,
        .requiredItemId    = InvItemId_Lighter,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `func_800D64E0`
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_M3S05_AlcoholPouredOnVines,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800D63C4`
    },
    // [14]
    {
        .completeEventFlag = EventFlag_M3S05_AlcoholPouredOnVines,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 18,
        .requiredItemId    = InvItemId_DisinfectingAlcohol,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D5FC4`
    },
    // [15]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Item,
        .mapPointIdx    = 18,
        .requiredItemId = InvItemId_Lighter,
        .sysState       = SysState_EventCallback,
        .eventParam     = 5, // `func_800D5C98`
    },
    // [16]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 18,
        .sysState       = SysState_EventCallback,
        .eventParam     = 4, // `func_800D5A98`
    },
    // [17]
    {
        .completeEventFlag = EventFlag_M3S05_CabinetPushed,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800D72AC`
    },
    // [18]
    {
        .requiredEventFlag = EventFlag_259,
        .completeEventFlag = EventFlag_260,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `func_800D6D1C`
    },
    // [19]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 39,
        .sysState       = SysState_EventCallback,
        .eventParam     = 10, // `func_800D6BE0`
    },
    // [20]
    {
        .completeEventFlag = EventFlag_M3S05_PickupExaminationRoomKey,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800D6CF0`
    },
    // [21]
    {
        .completeEventFlag = EventFlag_M3S05_PickupVideoTape,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `func_800D6BB4`
    },
    // [22]
    {
        .completeEventFlag = EventFlag_M3S05_PickupHammer,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_EventCallback,
        .eventParam        = 14, // `func_800D7280`
    },
    // [23]
    {
        .completeEventFlag = EventFlag_1533,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_14,
        .field_8_24        = 1,
    },
    // [24]
    {
        .completeEventFlag = EventFlag_1533,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .sfxPairIdx_8_19   = SfxPairIdx_14,
    },
    // [25]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 5,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 6,
        .mapIdx      = MapIdx_MAP3_S04,
    },
    // [26]
    {
        .completeEventFlag = EventFlag_1539,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 12,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_1539,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [28]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 42,
        .sysState       = SysState_EventCallback,
        .eventParam     = 15, // `func_800D719C`
        .flags_8_13     = 1,
    },
    // [29]
    {
        .completeEventFlag = EventFlag_1540,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [30]
    {
        .completeEventFlag = EventFlag_1535,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [31]
    {
        .completeEventFlag = EventFlag_1535,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 10,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [32]
    {
        .requiredEventFlag = EventFlag_M3S03_PickupBasementStoreroomKey,
        .completeEventFlag = EventFlag_256,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D59D4`
    },
    // [33]
    {
        .requiredEventFlag = EventFlag_M3S03_PickupBasementStoreroomKey,
        .completeEventFlag = EventFlag_256,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 11,
        .requiredItemId    = InvItemId_BasementStoreroomKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D59D4`
    },
    // [34]
    {
        .requiredEventFlag = EventFlag_MapMark_FogHospital3F_NearElevatorBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 15,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [35]
    {
        .requiredEventFlag = EventFlag_MapMark_FogHospital3F_NearElevatorBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 11,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_1536,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .flags_8_13        = 1,
    },
    // [37]
    {
        .requiredEventFlag = EventFlag_M3S05_CabinetPushed,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 17,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [38]
    {
        .requiredEventFlag = EventFlag_M3S05_CabinetPushed,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 16,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [39]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 20,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 18,
    },
    // [40]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 22,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 23,
        .sfxPairIdx_8_19 = SfxPairIdx_14,
        .field_8_24      = 1,
    },
    // [41]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 23,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 22,
        .sfxPairIdx_8_19 = SfxPairIdx_14,
    },
    // [42]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 25,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [43]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 24,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 26,
        .sfxPairIdx_8_19 = SfxPairIdx_14,
        .field_8_24      = 1,
    },
    // [44]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 26,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 24,
        .sfxPairIdx_8_19 = SfxPairIdx_14,
        .field_8_24      = 1,
    },
    // [45]
    {
        .completeEventFlag = EventFlag_259,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 34,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [46]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 29,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 34,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [47]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 34,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 29,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [48]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 27,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 33,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [49]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 33,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 27,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [50]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 28,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [51]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 30,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 35,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [52]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 35,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 30,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [53]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 31,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [54]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 32,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [55]
    {
        .requiredEventFlag = EventFlag_288,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 30,
    },
    // [56]
    {
        .requiredEventFlag = EventFlag_288,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 30,
    },
    // [57]
    {
        .requiredEventFlag = EventFlag_288,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 30,
    },
    // [58]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 47,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 32,
    },
    // [59]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 48,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 32,
    },
    // [60]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 49,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 32,
    },
    // [61]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 50,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 32,
    },
    // [62]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 51,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [63]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 52,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [64]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 53,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [65]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 54,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [66]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 55,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [67]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 56,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [68]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 57,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [69]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 58,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [70]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 59,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [71]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 60,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [72]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 61,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [73]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 62,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [74]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 63,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [75]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 64,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [76]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 65,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [77]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 66,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [78]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 67,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [79]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 68,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 33,
    },
    // [80]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 69,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [81]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 70,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [82]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 71,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [83]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 72,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [84]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 73,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [85]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 74,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [86]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 75,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [87]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 76,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
    },
    // [88]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 77,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [89]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 78,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [90]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 79,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [91]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 80,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [92]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 81,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [93]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 82,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [94]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 83,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [95]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 84,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [96]
    {
        .requiredEventFlag = EventFlag_288,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 85,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 39,
    },
    // [97]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 86,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 38,
    },
    // [98]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 87,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 38,
    },
    // [99]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 88,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [100]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 89,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [101]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 90,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [102]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 91,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 38,
    },
    // [103]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

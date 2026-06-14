#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[136] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M3S03_FirstAidKit0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 126,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D151C`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M3S03_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 127,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D151C`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M3S03_HandgunBullets,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 128,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D151C`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M3S03_FirstAidKit1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 129,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D151C`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M3S03_ShotgunShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 130,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D151C`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_214,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 73,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [6]
    {
        .completeEventFlag = EventFlag_214,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 73,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [7]
    {
        .completeEventFlag = EventFlag_215,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 1,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 73,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [8]
    {
        .completeEventFlag = EventFlag_215,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 73,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 125,
        .sysState       = SysState_EventCallback,
        .eventParam     = 20, // `sharedFunc_800D15F0_3_s01`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_216,
        .completeEventFlag = EventFlag_220,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 124,
        .mapIdx            = MapIdx_MAP3_S05,
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_217,
        .completeEventFlag = EventFlag_221,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 123,
        .mapIdx            = MapIdx_MAP3_S04,
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_218,
        .completeEventFlag = EventFlag_222,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 38,
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_219,
        .completeEventFlag = EventFlag_223,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 1,
    },
    // [14]
    {
        .completeEventFlag = EventFlag_250,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 87,
        .requiredItemId    = InvItemId_BloodPack,
        .sysState          = SysState_EventCallback,
        .eventParam        = 17, // `func_800D2CDC`
    },
    // [15]
    {
        .completeEventFlag = EventFlag_M3S03_PickupPlateOfHatter,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 78,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D1774`
    },
    // [16]
    {
        .completeEventFlag = EventFlag_M3S03_PickupPlateOfCat,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 77,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D17A0`
    },
    // [17]
    {
        .completeEventFlag = EventFlag_M3S03_PickupPlateOfTurtle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 76,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D17CC`
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 92,
        .sysState       = SysState_EventCallback,
        .eventParam     = 19, // `func_800D3128`
        .flags_8_13     = 1,
    },
    // [19]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 79,
        .sysState       = SysState_EventCallback,
        .eventParam     = 8, // `func_800D26D0`
    },
    // [20]
    {
        .requiredEventFlag = EventFlag_254,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 74,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 26,
        .flags_8_13        = 1,
    },
    // [21]
    {
        .completeEventFlag = EventFlag_254,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 74,
        .requiredItemId    = InvItemId_VideoTape,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `func_800D27F4`
    },
    // [22]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 74,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 54,
    },
    // [23]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 85,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 11,
    },
    // [24]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 86,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 11,
    },
    // [25]
    {
        .completeEventFlag = EventFlag_M3S03_PickupBloodPack,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 75,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800D2C2C`
    },
    // [26]
    {
        .completeEventFlag = EventFlag_M3S03_PickupDisinfectingAlcohol,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 93,
        .sysState          = SysState_EventCallback,
        .eventParam        = 14, // `func_800D2C58`
    },
    // [27]
    {
        .completeEventFlag = EventFlag_M3S03_PickupLighter,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 80,
        .sysState          = SysState_EventCallback,
        .eventParam        = 15, // `func_800D2C84`
    },
    // [28]
    {
        .completeEventFlag = EventFlag_M3S03_PickupBasementStoreroomKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 81,
        .sysState          = SysState_EventCallback,
        .eventParam        = 16, // `func_800D2CB0`
    },
    // [29]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 82,
        .sysState       = SysState_EventCallback,
        .eventParam     = 9, // `func_800D2708`
    },
    // [30]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 83,
        .sysState       = SysState_EventCallback,
        .eventParam     = 10, // `func_800D2740`
    },
    // [31]
    {
        .requiredEventFlag = EventFlag_1611,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [32]
    {
        .requiredEventFlag = EventFlag_1611,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 3,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [33]
    {
        .completeEventFlag = EventFlag_1611,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [34]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital3F_StairsArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .flags_8_13        = 1,
    },
    // [35]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital3F_Room301Arrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital3F_Room303Broken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 32,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [37]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital3F_Room303Broken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 32,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 6,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [38]
    {
        .completeEventFlag = EventFlag_1616,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [39]
    {
        .completeEventFlag = EventFlag_1619,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 30,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [40]
    {
        .completeEventFlag = EventFlag_1619,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [41]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital3F_LinenRoomLeftArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 31,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [42]
    {
        .completeEventFlag = EventFlag_1623,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 33,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [43]
    {
        .completeEventFlag = EventFlag_1623,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 33,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 9,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [44]
    {
        .completeEventFlag = EventFlag_1625,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 11,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [45]
    {
        .completeEventFlag = EventFlag_1625,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 10,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [46]
    {
        .completeEventFlag = EventFlag_1628,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [47]
    {
        .completeEventFlag = EventFlag_1627,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 28,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [48]
    {
        .completeEventFlag = EventFlag_1627,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 13,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [49]
    {
        .completeEventFlag = EventFlag_1631,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 20,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [50]
    {
        .completeEventFlag = EventFlag_1631,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 20,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [51]
    {
        .completeEventFlag = EventFlag_1633,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 27,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [52]
    {
        .completeEventFlag = EventFlag_1633,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 15,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [53]
    {
        .completeEventFlag = EventFlag_1635,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 26,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [54]
    {
        .completeEventFlag = EventFlag_1635,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 16,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [55]
    {
        .completeEventFlag = EventFlag_1636,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [56]
    {
        .completeEventFlag = EventFlag_1639,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 25,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [57]
    {
        .completeEventFlag = EventFlag_1639,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 18,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [58]
    {
        .completeEventFlag = EventFlag_1641,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 19,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 34,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [59]
    {
        .completeEventFlag = EventFlag_1641,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 19,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [60]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 21,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 22,
    },
    // [61]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 23,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 24,
    },
    // [62]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 35,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 36,
    },
    // [63]
    {
        .requiredEventFlag = EventFlag_1565,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 41,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [64]
    {
        .requiredEventFlag = EventFlag_1565,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 40,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [65]
    {
        .completeEventFlag = EventFlag_1565,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [66]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital2F_StairsArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .flags_8_13        = 1,
    },
    // [67]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital2F_Room202Broken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 70,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [68]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital2F_Room202Broken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 70,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 42,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [69]
    {
        .completeEventFlag = EventFlag_1568,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [70]
    {
        .completeEventFlag = EventFlag_1571,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 69,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [71]
    {
        .completeEventFlag = EventFlag_1571,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 69,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 44,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [72]
    {
        .completeEventFlag = EventFlag_1573,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 66,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [73]
    {
        .completeEventFlag = EventFlag_1573,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 45,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [74]
    {
        .completeEventFlag = EventFlag_1575,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 68,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [75]
    {
        .completeEventFlag = EventFlag_1575,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 68,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 67,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [76]
    {
        .requiredEventFlag = EventFlag_MapMark_713,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 71,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [77]
    {
        .requiredEventFlag = EventFlag_MapMark_713,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 71,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 46,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [78]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Item,
        .mapPointIdx    = 71,
        .requiredItemId = InvItemId_PlateOfTurtle,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D1A58`
        .flags_8_13     = 1,
    },
    // [79]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Item,
        .mapPointIdx    = 71,
        .requiredItemId = InvItemId_PlateOfHatter,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D1A58`
        .flags_8_13     = 1,
    },
    // [80]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Item,
        .mapPointIdx    = 71,
        .requiredItemId = InvItemId_PlateOfCat,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D1A58`
        .flags_8_13     = 1,
    },
    // [81]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Item,
        .mapPointIdx    = 71,
        .requiredItemId = InvItemId_PlateOfQueen,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D1A58`
        .flags_8_13     = 1,
    },
    // [82]
    {
        .completeEventFlag = EventFlag_281,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 71,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800D1A58`
    },
    // [83]
    {
        .requiredEventFlag = EventFlag_1579,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 47,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 48,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [84]
    {
        .requiredEventFlag = EventFlag_1579,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 48,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 47,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [85]
    {
        .completeEventFlag = EventFlag_1579,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 47,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [86]
    {
        .completeEventFlag = EventFlag_1578,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 48,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .flags_8_13        = 1,
    },
    // [87]
    {
        .completeEventFlag = EventFlag_1580,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 49,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [88]
    {
        .completeEventFlag = EventFlag_1582,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 50,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [89]
    {
        .completeEventFlag = EventFlag_1585,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 57,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [90]
    {
        .completeEventFlag = EventFlag_1585,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 57,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 51,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [91]
    {
        .completeEventFlag = EventFlag_1587,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 52,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 63,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [92]
    {
        .completeEventFlag = EventFlag_1587,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 63,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 52,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [93]
    {
        .completeEventFlag = EventFlag_1588,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 53,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [94]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital3F_NearElevatorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 54,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [95]
    {
        .completeEventFlag = EventFlag_1593,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 62,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [96]
    {
        .completeEventFlag = EventFlag_1593,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 62,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 55,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [97]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital3F_Room305Broken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 56,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 72,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [98]
    {
        .completeEventFlag = EventFlag_MapMark_AltHospital3F_Room305Broken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 72,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 56,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [99]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 58,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 59,
    },
    // [100]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 60,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 61,
        .mapIdx      = MapIdx_MAP3_S04,
    },
    // [101]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 88,
        .sysState       = SysState_EventCallback,
        .eventParam     = 18, // `func_800D30FC`
    },
    // [102]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 89,
        .sysState       = SysState_EventCallback,
        .eventParam     = 18, // `func_800D30FC`
    },
    // [103]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 90,
        .sysState       = SysState_EventCallback,
        .eventParam     = 18, // `func_800D30FC`
    },
    // [104]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 91,
        .sysState       = SysState_EventCallback,
        .eventParam     = 18, // `func_800D30FC`
    },
    // [105]
    {
        .requiredEventFlag = EventFlag_M3S03_PickupDisinfectingAlcohol,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 93,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 46,
    },
    // [106]
    {
        .requiredEventFlag = EventFlag_M3S03_PickupDisinfectingAlcohol,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 94,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 46,
    },
    // [107]
    {
        .requiredEventFlag = EventFlag_M3S03_PickupDisinfectingAlcohol,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 95,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 46,
    },
    // [108]
    {
        .requiredEventFlag = EventFlag_M3S03_PickupDisinfectingAlcohol,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 96,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 46,
    },
    // [109]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 97,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 56,
    },
    // [110]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 98,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 56,
    },
    // [111]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 99,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 56,
    },
    // [112]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 100,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 57,
    },
    // [113]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 101,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 57,
    },
    // [114]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 102,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 59,
    },
    // [115]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 103,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 59,
    },
    // [116]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 104,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 59,
    },
    // [117]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 105,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 59,
    },
    // [118]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 106,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 60,
    },
    // [119]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 107,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 60,
    },
    // [120]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 108,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 58,
    },
    // [121]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 109,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 58,
    },
    // [122]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 110,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 58,
    },
    // [123]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 111,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 61,
    },
    // [124]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 112,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 61,
    },
    // [125]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 113,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 61,
    },
    // [126]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 114,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 61,
    },
    // [127]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 115,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 60,
    },
    // [128]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 116,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 60,
    },
    // [129]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 117,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 60,
    },
    // [130]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 118,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 60,
    },
    // [131]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 119,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 58,
    },
    // [132]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 120,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 58,
    },
    // [133]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 121,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 58,
    },
    // [134]
    {
        .completeEventFlag = EventFlag_1642,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 122,
        .sysState          = SysState_EventSetFlag,
    },
    // [135]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

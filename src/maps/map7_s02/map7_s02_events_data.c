#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[251] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M7S01_RifleShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 212,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M7S01_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 213,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M7S01_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 214,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M7S01_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 215,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M7S01_ShotgunShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 216,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_M7S01_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 217,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [6]
    {
        .completeEventFlag = EventFlag_M7S01_HandgunBullets2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 218,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_M7S01_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 219,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 143,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 22,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 144,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 22,
    },
    // [10]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 157,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 23,
    },
    // [11]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 158,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 23,
    },
    // [12]
    {
        .completeEventFlag = EventFlag_488,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 109,
        .sysState          = SysState_EventCallback,
        .eventParam        = 45, // `func_800E32E0`
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Item,
        .mapPointIdx    = 102,
        .requiredItemId = InvItemId_VideoTape,
        .sysState       = SysState_EventCallback,
        .eventParam     = 8, // `func_800DB738`
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 102,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 151,
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_547,
        .completeEventFlag = EventFlag_548,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `func_800DBB34`
    },
    // [16]
    {
        .completeEventFlag = EventFlag_M7S02_PickupAnkh,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 100,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `MapEvent_AnkhTake`
    },
    // [17]
    {
        .completeEventFlag = EventFlag_M7S02_PickupAnkh,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 101,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `MapEvent_AnkhTake`
    },
    // [18]
    {
        .completeEventFlag = EventFlag_556,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 99,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800DC14C`
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_556,
        .completeEventFlag = EventFlag_M7S02_PickupKeyOfBethor,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 98,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `func_800DC778`
    },
    // [20]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Item,
        .mapPointIdx    = 96,
        .requiredItemId = InvItemId_RingOfContract,
        .sysState       = SysState_EventCallback,
        .eventParam     = 14, // `func_800DC954`
    },
    // [21]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 96,
        .sysState       = SysState_EventCallback,
        .eventParam     = 15, // `func_800DCD00`
    },
    // [22]
    {
        .requiredEventFlag = EventFlag_553,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 104,
        .sysState          = SysState_EventCallback,
        .eventParam        = 16, // `func_800DD2D4`
    },
    // [23]
    {
        .requiredEventFlag = EventFlag_554,
        .completeEventFlag = EventFlag_555,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 104,
        .sysState          = SysState_EventCallback,
        .eventParam        = 17, // `func_800DD9E8`
    },
    // [24]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 95,
        .sysState       = SysState_EventCallback,
        .eventParam     = 18, // `func_800DDEC8`
    },
    // [25]
    {
        .requiredEventFlag = EventFlag_550,
        .completeEventFlag = EventFlag_551,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 20, // `func_800DE1FC`
    },
    // [26]
    {
        .completeEventFlag = EventFlag_M7S02_PickupDiskOfOuroboros,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 93,
        .sysState          = SysState_EventCallback,
        .eventParam        = 21, // `MapEvent_DiskOfOuroborosTake`
    },
    // [27]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 94,
        .sysState       = SysState_EventCallback,
        .eventParam     = 43, // `func_800E2DC0`
    },
    // [28]
    {
        .requiredEventFlag = EventFlag_559,
        .completeEventFlag = EventFlag_560,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 22, // `func_800DF21C`
    },
    // [29]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 3,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 132,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [30]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 4,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 132,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [31]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 5,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 13,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [32]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 13,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 5,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [33]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 6,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 16,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [34]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 16,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 6,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [35]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 7,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 17,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [36]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 17,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 7,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [37]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 8,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 18,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [38]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 18,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 8,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [39]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 9,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 19,
        .sfxPairIdx_8_19 = SfxPairIdx_14,
    },
    // [40]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 19,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_14,
        .field_8_24      = 1,
    },
    // [41]
    {
        .requiredEventFlag = EventFlag_546,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 30,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [42]
    {
        .requiredEventFlag = EventFlag_546,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 10,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [43]
    {
        .completeEventFlag = EventFlag_546,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [44]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_EventCallback,
        .eventParam     = 1, // `MapEvent_DoorLocked`
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [45]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 11,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 53,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
        .mapIdx          = MapIdx_MAP0_S01,
    },
    // [46]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 53,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 11,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
        .mapIdx          = MapIdx_MAP0_S01,
    },
    // [47]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 12,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 71,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [48]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 71,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 12,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [49]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 20,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 26,
    },
    // [50]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 24,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 21,
    },
    // [51]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 25,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 27,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [52]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 27,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 25,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [53]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 28,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 29,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [54]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 29,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 28,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [55]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 31,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 39,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [56]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 39,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 31,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [57]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 32,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 51,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [58]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 51,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 32,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [59]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 33,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 52,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [60]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 52,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 33,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [61]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 40,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 48,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [62]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 48,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 40,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [63]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 41,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 49,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [64]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 49,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 41,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [65]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 54,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 62,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .mapIdx          = MapIdx_MAP0_S01,
    },
    // [66]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 62,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 54,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
        .mapIdx          = MapIdx_MAP0_S01,
    },
    // [67]
    {
        .requiredEventFlag = EventFlag_488,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 63,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [68]
    {
        .requiredEventFlag = EventFlag_488,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 63,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 55,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [69]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 55,
        .sysState       = SysState_EventCallback,
        .eventParam     = 1, // `MapEvent_DoorLocked`
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [70]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupAmuletOfSolomon,
        .completeEventFlag = EventFlag_481,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 65,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 92,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [71]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 64,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 65,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
    },
    // [72]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 65,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 64,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
    },
    // [73]
    {
        .requiredEventFlag = EventFlag_492,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 69,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [74]
    {
        .requiredEventFlag = EventFlag_492,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 69,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 67,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [75]
    {
        .completeEventFlag = EventFlag_493,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_EventCallback,
        .eventParam        = 39, // `sharedFunc_800DB60C_7_s01`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [76]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 68,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 70,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [77]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 70,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 68,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [78]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 72,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 78,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [79]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 78,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 72,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [80]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 73,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 79,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [81]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 79,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 73,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [82]
    {
        .requiredEventFlag = EventFlag_M7S02_PickupKeyOfAratron,
        .completeEventFlag = EventFlag_534,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 74,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_KeyOfAratronUse`
    },
    // [83]
    {
        .requiredEventFlag = EventFlag_M7S02_PickupKeyOfAratron,
        .completeEventFlag = EventFlag_534,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 74,
        .requiredItemId    = InvItemId_KeyOfAratron,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_KeyOfAratronUse`
    },
    // [84]
    {
        .requiredEventFlag = EventFlag_534,
        .completeEventFlag = EventFlag_550,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 74,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 82,
        .transitionFlags        = AreaTransitionFlag_0,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [85]
    {
        .requiredEventFlag = EventFlag_534,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 74,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 82,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [86]
    {
        .requiredEventFlag = EventFlag_534,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 82,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 74,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [87]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 74,
        .sysState       = SysState_EventCallback,
        .eventParam     = 5, // `func_800DB52C`
    },
    // [88]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 74,
        .sysState       = SysState_EventCallback,
        .eventParam     = 1, // `MapEvent_DoorLocked`
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [89]
    {
        .requiredEventFlag = EventFlag_M7S02_PickupKeyOfBethor,
        .completeEventFlag = EventFlag_533,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 75,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_KeyOfBethorUse`
    },
    // [90]
    {
        .requiredEventFlag = EventFlag_M7S02_PickupKeyOfBethor,
        .completeEventFlag = EventFlag_533,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 75,
        .requiredItemId    = InvItemId_KeyOfBethor,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_KeyOfBethorUse`
    },
    // [91]
    {
        .requiredEventFlag = EventFlag_533,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 75,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 83,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [92]
    {
        .requiredEventFlag = EventFlag_533,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 83,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 75,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [93]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 75,
        .sysState       = SysState_EventCallback,
        .eventParam     = 4, // `func_800DB498`
    },
    // [94]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 75,
        .sysState       = SysState_EventCallback,
        .eventParam     = 1, // `MapEvent_DoorLocked`
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [95]
    {
        .completeEventFlag = EventFlag_547,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 76,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 84,
        .transitionFlags        = AreaTransitionFlag_SkipFadeIn,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [96]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 76,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 84,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [97]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 84,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 76,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [98]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 77,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 85,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [99]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 85,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 77,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [100]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 80,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 81,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [101]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 81,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 80,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [102]
    {
        .requiredEventFlag = EventFlag_545,
        .completeEventFlag = EventFlag_559,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 86,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 87,
        .sfxPairIdx_8_19   = SfxPairIdx_14,
    },
    // [103]
    {
        .requiredEventFlag = EventFlag_545,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 86,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 87,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [104]
    {
        .requiredEventFlag = EventFlag_545,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 87,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 86,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [105]
    {
        .completeEventFlag = EventFlag_564,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 86,
        .requiredItemId    = InvItemId_AmuletOfSolomon,
        .sysState          = SysState_EventCallback,
        .eventParam        = 44, // `func_800E2DEC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [106]
    {
        .completeEventFlag = EventFlag_565,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 86,
        .requiredItemId    = InvItemId_CrestOfMercury,
        .sysState          = SysState_EventCallback,
        .eventParam        = 44, // `func_800E2DEC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [107]
    {
        .completeEventFlag = EventFlag_566,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 86,
        .requiredItemId    = InvItemId_Ankh,
        .sysState          = SysState_EventCallback,
        .eventParam        = 44, // `func_800E2DEC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [108]
    {
        .completeEventFlag = EventFlag_567,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 86,
        .requiredItemId    = InvItemId_DaggerOfMelchior,
        .sysState          = SysState_EventCallback,
        .eventParam        = 44, // `func_800E2DEC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [109]
    {
        .completeEventFlag = EventFlag_568,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 86,
        .requiredItemId    = InvItemId_DiskOfOuroboros,
        .sysState          = SysState_EventCallback,
        .eventParam        = 44, // `func_800E2DEC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [110]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 86,
        .sysState       = SysState_EventCallback,
        .eventParam     = 44, // `func_800E2DEC`
    },
    // [111]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 88,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 91,
        .transitionFlags  = AreaTransitionFlag_0,
        .mapIdx      = MapIdx_MAP7_S03,
    },
    // [112]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 118,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 109,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [113]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 119,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 109,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [114]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 120,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 109,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [115]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 121,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 109,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [116]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 122,
        .sysState       = SysState_EventCallback,
        .eventParam     = 23, // `func_800DFA54`
    },
    // [117]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 123,
        .sysState       = SysState_EventCallback,
        .eventParam     = 23, // `func_800DFA54`
    },
    // [118]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 124,
        .sysState       = SysState_EventCallback,
        .eventParam     = 23, // `func_800DFA54`
    },
    // [119]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupPliers,
        .completeEventFlag = EventFlag_M7S01_PickupScrewdriver,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 108,
        .sysState          = SysState_EventCallback,
        .eventParam        = 24, // `MapEvent_ScrewdriverTake`
    },
    // [120]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 115,
        .sysState       = SysState_EventCallback,
        .eventParam     = 25, // `func_800DFAAC`
    },
    // [121]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 114,
        .sysState       = SysState_EventCallback,
        .eventParam     = 26, // `func_800DFAE4`
    },
    // [122]
    {
        .completeEventFlag = EventFlag_M7S01_PickupAmuletOfSolomon,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 113,
        .sysState          = SysState_EventCallback,
        .eventParam        = 27, // `MapEvent_AmuletOfSolomonTake`
    },
    // [123]
    {
        .requiredEventFlag = EventFlag_481,
        .completeEventFlag = EventFlag_482,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 28, // `func_800DA248`
    },
    // [124]
    {
        .requiredEventFlag = EventFlag_482,
        .completeEventFlag = EventFlag_483,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 5,
        .transitionFlags        = AreaTransitionFlag_SkipFadeIn,
    },
    // [125]
    {
        .requiredEventFlag = EventFlag_483,
        .completeEventFlag = EventFlag_484,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 29, // `func_800DAA4C`
    },
    // [126]
    {
        .requiredEventFlag = EventFlag_484,
        .completeEventFlag = EventFlag_569,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 211,
    },
    // [127]
    {
        .requiredEventFlag = EventFlag_569,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 112,
        .sysState          = SysState_EventCallback,
        .eventParam        = 30, // `func_800DFB48`
    },
    // [128]
    {
        .completeEventFlag = EventFlag_500,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 127,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DFDDC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [129]
    {
        .completeEventFlag = EventFlag_501,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 128,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DFDDC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [130]
    {
        .completeEventFlag = EventFlag_502,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 129,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DFDDC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [131]
    {
        .completeEventFlag = EventFlag_503,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 130,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DFDDC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [132]
    {
        .completeEventFlag = EventFlag_504,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 131,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DFDDC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [133]
    {
        .completeEventFlag = EventFlag_505,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 132,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DFDDC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [134]
    {
        .completeEventFlag = EventFlag_506,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 133,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DFDDC`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [135]
    {
        .completeEventFlag = EventFlag_M7S01_PickupCrestOfMercury,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 134,
        .sysState          = SysState_EventCallback,
        .eventParam        = 32, // `MapEvent_CrestOfMercuryTake`
    },
    // [136]
    {
        .completeEventFlag = EventFlag_M7S01_PickupCrestOfMercury,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 135,
        .sysState          = SysState_EventCallback,
        .eventParam        = 32, // `MapEvent_CrestOfMercuryTake`
    },
    // [137]
    {
        .completeEventFlag = EventFlag_M7S01_PickupCrestOfMercury,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 136,
        .sysState          = SysState_EventCallback,
        .eventParam        = 32, // `MapEvent_CrestOfMercuryTake`
    },
    // [138]
    {
        .completeEventFlag = EventFlag_M7S01_PickupRingOfContract,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 137,
        .sysState          = SysState_EventCallback,
        .eventParam        = 33, // `MapEvent_RingOfContractTake`
    },
    // [139]
    {
        .completeEventFlag = EventFlag_M7S01_PickupRingOfContract,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 138,
        .sysState          = SysState_EventCallback,
        .eventParam        = 33, // `MapEvent_RingOfContractTake`
    },
    // [140]
    {
        .completeEventFlag = EventFlag_M7S01_PickupRingOfContract,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 139,
        .sysState          = SysState_EventCallback,
        .eventParam        = 33, // `MapEvent_RingOfContractTake`
    },
    // [141]
    {
        .completeEventFlag = EventFlag_M7S01_PickupCamera,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 106,
        .sysState          = SysState_EventCallback,
        .eventParam        = 34, // `MapEvent_CameraTake`
    },
    // [142]
    {
        .requiredEventFlag = EventFlag_M7S02_PickupKeyOfAratron,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 103,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 131,
    },
    // [143]
    {
        .completeEventFlag = EventFlag_486,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 103,
        .requiredItemId    = InvItemId_Screwdriver,
        .sysState          = SysState_EventCallback,
        .eventParam        = 35, // `func_800E0CB4`
    },
    // [144]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 103,
        .sysState       = SysState_EventCallback,
        .eventParam     = 36, // `func_800E0FF0`
    },
    // [145]
    {
        .completeEventFlag = EventFlag_496,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 125,
        .requiredItemId    = InvItemId_Camera,
        .sysState          = SysState_EventCallback,
        .eventParam        = 38, // `func_800E1398`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [146]
    {
        .completeEventFlag = EventFlag_497,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 126,
        .requiredItemId    = InvItemId_Camera,
        .sysState          = SysState_EventCallback,
        .eventParam        = 38, // `func_800E1398`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [147]
    {
        .completeEventFlag = EventFlag_496,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 125,
        .sysState          = SysState_EventCallback,
        .eventParam        = 37, // `func_800E12E4`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [148]
    {
        .completeEventFlag = EventFlag_497,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 126,
        .sysState          = SysState_EventCallback,
        .eventParam        = 37, // `func_800E12E4`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [149]
    {
        .requiredEventFlag = EventFlag_M5S03_SeenSecondNewspaper,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 111,
        .sysState          = SysState_EventCallback,
        .eventParam        = 40, // `func_800E1DAC`
    },
    // [150]
    {
        .requiredEventFlag = EventFlag_477,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 110,
        .sysState          = SysState_EventCallback,
        .eventParam        = 41, // `func_800E1FF4`
    },
    // [151]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 110,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 158,
    },
    // [152]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 116,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 133,
    },
    // [153]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_EventCallback,
        .eventParam     = 42, // `sharedFunc_800D15F0_3_s01`
    },
    // [154]
    {
        .requiredEventFlag = EventFlag_549,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 132,
    },
    // [155]
    {
        .requiredEventFlag = EventFlag_420,
        .completeEventFlag = EventFlag_213,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [156]
    {
        .requiredEventFlag = EventFlag_549,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 140,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 132,
    },
    // [157]
    {
        .requiredEventFlag = EventFlag_420,
        .completeEventFlag = EventFlag_213,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 140,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [158]
    {
        .requiredEventFlag = EventFlag_549,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 132,
    },
    // [159]
    {
        .requiredEventFlag = EventFlag_420,
        .completeEventFlag = EventFlag_214,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [160]
    {
        .requiredEventFlag = EventFlag_549,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 141,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 132,
    },
    // [161]
    {
        .requiredEventFlag = EventFlag_420,
        .completeEventFlag = EventFlag_214,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 141,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [162]
    {
        .requiredEventFlag = EventFlag_420,
        .completeEventFlag = EventFlag_215,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [163]
    {
        .requiredEventFlag = EventFlag_420,
        .completeEventFlag = EventFlag_215,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 142,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [164]
    {
        .requiredEventFlag = EventFlag_217,
        .completeEventFlag = EventFlag_221,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 140,
    },
    // [165]
    {
        .requiredEventFlag = EventFlag_218,
        .completeEventFlag = EventFlag_222,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 141,
    },
    // [166]
    {
        .requiredEventFlag = EventFlag_219,
        .completeEventFlag = EventFlag_561,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 142,
        .transitionFlags        = AreaTransitionFlag_SkipFadeIn,
    },
    // [167]
    {
        .requiredEventFlag = EventFlag_219,
        .completeEventFlag = EventFlag_223,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 142,
    },
    // [168]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 34,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [169]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 35,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [170]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 36,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [171]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 37,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [172]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 38,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [173]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 42,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [174]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 43,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [175]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 44,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [176]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 45,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [177]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 50,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [178]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 56,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [179]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 57,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [180]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 58,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [181]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 59,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [182]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 60,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [183]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 61,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [184]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 89,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [185]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 90,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [186]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 145,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 135,
    },
    // [187]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 146,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 136,
    },
    // [188]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 147,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 137,
    },
    // [189]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 148,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 138,
    },
    // [190]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 150,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 141,
    },
    // [191]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 151,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 141,
    },
    // [192]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 154,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 143,
    },
    // [193]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 155,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 144,
    },
    // [194]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 156,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 145,
    },
    // [195]
    {
        .triggerType    = TriggerType_TouchAabb,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 149,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 140,
    },
    // [196]
    {
        .triggerType    = TriggerType_TouchAabb,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 152,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 142,
    },
    // [197]
    {
        .triggerType    = TriggerType_TouchAabb,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 153,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 142,
    },
    // [198]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 159,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [199]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 160,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [200]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 161,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [201]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 162,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [202]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 163,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 149,
    },
    // [203]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 164,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 149,
    },
    // [204]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 165,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 149,
    },
    // [205]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 166,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 150,
    },
    // [206]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 167,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 150,
    },
    // [207]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 168,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 150,
    },
    // [208]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 169,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 150,
    },
    // [209]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 170,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 150,
    },
    // [210]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 171,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 150,
    },
    // [211]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 172,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 150,
    },
    // [212]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 173,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [213]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 174,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [214]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 175,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [215]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 176,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [216]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 177,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [217]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 178,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [218]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 179,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [219]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 180,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [220]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 181,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [221]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 182,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [222]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 183,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [223]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 184,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [224]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 185,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [225]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 186,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [226]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 187,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [227]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 188,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [228]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 189,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [229]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 190,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 152,
    },
    // [230]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 191,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 157,
    },
    // [231]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 192,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 157,
    },
    // [232]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 193,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 157,
    },
    // [233]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 194,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 157,
    },
    // [234]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 195,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 153,
    },
    // [235]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 196,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 153,
    },
    // [236]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 197,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [237]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 198,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [238]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 199,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [239]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 200,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 154,
    },
    // [240]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 201,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 154,
    },
    // [241]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 202,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 154,
    },
    // [242]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 203,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 154,
    },
    // [243]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 204,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 153,
    },
    // [244]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 205,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 153,
    },
    // [245]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 206,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 153,
    },
    // [246]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 207,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 153,
    },
    // [247]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 208,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [248]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 209,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [249]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 210,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 148,
    },
    // [250]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

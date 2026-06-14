#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[44] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M5S01_RifleShells0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M5S01_HandgunBullets,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M5S01_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M5S01_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M5S01_RifleShells1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_378,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP5_S02,
    },
    // [6]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 7,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 8,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
        .mapIdx          = MapIdx_MAP5_S02,
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_371,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 10,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .mapIdx            = MapIdx_MAP5_S02,
    },
    // [8]
    {
        .completeEventFlag = EventFlag_371,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800EBF70`
    },
    // [9]
    {
        .completeEventFlag = EventFlag_360,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 6,
        .mapIdx            = MapIdx_MAP5_S00,
    },
    // [10]
    {
        .completeEventFlag = EventFlag_360,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 6,
        .mapIdx            = MapIdx_MAP5_S00,
    },
    // [11]
    {
        .completeEventFlag = EventFlag_360,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 6,
        .mapIdx            = MapIdx_MAP5_S00,
    },
    // [12]
    {
        .completeEventFlag = EventFlag_360,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 6,
        .mapIdx            = MapIdx_MAP5_S00,
    },
    // [13]
    {
        .completeEventFlag = EventFlag_387,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800EBA40`
    },
    // [14]
    {
        .completeEventFlag = EventFlag_387,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800EBA40`
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_387,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 16,
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_387,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 16,
    },
    // [17]
    {
        .requiredEventFlag = EventFlag_387,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 19,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 20,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP5_S03,
    },
    // [18]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 19,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `MapEvent_DoorLocked`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_388,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 18,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP5_S03,
    },
    // [20]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 17,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `MapEvent_DoorLocked`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [21]
    {
        .requiredEventFlag = EventFlag_M5S01_KaufmannKeyUsed,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 16,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP5_S03,
    },
    // [22]
    {
        .requiredEventFlag = EventFlag_380,
        .completeEventFlag = EventFlag_M5S01_KaufmannKeyUsed,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800EC2D8`
    },
    // [23]
    {
        .requiredEventFlag = EventFlag_380,
        .completeEventFlag = EventFlag_M5S01_KaufmannKeyUsed,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 15,
        .requiredItemId    = InvItemId_KaufmannKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800EC2D8`
    },
    // [24]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 15,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `MapEvent_DoorLocked`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [25]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 11,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 12,
    },
    // [26]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 13,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 14,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_M5S01_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `MapEvent_PaperMapTake`
    },
    // [28]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 23,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 24,
        .mapIdx      = MapIdx_MAP6_S00,
    },
    // [29]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 26,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [30]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 27,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [31]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 28,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [32]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 29,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [33]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 30,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [34]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 31,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [35]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 32,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [36]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 33,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [37]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 34,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [38]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 35,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [39]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 36,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [40]
    {
        .completeEventFlag = EventFlag_MapMark_ResortTown_BachmanRdCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 37,
        .sysState          = SysState_EventSetFlag,
    },
    // [41]
    {
        .completeEventFlag = EventFlag_MapMark_ResortTown_CraigStBigCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 38,
        .sysState          = SysState_EventSetFlag,
    },
    // [42]
    {
        .completeEventFlag = EventFlag_458,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 39,
        .requiredItemId    = InvItemId_ChannelingStone,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800EC42C`
    },
    // [43]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

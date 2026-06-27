#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[203] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M7S01_RifleShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 170,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M7S01_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 171,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M7S01_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 172,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M7S01_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 173,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M7S01_ShotgunShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 174,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_M7S01_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 175,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [6]
    {
        .completeEventFlag = EventFlag_M7S01_HandgunBullets2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 176,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_M7S01_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 177,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 140,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 22,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 141,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 22,
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_473,
        .completeEventFlag = EventFlag_479,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 45, // `func_800DCE20`
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_479,
        .completeEventFlag = EventFlag_480,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .field_8_24        = 1,
        .mapIdx            = MapIdx_MAP2_S04,
    },
    // [12]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 3,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 88,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [13]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 4,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 88,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 118,
        .sysState          = SysState_EventCallback,
        .eventParam        = 46, // `func_800D8A04`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 119,
        .sysState          = SysState_EventCallback,
        .eventParam        = 46, // `func_800D8A04`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 120,
        .sysState          = SysState_EventCallback,
        .eventParam        = 46, // `func_800D8A04`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [17]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 121,
        .sysState          = SysState_EventCallback,
        .eventParam        = 46, // `func_800D8A04`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [18]
    {
        .requiredEventFlag = EventFlag_491,
        .completeEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 118,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800D89D8`
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_491,
        .completeEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 119,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800D89D8`
    },
    // [20]
    {
        .requiredEventFlag = EventFlag_491,
        .completeEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 120,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800D89D8`
    },
    // [21]
    {
        .requiredEventFlag = EventFlag_491,
        .completeEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 121,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800D89D8`
    },
    // [22]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 118,
        .requiredItemId    = InvItemId_BirdCageKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_BirdCageKeyUse`
    },
    // [23]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 118,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_BirdCageKeyUse`
    },
    // [24]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 119,
        .requiredItemId    = InvItemId_BirdCageKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_BirdCageKeyUse`
    },
    // [25]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 119,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_BirdCageKeyUse`
    },
    // [26]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 120,
        .requiredItemId    = InvItemId_BirdCageKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_BirdCageKeyUse`
    },
    // [27]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 120,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_BirdCageKeyUse`
    },
    // [28]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 121,
        .requiredItemId    = InvItemId_BirdCageKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_BirdCageKeyUse`
    },
    // [29]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 121,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_BirdCageKeyUse`
    },
    // [30]
    {
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 118,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800D8958`
    },
    // [31]
    {
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 119,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800D8958`
    },
    // [32]
    {
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 120,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800D8958`
    },
    // [33]
    {
        .completeEventFlag = EventFlag_491,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 121,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800D8958`
    },
    // [34]
    {
        .completeEventFlag = EventFlag_490,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 117,
        .requiredItemId    = InvItemId_Pliers,
        .sysState          = SysState_EventCallback,
        .eventParam        = 15, // `func_800D8A5C`
    },
    // [35]
    {
        .completeEventFlag = EventFlag_490,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 117,
        .sysState          = SysState_EventCallback,
        .eventParam        = 14, // `func_800D8A30`
    },
    // [36]
    {
        .requiredEventFlag = EventFlag_490,
        .completeEventFlag = EventFlag_525,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 103,
        .sysState          = SysState_EventCallback,
        .eventParam        = 16, // `func_800D8DB4`
    },
    // [37]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfHagith,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 116,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 89,
    },
    // [38]
    {
        .requiredEventFlag = EventFlag_489,
        .completeEventFlag = EventFlag_M7S01_PickupKeyOfHagith,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 116,
        .sysState          = SysState_EventCallback,
        .eventParam        = 19, // `func_800D93BC`
    },
    // [39]
    {
        .completeEventFlag = EventFlag_489,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 116,
        .requiredItemId    = InvItemId_StoneOfTime,
        .sysState          = SysState_EventCallback,
        .eventParam        = 18, // `func_800D8FF8`
    },
    // [40]
    {
        .completeEventFlag = EventFlag_489,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 116,
        .sysState          = SysState_EventCallback,
        .eventParam        = 17, // `func_800D8FCC`
    },
    // [41]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 122,
        .sysState       = SysState_EventCallback,
        .eventParam     = 20, // `func_800D93E8`
    },
    // [42]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 123,
        .sysState       = SysState_EventCallback,
        .eventParam     = 20, // `func_800D93E8`
    },
    // [43]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 124,
        .sysState       = SysState_EventCallback,
        .eventParam     = 20, // `func_800D93E8`
    },
    // [44]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupScrewdriver,
        .completeEventFlag = EventFlag_M7S01_PickupPliers,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 105,
        .sysState          = SysState_EventCallback,
        .eventParam        = 21, // `func_800D9414`
    },
    // [45]
    {
        .completeEventFlag = EventFlag_M7S01_PickupPliers,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 104,
        .sysState          = SysState_EventCallback,
        .eventParam        = 21, // `func_800D9414`
    },
    // [46]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupPliers,
        .completeEventFlag = EventFlag_M7S01_PickupScrewdriver,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 107,
        .sysState          = SysState_EventCallback,
        .eventParam        = 22, // `func_800D9440`
    },
    // [47]
    {
        .completeEventFlag = EventFlag_M7S01_PickupScrewdriver,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 106,
        .sysState          = SysState_EventCallback,
        .eventParam        = 22, // `func_800D9440`
    },
    // [48]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 115,
        .sysState       = SysState_EventCallback,
        .eventParam     = 23, // `func_800D946C`
    },
    // [49]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 114,
        .sysState       = SysState_EventCallback,
        .eventParam     = 24, // `func_800D94A4`
    },
    // [50]
    {
        .completeEventFlag = EventFlag_488,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 108,
        .sysState          = SysState_EventCallback,
        .eventParam        = 25, // `func_800D94DC`
    },
    // [51]
    {
        .completeEventFlag = EventFlag_M7S01_PickupAmuletOfSolomon,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 113,
        .sysState          = SysState_EventCallback,
        .eventParam        = 26, // `func_800D99DC`
    },
    // [52]
    {
        .requiredEventFlag = EventFlag_481,
        .completeEventFlag = EventFlag_482,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 27, // `func_800D725C`
    },
    // [53]
    {
        .requiredEventFlag = EventFlag_482,
        .completeEventFlag = EventFlag_483,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 5,
        .transitionFlags   = AreaTransitionFlag_SkipFadeIn,
    },
    // [54]
    {
        .requiredEventFlag = EventFlag_483,
        .completeEventFlag = EventFlag_484,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 28, // `func_800D7A60`
    },
    // [55]
    {
        .requiredEventFlag = EventFlag_484,
        .completeEventFlag = EventFlag_569,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 169,
    },
    // [56]
    {
        .requiredEventFlag = EventFlag_569,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 112,
        .sysState          = SysState_EventCallback,
        .eventParam        = 29, // `func_800D9A08`
    },
    // [57]
    {
        .completeEventFlag = EventFlag_500,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 127,
        .sysState          = SysState_EventCallback,
        .eventParam        = 30, // `func_800D9C9C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [58]
    {
        .completeEventFlag = EventFlag_501,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 128,
        .sysState          = SysState_EventCallback,
        .eventParam        = 30, // `func_800D9C9C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [59]
    {
        .completeEventFlag = EventFlag_502,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 129,
        .sysState          = SysState_EventCallback,
        .eventParam        = 30, // `func_800D9C9C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [60]
    {
        .completeEventFlag = EventFlag_503,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 130,
        .sysState          = SysState_EventCallback,
        .eventParam        = 30, // `func_800D9C9C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [61]
    {
        .completeEventFlag = EventFlag_504,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 131,
        .sysState          = SysState_EventCallback,
        .eventParam        = 30, // `func_800D9C9C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [62]
    {
        .completeEventFlag = EventFlag_505,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 132,
        .sysState          = SysState_EventCallback,
        .eventParam        = 30, // `func_800D9C9C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [63]
    {
        .completeEventFlag = EventFlag_506,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 133,
        .sysState          = SysState_EventCallback,
        .eventParam        = 30, // `func_800D9C9C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [64]
    {
        .requiredEventFlag = EventFlag_487,
        .completeEventFlag = EventFlag_M7S01_PickupStoneOfTime,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 98,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DAB64`
    },
    // [65]
    {
        .requiredEventFlag = EventFlag_487,
        .completeEventFlag = EventFlag_M7S01_PickupStoneOfTime,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 99,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DAB64`
    },
    // [66]
    {
        .requiredEventFlag = EventFlag_487,
        .completeEventFlag = EventFlag_M7S01_PickupStoneOfTime,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 100,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DAB64`
    },
    // [67]
    {
        .requiredEventFlag = EventFlag_487,
        .completeEventFlag = EventFlag_M7S01_PickupStoneOfTime,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 101,
        .sysState          = SysState_EventCallback,
        .eventParam        = 31, // `func_800DAB64`
    },
    // [68]
    {
        .completeEventFlag = EventFlag_M7S01_PickupCrestOfMercury,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 134,
        .sysState          = SysState_EventCallback,
        .eventParam        = 32, // `func_800DAD7C`
    },
    // [69]
    {
        .completeEventFlag = EventFlag_M7S01_PickupCrestOfMercury,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 135,
        .sysState          = SysState_EventCallback,
        .eventParam        = 32, // `func_800DAD7C`
    },
    // [70]
    {
        .completeEventFlag = EventFlag_M7S01_PickupCrestOfMercury,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 136,
        .sysState          = SysState_EventCallback,
        .eventParam        = 32, // `func_800DAD7C`
    },
    // [71]
    {
        .completeEventFlag = EventFlag_M7S01_PickupRingOfContract,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 137,
        .sysState          = SysState_EventCallback,
        .eventParam        = 33, // `func_800DADA8`
    },
    // [72]
    {
        .completeEventFlag = EventFlag_M7S01_PickupRingOfContract,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 138,
        .sysState          = SysState_EventCallback,
        .eventParam        = 33, // `func_800DADA8`
    },
    // [73]
    {
        .completeEventFlag = EventFlag_M7S01_PickupRingOfContract,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 139,
        .sysState          = SysState_EventCallback,
        .eventParam        = 33, // `func_800DADA8`
    },
    // [74]
    {
        .completeEventFlag = EventFlag_M7S01_PickupCamera,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 97,
        .sysState          = SysState_EventCallback,
        .eventParam        = 34, // `MapEvent_CutsceneCherylRedirect3`
    },
    // [75]
    {
        .completeEventFlag = EventFlag_486,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 111,
        .requiredItemId    = InvItemId_Screwdriver,
        .sysState          = SysState_EventCallback,
        .eventParam        = 35, // `func_800DAE00`
    },
    // [76]
    {
        .requiredEventFlag = EventFlag_486,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 111,
        .sysState          = SysState_EventCallback,
        .eventParam        = 36, // `func_800DB13C`
    },
    // [77]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 111,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 87,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [78]
    {
        .requiredEventFlag = EventFlag_561,
        .completeEventFlag = EventFlag_562,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 37, // `func_800DB1F0`
    },
    // [79]
    {
        .completeEventFlag = EventFlag_496,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 125,
        .requiredItemId    = InvItemId_Camera,
        .sysState          = SysState_EventCallback,
        .eventParam        = 39, // `func_800DB3D0`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [80]
    {
        .completeEventFlag = EventFlag_497,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 126,
        .requiredItemId    = InvItemId_Camera,
        .sysState          = SysState_EventCallback,
        .eventParam        = 39, // `func_800DB3D0`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [81]
    {
        .completeEventFlag = EventFlag_496,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 125,
        .sysState          = SysState_EventCallback,
        .eventParam        = 38, // `func_800DB31C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [82]
    {
        .completeEventFlag = EventFlag_497,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 126,
        .sysState          = SysState_EventCallback,
        .eventParam        = 38, // `func_800DB31C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [83]
    {
        .requiredEventFlag = EventFlag_M5S03_SeenSecondNewspaper,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 110,
        .sysState          = SysState_EventCallback,
        .eventParam        = 41, // `func_800DBDE0`
    },
    // [84]
    {
        .requiredEventFlag = EventFlag_M7S00_BotanyBookReadable,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 109,
        .sysState          = SysState_EventCallback,
        .eventParam        = 42, // `func_800DC028`
    },
    // [85]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 109,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 96,
    },
    // [86]
    {
        .completeEventFlag = EventFlag_M7S01_PickupBirdCageKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 96,
        .sysState          = SysState_EventCallback,
        .eventParam        = 43, // `func_800DC080`
    },
    // [87]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfHagith,
        .completeEventFlag = EventFlag_531,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `MapEvent_KeyOfHagithUse`
    },
    // [88]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfHagith,
        .completeEventFlag = EventFlag_531,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 5,
        .requiredItemId    = InvItemId_KeyOfHagith,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `MapEvent_KeyOfHagithUse`
    },
    // [89]
    {
        .requiredEventFlag = EventFlag_531,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 13,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [90]
    {
        .requiredEventFlag = EventFlag_531,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 5,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [91]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 5,
        .sysState       = SysState_EventCallback,
        .eventParam     = 5, // `func_800D8540`
    },
    // [92]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 5,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `func_800D82C4`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [93]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 6,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 16,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [94]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 16,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 6,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [95]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 7,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 17,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [96]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 17,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 7,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [97]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 8,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 18,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [98]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 18,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 8,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [99]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 9,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 19,
        .sfxPairIdx_8_19 = SfxPairIdx_14,
    },
    // [100]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 19,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_14,
        .field_8_24      = 1,
    },
    // [101]
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
    // [102]
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
    // [103]
    {
        .completeEventFlag = EventFlag_546,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D8358`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [104]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 10,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `func_800D82C4`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [105]
    {
        .requiredEventFlag = EventFlag_525,
        .completeEventFlag = EventFlag_530,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_KeyOfOphielUse`
    },
    // [106]
    {
        .requiredEventFlag = EventFlag_525,
        .completeEventFlag = EventFlag_530,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 11,
        .requiredItemId    = InvItemId_KeyOfOphiel,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_KeyOfOphielUse`
    },
    // [107]
    {
        .requiredEventFlag = EventFlag_530,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 53,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
        .mapIdx            = MapIdx_MAP0_S01,
    },
    // [108]
    {
        .requiredEventFlag = EventFlag_530,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 53,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 11,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
        .mapIdx            = MapIdx_MAP0_S01,
    },
    // [109]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_EventCallback,
        .eventParam     = 4, // `func_800D84AC`
    },
    // [110]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 11,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `func_800D82C4`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [111]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .completeEventFlag = EventFlag_532,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `MapEvent_KeyOfPhalegUse`
    },
    // [112]
    {
        .requiredEventFlag = EventFlag_M7S01_PickupKeyOfPhaleg,
        .completeEventFlag = EventFlag_532,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 12,
        .requiredItemId    = InvItemId_KeyOfPhaleg,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `MapEvent_KeyOfPhalegUse`
    },
    // [113]
    {
        .requiredEventFlag = EventFlag_532,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 71,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .mapIdx            = MapIdx_MAP7_S02,
    },
    // [114]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_EventCallback,
        .eventParam     = 6, // `func_800D85D4`
    },
    // [115]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 12,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `func_800D82C4`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [116]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 20,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 26,
    },
    // [117]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 24,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 21,
    },
    // [118]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_EventCallback,
        .eventParam     = 44, // `sharedFunc_800D15F0_3_s01`
    },
    // [119]
    {
        .completeEventFlag = EventFlag_213,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [120]
    {
        .completeEventFlag = EventFlag_213,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 93,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [121]
    {
        .completeEventFlag = EventFlag_214,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [122]
    {
        .completeEventFlag = EventFlag_214,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 94,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [123]
    {
        .completeEventFlag = EventFlag_215,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [124]
    {
        .completeEventFlag = EventFlag_215,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 95,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_7,
    },
    // [125]
    {
        .requiredEventFlag = EventFlag_217,
        .completeEventFlag = EventFlag_221,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 93,
    },
    // [126]
    {
        .requiredEventFlag = EventFlag_218,
        .completeEventFlag = EventFlag_222,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 94,
    },
    // [127]
    {
        .requiredEventFlag = EventFlag_219,
        .completeEventFlag = EventFlag_561,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 95,
        .transitionFlags   = AreaTransitionFlag_SkipFadeIn,
        .field_8_24        = 1,
    },
    // [128]
    {
        .requiredEventFlag = EventFlag_219,
        .completeEventFlag = EventFlag_223,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 95,
    },
    // [129]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 25,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 27,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [130]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 27,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 25,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [131]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 28,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 29,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [132]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 29,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 28,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [133]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 31,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 39,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [134]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 39,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 31,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [135]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 32,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 51,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [136]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 51,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 32,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [137]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 33,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 52,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [138]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 52,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 33,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [139]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 40,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 48,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [140]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 48,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 40,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .field_8_24      = 1,
    },
    // [141]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 41,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 49,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
    },
    // [142]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 49,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 41,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
    },
    // [143]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 54,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 62,
        .sfxPairIdx_8_19 = SfxPairIdx_12,
        .field_8_24      = 1,
        .mapIdx          = MapIdx_MAP0_S01,
    },
    // [144]
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
    // [145]
    {
        .requiredEventFlag = EventFlag_488,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 63,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [146]
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
    // [147]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 55,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `func_800D82C4`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [148]
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
    // [149]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 64,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 65,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
    },
    // [150]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 65,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 64,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
    },
    // [151]
    {
        .requiredEventFlag = EventFlag_492,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 69,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [152]
    {
        .requiredEventFlag = EventFlag_492,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 69,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 67,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [153]
    {
        .completeEventFlag = EventFlag_493,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_EventCallback,
        .eventParam        = 40, // `sharedFunc_800DB60C_7_s01`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [154]
    {
        .requiredEventFlag = EventFlag_494,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 68,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 70,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [155]
    {
        .requiredEventFlag = EventFlag_494,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 70,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 68,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [156]
    {
        .completeEventFlag = EventFlag_495,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 68,
        .sysState          = SysState_EventCallback,
        .eventParam        = 40, // `sharedFunc_800DB60C_7_s01`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [157]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 34,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [158]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 35,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [159]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 36,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [160]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 37,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [161]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 38,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [162]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 42,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [163]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 43,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [164]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 44,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [165]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 45,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [166]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 50,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [167]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 56,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [168]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 57,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [169]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 58,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [170]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 59,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [171]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 60,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [172]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 61,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [173]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 89,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [174]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 90,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [175]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 142,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 90,
    },
    // [176]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 143,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 91,
    },
    // [177]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 144,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 93,
    },
    // [178]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 145,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 93,
    },
    // [179]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 146,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 93,
    },
    // [180]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 147,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 93,
    },
    // [181]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 148,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 94,
    },
    // [182]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 149,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 94,
    },
    // [183]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 150,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 94,
    },
    // [184]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 151,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [185]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 152,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [186]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 153,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [187]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 154,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [188]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 155,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [189]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 156,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [190]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 157,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [191]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 158,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [192]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 159,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [193]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 160,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [194]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 161,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [195]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 162,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [196]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 163,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [197]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 164,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [198]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 165,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [199]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 166,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [200]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 167,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [201]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 168,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 95,
    },
    // [202]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

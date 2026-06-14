#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[46] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M5S03_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M5S03_ShotgunShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M5S03_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 19,
    },
    // [4]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 19,
        .sysState       = SysState_EventCallback,
        .eventParam     = 6, // `func_800D1A84`
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_203,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 20,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `func_800D2640`
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_203,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `func_800D2640`
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_203,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `func_800D2640`
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 20,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 21,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [10]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 22,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [11]
    {
        .completeEventFlag = EventFlag_M5S03_PickupMagnet,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 24,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800D1ACC`
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_389,
        .completeEventFlag = EventFlag_390,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 15,
        .requiredItemId    = InvItemId_Magnet,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D1628`
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_390,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 16,
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_389,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D1904`
    },
    // [15]
    {
        .completeEventFlag = EventFlag_389,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `func_800D2674`
    },
    // [16]
    {
        .completeEventFlag = EventFlag_389,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 36,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `func_800D2674`
    },
    // [17]
    {
        .requiredEventFlag = EventFlag_M5S03_KaufmannHasMotorcycleVial,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 67,
    },
    // [18]
    {
        .requiredEventFlag = EventFlag_M5S03_KaufmannHasMotorcycleVial,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 67,
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_M5S03_KaufmannHasMotorcycleVial,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 67,
    },
    // [20]
    {
        .completeEventFlag = EventFlag_M5S03_KaufmannHasMotorcycleVial,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 16,
        .requiredItemId    = InvItemId_MotorcycleKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `func_800D1AF8`
    },
    // [21]
    {
        .completeEventFlag = EventFlag_M5S03_KaufmannHasMotorcycleVial,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 17,
        .requiredItemId    = InvItemId_MotorcycleKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `func_800D1AF8`
    },
    // [22]
    {
        .completeEventFlag = EventFlag_M5S03_KaufmannHasMotorcycleVial,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 18,
        .requiredItemId    = InvItemId_MotorcycleKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `func_800D1AF8`
    },
    // [23]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 19,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [24]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 17,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 19,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [25]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 19,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [26]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 18,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 19,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [27]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 12,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 13,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
        .mapIdx          = MapIdx_MAP5_S01,
    },
    // [28]
    {
        .requiredEventFlag = EventFlag_388,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 3,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP5_S01,
    },
    // [29]
    {
        .completeEventFlag = EventFlag_388,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags        = AreaTransitionFlag_0,
    },
    // [30]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 9,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 11,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
        .mapIdx          = MapIdx_MAP5_S01,
    },
    // [31]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 4,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 7,
    },
    // [32]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 6,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 5,
    },
    // [33]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 14,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 8,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
    },
    // [34]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 8,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 14,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
    },
    // [35]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_EventCallback,
        .transitionFlags     = AreaTransitionFlag_0,
    },
    // [36]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 26,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 55,
    },
    // [37]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 27,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 57,
    },
    // [38]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 28,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 59,
    },
    // [39]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 29,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 60,
    },
    // [40]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 30,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 62,
    },
    // [41]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 31,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 62,
    },
    // [42]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 32,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 63,
    },
    // [43]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 33,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 64,
    },
    // [44]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 34,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 65,
    },
    // [45]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

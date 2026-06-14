#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[16] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M6S03_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M6S03_HandgunBullets,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M6S03_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .requiredEventFlag = EventFlag_426,
        .completeEventFlag = EventFlag_438,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 9,
        .transitionFlags   = AreaTransitionFlag_SkipFadeIn,
    },
    // [4]
    {
        .completeEventFlag = EventFlag_431,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D822C`
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_431,
        .completeEventFlag = EventFlag_432,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
    },
    // [6]
    {
        .completeEventFlag = EventFlag_433,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D84EC`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_433,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D84EC`
    },
    // [8]
    {
        .completeEventFlag = EventFlag_433,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D84EC`
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_433,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 7,
        .mapIdx            = MapIdx_MAP6_S04,
    },
    // [10]
    {
        .completeEventFlag = EventFlag_434,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventSetFlag,
    },
    // [11]
    {
        .completeEventFlag = EventFlag_435,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 6,
        .sysState          = SysState_EventSetFlag,
    },
    // [12]
    {
        .completeEventFlag = EventFlag_M6S03_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_PaperMapTake`
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 16,
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_435,
        .completeEventFlag = EventFlag_MapMark_FogHospital1F_MedicineRoomBotArrows,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 9,
        .sysState          = SysState_EventSetFlag,
    },
    // [15]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

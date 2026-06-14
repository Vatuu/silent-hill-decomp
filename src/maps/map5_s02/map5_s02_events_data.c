#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[21] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M5S02_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M5S02_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M5S02_RifleShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M5S02_HealthDrink2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .requiredEventFlag = EventFlag_378,
        .completeEventFlag = EventFlag_379,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `MapEvent_KaufmannBarFightCutscene`
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_379,
        .completeEventFlag = EventFlag_380,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800D54D0`
    },
    // [6]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
        .mapIdx          = MapIdx_MAP5_S01,
    },
    // [7]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 3,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP5_S01,
    },
    // [8]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 2,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 5,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 14,
    },
    // [10]
    {
        .completeEventFlag = EventFlag_375,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D4B58`
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_375,
        .completeEventFlag = EventFlag_M5S02_PickupSafeKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D4DF8`
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_375,
        .completeEventFlag = EventFlag_M5S02_PickupSafeKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D4DF8`
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_375,
        .completeEventFlag = EventFlag_M5S02_PickupSafeKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D4DF8`
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_M5S02_UsedSafeKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800D519C`
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_M5S02_PickupSafeKey,
        .completeEventFlag = EventFlag_M5S02_UsedSafeKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 11,
        .requiredItemId    = InvItemId_SafeKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D4E64`
    },
    // [16]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 11,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 48,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_EventCallback,
        .eventParam     = 5, // `func_800D4E24`
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_EventCallback,
        .eventParam     = 8, // `func_800D5478`
    },
    // [19]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 13,
        .sysState       = SysState_EventCallback,
        .eventParam     = 9, // `func_800D54A4`
    },
    // [20]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

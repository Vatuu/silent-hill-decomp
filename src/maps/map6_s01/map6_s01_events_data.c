#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[17] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M6S01_RifleShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M6S01_HandgunBullets,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M6S01_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_423,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .flags_8_13        = 2,
        .sfxPairIdx_8_19   = SfxPairIdx_10,
    },
    // [4]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 3,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_10,
    },
    // [5]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 4,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 3,
        .sfxPairIdx_8_19 = SfxPairIdx_10,
    },
    // [6]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 2,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 6,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP6_S00,
    },
    // [7]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 5,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 7,
        .sfxPairIdx_8_19 = SfxPairIdx_9,
        .mapIdx          = MapIdx_MAP6_S00,
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_423,
        .completeEventFlag = EventFlag_424,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D13D8`
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_425,
        .completeEventFlag = EventFlag_426,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D236C`
    },
    // [10]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 8,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 17,
    },
    // [11]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 9,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 87,
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 88,
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 88,
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_426,
        .completeEventFlag = EventFlag_459,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventSetFlag,
    },
    // [15]
    {
        .completeEventFlag = EventFlag_459,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 12,
        .requiredItemId    = InvItemId_ChannelingStone,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D2658`
    },
    // [16]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

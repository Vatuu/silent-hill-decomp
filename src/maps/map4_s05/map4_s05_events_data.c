#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[18] = {
    // [0]
    {
        .requiredEventFlag = EventFlag_347,
        .completeEventFlag = EventFlag_349,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D61AC`
    },
    // [1]
    {
        .requiredEventFlag = EventFlag_350,
        .completeEventFlag = EventFlag_352,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D6800`
    },
    // [2]
    {
        .requiredEventFlag = EventFlag_352,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 14,
        .transitionFlags   = 6,
        .mapIdx            = MapIdx_MAP2_S02,
    },
    // [3]
    {
        .completeEventFlag = EventFlag_346,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventSetFlag,
    },
    // [4]
    {
        .requiredEventFlag = EventFlag_346,
        .completeEventFlag = EventFlag_347,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 12,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 13,
        .transitionFlags   = AreaTransitionFlag_SkipFadeIn,
    },
    // [5]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 2,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 5,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [6]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 3,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 5,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [7]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 4,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 5,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [8]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 6,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [9]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 7,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [10]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 8,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [11]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 9,
        .sysState        = SysState_EventCallback,
        .eventParam      = 1, // `MapEvent_DoorLocked`
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [12]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 10,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [13]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 15,
        .sysState        = SysState_EventCallback,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 17,
    },
    // [15]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 18,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 18,
    },
    // [16]
    {
        .completeEventFlag = EventFlag_457,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 17,
        .requiredItemId    = InvItemId_ChannelingStone,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D6BC0`
    },
    // [17]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

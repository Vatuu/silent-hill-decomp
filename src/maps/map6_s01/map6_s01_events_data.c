#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[17] = {
    {
        .disabledEventFlag  = EventFlag_M6S01_RifleShells,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 13,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M6S01_HandgunBullets,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 14,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M6S01_HealthDrink,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 15,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_423,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 3,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 4,
        .flags_8_13           = 2,
        .sfxPairIdx_8_19 = SfxPairIdx_10,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 3,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_10,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 3,
        .sfxPairIdx_8_19 = SfxPairIdx_10,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 6,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx   = MapIdx_MAP6_S00,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 5,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 7,
        .sfxPairIdx_8_19 = SfxPairIdx_9,
        .mapIdx   = MapIdx_MAP6_S00,
    },
    {
        .requiredEventFlag = EventFlag_423,
        .disabledEventFlag = EventFlag_424,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 3, // `func_800D13D8`
    },
    {
        .requiredEventFlag = EventFlag_425,
        .disabledEventFlag = EventFlag_426,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 4, // `func_800D236C`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 8,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 17,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 9,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 87,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 88,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 11,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 88,
    },
    {
        .requiredEventFlag = EventFlag_426,
        .disabledEventFlag = EventFlag_459,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventSetFlag,
    },
    {
        .disabledEventFlag  = EventFlag_459,
        .triggerType      = TriggerType_TouchAabb,
        .activationType   = TriggerActivationType_Item,
        .pointOfInterestIdx = 12,
        .requiredItemId     = InvItemId_ChannelingStone,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 5, // `func_800D2658`
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

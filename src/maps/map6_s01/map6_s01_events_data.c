#include "bodyprog/bodyprog.h"

s_EventData D_800D3FA4[17] = {
    {
        .disabledEventFlag_2  = EventFlag_M6S01_RifleShells,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 13,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M6S01_HandgunBullets,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 14,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M6S01_HealthDrink,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 15,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_423,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 3,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 4,
        .flags_8_13           = 2,
        .field_8_19           = 10,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 3,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 4,
        .field_8_19           = 10,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 3,
        .field_8_19           = 10,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 6,
        .field_8_19           = 2,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP6_S00,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 5,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 7,
        .field_8_19           = 9,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP6_S00,
    },
    {
        .requiredEventFlag_0 = EventFlag_423,
        .disabledEventFlag_2 = EventFlag_424,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 3, // `func_800D13D8`
    },
    {
        .requiredEventFlag_0 = EventFlag_425,
        .disabledEventFlag_2 = EventFlag_426,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 4, // `func_800D236C`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 8,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 17,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 9,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 87,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 88,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 11,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 88,
    },
    {
        .requiredEventFlag_0 = EventFlag_426,
        .disabledEventFlag_2 = EventFlag_459,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventSetFlag,
    },
    {
        .disabledEventFlag_2  = EventFlag_459,
        .triggerType_4_0      = TriggerType_TouchAabb,
        .activationType_4_4   = TriggerActivationType_Item,
        .pointOfInterestIdx_5 = 12,
        .requiredItemId_6     = InventoryItemId_ChannelingStone,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 5, // `func_800D2658`
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

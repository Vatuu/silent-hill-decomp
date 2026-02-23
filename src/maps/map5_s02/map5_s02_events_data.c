#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[21] = {
    {
        .disabledEventFlag_2  = EventFlag_M5S02_HealthDrink0,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 15,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M5S02_HealthDrink1,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 16,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M5S02_RifleShells,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 17,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M5S02_HealthDrink2,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 18,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .requiredEventFlag_0 = EventFlag_378,
        .disabledEventFlag_2 = EventFlag_379,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 10, // `MapEvent_KaufmannBarFightCutscene`
    },
    {
        .requiredEventFlag_0  = EventFlag_379,
        .disabledEventFlag_2  = EventFlag_380,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 14,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 11, // `func_800D54D0`
    },
    {
        .triggerType_4_0    = TriggerType_TouchObbFacing,
        .activationType_4_4 = TriggerActivationType_Button,
        .sysState_8_0       = SysState_LoadOverlay,
        .eventParam_8_5     = 1,
        .field_8_19         = 1,
        .mapOverlayIdx_8_25 = MapOverlayId_MAP5_S01,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 3,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 4,
        .field_8_19           = 2,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP5_S01,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 5,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 14,
    },
    {
        .disabledEventFlag_2  = EventFlag_375,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 3, // `func_800D4B58`
    },
    {
        .requiredEventFlag_0  = EventFlag_375,
        .disabledEventFlag_2  = EventFlag_M5S02_PickupSafeKey,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 7,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800D4DF8`
    },
    {
        .requiredEventFlag_0  = EventFlag_375,
        .disabledEventFlag_2  = EventFlag_M5S02_PickupSafeKey,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 8,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800D4DF8`
    },
    {
        .requiredEventFlag_0  = EventFlag_375,
        .disabledEventFlag_2  = EventFlag_M5S02_PickupSafeKey,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 9,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800D4DF8`
    },
    {
        .requiredEventFlag_0  = EventFlag_M5S02_UsedSafeKey,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 11,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 7, // `func_800D519C`
    },
    {
        .requiredEventFlag_0  = EventFlag_M5S02_PickupSafeKey,
        .disabledEventFlag_2  = EventFlag_M5S02_UsedSafeKey,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Item,
        .pointOfInterestIdx_5 = 11,
        .requiredItemId_6     = InventoryItemId_SafeKey,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 6, // `func_800D4E64`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 11,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 48,
        .flags_8_13           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 5, // `func_800D4E24`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 12,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 8, // `func_800D5478`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 13,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 9, // `func_800D54A4`
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

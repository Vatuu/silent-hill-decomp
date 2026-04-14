#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[21] = {
    {
        .disabledEventFlag  = EventFlag_M5S02_HealthDrink0,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 15,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M5S02_HealthDrink1,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 16,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M5S02_RifleShells,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 17,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M5S02_HealthDrink2,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 18,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .requiredEventFlag = EventFlag_378,
        .disabledEventFlag = EventFlag_379,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallFunc,
        .eventParam      = 10, // `MapEvent_KaufmannBarFightCutscene`
    },
    {
        .requiredEventFlag  = EventFlag_379,
        .disabledEventFlag  = EventFlag_380,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 14,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 11, // `func_800D54D0`
    },
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .sysState       = SysState_LoadOverlay,
        .eventParam     = 1,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
        .mapIdx = MapIdx_MAP5_S01,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 3,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 4,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx   = MapIdx_MAP5_S01,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 5,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 14,
    },
    {
        .disabledEventFlag  = EventFlag_375,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 3, // `func_800D4B58`
    },
    {
        .requiredEventFlag  = EventFlag_375,
        .disabledEventFlag  = EventFlag_M5S02_PickupSafeKey,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 7,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 4, // `func_800D4DF8`
    },
    {
        .requiredEventFlag  = EventFlag_375,
        .disabledEventFlag  = EventFlag_M5S02_PickupSafeKey,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 8,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 4, // `func_800D4DF8`
    },
    {
        .requiredEventFlag  = EventFlag_375,
        .disabledEventFlag  = EventFlag_M5S02_PickupSafeKey,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 9,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 4, // `func_800D4DF8`
    },
    {
        .requiredEventFlag  = EventFlag_M5S02_UsedSafeKey,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 11,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 7, // `func_800D519C`
    },
    {
        .requiredEventFlag  = EventFlag_M5S02_PickupSafeKey,
        .disabledEventFlag  = EventFlag_M5S02_UsedSafeKey,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Item,
        .pointOfInterestIdx = 11,
        .requiredItemId     = InventoryItemId_SafeKey,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 6, // `func_800D4E64`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 11,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 48,
        .flags_8_13           = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 5, // `func_800D4E24`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 12,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 8, // `func_800D5478`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 13,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 9, // `func_800D54A4`
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

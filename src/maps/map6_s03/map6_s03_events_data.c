#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[16] = {
    {
        .disabledEventFlag_2  = EventFlag_M6S03_HealthDrink0,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M6S03_HandgunBullets,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 11,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M6S03_HealthDrink1,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 12,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .requiredEventFlag_0 = EventFlag_426,
        .disabledEventFlag_2 = EventFlag_438,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_Fmv,
        .eventParam_8_5      = 9,
        .flags_8_13          = 2,
    },
    {
        .disabledEventFlag_2 = EventFlag_431,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_EventCallFunc,
        .eventParam_8_5      = 3, // `func_800D822C`
    },
    {
        .requiredEventFlag_0 = EventFlag_431,
        .disabledEventFlag_2 = EventFlag_432,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadRoom,
    },
    {
        .disabledEventFlag_2  = EventFlag_433,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800D84EC`
    },
    {
        .disabledEventFlag_2  = EventFlag_433,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 3,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800D84EC`
    },
    {
        .disabledEventFlag_2  = EventFlag_433,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800D84EC`
    },
    {
        .requiredEventFlag_0 = EventFlag_433,
        .triggerType_4_0     = TriggerType_None,
        .sysState_8_0        = SysState_LoadOverlay,
        .eventParam_8_5      = 7,
        .mapOverlayIdx_8_25  = MapOverlayId_MAP6_S04,
    },
    {
        .disabledEventFlag_2  = EventFlag_434,
        .triggerType_4_0      = TriggerType_TouchAabb,
        .activationType_4_4   = TriggerActivationType_Exclusive,
        .pointOfInterestIdx_5 = 5,
        .sysState_8_0         = SysState_EventSetFlag,
    },
    {
        .disabledEventFlag_2  = EventFlag_435,
        .triggerType_4_0      = TriggerType_TouchAabb,
        .activationType_4_4   = TriggerActivationType_Exclusive,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_EventSetFlag,
    },
    {
        .disabledEventFlag_2  = EventFlag_M6S03_PickupMap,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 8,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 5, // `MapEvent_MapTake`
    },
    {
        .triggerType_4_0    = TriggerType_TouchObbFacing,
        .activationType_4_4 = TriggerActivationType_Button,
        .sysState_8_0       = SysState_ReadMessage,
        .eventParam_8_5     = 16,
    },
    {
        .requiredEventFlag_0  = EventFlag_435,
        .disabledEventFlag_2  = EventFlag_MapMark_FogHospital1F_MedicineRoomBotArrows,
        .triggerType_4_0      = TriggerType_TouchAabb,
        .activationType_4_4   = TriggerActivationType_Exclusive,
        .pointOfInterestIdx_5 = 9,
        .sysState_8_0         = SysState_EventSetFlag,
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

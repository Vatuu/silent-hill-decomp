#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[16] = {
    {
        .disabledEventFlag  = EventFlag_M6S03_HealthDrink0,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_EventCallback,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M6S03_HandgunBullets,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 11,
        .sysState         = SysState_EventCallback,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .disabledEventFlag  = EventFlag_M6S03_HealthDrink1,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 12,
        .sysState         = SysState_EventCallback,
        .eventParam       = 2, // `MapEvent_CommonItemTake`
    },
    {
        .requiredEventFlag = EventFlag_426,
        .disabledEventFlag = EventFlag_438,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_Fmv,
        .eventParam      = 9,
        .flags_8_13          = 2,
    },
    {
        .disabledEventFlag = EventFlag_431,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_EventCallback,
        .eventParam      = 3, // `func_800D822C`
    },
    {
        .requiredEventFlag = EventFlag_431,
        .disabledEventFlag = EventFlag_432,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadRoom,
    },
    {
        .disabledEventFlag  = EventFlag_433,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_EventCallback,
        .eventParam       = 4, // `func_800D84EC`
    },
    {
        .disabledEventFlag  = EventFlag_433,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 3,
        .sysState         = SysState_EventCallback,
        .eventParam       = 4, // `func_800D84EC`
    },
    {
        .disabledEventFlag  = EventFlag_433,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_EventCallback,
        .eventParam       = 4, // `func_800D84EC`
    },
    {
        .requiredEventFlag = EventFlag_433,
        .triggerType     = TriggerType_None,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 7,
        .mapIdx  = MapIdx_MAP6_S04,
    },
    {
        .disabledEventFlag  = EventFlag_434,
        .triggerType      = TriggerType_TouchAabb,
        .activationType   = TriggerActivationType_Exclusive,
        .pointOfInterestIdx = 5,
        .sysState         = SysState_EventSetFlag,
    },
    {
        .disabledEventFlag  = EventFlag_435,
        .triggerType      = TriggerType_TouchAabb,
        .activationType   = TriggerActivationType_Exclusive,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_EventSetFlag,
    },
    {
        .disabledEventFlag  = EventFlag_M6S03_PickupMap,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 8,
        .sysState         = SysState_EventCallback,
        .eventParam       = 5, // `MapEvent_MapTake`
    },
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 16,
    },
    {
        .requiredEventFlag  = EventFlag_435,
        .disabledEventFlag  = EventFlag_MapMark_FogHospital1F_MedicineRoomBotArrows,
        .triggerType      = TriggerType_TouchAabb,
        .activationType   = TriggerActivationType_Exclusive,
        .pointOfInterestIdx = 9,
        .sysState         = SysState_EventSetFlag,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[28] = {
    {
        .disabledEventFlag_2  = EventFlag_M2S04_ShotgunShells0,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 24,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag_2  = EventFlag_M2S04_HandgunBullets0,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 25,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag_2  = EventFlag_M2S04_HandgunBullets1,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 26,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag_2  = EventFlag_M2S04_ShotgunShells1,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 27,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag_2  = EventFlag_M2S04_HandgunBullets2,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 28,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag_2  = EventFlag_M2S04_HandgunBullets3,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 29,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag_2  = EventFlag_M2S04_RifleShells,
        .triggerType_4_0      = TriggerType_TouchFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 30,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 2, // `func_800CCF9C`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 10,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 9,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 11,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 9,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 20,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 9,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 21,
        .sysState_8_0         = SysState_SaveMenu1,
        .eventParam_8_5       = 9,
    },
    {
        .disabledEventFlag_2  = EventFlag_M1S02_PickupShotgun,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 22,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 6, // `MapEvent_ShotgunTake`
    },
    {
        .disabledEventFlag_2  = EventFlag_M1S02_PickupShotgun,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 23,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 6, // `MapEvent_ShotgunTake`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 13,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 24,
    },
    {
        .disabledEventFlag_2  = EventFlag_M2S00_PickupMap,
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 12,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 5, // `MapEvent_MapTake`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 4,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 9,
        .field_8_19           = 2,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP2_S02,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 7,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 3, // `func_800CD050`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 8,
        .sysState_8_0         = SysState_EventCallFunc,
        .eventParam_8_5       = 4, // `func_800CD088`
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 2,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 5,
        .field_8_19           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 5,
        .sysState_8_0         = SysState_LoadRoom,
        .eventParam_8_5       = 2,
        .field_8_19           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 3,
        .sysState_8_0         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 6,
        .sysState_8_0         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 16,
        .sysState_8_0         = SysState_LoadOverlay,
        .eventParam_8_5       = 17,
        .field_8_19           = 13,
        .mapOverlayIdx_8_25   = MapOverlayId_MAP4_S02,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 18,
        .sysState_8_0         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 19,
        .sysState_8_0         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 14,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 25,
    },
    {
        .triggerType_4_0      = TriggerType_TouchObbFacing,
        .activationType_4_4   = TriggerActivationType_Button,
        .pointOfInterestIdx_5 = 15,
        .sysState_8_0         = SysState_ReadMessage,
        .eventParam_8_5       = 25,
    },
    {
        .triggerType_4_0 = TriggerType_EndOfArray,
    },
};

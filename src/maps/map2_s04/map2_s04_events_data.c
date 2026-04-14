#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[28] = {
    {
        .disabledEventFlag  = EventFlag_M2S04_ShotgunShells0,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 24,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag  = EventFlag_M2S04_HandgunBullets0,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 25,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag  = EventFlag_M2S04_HandgunBullets1,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 26,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag  = EventFlag_M2S04_ShotgunShells1,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 27,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag  = EventFlag_M2S04_HandgunBullets2,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 28,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag  = EventFlag_M2S04_HandgunBullets3,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 29,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `func_800CCF9C`
    },
    {
        .disabledEventFlag  = EventFlag_M2S04_RifleShells,
        .triggerType      = TriggerType_TouchFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 30,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 2, // `func_800CCF9C`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 10,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 9,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 11,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 9,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 20,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 9,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 21,
        .sysState         = SysState_SaveMenu1,
        .eventParam       = 9,
    },
    {
        .disabledEventFlag  = EventFlag_M1S02_PickupShotgun,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 22,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 6, // `MapEvent_ShotgunTake`
    },
    {
        .disabledEventFlag  = EventFlag_M1S02_PickupShotgun,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 23,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 6, // `MapEvent_ShotgunTake`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 13,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 24,
    },
    {
        .disabledEventFlag  = EventFlag_M2S00_PickupMap,
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 12,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 5, // `MapEvent_MapTake`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 4,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx   = MapIdx_MAP2_S02,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 7,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 3, // `func_800CD050`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 8,
        .sysState         = SysState_EventCallFunc,
        .eventParam       = 4, // `func_800CD088`
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 2,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 5,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 5,
        .sysState         = SysState_LoadRoom,
        .eventParam       = 2,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 3,
        .sysState         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 6,
        .sysState         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 16,
        .sysState         = SysState_LoadOverlay,
        .eventParam       = 17,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .mapIdx   = MapIdx_MAP4_S02,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 18,
        .sysState         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 19,
        .sysState         = SysState_EventCallFunc,
        .flags_8_13           = 1,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 14,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 25,
    },
    {
        .triggerType      = TriggerType_TouchObbFacing,
        .activationType   = TriggerActivationType_Button,
        .pointOfInterestIdx = 15,
        .sysState         = SysState_ReadMessage,
        .eventParam       = 25,
    },
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[28] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M2S04_ShotgunShells0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 24,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800CCF9C`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M2S04_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800CCF9C`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M2S04_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800CCF9C`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M2S04_ShotgunShells1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800CCF9C`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M2S04_HandgunBullets2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800CCF9C`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_M2S04_HandgunBullets3,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800CCF9C`
    },
    // [6]
    {
        .completeEventFlag = EventFlag_M2S04_RifleShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800CCF9C`
    },
    // [7]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 10,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 9,
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 9,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 20,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 9,
    },
    // [10]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 21,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 9,
    },
    // [11]
    {
        .completeEventFlag = EventFlag_M1S02_PickupShotgun,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_ShotgunTake`
    },
    // [12]
    {
        .completeEventFlag = EventFlag_M1S02_PickupShotgun,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 23,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_ShotgunTake`
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 13,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 24,
    },
    // [14]
    {
        .completeEventFlag = EventFlag_M2S00_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_PaperMapTake`
    },
    // [15]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 4,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP2_S02,
    },
    // [16]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 7,
        .sysState       = SysState_EventCallback,
        .eventParam     = 3, // `func_800CD050`
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 8,
        .sysState       = SysState_EventCallback,
        .eventParam     = 4, // `func_800CD088`
    },
    // [18]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 2,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 5,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
    },
    // [19]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 5,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 2,
        .sfxPairIdx_8_19 = SfxPairIdx_1,
    },
    // [20]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 3,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [21]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 6,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [22]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 16,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 17,
        .sfxPairIdx_8_19 = SfxPairIdx_13,
        .mapIdx          = MapIdx_MAP4_S02,
    },
    // [23]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 18,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [24]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 19,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [25]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 14,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 25,
    },
    // [26]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 15,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 25,
    },
    // [27]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

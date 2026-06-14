#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[42] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M2S02_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800E9E10`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M2S02_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800E9E10`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M2S02_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800E9E10`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M2S02_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800E9E10`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M2S02_HealthDrink2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800E9E10`
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_352,
        .completeEventFlag = EventFlag_191,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800E9EAC`
    },
    // [6]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 3,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 4,
    },
    // [7]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 5,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 6,
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_351,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_M3S06_PickupAntiqueShopKey,
        .completeEventFlag = EventFlag_M2S02_AntiqueShopOpen,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800E9D54`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_M3S06_PickupAntiqueShopKey,
        .completeEventFlag = EventFlag_M2S02_AntiqueShopOpen,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 7,
        .requiredItemId    = InvItemId_AntiqueShopKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800E9D54`
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_M2S02_AntiqueShopOpen,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .mapIdx            = MapIdx_MAP4_S01,
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 7,
        .sysState       = SysState_EventCallback,
        .eventParam     = 1, // `MapEvent_DoorLocked`
        .flags_8_13     = 1,
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_191,
        .completeEventFlag = EventFlag_193,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 24,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 33,
        .mapIdx            = MapIdx_MAP2_S00,
    },
    // [14]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 24,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 25,
        .mapIdx      = MapIdx_MAP2_S00,
    },
    // [15]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 20,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 23,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP2_S04,
    },
    // [16]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 21,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 23,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP2_S04,
    },
    // [17]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 22,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 23,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP2_S04,
    },
    // [18]
    {
        .requiredEventFlag = EventFlag_295,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 19,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .mapIdx            = MapIdx_MAP3_S06,
    },
    // [19]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 17,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 19,
        .sfxPairIdx_8_19 = SfxPairIdx_2,
        .mapIdx          = MapIdx_MAP3_S00,
    },
    // [20]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 10,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 13,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [21]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 11,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 13,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [22]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 12,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 13,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [23]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 14,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [24]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 15,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [25]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 16,
        .sysState        = SysState_LoadRoom,
        .eventParam      = 9,
        .sfxPairIdx_8_19 = SfxPairIdx_16,
    },
    // [26]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 18,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_346,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 26,
        .sysState          = SysState_EventSetFlag,
    },
    // [28]
    {
        .requiredEventFlag = EventFlag_346,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 27,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 28,
    },
    // [29]
    {
        .requiredEventFlag = EventFlag_191,
        .completeEventFlag = EventFlag_194,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 29,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 30,
        .flags_8_13        = 2,
    },
    // [30]
    {
        .requiredEventFlag = EventFlag_194,
        .completeEventFlag = EventFlag_189,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800E9FDC`
    },
    // [31]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 29,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 30,
    },
    // [32]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 31,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 16,
    },
    // [33]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 34,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 17,
    },
    // [34]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 32,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [35]
    {
        .completeEventFlag = EventFlag_MapMark_FogCentralTown_CrichtonStTotBigCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 36,
        .sysState          = SysState_EventSetFlag,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_MapMark_FogCentralTown_CrichtonStBotBigCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 37,
        .sysState          = SysState_EventSetFlag,
    },
    // [37]
    {
        .completeEventFlag = EventFlag_MapMark_FogCentralTown_SaganStBigCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 38,
        .sysState          = SysState_EventSetFlag,
    },
    // [38]
    {
        .completeEventFlag = EventFlag_MapMark_FogCentralTown_KoontzStBigCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 39,
        .sysState          = SysState_EventSetFlag,
    },
    // [39]
    {
        .completeEventFlag = EventFlag_MapMark_FogCentralTown_SimmonsStBigCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 40,
        .sysState          = SysState_EventSetFlag,
    },
    // [40]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 35,
        .sysState       = SysState_EventCallback,
        .flags_8_13     = 1,
    },
    // [41]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

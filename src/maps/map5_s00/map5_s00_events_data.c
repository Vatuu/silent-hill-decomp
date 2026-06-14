#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[52] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M5S00_ShotgunShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M5S00_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M5S00_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M5S00_RifleShells,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M5S00_FirstAidKit0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_M5S00_FirstAidKit1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [6]
    {
        .completeEventFlag = EventFlag_M5S00_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_M5S00_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 34,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 21,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 35,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 21,
    },
    // [10]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 36,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 21,
    },
    // [11]
    {
        .completeEventFlag = EventFlag_355,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D732C`
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 22,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 19,
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D75FC`
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 24,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D75FC`
    },
    // [15]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 25,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D75FC`
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_356,
        .completeEventFlag = EventFlag_357,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 26,
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 26,
        .sysState       = SysState_EventCallback,
        .eventParam     = 8, // `func_800D7940`
    },
    // [18]
    {
        .requiredEventFlag = EventFlag_357,
        .completeEventFlag = EventFlag_356,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 23,
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_360,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `func_800D7F88`
    },
    // [20]
    {
        .requiredEventFlag = EventFlag_359,
        .completeEventFlag = EventFlag_358,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 27,
    },
    // [21]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 27,
        .sysState       = SysState_EventCallback,
        .eventParam     = 9, // `func_800D7C84`
    },
    // [22]
    {
        .requiredEventFlag = EventFlag_358,
        .completeEventFlag = EventFlag_359,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 31,
        .mapIdx            = MapIdx_MAP5_S01,
    },
    // [23]
    {
        .completeEventFlag = EventFlag_M5S00_PickupSewerKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `MapEvent_SewerKeyTake`
    },
    // [24]
    {
        .completeEventFlag = EventFlag_354,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D6B00`
    },
    // [25]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSewer1F_RightMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 6,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [26]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSewer1F_RightMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 5,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_RightMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D69DC`
        .flags_8_13        = 1,
    },
    // [28]
    {
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_RightMidLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `func_800D6888`
        .flags_8_13        = 1,
    },
    // [29]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSewer1F_MidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 9,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [30]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSewer1F_MidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 10,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [31]
    {
        .requiredEventFlag = EventFlag_M5S00_PickupSewerKey,
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_MidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D69DC`
        .flags_8_13        = 1,
    },
    // [32]
    {
        .requiredEventFlag = EventFlag_M5S00_PickupSewerKey,
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_MidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 10,
        .requiredItemId    = InvItemId_SewerKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D69DC`
        .flags_8_13        = 1,
    },
    // [33]
    {
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_MidLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `func_800D6888`
        .flags_8_13        = 1,
    },
    // [34]
    {
        .requiredEventFlag = EventFlag_MapMark_527,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 15,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [35]
    {
        .requiredEventFlag = EventFlag_MapMark_527,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [36]
    {
        .requiredEventFlag = EventFlag_354,
        .completeEventFlag = EventFlag_MapMark_527,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D69DC`
        .flags_8_13        = 1,
    },
    // [37]
    {
        .requiredEventFlag = EventFlag_354,
        .completeEventFlag = EventFlag_MapMark_527,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 14,
        .requiredItemId    = InvItemId_SewerExitKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `func_800D69DC`
        .flags_8_13        = 1,
    },
    // [38]
    {
        .completeEventFlag = EventFlag_1390,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `func_800D6888`
        .flags_8_13        = 1,
    },
    // [39]
    {
        .completeEventFlag = EventFlag_M5S00_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 32,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `MapEvent_PaperMapTake`
    },
    // [40]
    {
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_RightTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [41]
    {
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_RightTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 3,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [42]
    {
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_RightBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [43]
    {
        .completeEventFlag = EventFlag_MapMark_FogSewer1F_RightBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [44]
    {
        .completeEventFlag = EventFlag_MapMark_AltSewer_BigCross,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 17,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [45]
    {
        .completeEventFlag = EventFlag_MapMark_AltSewer_BigCross,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 16,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [46]
    {
        .completeEventFlag = EventFlag_1395,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 19,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [47]
    {
        .completeEventFlag = EventFlag_1395,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 19,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 18,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [48]
    {
        .completeEventFlag = EventFlag_1397,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 20,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 21,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [49]
    {
        .completeEventFlag = EventFlag_1397,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 20,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [50]
    {
        .completeEventFlag = EventFlag_1398,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 37,
        .sysState          = SysState_EventSetFlag,
    },
    // [51]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

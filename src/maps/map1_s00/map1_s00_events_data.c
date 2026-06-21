#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[101] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M1S00_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 94,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M1S00_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 95,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M1S00_HandgunBullets2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 96,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M1S00_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 97,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M1S00_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 98,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [5]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 89,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 4,
    },
    // [6]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 91,
        .sysState       = SysState_EventCallback,
        .eventParam     = 21, // `func_800D9254`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_M1S00_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 90,
        .sysState          = SysState_EventCallback,
        .eventParam        = 20, // `MapEvent_TownMapTake`
    },
    // [8]
    {
        .requiredEventFlag = EventFlag_73,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 23, // `MapEvent_Boiler2`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [9]
    {
        .requiredEventFlag = EventFlag_72,
        .completeEventFlag = EventFlag_73,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 18, // `MapEvent_Boiler0`
    },
    // [10]
    {
        .completeEventFlag = EventFlag_72,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 19, // `MapEvent_Boiler1`
    },
    // [11]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 31,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 32,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [12]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 32,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 33,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [13]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 29,
        .sysState       = SysState_EventCallback,
        .eventParam     = 17, // `func_800D8CC4`
    },
    // [14]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ReceptionQuestion,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 24,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `func_800D853C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [15]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ReceptionQuestion,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800D8570`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [16]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ReceptionQuestion,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_EventCallback,
        .eventParam        = 14, // `func_800D85A4`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [17]
    {
        .requiredEventFlag = EventFlag_73,
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ClockTowerCircle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 20,
        .sfxPairIdx_8_19   = SfxPairIdx_3,
    },
    // [18]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ClockTowerCircle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `MapEvent_ClockTowerInspect`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [19]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 20,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 21,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [20]
    {
        .completeEventFlag = EventFlag_184,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 19,
        .sysState          = SysState_EventCallback,
        .eventParam        = 22, // `func_800D928C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [21]
    {
        .requiredEventFlag = EventFlag_184,
        .completeEventFlag = EventFlag_78,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 23,
        .transitionFlags   = AreaTransitionFlag_SkipFadeIn,
    },
    // [22]
    {
        .requiredEventFlag = EventFlag_78,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 15, // `func_800D85D8`
    },
    // [23]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_EventCallback,
        .eventParam     = 16, // `func_800D8948`
    },
    // [24]
    {
        .requiredEventFlag = EventFlag_79,
        .completeEventFlag = EventFlag_82,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 19,
    },
    // [25]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 17,
        .sysState       = SysState_EventCallback,
        .eventParam     = 16, // `func_800D8948`
    },
    // [26]
    {
        .requiredEventFlag = EventFlag_80,
        .completeEventFlag = EventFlag_82,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 21,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_185,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_EventCallback,
        .eventParam        = 22, // `func_800D928C`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [28]
    {
        .requiredEventFlag = EventFlag_185,
        .completeEventFlag = EventFlag_81,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 23,
        .transitionFlags   = AreaTransitionFlag_SkipFadeIn,
    },
    // [29]
    {
        .requiredEventFlag = EventFlag_81,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 15, // `func_800D85D8`
    },
    // [30]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 22,
        .sysState        = SysState_LoadOverlay,
        .eventParam      = 18,
        .sfxPairIdx_8_19 = SfxPairIdx_3,
        .mapIdx          = MapIdx_MAP1_S02,
    },
    // [31]
    {
        .requiredEventFlag = EventFlag_71,
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ClockTowerCircle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_GoldenSunFilledReceptacleInspect`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [32]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ClockTowerCircle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `MapEvent_GoldenSunEmptyReceptableInspect`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [33]
    {
        .completeEventFlag = EventFlag_71,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 14,
        .requiredItemId    = InvItemId_GoldMedallion,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `MapEvent_GoldenSunItemUse`
    },
    // [34]
    {
        .requiredEventFlag = EventFlag_72,
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ClockTowerCircle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `MapEvent_SilverMoonFilledReceptacleInspect`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [35]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ClockTowerCircle,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_SilverMoonEmptyReceptableInspect`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_72,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 15,
        .requiredItemId    = InvItemId_SilverMedallion,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `MapEvent_SilverMoonItemUse`
    },
    // [37]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 1,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 26,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [38]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 2,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 26,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [39]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_LobbyArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 33,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [40]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_LobbyArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 33,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 38,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
    },
    // [41]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_UntitledLobbyTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 49,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [42]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_CourtyardBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 3,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [43]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_CourtyardBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 5,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [44]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool1F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 50,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [45]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool1F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 50,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 34,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [46]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 50,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [47]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotRightCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [48]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool1F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 65,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [49]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool1F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 65,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 35,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [50]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 65,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [51]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotLeftCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [52]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_InfirmaryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 40,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [53]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_InfirmaryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 37,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [54]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ReceptionArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 36,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 39,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [55]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ReceptionArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 36,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [56]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool1F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 51,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [57]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool1F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 41,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [58]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [59]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopRightCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [60]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 66,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [61]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 42,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [62]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_StorageBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [63]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_UntitledLobbyBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 48,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
    },
    // [64]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_UntitledLobbyBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 48,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 45,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [65]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_HallLeftBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [66]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_CourtyardTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [67]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_CourtyardTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 6,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [68]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 52,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 59,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [69]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 59,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 52,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [70]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 53,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 60,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [71]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 60,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 53,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [72]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 54,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 62,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [73]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 62,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 54,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [74]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 63,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [75]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 63,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 55,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [76]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 64,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 61,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [77]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 61,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 64,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [78]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_HallMidBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 56,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [79]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_WomensBathroomArrow,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [80]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_WomensBathroomArrow,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 67,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [81]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_MensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 68,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [82]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_MensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 68,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [83]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotTeachersRoomBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 69,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [84]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotTeachersRoomTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 70,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [85]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopTeachersRoomBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 71,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [86]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopTeachersRoomTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 72,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [87]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchoolBF_StorageBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 82,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [88]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchoolBF_BoilerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 83,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 85,
        .sfxPairIdx_8_19   = SfxPairIdx_17,
    },
    // [89]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchoolBF_BoilerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 85,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 83,
        .sfxPairIdx_8_19   = SfxPairIdx_17,
        .field_8_24        = 1,
    },
    // [90]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 79,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 11,
        .mapIdx      = MapIdx_MAP1_S01,
    },
    // [91]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 80,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 10,
    },
    // [92]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 86,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 9,
    },
    // [93]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 81,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 12,
        .mapIdx      = MapIdx_MAP1_S01,
    },
    // [94]
    {
        .completeEventFlag = EventFlag_594,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 28,
        .sysState          = SysState_EventSetFlag,
    },
    // [95]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 26,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
    },
    // [96]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 87,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [97]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 88,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [98]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 92,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [99]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 93,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
    },
    // [100]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

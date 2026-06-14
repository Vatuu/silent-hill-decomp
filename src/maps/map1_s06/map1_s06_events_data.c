#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[49] = {
    // [0]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 49,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 4,
    },
    // [1]
    {
        .completeEventFlag = EventFlag_133,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_Fmv,
        .eventParam        = 14,
        .flags_8_13        = 2,
    },
    // [2]
    {
        .completeEventFlag = EventFlag_134,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `func_800D5614`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M1S06_PickupKGordonKey,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D5B98`
    },
    // [4]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 11,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 19,
        .flags_8_13     = 1,
    },
    // [5]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 20,
        .flags_8_13     = 1,
    },
    // [6]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 13,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 21,
        .flags_8_13     = 1,
    },
    // [7]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 50,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800D6338`
    },
    // [8]
    {
        .completeEventFlag = EventFlag_M1S00_PickupMap,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `MapEvent_PaperMapTake`
    },
    // [9]
    {
        .completeEventFlag = EventFlag_140,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 1,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_140,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 1,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 4,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .mapIdx            = MapIdx_MAP2_S00,
    },
    // [11]
    {
        .completeEventFlag = EventFlag_141,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_141,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 2,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 3,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .mapIdx            = MapIdx_MAP2_S00,
    },
    // [13]
    {
        .completeEventFlag = EventFlag_139,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_139,
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_LobbyArrows,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventSetFlag,
    },
    // [15]
    {
        .requiredEventFlag = EventFlag_139,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 19,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 14,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_139,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 19,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
    },
    // [17]
    {
        .completeEventFlag = EventFlag_138,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [18]
    {
        .requiredEventFlag = EventFlag_138,
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotRightCorridorArrows,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventSetFlag,
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_138,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 15,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 22,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [20]
    {
        .requiredEventFlag = EventFlag_138,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 22,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 15,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [21]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightCorridorBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [22]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_CourtyardBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [23]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotLeftCorridorBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [24]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_InfirmaryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 21,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [25]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_InfirmaryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 18,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [26]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_ReceptionBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopRightCorridorBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 23,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [28]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightCorridorBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [29]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotClassRoomBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 24,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [30]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightClassRoomBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [31]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_BotClassRoomTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 25,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [32]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightClassRoomTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [33]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopClassRoomBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [34]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightClassRoomBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [35]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_TopClassRoomTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightClassRoomTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [37]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool1F_HallMidBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [38]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LibraryBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [39]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchoolBF_StorageBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [40]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchoolBF_BoilerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 37,
        .sfxPairIdx_8_19   = SfxPairIdx_17,
    },
    // [41]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchoolBF_BoilerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 35,
        .sfxPairIdx_8_19   = SfxPairIdx_17,
        .field_8_24        = 1,
    },
    // [42]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 32,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 7,
    },
    // [43]
    {
        .completeEventFlag = EventFlag_135,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 38,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 6,
        .flags_8_13        = 2,
    },
    // [44]
    {
        .requiredEventFlag = EventFlag_135,
        .completeEventFlag = EventFlag_M1S06_ChurchMarkedOnMap,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D5DD8`
    },
    // [45]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 38,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 6,
    },
    // [46]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 31,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 8,
    },
    // [47]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 46,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 9,
    },
    // [48]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

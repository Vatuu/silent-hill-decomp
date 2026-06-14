#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[104] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M1S01_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 96,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D7214`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M1S01_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 97,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D7214`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M1S01_HealthDrink,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 98,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D7214`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M1S01_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 99,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D7214`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M1S01_HandgunBullets2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 100,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `func_800D7214`
    },
    // [5]
    {
        .requiredEventFlag = EventFlag_M1S01_PianoPuzzleSolved,
        .completeEventFlag = EventFlag_M1S01_PickupSilverMedallion,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `func_800D857C`
    },
    // [6]
    {
        .requiredEventFlag = EventFlag_M1S01_PianoPuzzleSolved,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `func_800D7EEC`
    },
    // [7]
    {
        .requiredEventFlag = EventFlag_71,
        .completeEventFlag = EventFlag_M1S01_PianoPuzzleSolved,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 16,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `func_800D7864`
    },
    // [8]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 16,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 26,
        .flags_8_13     = 1,
    },
    // [9]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 15,
        .sysState       = SysState_EventCallback,
        .eventParam     = 8, // `func_800D7830`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_74,
        .completeEventFlag = EventFlag_M1S01_PickupGoldMedallion,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `func_800D76F4`
    },
    // [11]
    {
        .requiredEventFlag = EventFlag_M1S01_PickupGoldMedallion,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 20,
        .flags_8_13        = 1,
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 12,
        .sysState       = SysState_EventCallback,
        .eventParam     = 4, // `func_800D72B0`
    },
    // [13]
    {
        .completeEventFlag = EventFlag_74,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 12,
        .requiredItemId    = InvItemId_Chemical,
        .sysState          = SysState_EventCallback,
        .eventParam        = 6, // `func_800D7308`
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_M1S01_PickupChemical,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 19,
        .flags_8_13        = 1,
    },
    // [15]
    {
        .completeEventFlag = EventFlag_M1S01_PickupChemical,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800D72DC`
    },
    // [16]
    {
        .requiredEventFlag = EventFlag_77,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `func_800D8794`
    },
    // [17]
    {
        .completeEventFlag = EventFlag_76,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 14,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800D87C0`
    },
    // [18]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 36,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [19]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 36,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 51,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [20]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 52,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 42,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [21]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 52,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [22]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 53,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 58,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [23]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 58,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 53,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [24]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 54,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 59,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [25]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 59,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 54,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [26]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 61,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [27]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 61,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 55,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [28]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 56,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 62,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [29]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 62,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 56,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [30]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LibraryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 57,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 64,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [31]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LibraryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 64,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 57,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [32]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_RightClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 60,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 63,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [33]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_RightClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 63,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 60,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [34]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LockerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 40,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [35]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LockerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 38,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_MusicRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 41,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [37]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_MusicRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 39,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [38]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool2F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 37,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [39]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool2F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 66,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [40]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [41]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotLeftCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .flags_8_13        = 1,
    },
    // [42]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopLeftArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 43,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [43]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopLeftArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 67,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [44]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_WomensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 68,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 3,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [45]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_WomensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 3,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 68,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [46]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_MensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 69,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 4,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [47]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_MensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 69,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [48]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotLeftClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 70,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 74,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [49]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotLeftClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 74,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 70,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [50]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotLeftClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 71,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 75,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [51]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_BotLeftClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 75,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 71,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [52]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopLeftClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 72,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 77,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [53]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopLeftClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 77,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 72,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [54]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopLeftClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 73,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 78,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [55]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_TopLeftClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 78,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 73,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [56]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LeftClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 76,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 79,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [57]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LeftClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 79,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 76,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [58]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_ReserveLibraryMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 65,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 48,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [59]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_ReserveLibraryMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 48,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 65,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [60]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool2F_LibraryReserveArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 47,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
    },
    // [61]
    {
        .requiredEventFlag = EventFlag_MapMark_FogSchool2F_LibraryReserveArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 47,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 44,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [62]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LibraryReserveArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 47,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .flags_8_13        = 1,
    },
    // [63]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LibraryReserveLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .flags_8_13        = 1,
    },
    // [64]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_ChemistryLabArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 49,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [65]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_ChemistryLabArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 49,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 45,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [66]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LabEquipmentRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 50,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
    },
    // [67]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_LabEquipmentRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 50,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 46,
        .sfxPairIdx_8_19   = SfxPairIdx_1,
        .field_8_24        = 1,
    },
    // [68]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 82,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 11,
    },
    // [69]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 10,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 7,
    },
    // [70]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchoolRF_RoofBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_EventCallback,
        .flags_8_13        = 1,
    },
    // [71]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 80,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 5,
        .mapIdx      = MapIdx_MAP1_S00,
    },
    // [72]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 81,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 6,
        .mapIdx      = MapIdx_MAP1_S00,
    },
    // [73]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_StatueOfHandSign,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 18,
        .sysState          = SysState_EventSetFlag,
    },
    // [74]
    {
        .completeEventFlag = EventFlag_MapMark_FogSchool2F_PianoSign,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 19,
        .sysState          = SysState_EventSetFlag,
    },
    // [75]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 21,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 34,
        .flags_8_13     = 1,
    },
    // [76]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 22,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [77]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 23,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [78]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 24,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 35,
        .flags_8_13     = 1,
    },
    // [79]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 25,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [80]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 26,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
        .flags_8_13     = 1,
    },
    // [81]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 27,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 37,
        .flags_8_13     = 1,
    },
    // [82]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 28,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 38,
        .flags_8_13     = 1,
    },
    // [83]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 29,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 39,
        .flags_8_13     = 1,
    },
    // [84]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 30,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 41,
        .flags_8_13     = 1,
    },
    // [85]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 31,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 41,
        .flags_8_13     = 1,
    },
    // [86]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 32,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
        .flags_8_13     = 1,
    },
    // [87]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 33,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
        .flags_8_13     = 1,
    },
    // [88]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 34,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 42,
        .flags_8_13     = 1,
    },
    // [89]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 35,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [90]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 94,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [91]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 95,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 36,
    },
    // [92]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 83,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 44,
    },
    // [93]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 84,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 44,
    },
    // [94]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 85,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [95]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 86,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [96]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 87,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 46,
    },
    // [97]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 88,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 44,
    },
    // [98]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 89,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [99]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 90,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 45,
    },
    // [100]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 91,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 44,
    },
    // [101]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 92,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 46,
    },
    // [102]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 93,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 46,
    },
    // [103]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

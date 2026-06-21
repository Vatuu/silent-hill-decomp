#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[121] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M1S02_Ampoule0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 107,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M1S02_ShotgunShells0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 108,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M1S02_ShotgunShells1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 109,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M1S02_FirstAidKit0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 110,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M1S02_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 111,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_M1S02_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 112,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [6]
    {
        .completeEventFlag = EventFlag_M1S02_HandgunBullets2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 113,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_M1S02_Ampoule1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 114,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [8]
    {
        .completeEventFlag = EventFlag_M1S02_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 115,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [9]
    {
        .completeEventFlag = EventFlag_M1S02_FirstAidKit1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 116,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [10]
    {
        .completeEventFlag = EventFlag_M1S02_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 117,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_CommonItemTake`
    },
    // [11]
    {
        .completeEventFlag = EventFlag_91,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 1,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `func_800DA384`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [12]
    {
        .requiredEventFlag = EventFlag_225,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_EventCallback,
        .eventParam        = 21, // `func_800DD420`
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_M1S03_KeyDownTheDrain,
        .completeEventFlag = EventFlag_M1S02_PickupClassroomKey,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 103,
        .sysState          = SysState_EventCallback,
        .eventParam        = 20, // `MapEvent_ClassroomKeyItemTake`
    },
    // [14]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 101,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 4,
    },
    // [15]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 102,
        .sysState       = SysState_SaveMenu1,
        .eventParam     = 4,
    },
    // [16]
    {
        .completeEventFlag = EventFlag_118,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 40,
        .sysState          = SysState_EventCallback,
        .eventParam        = 18, // `func_800DC1E0`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [17]
    {
        .completeEventFlag = EventFlag_119,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 39,
        .sysState          = SysState_EventCallback,
        .eventParam        = 18, // `func_800DC1E0`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [18]
    {
        .completeEventFlag = EventFlag_120,
        .triggerType       = TriggerType_TouchAabb,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .eventParam        = 19, // `func_800DCF00`
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_120,
        .triggerType       = TriggerType_Tick,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 18,
        .mapIdx            = MapIdx_MAP1_S05,
    },
    // [20]
    {
        .completeEventFlag = EventFlag_96,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_EventCallback,
        .eventParam        = 15, // `func_800DBB7C`
    },
    // [21]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 38,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 52,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [22]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 36,
        .sysState       = SysState_EventCallback,
        .eventParam     = 16, // `func_800DBF88`
    },
    // [23]
    {
        .requiredEventFlag = EventFlag_96,
        .completeEventFlag = EventFlag_M1S02_PickupShotgun,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_EventCallback,
        .eventParam        = 17, // `func_800DBFC8`
    },
    // [24]
    {
        .completeEventFlag = EventFlag_M1S02_PickupRubberBall,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 33,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800DB33C`
    },
    // [25]
    {
        .completeEventFlag = EventFlag_M1S02_PickupRubberBall,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `func_800DB33C`
    },
    // [26]
    {
        .completeEventFlag = EventFlag_98,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 91,
        .sysState          = SysState_EventCallback,
        .eventParam        = 14, // `MapEvent_CutscenePhoneCall`
    },
    // [27]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 42,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 50,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [28]
    {
        .completeEventFlag = EventFlag_M1S02_PickupPictureCard,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `func_800DB310`
    },
    // [29]
    {
        .completeEventFlag = EventFlag_M1S02_PickupPictureCard,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `func_800DB310`
    },
    // [30]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 31,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 45,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [31]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 32,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 45,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [32]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_SecretDoorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 12,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 26,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
    },
    // [33]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_SecretDoorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 12,
        .sfxPairIdx_8_19   = SfxPairIdx_2,
        .field_8_24        = 1,
    },
    // [34]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_SecretDoorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_EventCallback,
        .eventParam        = 10, // `MapEvent_DoorWithHorizontalSlotInteract`
    },
    // [35]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Item,
        .mapPointIdx    = 26,
        .requiredItemId = InvItemId_PictureCard,
        .sysState       = SysState_EventCallback,
        .eventParam     = 11, // `func_800DB058`
    },
    // [36]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 19,
        .sysState       = SysState_EventCallback,
        .eventParam     = 8, // `func_800DA8F8`
    },
    // [37]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 20,
        .sysState       = SysState_EventCallback,
        .eventParam     = 6, // `func_800DA9D4`
    },
    // [38]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 21,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `func_800DAA00`
    },
    // [39]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_LobbyTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 47,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 52,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
    },
    // [40]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_LobbyTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 52,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 47,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [41]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_LobbyBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 4,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [42]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_LobbyBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [43]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_CourtyardBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 6,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [44]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_CourtyardBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 8,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [45]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_CourtyardBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 8,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [46]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_CourtyardBotLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [47]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 48,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 64,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [48]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 64,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 48,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [49]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 49,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 79,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [50]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 79,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 49,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [51]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 79,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [52]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotLeftCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 49,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [53]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_InfirmaryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 54,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [54]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_InfirmaryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 54,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 51,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [55]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_ReceptionArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 50,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 53,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [56]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_ReceptionArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 53,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 50,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [57]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 65,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 55,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [58]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 65,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [59]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 65,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [60]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopRightCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [61]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_TopLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 56,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 80,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [62]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_TopLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 80,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 56,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [63]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 80,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [64]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopLeftCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 56,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [65]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_StorageArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 58,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 61,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [66]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_StorageArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 61,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 58,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [67]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_UntitledLobbyBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 59,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 62,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [68]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_UntitledLobbyBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 62,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 59,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [69]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_HallLeftArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 60,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 72,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [70]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_HallLeftArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 72,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 60,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [71]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_CourtyardTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 7,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [72]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_CourtyardTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 7,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 9,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [73]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 73,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [74]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 73,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 66,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [75]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotClassRoomTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [76]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotClassRoomTopBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 74,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [77]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 68,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 76,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [78]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 76,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 68,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [79]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 69,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 77,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [80]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 77,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 69,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [81]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_ClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 78,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 75,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [82]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_ClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 75,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 78,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [83]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_HallMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 70,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 71,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [84]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_HallMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 71,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 70,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [85]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_WomensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 81,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 10,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .mapIdx            = MapIdx_MAP1_S03,
    },
    // [86]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_WomensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 81,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [87]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_MensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 82,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 11,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [88]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_MensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 11,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 82,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [89]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotTeachersRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 83,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 87,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [90]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotTeachersRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 87,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 83,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [91]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotTeachersRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 84,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 88,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [92]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_BotTeachersRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 88,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 84,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [93]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopTeachersRoomBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 85,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [94]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopTeachersRoomBotBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 90,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [95]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopTeachersRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 86,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 91,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [96]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TopTeachersRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 91,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 86,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [97]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TeacherMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 89,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 92,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [98]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_TeacherMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 92,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 89,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [99]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchoolBF_StorageArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 96,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 98,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [100]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchoolBF_StorageArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 98,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 96,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [101]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchoolBF_BoilerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 97,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 17,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [102]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchoolBF_BoilerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 97,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [103]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_RightCorridorBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 28,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [104]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool1F_RightCorridorBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 27,
        .sfxPairIdx_8_19   = SfxPairIdx_8,
    },
    // [105]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_RightCorridorBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [106]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_RightCorridorBotLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [107]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 93,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 15,
        .mapIdx      = MapIdx_MAP1_S03,
    },
    // [108]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 94,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 14,
    },
    // [109]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 100,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 13,
    },
    // [110]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 95,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 16,
        .mapIdx      = MapIdx_MAP1_S03,
    },
    // [111]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_LeftMidCorridorBroken,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 22,
        .sysState          = SysState_EventSetFlag,
    },
    // [112]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_RightCorridorMidBroken,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 23,
        .sysState          = SysState_EventSetFlag,
    },
    // [113]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_UntitledLobbyTopCross,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 25,
        .sysState          = SysState_EventSetFlag,
    },
    // [114]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 43,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 46,
    },
    // [115]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 44,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 46,
    },
    // [116]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 46,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 48,
    },
    // [117]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 105,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 54,
    },
    // [118]
    {
        .triggerType    = TriggerType_TouchFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 104,
        .sysState       = SysState_ReadMessage,
        .eventParam     = 53,
    },
    // [119]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool1F_RightCorridorBotDots,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 106,
        .sysState          = SysState_EventSetFlag,
    },
    // [120]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

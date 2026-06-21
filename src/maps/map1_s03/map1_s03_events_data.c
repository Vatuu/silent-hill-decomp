#include "bodyprog/bodyprog.h"

s_EventData MAP_EVENTS[103] = {
    // [0]
    {
        .completeEventFlag = EventFlag_M1S03_ShotgunShells0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 84,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [1]
    {
        .completeEventFlag = EventFlag_M1S03_HandgunBullets0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 85,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [2]
    {
        .completeEventFlag = EventFlag_M1S03_HealthDrink0,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 86,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [3]
    {
        .completeEventFlag = EventFlag_M1S03_HandgunBullets1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 87,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [4]
    {
        .completeEventFlag = EventFlag_M1S03_HandgunBullets2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 88,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [5]
    {
        .completeEventFlag = EventFlag_M1S03_ShotgunShells1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 89,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [6]
    {
        .completeEventFlag = EventFlag_M1S03_HandgunBullets3,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 90,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [7]
    {
        .completeEventFlag = EventFlag_M1S03_HealthDrink1,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 91,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [8]
    {
        .completeEventFlag = EventFlag_M1S03_HealthDrink2,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 92,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [9]
    {
        .completeEventFlag = EventFlag_M1S03_FirstAidKit,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 93,
        .sysState          = SysState_EventCallback,
        .eventParam        = 5, // `MapEvent_CommonItemTake`
    },
    // [10]
    {
        .requiredEventFlag = EventFlag_97,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 23,
        .sysState          = SysState_EventCallback,
        .eventParam        = 9, // `MapEvent_TheMonsterLurksBookRead`
    },
    // [11]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 24,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 39,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [12]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 25,
        .sysState       = SysState_EventCallback,
        .eventParam     = 10, // `MapEvent_SplitHeadFairyTaleBookRead`
    },
    // [13]
    {
        .requiredEventFlag = EventFlag_M1S03_KeyDownTheDrain,
        .completeEventFlag = EventFlag_M1S02_PickupClassroomKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [14]
    {
        .requiredEventFlag = EventFlag_M1S03_KeyDownTheDrain,
        .completeEventFlag = EventFlag_M1S02_PickupClassroomKey,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [15]
    {
        .completeEventFlag = EventFlag_M1S03_KeyDownTheDrain,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 17,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [16]
    {
        .completeEventFlag = EventFlag_M1S03_KeyDownTheDrain,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 18,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [17]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 17,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [18]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 18,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [19]
    {
        .requiredEventFlag = EventFlag_M1S02_UsedRubberBall,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 19,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [20]
    {
        .requiredEventFlag = EventFlag_M1S02_UsedRubberBall,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 20,
        .sysState          = SysState_EventCallback,
        .eventParam        = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [21]
    {
        .completeEventFlag = EventFlag_M1S02_UsedRubberBall,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 19,
        .requiredItemId    = InvItemId_RubberBall,
        .sysState          = SysState_EventCallback,
        .eventParam        = 15, // `MapEvent_RubberBallUse`
    },
    // [22]
    {
        .completeEventFlag = EventFlag_M1S02_UsedRubberBall,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 20,
        .requiredItemId    = InvItemId_RubberBall,
        .sysState          = SysState_EventCallback,
        .eventParam        = 15, // `MapEvent_RubberBallUse`
    },
    // [23]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 19,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [24]
    {
        .triggerType    = TriggerType_TouchObbFacing,
        .activationType = TriggerActivationType_Button,
        .mapPointIdx    = 20,
        .sysState       = SysState_EventCallback,
        .eventParam     = 7, // `MapEvent_RoofDrainPuzzleInteract1`
    },
    // [25]
    {
        .requiredEventFlag = EventFlag_112,
        .completeEventFlag = EventFlag_M1S03_KeyDownTheDrain,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_EventCallback,
        .eventParam        = 8, // `MapEvent_DrainageValveInteract`
    },
    // [26]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchoolRF_ValveSign,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 21,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 31,
    },
    // [27]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 41,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [28]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 26,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [29]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 41,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [30]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotRightCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 26,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [31]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 32,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [32]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 32,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 42,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [33]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopRightCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 42,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [34]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopRightCorridorLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 32,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [35]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 43,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 48,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [36]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 48,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 43,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [37]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 44,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 49,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [38]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 49,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 44,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [39]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 51,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [40]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 45,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [41]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 51,
        .sysState          = SysState_EventCallback,
        .eventParam        = 2, // `MapEvent_DoorUnlocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [42]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomBotLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 45,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [43]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 52,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [44]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 52,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 46,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [45]
    {
        .requiredEventFlag = EventFlag_M1S02_PickupClassroomKey,
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `MapEvent_ClassroomKeyUse`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [46]
    {
        .requiredEventFlag = EventFlag_M1S02_PickupClassroomKey,
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 46,
        .requiredItemId    = InvItemId_ClassroomKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 4, // `MapEvent_ClassroomKeyUse`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [47]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopRightClassRoomTopLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 46,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [48]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LibraryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 47,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 54,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [49]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LibraryArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 54,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 47,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [50]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_RightClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 50,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 53,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [51]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_RightClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 53,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 50,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [52]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LockerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 28,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 30,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [53]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LockerRoomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 30,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 28,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [54]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_MusicRoomBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 29,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [55]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 56,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 27,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [56]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 27,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 56,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [57]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 57,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 33,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [58]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopLeftCorridorArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 33,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 57,
        .sfxPairIdx_8_19   = SfxPairIdx_13,
        .field_8_24        = 1,
    },
    // [59]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_WomensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 58,
        .sysState          = SysState_LoadOverlay,
        .eventParam        = 9,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .mapIdx            = MapIdx_MAP1_S02,
    },
    // [60]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_WomensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 9,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 58,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [61]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_MensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 59,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 10,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [62]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_MensBathroomArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 10,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 59,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [63]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotLeftClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 60,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 64,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [64]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotLeftClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 64,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 60,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [65]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotLeftClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 61,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 65,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [66]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_BotLeftClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 65,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 61,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [67]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopLeftClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 62,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 67,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [68]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopLeftClassRoomBotArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 67,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 62,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [69]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopLeftClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 63,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 68,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [70]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_TopLeftClassRoomTopArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 68,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 63,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [71]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LeftClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 66,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 69,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [72]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LeftClassRoomMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 69,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 66,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [73]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_ReserveLibraryMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 55,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 38,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [74]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_ReserveLibraryMidArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 38,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 55,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [75]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_LibraryReserveArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 37,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
    },
    // [76]
    {
        .requiredEventFlag = EventFlag_MapMark_AltSchool2F_LibraryReserveArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 37,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 34,
        .sfxPairIdx_8_19   = SfxPairIdx_12,
        .field_8_24        = 1,
    },
    // [77]
    {
        .requiredEventFlag = EventFlag_M1S03_PickupLibraryReserveKey,
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LibraryReserveArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_LibraryReserveKeyUse`
    },
    // [78]
    {
        .requiredEventFlag = EventFlag_M1S03_PickupLibraryReserveKey,
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LibraryReserveArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 34,
        .requiredItemId    = InvItemId_LibraryReserveKey,
        .sysState          = SysState_EventCallback,
        .eventParam        = 3, // `MapEvent_LibraryReserveKeyUse`
    },
    // [79]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LibraryReserveLocked,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 34,
        .sysState          = SysState_EventCallback,
        .eventParam        = 1, // `MapEvent_DoorLocked`
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [80]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_ChemistryLabBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 35,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [81]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LabEquipmentRoomBroken,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 36,
        .sysState          = SysState_EventCallback,
        .transitionFlags   = AreaTransitionFlag_UnfreezeWorld,
    },
    // [82]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 72,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 8,
    },
    // [83]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 7,
        .sysState    = SysState_LoadRoom,
        .eventParam  = 4,
    },
    // [84]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchoolRF_RoofArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 5,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 6,
        .sfxPairIdx_8_19   = SfxPairIdx_14,
    },
    // [85]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchoolRF_RoofArrows,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 6,
        .sysState          = SysState_LoadRoom,
        .eventParam        = 5,
        .sfxPairIdx_8_19   = SfxPairIdx_14,
    },
    // [86]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 70,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 2,
        .mapIdx      = MapIdx_MAP1_S02,
    },
    // [87]
    {
        .triggerType = TriggerType_TouchAabb,
        .mapPointIdx = 71,
        .sysState    = SysState_LoadOverlay,
        .eventParam  = 3,
        .mapIdx      = MapIdx_MAP1_S02,
    },
    // [88]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LeftCorridorMidBroken,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 11,
        .sysState          = SysState_EventSetFlag,
    },
    // [89]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_LeftCorridorMidArrows,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 12,
        .sysState          = SysState_EventSetFlag,
    },
    // [90]
    {
        .completeEventFlag = EventFlag_MapMark_AltSchool2F_RightCorridorMidBroken,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 13,
        .sysState          = SysState_EventSetFlag,
    },
    // [91]
    {
        .requiredEventFlag = EventFlag_M1S03_LockerOpened,
        .completeEventFlag = EventFlag_105,
        .triggerType       = TriggerType_TouchObb,
        .activationType    = TriggerActivationType_Exclusive,
        .mapPointIdx       = 77,
        .sysState          = SysState_EventCallback,
        .eventParam        = 13, // `MapEvent_LockerDeadBodyCutscene`
    },
    // [92]
    {
        .requiredEventFlag = EventFlag_M1S03_LockerOpened,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 76,
        .sysState          = SysState_EventCallback,
        .eventParam        = 11, // `MapEvent_OpenedCatLockerInspect`
    },
    // [93]
    {
        .completeEventFlag = EventFlag_M1S03_LockerOpened,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 76,
        .sysState          = SysState_EventCallback,
        .eventParam        = 12, // `MapEvent_UnopenedCatLockerInspect`
    },
    // [94]
    {
        .requiredEventFlag = EventFlag_106,
        .completeEventFlag = EventFlag_M1S03_PickupLibraryReserveKey,
        .triggerType       = TriggerType_TouchFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 82,
        .sysState          = SysState_EventCallback,
        .eventParam        = 14, // `MapEvent_LibraryReserveKeyItemTake`
    },
    // [95]
    {
        .requiredEventFlag = EventFlag_106,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 78,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 45,
    },
    // [96]
    {
        .requiredEventFlag = EventFlag_106,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 79,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 45,
    },
    // [97]
    {
        .requiredEventFlag = EventFlag_106,
        .triggerType       = TriggerType_TouchObbFacing,
        .activationType    = TriggerActivationType_Button,
        .mapPointIdx       = 80,
        .sysState          = SysState_ReadMessage,
        .eventParam        = 45,
    },
    // [98]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 73,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 42,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [99]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 74,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 42,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [100]
    {
        .triggerType     = TriggerType_TouchObbFacing,
        .activationType  = TriggerActivationType_Button,
        .mapPointIdx     = 75,
        .sysState        = SysState_ReadMessage,
        .eventParam      = 42,
        .transitionFlags = AreaTransitionFlag_UnfreezeWorld,
    },
    // [101]
    {
        .completeEventFlag = EventFlag_456,
        .triggerType       = TriggerType_TouchAabb,
        .activationType    = TriggerActivationType_Item,
        .mapPointIdx       = 83,
        .requiredItemId    = InvItemId_ChannelingStone,
        .sysState          = SysState_EventCallback,
        .eventParam        = 16, // `func_800DCDDC`
    },
    // [102]
    {
        .triggerType = TriggerType_EndOfArray,
    },
};

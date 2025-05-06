#ifndef _GAME_H
#define _GAME_H

#include "gpu.h"
#include "types.h"

#define TICKS_PER_SECOND 60 // Game has a variable timestep with 60 ticks max.

#define SCREEN_WIDTH                   320
#define SCREEN_HEIGHT                  240
#define FRAMEBUFFER_HEIGHT_PROGRESSIVE 224
#define FRAMEBUFFER_HEIGHT_INTERLACED  (FRAMEBUFFER_HEIGHT_PROGRESSIVE * 2)

#define CHARA_PROPERTY_COUNT_MAX 10
#define NPC_COUNT_MAX            6
#define INVENTORY_ITEM_COUNT_MAX 40
#define SAVEGAME_FOOTER_MAGIC    0xDCDC

/** @brief Converts a floating-point X screen position in percent to a fixed-point X screen coodinate. */
#define SCREEN_POSITION_X(percent) \
    (s32)((SCREEN_WIDTH) * ((percent) / 100.0f))

/** @brief Converts a floating-point Y screen position in percent to a fixed-point Y screen coodinate. */
#define SCREEN_POSITION_Y(percent) \
    (s32)((SCREEN_HEIGHT) * ((percent) / 100.0f))

/** @brief Color IDs used by strings displayed on the screen. */
typedef enum _ColorId
{
    ColorId_Gold      = 0,
    ColorId_DarkGrey  = 1,
    ColorId_Green0    = 2,
    ColorId_Nuclear   = 3,
    ColorId_Red       = 4,
    ColorId_Green1    = 5,
    ColorId_LightGrey = 6,
    ColorId_White     = 7
} e_ColorId;
    
typedef enum _PadButtonFlags
{
    Pad_Select       = 1 << 0,
    Pad_L3           = 1 << 1,
    Pad_R3           = 1 << 2,
    Pad_Start        = 1 << 3,
    Pad_DpadUp       = 1 << 4,
    Pad_DpadRight    = 1 << 5,
    Pad_DpadDown     = 1 << 6,
    Pad_DpadLeft     = 1 << 7,
    Pad_L2           = 1 << 8,
    Pad_R2           = 1 << 9,
    Pad_L1           = 1 << 10,
    Pad_R1           = 1 << 11,
    Pad_Triangle     = 1 << 12,
    Pad_Circle       = 1 << 13,
    Pad_Cross        = 1 << 14,
    Pad_Square       = 1 << 15,
    Pad_LStickUp2    = 1 << 16,
    Pad_LStickRight2 = 1 << 17,
    Pad_LStickDown2  = 1 << 18,
    Pad_LStickLeft2  = 1 << 19,
    Pad_RStickUp     = 1 << 20,
    Pad_RStickRight  = 1 << 21,
    Pad_RStickDown   = 1 << 22,
    Pad_RStickLeft   = 1 << 23,
    Pad_LStickUp     = 1 << 24,
    Pad_LStickRight  = 1 << 25,
    Pad_LStickDown   = 1 << 26,
    Pad_LStickLeft   = 1 << 27
} e_PadButtonFlags;

typedef enum _AnimFlags
{
    AnimFlag_None = 0,
    AnimFlag_Unk1 = 1 << 0,
    AnimFlag_Unk2 = 1 << 1
} e_AnimFlags;

/** @brief State IDs used by the main game loop. The values are used as indices into the 0x800A977C function array. */
typedef enum _GameState
{
    GameState_Unk0                = 0,
    GameState_KonamiLogo          = 1,
    GameState_KcetLogo            = 2,
    GameState_StartMovieIntro     = 3,
    GameState_DeathLoadScreen     = 4,
    GameState_MovieIntroAlternate = 5,
    GameState_MovieIntro          = 6,
    GameState_MainMenu            = 7,
    GameState_SaveScreen          = 8,
    GameState_MovieOpening        = 9,
    GameState_MainLoadScreen      = 10,
    GameState_InGame              = 11,
    GameState_MapEvent            = 12,
    GameState_ExitMovie           = 13,
    GameState_StatusScreen        = 14,
    GameState_MapScreen           = 15,
    GameState_Unk10               = 16,
    GameState_DebugMoviePlayer    = 17,
    GameState_OptionScreen        = 18,
    GameState_LoadStatusScreen    = 19,
    GameState_LoadMapScreen       = 20,
    GameState_Unk15               = 21,
    GameState_Unk16               = 22 /** Removed debug menu? Doesn't exist in function array, but `DebugMoviePlayer` state tries to switch to it. */
} e_GameState;

/** @brief State IDs used by `GameState_InGame`.
 * 
 * The values are used as indices into the 0x800A9A2C function array.
 */
typedef enum _SysState
{
    SysState_Gameplay       = 0,
    SysState_OptionsMenu    = 1,
    SysState_StatusMenu     = 2,
    SysState_Unk3           = 3,
    SysState_Fmv            = 4,
    SysState_LoadArea0      = 5,
    SysState_LoadArea1      = 6,
    SysState_ReadMessage    = 7,
    SysState_SaveMenu0      = 8,
    SysState_SaveMenu1      = 9,
    SysState_EventCallFunc  = 10,
    SysState_EventSetFlag   = 11,
    SysState_EventPlaySound = 12,
    SysState_GameOver       = 13,
    SysState_GamePaused     = 14
} e_SysState;

/** @brief Inventory command IDs. */
typedef enum _InventoryCommandId
{
    InventoryCommandId_UseHealth     = 0,
    InventoryCommandId_Use           = 1,
    InventoryCommandId_Equip         = 2,
    InventoryCommandId_Unequip       = 3,
    InventoryCommandId_EquipReload   = 4,
    InventoryCommandId_UnequipReload = 5,
    InventoryCommandId_OnOff         = 6,
    InventoryCommandId_Reload        = 7,
    InventoryCommandId_Look          = 8,
    InventoryCommandId_UseLook       = 9
    // Flashlight 11 in daytime?
} s_InventoryCommandId;

/** @brief Inventory item IDs. */
typedef enum _InventoryItemId
{
    InventoryItemId_Empty                = NO_VALUE,
    InventoryItemId_Unequipped           = 0,

    InventoryItemId_HealthDrink          = 32,
    InventoryItemId_FirstAidKit          = 33,
    InventoryItemId_Ampoule              = 34,

    InventoryItemId_LobbyKey             = 64,
    InventoryItemId_HouseKey             = 65,
    InventoryItemId_KeyOfLion            = 66,
    InventoryItemId_KeyOfWoodman         = 67,
    InventoryItemId_KeyOfScarecrow       = 68,
    InventoryItemId_LibraryReserveKey    = 69,
    InventoryItemId_ClassroomKey         = 70,
    InventoryItemId_KGordonKey           = 71,
    InventoryItemId_DrawbridgeKey        = 72,
    InventoryItemId_BasementKey          = 73,
    InventoryItemId_BasementStoreroomKey = 74,
    InventoryItemId_ExaminationRoomKey   = 75,
    InventoryItemId_AntiqueShopKey       = 76,
    InventoryItemId_SewerKey             = 77,
    InventoryItemId_KeyOfOphiel          = 78,
    InventoryItemId_KeyOfHagith          = 79,
    InventoryItemId_KeyOfPhaleg          = 80,
    InventoryItemId_KeyOfBethor          = 81,
    InventoryItemId_KeyOfAratron         = 82,
    InventoryItemId_NoteToSchool         = 83,
    InventoryItemId_NoteDoghouse         = 84,
    InventoryItemId_PictureCard          = 85,

    InventoryItemId_SewerExitKey         = 87,
    InventoryItemId_ChannelingStone      = 88,

    InventoryItemId_Chemical             = 96,
    InventoryItemId_GoldMedallion        = 97,
    InventoryItemId_SilverMedallion      = 98,
    InventoryItemId_RubberBall           = 99,
    InventoryItemId_Flauros              = 100,
    InventoryItemId_PlasticBottle        = 101,
    InventoryItemId_UnknownLiquid        = 102,
    InventoryItemId_PlateOfTurtle        = 103,
    InventoryItemId_PlateOfHatter        = 104,
    InventoryItemId_PlateOfCat           = 105,
    InventoryItemId_PlateOfQueen         = 106,
    InventoryItemId_BloodPack            = 107,
    InventoryItemId_DisinfectingAlcohol  = 108,
    InventoryItemId_Lighter              = 109,
    InventoryItemId_VideoTape            = 110,

    InventoryItemId_KaufmannKey          = 112,
    InventoryItemId_Receipt              = 113,
    InventoryItemId_SafeKey              = 114,
    InventoryItemId_Magnet               = 115,
    InventoryItemId_MotorcycleKey        = 116,
    InventoryItemId_BirdCageKey          = 117,
    InventoryItemId_Pliers               = 118,
    InventoryItemId_Screwdriver          = 119,
    InventoryItemId_Camera               = 120,
    InventoryItemId_RingOfContract       = 121,
    InventoryItemId_KitchenKnife         = 128,
    InventoryItemId_SteelPipe            = 129,
    InventoryItemId_RockDrill            = 130,

    InventoryItemId_Hammer               = 132,
    InventoryItemId_Chainsaw             = 133,
    InventoryItemId_Katana               = 134,
    InventoryItemId_Axe                  = 135,

    InventoryItemId_Handgun              = 160,
    InventoryItemId_HuntingRifle         = 161,
    InventoryItemId_Shotgun              = 162,
    InventoryItemId_HyperBlaster         = 163,

    InventoryItemId_HandgunBullets       = 192,
    InventoryItemId_RifleShells          = 193,
    InventoryItemId_ShotgunShells        = 194,

    InventoryItemId_Flashlight           = 224,
    InventoryItemId_PocketRadio          = 225,
    InventoryItemId_GasolineTank         = 226
} e_InventoryItemId;

/** @brief Player model bone indices. */
typedef enum _PlayerBone
{
    PlayerBone_Root          = 0,
    PlayerBone_Torso         = 1,
    PlayerBone_Head          = 2,
    PlayerBone_LeftShoulder  = 3,
    PlayerBone_LeftUpperArm  = 4,
    PlayerBone_LeftForearm   = 5,
    PlayerBone_LeftHand      = 6,
    PlayerBone_RightShoulder = 7,
    PlayerBone_RightUpperArm = 8,
    PlayerBone_RightForearm  = 9,
    PlayerBone_RightHand     = 10,
    PlayerBone_Hips          = 11,
    PlayerBone_LeftThigh     = 12,
    PlayerBone_LeftShin      = 13,
    PlayerBone_LeftFoot      = 14,
    PlayerBone_RightThigh    = 15,
    PlayerBone_RightShin     = 16,
    PlayerBone_RightFoot     = 17,

    PlayerBone_Count         = 18
} s_PlayerBone;

/** @brief Player property indices. */
typedef enum _PlayerProperty
{
    PlayerProperty_Unk0          = 0,
    PlayerProperty_AfkTimer      = 1, // Increments every tick for 10 seconds before AFK anim starts.
    PlayerProperty_PositionY     = 2,
    PlayerProperty_Unk3          = 3,
    PlayerProperty_Unk4          = 4,
    PlayerProperty_RunTimer0     = 5, // Increments indefinitely, but more slowly than `PlayerProperty_RunTimer1`.
    PlayerProperty_ExertionTimer = 6, // Counts ~20 seconds worth of ticks while running and caps at 0x23000.
    PlayerProperty_Unk7          = 7,
    PlayerProperty_Unk8          = 8, // Returned by `func_8007FD2C`.
    PlayerProperty_RunTimer1     = 9  // Increments every tick indefinitely.
} s_PlayerProperty;

/** Based on LIBOVR.PDF `Buffer Data Format` section. */
typedef enum _PadTerminalType
{
    PadTerminalType_Mouse               = 1,
    PadTerminalType_16ButtonAnalog      = 2,
    PadTerminalType_GunControllerKonami = 3,
    PadTerminalType_16Button            = 4,
    PadTerminalType_AnalogJoystick      = 5,
    PadTerminalType_GunControllerNamco  = 6,
    PadTerminalType_AnalogController    = 7,
    PadTerminalType_MultitapAdapter     = 8
} e_PadTerminalType;

typedef struct _AnalogPadData
{
    u8  status;
    u8  received_bytes : 4; /** Number of bytes received / 2. */
    u8  terminal_type  : 4; /** `e_PadTerminalType` */
    u16 digitalButtons;
    u8  right_x;
    u8  right_y;
    u8  left_x;
    u8  left_y;
} s_AnalogPadData;
STATIC_ASSERT_SIZEOF(s_AnalogPadData, 8);

typedef struct _ControllerData
{
    s_AnalogPadData analogPad_0;
    s8              unk_8[1];
    u8              field_9;
    s8              unk_A[2];
    s32             btns_held_C; /** `e_PadButton` */
    s32             btns_new_10; /** `e_PadButton` */
    s8              field_14[4];
    s32             field_18;    /** `e_PadButton` */
    s32             field_1C;
    char            field_20;
    char            field_21;
    char            field_22;
    char            field_23;
    char            field_24;
    char            field_25;
    char            field_26;
    char            field_27;
    s32             field_28;
} s_ControllerData;
STATIC_ASSERT_SIZEOF(s_ControllerData, 44);

/** Key bindings for input actions. */
// TODO: Instead of `u16`s, it should use 1-bit packed 16-bit `u32`, similar to `PadButtonFlags` but not an enum because it can have multiple values.
// Only the first 16 values are counted (analog directions are not included). Also, D-Pad is not registered.
typedef struct _ControllerBindings
{
    u16 enter;
    u16 cancel;
    u16 skip;
    u16 action;
    u16 aim;
    u16 light;
    u16 run;
    u16 view;
    u16 stepLeft;
    u16 stepRight;
    u16 pause;
    u16 item;
    u16 map;
    u16 option;
} s_ControllerBindings;
STATIC_ASSERT_SIZEOF(s_ControllerBindings, 28);

typedef struct _ShInventoryItem
{
    u8 id;      /** `InventoryItemId` */
    u8 count;
    u8 command; /** `InventoryCommandId` */
    u8 unk_3;   // Some sort of index?
} s_ShInventoryItem;
STATIC_ASSERT_SIZEOF(s_ShInventoryItem, 4);

typedef struct _ShSaveGame
{
    s_ShInventoryItem items_0[INVENTORY_ITEM_COUNT_MAX];
    s8                field_A0;
    s8                field_A1[3];
    s8                mapOverlayIdx_A4;
    s8                field_A5;
    s16               saveGameCount_A6;
    s8                mapEventIdx_A8;          // See Sparagas' `SaveTitle` enum for details of every value.
    u8                mapIdx_A9; 
    s8                equippedWeapon_AA;       /** `InventoryItemId` */
    u8                field_AB;
    u32               flags_AC;
    s32               field_B0[45];
    s32               hasMapsFlags_164;        // See Sparagas' `HasMapsFlags` struct for details of every bit.
    s32               eventFlags_168[6];       //----------------------------------------
    s32               field_180[2];            //
    s32               field_188;               //
    s32               field_18C;               // Only tested a few, but it seems all are related to events and pick-up flags, grouped by location and not item types.
    s32               field_190[4];            //
    s32               field_1A0;               //
    s32               field_1A4[12];           //----------------------------------------
    s32               mapFlags_1D4[2];         //----------------------------------------
    s32               field_1DC;               // These 3 are one `u32 mapMarkingsFlags[25];` (or maybe `u8 mapMarkingsFlags[100];`?) See Sparagas' `MapMarkingsFlags` struct for details of every bit.
    s32               field_1E0[22];           //----------------------------------------
    s32               field_238;
    s16               pickedUpItemCount_23C;
    s8                field_23E;
    s8                field_23F;
    s32               playerHealth_240;        /** Q20.12, default: 100 */
    s32               playerPositionX_244;     /** Q20.12 */
    s16               playerRotationY_248;     /** Q4.12, Range [0, 0.999755859375], Positive Z: 0, clockwise rotation. It can be multiplied by 360 to get degrees. */
    u8                field_24A;
    u8                field_24B;
    s32               playerPositionZ_24C;     /** Q20.12 */
    s32               gameplayTimer_250;       /** Q20.12 */
    s32               runDistance_254;         /** Q20.12 */
    s32               walkDistance_258;        /** Q20.12 */
    s32               field_25C;
    s32               field_260;               /** Packed data. Stores game difficulty and something else. Last byte is -16 on easy, 0 on normal, and 16 on hard. */
    s16               firedShotCount_264;      /** Missed shot count = firedShotCount - (closeRangeShotCount + midRangeShotCount + longRangeShotCount). */
    s16               closeRangeShotCount_266; /** Only hits counted. */
    s16               midRangeShotCount_268;   /** Only hits counted. */
    s16               longRangeShotCount_26A;  /** Only hits counted. */
    s16               field_26C;
    s16               field_26E; // Related to enemy kills.
    s16               field_270;
    s16               field_272;
    s16               field_274;
    s16               field_276;
    s16               field_278;
    s8                field_27A;
    u8                continueCount_27B;
} s_ShSaveGame;
STATIC_ASSERT_SIZEOF(s_ShSaveGame, 636);

typedef struct _ShEventParam
{
    u8  unk_0[2];
    s16 eventFlagId_2;
    u8  unk_4[1];
    u8  field_5;
    u8  unk_6[2];
    u32 flags_8;
} s_ShEventParam;
STATIC_ASSERT_SIZEOF(s_ShEventParam, 12);

typedef struct _ShSaveUserConfig
{
    s_ControllerBindings controllerBinds_0;
    s8                   screenPosX_1C;             /** Range: [-11, 11], default: 0. */
    s8                   screenPosY_1D;             /** Range: [-8, 8], default: 0. */
    u8                   optSoundType_1E;           /** Stereo: 0, Monaural: 1, default: Stereo. */
    u8                   optVolumeBgm_1F;           /** Range: [0, 128] with steps of 8, default: 16. */
    u8                   optVolumeSe_20;            /** Range: [0, 128] with steps of 8, default: 16. */
    u8                   optVibrationEnabled_21;    /** Off: 0, On: 128, default: On. */
    u8                   optBrightness_22;          /** Range: [0, 7], default: 3. */
    u8                   optWeaponCtrl_23;          /** Switch: 0, Press: 1, default: Press. */
    u8                   optBloodColor_24;          /** Normal: 0, Green: 2, Violet: 5, Black: 13, default: Normal */
    u8                   optAutoLoad_25;            /** Off: 0, On: 1, default: Off. */
    u8                   unk_26;
    u8                   optExtraOptionsEnabled_27;
    s8                   optViewCtrl_28;            /** Normal: 0, Reverse: 1, default: Normal. */
    s8                   optViewMode_29;            /** Normal: 0, Self View: 1, default: Normal. */
    u8                   optRetreatTurn_2A;         /** Normal: 0, Reverse: 1, default: Normal. */
    u8                   optWalkRunCtrl_2B;         /** Normal: 0, Reverse: 1, default: Normal. */
    u8                   optAutoAiming_2C;          /** On: 0, Off: 1, default: On. */
    s8                   optBulletAdjust_2D;        /** x1-x6: Range [0, 5], default: x1. */
    u16                  seenGameOverTips_2E[1];    /** Bitfield tracking seen game-over tips. Each bit corresponds to a tip index (0–15), set bits indicate seen tips. */
    s8                   unk_30[4];
    u32                  unk_34[1];
} s_ShSaveUserConfig;
STATIC_ASSERT_SIZEOF(s_ShSaveUserConfig, 56);

/** @brief Appended to `ShSaveGame` and `ShSaveUserConfig` during game save. Contains 8-bit XOR checksum + magic.
 * Checksum generated via `SaveGame_ChecksumGenerate`.
 */
typedef struct _ShSaveGameFooter
{
    u8  checksum_0[2];
    u16 magic_2;
} s_ShSaveGameFooter;
STATIC_ASSERT_SIZEOF(s_ShSaveGameFooter, 4);

/** @brief Contains `s_ShSaveGame` data with the footer appended to the end containing the checksum + magic. */
typedef struct _ShSaveGameContainer
{
    s_ShSaveGame       saveGame_0;
    s_ShSaveGameFooter footer_27C;
} s_ShSaveGameContainer;
STATIC_ASSERT_SIZEOF(s_ShSaveGameContainer, 640);

/** @brief Contains `s_ShSaveUserConfig` data padded to 128 bytes, with footer at the end containing checksum + magic. */
typedef struct _ShSaveUserConfigContainer
{
    s_ShSaveUserConfig config_0;
    u8                 pad_38[68];
    s_ShSaveGameFooter footer_7C;
} s_ShSaveUserConfigContainer;

typedef struct _GameWork
{
    s_ShSaveUserConfig config_0;
    s_ControllerData   controllers_38[2];
    s_ShSaveGame       saveGame_90; // Backup savegame?
    s_ShSaveGame       saveGame_30C;
    u16                gsScreenWidth_588;
    u16                gsScreenHeight_58A;
    u8                 field_58C; // R?
    u8                 field_58D; // G?
    u8                 field_58E; // B?
    u8                 field_58F; // A or graphics command code?
    s32                gameStatePrev_590;    /** `e_GameState` */
    s32                gameState_594;        /** `e_GameState` */
    s32                gameStateStep_598[3]; /** Temp data used by current gameState. Can be another state ID or other data. */
    s8                 unk_5A4[4];
    s32                field_5A8;
    s32                field_5AC;
    s8                 unk_5B0;
    s8                 mapAnimIdx_5B1;
    s8                 unk_5B2[2];
    s_AnalogPadData    rawPadData_5B4;
    s8                 unk_5BC[28];
} s_GameWork;
STATIC_ASSERT_SIZEOF(s_GameWork, 1496);

typedef struct _ModelAnimData
{
    // Following 4 bytes might be packed into an s32 called `animStatus`,
    // implied by an original param name in `vcMixSelfViewEffectToWatchTgtPos`.

    u8  animIdx_0;
    u8  maybeSomeState_1; // State says if `animTime_4` is anim time or a func ptr? That field could be a union.
    u16 flags_2;          /** `e_AnimFlags` */ // Bit 1: movement unlockled(?), bit 2: visible.
    s32 time_4;           /** Fixed-point time along keyframe timeline. */ 
    s16 keyframeIdx0_8;
    s16 keyframeIdx1_A;
    s32 field_C;
    s32 field_10;
} s_ModelAnim;
STATIC_ASSERT_SIZEOF(s_ModelAnim, 20);

typedef struct _Model
{
    s8 chara_type_0;
    u8 field_1;
    u8 field_2;
    u8 isAnimStateUnchanged_3; // Educated guess. In `s_MainCharacterExtra`, always 1, set to 0 for 1 tick when anim state appears to change.
                               // Used differently in player's `s_SubCharacter`. 0: anim transitioning(?), bit 1: animated, bit 2: turning.
    s_ModelAnim anim_4;
} s_Model;
STATIC_ASSERT_SIZEOF(s_Model, 24);

typedef struct _SubCharacter
{
    s_Model model_0;
    VECTOR3 position_18;
    SVECTOR rotation_24;
    SVECTOR rotationSpeed_2C;
    s32     field_34;
    s32     moveSpeed_38;
    s16     headingAngle_3C;
    s16     field_3E;
    s8      unk_40[4];
    s16     field_44;
    s8      unk_46[2];
    s8      unk_48[104];
    s32     health_B0; // Bits 3-4 contain `s16` associated with player's rate of heavy breathing, always set to 6. Can't split into `s16`s? Maybe packed data.
    s8      unk_B4[16];
    u16     dead_timer_C4; // Part of `shBattleInfo` struct in SH2, may use something similar here.
    u16     field_C6;

    // Fields seen used inside maps (eg. `map0_s00` `func_800D923C`)

    s16 field_C8;
    s16 field_CA;
    s8  unk_CC[2];
    s16 field_CE;
    s8  unk_D0[4];
    s16 field_D4;
    s16 field_D6;
    s16 field_D8;
    s16 field_DA;
    s16 field_DC;
    s16 field_DE;
    s32 flags_E0;
    s32 properties_E4[CHARA_PROPERTY_COUNT_MAX];
    s8  unk_10C;
    u8  field_10D;
    s8  unk_10E[6];
    s32 field_114;
    s8  unk_118[4];
    s32 field_11C;
    s8  unk_120[6];
    s16 field_126;
} s_SubCharacter;
STATIC_ASSERT_SIZEOF(s_SubCharacter, 296);

typedef struct _MainCharacterExtra
{
    s_Model model_0; // For player, this is a copy of model_0 in its corresponding s_SubCharacter.
    s32     field_18;
    s32     field_1C; // Some kind of state. 0: nothing, 1: unknown bent over pose, 2: AFK, 8: dying, 5: forcefully turned around.
    s32     field_20; // Some kind of anim state related to current action (running, walking, sidestepping, etc.).
    s32     field_24; // Some kind of anim state related to current action (running, walking, sidestepping, etc.). Sometimes same as above, but not always.
    s8      field_28; // Forcefully setting to 1 opens options menu.
} s_MainCharacterExtra;
STATIC_ASSERT_SIZEOF(s_MainCharacterExtra, 44);

// TODO: Is this a struct of its own, or are its fields kept separately?
typedef struct _MainCharacter
{
    s_SubCharacter       chara_0;
    s_MainCharacterExtra extra_128;
} s_MainCharacter;
STATIC_ASSERT_SIZEOF(s_MainCharacter, 340);

typedef struct _SysWork
{
    s8              unk_0[8];
    s32             sysState_8;     /** e_SysState */
    s32             sysStateStep_C; // Current step/state of sysState_8 game is in.
    s32             field_10;       // Sometimes assigned to same thing as sysStateStep_C.
    s32             field_14;
    s32             field_18;
    s32             timer_1C;
    s32             timer_20;
    s32             timer_24;
    s32             field_28;
    s32             timer_2C;
    s32             field_30;
    s8              unk_34[4];
    s32             field_38; // Something related to map loading.
    s8              unk_3C[11];
    s8              field_47; // Something related to map loading.
    s8              unk_48[3];
    u8              isPlayerInCombatMode_4B;
    s_MainCharacter player_4C;
    s_SubCharacter  npcs_1A0[NPC_COUNT_MAX];
    GsCOORDINATE2   playerBoneCoords_890[PlayerBone_Count];
    s8              pad_E30[400];  // Might be part of previous array for 5 exra coords which go unused.
    s8              unk_FC0[4810]; // Start is tightly-packed buffer for NPC bone coords. Size unclear, appears to be enough for 60 before what might be AI data.
    u16             field_228A;
    s8              unk_228C[12];
    s32             flags_2298;    // Something related to map loading.
    s8              unk_229C[4];
    s32             field_22A0;
    s32             flags_22A4;
    s8              unk_22A8[168];
    s32             field_2350;
    s8              unk_2354[4];
    u8              field_2358;
    s8              unk_2359[33];
    s16             cameraAngleY_237A;
    s16             cameraAngleZ_237C;
    s16             field_237E;
    s32             cameraRadiusXz_2380;
    s32             cameraY_2384;
    s8              unk_2388[20];
    s8              field_239C;
    u8              field_239D; // Index?
    s8              unk_239E[318];
    s32             field_24DC;
    s8              unk_24E0[48];
    s32             field_2510;
    s32             field_2514[10];
    u8              unk_253C[524];
    s16             field_2748[9];
    u8              unk_275A[2];
    s32             field_275C;
    u8              unk_2760[8];
} s_SysWork;
STATIC_ASSERT_SIZEOF(s_SysWork, 10088);

extern void* g_OvlBodyprog;
extern void* g_OvlDynamic;

extern s_SysWork         g_SysWork; // 0x800B9FC0
extern s_GameWork        g_GameWork;
extern s_GameWork*       g_GameWorkPtr0;
extern s_GameWork*       g_GameWorkPtr1;
extern s_ShSaveGame*     g_SaveGamePtr;
extern s_ControllerData* g_ControllerPtr0;
extern s_ControllerData* g_ControllerPtr1;

extern s32  g_ObjectTableIdx;
extern GsOT g_ObjectTable0[];
extern GsOT g_ObjectTable1[];

extern s32 g_DeltaTime0;
extern s32 g_DeltaTime1;
extern s32 g_DeltaTime2;
extern u32 g_MapEventIdx;
extern s_ShEventParam* g_MapEventParam;

extern s32 g_IntervalVBlanks;
extern s32 g_PrevVBlanks;
extern s32 g_VBlanks;
extern s32 g_UncappedVBlanks;

/** @brief Sets the SysState to be used in the next game update. */
static inline void SysWork_StateSetNext(e_SysState sysState)
{
    g_SysWork.sysState_8     = sysState;
    g_SysWork.timer_24       = 0;
    g_SysWork.sysStateStep_C = 0;
    g_SysWork.field_28       = 0;
    g_SysWork.field_10       = 0;
    g_SysWork.timer_2C       = 0;
    g_SysWork.field_14       = 0;
}

/** @brief Increments the `sysStateStep` index in `g_SysWork`. */
static inline void SysWork_StateStepIncrement()
{
    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.timer_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.sysStateStep_C++;
}

/** @brief Sets the GameState to be used in the next game update.
 * Inlined into stream and b_konami.
 */
static inline void Game_StateSetNext(e_GameState gameState)
{
    e_GameState prevState = g_GameWork.gameState_594;

    g_GameWork.gameState_594 = gameState;

    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

/** @brief Returns the GameState to the previously used state.
 * Inlined into credits.
 */
static inline void Game_StateSetPrevious()
{
    e_GameState prevState = g_GameWork.gameState_594;

    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameState_594        = g_GameWork.gameStatePrev_590;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

/** @brief Sets the given flag ID inside the savegame event flags array. */
static inline void SaveGame_EventFlagSet(u32 flagId)
{
    s16 flagIdx = flagId / 32;
    s16 flagBit = flagId % 32;

    g_SaveGamePtr->eventFlags_168[flagIdx] |= 1 << flagBit;
}

/** @brief Checks if the given flag ID is set inside the array of 16-bit flag values. */
static inline s32 Flags16b_IsSet(u16* array, s32 flagId)
{
    // BUG: `>> 5` divides flagId by 32 to get array index, but array is of 16-bit values.
    // Maybe copy paste from `u32` version of func.
    return (array[flagId >> 5] >> (flagId & 0x1F)) & (1 << 0);
}

#endif

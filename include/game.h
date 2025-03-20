#ifndef _GAME_H
#define _GAME_H

#include "gpu.h"

#define TICKS_PER_SECOND      60
#define NPC_COUNT_MAX         6
#define GAME_INVENTORY_SIZE   40
#define SAVEGAME_FOOTER_MAGIC 0xDCDC

/** Convert tile units (the engine's measurement reference) to world units. */
#define TILE_UNIT(value) \
    (s32)((value) * 256.0f)

typedef enum _PadButton
{
    Pad_BtnSelect    = 1 << 0,
    Pad_BtnL3        = 1 << 1,
    Pad_BtnR3        = 1 << 2,
    Pad_BtnStart     = 1 << 3,
    Pad_BtnDpadUp    = 1 << 4,
    Pad_BtnDpadRight = 1 << 5,
    Pad_BtnDpadDown  = 1 << 6,
    Pad_BtnDpadLeft  = 1 << 7,
    Pad_BtnL2        = 1 << 8,
    Pad_BtnR2        = 1 << 9,
    Pad_BtnL1        = 1 << 10,
    Pad_BtnR1        = 1 << 11,
    Pad_BtnTriangle  = 1 << 12,
    Pad_BtnCircle    = 1 << 13,
    Pad_BtnCross     = 1 << 14,
    Pad_BtnSquare    = 1 << 15,
    Pad_LSUp2        = 1 << 16,
    Pad_LSRight2     = 1 << 17,
    Pad_LSDown2      = 1 << 18,
    Pad_LSLeft2      = 1 << 19,
    Pad_RSUp         = 1 << 20,
    Pad_RSRight      = 1 << 21,
    Pad_RSDown       = 1 << 22,
    Pad_RSLeft       = 1 << 23,
    Pad_LSUp         = 1 << 24,
    Pad_LSRight      = 1 << 25,
    Pad_LSDown       = 1 << 26,
    Pad_LSLeft       = 1 << 27
} e_PadButton;

/** State IDs used by the main game loop. The values are used as indices into the 0x800A977C function array. */
typedef enum _GameState
{
    GameState_Unk0                = 0,
    GameState_KonamiLogo          = 1,
    GameState_KcetLogo            = 2,
    GameState_StartMovieIntro     = 3,
    GameState_Unk4                = 4,
    GameState_MovieIntroAlternate = 5,
    GameState_MovieIntro          = 6,
    GameState_MainMenu            = 7,
    GameState_Unk8                = 8,
    GameState_MovieOpening        = 9,
    GameState_LoadScreen          = 10,
    GameState_InGame              = 11,
    GameState_MapEvent            = 12,
    GameState_ReturnToGameplay    = 13,
    GameState_StatusScreen        = 14,
    GameState_MapScreen           = 15,
    GameState_Unk10               = 16,
    GameState_MovieEnding         = 17,
    GameState_OptionScreen        = 18,
    GameState_LoadStatusScreen    = 19,
    GameState_LoadMapScreen       = 20,
    GameState_Unk15               = 21,
    GameState_Unk16               = 22
} e_GameState;

/** State IDs used by GameState_InGame. The values are used as indices into the 0x800A9A2C function array. */
typedef enum _SysState
{
    SysState_Gameplay    = 0,
    SysState_OptionsMenu = 1,
    SysState_StatusMenu  = 2,
    SysState_Unk3        = 3,
    SysState_FMV         = 4,
    SysState_LoadArea1   = 5,
    SysState_LoadArea2   = 6,
    SysState_ReadMessage = 7,
    SysState_SaveMenu1   = 8,
    SysState_SaveMenu2   = 9,
    SysState_Unk10       = 10,
    SysState_Unk11       = 11,
    SysState_Unk12       = 12,
    SysState_GameOver    = 13,
    SysState_GamePaused  = 14
} e_SysState;

typedef struct _AnalogPadData
{
    u8  status;
    u8  data_format;
    u16 digitalButtons;
    u8  right_x;
    u8  right_y;
    u8  left_x;
    u8  left_y;
} s_AnalogPadData;

typedef struct _ControllerData
{
    s_AnalogPadData analogPad_0;
    s8              unk_8[1];
    u8              field_9;
    s8              unk_A[2];
    s32             btns_held_C; /** e_PadButton */
    s32             btns_new_10; /** e_PadButton */
    s8              field_14[4];
    s32             field_18;    /** e_PadButton */
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

// Input action key bindings.
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

typedef struct _ShInventoryItem
{
    u8 id;
    u8 count;
    u8 unk_2;
    u8 unk_3;
} s_ShInventoryItem;

typedef struct _ShSaveGame
{
    s_ShInventoryItem items_0[GAME_INVENTORY_SIZE];
    s8                field_A0;
    s8                field_A1[3];
    s8                mapOverlayIdx_A4;
    s8                field_A5;
    s16               saveGameCount_A6;
    s8                mapEventIdx_A8;
    u8                mapIdx_A9;
    s8                field_AA;
    u8                field_AB;
    u32               flags_AC;
    s32               field_B0[45];
    s32               field_164;
    s32               eventFlags_168[6];
    s32               field_180[2];
    s32               field_188;
    s32               field_18C;
    s32               field_190[4];
    s32               field_1A0;
    s32               field_1A4[12];
    s32               mapFlags_1D4[2];
    s32               field_1DC;
    s32               field_1E0[22];
    s32               field_238;
    s16               field_23C;
    s8                field_23E;
    s8                field_23F;
    s32               playerHealth_240;
    s32               playerPositionX_244;
    s16               playerRotationY_248;
    s8                field_24A;
    s8                field_24B;
    s32               playerPositionZ_24C;
    s32               gameplayTimer_250;
    s32               field_254;
    s32               field_258;
    s32               field_25C;
    s32               field_260; // Packed data. Stores game difficulty and something else.
    s16               field_264;
    s16               field_266;
    s16               field_268;
    s16               field_26A;
    s16               field_26C;
    s16               field_26E;
    s16               field_270;
    s16               field_272;
    s16               field_274;
    s16               field_276;
    s16               field_278;
    s8                field_27A;
    s8                field_27B;
} s_ShSaveGame;
STATIC_ASSERT_SIZEOF(s_ShSaveGame, 0x27C);

/** 
 * Appended to ShSaveGame during game save. Contains 8-bit XOR checksum + magic
 * checksum generated via the SaveGame_ChecksumGenerate function .
 */
typedef struct _ShSaveGameFooter
{
    u8  checksum_0[2];
    u16 magic_2;
} s_ShSaveGameFooter;
STATIC_ASSERT_SIZEOF(s_ShSaveGameFooter, 4);

/** Contains s_ShSaveGame data with the footer appended to the end containing the checksum + magic. */
typedef struct _ShSaveGameContainer
{
    s_ShSaveGame       saveGame_0;
    s_ShSaveGameFooter footer_27C;
} s_ShSaveGameContainer;
STATIC_ASSERT_SIZEOF(s_ShSaveGameContainer, 0x280);
    
typedef struct _GameWork
{
    s_ControllerBindings controllerBinds_0;
    s8                   field_1C;
    s8                   field_1D;
    u8                   optSoundType_1E;           /** Stereo: 0, monaural: 1. */
    u8                   optVolumeBgm_1F;           /** Range: [0, 128] with steps of 8. */
    u8                   optVolumeSe_20;            /** Range: [0, 128] with steps of 8. */
    u8                   optVibrationEnabled_21;    /** Off: 0, on: 0x80. */
    u8                   optBrightness_22;          /** Range: [0, 7], default: 3. */
    u8                   optWeaponCtrl_23;          /** Switch: 0, press: 1. */
    u8                   optBloodColor_24;          /** Normal: 0, green: 2, violet: 5, black: 11. */
    u8                   optAutoLoad_25;            /** Off: 0, on: 1. */
    u8                   unk_26;
    u8                   optExtraOptionsEnabled_27;
    s8                   optViewCtrl_28;            /** Normal: 0, reverse: 1. */
    s8                   optViewMode_29;
    u8                   optRetreatTurn_2A;         /** Normal: 0, reverse: 1. */
    u8                   optWalkRunCtrl_2B;         /** Normal: 0, reverse: 1. */
    u8                   optAutoAiming_2C;          /** Off: 1, on: 0. */
    u8                   optBulletAdjust_2D;
    s8                   unk_2E[2];
    s8                   unk_30[8];
    s_ControllerData     controllers_38[2];
    s_ShSaveGame         saveGame_90; // Backup savegame?
    s_ShSaveGame         saveGame_30C;
    u16                  gsScreenWidth_588;
    u16                  gsScreenHeight_58A;
    u8                   field_58C; // R?
    u8                   field_58D; // G?
    u8                   field_58E; // B?
    u8                   field_58F; // A or graphics command code?
    s32                  gameStatePrev_590;    /** e_GameState */
    s32                  gameState_594;        /** e_GameState */
    s32                  gameStateStep_598[3]; /** Temp data used by current gameState. Can be another state ID or other data. */
    s8                   unk_5A4[4];
    s32                  field_5A8;
    s32                  field_5AC;
    s8                   unk_5B0;
    s8                   mapAnimIdx_5B1;
    s8                   unk_5B2[2];
    s_AnalogPadData      rawPadData_5B4;
    s8                   unk_5BC[28];
} s_GameWork;
STATIC_ASSERT_SIZEOF(s_GameWork, 1496);

typedef struct _SubCharacter
{
    s8    chara_type_0; // NOTE: Character types <24 must be some distinct category.
    u8    field_1;
    u8    field_2;
    u8    field_3; // Clear: anim transitioning(?), bit 1: animated, bit2: turning.

    // Probably struct.
    //==================

    // Following 4 bytes might be packed into an s32 called "animStatus",
    // implied by an original param name in `vcMixSelfViewEffectToWatchTgtPos`.

    u8  animIdx_4;
    u8  maybeSomeState_5;
    s16 flags_6; // Bit 1: movement unlockled? Bit 2: visible.

    s32 fixedAnimFrameIdx_8;  // animFrameIdx_C << 12. Maybe used for interpolation?
    s16 animFrameIdx_C;       // Frame index into large array containing all frames for all anims?
    s16 interpolationAlpha_E; // Something to do with linear anim interpolation. Maybe fixed-point alpha value. Gets set to 1 << 12 (4096).
    u8  unk_10[8];            // Maybe flag fields.

    //==================

    VECTOR3 position_18;
    SVECTOR rotation_24;
    SVECTOR rotationSpeed_2C;
    s32     field_34;
    s32     moveSpeed_38;
    s16     headingAngle_3C;
    s8      pad_3E[2];
    s8      unk_40[4];
    s32     field_44;
    s8      unk_45[104];
    s32     health_B0; // Bits 3-4 contain s16 associated with player's rate of heavy breathing, always set to 6. Can't split into `s16`s? Maybe packed data.
    s8      unk_B4[16];
    u16     dead_timer_C4; // Part of shBattleInfo struct in SH2, may use something similar here.
    s8      unk_C6[2];
    s8      unk_C8[32];

    // Fields in the following block may be part of a multi-purpose array of `s32` elements used to store unique property data for each character type.
    // Start of this section is unclear, bytes above may be part of it.
    // For player, mostly used for counters as far as I could see. -- Sezz

    s32 field_E8;  // Player AFK counter. Increments every tick for 10 seconds before player starts AFK anim. Purpose for other characters unknown.
    s32 field_EC;  // Copy of player Y position. Purpose for other characters unknown.
    s32 field_F0;
    s32 field_F4;
    s32 field_F8;  // Player run counter. Increments more slowly than runCounter_108. Purpose for other characters unknown.
    s32 field_FC;  // Player winded counter. Counts 20 seconds worth of ticks and caps at 0x23000. Purpose for other characters unknown.
    s32 unk_100;
    s32 field_104;  // Used by player, returned by `func_8007FD2C`. Purpose unknown.
    s32 field_108; // Player run counter. Increments every tick indefinitely. Purpose for other characters unknown.

    s8  unk_10C;
	u8  field_10D;
	s8  unk_10E[5];
    s32 field_112;
	s8  unk_116[14];
    s16 field_126;
} s_SubCharacter;
STATIC_ASSERT_SIZEOF(s_SubCharacter, 296);

typedef struct _MainCharacterExtra
{
    // SubCharacter has the same 0x2C starting bytes?
    // Maybe this is actually just a base model struct, which SubCharacter extends, and the extra data in MainCharacter is some model attached to player?
    u8             field_0;
    u8             field_1;
    u8             field_2;
    u8             isAnimStateUnchanged_3; // Educated guess. Always 1, set to 0 for 1 tick when anim state appears to change.

    // Probably struct.
    //==================

    u8  animIdx_4;
    u8  maybeSomeState_5;
    s16 flags_6;
    s32 fixedAnimFrameIdx_8;
    s16 animFrameIdx_C;
    s16 interpolationAlpha_E;
    u8  unk_10[8];

    //==================

    s32            field_18;
    s32            field_1C; // Some kind of anim state. Set to 2 when player is in AFK anim, 0 otherwise.
    s32            field_20; // Some kind of anim state.
    s32            field_24; // Some kind of anim state.
    s8             unk_28[4];
} s_MainCharacterExtra;
STATIC_ASSERT_SIZEOF(s_MainCharacterExtra, 44);

typedef struct _MainCharacter
{
    s_SubCharacter       character;
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
    s8              unk_18[4];
    s32             field_1C;
    s32             field_20;
    s32             field_24;
    s32             field_28;
    s32             field_2C; // Timer of some kind.
    s32             field_30;
    s8              unk_34[4];
    s32             field_38; // Something related to map loading.
    s8              unk_3C[11];
    s8              field_47; // Something related to map loading.
    s8              unk_48[3];
    u8              field_4B; // Something used among player anim state checks.
    s_MainCharacter player_4C;
    s_SubCharacter  characters_1A0[NPC_COUNT_MAX];
    GsCOORDINATE2   unk_coord_890[2];
    GsCOORDINATE2   hero_neck_930;
    s8              unk_980[6424];
    s32             flags_2298; // Something related to map loading.
    s8              unk_229C[4];
    s32             field_22A0;
    s32             flags_22A4;
    s8              unk_22A8[176];
    u8              field_2358;
    s8              unk_2359[33];
    s16             cam_ang_y_237A;
    s16             cam_ang_z_237C;
    s16             field_237E;
    s32             cam_r_xz_2380;
    s32             cam_y_2384;
    u8              unk_2388[392];
    s32             field_2510;
    s32             field_2514[10];
    u8              unk_253C[556];
} s_SysWork;
STATIC_ASSERT_SIZEOF(s_SysWork, 0x2768);

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

extern s32 g_IntervalVBlanks;
extern s32 g_PrevVBlanks;
extern s32 g_VBlanks;
extern s32 g_UncappedVBlanks;

/** Sets the SysState to be used in the next game update. */
static inline void SysWork_StateSetNext(e_SysState sysState)
{
    g_SysWork.sysState_8     = sysState;
    g_SysWork.field_24       = 0;
    g_SysWork.sysStateStep_C = 0;
    g_SysWork.field_28       = 0;
    g_SysWork.field_10       = 0;
    g_SysWork.field_2C       = 0;
    g_SysWork.field_14       = 0;
}

/**
 * Sets the GameState to be used in the next game update.
 * Inlined into stream and b_konami.
 */
static inline void Game_StateSetNext(e_GameState gameState)
{
    e_GameState prevState = g_GameWork.gameState_594;

    g_GameWork.gameState_594 = gameState;

    g_SysWork.field_1C = 0;
    g_SysWork.field_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

/**
 * Returns the GameState to the previously used state.
 * Inlined into credits.
 */
static inline void Game_StateSetPrevious()
{
    e_GameState prevState = g_GameWork.gameState_594;

    g_SysWork.field_1C = 0;
    g_SysWork.field_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameState_594        = g_GameWork.gameStatePrev_590;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

#endif

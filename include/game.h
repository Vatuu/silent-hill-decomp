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
    s_AnalogPadData AnalogPad;
    int             field_8;
    e_PadButton     btns_held_C;
    e_PadButton     btns_new_10;
    char            field_14[4];
    e_PadButton     field_18;
    int             field_1C;
    char            field_20;
    char            field_21;
    char            field_22;
    char            field_23;
    char            field_24;
    char            field_25;
    char            field_26;
    char            field_27;
    int             field_28;
} s_ControllerData;

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
    s8                curMapOverlayIndex_A4;
    s8                field_A5;
    s16               saveGameCount_A6;
    s8                curMapEventNum_A8;
    u8                curMapIndex_A9;
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
    s32               playerPosX_244;
    s16               playerRotationYaw_248;
    s8                field_24A;
    s8                field_24B;
    s32               playerPosZ_24C;
    s32               gameplayTimer_250;
    s32               field_254;
    s32               field_258;
    s32               field_25C;
    s32               field_260;
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
    u8                   optViewCtrl_28;            /** Normal: 0, reverse: 1. */
    s8                   optViewMode_29;
    u8                   optRetreatTurn_2A;         /** Normal: 0, reverse: 1. */
    u8                   optWalkRunCtrl_2B;         /** Normal: 0, reverse: 1. */
    u8                   optAutoAiming_2C;          /** Off: 1, on: 0. */
    u8                   optBulletAdjust_2D;
    char                 unk_2E[2];
    char                 unk_30[8];
    s_ControllerData     controllers_38[2];
    s_ShSaveGame         saveGame_90; // Backup savegame?
    s_ShSaveGame         saveGame_30C;
    u16                  gsScreenWidth_588;
    u16                  gsScreenHeight_58A;
    u8                   field_58C; // R?
    u8                   field_58D; // G?
    u8                   field_58E; // B?
    u8                   field_58F; // A or graphics command code?
    e_GameState          gameStatePrev_590;
    e_GameState          gameState_594;
    s32                  gameStateStep_598[3]; /** Temp data used by current gameState. Can be another state ID or other data. */
    char                 unk_5A4[52];
} s_GameWork;
STATIC_ASSERT_SIZEOF(s_GameWork, 0x5D8);

typedef struct _SubCharacter
{
    u8    chara_type_0; // NOTE: Character types <24 must be some distinct category.
    u8    field_1;
    u8    field_2;
    u8    field_3; // Clear: anim transitioning(?), bit 1: animated, bit2: turning.

    // Following 4 bytes might be packed into an s32 called "animStatus",
    // going by an original param name in vcMixSelfViewEffectToWatchTgtPos.

    u8  animIdx_4;
    u8  maybeSomeState_5;
    s16 flags_6; // Bit 1: movement unlockled? Bit 2: visible.

    s32 animFrameIdx_8;       // Rapidly incrementing anim frame index. Maybe interpolated frame index?
    s16 animFrameIdx_C;       // Slowly incrementing anim frame index. Maybe actual frame data index of frame to be interpolated?
    s16 interpolationAlpha_E; // Something to do with linear anim interpolation. Maybe alpha value in Q format.
    u8  flags_12[8];

    VECTOR3 position_18;
    SVECTOR rotation_24;
    SVECTOR rot_spd_2C;
    s32     field_34;
    s32     chara_mv_spd_38;
    s16     chara_mv_ang_y_3C;
    u8      pad_3E[2];
    u8      unk_40[112];
    s32     health_B0; // Bits 3-4 contain s16 associated with player's rate of heavy breathing, always set to 6. Can't split into s16s? Maybe packed data.
    s8      unk_B4[52];  

    // These might be part of a multi-purpose array of s32 elements used for storing unique data for each character type.
    // For player, mostly used for counters as far as I could see. --Sezz

    s32 field_E8;  // Player AFK counter. Increments every tick(?) for 10 seconds before player starts AFK anim. Purpose for other characters unknown.
    s32 field_EC;  // Copy of player Y position. Purpose for other characters unknown.
    s8  unk_F0[8]; // 2 more s32 for custom data?
    s32 field_F8;  // Player run counter. Increments more slowly than runCounter_108. Purpose for other characters unknown.
    s32 field_FC;  // Player winded counter. Counts 20 seconds worth of ticks(?) and caps at 0x23000. Purpose for other characters unknown.
    s8  unk_FC[8]; // 2 more s32 for custom data?
    s32 field_108; // Player run counter. Increments every tick(?) indefinitely. Purpose for other characters unknown.

    s8 unk_EC[28]; 
} s_SubCharacter;
STATIC_ASSERT_SIZEOF(s_SubCharacter, 296);

typedef struct _MainCharacter
{
    s_SubCharacter character;
    u8             field_128;
    u8             field_129;
    u8             field_12A;
    u8             field_12B;    // isPrevAnimStateSame? Always 1, set to 0 for 1 tick when anim state changes.
    s8             copy_12C[20]; // Duplicate data. Sequentially opies all fields from 0x4 to 0x18 of s_SubCharacter.
    s8             field_140[4];
    s8             field_144[4]; // s32? Some kind of anim state. Set to 2 when player is in AFK anim, 0 otherwise.
    s8             field_148[4]; // s32? Some kind of anim state.
    s8             field_14C[4]; // s32? Some kind of anim state.
    s8             unk_150[4];
} s_MainCharacter;
STATIC_ASSERT_SIZEOF(s_MainCharacter, 0x154);

typedef struct _SysWork
{
    char            unk_0[8];
    e_SysState      sysState_8;
    s32             sysStateStep_C; // Current step/state of sysState_8 game is in.
    s32             field_10;       // Sometimes assigned to same thing as sysStateStep_C.
    s32             field_14;
    char            unk_18[4];
    s32             field_1C;
    s32             field_20;
    s32             field_24;
    s32             field_28;
    s32             field_2C; // Distance of some kind?
    s32             field_30;
    char            unk_34[24];
    s_MainCharacter player_4C;
    s_SubCharacter  characters_1A0[NPC_COUNT_MAX];
    GsCOORDINATE2   unk_coord_890[2];
    GsCOORDINATE2   hero_neck_930;
    s8              unk_980[6432];
    s32             field_22A0;
    s32             flags_22A4;
    char            unk_22A8[210];
    s16             cam_ang_y_237A;
    s16             cam_ang_z_237C;
    s16             field_237E;
    int             cam_r_xz_2380;
    int             cam_y_2384;
    u8              unk_2388[992];
} s_SysWork;
STATIC_ASSERT_SIZEOF(s_SysWork, 0x2768);

extern void* g_OvlBodyprog;
extern void* g_OvlDynamic;

extern s_SysWork         g_SysWork;
extern s_GameWork        g_GameWork;
extern s_GameWork*       g_GameWorkPtr0;
extern s_GameWork*       g_GameWorkPtr1;
extern s_ShSaveGame*     g_SaveGamePtr;
extern s_ControllerData* g_ControllerPtr0;
extern s_ControllerData* g_ControllerPtr1;

extern s32  g_ObjectTableIdx;
extern GsOT g_ObjectTable0[];
extern GsOT g_ObjectTable1[];

extern s32 g_DeltaTime;
extern u32 g_MapEventIdx;

extern s32 g_IntervalVBlanks;
extern s32 g_PrevVBlanks;
extern s32 g_CappedVBlanks;
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

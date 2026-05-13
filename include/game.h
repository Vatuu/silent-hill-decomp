#ifndef _GAME_H
#define _GAME_H

#include "event_flags.h"
#include "gpu.h"
#include "types.h"
#include "lib_unk.h"

#include "bodyprog/anim.h"
#include "bodyprog/chara.h"
#include "bodyprog/formats/anm.h"
#include "bodyprog/items.h"
#include "bodyprog/model.h"
#include "maps/characters/harry.h"

struct _AnmHeader;
struct _Model;

#define TICKS_PER_SECOND 60                                        /** Game has a variable timestep with 60 ticks max. */
#define TIMESTEP_30_FPS  Q12(1.0f / (float)(TICKS_PER_SECOND / 2)) /** Timestep at 30 FPS. */
#define TIMESTEP_60_FPS  Q12(1.0f / (float)(TICKS_PER_SECOND))     /** Timestep at 60 FPS. */

#define SCREEN_WIDTH                   320
#define SCREEN_HEIGHT                  240
#define FRAMEBUFFER_HEIGHT_PROGRESSIVE 224
#define FRAMEBUFFER_HEIGHT_INTERLACED  (FRAMEBUFFER_HEIGHT_PROGRESSIVE * 2)
#define ORDERING_TABLE_SIZE            2048

#define INV_ITEM_COUNT_MAX   40
#define INPUT_ACTION_COUNT   14
#define CONTROLLER_COUNT_MAX 2

#define DEFAULT_PICKUP_ITEM_COUNT      1
#define HANDGUN_AMMO_PICKUP_ITEM_COUNT 15
#define SHOTGUN_AMMO_PICKUP_ITEM_COUNT 6
#define RIFLE_AMMO_PICKUP_ITEM_COUNT   6

#define DEFAULT_MAP_MESSAGE_LENGTH     99
#define GLYPH_TABLE_ASCII_OFFSET       '\'' /** Subtracted from ASCII bytes to get index to some string-related table. */

#if VERSION_REGION_IS(NTSC)
#define MAP_MESSAGE_DISPLAY_ALL_LENGTH 400 /** Long string length is used to display a whole message instantly without a rollout. */
#elif VERSION_REGION_IS(NTSCJ)
#define MAP_MESSAGE_DISPLAY_ALL_LENGTH 200 /** Long string length is used to display a whole message instantly without a rollout. */
#endif

#define CHUNK_CELL_SIZE Q12(40.0f)

#define BGM_LAYER_COUNT 9

/** @brief Converts a floating-point X screen position in percent to a fixed-point X screen coodinate. */
#define SCREEN_POSITION_X(percent) \
    (s32)(SCREEN_WIDTH * ((percent) / 100.0f))

/** @brief Converts a floating-point Y screen position in percent to a fixed-point Y screen coodinate. */
#define SCREEN_POSITION_Y(percent) \
    (s32)(SCREEN_HEIGHT * ((percent) / 100.0f))

/** @brief Checks if a specified map has been collected. */
#define HAS_MAP(mapIdx) \
    ((((u32*)&g_SavegamePtr->hasMapsFlags)[(mapIdx) / 32] >> ((mapIdx) % 32)) & (1 << 0))

/** @brief Packs a weapon attack containing a weapon ID and attack input type.
 *
 * @param weaponId Weapon ID.
 * @param attackInputType Attack input type.
 * @return Packed weapon attack containing a weapon ID and attack input type.
 */
#define WEAPON_ATTACK(weaponId, attackInputType) \
    ((weaponId) + ((attackInputType) * 10))

/** @brief Retrieves the weapon ID from a packed weapon attack.
 *
 * @param weaponAttack Packed weapon attack containing a weapon ID and attack input type.
 * @return Weapon ID.
 */
#define WEAPON_ATTACK_ID_GET(weaponAttack) \
    ((weaponAttack) % 10)

/** @brief Creates a bitmask with a contiguous range of bits set.
 * For use with `s_PlayerExtra::disabledAnimBones`.
 *
 * Generates an `unsigned int` mask with all bits in the range `[fromInclusive, toInclusive]` set.
 *
 * For example:
 * - `BITMASK_RANGE(0, 2)` -> 0b000...0111 (decimal 7).
 * - `BITMASK_RANGE(4, 11)` -> 0b000...111111110000 (decimal 4080).
 *
 * @param fromInclusive Index of the lowest bit to set (0 = least significant bit).
 * @param toInclusive Index of the highest bit to set.
 * @return Bitmask with the specified range of bits set to 1 (`unsigned int`).
 */
#define BITMASK_RANGE(fromInclusive, toInclusive) \
    (((~0u << (fromInclusive)) & ~(~0u << ((toInclusive) + 1))))

/** @brief Packs a screen fade status containing a fade state and white flag.
 * See `g_Screen_FadeStatus` for bit layout.
 *
 * @param state Screen fade state.
 * @param isWhite White status (`bool`).
 * @return Packed screen fade status containing a fade state and white flag.
 */
#define SCREEN_FADE_STATUS(state, isWhite) \
    ((state) | ((isWhite) ? (1 << 3) : 0))

/** @brief Checks if the screen fade is not in progress (finished step) by masking away the color bit.
 *
 * @return `true` if finished, `false` if still in progress.
 */
#define ScreenFade_IsFinished() \
    ((g_Screen_FadeStatus & 0x7) == ScreenFadeState_FadeOutComplete)

/** @brief Checks if the screen fade is not in progress (idle step) without masking away the color bit.
 *
 * @return `true` if idle, `false` otherwise.
 */
#define ScreenFade_IsNone() \
    (g_Screen_FadeStatus == ScreenFadeState_None)

/** @brief Checks if the screen fade is white.
 * See `g_Screen_FadeStatus` for bit layout.
 *
 * @param fadeStatus Packed screen fade status containing a fade state and white flag.
 * @return `true` if white, `false` if black.
 */
#define IS_SCREEN_FADE_WHITE(fadeStatus) \
    ((fadeStatus) & (1 << 3))

/** @brief Starts a screen fade in/out.
 *
 * @param reset `true` to reset fade progress to 0, `false` to keep it.
 *              Speculation: Skipping the screen fade progress step is a mistake. It still works because once a fade
 *              is finished, the progress variable will be reset to 0 anyway.
 * @param fadeIn `true` for fade in, `false` for fade out.
 * @param isWhite `true` for white fade, `false` for black fade.
 */
#define ScreenFade_Start(reset, fadeIn, isWhite)                                                                \
    g_Screen_FadeStatus = (((((reset) == true) ? ScreenFadeState_FadeOutStart : ScreenFadeState_FadeOutSteps) + \
                            (((fadeIn) == true) ? 4 : 0)) |                                                     \
                           (((isWhite) == true) ? (1 << 3) : 0))

/** @brief Resets the screen fade. */
#define ScreenFade_Reset() \
    g_Screen_FadeStatus = ScreenFadeState_Reset

/** @brief Resets the custom screen fade timestep back to zero, disregarding the color bit. */
#define ScreenFade_ResetTimestep() \
    g_Screen_FadeStatus = ScreenFadeState_ResetTimestep

#define MAP_CHUNK_CHECK_VARIABLE_DECL() \
    s32 __chunkIdx

/** @hack This macro requires a variable `s32 __chunkIdx` to be declared before using it.
 * The macro `MAP_CHUNK_CHECK_VARIABLE_DECL` declares that variable and must be called before this macro.
 * The first argument is `vx` or `vz`, which is used as the component name in `VECTOR3`.
 * @bug Some maps appear to have a bug where the negative position check will never be true because they check
 * if the chunk index will be a positive number. Seems like they forgot to use `ABS`?
 */
#define PLAYER_IN_MAP_CHUNK(comp, x0, x1, x2, x3)                                                \
    (__chunkIdx = g_SysWork.playerWork.player.position.comp / Q12(40.0f),                        \
     ((g_SysWork.playerWork.player.position.comp >  Q12(0.0f) && (__chunkIdx + (x0)) == (x1)) || \
      (g_SysWork.playerWork.player.position.comp <= Q12(0.0f) && (__chunkIdx + (x2)) == (x3))))

#define PLAYER_NOT_IN_MAP_CHUNK(comp, x0, x1, x2, x3)                                            \
    (__chunkIdx = g_SysWork.playerWork.player.position.comp / Q12(40.0f),                        \
     ((g_SysWork.playerWork.player.position.comp >  Q12(0.0f) && (__chunkIdx + (x0)) != (x1)) || \
      (g_SysWork.playerWork.player.position.comp <= Q12(0.0f) && (__chunkIdx + (x2)) != (x3))))

#define MAP_CHUNK_CHECK_VARIABLE_DECL_2() \
    s32 __chunkIdx2

#define PLAYER_IN_MAP_CHUNK_2(comp, x0, x1, x2, x3)                                              \
    (__chunkIdx2 = g_SysWork.playerWork.player.position.comp / Q12(40.0f),                       \
     ((g_SysWork.playerWork.player.position.comp >  Q12(0.0f) && (__chunkIdx2 + (x0)) < (x1)) || \
      (g_SysWork.playerWork.player.position.comp <= Q12(0.0f) && (__chunkIdx2 + (x2)) < (x3))))

#define PLAYER_NEAR_POS(comp, base, tol)                                                                                                             \
    (((g_SysWork.playerWork.player.position.comp - Q12(base)) >= Q12(0.0f)) ? ((g_SysWork.playerWork.player.position.comp - Q12(base)) < Q12(tol)) : \
                                                                              ((Q12(base) - g_SysWork.playerWork.player.position.comp) < Q12(tol)))

#define MIN_OFFSET(x, neg, pos) \
    ((((x) + (-neg)) <= ((x) + (pos))) ? ((x) - (neg)) : ((x) + (pos)))

#define MAX_OFFSET(x, neg, pos) \
    ((((x) - (neg)) > ((x) + (pos))) ? ((x) - (neg)) : ((x) + (pos)))

/** @brief Packs XZ cell coordinates in a single value.
 *
 * @param x X cell coordinate.
 * @param z Z cell coordinate.
 * @return Packed XZ cell coordinates.
 */
#define CELL_XZ(x, z) \
    ((x) + ((z) << 8))

#define HAS_FLAG(ptr, idx) \
    ((((u32*)ptr)[(idx) >> 5] >> ((idx) & 0x1F)) & (1 << 0))

#define SET_FLAG(ptr, idx) \
    ((((u32*)ptr)[(idx) >> 5] |= (1 << 0) << ((idx) & 0x1F)))

#define CLEAR_FLAG(ptr, idx) \
    ((((u32*)ptr)[(idx) >> 5] &= ~((1 << 0) << ((idx) & 0x1F))))

/** @brief Character group flags. Used by `s_SysWork::charaGroupFlags`. */
typedef enum _CharaGroupFlags
{
    CharaGroupFlag_None = 0,
    CharaGroupFlag_0    = 1 << 0,
    CharaGroupFlag_1    = 1 << 1
} e_CharaGroupFlags;

/** @brief Character collision states. */
typedef enum _CharaCollisionState
{
    CharaCollisionState_Ignore = 0,
    CharaCollisionState_Player = 1,
    CharaCollisionState_2      = 2,
    CharaCollisionState_Npc    = 3,
    CharaCollisionState_4      = 4,
    CharaCollisionState_5      = 5
} e_CharaCollisionState;

/** @brief Sync modes used by `DrawSync` and `VSync`. */
typedef enum _SyncMode
{
    SyncMode_Count     = -1,
    SyncMode_Wait      = 0,
    SyncMode_Immediate = 1,
    SyncMode_Wait2     = 2,
    SyncMode_Wait3     = 3,
    SyncMode_Wait8     = 8
} e_SyncMode;

typedef enum _DmsIntervalState
{
    DmsIntervalState_Interpolating = 0,
    DmsIntervalState_SingleFrame   = 1,
    DmsIntervalState_Ending        = 2
} e_DmsIntervalState;

/** @brief Screen fade states used by `g_Screen_FadeStatus`. The flow is not linear. */
typedef enum _ScreenFadeState
{
    ScreenFadeState_Reset           = 0,
    ScreenFadeState_None            = 1,
    ScreenFadeState_FadeOutStart    = 2,
    ScreenFadeState_FadeOutSteps    = 3,
    ScreenFadeState_ResetTimestep   = 4,
    ScreenFadeState_FadeOutComplete = 5,
    ScreenFadeState_FadeInStart     = 6,
    ScreenFadeState_FadeInSteps     = 7
} e_ScreenFadeState;

/** @brief Map message indices.
 *
 * @note Each map has its own messages, with the first 15 hardcoded to be the same.
 */
typedef enum _MapMsgIdx
{
    MapMsgIdx_Yes               = 0,
    MapMsgIdx_No                = 1,
    MapMsgIdx_SaveGame          = 2, // "Someday, someone may experience..."
    MapMsgIdx_NoMap             = 3,
    MapMsgIdx_TooDarkForMap     = 4,
    MapMsgIdx_FirstAidSelect    = 5,
    MapMsgIdx_HealthDrinkSelect = 6,
    MapMsgIdx_AmpouleSelect     = 7,
    MapMsgIdx_HandgunAmmoSelect = 8,
    MapMsgIdx_RifleAmmoSelect   = 9,
    MapMsgIdx_ShotgunAmmoSelect = 10,
    MapMsgIdx_DoorJammed        = 11,
    MapMsgIdx_DoorLocked        = 12,
    MapMsgIdx_DoorUnlocked      = 13,
    MapMsgIdx_NowMaking         = 14 // @unused?
} e_MapMsgIdx;

typedef enum _MapMsgCode
{
    MapMsgCode_None        = 0,
    MapMsgCode_Select2     = 2,
    MapMsgCode_Select3     = 3,
    MapMsgCode_Select4     = 4,
    MapMsgCode_DisplayAll  = 20,
    MapMsgCode_SetByT      = 88,
    MapMsgCode_AlignCenter = 99
} e_MapMsgCode;

/** @brief Map message states.
 *
 * Return states used by `MapMsg_Draw`.
 */
typedef enum _MapMsgState
{
    MapMsgState_Finish       = NO_VALUE, /** Initial setup complete, cutscene timer complete, or input to continue from user received. */
    MapMsgState_Idle         = 0,        /** Continue displaying message. */
    MapMsgState_SelectEntry0 = 1,        /** First entry selected in selection dialog. */
    MapMsgState_SelectEntry1 = 2,        /** Second entry selected in selection dialog. */
    MapMsgState_SelectEntry2 = 3         /** Third entry selected in selection dialog. */
} e_MapMsgState;

typedef enum _MapMsgAudioLoadBlock
{
    MapMsgAudioLoadBlock_None = 0, // TODO: Some code checks only for bit 0, so it should mean something.
    MapMsgAudioLoadBlock_Unk1 = 1,
    MapMsgAudioLoadBlock_J2   = 3  // `J2` map messages set this, causing voice audio to not load.
                                   // `J2` cutscenes use single audio file for all lines (e.g. video tape cutscene).
} e_MapMsgAudioLoadBlock;

/** @brief Playable map indices. Used for binary overlays. */
typedef enum _MapIdx
{
    MapIdx_MAP0_S00 = 0,
    MapIdx_MAP0_S01 = 1,
    MapIdx_MAP0_S02 = 2,
    MapIdx_MAP1_S00 = 3,
    MapIdx_MAP1_S01 = 4,
    MapIdx_MAP1_S02 = 5,
    MapIdx_MAP1_S03 = 6,
    MapIdx_MAP1_S04 = 7,
    MapIdx_MAP1_S05 = 8,
    MapIdx_MAP1_S06 = 9,
    MapIdx_MAP2_S00 = 10,
    MapIdx_MAP2_S01 = 11,
    MapIdx_MAP2_S02 = 12,
    MapIdx_MAP2_S03 = 13,
    MapIdx_MAP2_S04 = 14,
    MapIdx_MAP3_S00 = 15,
    MapIdx_MAP3_S01 = 16,
    MapIdx_MAP3_S02 = 17,
    MapIdx_MAP3_S03 = 18,
    MapIdx_MAP3_S04 = 19,
    MapIdx_MAP3_S05 = 20,
    MapIdx_MAP3_S06 = 21,
    MapIdx_MAP4_S00 = 22,
    MapIdx_MAP4_S01 = 23,
    MapIdx_MAP4_S02 = 24,
    MapIdx_MAP4_S03 = 25,
    MapIdx_MAP4_S04 = 26,
    MapIdx_MAP4_S05 = 27,
    MapIdx_MAP4_S06 = 28,
    MapIdx_MAP5_S00 = 29,
    MapIdx_MAP5_S01 = 30,
    MapIdx_MAP5_S02 = 31,
    MapIdx_MAP5_S03 = 32,
    MapIdx_MAP6_S00 = 33,
    MapIdx_MAP6_S01 = 34,
    MapIdx_MAP6_S02 = 35,
    MapIdx_MAP6_S03 = 36,
    MapIdx_MAP6_S04 = 37,
    MapIdx_MAP6_S05 = 38,
    MapIdx_MAP7_S00 = 39,
    MapIdx_MAP7_S01 = 40,
    MapIdx_MAP7_S02 = 41,
    MapIdx_MAP7_S03 = 42,
    MapIdx_MAPT_S00 = 43, // } @unused Empty test maps. Only some code references remain and `HB_MTS00.ANM`/`HB_MTX00.ANM` anim files.
    MapIdx_MAPX_S00 = 44  // }
} e_MapIdx;

/** @brief Paper map indices. Used for the navigation map screen. */
typedef enum _PaperMapIdx
{
    PaperMapIdx_OtherPlaces    = 0,
    PaperMapIdx_OldTown        = 1,
    PaperMapIdx_FogCentralTown = 2,
    PaperMapIdx_AltCentralTown = 3,
    PaperMapIdx_ResortTown     = 4,
    PaperMapIdx_FogSchoolBF    = 5,
    PaperMapIdx_FogSchool1F    = 6,
    PaperMapIdx_FogSchool2F    = 7,
    PaperMapIdx_FogSchoolRF    = 8,
    PaperMapIdx_AltSchoolBF    = 9,
    PaperMapIdx_AltSchool1F    = 10,
    PaperMapIdx_AltSchool2F    = 11,
    PaperMapIdx_AltSchoolRF    = 12,
    PaperMapIdx_FogSewer1F     = 13,
    PaperMapIdx_FogSewer2F     = 14,
    PaperMapIdx_AltSewer       = 15,
    PaperMapIdx_FogHospitalBF  = 16,
    PaperMapIdx_FogHospital1F  = 17,
    PaperMapIdx_FogHospital2F  = 18,
    PaperMapIdx_FogHospital3F  = 19,
    PaperMapIdx_AltHospitalBF  = 20,
    PaperMapIdx_AltHospital1F  = 21,
    PaperMapIdx_AltHospital2F  = 22,
    PaperMapIdx_AltHospital3F  = 23
} e_PaperMapIdx;

/** @brief Background music status flags. */
typedef enum _BgmStatusFlags
{
    BgmStatusFlag_None        = 0,
    BgmStatusFlag_Pause       = 1 << 0,
    BgmStatusFlag_ApplyMute   = 1 << 1,
    BgmStatusFlag_RadioActive = 1 << 2,
    BgmStatusFlag_Duck        = 1 << 3,
    BgmStatusFlag_4           = 1 << 4,
    BgmStatusFlag_VoiceDialog = 1 << 5,
    BgmStatusFlag_6           = 1 << 6, // Something to do with the radio?
    BgmStatusFlag_RequestMute = 1 << 7
} e_BgmStatusFlags;

// Temp name.
typedef enum _UnkSysFlags
{
    UnkSysFlag_None     = 0,
    UnkSysFlag_0        = 1 << 0,
    UnkSysFlag_1        = 1 << 1, // Demo in progress?

    UnkSysFlag_3        = 1 << 3,
    UnkSysFlag_4        = 1 << 4,
    UnkSysFlag_5        = 1 << 5, /** Related to camera. */
    UnkSysFlag_6        = 1 << 6,
    UnkSysFlag_MenuOpen = 1 << 7, /** Set by `SysState_Gameplay_Update` when opening the menu and cleared when returning to `SysState_Gameplay` once screen fade has completed. */
    UnkSysFlag_8        = 1 << 8,
    UnkSysFlag_9        = 1 << 9,
    UnkSysFlag_10       = 1 << 10
} e_UnkSysFlags;

/** @brief System process flags. */
typedef enum _ProcessFlags
{
    ProcessFlag_None              = 0,
    ProcessFlag_RoomTransition    = 1 << 0,
    ProcessFlag_OverlayTransition = 1 << 1,
    ProcessFlag_NewGame           = 1 << 2,
    ProcessFlag_LoadSave          = 1 << 3,
    ProcessFlag_Continue          = 1 << 4,
    ProcessFlag_BootDemo          = 1 << 5
} e_ProcessFlags;

typedef enum _ControllerFlags
{
    ControllerFlag_None         = 0,
    ControllerFlag_Select       = 1 << 0,  // 0x1
    ControllerFlag_L3           = 1 << 1,  // 0x2
    ControllerFlag_R3           = 1 << 2,  // 0x4
    ControllerFlag_Start        = 1 << 3,  // 0x8
    ControllerFlag_DpadUp       = 1 << 4,  // 0x10
    ControllerFlag_DpadRight    = 1 << 5,  // 0x20
    ControllerFlag_DpadDown     = 1 << 6,  // 0x40
    ControllerFlag_DpadLeft     = 1 << 7,  // 0x80
    ControllerFlag_L2           = 1 << 8,  // 0x100
    ControllerFlag_R2           = 1 << 9,  // 0x200
    ControllerFlag_L1           = 1 << 10, // 0x400
    ControllerFlag_R1           = 1 << 11, // 0x800
    ControllerFlag_Triangle     = 1 << 12, // 0x1000
    ControllerFlag_Circle       = 1 << 13, // 0x2000
    ControllerFlag_Cross        = 1 << 14, // 0x4000
    ControllerFlag_Square       = 1 << 15, // 0x8000
    ControllerFlag_LStickUp2    = 1 << 16, // 0x10000
    ControllerFlag_LStickRight2 = 1 << 17, // 0x20000
    ControllerFlag_LStickDown2  = 1 << 18, // 0x40000
    ControllerFlag_LStickLeft2  = 1 << 19, // 0x80000
    ControllerFlag_RStickUp     = 1 << 20, // 0x100000
    ControllerFlag_RStickRight  = 1 << 21, // 0x200000
    ControllerFlag_RStickDown   = 1 << 22, // 0x400000
    ControllerFlag_RStickLeft   = 1 << 23, // 0x800000
    ControllerFlag_LStickUp     = 1 << 24, // 0x1000000
    ControllerFlag_LStickRight  = 1 << 25, // 0x2000000
    ControllerFlag_LStickDown   = 1 << 26, // 0x4000000
    ControllerFlag_LStickLeft   = 1 << 27  // 0x8000000
} e_ControllerFlags;

/** @brief Character flags. Used by `s_SubCharacter::flags`. */
typedef enum _CharaFlags
{
    CharaFlag_None          = 0,
    CharaFlag_PadlockBroken = 1 << 0, /** Only used by Padlock character. */
    CharaFlag_Unk2          = 1 << 1, // Targeted by player?
    CharaFlag_Hit           = 1 << 2, // Associated with recoil-causing hit?
    CharaFlag_Unk4          = 1 << 3,
    CharaFlag_Unk5          = 1 << 4, // Camera-related. Only used by Stalker? Maybe only for alley scenario?
    CharaFlag_Damaged       = 1 << 5,
    CharaFlag_Dead          = 1 << 6, // Unure.
    CharaFlag_Unk8          = 1 << 7,
    CharaFlag_Unk9          = 1 << 8  // Only set for bosses and NPCs in special scenarios.
} e_CharaFlags;

/** @brief Character animation flags. */
typedef enum _AnimFlags
{
    AnimFlag_None     = 0,
    AnimFlag_Unlocked = 1 << 0,
    AnimFlag_Visible  = 1 << 1
} e_AnimFlags;

/** @brief State IDs used by the main game loop. The values are used as indices into the `g_GameStateUpdateFuncs` function array. */
typedef enum _GameState
{
    GameState_Init                = 0,
    GameState_KonamiLogo          = 1,
    GameState_KcetLogo            = 2,
    GameState_MovieIntroFadeIn    = 3,
    GameState_AutoLoadSavegame    = 4,
    GameState_MovieIntroAlternate = 5,
    GameState_MovieIntro          = 6,
    GameState_MainMenu            = 7,
    GameState_LoadSavegameScreen  = 8,
    GameState_MovieOpening        = 9,
    GameState_MainLoadScreen      = 10,
    GameState_InGame              = 11,
    GameState_MapEvent            = 12,
    GameState_ExitMovie           = 13,
    GameState_InventoryScreen     = 14,
    GameState_MapScreen           = 15,
    GameState_SaveScreen          = 16,
    GameState_DebugMoviePlayer    = 17,
    GameState_OptionScreen        = 18,
    GameState_LoadStatusScreen    = 19,
    GameState_LoadMapScreen       = 20,
    GameState_Unk15               = 21,
    GameState_Unk16               = 22, /** Removed debug menu? Doesn't exist in function array, but `DebugMoviePlayer` state tries to switch to it. */

    GameState_Hack                = NO_VALUE // @hack Force enum to be treated as s32.
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
    SysState_MapScreen      = 3,
    SysState_Fmv            = 4,
    SysState_LoadOverlay    = 5,
    SysState_LoadRoom       = 6, // Alternative: SysState_LoadArea
    SysState_ReadMessage    = 7,
    SysState_SaveMenu0      = 8,
    SysState_SaveMenu1      = 9,
    SysState_EventCallback  = 10,
    SysState_EventSetFlag   = 11,
    SysState_EventPlaySound = 12,
    SysState_GameOver       = 13,
    SysState_GamePaused     = 14,
    SysState_Invalid        = 15 /** Used by `Event_Update` to signal that SysState shouldn't be updated. */
} e_SysState;

/** @brief Attack input types. Packed into a weapon attack using `WEAPON_ATTACK`. */
typedef enum _AttackInputType
{
    AttackInputType_Tap      = 0,
    AttackInputType_Hold     = 1,
    AttackInputType_Multitap = 2
} e_AttackInputType;

/** @brief Equipped weapon IDs. Derivative of `e_InvItemId`.
 *
 * TODO: Maybe just "Weapon ID", "equipable item ID", "[something else] item ID"?
 */
typedef enum _EquippedWeaponId
{
    EquippedWeaponId_KitchenKnife   = 0,
    EquippedWeaponId_SteelPipe      = 1,
    EquippedWeaponId_RockDrill      = 2,
    EquippedWeaponId_Unk3           = 3,
    EquippedWeaponId_Hammer         = 4,
    EquippedWeaponId_Chainsaw       = 5,
    EquippedWeaponId_Katana         = 6,
    EquippedWeaponId_Axe            = 7,
    EquippedWeaponId_Kick           = 8,
    EquippedWeaponId_Stomp          = 9,

    EquippedWeaponId_Unk31          = 31, // Larval Stalker attack.
    EquippedWeaponId_Handgun        = 32,
    EquippedWeaponId_HuntingRifle   = 33,
    EquippedWeaponId_Shotgun        = 34,
    EquippedWeaponId_HyperBlaster   = 35,

    EquippedWeaponId_Unk37          = 37, // Split Head attack.

    EquippedWeaponId_Unk44          = 44, // } HangedScratcher attack.
    EquippedWeaponId_Unk45          = 45, // }

    EquippedWeaponId_Unk48          = 48, // } Stalker attack.
    EquippedWeaponId_Unk49          = 49, // }

    EquippedWeaponId_Unk56          = 56, // Puppet Nurse attack.

    EquippedWeaponId_Unk59          = 59, // Float Stinger attack.

    EquippedWeaponId_Unk61          = 61, // Twinfeeler attack.

    EquippedWeaponId_Unk63          = 63, // Cybil or Monster Cybil attack.

    EquippedWeaponId_HandgunBullets = 64, // Monster Cybil attack?
    EquippedWeaponId_RifleShells    = 65, // Monster Cybil attack?
    EquippedWeaponId_ShotgunShells  = 66, // Monster Cybil attack?

    EquippedWeaponId_Unk69          = 69, // Bloodsucker attack.
    EquippedWeaponId_Unk70          = 70, // Kaufmann attack on Dahlia?

    EquippedWeaponId_Flashlight     = 96,
    EquippedWeaponId_PocketRadio    = 97,
    EquippedWeaponId_GasolineTank   = 98
} e_EquippedWeaponId;

/** @brief Player control flags. */
typedef enum _PlayerFlags
{
    PlayerFlag_None           = 0,
    PlayerFlag_Unk0           = 1 << 0,
    PlayerFlag_Shooting       = 1 << 1,
    PlayerFlag_Unk2           = 1 << 2,
    PlayerFlag_WallStopRight  = 1 << 3, /** Use right leg for wall stop. */
    PlayerFlag_Unk4           = 1 << 4,
    PlayerFlag_Unk5           = 1 << 5, // `PlayerFlag_MoveBackward`?
    PlayerFlag_Unk6           = 1 << 6,
    PlayerFlag_Unk7           = 1 << 7,
    PlayerFlag_Unk8           = 1 << 8,
    PlayerFlag_Unk9           = 1 << 9,
    PlayerFlag_Unk10          = 1 << 10, // `PlayerFlag_MeleeAttack`?
    PlayerFlag_Unk11          = 1 << 11, // `PlayerFlag_GunAttack`?
    PlayerFlag_Unk12          = 1 << 12,
    PlayerFlag_SfxActive      = 1 << 13,
    PlayerFlag_DamageReceived = 1 << 14,
    PlayerFlag_Moving         = 1 << 15,
    PlayerFlag_Unk16          = 1 << 16,
    PlayerFlag_Unk17          = 1 << 17,
    PlayerFlag_Unk18          = 1 << 18,
    PlayerFlag_Unk19          = 1 << 19,
    PlayerFlag_Unk20          = 1 << 20,

    PlayerFlag_Unk28          = 1 << 28,
    PlayerFlag_Unk29          = 1 << 29,
    PlayerFlag_Unk30          = 1 << 30,
    PlayerFlag_Unk31          = 1 << 31
} e_PlayerFlags;

/** @brief Character IDs. The `CHARA_FILE_INFOS` array associates each character ID with asset files. */
typedef enum _CharaId
{
    Chara_None             = 0,
    Chara_Harry            = 1,
    Chara_AirScreamer      = 2,
    Chara_NightFlutter     = 3,
    Chara_Groaner          = 4,
    Chara_Wormhead         = 5,
    Chara_LarvalStalker    = 6,
    Chara_Stalker          = 7,
    Chara_GreyChild        = 8,
    Chara_Mumbler          = 9,
    Chara_HangedScratcher  = 10,
    Chara_Creeper          = 11,
    Chara_Romper           = 12,
    Chara_Chicken          = 13, /** @unused */
    Chara_SplitHead        = 14,
    Chara_Floatstinger     = 15,
    Chara_PuppetNurse      = 16,
    Chara_DummyNurse       = 17, /** Uses dummy anim file without model/texture, but the same update funcptr as `Chara_PuppetNurse`. */
    Chara_PuppetDoctor     = 18,
    Chara_DummyDoctor      = 19, /** Uses dummy anim file without model/texture, but the same update funcptr as `Chara_PuppetDoctor`. */
    Chara_Twinfeeler       = 20,
    Chara_Bloodsucker      = 21,
    Chara_Incubus          = 22,
    Chara_Unknown23        = 23,
    Chara_MonsterCybil     = 24,
    Chara_LockerDeadBody   = 25,
    Chara_Cybil            = 26,
    Chara_EndingCybil      = 27,
    Chara_Cheryl           = 28,
    Chara_Cat              = 29,
    Chara_Dahlia           = 30,
    Chara_EndingDahlia     = 31,
    Chara_Lisa             = 32,
    Chara_BloodyLisa       = 33,
    Chara_Alessa           = 34,
    Chara_GhostChildAlessa = 35,
    Chara_Incubator        = 36,
    Chara_BloodyIncubator  = 37,
    Chara_Kaufmann         = 38,
    Chara_EndingKaufmann   = 39,
    Chara_Flauros          = 40,
    Chara_LittleIncubus    = 41,
    Chara_GhostDoctor      = 42,
    Chara_Parasite         = 43,
    Chara_Padlock          = 44,

    Chara_Count,

    Chara_Hack = NO_VALUE, // @hack Force enum to be treated as `s32`.
} e_CharaId;

/** @brief Game difficulties. */
typedef enum _GameDifficulty
{
    GameDifficulty_Easy   = -1,
    GameDifficulty_Normal = 0,
    GameDifficulty_Hard   = 1
} e_GameDifficulty;

/** @brief Event trigger types. */
typedef enum _TriggerType
{
    TriggerType_EndOfArray     = NO_VALUE,
    TriggerType_None           = 0, /** Skips trigger/activation type checks. Always activates if required event flags are set and skips processing later events until flags deactivate it. */
    TriggerType_TouchAabb      = 1, /** Player has collided with an AABB. */
    TriggerType_TouchFacing    = 2, /** Player collided with a trigger is facing toward it. */
    TriggerType_TouchObbFacing = 3, /** Player collided with an OBB and is facing toward it. */
    TriggerType_TouchObb       = 4, /** Player collided with an OBB. No facing requirement. */
} e_TriggerType;

/** @brief Event triger activation types. */
typedef enum _TriggerActivationType
{
    TriggerActivationType_None      = 0, /** No activation conditions other than event flag/trigger checks. */
    TriggerActivationType_Exclusive = 1, /** Prevents other events from being triggered while the event is active. */
    TriggerActivationType_Button    = 2, /** Requires a button press. */
    TriggerActivationType_Item      = 3, /** Requires an inventory item. */
} e_TriggerActivationType;

/** Some events indicate specific cutscenes behavior via flags. */
typedef enum _EventDataUnkState
{
    EventParamUnkState_None = 0,
    EventParamUnkState_0    = 1 << 0, /** Possible name: `EventParamUnkState_UnfreezeWorld`. Used to freeze/unfreeze the game world. */
    EventParamUnkState_1    = 1 << 1, /** Triggers cutscenes that go to the in-game mode. */
    EventParamUnkState_2    = 1 << 2
} e_EventDataUnkState;

typedef union
{
    u32 rawData_0;
    struct
    {
        s8 rightX;
        s8 rightY;
        s8 leftX;
        s8 leftY;
    } sticks_0; // Normalized range: `[-128, 127]`.
} s_AnalogSticks;

typedef struct _AnalogController
{
    u8  status;
    u8  received_bytes : 4; /** Number of bytes received / 2. */
    u8  terminal_type  : 4; /** `e_PadTerminalType` */
    u16 digitalButtons;
    u8  rightX;
    u8  rightY;
    u8  leftX;
    u8  leftY;
} s_AnalogController;
STATIC_ASSERT_SIZEOF(s_AnalogController, 8);

typedef struct _ControllerData
{
    s_AnalogController analogController_0;
    s32                pulseTicks_8;
    e_ControllerFlags  btnsHeld_C;
    e_ControllerFlags  btnsClicked_10;
    e_ControllerFlags  btnsReleased_14;
    e_ControllerFlags  btnsPulsed_18;
    e_ControllerFlags  btnsPulsedGui_1C;
    s_AnalogSticks     sticks_20;
    s_AnalogSticks     sticks_24;
    s32                field_28;
} s_ControllerData;
STATIC_ASSERT_SIZEOF(s_ControllerData, 44);

/** @brief Controller key bindings for input actions. Contains bitfield of button presses assigned to each action.
 *
 * Bitfields only contain buttons. Analog directions and D-Pad aren't included.
 */
typedef struct _ControllerConfig
{
    /* 0x0  */ u16 enter;
    /* 0x2  */ u16 cancel;
    /* 0x4  */ u16 skip;
    /* 0x6  */ u16 action;
    /* 0x8  */ u16 aim;
    /* 0xA  */ u16 light;
    /* 0xC  */ u16 run;
    /* 0xE  */ u16 view;
    /* 0x10 */ u16 stepLeft;
    /* 0x12 */ u16 stepRight;
    /* 0x14 */ u16 pause;
    /* 0x16 */ u16 item;
    /* 0x18 */ u16 map;
    /* 0x1A */ u16 option;
} s_ControllerConfig;
STATIC_ASSERT_SIZEOF(s_ControllerConfig, 28);

/** @brief Savegame data. */
typedef struct _Savegame
{
    /* 0x0      */ s_InventoryItem items[INV_ITEM_COUNT_MAX];
    /* 0xA0     */ s8              field_A0;
    /* 0xA1     */ s8              unused_A1[3]; /** @unused */
    /* 0xA4     */ s8              mapIdx;       /** `e_MapIdx` Index to overlay `.BIN` files. */
    /* 0xA5     */ s8              mapRoomIdx;   /** Index to local map geometry `.IPD` files. */
    /* 0xA6     */ s16             savegameCount;
    /* 0xA8     */ s8              locationId;                  /** `e_SaveLocationId` */
    /* 0xA9     */ u8              paperMapIdx;                 /** `e_PaperMapIdx` | Index of the paper map displayed when opening the map screen. */
    /* 0xAA     */ u8              equippedWeapon;              /** `e_InvItemId` | Affects the visible player weapon model. */
    /* 0xAB     */ u8              inventorySlotCount;          /** Item slots. */
    /* 0xAC     */ u32             itemToggleFlags;             /** `e_ItemToggleFlags` */
    /* 0xB0     */ s32             ovlEnemyStates[Chara_Count]; /** Flags indicating the enemy states in a given overlay.
                                                                 * All set to 1 by default. As soon as they are killed (not just stunned),
                                                                 * set to 0 based on a currently unknown index value.
                                                                 */
    /* 0x164    */ s32             hasMapsFlags;                // See Sparagas' `HasMapsFlags` struct for details of every bit.
    /* 0x168    */ u32             eventFlags[52];              // Can be accessed through `Savegame_EventFlagGet` / `Savegame_EventFlagSet`, only tested a few, but seems all are related to events and pick-up flags
                                                                // grouped by location and not item types.
                                                                // Also includes map marking flags - see Sparagas' `MapMarkingsFlags` struct for details of every bit.
    /* 0x238    */ q19_12          healthSaturation;            /** Range: [0, 300]. Ampoules give extra stored health. If the player loses health, it will be slowly restored. */
    /* 0x23C    */ s16             pickedUpItemCount;
    /* 0x23E    */ s8              unused_23E;         /** @unused */
    /* 0x23F    */ u8              inventoryItemFlags; /** `e_InventoryItemFlags` */
    /* 0x240    */ q19_12          playerHealth;       /** Default: `Q12(100.0f)` */
    /* 0x244    */ q19_12          playerPositionX;
    /* 0x248    */ q3_12           playerRotationY;  /** Range [0, 0.999755859375], positive Z: 0, clockwise rotation. It can be multiplied by 360 to get degrees. */
    /* 0x24A    */ u8              clearGameCount;   /** Range [0, 99] */
    /* 0x24B    */ u8              clearGameEndings; /** `e_GameEndingFlags` */
    /* 0x24C    */ q19_12          playerPositionZ;
    /* 0x250    */ q20_12          gameplayTimer;
    /* 0x254    */ q20_12          runDistance;
    /* 0x258    */ q20_12          walkDistance;
    /* 0x25C+0  */ u8              isNextFearMode           : 1; /** `bool` | Makes savegame entry text gold. */
    /* 0x25C+1  */ u8              add290Hours              : 2; /** Adds 290 hours per 1 bit, i.e. 290, 580, 870. */
    /* 0x25C+3  */ u8              pickedUpSpecialItemCount : 5; /** Red/None: 0?, Yellow: 8, Green: 16, @unused Rainbow: 24. */
                                                                 /** Sparagas' investigations indicate this variable should be
                                                                  * two different variables. However, splitting it causes minor
                                                                  * mismatches in some functions.
                                                                  *
                                                                  * The first 3 bits indicate the number of special items the
                                                                  * player has picked up, and the last 2 bits indicate the color of the Hyper
                                                                  * Blaster beam.
                                                                  *
                                                                  * Belek666 suggests that some functions specifically access this field as 5 bits.
                                                                  *
                                                                  * The the odd access results in a bug where the results screen will count more collected
                                                                  * special items than normal by additionally reading one of the two bits
                                                                  * for the Hyper Blaster beam color.
                                                                  */
    /* 0x25D    */ u8              meleeKillCount;
    /* 0x25E    */ u8              meleeKillCountB; // Can't be packed if used as `u16`.
    /* 0x25F    */ u8              rangedKillCount;
    /* 0x260+0  */ u32             field_260      : 28;
    /* 0x260+28 */ s32             gameDifficulty : 4;  /** `e_GameDifficulty` */
    /* 0x264    */ u16             firedShotCount;      /** Missed shot count = firedShotCount - (closeRangeShotCount + midRangeShotCount + longRangeShotCount). */
    /* 0x266    */ u16             closeRangeShotCount; /** Only hits counted. */
    /* 0x268    */ u16             midRangeShotCount;   /** Only hits counted. */
    /* 0x26A    */ u16             longRangeShotCount;  /** Only hits counted. */
    /* 0x26C    */ u16             field_26C;
    /* 0x26E    */ u16             field_26E; // Related to enemy kills.
    /* 0x270    */ u16             field_270;
    /* 0x272    */ u16             field_272;
    /* 0x274    */ u16             field_274;
    /* 0x276    */ u16             field_276;
    /* 0x278    */ u16             field_278;
    /* 0x27A    */ s8              field_27A; // Flags.
    /* 0x27B    */ u8              continueCount;
} s_Savegame;
STATIC_ASSERT_SIZEOF(s_Savegame, 636);

/** TODO: Known as `Trigger` in SilentHillMapExaminer: https://github.com/ItEndsWithTens/SilentHillMapExaminer/blob/master/src/SHME.ExternalTool.Guts/Trigger.cs */
typedef struct _EventData
{
    /* 0x0    */ s16 requiredEventFlag;
    /* 0x2    */ s16 disabledEventFlag;
    /* 0x4+0  */ s8  triggerType    : 4; /** `e_TriggerType` */
    /* 0x4+4  */ u8  activationType : 4; /** `e_TriggerActivationType` */
    /* 0x5    */ u8  pointOfInterestIdx; /** Index into `g_MapOverlayHeader.mapPoints`. */
    /* 0x6    */ u8  requiredItemId;     /** `e_InvItemId` that player must use from item screen. */
    /* 0x7    */ u8  __pad_7;
    /* 0x8+0  */ u32 sysState        : 5; /** `e_SysState` used by the event. */
    /* 0x8+5  */ u32 eventParam      : 8; /** Can be an ID of a `MapMsg`, sound effect, index into `mapEventFuncs`, or index into `mapPoints` for `areaLoad` events. */
    /* 0x8+8  */ u32 flags_8_13      : 6; /** `e_EventDataUnkState` */
    /* 0x8+13 */ u32 sfxPairIdx_8_19 : 5; /** `e_SfxPairIdx` | Index into `SFX_PAIRS`. */
    /* 0x8+19 */ u32 field_8_24      : 1;
    /* 0x8+24 */ u32 mapIdx          : 6;
    /* 0x8+25 */ u32 field_8_31      : 1;
} s_EventData;
STATIC_ASSERT_SIZEOF(s_EventData, 12);

/** @brief User options configuration. */
typedef struct _SaveUserConfig
{
    s_ControllerConfig controllerConfig;
    s8                 optScreenPosX_1C;          /** Range: [-11, 11], default: 0. */
    s8                 optScreenPosY_1D;          /** Range: [-8, 8], default: 0. */
    u8                 optSoundType_1E;           /** `bool` | Stereo: `false`, Monaural: `true`, default: Stereo. */
    u8                 optVolumeBgm_1F;           /** Range: [0, 128] with steps of 8, default: 16. */
    u8                 optVolumeSe_20;            /** Range: [0, 128] with steps of 8, default: 16. */
    u8                 optVibrationEnabled_21;    /** `bool` | Off: 0, On: 128, default: On. */
    u8                 optBrightness_22;          /** Range: [0, 7], default: 3. */
    u8                 optExtraWeaponCtrl_23;     /** `bool` | Switch: `false`, Press: `true`, default: Press. */
    u8                 optExtraBloodColor_24;     /** `e_BloodColor` | Default: Normal. */
    s8                 optAutoLoad_25;            /** `bool` | Off: `false`, On: `true`, default: Off. */
    u8                 __pad_26;
    u8                 optExtraOptionsEnabled_27; /** Holds unlocked option flags. */
    s8                 optExtraViewCtrl_28;       /** `bool` | Normal: `false`, Reverse: `true`, default: Normal. */
    s8                 optExtraViewMode_29;       /** `bool` | Normal: `false`, Self View: `true`, default: Normal. */
    s8                 optExtraRetreatTurn_2A;    /** `bool` | Normal: `false`, Reverse: `true`, default: Normal. */
    s8                 optExtraWalkRunCtrl_2B;    /** `bool` | Normal: `false`, Reverse: `true`, default: Normal. */
    s8                 optExtraAutoAiming_2C;     /** `bool` | On: `false`, Off: `true`, default: On. */
    s8                 optExtraBulletAdjust_2D;   /** x1-x6: Range [0, 5], default: x1. */
    u16                seenGameOverTips_2E[1];    /** Bitfield tracking seen game-over tips. Each bit corresponds to a tip index (0–14), set bits indicate seen tips. Resets after picking all 15. */
    s8                 unk_30[4];
    u32                palLanguageId_34;
} s_SaveUserConfig;
STATIC_ASSERT_SIZEOF(s_SaveUserConfig, 56);

/** @brief Game workspace. Stores miscellaneous gameplay-related data. */
typedef struct _GameWork
{
    /* 0x0   */ s_SaveUserConfig   config;
    /* 0x38  */ s_ControllerData   controllers[CONTROLLER_COUNT_MAX];
    /* 0x90  */ s_Savegame         autosave;
    /* 0x30C */ s_Savegame         savegame;
    /* 0x588 */ u16                gsScreenWidth;
    /* 0x58A */ u16                gsScreenHeight;
    /* 0x58C */ s_PrimColor        background2dColor;
    /* 0x590 */ e_GameState        gameStatePrev;
    /* 0x594 */ e_GameState        gameState;
    /* 0x598 */ s32                gameStateSteps[3]; /** Sub-state steps used by the current `gameState`. Can be other state IDs or data. */
    /* 0x5A4 */ s8                 unk_5A4[4];        // Padding?
    /* 0x5A8 */ s32                field_5A8;
    /* 0x5AC */ s32                field_5AC;
    /* 0x5B0 */ s8                 __pad_5B0;
    /* 0x5B1 */ s8                 mapAnimIdx;
    /* 0x5B2 */ s8                 bgmIdx;            /** `BgmTrackIdx` | Currently player background music track. */
    /* 0x5B4 */ s8                 ambientIdx;        /** Index of `g_AmbientVabTaskLoadCmds`. */
    /* 0x5B4 */ s_AnalogController rawController;
    /* 0x5BC */ s8                 unused_5BC[28];    // @unused Debug data?
} s_GameWork;
STATIC_ASSERT_SIZEOF(s_GameWork, 1496);

/** @brief Extra player character info. */
typedef struct _PlayerExtra
{
    /* 0x0  */ s_Model     model;             /** Manages upper half body's animations (torso, arms, head). */
    /* 0x18 */ s32         disabledAnimBones; /** Bitfield of disabled animation bones. Can be created using the `BITMASK_RANGE` macro. */
    /* 0x1C */ s32         state;             /** `e_PlayerState` */
    /* 0x20 */ s32         upperBodyState;    /** `e_PlayerUpperBodyState` */
    /* 0x24 */ s32         lowerBodyState;    /** `e_PlayerLowerBodyState` */
    /* 0x28 */ e_InvItemId lastUsedItem;      /** Holds the last item ID used from inventory when the player is inside an item trigger area. */
} s_PlayerExtra;
STATIC_ASSERT_SIZEOF(s_PlayerExtra, 44);

/** @brief Player workspace.
 *
 * Possible original name: `shPlayerWork`.
 */
typedef struct _PlayerWork
{
    /* 0x0   */ s_SubCharacter player;
    /* 0x128 */ s_PlayerExtra  extra;
} s_PlayerWork;
STATIC_ASSERT_SIZEOF(s_PlayerWork, 340);

/** @brief Player combat info. */
typedef struct _PlayerCombat
{
    /* 0x0  */ VECTOR3 attackPosition; /** Q19.12 */
    /* 0xC  */ s8      __pad_C[3];
    /* 0xF  */ s8      weaponAttack; /** Packed weapon attack. See `WEAPON_ATTACK`. */
    /* 0x10 */ u8      currentWeaponAmmo;
    /* 0x11 */ u8      totalWeaponAmmo;
    /* 0x12 */ s8      weaponInventoryIdx; /** Index of the currently equipped weapon in the inventory. */
    /* 0x13 */ u8      isAiming;           /** `bool` */
} s_PlayerCombat;
STATIC_ASSERT_SIZEOF(s_PlayerCombat, 20);

typedef union
{
    s32 field_0; // Flags?
    struct
    {
        u8 field_0; // Flags.
        u8 field_1;
        u8 field_2;
        u8 unk_3;
    } s_field_0;
} u_Unk0;

/** @brief Map effects info. */
typedef struct _MapEffectsInfo
{
    u_Unk0  field_0;
    q3_12   field_4; // Alpha.
    q3_12   field_6; // World tint color intensity.
    q3_12   worldTintR_8;
    q3_12   worldTintG_A;
    q3_12   worldTintB_C;
    u8      field_E; // Fog enabled if not set to 0, `Gfx_FogParametersSet` checks for values 0/1/2/3.
                     // Sets the transparent grey layer overlaid on characters and the enviroment.
    q19_12  fogDistance_10;
    CVECTOR fogColor_14;
    u8      field_18; // `bool`?
    CVECTOR field_19;
    CVECTOR screenTint_1D; // Subtractive screen tint.
    CVECTOR field_21;      // Particle effect related. Only the first value affects snow transparency.
    CVECTOR field_25;
    u8      unk_29; // } Padding?
    s16     unk_2A; // }
} s_MapEffectsInfo;
STATIC_ASSERT_SIZEOF(s_MapEffectsInfo, 44);

typedef struct
{
    s_MapEffectsInfo effectsInfo_0;
    q3_12            flashlightLensFlareIntensity_2C; // Stores flashlight lens flare intensity alpha.
    q3_12            field_2E;                        // Some gamma or brightness layer alpha.
    q19_12           field_30;                        // Stores fog distance.
} s_StructUnk3;
STATIC_ASSERT_SIZEOF(s_StructUnk3, 52);

// Extra effects info?
typedef struct
{
    /* 0x0   */ s32             primType_0; /** `e_PrimitiveType` */
    /* 0x4   */ s8*             field_4;    /** Points to different types of data depending on `field_0`. */
    /* 0x8   */ s32             field_8;    // } Q19.12?
    /* 0xC   */ s32             field_C;    // }
    /* 0x10  */ s32             field_10;
    /* 0x14  */ u8              field_14;
    /* 0x15  */ u8              isFlashlightOn_15;          /** `bool` */
    /* 0x16  */ u8              isFlashlightUnavailable_16; /** `bool` */
    /* 0x17  */ s8              __pad_17;
    /* 0x18  */ q3_12           flashlightIntensity_18;
    /* 0x1A  */ u16             field_1A;
    /* 0x1C  */ s_StructUnk3    field_1C[2];
    /* 0x84  */ s_StructUnk3    field_84[2];
    /* 0xEC  */ s_StructUnk3    field_EC[2];
    /* 0x154 */ s_StructUnk3    field_154;
} s_SysWork_2388;
STATIC_ASSERT_SIZEOF(s_SysWork_2388, 392);

/** @brief Main system workspace. Stores key engine data. */
typedef struct _SysWork
{
    /* 0x0      */ s8               unused_0[8]; /** @unused */
    /* 0x8      */ e_SysState       sysState;
    /* 0xC      */ s32              sysStateSteps[3]; /** Temp data used by current `sysState`. Can be another state ID or other data. */
    /* 0x10     */ bool             isMgsStringSet;   /** Indicates if string have been loaded and is going (or it is) being display. */
    /* 0x1C     */ s32              counters_1C[3];
    /* 0x28     */ q19_12           field_28; // Multi-purpose? Used as alpha to fade between images in `Screen_BackgroundImgTransition`.
    /* 0x2C     */ q19_12           timer_2C; // Cutscene message timer?
    /* 0x30     */ s32              cutsceneBorderState;
    /* 0x34     */ s8               unused_34[4]; /** @unused */
    /* 0x38     */ s_PlayerCombat   playerCombat;
    /* 0x4C     */ s_PlayerWork     playerWork;
    /* 0x1A0    */ s_SubCharacter   npcs[NPC_COUNT_MAX];
    /* 0x890    */ GsCOORDINATE2    playerBoneCoords[HarryBone_Count];
    /* 0xE30    */ GsCOORDINATE2    unkCoords_E30[5];                  // Might be part of previous array for 5 extra coords which go unused.
    /* 0xFC0    */ GsCOORDINATE2    npcBoneCoords[NPC_BONE_COUNT_MAX]; // Dynamic coord buffer? 10 coords per NPC (given max of 6 NPCs).
    /* 0x2280   */ s8               npcFlagsId;                        // 1-based NPC ID for `npcFlags`.
    /* 0x2281   */ s8               loadingScreenIdx;
    /* 0x2282   */ s8               field_2282;                         /** `e_EventDataUnkState` */
    /* 0x2283   */ s8               sfxPairIdx_2283;                    /** `e_SfxPairIdx` | Index into `SFX_PAIRS`. */
    /* 0x2284   */ u16              charaGroupFlags[CHARA_GROUP_COUNT]; /** `e_CharaGroupFlags` */
                                                                        // Enabling a flag for Larval Stalkers causes them to die.
    /* 0x228C   */ s32              field_228C[1];
    /* 0x2290   */ s32              npcFlags;       // Flags related to NPCs. Each bit corresponds to an `npcs` array entry.
    /* 0x2294   */ s8               unused_2294[4]; /** @unused */
    /* 0x2298   */ e_ProcessFlags   processFlags;
    /* 0x229C   */ s32              field_229C; /** Dead code. Set to -1 when the player has been initalized and set to 0 when the player changes areas. Beyond that, this variable is unused. */
    /* 0x22A0   */ e_BgmStatusFlags bgmStatusFlags;
    /* 0x22A4   */ e_UnkSysFlags    flags_22A4;       // `UnkSysFlag_6` passed as "use through door cam" flag in `vcSetFirstCamWork`.
    /* 0x22A8   */ GsCOORDINATE2    coord_22A8;       // For particles only?
    /* 0x22F8   */ GsCOORDINATE2    coord_22F8;       // Likely related to above.
    /* 0x2348+0 */ s8               field_2348   : 8; // Related to particles.
    /* 0x2349+0 */ s8               field_2349   : 8; // Particle spawn multiplier?
    /* 0x234A+0 */ u8               field_234A   : 8; /** `bool` */
    /* 0x234B+0 */ u8               field_234B_0 : 4; /** `bool` | Related to particles. Used to trigger SFX? */
    /* 0x234B+4 */ u8               field_234B_4 : 4; // Related to particles.
    /* 0x234C   */ s32              mapMsgTimer;
    /* 0x2350+0 */ u8               enableHighResGlyphs : 4; /** `bool` */
    /* 0x2350+4 */ u8               silentYesSelection  : 4; /** `bool` */
    /* 0x2351+0 */ u32              invItemSelectedIdx  : 8;
    /* 0x2352+0 */ u32              invItemLoadFlags    : 8; /** `e_InvItemLoadFlags` */
    /* 0x2353   */ s8               targetNpcIdx;            /** Index of the NPC in `npcs` being targeted by the player. */
    /* 0x2354   */ s8               npcIdxs[CHARA_GROUP_COUNT];
    /* 0x2358   */ u8               enablePlayerMatchAnim; /** `bool` | Activates the animation performed by Harry when lighting a match at the beginning of the game. */
    /* 0x2359   */ s8               unused_2359;           /** @unused */
    /* 0x235A   */ u8               playerStopFlags;       /** `e_PlayerStopFlags` */
                // 1 byte of padding.
    /* 0x235C   */ GsCOORDINATE2*   field_235C;         // Bone related to pocket light.
    /* 0x2360   */ VECTOR3          pointLightPosition; //                               } Often gets set from DMS cutscene data.
    /* 0x236C   */ GsCOORDINATE2*   field_236C;         // Bone related to pocket light. }
    /* 0x2370   */ SVECTOR          pointLightRotation; //                               }
    /* 0x2378   */ s16              pointLightIntensity;
    /* 0x237A   */ q3_12            cameraAngleY;
    /* 0x237C   */ q3_12            cameraAngleZ;
    /* 0x237E   */ s16              field_237E;
    /* 0x2380   */ q19_12           cameraRadiusXz;
    /* 0x2384   */ q19_12           cameraY_2384;
    /* 0x2388   */ s_SysWork_2388   field_2388;
    /* 0x2510   */ s32              field_2510;
    /* 0x2514   */ s_SysWork_2514   field_2514;
    /* 0x254C   */ s8               field_254C[508]; /** Used through indirect pointer calls. Tied to `lib_unk`.*/
    /* 0x2748   */ q3_12            bgmLayerVolumes[BGM_LAYER_COUNT];
                   // 2 bytes of padding.
    /* 0x275C   */ q19_12           field_275C;
    /* 0x2760   */ s32              field_2760;
    /* 0x2764   */ s32              field_2764;
} s_SysWork;
STATIC_ASSERT_SIZEOF(s_SysWork, 10088);

extern void* g_OvlBodyprog;
extern void* g_OvlDynamic;

extern s_SysWork               g_SysWork;
extern s_GameWork              g_GameWork;
extern s_GameWork* const       g_GameWorkConst;
extern s_GameWork* const       g_GameWorkPtr;
extern s_Savegame* const       g_SavegamePtr;
extern s_ControllerData* const g_Controller0;
extern s_ControllerData* const g_Controller1;

/** @brief Sets `sysState` in `g_SysWork` for the next tick.
 *
 * @param sysState System state to set.
 * @return New system state.
 */
static inline s32 SysWork_StateSetNext(e_SysState sysState)
{
    s32 state;

    state                       =
    g_SysWork.sysState        = sysState;
    g_SysWork.counters_1C[2]          = 0;
    g_SysWork.sysStateSteps[0] = 0;
    g_SysWork.field_28          = 0;//Q12(0.0f);
    g_SysWork.sysStateSteps[1] = 0;
    g_SysWork.timer_2C          = 0;//Q12(0.0f);
    g_SysWork.sysStateSteps[2] = 0;
    return state;
}

/** @brief Increments `sysStateStep` in `g_SysWork` for the next tick.
 *
 * @param stepIdx The `sysStateStep` index to change.
 */
static inline void SysWork_StateStepIncrement(s32 stepIdx)
{
    if (stepIdx == 0)
    {
        g_SysWork.field_28         = 0;//Q12(0.0f);
        g_SysWork.sysStateSteps[1] = 0;
        g_SysWork.timer_2C         = 0;//Q12(0.0f);
        g_SysWork.sysStateSteps[2] = 0;
        g_SysWork.sysStateSteps[0]++;
    }
    else if (stepIdx == 1)
    {
        g_SysWork.timer_2C         = 0;//Q12(0.0f);
        g_SysWork.sysStateSteps[2] = 0;
        g_SysWork.sysStateSteps[1]++;
    }
    else
    {
        g_SysWork.sysStateSteps[2]++;
    }
}

/** @brief Sets `sysStateStep[stepIdx]` in `g_SysWork` for the next tick.
 *
 * @param stepIdx The `sysStateStep` index to change.
 * @param sysStateStep System state step to set.
 * @return New system state step.
 */
static inline s32 SysWork_StateStepSet(s32 stepIdx, s32 sysStateStep)
{
    s32 step;

    if (stepIdx == 0)
    {
        step                        =
        g_SysWork.sysStateSteps[0] = sysStateStep;
        g_SysWork.field_28          = 0;//Q12(0.0f);
        g_SysWork.sysStateSteps[1] = 0;
        g_SysWork.timer_2C          = 0;//Q12(0.0f);
        g_SysWork.sysStateSteps[2] = 0;
    }
    else if (stepIdx == 1)
    {
        step                        =
        g_SysWork.sysStateSteps[1] = sysStateStep;
        g_SysWork.timer_2C          = 0;//Q12(0.0f);
        g_SysWork.sysStateSteps[2] = 0;
    }
    else
    {
        step                        =
        g_SysWork.sysStateSteps[2] = sysStateStep;
    }

    return step;
}

/** @brief Resets `sysStateStep` in `g_SysWork` for the next tick. */
static inline void SysWork_StateStepReset()
{
    g_SysWork.sysStateSteps[0] = NO_VALUE;
    g_SysWork.field_28          = 0;//Q12(0.0f);
    g_SysWork.sysStateSteps[1] = 0;
    g_SysWork.timer_2C          = 0;//Q12(0.0f);
    g_SysWork.sysStateSteps[2] = 0;
}

/** @brief Sets an NPC flag in the `g_SysWork.npcFlags` bitfield.
 *
 * @param flagIdx Index of the NPC flag to set.
 */
static inline void SysWork_NpcFlagSet(s32 flagIdx)
{
    g_SysWork.npcFlags |= 1 << flagIdx;
}

/** @brief Clears an NPC flag in the `g_SysWork.npcFlags` bitfield.
 *
 * @param flagIdx Index of the NPC flag to clear.
 */
static inline void SysWork_NpcFlagClear(s32 flagIdx)
{
    CLEAR_FLAG(&g_SysWork.npcFlags, flagIdx);
}

/** @brief Clears state steps twice for some reason? Only used once below, others use regular `Game_StateSetNext`. */
static inline void Game_StateSetNext_ClearStateSteps(e_GameState gameState)
{
    e_GameState prevState;

    prevState = g_GameWork.gameState;

    g_GameWork.gameState         = gameState;
    g_SysWork.counters_1C[0]        = 0;
    g_SysWork.counters_1C[1]        = 0;
    g_GameWork.gameStateSteps[1] = 0;
    g_GameWork.gameStateSteps[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateSteps[1] = 0;
    g_GameWork.gameStateSteps[2] = 0;
    g_GameWork.gameStateSteps[0] = prevState;
    g_GameWork.gameStatePrev     = prevState;
    g_GameWork.gameStateSteps[0] = 0;
}

/** @brief Sets the GameState to be used in the next game update.
 * Inlined into `stream` and `b_konami`.
 */
static inline void Game_StateSetNext(e_GameState gameState)
{
    e_GameState prevState;

    prevState = g_GameWork.gameState;

    g_GameWork.gameState         = gameState;
    g_SysWork.counters_1C[0]        = 0;
    g_SysWork.counters_1C[1]        = 0;
    g_GameWork.gameStateSteps[1] = 0;
    g_GameWork.gameStateSteps[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateSteps[0] = prevState;
    g_GameWork.gameStatePrev     = prevState;
    g_GameWork.gameStateSteps[0] = 0;
}

/** @brief Returns the GameState to the previously used state.
 * Inlined into credits.
 */
static inline void Game_StateSetPrevious()
{
    e_GameState prevState;

    prevState = g_GameWork.gameState;

    g_SysWork.counters_1C[0]        = 0;
    g_SysWork.counters_1C[1]        = 0;
    g_GameWork.gameStateSteps[1] = 0;
    g_GameWork.gameStateSteps[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateSteps[0] = prevState;
    g_GameWork.gameState         = g_GameWork.gameStatePrev;
    g_GameWork.gameStatePrev     = prevState;
    g_GameWork.gameStateSteps[0] = 0;
}

/** @brief Gets an event flag state from the savegame event flags array.
 *
 * @param flagIdx Event flag index.
 * @return Event flag state (`bool`).
 */
#define Savegame_EventFlagGet(flagIdx) \
    (g_SavegamePtr->eventFlags[(flagIdx) >> 5] & (1 << ((flagIdx) & 0x1F)))

/** @brief Gets an event flag state from the savegame event flags array.
 *
 * @note This alternate version shifts the flags array value by the flag index for some reason
 * and is required for some matches.
 *
 * @param flagIdx Event flag index.
 * @return Event flag state (`bool`).
 */
#define Savegame_EventFlagGetAlt(flagIdx) \
    ((g_SavegamePtr->eventFlags[(flagIdx) >> 5] >> ((flagIdx) & 0x1F)) & (1 << 0))

/** @brief Clears an event flag state in the savegame event flags array.
 *
 * @param flagIdx Event flag index.
 */
#define Savegame_EventFlagClear(flagIdx) \
    (g_SavegamePtr->eventFlags[(flagIdx) >> 5] &= ~(1 << ((flagIdx) & 0x1F)))

/** @brief Sets an event flag state in the savegame event flags array.
 *
 * @param flagIdx Event flag index.
 */
#define Savegame_EventFlagSet(flagIdx) \
    (g_SavegamePtr->eventFlags[(flagIdx) >> 5] |= 1 << ((flagIdx) & 0x1F))

/** @brief Sets an event flag state in the savegame event flags array.
 *
 * @note Some map event code only seems to work with this inline version.
 *
 * @param flagIdx Event flag index.
 */
static inline void Savegame_EventFlagSetAlt(u32 flagIdx)
{
    s16 localIdx;
    s16 localBit;

    localIdx = flagIdx / 32;
    localBit = flagIdx % 32;

    g_SavegamePtr->eventFlags[localIdx] |= 1 << localBit;
}

/** @brief Checks a flag state is `true` in the array of 16-bit flags.
 *
 * @param flags Flag array.
 * @param flagIdx Flag index.
 */
static inline s32 Flags16b_IsSet(const u16* flags, s32 flagIdx)
{
    // @bug `>> 5` divides `flagId` by 32 to get array index, but array contains 16-bit values. Maybe copy-paste from `u32` version of func.
    return (flags[flagIdx >> 5] >> (flagIdx & 0x1F)) & (1 << 0);
}

#endif

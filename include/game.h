#ifndef _GAME_H
#define _GAME_H

#include "event_flags.h"
#include "gpu.h"
#include "types.h"

struct _AnmHeader;
struct _Model;

#define TICKS_PER_SECOND 60                                        /** Game has a variable timestep with 60 ticks max. */
#define TIMESTEP_30_FPS  Q12(1.0f / (float)(TICKS_PER_SECOND / 2)) /** Timestep at 30 FPS. */
#define TIMESTEP_60_FPS  Q12(1.0f / (float)(TICKS_PER_SECOND))     /** Timestep at 60 FPS. */

#define SCREEN_WIDTH                   320
#define SCREEN_HEIGHT                  240
#define FRAMEBUFFER_HEIGHT_PROGRESSIVE 224
#define FRAMEBUFFER_HEIGHT_INTERLACED  (FRAMEBUFFER_HEIGHT_PROGRESSIVE * 2)

#define NPC_COUNT_MAX            6
#define NPC_BONE_COUNT_MAX       10 * NPC_COUNT_MAX
#define GROUP_CHARA_COUNT        4
#define INVENTORY_ITEM_COUNT_MAX 40
#define INPUT_ACTION_COUNT       14
#define SAVEGAME_FOOTER_MAGIC    0xDCDC
#define MEMORY_CARD_SLOT_COUNT   2
#define CONTROLLER_COUNT_MAX     2

#define DEFAULT_PICKUP_ITEM_COUNT      1
#define HANDGUN_AMMO_PICKUP_ITEM_COUNT 15
#define SHOTGUN_AMMO_PICKUP_ITEM_COUNT 6
#define RIFLE_AMMO_PICKUP_ITEM_COUNT   6

#define DEFAULT_MAP_MESSAGE_LENGTH     99
#define MAP_MESSAGE_DISPLAY_ALL_LENGTH 400  /** Long string length is used to display a whole message instantly without a rollout. */
#define GLYPH_TABLE_ASCII_OFFSET       '\'' /** Subtracted from ASCII bytes to get index to some string-related table. */

/** @brief Unknown packed data used for something to do with character model bones.
 *
 * @param a First value.
 * @param b Second value.
 * @return Packed `a` and `b`.
 */
#define UNK_PACKED_DATA(a, b) \
    (s16)((a) | ((b) << 4))

/** @brief Converts a floating-point X screen position in percent to a fixed-point X screen coodinate. */
#define SCREEN_POSITION_X(percent) \
    (s32)(SCREEN_WIDTH * ((percent) / 100.0f))

/** @brief Converts a floating-point Y screen position in percent to a fixed-point Y screen coodinate. */
#define SCREEN_POSITION_Y(percent) \
    (s32)(SCREEN_HEIGHT * ((percent) / 100.0f))

// TODO: Not correct. Should use unions instead.
/** @brief Accessors for low and high parts of each character property, returns a pointer which can be read or written to. */
#define GET_PROPERTY_LOW(prop) \
    ((u16*)&(prop))
#define GET_PROPERTY_HIGH(prop) \
    ((u16*)&(prop) + 1)

/** @brief Checks if a specified map has been collected. */
#define HAS_MAP(mapIdx) \
    ((((u32*)&g_SavegamePtr->hasMapsFlags_164)[(mapIdx) / 32] >> ((mapIdx) % 32)) & (1 << 0))

/** @brief Packs a weapon attack containing a weapon ID and attack input type
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

/** @brief Packs an animation status containing an animation index and active flag.
 *
 * @param animIdx Animation index.
 * @param isActive Active status (`bool`).
 * @return Packed animation status containing the animation index and active flag.
 */
#define ANIM_STATUS(animIdx, isActive) \
    (((animIdx) << 1) | ((isActive) ? (1 << 0) : 0))

/** @brief Retrieves the animation index from a packed animation status.
 *
 * @param animStatus Packed animation status containing an animation index and active flag.
 * @return Anim index.
 */
#define ANIM_STATUS_IDX_GET(animStatus) \
    ((animStatus) >> 1)

/** @brief Checks if an animation is active.
 *
 * @param animStatus Packed animation status containing an animation index and active flag.
 * @return `true` if active, `false` otherwise.
 */
#define ANIM_STATUS_IS_ACTIVE(animStatus) \
    ((animStatus) & (1 << 0))

/** @brief Checks if an animation time is within the keyframe range `[low, high]`.
 *
 * @param animTime Animation time to check.
 * @param low Low keyframe.
 * @param high High keyframe.
 * @return `true` if the animation time is within the keyframe range, `false` otherwise.
 */
#define ANIM_TIME_RANGE_CHECK(animTime, low, high) \
    (FP_FROM(animTime, Q12_SHIFT) >= (low) && FP_FROM(animTime, Q12_SHIFT) <= (high))

/** @brief Creates a bitmask with a contiguous range of bits set.
 * For use with `s_MainCharacterExtra::disabledAnimBones_18`.
 *
 * Generates an `unsigned int` mask with all bits in the range `[fromInclusive, toInclusive]` set.
 *
 * For example:
 * - `BITMASK_RANGE(0, 2)` -> 0b000...0111 (decimal 7)
 * - `BITMASK_RANGE(4, 11)` -> 0b000...111111110000 (decimal 4080)
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

/** @brief Checks if the screen fade is is not in progress (finished step) by masking away the color bit.
 *
 * @return `true` if finished, `false` if still in progress.
 */
#define ScreenFade_IsFinished() \
    ((g_Screen_FadeStatus & 0x7) == ScreenFadeState_FadeOutComplete)

/** @brief Checks if the screen fade is is not in progress (idle step) without masking away the color bit.
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
#define ScreenFade_Start(reset, fadeIn, isWhite) \
    g_Screen_FadeStatus = (((((reset) == true) ? ScreenFadeState_FadeOutStart : ScreenFadeState_FadeOutSteps) + \
                           (((fadeIn) == true) ? 4 : 0)) | \
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
#define PLAYER_IN_MAP_CHUNK(comp, x0, x1, x2, x3)                                                  \
    (__chunkIdx = g_SysWork.player_4C.chara_0.position_18.comp / Q12(40.0f),                       \
     ((g_SysWork.player_4C.chara_0.position_18.comp > Q12(0.0f) && (__chunkIdx + (x0)) == (x1)) || \
      (g_SysWork.player_4C.chara_0.position_18.comp <= Q12(0.0f) && (__chunkIdx + (x2)) == (x3))))

#define PLAYER_NOT_IN_MAP_CHUNK(comp, x0, x1, x2, x3)                                              \
    (__chunkIdx = g_SysWork.player_4C.chara_0.position_18.comp / Q12(40.0f),                       \
     ((g_SysWork.player_4C.chara_0.position_18.comp > Q12(0.0f) && (__chunkIdx + (x0)) != (x1)) || \
      (g_SysWork.player_4C.chara_0.position_18.comp <= Q12(0.0f) && (__chunkIdx + (x2)) != (x3))))

#define PLAYER_NEAR_POS(comp, base, tol) \
    (((g_SysWork.player_4C.chara_0.position_18.comp - Q12(base)) >= 0) ? ((g_SysWork.player_4C.chara_0.position_18.comp - Q12(base)) < Q12(tol)) : ((Q12(base) - g_SysWork.player_4C.chara_0.position_18.comp) < Q12(tol)))

#define HAS_FLAG(ptr, idx) \
    ((((u32*)ptr)[(idx) >> 5] >> ((idx) & 0x1F)) & (1 << 0))

#define SET_FLAG(ptr, idx) \
    ((((u32*)ptr)[(idx) >> 5] |= (1 << 0) << ((idx) & 0x1F)))

#define CLEAR_FLAG(ptr, idx) \
    ((((u32*)ptr)[(idx) >> 5] &= ~((1 << 0) << ((idx) & 0x1F))))

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

/** @brief Map overlay IDs. */
typedef enum _MapOverlayId
{
    MapOverlayId_MAP0_S00 = 0,
    MapOverlayId_MAP0_S01 = 1,
    MapOverlayId_MAP0_S02 = 2,
    MapOverlayId_MAP1_S00 = 3,
    MapOverlayId_MAP1_S01 = 4,
    MapOverlayId_MAP1_S02 = 5,
    MapOverlayId_MAP1_S03 = 6,
    MapOverlayId_MAP1_S04 = 7,
    MapOverlayId_MAP1_S05 = 8,
    MapOverlayId_MAP1_S06 = 9,
    MapOverlayId_MAP2_S00 = 10,
    MapOverlayId_MAP2_S01 = 11,
    MapOverlayId_MAP2_S02 = 12,
    MapOverlayId_MAP2_S03 = 13,
    MapOverlayId_MAP2_S04 = 14,
    MapOverlayId_MAP3_S00 = 15,
    MapOverlayId_MAP3_S01 = 16,
    MapOverlayId_MAP3_S02 = 17,
    MapOverlayId_MAP3_S03 = 18,
    MapOverlayId_MAP3_S04 = 19,
    MapOverlayId_MAP3_S05 = 20,
    MapOverlayId_MAP3_S06 = 21,
    MapOverlayId_MAP4_S00 = 22,
    MapOverlayId_MAP4_S01 = 23,
    MapOverlayId_MAP4_S02 = 24,
    MapOverlayId_MAP4_S03 = 25,
    MapOverlayId_MAP4_S04 = 26,
    MapOverlayId_MAP4_S05 = 27,
    MapOverlayId_MAP4_S06 = 28,
    MapOverlayId_MAP5_S00 = 29,
    MapOverlayId_MAP5_S01 = 30,
    MapOverlayId_MAP5_S02 = 31,
    MapOverlayId_MAP5_S03 = 32,
    MapOverlayId_MAP6_S00 = 33,
    MapOverlayId_MAP6_S01 = 34,
    MapOverlayId_MAP6_S02 = 35,
    MapOverlayId_MAP6_S03 = 36,
    MapOverlayId_MAP6_S04 = 37,
    MapOverlayId_MAP6_S05 = 38,
    MapOverlayId_MAP7_S00 = 39,
    MapOverlayId_MAP7_S01 = 40,
    MapOverlayId_MAP7_S02 = 41,
    MapOverlayId_MAP7_S03 = 42,
    MapOverlayId_MAPT_S00 = 43, // } @unused Empty test maps. Only some code references remain and `HB_MTS00.ANM`/`HB_MTX00.ANM` anim files.
    MapOverlayId_MAPX_S00 = 44  // }
} e_MapOverlayId;

/** @brief Save location IDs. */
typedef enum _SaveLocationId
{
    SaveLocationId_Anywhere    = 0,
    SaveLocationId_Cafe        = 1,
    SaveLocationId_Bus         = 2,
    SaveLocationId_Store       = 3,
    SaveLocationId_Infirmary   = 4,
    SaveLocationId_Doghouse    = 5,
    SaveLocationId_Gordon      = 6,
    SaveLocationId_Church      = 7,
    SaveLocationId_Garage      = 8,
    SaveLocationId_Police      = 9,
    SaveLocationId_Reception   = 10,
    SaveLocationId_Room302     = 11,
    SaveLocationId_Directors   = 12,
    SaveLocationId_JewelryShop = 13,
    SaveLocationId_PoolHall    = 14,
    SaveLocationId_AntiqueShop = 15,
    SaveLocationId_ThemePark   = 16,
    SaveLocationId_Boat        = 17,
    SaveLocationId_Bridge      = 18,
    SaveLocationId_Motel       = 19,
    SaveLocationId_Lighthouse  = 20,
    SaveLocationId_Sewer       = 21,
    SaveLocationId_Nowhere     = 22,
    SaveLocationId_ChildsRoom  = 23,
    SaveLocationId_NextFear    = 24
} e_SaveLocationId;

typedef enum _Current2dMapIdx
{
    Current2dMap_OtherPlaces    = 0,
    Current2dMap_OldTown        = 1,
    Current2dMap_FogCentralTown = 2,
    Current2dMap_AltCentralTown = 3,
    Current2dMap_ResortTown     = 4,
    Current2dMap_FogSchoolBF    = 5,
    Current2dMap_FogSchool1F    = 6,
    Current2dMap_FogSchool2F    = 7,
    Current2dMap_FogSchoolRF    = 8,
    Current2dMap_AltSchoolBF    = 9,
    Current2dMap_AltSchool1F    = 10,
    Current2dMap_AltSchool2F    = 11,
    Current2dMap_AltSchoolRF    = 12,
    Current2dMap_FogSewer1F     = 13,
    Current2dMap_FogSewer2F     = 14,
    Current2dMap_AltSewer       = 15,
    Current2dMap_FogHospitalBF  = 16,
    Current2dMap_FogHospital1F  = 17,
    Current2dMap_FogHospital2F  = 18,
    Current2dMap_FogHospital3F  = 19,
    Current2dMap_AltHospitalBF  = 20,
    Current2dMap_AltHospital1F  = 21,
    Current2dMap_AltHospital2F  = 22,
    Current2dMap_AltHospital3F  = 23
} e_Current2dMapIdx;

// Temp name.
typedef enum _SysFlags
{
    SysFlag_None   = 0,
    SysFlag_Freeze = 1 << 0,
    SysFlag_1      = 1 << 1,
    SysFlag_2      = 1 << 2,
    SysFlag_3      = 1 << 3,
    SysFlag_4      = 1 << 4,
    SysFlag_5      = 1 << 5,
    SysFlag_6      = 1 << 6,
    SysFlag_7      = 1 << 7
} e_SysFlags;

typedef enum _SysWorkProcessFlags
{
    SysWorkProcessFlag_None              = 0,
    SysWorkProcessFlag_RoomTransition    = 1 << 0,
    SysWorkProcessFlag_OverlayTransition = 1 << 1,
    SysWorkProcessFlag_NewGame           = 1 << 2,
    SysWorkProcessFlag_LoadSave          = 1 << 3,
    SysWorkProcessFlag_Continue          = 1 << 4,
    SysWorkProcessFlag_BootDemo          = 1 << 5
} e_SysWorkProcessFlags;

typedef enum _ControllerFlags
{
    ControllerFlag_None         = 0,
    ControllerFlag_Select       = 1 << 0,
    ControllerFlag_L3           = 1 << 1,
    ControllerFlag_R3           = 1 << 2,
    ControllerFlag_Start        = 1 << 3,
    ControllerFlag_DpadUp       = 1 << 4,
    ControllerFlag_DpadRight    = 1 << 5,
    ControllerFlag_DpadDown     = 1 << 6,
    ControllerFlag_DpadLeft     = 1 << 7,
    ControllerFlag_L2           = 1 << 8,
    ControllerFlag_R2           = 1 << 9,
    ControllerFlag_L1           = 1 << 10,
    ControllerFlag_R1           = 1 << 11,
    ControllerFlag_Triangle     = 1 << 12,
    ControllerFlag_Circle       = 1 << 13,
    ControllerFlag_Cross        = 1 << 14,
    ControllerFlag_Square       = 1 << 15,
    ControllerFlag_LStickUp2    = 1 << 16,
    ControllerFlag_LStickRight2 = 1 << 17,
    ControllerFlag_LStickDown2  = 1 << 18,
    ControllerFlag_LStickLeft2  = 1 << 19,
    ControllerFlag_RStickUp     = 1 << 20,
    ControllerFlag_RStickRight  = 1 << 21,
    ControllerFlag_RStickDown   = 1 << 22,
    ControllerFlag_RStickLeft   = 1 << 23,
    ControllerFlag_LStickUp     = 1 << 24,
    ControllerFlag_LStickRight  = 1 << 25,
    ControllerFlag_LStickDown   = 1 << 26,
    ControllerFlag_LStickLeft   = 1 << 27
} e_ControllerFlags;

/** @brief Character flags. Used by `s_SubCharacter::flags_3E`. */
typedef enum _CharaFlags
{
    CharaFlag_None = 0,
    CharaFlag_Unk2 = 1 << 1,
    CharaFlag_Unk3 = 1 << 2,
    CharaFlag_Unk4 = 1 << 3,
    CharaFlag_Unk5 = 1 << 4,
    CharaFlag_Unk6 = 1 << 5,
    CharaFlag_Unk7 = 1 << 6,
    CharaFlag_Unk8 = 1 << 7,
    CharaFlag_Unk9 = 1 << 8
} e_CharaFlags;

/** @brief String color IDs for strings displayed in screen space.
 * Used as indices into `STRING_COLORS`.
 *
 * TODO: Move to `text_draw.h`.
 */
typedef enum _StringColorId
{
    StringColorId_Gold           = 0,
    StringColorId_DarkGrey       = 1,
    StringColorId_Green          = 2,
    StringColorId_Nuclear        = 3,
    StringColorId_Red            = 4,
    StringColorId_GreenDuplicate = 5, // Gives same color as `StringColorId_Green`. Unused?
    StringColorId_LightGrey      = 6,
    StringColorId_White          = 7,

    StringColorId_Count          = 8
} e_StringColorId;

/** @brief Character animation flags. */
typedef enum _AnimFlags
{
    AnimFlag_None     = 0,
    AnimFlag_Unlocked = 1 << 0,
    AnimFlag_Visible  = 1 << 1
} e_AnimFlags;

/** @brief State IDs used by the main game loop. The values are used as indices into the 0x800A977C function array. */
typedef enum _GameState
{
    GameState_Init                = 0,
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
    GameState_InventoryScreen     = 14,
    GameState_MapScreen           = 15,
    GameState_Unk10               = 16,
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
    SysState_LoadArea0      = 5,
    SysState_LoadArea1      = 6,
    SysState_ReadMessage    = 7,
    SysState_SaveMenu0      = 8,
    SysState_SaveMenu1      = 9,
    SysState_EventCallFunc  = 10,
    SysState_EventSetFlag   = 11,
    SysState_EventPlaySound = 12,
    SysState_GameOver       = 13,
    SysState_GamePaused     = 14,
    SysState_Unk15          = 15
} e_SysState;

/** @brief Inventory command IDs. */
typedef enum _InventoryCmdId
{
    InventoryCmdId_UseHealth     = 0, /** Text is "Use", but this one is used exclusively on health items. */
    InventoryCmdId_Use           = 1,
    InventoryCmdId_Equip         = 2,
    InventoryCmdId_Unequip       = 3,
    InventoryCmdId_EquipReload   = 4,
    InventoryCmdId_UnequipReload = 5,
    InventoryCmdId_OnOff         = 6,
    InventoryCmdId_Reload        = 7,
    InventoryCmdId_Look          = 8,
    InventoryCmdId_UseLook       = 9,
    InventoryCmdId_Unk10         = 10,
    InventoryCmdId_Unk11         = 11 // Flashlight in daytime?
} e_InventoryCmdId;

typedef enum _InventoryItemId
{
    InventoryItemId_Empty                 = NO_VALUE,
    InventoryItemId_Unequipped            = 0,

    InventoryItemId_HealthDrink           = 32,
    InventoryItemId_FirstAidKit           = 33,
    InventoryItemId_Ampoule               = 34,

    InventoryItemId_LobbyKey              = 64,
    InventoryItemId_HouseKey              = 65,
    InventoryItemId_KeyOfLion             = 66,
    InventoryItemId_KeyOfWoodman          = 67,
    InventoryItemId_KeyOfScarecrow        = 68,
    InventoryItemId_LibraryReserveKey     = 69,
    InventoryItemId_ClassroomKey          = 70,
    InventoryItemId_KGordonKey            = 71,
    InventoryItemId_DrawbridgeKey         = 72,
    InventoryItemId_BasementKey           = 73,
    InventoryItemId_BasementStoreroomKey  = 74,
    InventoryItemId_ExaminationRoomKey    = 75,
    InventoryItemId_AntiqueShopKey        = 76,
    InventoryItemId_SewerKey              = 77,
    InventoryItemId_KeyOfOphiel           = 78,
    InventoryItemId_KeyOfHagith           = 79,
    InventoryItemId_KeyOfPhaleg           = 80,
    InventoryItemId_KeyOfBethor           = 81,
    InventoryItemId_KeyOfAratron          = 82,
    InventoryItemId_NoteToSchool          = 83,
    InventoryItemId_NoteDoghouse          = 84,
    InventoryItemId_PictureCard           = 85,

    InventoryItemId_SewerExitKey          = 87,
    InventoryItemId_ChannelingStone       = 88,

    InventoryItemId_Chemical              = 96,
    InventoryItemId_GoldMedallion         = 97,
    InventoryItemId_SilverMedallion       = 98,
    InventoryItemId_RubberBall            = 99,
    InventoryItemId_Flauros               = 100,
    InventoryItemId_PlasticBottle         = 101,
    InventoryItemId_UnknownLiquid         = 102,
    InventoryItemId_PlateOfTurtle         = 103,
    InventoryItemId_PlateOfHatter         = 104,
    InventoryItemId_PlateOfCat            = 105,
    InventoryItemId_PlateOfQueen          = 106,
    InventoryItemId_BloodPack             = 107,
    InventoryItemId_DisinfectingAlcohol   = 108,
    InventoryItemId_Lighter               = 109,
    InventoryItemId_VideoTape             = 110,

    InventoryItemId_KaufmannKey           = 112,
    InventoryItemId_Receipt               = 113,
    InventoryItemId_SafeKey               = 114,
    InventoryItemId_Magnet                = 115,
    InventoryItemId_MotorcycleKey         = 116,
    InventoryItemId_BirdCageKey           = 117,
    InventoryItemId_Pliers                = 118,
    InventoryItemId_Screwdriver           = 119,
    InventoryItemId_Camera                = 120,
    InventoryItemId_RingOfContract        = 121,
    InventoryItemId_StoneOfTime           = 122,
    InventoryItemId_AmuletOfSolomon       = 123,
    InventoryItemId_CrestOfMercury        = 124,
    InventoryItemId_Ankh                  = 125,
    InventoryItemId_DaggerOfMelchior      = 126,
    InventoryItemId_DiskOfOuroboros       = 127,

    InventoryItemId_KitchenKnife          = 128,
    InventoryItemId_SteelPipe             = 129,
    InventoryItemId_RockDrill             = 130,

    InventoryItemId_Hammer                = 132,
    InventoryItemId_Chainsaw              = 133,
    InventoryItemId_Katana                = 134,
    InventoryItemId_Axe                   = 135,

    InventoryItemId_Handgun               = 160,
    InventoryItemId_HuntingRifle          = 161,
    InventoryItemId_Shotgun               = 162,
    InventoryItemId_HyperBlaster          = 163,
	
    InventoryItemId_CutscenePhone         = 164,
    InventoryItemId_CutsceneFlauros       = 165,
    InventoryItemId_CutsceneAglaophotis   = 166,
    InventoryItemId_CutscenePlasticBottle = 167,
    InventoryItemId_CutsceneBaby          = 168,
    InventoryItemId_CutsceneBloodPack     = 169,

    InventoryItemId_HandgunBullets        = 192,
    InventoryItemId_RifleShells           = 193,
    InventoryItemId_ShotgunShells         = 194,

    InventoryItemId_Flashlight            = 224,
    InventoryItemId_PocketRadio           = 225,
    InventoryItemId_GasolineTank          = 226
} e_InventoryItemId;


/** @brief Common pickup item IDs. */
typedef enum _CommonPickupItemId
{
    CommonPickupItemId_FirstAidKit    = 0,
    CommonPickupItemId_HealthDrink    = 1,
    CommonPickupItemId_Ampoule        = 2,
    CommonPickupItemId_HandgunBullets = 3,
    CommonPickupItemId_RifleShells    = 4,
    CommonPickupItemId_ShotgunShells  = 5
} e_CommonPickupItemId;

/** @brief Attack input types. Packed into a weapon attack using `WEAPON_ATTACK`. */
typedef enum _AttackInputType
{
	AttackInputType_Tap      = 0,
	AttackInputType_Hold     = 1,
	AttackInputType_Multitap = 2
} e_AttackInputType;

/** @brief Equipped weapon IDs. Derivative of `e_InventoryItemId`.
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
    EquippedWeaponId_Unk8           = 8,
    EquippedWeaponId_Unk9           = 9,

    EquippedWeaponId_Unk31          = 31,
    EquippedWeaponId_Handgun        = 32,
    EquippedWeaponId_HuntingRifle   = 33,
    EquippedWeaponId_Shotgun        = 34,
    EquippedWeaponId_HyperBlaster   = 35,

    EquippedWeaponId_HandgunBullets = 64,
    EquippedWeaponId_RifleShells    = 65,
    EquippedWeaponId_ShotgunShells  = 66,

    EquippedWeaponId_Flashlight     = 96,
    EquippedWeaponId_PocketRadio    = 97,
    EquippedWeaponId_GasolineTank   = 98
} e_EquippedWeaponId;

/** @brief Harry character model bone indices. */
typedef enum _HarryBone
{
    HarryBone_Root          = 0,
    HarryBone_Torso         = 1,
    HarryBone_Head          = 2,
    HarryBone_LeftShoulder  = 3,
    HarryBone_LeftUpperArm  = 4,
    HarryBone_LeftForearm   = 5,
    HarryBone_LeftHand      = 6,
    HarryBone_RightShoulder = 7,
    HarryBone_RightUpperArm = 8,
    HarryBone_RightForearm  = 9,
    HarryBone_RightHand     = 10,
    HarryBone_Hips          = 11,
    HarryBone_LeftThigh     = 12,
    HarryBone_LeftShin      = 13,
    HarryBone_LeftFoot      = 14,
    HarryBone_RightThigh    = 15,
    HarryBone_RightShin     = 16,
    HarryBone_RightFoot     = 17,

    HarryBone_Count         = 18
} s_HarryBone;

/** @brief Player control flags */
typedef enum _PlayerFlags
{
    PlayerFlag_None           = 0,
    PlayerFlag_Unk0           = 1 << 0,
    PlayerFlag_Shooting       = 1 << 1,
    PlayerFlag_Unk2           = 1 << 2,
    PlayerFlag_WallStopRight  = 1 << 3, // Use right leg for wall stop.
    PlayerFlag_Unk4           = 1 << 4,
    PlayerFlag_Unk5           = 1 << 5, // `PlayerFlag_MoveBackward`?
    PlayerFlag_Unk6           = 1 << 6,
    PlayerFlag_Unk7           = 1 << 7,
    PlayerFlag_Unk8           = 1 << 8,
    PlayerFlag_Unk9           = 1 << 9,
    PlayerFlag_Unk10          = 1 << 10, // `PlayerFlag_MeleeAttack`?
    PlayerFlag_Unk11          = 1 << 11, // `PlayerFlag_GunAttack`?
    PlayerFlag_Unk12          = 1 << 12,
    PlayerFlag_Unk13          = 1 << 13,
    PlayerFlag_DamageReceived = 1 << 14,
    PlayerFlag_Moving         = 1 << 15,
    PlayerFlag_Unk16          = 1 << 16,
    PlayerFlag_Unk17          = 1 << 17,
    PlayerFlag_Unk18          = 1 << 18,
    PlayerFlag_Unk19          = 1 << 19,
    PlayerFlag_Unk20          = 1 << 20,

    PlayerFlag_Unk29          = 1 << 29,
    PlayerFlag_Unk30          = 1 << 30,
    PlayerFlag_Unk31          = 1 << 31
} e_PlayerFlags;

/** @brief Unk0 character flags. */
typedef enum _CharaUnk0Flags
{
    CharaUnk0Flag_None  = 0,
    CharaUnk0Flag_Unk0  = 1 << 0,
    CharaUnk0Flag_Unk1  = 1 << 1,
    CharaUnk0Flag_Unk2  = 1 << 2,
    CharaUnk0Flag_Unk3  = 1 << 3,
    CharaUnk0Flag_Unk4  = 1 << 4,
    CharaUnk0Flag_Unk5  = 1 << 5,
    CharaUnk0Flag_Unk6  = 1 << 6,
    CharaUnk0Flag_Unk7  = 1 << 7,
    CharaUnk0Flag_Unk8  = 1 << 8,
    CharaUnk0Flag_Unk9  = 1 << 9,
    CharaUnk0Flag_Unk10 = 1 << 10,
    CharaUnk0Flag_Unk11 = 1 << 11,
    CharaUnk0Flag_Unk12 = 1 << 12,
    CharaUnk0Flag_Unk13 = 1 << 13,
    CharaUnk0Flag_Unk14 = 1 << 14,
    CharaUnk0Flag_Unk15 = 1 << 15,
    CharaUnk0Flag_Unk16 = 1 << 16
} e_CharaUnk0Flags;

/** @brief Character IDs. The `CHARA_FILE_INFOS` array associates each character ID with animimation, model, and texture files. */
typedef enum _CharacterId
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
    Chara_Creaper          = 11,
    Chara_Romper           = 12,
    Chara_Chicken          = 13, /** @unused */
    Chara_Splithead        = 14,
    Chara_Floatstinger     = 15,
    Chara_PuppetNurse      = 16,
    Chara_DummyNurse       = 17, /** Uses dummy anim file without model/texture, but uses same update funcptr as `Chara_PuppetNurse`. */
    Chara_PuppetDoctor     = 18,
    Chara_DummyDoctor      = 19, /** Uses dummy anim file without model/texture, but uses same update funcptr as `Chara_PuppetDoctor`. */
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
} e_CharacterId;

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

typedef enum _GameDifficulty
{
    GameDifficulty_Easy   = -1,
    GameDifficulty_Normal = 0,
    GameDifficulty_Hard   = 1
} e_GameDifficulty;

typedef union
{
    u32 rawData_0;
    struct
    {
        s8 rightX;
        s8 rightY;
        s8 leftX;
        s8 leftY;
    } sticks_0; // Range is `[-128, 127]`?
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

/** @brief Controller key bindings for input actions. Bontains bitfield of button presses assigned to each action.
 *
 * Bitfields only contain buttons. Analog directions and D-Pad aren't included.
 */
typedef struct _ControllerConfig
{
    u16 enter_0;
    u16 cancel_2;
    u16 skip_4;
    u16 action_6;
    u16 aim_8;
    u16 light_A;
    u16 run_C;
    u16 view_E;
    u16 stepLeft_10;
    u16 stepRight_12;
    u16 pause_14;
    u16 item_16;
    u16 map_18;
    u16 option_1A;
} s_ControllerConfig;
STATIC_ASSERT_SIZEOF(s_ControllerConfig, 28);

typedef struct _InventoryItem
{
    u8 id_0;      /** `InventoryItemId` */
    u8 count_1;
    u8 command_2; /** `InventoryCmdId` */
    u8 field_3;   // Some sort of index?
} s_InventoryItem;
STATIC_ASSERT_SIZEOF(s_InventoryItem, 4);

typedef enum _ItemToggleFlags
{
    ItemToggleFlag_RadioOn       = 1 << 0,
    ItemToggleFlag_FlashlightOff = 1 << 1,
} e_ItemToggleFlags;

typedef struct _Savegame
{
    s_InventoryItem items_0[INVENTORY_ITEM_COUNT_MAX];
    s8              field_A0;
    s8              field_A1[3];
    s8              mapOverlayId_A4;          /** `e_MapOverlayId` Index to overlay `.BIN` files. */
    s8              mapRoomIdx_A5;            /** Index to local map geometry `.IPD` files. */
    s16             savegameCount_A6;
    s8              locationId_A8;            /** `e_SaveLocationId` */
    u8              current2dMapIdx_A9;       /** `e_Current2dMapIdx` Index to the 2D map shown when opening the map screen. */
    u8              equippedWeapon_AA;        /** `e_InventoryItemId` Affects only the visible player weapon model. */
    u8              inventorySlotCount_AB;    /** Item slots. */
    u32             itemToggleFlags_AC;       /** `e_ItemToggleFlags` */
    s32             field_B0[45];
    s32             hasMapsFlags_164;         // See Sparagas' `HasMapsFlags` struct for details of every bit.
    u32             eventFlags_168[27];       // Can be accessed through `Savegame_EventFlagGet` / `Savegame_EventFlagSet`, only tested a few, but seems all are related to events and pick-up flags, grouped by location and not item types.
    s32             mapMarkingFlags_1D4[25];  // See Sparagas' `MapMarkingsFlags` struct for details of every bit.
    q19_12          healthSaturation_238;     /** Range: [0, 300]. Ampoules give extra stored health. If the player loses health, it will be slowly restored. */
    s16             pickedUpItemCount_23C;
    s8              field_23E;
    u8              field_23F;
    q19_12          playerHealth_240;         /** Default: `Q12(100.0f)` */
    q19_12          playerPositionX_244;
    q3_12           playerRotationY_248;      /** Range [0, 0.999755859375], positive Z: 0, clockwise rotation. It can be multiplied by 360 to get degrees. */
    u8              clearGameCount_24A;       /** Range [0, 99] */
    u8              clearGameEndings_24B;     /** `e_GameEndingFlags` */
    q19_12          playerPositionZ_24C;
    q20_12          gameplayTimer_250;
    q20_12          runDistance_254;
    q20_12          walkDistance_258;
    u8              isNextFearMode_25C             : 1; /** Makes savegame entry text gold. */
    u8              add290Hours_25C_1              : 2; /** Adds 290 hours per 1 bit, i.e. 290, 580, 870. */
    u8              pickedUpSpecialItemCount_25C_3 : 5; /** Red/None: 0?, Yellow: 8, Green: 16, @unused Rainbow: 24. */
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
    u8              meleeKillCount_25D;
    u8              meleeKillCountB_25E; // Can't be packed if used as `u16`.
    u8              rangedKillCount_25F;
    u32             field_260          : 28;
    s32             gameDifficulty_260 : 4;  /** `e_GameDifficulty`. */
    u16             firedShotCount_264;      /** Missed shot count = firedShotCount - (closeRangeShotCount + midRangeShotCount + longRangeShotCount). */
    u16             closeRangeShotCount_266; /** Only hits counted. */
    u16             midRangeShotCount_268;   /** Only hits counted. */
    u16             longRangeShotCount_26A;  /** Only hits counted. */
    u16             field_26C;
    u16             field_26E; // Related to enemy kills.
    u16             field_270;
    u16             field_272;
    u16             field_274;
    u16             field_276;
    u16             field_278;
    s8              field_27A; // Flags.
    u8              continueCount_27B;
} s_Savegame;
STATIC_ASSERT_SIZEOF(s_Savegame, 636);

/** TODO: Known as `Trigger` in SilentHillMapExaminer: https://github.com/ItEndsWithTens/SilentHillMapExaminer/blob/master/src/SHME.ExternalTool.Guts/Trigger.cs */
typedef struct _EventParam
{
    u8  unk_0[2];
    s16 eventFlagId_2;
    u8 unk_4_0: 4;
    u8 unk_4_4: 4;
    u8  field_5; // Index into `D_800E839C`. Related pickup item SFX.
    u8  unk_6[2];
    u32 triggerType_8_0        : 5;
    u32 pointOfInterestIdx_8_5 : 8; /** Index into `g_MapOverlayHeader.mapPointsOfInterest_1C`. */
    u32 flags_8_13             : 6;
    u32 field_8_19             : 5;
    u32 field_8_24             : 1;
    u32 mapOverlayIdx_8_25     : 6;
    u32 field_8_31             : 1;
} s_EventParam;
STATIC_ASSERT_SIZEOF(s_EventParam, 12);

typedef struct _SaveUserConfig
{
    s_ControllerConfig controllerConfig_0;
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
    u8                 unk_26;                    // Padding?
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

/** @brief Appended to `ShSavegame` and `ShSaveUserConfig` during game save. Contains 8-bit XOR checksum + magic.
 * Checksum generated via `Savegame_ChecksumGenerate`.
 */
typedef struct _SavegameFooter
{
    u8  checksum_0[2];
    u16 magic_2;
} s_SavegameFooter;
STATIC_ASSERT_SIZEOF(s_SavegameFooter, 4);

/** @brief Contains `s_Savegame` data with the footer appended to the end containing the checksum + magic. */
typedef struct _SavegameContainer
{
    s_Savegame       savegame_0;
    s_SavegameFooter footer_27C;
} s_SavegameContainer;
STATIC_ASSERT_SIZEOF(s_SavegameContainer, 640);

/** @brief Contains `s_SaveUserConfig` data padded to 128 bytes, with footer at the end containing checksum + magic. */
typedef struct _SaveUserConfigContainer
{
    s_SaveUserConfig config_0;
    u8               pad_38[68];
    s_SavegameFooter footer_7C;
} s_SaveUserConfigContainer;

typedef struct _GameWork
{
    s_SaveUserConfig   config_0;
    s_ControllerData   controllers_38[CONTROLLER_COUNT_MAX];
    s_Savegame         autosave_90;
    s_Savegame         savegame_30C;
    u16                gsScreenWidth_588;
    u16                gsScreenHeight_58A;
    u8                 background2dColor_R_58C;
    u8                 background2dColor_G_58D;
    u8                 background2dColor_B_58E;
    u8                 field_58F;            // Command code? Maybe `s_PrimColor` fits here.
    e_GameState        gameStatePrev_590;
    e_GameState        gameState_594;
    s32                gameStateStep_598[3]; /** Temp data used by current `gameState`. Can be another state ID or other data. 
                                              * This states could be sub-states for specific events of individual screens
                                              * because of the way it's normally used in menus. For example: in the settings
                                              * screen, [0] is used to define what option the player has selected, and [1] is used
                                              * during specific settings screens, such as the position screen or the brightness screen.
                                              *
                                              * [2] is likely rarely used or maybe only used during maps.
                                              */
    s8                 unk_5A4[4];
    s32                field_5A8;
    s32                field_5AC;
    s8                 unk_5B0;
    s8                 mapAnimIdx_5B1;
    s8                 soundCmd_5B2;
    s8                 field_5B3;
    s_AnalogController rawController_5B4;
    s8                 unk_5BC[28];
} s_GameWork;
STATIC_ASSERT_SIZEOF(s_GameWork, 1496);

/** @brief Const data passed over to `Anim_Update` funcs. Struct itself contains which `Anim_Update` func is to be called. */
typedef struct _AnimInfo
{
    void (*updateFunc_0)(struct _Model* model, struct _AnmHeader* anmHdr, GsCOORDINATE2* coords, struct _AnimInfo* animInfo);
    u8 status_4;                 /** Packed anim status. Init base? See `s_ModelAnimData::status_0`. */
    s8 hasVariableDuration_5;    /** `bool` | Use `duration_8.variableFunc`: `true`, Use `duration_8.constant`: `false`. */
    u8 status_6;                 /** Packed anim status. Link target? Sometimes `NO_VALUE`, unknown why. See `s_ModelAnim::status_0`. */
    // 1 byte of padding.
    union
    {
        q19_12 constant;          /** Constant duration at 30 FPS. */
        q19_12 (*variableFunc)(void); /** Variable duration at 30 FPS via a function. Allows animations to be sped up or slowed down. */
    } duration_8;
    s16 startKeyframeIdx_C;       /** Start keyframe index. Sometimes `NO_VALUE`, unknown why. */
    s16 endKeyframeIdx_E;         /** End keyframe index. */
} s_AnimInfo;
STATIC_ASSERT_SIZEOF(s_AnimInfo, 16);

typedef struct _ModelAnim
{
    u8          status_0;         /** Is active: bit 0, Anim index: bits 1-7. Possible original name: `anim_status`. */
    u8          maybeSomeState_1; // State says if `time_4` is anim time/anim status or a func ptr? That field could be a union.
    u16         flags_2;          /** `e_AnimFlags` */
    q19_12      time_4;           /** Time on timeline. */ 
    s16         keyframeIdx_8;    /** Active keyframe index. */
    q3_12       alpha_A;          /** Keyframe progress alpha. Rename to `keyframeAlpha_A`? */ 
    s_AnimInfo* animInfo_C;       // } Arrays of anim infos?
    s_AnimInfo* animInfo_10;      // }
} s_ModelAnim;
STATIC_ASSERT_SIZEOF(s_ModelAnim, 20);

typedef struct _Model
{
    s8          charaId_0;    /** `e_CharacterId` */
    u8          paletteIdx_1; /** Changes the texture palette index for this model. */
    u8          state_2;      /** Current state for this model/character. 0 usually means it still has to be initialized. */
    u8          stateStep_3;  // Step number or temp data for the current `state_2`? In `s_MainCharacterExtra` always 1, set to 0 for 1 tick when anim state appears to change.
                              // Used differently in player's `s_SubCharacter`. 0: anim transitioning(?), bit 1: animated, bit 2: turning.
                              // Sometimes holds actual anim index?
    s_ModelAnim anim_4;
} s_Model;
STATIC_ASSERT_SIZEOF(s_Model, 24);

typedef union 
{
    s32 val32;
    s16 val16[2];
    s8  val8[4];
} u_Property;

// TODO: Unsure if this struct is puppet doctor specific or shared with all characterss. Pointer gets set at puppetDoc+0x124.
typedef struct
{
    q19_12      health_0;
    s8          unk_4[32];
    s_AnimInfo* animInfo_24;
    s8          unk_28[12];
} s_800D5710;
STATIC_ASSERT_SIZEOF(s_800D5710, 0x34);

typedef struct
{
    VECTOR3 position_0;
    s16     field_C;
    s16     field_E;
    s16     field_10;
    s8      field_12;
    u8      field_13;
} s_func_8006CF18;

// TODO: Re-offset `s_SubCharaPropertiesPlayer` / `s_SubCharaPropertiesNpc`.
// Probably easier to do that after it's merged with rest of code.
typedef struct _SubCharaPropertiesPlayer
{
    s32           field_E4;
    q19_12        afkTimer_E8; // Increments every tick for 10 seconds before AFK anim starts.
    q19_12        positionY_EC;
    s32           field_F0;
    q19_12        field_F4;    // Angle. Related to X axis flex rotation.
    q19_12        runTimer_F8;
    q19_12        exhaustionTimer_FC;
    q19_12        field_100;    // Angle?
    q19_12        field_104;    // Distance?
    q19_12        runTimer_108;
    u8            field_10C;    // Player SFX pitch?
    u8            field_10D;
    s8            unk_10E[2];
    s32           field_110;
    q19_12        gasWeaponPowerTimer_114; // Timer for the rock drill and chainsaw power.
    s16           field_118;
    s8            unk_11A[2];
    e_PlayerFlags flags_11C;
    q3_12         quickTurnHeadingAngle_120; /** Target heading angle from a quick turn. */
    q3_12         field_122; // Some sort of X angle for the player. Specially used when aiming an enemy.
    q3_12         headingAngle_124;
    q3_12         playerMoveDistance_126; // Used to indicate how much the player should move foward. Seems to be squared.
} s_SubCharaPropertiesPlayer;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesPlayer, 68);

// TODO: This may be a puppet doctor/nurse specific struct, need to compare with other NPCs.
typedef struct _SubCharaPropertiesNpc
{
    s_func_8006CF18* unk_E4; // TODO: Not sure if this is meant to be in player or NPC properties, has to be at 0x0.
    VECTOR3          field_E8;
    s32              field_F4;
    s32              field_F8;
    s32              field_FC;
    s32              field_100;
    s32              field_104;
    s32              field_108;
    s32              field_10C;
    s8               unk_110[4];
    s32              field_114;
    s8               field_118;
    s8               modelVariation_119;
    s16              field_11A;
    s32              field_11C;
    s16              field_120;
    s16              field_122;
    s_800D5710*      field_124;
} s_SubCharaPropertiesNpc;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesNpc, 68);

typedef struct _SubCharPropertiesLarvalStalker
{
    s32        unk_E4;            // Is this part of `a_SubCharacter`?
    u_Property properties_E8[16];
} s_SubCharaPropertiesLarvalStalker;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesLarvalStalker, 68);

typedef struct _SubCharPropertiesUnk0
{
    s32        unk_E4; // Is this part of `a_SubCharacter`?
    u32        field_E8_0 : 4;
    u32        field_E8_4 : 4;
    u32        field_E8_8 : 4;
    u32        field_E8_C : 20;
    u_Property properties_EC;
    u_Property properties_F0;
    u_Property properties_F4;
    VECTOR3    field_F8; // Q19.12 | Position or offset.
    VECTOR3    pos_104;
    VECTOR3    pos_110;
    s32        flags_11C; /** `e_CharaUnk0Flags` */
    u_Property properties_120;
    u_Property properties_124;
} s_SubCharaPropertiesUnk0;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesUnk0, 68);

typedef struct _SubCharPropertiesDahlia
{
    s32        unk_E4;
    s32        stateIdx0;
    u_Property properties_EC;
    u_Property properties_F0;
    u_Property properties_F4;
    s32        resetStateIdx0_F8;
    s32        field_FC;
    s32        field_100;
    u_Property properties_104;
    u_Property properties_108;
    u_Property properties_10C;
    VECTOR3    field_110;
    s32        flags_11C;
    u_Property properties_120;
    s16        field_124;
    q3_12      moveDistance_126;
} s_SubCharaPropertiesDahlia;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesDahlia, 68);

typedef struct _SubCharaPropertiesSplitHead
{
    s32        unk_E4;
    u16        flags_E8;
    u16        unk_EA;
    u_Property field_EC;
    u_Property field_F0;
    u16        timer_F4;
    u16        unk_F8;
    s32        resetStateIdx0_F8;
    s32        field_FC;
    s32        field_100;
    u_Property field_104;
    u_Property field_108;
    u_Property field_10C;
    VECTOR3    field_110;
    s32        flags_11C;
    u_Property field_120;
    s16        field_124;
    s16        moveDistance_126;
} s_SubCharaPropertiesSplitHead;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesSplitHead, 68);

/** Offsets for translation? */
typedef struct
{
    q3_12 offsetX_0;
    q3_12 offsetZ_2;
    q3_12 offsetX_4;
    q3_12 offsetZ_6;
} s_SubCharacter_D8;
STATIC_ASSERT_SIZEOF(s_SubCharacter_D8, 8);

typedef struct _SubCharacter
{
    s_Model model_0;           // In player: Manage the half lower part of Harry's body animations (legs and feet).
    VECTOR3 position_18;       /** `Q19.12` */
    SVECTOR rotation_24;       // Maybe `SVECTOR3` instead of `SVECTOR` because 4th field is copy of `.xy` field.
    SVECTOR rotationSpeed_2C;  /** Q3.12 | Range: `[FP_ANGLE(-157.5f), FP_ANGLE(157.5f)]`. */
    q19_12  field_34;          // Character Y position?
    q19_12  moveSpeed_38;
    q3_12   headingAngle_3C;
    s16     flags_3E;          /** `e_CharaFlags` */
    s8      field_40;          // In player: Index of the NPC attacking the player.
                               // In NPCs: Unknown.
    s8      attackReceived_41; // Indicates what attack has been performed to the character. For enemies is based on `e_EquippedWeaponId` enum.
    s8      unk_42[2];
    s16     field_44;
    s8      field_46; // In player: packed weapon attack. See `WEAPON_ATTACK`.
                      // This is not the same as `attackReceived_41`, as this value only resets when player is aiming.
                      // In NPCs: Indicates attack performed on player.
    s8      field_47;
    s8      unk_48[4];
    s32     field_4C; // } Fields used by `func_8008A3E0`. Types guessed for now.
    s16     field_50; // } Angle?
    s16     field_52; // } Angle?
    s16     field_54; // }
    s16     field_56; // }
    s32     field_58; // }
    VECTOR3 field_5C;
    VECTOR3 characterCount_68;
    VECTOR3 field_74;
    VECTOR3 field_80;
    VECTOR3 field_8C;
    VECTOR3 field_98;
    VECTOR3 field_A4;
    q19_12  health_B0;
    s32     field_B4;          // X? } In player: Adds/subtracts if hurt by enemy. Related to heading angle?
    s32     field_B8;          // Y? } Angle.
    s32     field_BC;          // Z? }
    q19_12  damageReceived_C0;
    u16     deathTimer_C4;     // Part of `shBattleInfo` struct in SH2, may use something similar here.
    s16     timer_C6;          // Some sort of timer, value written by `Ai_LarvalStalker_Update`.

    // Fields seen used inside maps (eg. `map0_s00` `func_800D923C`)

    q3_12             field_C8; // } Anim root offset? Set to player head position in `sharedFunc_800D0828_3_s03`.
    q3_12             field_CA; // } } Computed as Y offsets in `sharedFunc_800D0828_3_s03`.
    q3_12             field_CC; // } }
    q3_12             field_CE;
    s16               field_D0; // Q3.12? Maybe weapon range?
    s16               field_D2;
    q3_12             field_D4;
    q3_12             field_D6;
    s_SubCharacter_D8 field_D8; // Translation data?

    u8 field_E0; // Related to collision. If the player collides with the only enemy in memory and the enemy is knocked down, this is set to 1.

    s8 field_E1_0 : 4; // Flags?
    u8 field_E1_4 : 4;

    union
    {
        s_SubCharaPropertiesPlayer        player;
        s_SubCharaPropertiesNpc           npc;
        s_SubCharaPropertiesLarvalStalker larvalStalker;
        s_SubCharaPropertiesUnk0          unk0;
        s_SubCharaPropertiesDahlia        dahlia;
        s_SubCharaPropertiesSplitHead     splitHead;
    } properties_E4;
} s_SubCharacter;
STATIC_ASSERT_SIZEOF(s_SubCharacter, 296);

typedef struct _MainCharacterExtra
{
    s_Model model_0;              /** Manages upper half body's animations (torso, arms, head). */
    s32     disabledAnimBones_18; /** Bitfield of disabled animation bones. Can be created using the `BITMASK_RANGE` macro. */
    s32     state_1C;             /** `e_PlayerState` */
    s32     upperBodyState_20;    /** `e_PlayerUpperBodyState` */
    s32     lowerBodyState_24;    /** `e_PlayerLowerBodyState` */
    s32     field_28;             // Related to item interactions. Forcing specific values opens options menu, a behaviour is caused by `func_800373CC`.
} s_MainCharacterExtra;
STATIC_ASSERT_SIZEOF(s_MainCharacterExtra, 44);

// TODO: Based on SH2 symbols this struct should be named `shPlayerWork` and `chara_0` should be `player`.
typedef struct _MainCharacter
{
    s_SubCharacter       chara_0;
    s_MainCharacterExtra extra_128;
} s_MainCharacter;
STATIC_ASSERT_SIZEOF(s_MainCharacter, 340);

typedef struct _PlayerCombat
{
    VECTOR3 field_0; // Q19.12 position offset?
    s8      unk_C[3];
    s8      weaponAttack_F;        /** Packed weapon attack. See `WEAPON_ATTACK`. */
    u8      currentWeaponAmmo_10;
    u8      totalWeaponAmmo_11;
    s8      weaponInventoryIdx_12; /** Index of the currently equipped weapon in the inventory. */
    u8      isAiming_13;           /** `bool` */
} s_PlayerCombat;
STATIC_ASSERT_SIZEOF(s_PlayerCombat, 20);

typedef union
{
    s32 field_0;
    struct
    {
        u8 field_0;
        u8 field_1;
        u8 field_2;
        u8 unk_3;
    } s_field_0;
} u_Unk0;

typedef struct
{
    u_Unk0  field_0;
    q3_12   field_4; // FP alpha.
    s16     field_6;
    s16     field_8; // } World tint color.
    s16     field_A; // }
    s16     field_C; // }
    u8      field_E; // Fog enabled if not set to 0, `func_8003F08C` checks for values 0/1/2/3.
    s8      unk_F;
    s32     field_10;
    CVECTOR fogColor_14;
    u8      field_18; // `bool`?
    CVECTOR field_19;
    CVECTOR field_1D;
    CVECTOR field_21;
    CVECTOR field_25;
    u8      unk_29;
    s16     unk_2A;
} s_sub_StructUnk3;
STATIC_ASSERT_SIZEOF(s_sub_StructUnk3, 44);

typedef struct
{
    s_sub_StructUnk3 field_0;
    s16              field_2C; // FP alpha.
    s16              field_2E; // FP alpha.
    s32              field_30;
} s_StructUnk3;
STATIC_ASSERT_SIZEOF(s_StructUnk3, 52);

typedef struct
{
    s32             field_0; /** `e_PrimitiveType` */
    s8*             field_4; /** Points to different types of data depending on `field_0`. */
    s32             field_8; // } Q19.12?
    s32             field_C; // }
    s32             field_10;
    u8              field_14;
    u8              isFlashlightOn_15; /** `bool` */
    u8              field_16;          /** `bool` */
    s8              unk_17;
    q3_12           flashlightIntensity_18; // Alpha.
    u16             field_1A;
    s_StructUnk3    field_1C[2];
    s_StructUnk3    field_84[2];
    s_StructUnk3    field_EC[2];
    s_StructUnk3    field_154;
} s_SysWork_2288;
STATIC_ASSERT_SIZEOF(s_SysWork_2288, 392);

typedef struct
{
    s8  field_0[4];
    s32 field_4;
    s8  unk_8[4];
    s32 field_C;
} s_SysWork_2514_C;

typedef struct _s_SysWork_2514_18
{
    struct _s_SysWork_2514_18* next_0;

    u8  unk_4[4]; // Prev?
    u8  unk_8[4];
    s32 field_C;
    u8  unk_10[8];
    u8  unk_18[4];
    u16 field_1C;
    u16 field_1E;
} s_SysWork_2514_18;

typedef struct
{
    u32               field_0   : 8;
    u8                field_1   : 8;
    u32               field_2_0 : 1;
    u32               field_2_1 : 1;
    u32               field_2_2 : 4;
    u32               field_2_3 : 1;
    u32               field_2_4 : 1;
    u32               field_2_5 : 8;
    u8                unk_4[8];
    s_SysWork_2514_C* field_C;
    u8                unk_10[8];
    s_SysWork_2514_18 head_18;
} s_SysWork_2514;
STATIC_ASSERT_SIZEOF(s_SysWork_2514, 56);

typedef struct _SysWork
{
    s8              unk_0[8];
    e_SysState      sysState_8;
    s32             sysStateStep_C[3]; /** Temp data used by current `sysState_8`. Can be another state ID or other data. */
    s32             field_18; // Related to map messages.
    s32             timer_1C;
    s32             timer_20;
    s32             timer_24;
    s32             field_28;
    q19_12          timer_2C; // Cutscene message timer?
    s32             field_30;
    s8              unk_34[4];
    s_PlayerCombat  playerCombatInfo_38; // Something related to weapons and attack. This is a struct as `func_8003CD6C` requires one and `GameFs_MapLoad` input is pointing here.
    s_MainCharacter player_4C;
    s_SubCharacter  npcs_1A0[NPC_COUNT_MAX];
    GsCOORDINATE2   playerBoneCoords_890[HarryBone_Count];
    GsCOORDINATE2   unkCoords_E30[5];  // Might be part of previous array for 5 extra coords which go unused.
    GsCOORDINATE2   npcCoords_FC0[NPC_BONE_COUNT_MAX]; // Dynamic coord buffer? 10 coords per NPC (given max of 6 NPCs).
    s8              field_2280;                        // NPC index for `flags_2290`.
    s8              loadingScreenIdx_2281;
    s8              field_2282; // Room process flags?
    s8              field_2283; // Index into `SfxPairs`.
    u16             field_2284[3]; // TODO: `func_80034EC8` indicates size of 4.
    u16             field_228A;
    s32             field_228C;
    s32             flags_2290; // Flags related to NPCs, each bit corresponds to `npcs_1A0` index.
    s8              unk_2294[4];
    e_SysWorkProcessFlags processFlags_2298;
    s32             field_229C;
    e_SysFlags      sysFlags_22A0;
    s32             flags_22A4; // (1 << 6) passed as "use through door cam" flag in `vcSetFirstCamWork`. Also `e_SysFlags` or different?
    GsCOORDINATE2   coord_22A8; // For particles only?
    GsCOORDINATE2   coord_22F8; // Likely related to above.
    s8              field_2348   : 8;
    s8              field_2349   : 8; // Particle spawn multiplier?
    u8              field_234A   : 8;
    u8              field_234B_0 : 4;
    u8              field_234B_4 : 4;
    s32             mapMsgTimer_234C;
    u8              enableHighResGlyphs_2350_0      : 4; /** `bool` */
    u8              silentYesSelection_2350_4       : 4; /** `bool` */
    u32             inventoryItemSelectedIdx_2351   : 8;
    u32             flags_2352                      : 8;
    s8              targetNpcIdx_2353; /** Index of the NPC being targeted by the player. */
    s8              npcIdxs_2354[4];
    u8              field_2358;          /** `bool` */
    s8              unk_2359[1];
    u8              field_235A; // If the player stops walking or running forward, the value changes to 1. If the player stops walking backward, the value changes to 2.
    s8              unk_235B[1];
    GsCOORDINATE2*  field_235C;
    VECTOR3         field_2360; // Position?
    GsCOORDINATE2*  field_236C;
    SVECTOR         field_2370; // Rotation.
    s16             field_2378;
    s16             cameraAngleY_237A;
    s16             cameraAngleZ_237C;
    s16             field_237E;
    q19_12          cameraRadiusXz_2380;
    q19_12          cameraY_2384;
    s_SysWork_2288  field_2388;
    s32             field_2510;
    s_SysWork_2514  field_2514;
    u8              unk_254C[508];
    s16             field_2748[9]; // `func_80035ED0` loops over this.
    u8              unk_275A[2];
    q19_12          field_275C;
    s32             field_2760;
    s32             field_2764;
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

extern s32  g_ActiveBufferIdx;
extern GsOT g_OrderingTable0[2];
extern GsOT g_OrderingTable1[2];
extern GsOT g_OrderingTable2[2];

extern q19_12        g_DeltaTime0;
extern q19_12        g_DeltaTime1;
extern q19_12        g_DeltaTime2;
extern u32           g_MapEventIdx;
extern s_EventParam* g_MapEventParam;

extern s32 g_IntervalVBlanks;
extern s32 g_PrevVBlanks;
extern s32 g_VBlanks;
extern s32 g_UncappedVBlanks;

/** @brief Sets `sysState` in `g_SysWork` for the next tick.
 *
 * @param sysState System state to set.
 * @return New system state.
 */
static inline s32 SysWork_StateSetNext(e_SysState sysState)
{
    s32 state;

    state                       =
    g_SysWork.sysState_8        = sysState;
    g_SysWork.timer_24          = 0;
    g_SysWork.sysStateStep_C[0] = 0;
    g_SysWork.field_28          = 0;
    g_SysWork.sysStateStep_C[1] = 0;
    g_SysWork.timer_2C          = 0;
    g_SysWork.sysStateStep_C[2] = 0;
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
        g_SysWork.field_28          = 0;
        g_SysWork.sysStateStep_C[1] = 0;
        g_SysWork.timer_2C          = 0;
        g_SysWork.sysStateStep_C[2] = 0;
        g_SysWork.sysStateStep_C[0]++;
    }
    else if (stepIdx == 1)
    {
        g_SysWork.timer_2C          = 0;
        g_SysWork.sysStateStep_C[2] = 0;
        g_SysWork.sysStateStep_C[1]++;
    }
    else
    {
        g_SysWork.sysStateStep_C[2]++;
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
        g_SysWork.sysStateStep_C[0] = sysStateStep;
        g_SysWork.field_28          = 0;
        g_SysWork.sysStateStep_C[1] = 0;
        g_SysWork.timer_2C          = 0;
        g_SysWork.sysStateStep_C[2] = 0;
    }
    else if (stepIdx == 1)
    {
        step                        = 
        g_SysWork.sysStateStep_C[1] = sysStateStep;
        g_SysWork.timer_2C          = 0;
        g_SysWork.sysStateStep_C[2] = 0;
    }
    else
    {
        step                        = 
        g_SysWork.sysStateStep_C[2] = sysStateStep;
    }

    return step;
}

/** @brief Resets `sysStateStep` in `g_SysWork` for the next tick. */
static inline void SysWork_StateStepReset()
{
    g_SysWork.sysStateStep_C[0] = NO_VALUE;
    g_SysWork.field_28          = 0;
    g_SysWork.sysStateStep_C[1] = 0;
    g_SysWork.timer_2C          = 0;
    g_SysWork.sysStateStep_C[2] = 0;
}

/** @brief Sets a flag from `g_SysWork.flags_2290` array.
 *
 * @param flagIdx Index of the flag to set.
 */
static inline void SysWork_Flags2290Set(s32 flagIdx)
{
    g_SysWork.flags_2290 |= 1 << flagIdx;
}

/** @brief Clears a flag from `g_SysWork.flags_2290` array.
 *
 * @param flagIdx Index of the flag to clear.
 */
static inline void SysWork_Flags2290Clear(s32 flagIdx)
{
    CLEAR_FLAG(&g_SysWork.flags_2290, flagIdx);
}

/** @brief Clears state steps twice for some reason? Only used once below, others use regular `Game_StateSetNext`. */
static inline void Game_StateSetNext_ClearStateSteps(e_GameState gameState)
{
    e_GameState prevState;

    prevState = g_GameWork.gameState_594;

    g_GameWork.gameState_594        = gameState;
    g_SysWork.timer_1C              = 0;
    g_SysWork.timer_20              = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

/** @brief Sets the GameState to be used in the next game update.
 * Inlined into `stream` and `b_konami`.
 */
static inline void Game_StateSetNext(e_GameState gameState)
{
    e_GameState prevState;

    prevState = g_GameWork.gameState_594;

    g_GameWork.gameState_594        = gameState;
    g_SysWork.timer_1C              = 0;
    g_SysWork.timer_20              = 0;
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
    e_GameState prevState;

    prevState = g_GameWork.gameState_594;

    g_SysWork.timer_1C              = 0;
    g_SysWork.timer_20              = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameState_594        = g_GameWork.gameStatePrev_590;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

/** @brief Gets an event flag state from the savegame event flags array.
 *
 * @param flagIdx Event flag index.
 * @return Event flag state (`bool`).
 */
#define Savegame_EventFlagGet(flagIdx) \
    (g_SavegamePtr->eventFlags_168[(flagIdx) >> 5] & (1 << ((flagIdx) & 0x1F)))

/** @brief Gets an event flag state from the savegame event flags array.
 *
 * @note This alternate version shifts the flags array value by the flag index for some reason
 * and is required for some matches.
 *
 * @param flagIdx Event flag index.
 * @return Event flag state (`bool`).
 */
#define Savegame_EventFlagGetAlt(flagIdx) \
    ((g_SavegamePtr->eventFlags_168[(flagIdx) >> 5] >> ((flagIdx) & 0x1F)) & (1 << 0))

/** @brief Clears an event flag state in the savegame event flags array.
 *
 * @param flagIdx Event flag index.
 */
#define Savegame_EventFlagClear(flagIdx) \
    (g_SavegamePtr->eventFlags_168[(flagIdx) >> 5] &= ~(1 << ((flagIdx) & 0x1F)))

/** @brief Sets an event flag state in the savegame event flags array.
 *
 * @param flagIdx Event flag index.
 */
#define Savegame_EventFlagSet(flagIdx) \
    (g_SavegamePtr->eventFlags_168[(flagIdx) >> 5] |= 1 << ((flagIdx) & 0x1F))

/** @brief Gets a map marking state from the savegame map marking array.
 *
 * @param flagIdx Map marking index.
 * @return Map marking state (`bool`).
 */
#define Savegame_MapMarkingGet(flagIdx) \
    (g_SavegamePtr->mapMarkingFlags_1D4[(flagIdx) >> 5] & (1 << ((flagIdx) & 0x1F)))

/** @brief Clears a map marking state in the savegame map marking array.
 *
 * @param flagIdx Map marking index.
 */
#define Savegame_MapMarkingClear(flagIdx) \
    (g_SavegamePtr->mapMarkingFlags_1D4[(flagIdx) >> 5] &= ~(1 << ((flagIdx) & 0x1F)))

/** @brief Sets a map marking in the savegame map marking array.
 *
 * @param flagIdx Map marking index.
 */
#define Savegame_MapMarkingSet(flagIdx) \
    (g_SavegamePtr->mapMarkingFlags_1D4[(flagIdx) >> 5] |= 1 << ((flagIdx) & 0x1F))

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

    g_SavegamePtr->eventFlags_168[localIdx] |= 1 << localBit;
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

/** @brief Sets the animation of a character.
 *
 * @param chara Character to set animation for. TODO: Maybe should take `s_ModelAnim` instead? If fits better, also rename to `Anim_Set`.
 * @param animStatus Packed anim status. See `s_ModelAnim::status_0`.
 * @param keyframeIdx Active keyframe index.
 */
static inline void Character_AnimSet(s_SubCharacter* chara, s32 animStatus, s32 keyframeIdx)
{
    // TODO: Problem with header includes prevents `Q12` macro use.
    chara->model_0.anim_4.status_0      = animStatus;
    chara->model_0.anim_4.time_4        = keyframeIdx << 12;//Q12(keyframeIdx);
    chara->model_0.anim_4.keyframeIdx_8 = keyframeIdx;
}

/** @brief Sets the given animation flag on both player character and player extra data. */
// TODO: Move to separate character/player header.
static inline void Player_AnimFlagsSet(u32 flags)
{
    s_SubCharacter*       chara;
    s_MainCharacterExtra* extra;

    extra = &g_SysWork.player_4C.extra_128;
    chara = &g_SysWork.player_4C.chara_0;

    extra->model_0.anim_4.flags_2 |= flags;
    chara->model_0.anim_4.flags_2 |= flags;
}

/** @brief Sets the given animation flag on a model. */
static inline void Model_AnimFlagsSet(s_Model* model, u32 flags)
{
    model->anim_4.flags_2 |= flags;
}

/** @brief Clears the given animation flag on a model. */
static inline void Model_AnimFlagsClear(s_Model* model, u32 flags)
{
    model->anim_4.flags_2 &= ~flags;
}

/** @brief Updates a model anim if `model->stateStep_3` is 0.
 *
 * @param model Model to update.
 * @param animIdx Anim index to set.
 * @param isActive Active status to set.
 */
static inline void Model_AnimStatusSet(s_Model* model, s32 animIdx, bool isActive)
{
    if (model->stateStep_3 == 0)
    {
        model->anim_4.status_0 = ANIM_STATUS(animIdx, isActive);
        model->stateStep_3++;
    }
}

/** @brief Increments the anim status of a model anim.
 *
 * @param anim Anim to update.
 */
static inline void ModelAnim_StatusIncrement(s_ModelAnim* anim)
{
    anim->status_0++;
}

/** @brief Decrements the anim status of a model anim.
 *
 * @param anim Anim to update.
 */
static inline void ModelAnim_StatusDecrement(s_ModelAnim* anim)
{
    anim->status_0--;
}

/** @brief Similar to `Model_AnimStatusSet`, but also sets `anim_4.time_4` and `anim_4.keyframeIdx_8`
 * from the `animInfos` `s_AnimInfo` array.
 *
 * @param model Model to update.
 * @param animIdx Anim index to set.
 * @param isActive Active status to set.
 * @param animInfos Reference anim infos.
 * @param animInfosOffset Anim infos offset.
 */
#define Model_AnimStatusKeyframeSet(model, animIdx, isActive, animInfos, animInfosOffset)                                                    \
    if ((model).stateStep_3 == 0)                                                                                                            \
    {                                                                                                                                        \
        (model).anim_4.status_0 = ANIM_STATUS(animIdx, isActive);                                                                            \
        (model).stateStep_3++;                                                                                                               \
        (model).anim_4.time_4        = FP_TO((animInfos)[ANIM_STATUS(animIdx, isActive) + (animInfosOffset)].startKeyframeIdx_C, Q12_SHIFT); \
        (model).anim_4.keyframeIdx_8 = (animInfos)[ANIM_STATUS(animIdx, (isActive) + (animInfosOffset))].startKeyframeIdx_C;                 \
    }

/** @brief Attempts to reset a humanoid NPC's anim state index to 0.
 *
 * @param chara Character to update.
 */
static inline void Character_AnimStateReset(s_SubCharacter* chara)
{
    // TODO: This uses `dahlia` part of union, but is most likely either a `human` part shared with all humanoid characters
    // or humanoids only share a small portion early in the union.
    if (chara->properties_E4.dahlia.resetStateIdx0_F8)
    {
        chara->properties_E4.dahlia.stateIdx0         = 0;
        chara->model_0.stateStep_3                    = 0;
        chara->properties_E4.dahlia.resetStateIdx0_F8 = 0;
    }
}

#endif

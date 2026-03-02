#ifndef _BODYPROG_GAMEBOOT_H
#define _BODYPROG_GAMEBOOT_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `game_boot/` files.
 */

// ==========
// FUNCTIONS
// ==========

void Anim_CharaTypeAnimInfoClear(void);

/** Handles `g_GameWork.gameStateStep_598[0]`.
 * Used to handle map loading and room changes.
 */
void GameBoot_GameStartup(void);

void GameBoot_NpcInit(void);

/** Crucial for getting in-game.
 * Removing it breaks the camera, inventory's 3D elements, effects
 * (lighting, fog, lens flare, etc.), NPCs don't spawn, and
 * doing any action unrelated to aiming a weapon or interacting
 * with the environment crashes the game.
 */
void GameBoot_InGameInit(void);

void GameBoot_SavegameInitialize(s8 overlayId, s32 difficulty);

/** @brief Initializes the player character model. */
void GameBoot_PlayerInit(void);

/** Loads a map file into `g_OvlDynamic`. */
void GameBoot_MapLoad(s32 mapIdx);

/** @brief Checks if the pointers of `g_CharaTypeAnimInfo` overlap each other.
 * Returns `false` if the compared pointers don't overlap.
 */
bool Fs_CharaAnimDataSizeCheck(s32 idx0, s32 idx1);

/** @brief Finds for the index of the character animation data in `g_CharaTypeAnimInfo`.
 *
 * @param charaId ID of the character for which to find the animation data.
 * @return Animation data index.
 */
s32 Fs_CharaAnimDataInfoIdxGet(e_CharacterId charaId);

/** Allocates and adjust where is animation data allocated. */
void Fs_CharaAnimDataAlloc(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coords);

/** Called by `Fs_QueuePostLoadAnm`. Assigns information about animation data to `g_CharaTypeAnimInfo`
 * and initializes NPC bones.
 */
void Fs_CharaAnimInfoUpdate(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coord);

/** @brief Updates character type bone initialization coordinates and reinitializes them. */
void Fs_CharaAnimBoneInfoUpdate(void);

s32 Bgm_Init(void);

/** @brief Checks if currently assigned song is the same as target. */
bool Bgm_IsCurrentBgmTargetCheck(s32 bgmIdx);

void Bgm_TrackSet(s32 bgmIdx);

/** Executes sound command. */
void Bgm_BgmChannelSet(void);

void func_8003596C(void);

s32 Sd_AmbientSfxInit(void);

bool Sd_IsCurrentAmbientTargetCheck(s32 ambIdx);

void Sd_AmbientSfxSet(s32 idx);

/** @brief Sets general environmental effects such as lighting, fog, and screen effects.
 *
 * @note Specific effect for enviroments like snow, rain, and the ending's fire rain
 * are set by code only found in map overlays.
 */
void Gfx_MapEffectsSet(s32 unused);

void func_80035B98(void);

/** @unused and broken.
 * Intended to draw a background image when a loading screen with the string "STAGE X-X" appears.
 */
void GameBoot_LoadScreen_BackgroundImg(void);

void GameBoot_LoadScreen_PlayerRun(void);

#endif

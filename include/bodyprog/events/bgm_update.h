#ifndef _BODYPROG_EVENTS_BGMUPDATE_H
#define _BODYPROG_EVENTS_BGMUPDATE_H

// ========
// STRUCTS
// ========

typedef struct _BgmLayerLimits
{
    /* 0x0 */ u8 limits[8];
} s_BgmLayerLimits;

// ==========
// FUNCTIONS
// ==========

void Bgm_TrackUpdate(bool arg0);

void Bgm_AllLayersMute(void);

/** @unused. */
bool Bgm_LayerOnCheck(void);

void Bgm_GlobalLayerVariablesUpdate(void);

/** @brief Undates background music.
 *
 * @param flags BGM layer flags.
 * @param fadeSpeed Volume fade speed.
 * @param layerLimits BGM layer limits.
 */
void Bgm_Update(s32 flags, q19_12 fadeSpeed, s_BgmLayerLimits* layerLimits);

/** @brief Updates the track index and disables radio effects. */
void func_800363D0(void);

void Bgm_TrackChange(s32 idx);

void Savegame_MapRoomIdxUpdate(void);

/** @Unused */
s32 func_8003647C(void);

/** @Unused */
s32 func_80036498(void);

/** @Unused */
u32 func_800364BC(void);

/** @brief Draws a palette of colors in the frame buffer. */
void func_8003652C(void);

#endif

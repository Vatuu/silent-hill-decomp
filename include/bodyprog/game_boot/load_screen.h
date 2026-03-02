#ifndef _BODYPROG_GAMEBOOT_LOADSCREEN_H
#define _BODYPROG_GAMEBOOT_LOADSCREEN_H

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

#ifndef _BODYPROG_SCREEN_DRAW_H
#define _BODYPROG_SCREEN_DRAW_H

/** @brief This header is used to declare variables and
 * functions from `screen_draw.c`
 */

// ========
// GLOBALS
// ========

extern q19_12 g_PrevScreenFadeProgress;

extern s32 pad_bss_800B5C2C;

extern q19_12 g_ScreenFadeTimestep;

// ==========
// FUNCTIONS
// ==========

void Screen_RectInterlacedClear(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

void Screen_Refresh(s32 screenWidth, bool isInterlaced);

void Screen_Init(s32 screenWidth, bool isInterlaced);

void Screen_XyPositionSet(s32 x, s32 y);

void Screen_DisplayEnvXySet(DISPENV* displayEnv, s32 x, s32 y);

void Screen_FadeDrawModeSet(DR_MODE* drMode);

q19_12 Screen_FadeInProgressGet(void);

void Screen_FadeUpdate(void);

void Screen_CutsceneCameraStateUpdate(void);

void Screen_VSyncCallback(void);

#endif

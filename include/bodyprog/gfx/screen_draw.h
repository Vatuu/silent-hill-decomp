#ifndef _BODYPROG_GFX_SCREEN_DRAW_H
#define _BODYPROG_GFX_SCREEN_DRAW_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the screen display system (not from PSY-Q SDK).
 */

// ==========
// FUNCTIONS
// ==========

void Screen_RectInterlacedClear(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

void Screen_Refresh(s32 screenWidth, s32 isInterlaced);

void Screen_Init(s32 screenWidth, s32 isInterlaced);

void Screen_XyPositionSet(s32 x, s32 y);

void Screen_DisplayEnvXySet(DISPENV* displayEnv, s32 x, s32 y);

void Screen_FadeDrawModeSet(DR_MODE* drMode);

q19_12 Screen_FadeInProgressGet();

void Screen_FadeUpdate();

void Screen_CutsceneCameraStateUpdate();

void Screen_VSyncCallback();

#endif

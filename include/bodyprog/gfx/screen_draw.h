#ifndef _BODYPROG_GFX_SCREEN_DRAW_H
#define _BODYPROG_GFX_SCREEN_DRAW_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the screen display system (not from PSY-Q SDK).
 */

// ========
// GLOBALS
// ========

extern q19_12 g_PrevScreenFadeProgress;

extern s32 pad_bss_0x800B5C2C;

extern q19_12 g_ScreenFadeTimestep;

// ====================
// GLOBALS (BSS; Hack)
// ====================
// To match the order of the BSS segment, extern declarations
// are required in a predetermined order.
// This is done until a way to replicate `common`
// segment behavior is found.

extern s32      g_VBlanks;
extern s32      g_UncappedVBlanks;
extern s32      pad_bss_800B5C3C;
extern GsOT_TAG g_OtTags0[2][16];

/** Main gameplay timer. Code may pause gameplay by setting this to 0. Demos override this with the time from demo file to ensure demos are in sync. */
extern q19_12   g_DeltaTime;

extern GsOT_TAG g_OtTags1[2][ORDERING_TABLE_SIZE];
extern s32      pad_bss_800B9CC4;

/** Gravity speed for this tick. */
extern q19_12   g_GravitySpeed;

/** Number of ticks since game start. */
extern s32      g_TickCount;

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

#ifndef _BODYPROG_SCREEN_SCREENDATA_H
#define _BODYPROG_SCREEN_SCREENDATA_H

/** @brief This header is used to declare any variable or struct
 * part of `BODYPROG.BIN` identified to be related
 * to the screen display system (not from PSY-Q SDK).
 */

// ========
// GLOBALS
// ========

extern s32  g_ActiveBufferIdx;
extern GsOT g_OrderingTable0[2];
extern GsOT g_OrderingTable1[2];
extern GsOT g_OrderingTable2[2];

/** Actual delta time since the previous tick. Unlike `g_DeltaTime`, this value is never overridden by demos or game code. Mostly seems used by UI code. */
extern q19_12 g_DeltaTimeRaw;

extern s32 g_IntervalVBlanks;

// ====================
// GLOBALS (BSS; Hack)
// ====================
// To match the order of the BSS segment, extern declarations
// are required in a predetermined order.
// This is done until a way to replicate `common`
// segment behavior is found.

extern s32      g_VBlanks;
extern s32      g_UncappedVBlanks;
extern s32      __pad_bss_800B5C3C;
extern GsOT_TAG g_OtTags0[2][16];

/** Main gameplay timer. Code pauses gameplay by setting this to `Q12(0.0f)`.
 * Demos override this with the time from a demo file to ensure deos remain in sync.
 * */
extern q19_12 g_DeltaTime; /** Possible original name: `_shDeltaTimePerFrame` */

extern GsOT_TAG g_OtTags1[2][ORDERING_TABLE_SIZE];
extern s32      __pad_bss_800B9CC4;

/** Gravity speed for this tick. */
extern q19_12 g_GravitySpeed;

/** Number of ticks since game start. */
extern s32 g_TickCount;

extern s32 g_MainLoop_FrameCount; // 0x800B9CCC

#endif

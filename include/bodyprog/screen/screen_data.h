#ifndef _BODYPROG_SCREEN_DATA_H
#define _BODYPROG_SCREEN_DATA_H

// TODO: Please move this and all `src/bodyprog/screen/` files headers into a different include folder
// (`include/bodyprog/screen/`) and divide all functions in different headers.
/** @brief This header is used to declare any variable or struct
 * part of `BODYPROG.BIN` identified to be related
 * to the screen display system (not from PSY-Q SDK).
 *
 * @note This contains data used among all the code, data exclusively
 * focused in specific aspects of the code (for example: fading effect code)
 * goes into a separated header file.
 */

// ========
// GLOBALS
// ========

extern s32    g_ActiveBufferIdx;
extern GsOT   g_OrderingTable0[2];
extern GsOT   g_OrderingTable1[2];
extern GsOT   g_OrderingTable2[2];
/** Actual delta time since the previous tick. Unlike `g_DeltaTime`, this value is never overridden by demos or game code. Mostly seems used by UI code. */
extern q19_12 g_DeltaTimeRaw;
extern s32    g_IntervalVBlanks;

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
extern s32      g_MainLoop_FrameCount; // 0x800B9CCC

#endif

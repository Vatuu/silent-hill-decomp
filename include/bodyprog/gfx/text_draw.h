#ifndef _TEXT_DRAW_H
#define _TEXT_DRAW_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the string display system (not from PSY-Q SDK).
 *
 * @note Likely the true name for this system is `font` as both
 * SH2 and SH4 symbols indicate that the way TS referred to strings
 * or text was using `font`.
 */

/** Control codes used by `Gfx_StringDraw`.
 * (TODO: rename to actual purpose, update `Gfx_StringDraw` calls to use them) */
#define STRING_CTRL_07 "\x07"
#define STRING_CTRL_0A "\x0a"

// ========
// GLOBALS
// ========

extern s16 g_StringColorId; // 0x800AD498

/** Text index 2D layer.
 * In case of modifying `Gfx_StringSetPosition` to set it to
 * a value lower than 6 text will not be affected by the fade effect
 */
extern s32 g_Strings2dLayerIndex; // 0x800AD49C

extern DVECTOR g_Gfx_DebugStringPosition0; // 0x800B5C20

extern DVECTOR g_Gfx_DebugStringPosition1; // 0x800B5C24

// ==========
// FUNCTIONS
// ==========

/** Sets the position of the next string to be drawn by `Gfx_StringDraw`. */
void Gfx_StringSetPosition(s32 x, s32 y);

void Gfx_StringsSet2dLayerIdx(s32 idx);

void Gfx_StringsReset2dLayerIdx();

/** Sets the color of the next string drawn by `Gfx_StringDraw`. Uses `e_ColorId`. */
void Gfx_StringSetColor(s16 colorId);

/** Draws a string in screen space using 12x16 glyphs.
 *
 * @note References glyphs in `FONT16.TIM`. Although this texture atlas contains a single row with 84 glyphs,
 * the function implies 21 glyphs per row. Maybe the engine slices the texture into a stack in VRAM?
 * Notably, the atlas happens to have a 4-pixel space every 21st glyph.
 */
bool Gfx_StringDraw(char* str, s32 strLength);

void MapMsg_CalculateWidthTable(s32 mapMsgIdx);

/** Draws string and returns map message index. */
s32 Gfx_MapMsg_StringDraw(char* mapMsg, s32 strLength);

void func_8004B658();

void Gfx_MapMsg_DefaultStringInfoSet();

void func_8004B6D4(s16 arg0, s16 arg1);

void func_8004B74C(s16 arg0);

/** Draws string. */
void func_8004B76C(char* str, s32 useFixedWidth);

/** Draws an integer string in screen space. */
void Gfx_StringDrawInt(s32 widthMin, s32 val);

void func_8004BB10();

void Gfx_DebugStringPosition(s16 x, s16 y);

/** Draws debug strings using 8x8 glyphs from `FONT8.TIM`. Valid `char` range: `[42, 95]` (`*` to `_`). */
void Gfx_DebugStringDraw(char* str);

char* Math_IntegerToString(s32 widthMin, s32 value);

void func_800321EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#endif

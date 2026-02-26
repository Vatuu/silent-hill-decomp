#ifndef _BODYPROG_TEXT_DRAW_H
#define _BODYPROG_TEXT_DRAW_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the string display system (not from PSY-Q SDK).
 *
 * @note Likely the true name for this system is `font` as both
 * SH2 and SH4 symbols indicate that the way TS referred to strings
 * or text was using `font`.
 */

/** @brief String color IDs for strings displayed in screen space.
 * Used as indices into `STRING_COLORS`.
 */
typedef enum _StringColorId
{
    StringColorId_Gold        = 0,
    StringColorId_DarkGrey    = 1,
    StringColorId_Green       = 2,
    StringColorId_Nuclear     = 3,
    StringColorId_Red         = 4,
    StringColorId_GreenUnused = 5, // @unused Same as `StringColorId_Green`.
    StringColorId_LightGrey   = 6,
    StringColorId_White       = 7,

    StringColorId_Count       = 8
} e_StringColorId;

// ========
// GLOBALS
// ========

/** String position. */
extern DVECTOR g_StringPosition; // 0x800C38A8

/** String X position as `s32`. It's unclear why there are two. */
extern s32 g_StringPositionX1; // 0x800C38AC

// Used in string parsing.
typedef struct
{
    s8 field_0;
    s8 positionIdx_1;
} s_800C38B0;

extern s_800C38B0 D_800C38B0;

extern s8 pad_bss_800C38B2[2];

extern s32 D_800C38B4;

extern s32 pad_bss_800C38B8[4];

extern s32 g_MapMsg_WidthTable[12];

/** String glyph sprite. */
extern GsSPRITE D_800C38F8;

extern s16 D_800C391C;

extern s16 pad_bss_800C391E;

extern s32 D_800C3920;

extern s32 pad_bss_800C3924;

// ==========
// FUNCTIONS
// ==========

/** Sets the position of the next string to be drawn by `Gfx_StringDraw`. */
void Gfx_StringSetPosition(s32 x, s32 y);

void Gfx_Strings2dLayerIdxSet(s32 idx);

void Gfx_StringsReset2dLayerIdx(void);

/** Sets the color of the next string drawn by `Gfx_StringDraw`. Uses `e_ColorId`. */
void Gfx_StringSetColor(s16 colorId);

/** Draws a string in screen space using 12x16 glyphs.
 *
 * @note References glyphs in `FONT16.TIM`. Although this texture atlas contains a single row with 84 glyphs,
 * the function implies 21 glyphs per row. Maybe the engine slices the texture into a stack in VRAM?
 * Notably, the atlas happens to have a 4-pixel space every 21st glyph.
 */
bool Gfx_StringDraw(char* str, s32 strLength);

void Gfx_MapMsg_CalculateWidths(s32 mapMsgIdx);

/** Draws string and returns map message index. */
s32 Gfx_MapMsg_StringDraw(char* mapMsg, s32 strLength);

void func_8004B658(void);

void Gfx_MapMsg_DefaultStringInfoSet(void);

/** @unused */
void func_8004B6D4(s16 arg0, s16 arg1);

/** @unused */
void func_8004B74C(s16 arg0);

/** @unused Draws string. */
void func_8004B76C(char* str, bool useFixedWidth);

/** Draws an integer string in screen space. */
void Gfx_StringDrawInt(s32 widthMin, s32 strLength);

void func_8004BB10(void);

#endif

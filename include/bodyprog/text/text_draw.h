#ifndef _BODYPROG_TEXT_TEXTDRAW_H
#define _BODYPROG_TEXT_TEXTDRAW_H

/** @note Likely the original name for this subsystem is `font` as indicated by SH2 and SH4 symbols. */

#define MAP_MSG_CODE_MARKER        '~' /** Message code start. */
#define MAP_MSG_CODE_COLOR         'C' /** Set color. */
#define MAP_MSG_CODE_DISPLAY_ALL   'D' /** Display message instantly with no rollout. */
#define MAP_MSG_CODE_END           'E' /** End message. */
#define MAP_MSG_CODE_HIGH_RES      'H' /** High-resolution glyph drawing. */
#define MAP_MSG_CODE_JUMP          'J' /** Jump timer. */
#define MAP_MSG_CODE_LINE_POSITION 'L' /** Set next line position. */
#define MAP_MSG_CODE_MIDDLE        'M' /** Align center. */
#define MAP_MSG_CODE_NEWLINE       'N' /** Newline. */
#define MAP_MSG_CODE_SELECT        'S' /** Display dialog prompt with selectable entries. */
#define MAP_MSG_CODE_TAB           'T' /** Inset line. */

#define FONT_12X16_GLYPH_COUNT        84
#define FONT_12X16_GLYPH_SIZE_X       12
#define FONT_12X16_GLYPH_SIZE_Y       16
#define FONT_12X16_SPACE_SIZE         6
#define FONT_12X16_LINE_COUNT_MAX     9
#define FONT_12X16_ATLAS_COLUMN_COUNT (FONT_12X16_GLYPH_COUNT / 4)

#define GLYPH_TABLE_ASCII_OFFSET '\'' /** Subtracted from ASCII bytes to get index to some string-related table. */

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

/** Used in string parsing. */
typedef struct
{
    /* 0x0 */ s8 unused;
    /* 0x1 */ u8 positionIdx;
} s_800C38B0;

// ====================
// GLOBALS (BSS; Hack; text_draw.c)
// ====================
// To match the order of the BSS segment, extern declarations
// are required in a predetermined order.
// This is done until a way to replicate `common`
// segment behavior is found.

/** String position. */
extern DVECTOR g_StringPosition; // 0x800C38A8

/** String X position as `s32`. It's unclear why there are two. */
extern s32 g_StringPositionX1; // 0x800C38AC

extern s_800C38B0 D_800C38B0;

extern s8 __pad_bss_800C38B2[2];

extern s32 g_MapMsg_WidthIdx;

extern s32 __pad_bss_800C38B8[4];

extern s32 g_MapMsg_Widths[12];

/** String glyph sprite. */
extern GsSPRITE g_MapMsg_GlyphSprite;

extern s16 D_800C391C;

extern s16 __pad_bss_800C391E;

extern s32 D_800C3920;

extern s32 __pad_bss_800C3924;

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

s32 Gfx_MapMsg_CalculateWidths(s32 mapMsgIdx);

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

#if VERSION_REGION_IS(NTSCJ)
    void func_8004B45C(s32 mapMsgBaseIdx, s32 arg1);
    void func_8004C8D8(u16*, s32*, s32);
    s32 func_8004C8AC(u8*);
#endif

// TODO: Move following funcs to item_screens_cam header.
#if VERSION_REGION_IS(NTSCJ)
    bool ItemScreen_TmdGsFCallInitTG3(void);
    void ItemScreen_TmdGsFCallInitG3G4(void);
    void ItemScreen_TmdGsFCallInitTG4(void);
#else
    void ItemScreen_TmdGsFCallInit(void);
#endif

#endif

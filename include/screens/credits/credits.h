#ifndef _SCREENS_CREDITS_H
#define _SCREENS_CREDITS_H

#include "common.h"

/** @brief Used for normal credits screen. */
typedef struct
{
    /* 0x0  */ s16  textX;  /** Prim vertex X. */
    /* 0x2  */ s16  textY;  /** Prim vertex Y. */
    /* 0x4  */ s16  leftMargin;  /** Width? */
    /* 0x6  */ s8   lineHeight;  /** Height? */
    /* 0x7  */ s8   semiTrans;  /** `bool` | Blend flag. */
    /* 0x8  */ s32  color;  /** Rgb24 color + code. */
    /* 0xC  */ s16* widthTable;  /** Points to 0x801E5C24, data size 400. */
    /* 0x10 */ s32* colorTable; /** Points to 0x801E5E24, data size 28, rgb24 + code. */
    /* 0x14 */ u16  tpage; /** Tpage for `setDrawTPage`, calculated from `uv` with `Credits_TextBlendSet`. */
    /* 0x16 */ s16  clut; /** Clut XY. */
    /* 0x18 */ u32  uv; /** Texture UV, tpageXY might be more accurate?. */
} s_800AFE08;
STATIC_ASSERT_SIZEOF(s_800AFE08, 28);

/** @brief Used for UFO ending credits screen. */
typedef struct
{
    /* 0x0  */ s_800AFE08 sub_0;
    /* 0x1C */ s32        field_1C;
    /* 0x20 */ s16        field_20;
    /* 0x22 */ s16        field_22;
    /* 0x24 */ s32        field_24;
    /* 0x28 */ s32        field_28;
    /* 0x2C */ s32        field_2C;
    /* 0x30 */ s32        field_30;
    /* 0x34 */ s32        field_34;
    /* 0x38 */ s32        field_38;
    /* 0x3C */ s32        field_3C;
    /* 0x40 */ s32        field_40;
    /* 0x44 */ s32        field_44;
    /* 0x48 */ s32        field_48;
    /* 0x4C */ s32        field_4C;
    /* 0x50 */ s32        field_50;
    /* 0x54 */ s32        field_54;
} s_800AFE24; // Size: 85

// Used by `func_801E2E28`.
typedef struct
{
    s16 xaSfxId;     /** SFX ID. */
    s16 scrollDelay; /** Initial value for the scrolling text timer, negative values cause delay before text is shown. */
    s16 field_4;     /** Text draw duration? Unsure. */
} s_801E5558;
STATIC_ASSERT_SIZEOF(s_801E5558, 6);

extern s_801E5558 D_801E5558[];

extern char* D_801E5590[]; // Credits string table.

extern char D_801E5BD0[]; // KCET string.

extern s32 D_801E5C20;

extern s16 D_801E5C24[256];

extern s32 D_801E5E24[7];

extern s32 D_801E5E40[7];

extern u8 D_801E5FF8[];

extern u8 D_801E5E5C[];

extern u8 D_801E5E6C[];

extern s32 D_801E5E74;

extern s32 D_801E5E78;

extern s32 D_801E5E7C;

extern s32 D_801E5E80;

extern s32 D_801E5E84;

extern s32 D_801E5E88;

extern s32 D_801E5E8C; // Index for some array used by most recent `func_801E2E28` call. `func_801E2ED8` accesses it.

extern u8 D_801E5E90[];

extern u8 D_801E5FD0[];

extern u32 D_801E600C; // Random 16-bit number.

void func_801E2E28(s32 idx);

bool func_801E2ED8(void);

bool func_801E2FC0(void);

void GameState_Credits_Update(void);

/** Draw some image on the screen. */
bool func_801E3124(void);

bool func_801E342C(void);

bool func_801E3304(void);

bool func_801E3684(void);

bool func_801E3970(void);

void func_801E386C(void);

void func_801E3DD0(void);

s32 func_801E3DF8(u8 arg0);

void Credits_TextPositionSet(s32 x, s32 y);

/** @brief Sets the current RGB+command color for `D_800AFE08` struct.
 *
 * Sets the packed RGB+command color for `D_800AFE08`,
 * with the command component hard-set to `PRIM_RECT | RECT_TEXTURE`.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void Credits_TextColorSet(s32 r, s32 g, s32 b);

void Credits_TextLineHeightSet(s8 arg0);

void Credits_TextBlendSet(bool semiTrans, u32 arg1);

void Credits_TextDraw(char* str);

void Credits_Text3dPositionSet(s32 arg0, s32 arg1);

/** @brief Sets the current RGB+command color for `D_800AFE2C`.
 *
 * Sets the packed RGB+command color for `D_800AFE10`,
 * with the command component hard-set to `GPU_COM_TF4`.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void Credits_Text3dColorSet(s32 r, s32 g, s32 b);

void Credits_Text3dLineHeightSet(s8 arg0);

void Credits_Text3dBlendSet(bool semiTrans, u32 arg1);

void Credits_Text3dDraw(u8* str);

#endif

#ifndef _SCREENS_CREDITS_H
#define _SCREENS_CREDITS_H

#include "common.h"

// Used by `func_801E2E28`.
typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
} s_801E5558;
STATIC_ASSERT_SIZEOF(s_801E5558, 6);

extern s_801E5558 D_801E5558[];

extern char* D_801E5590[]; // Credits string table.

extern char D_801E5BD0[]; // KCET string.

extern s32 D_801E5C20;

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

extern s32 D_801E600C; // Random 16-bit number.

void func_801E2E28(s32 idx);

bool func_801E2ED8();

bool func_801E2FC0();

void func_801E386C();

bool func_801E3970();

void func_801E3DD0();

/** Draw some image on the screen. */
bool func_801E3124();

bool func_801E342C();

s32 func_801E3304();

bool func_801E3684();

s32 func_801E3DF8(u8 arg0);

void func_801E42F8(s32 arg0, s32 arg1);

/** @brief Sets the current RGB+command color for `D_800AFE08` struct.
 *
 * Sets the packed RGB+command color for `D_800AFE08`,
 * with the command component hard-set to `PRIM_RECT | RECT_TEXTURE`.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void func_801E4310(s32 r, s32 g, s32 b);

void func_801E4340(s8 arg0);

void func_801E434C(u32 arg0, u32 arg1);

void func_801E4394(u8* str);

void func_801E47E0(s32 arg0, s32 arg1);

/** @brief Sets the current RGB+command color for `D_800AFE2C`.
 *
 * Sets the packed RGB+command color for `D_800AFE10`,
 * with the command component hard-set to `GPU_COM_TF4`.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void func_801E4B98(s32 r, s32 g, s32 b);

void func_801E4BC8(s8 arg0);

/** Identical to `func_801E434C` except for the global variable it modifies. */
void func_801E4BD4(u32 arg0, u32 arg1);

void func_801E4C1C(u8* str);

#endif

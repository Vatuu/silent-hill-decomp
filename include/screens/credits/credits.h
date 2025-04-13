#ifndef _CREDITS_H
#define _CREDITS_H

#include "common.h"

// Used by `func_801E2E28`.
typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
} s_UnkCredits1;
STATIC_ASSERT_SIZEOF(s_UnkCredits1, 6);

extern s_UnkCredits1 D_801E5558[];

extern RECT D_801E557C[];

extern s32 D_801E5590[];

extern s32 D_801E5BD0;

extern s32 D_801E5C20;

extern s32 D_801E5E74;

extern s32 D_801E5E78;

extern s32 D_801E5E7C;

extern s32 D_801E5E80;

extern s32 D_801E5E84;

extern s32 D_801E5E88;

extern s32 D_801E5E8C; // Index for some array used by most recent `func_801E2E28` call. `func_801E2ED8` accesses it.

extern s32 D_801E600C; // Random 16-bit number.

void func_801E2E28(s32 idx);

s32 func_801E2ED8();

void func_801E386C();

void func_801E3DD0();

/** Draw some image on the screen. */
s32 func_801E3124();

s32 func_801E342C();

s32 func_801E3304();

bool func_801E3684();

s32 func_801E3DF8(s32 arg0);

void func_801E42F8(s32 arg0, s32 arg1);

/** @brief Sets the current RGB+command color for `D_800AFE08` struct.
 *
 * This function sets the packed RGB+command color for `D_800AFE08` with
 * the fourth component hard set to 0x64, possibly a graphics command.
 * 
 * @note RGB order only assumed.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void func_801E4310(s32 r, s32 g, s32 b);

void func_801E4340(s8 arg0);

void func_801E434C(u32 arg0, u32 arg1);

/**
 * @brief Sets the current RGB+command color for D_800AFE2C.
 *
 * This function sets the packed RGB+command color for D_800AFE10 with
 * the fourth component hard set to 0x2C, possibly a graphics command.
 * 
 * @note RGB order only assumed.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void func_801E4B98(s32 r, s32 g, s32 b);

void func_801E4BC8(s8 arg0);

/** Identical to `func_801E434C` except for the global variable it modifies. */
void func_801E4BD4(u32 arg0, u32 arg1);

#endif

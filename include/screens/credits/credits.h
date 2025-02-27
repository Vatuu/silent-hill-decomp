#ifndef CREDITS_H
#define CREDITS_H

#include "common.h"

void func_801E2E28(s32 idx);

void func_801E3DD0(void);

s32 func_801E3DF8(s32 arg0);

void func_801E42F8(s16 arg0, s16 arg1);

/**
 * @brief Sets the current RGB+command color for D_800AFE10.
 *
 * This function sets the packed RGB+command color for D_800AFE10 with
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

/** Identical to func_801E434C except for the global variable it modifies. */
void func_801E4BD4(u32 arg0, u32 arg1);

#endif

#ifndef _CREDITS_H
#define _CREDITS_H

#include "common.h"

typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s8  unk_6;
    s8  field_7; // bool
    s32 unk_8;
    s32 unk_C;
    s32 unk_10;
    u16 field_14;
    s16 unk_16;
    u32 field_18;
} s_UnkCredits0; // Size: >=2C

// Used by func_801E2E28.
typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
} s_UnkCredits1; // Size: 6

typedef struct
{
    u32 unk_0;
    u32 unk_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
    u32 field_14;
    u32 unk_18;
    u32 field_1C;
    u32 field_20;
    u32 field_24;
    u32 field_28;
    u32 field_2C;
} s_UnkCredits2; // Size: >=48

extern s_UnkCredits0 D_800AFE08;
extern s8            D_800AFE0E;
extern s32           D_800AFE10; // Packed RGB+command color? Command is 0x64.
extern s_UnkCredits0 D_800AFE24;
extern s8            D_800AFE2A;
extern s32           D_800AFE2C; // Packed RGB+command color? Command is 0x2C.
extern s_UnkCredits2 g_Syswork;
extern s32           D_800C48F0;
extern s_UnkCredits1 D_801E5558[];
extern RECT          D_801E557C[];
extern s32           D_801E5C20;
extern s32           D_801E5E74;
extern s32           D_801E5E7C;
extern s32           D_801E5E80;
extern s32           D_801E5E84;
extern s32           D_801E5E88;
extern s32           D_801E5E8C; // Index for some array used by most recent func_801E2E28 call. func_801E2ED8 accesses it.
extern s32           D_801E600C; // Random 16-bit number.

void func_801E2E28(s32 idx);

s32 func_801E2ED8(void);

void func_801E3DD0(void);

s32 func_801E3124(void);

s32 func_801E3304(void);

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

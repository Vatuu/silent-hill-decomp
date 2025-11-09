#ifndef _BODYPROG_CREDITS_H
#define _BODYPROG_CREDITS_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the credits system.
 */

// ========
// STRUCTS
// ========

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
    u8 field_4;
    u8 field_5;
    u8 field_6;
    u8 field_7;
    u8 field_8;
    u8 unk_9;
    u8 unk_A;
    u8 unk_B;
    u8 unk_C;
    u8 unk_D;
    u8 unk_E;
    u8 unk_F;
} s_800C48E0;

// ========
// GLOBALS
// ========

// Data below is likely part of a collected results data struct.

//extern s_800AFDF4 D_800AFDF4;

/** Savegame count. */
extern s16 D_800C48A0;

/** Gameplay time. */
extern u16 D_800C48A2;

extern u16 D_800C48A4;

extern u16 D_800C48A6;

extern u16 D_800C48A8;

extern u16 D_800C48AA;

/** Picked up item count. */
extern u16 D_800C48AC;

extern u8 D_800C48AE;

extern u8 D_800C48AF;

/** Clear game count. */
extern u8 D_800C48B0;

/** Clear game endings. */
extern u8 D_800C48B1;

extern u8 D_800C48B2;

/** Location ID. */
extern u8 D_800C48B3;

extern u8 D_800C48B4;

extern s8 D_800C48B5;

extern u8 D_800C48B6;

extern u8 D_800C48B7;

extern u16 D_800C48B8;

extern u16 D_800C48BA;

/** Has fired shots. */
extern bool D_800C48BC;

/** Close range shot count. */
extern u32 D_800C48C0;

/** Mid range shot count. */
extern u32 D_800C48C4;

/** Long range shot count. */
extern u32 D_800C48C8;

extern u32 D_800C48CC;

/** Game difficulty. */
extern s8 D_800C48D0;

/** Continue count. */
extern u8 D_800C48D1;

extern s_800C48E0 D_800C48E0;

// ==========
// FUNCTIONS
// ==========

/** Processes and collects results data. */
void func_8008F94C(void);

void func_800904F4(void);

void Results_DisplayInfo(u32* arg0); // 0x80090664

void func_80090664(void);

u32 func_8009134C(u32 n);

void func_80091380(void);

void func_80091388(s32 arg0, s32 arg1, s32 arg2);

void func_80091464(void);

u32 func_8009146C(s32 arg0);

void func_800914C4(s32 arg0, u32 value);

void GameFs_StfRollBinLoad(void);

void func_800917C0(void* arg0, s32 arg1, s_FsImageDesc* img);

void func_8009185C(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

#endif

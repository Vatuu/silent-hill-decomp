#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "game.h"
#include "main/fsqueue.h"

#define IMAGE_BUFFER_0 (u_long*)0x801CFA00
#define IMAGE_BUFFER_1 (u_long*)0x801C8200

typedef struct
{
    s32 unk_0[2];
    s32 field_8;
    s32 unk_C[2213];
    s32 field_22A0;
    s32 field_22A4;
} s_SystemWork; // Size: >=8868

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
} s_80041CB4;

typedef struct
{
    s8  unk_0[4];
    s32 field_4;
    s8  unk_8[18];
} s_80041D10; // Size: 28

typedef struct
{
    s8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
    s8 unk_4[4];
    s8 field_8;
} s_80041CEC;

/** Something related to ANM files. See `D_800A90FC`. */
typedef struct
{
    s16 fileIdx;
    s16 field_2;
    u32 field_4;
    u32 field_8;
    u32 field_C;
} s_800A90FC;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18; 
} s_800B5508;

/** Accessed by credits and saveload. */
extern s32 D_800A8FF0;

extern s16 D_800AD498;

extern s32 D_800AD49C;

/** Unknown bodyprog var. Used in `Fs_QueueStartReadAnm`. */
extern s_800A90FC D_800A90FC[];

extern s_800B5508 D_800B2780[];

extern s_800B5508 D_800B3680[];

extern s_800B5508 D_800B4580[];

extern s32 D_800B5480;

extern s_800B5508 D_800B5508[];

extern s_800B5508 D_800B55E8;

extern s32 D_800B55FC;

extern s32 D_800B5618;

extern u16 D_800BCCB0;

extern u16 D_800BCCB2;

/** Accessed by credits and saveload. */
extern s32 D_800BCD0C;

extern s16 D_800C38A8;

extern s16 D_800C38AA;

extern s32 D_800C38AC;

extern s16 D_800C38FC;

extern s16 D_800C38FE;

extern s16 D_800C391C;

extern s16 D_800C391E;

/** Unknown bodyprog var. Set in `Fs_QueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

/** Initializer for something before the game loop. */
void func_8002E630();

void func_8002E6E4(s32 idx);

void func_8002E730(s32 idx);

/** Initializer for something before the game loop. */
void func_8002E7BC();

void func_8002E830();

void func_8002E85C();

void func_8002E8D4();

s32 func_8002E990();

void func_8002EB88(); // Return type assumed.

void func_8002ECE0(s_800B5508* arg0);

void func_800303E4();

/** Bodyprog function that fades the screen out?
 * Called by:
 * - `main` in main.c
 * - 'func_801E709C' in saveload.c */
void func_800314EC(s_FsImageDesc* image);

s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5);

void GFX_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

/** Bodyprog func that searches for English title screen background graphic. */
void GameFS_TitleGfxSeek();

void func_8003260C(); // Return type assumed.

/** Bodyprog entrypoint. Called by `main`. */
void func_80032EE0(void);

void func_80033548(); // Return type assumed.

/** Unknown bodyprog func. Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 arg0, s32 arg1, void* arg2, s32 arg3);

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003c850(void);

void func_8003D160(); // Return type assumed.

/** Some kind of queue entry load status getter. */
s32 func_80041ADC(s32 queueIdx);

void func_80041CB4(s_80041CB4* arg0, s_80041CEC* arg1);

void func_80041CEC(s_80041CEC*);

/** Clears some field in some struct. */
void func_80041D10(s_80041D10* array, s32 size);

u8 func_80045B28();

void func_8004729C(u16);

void func_8005E0DC(s32); // Types assumed.

/** Unknown bodyprog func. Called by `Fs_QueueWaitForEmpty`. */
void func_80089128(void);

/** Unknown bodyprog func. Called by `Fs_QueueWaitForEmpty` with `0` and then `1`. */
void func_800892A4(s32);

void func_801E2D8C();

/** Updates the footer with the checksum of the given data */
void SaveGame_ChecksumUpdate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength);

/** Generates checksum of the given saveData and compares against checksum value in the footer
    Return 1 if checksum matches, otherwise 0 */
s32 SaveGame_ChecksumValidate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength);

/** Generates an 8-bit XOR checksum over the given data, only appears used with s_ShSaveGame data */
u8 SaveGame_ChecksumGenerate(s8* saveData, s32 saveDataLength);

#endif

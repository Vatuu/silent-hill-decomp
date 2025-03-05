#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "common.h"
#include "main/fsqueue.h"

typedef struct
{
    u8  unk_0[1420];
    u8  field_58C; // R?
    u8  field_58D; // G?
    u8  field_58E; // B?
    u8  field_58F;
    u32 field_590;
    u32 field_594; // Maybe some game state enum entry.
    u32 field_598;
    u32 field_59C;
    u32 field_5A0;
} s_GameSystem; // Size: >=1444

typedef struct
{
    s32 unk_0[2];
    s32 field_8;
    s32 unk_C[2213];
    s32 field_22A0;
    s32 field_22A4;
} s_SystemWork; // Size: >=8868

/** Something related to ANM files. See `D_800A90FC`. */
typedef struct
{
    s16 fileIdx;
    s16 field_2;
    u32 field_4;
    u32 field_8;
    u32 field_C;
} s_800A90FC;

// GameSystem
extern s_GameSystem D_800BC728;

/** Vars accessed by credits and saveload. */
extern s32 D_800A8FF0;
extern s32 D_800BCD0C;

/** Unknown bodyprog var. Used in `Fs_QueueStartReadAnm`. */
extern s_800A90FC D_800A90FC[];

/** Unknown bodyprog var. Set in `Fs_QueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

/** Bodyprog function that fades the screen out?
 * Called by:
 * - `main` in main.c
 * - 'func_801E709C' in saveload.c */
void func_800314EC(s_FsImageDesc* arg0);

/** Bodyprog entrypoint. Called by `main`. */
void func_80032EE0(void);

/** Unknown bodyprog function. Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 arg0, s32 arg1, void* arg2, s32 arg3);

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003c850(void);

/** Unknown bodyprog func. Called by `Fs_QueueWaitForEmpty`. */
void func_80089128(void);

/** Unknown bodyprog func. Called by `Fs_QueueWaitForEmpty` with `0` and then `1`. */
void func_800892A4(s32);

#endif

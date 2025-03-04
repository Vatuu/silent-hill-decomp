#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "common.h"
#include "main/fsqueue.h"

/** Declarations for unknown symbols in bodyprog. */

/** Something related to ANM files. See `D_800A90FC`. */
typedef struct
{
    s16 fileIdx;
    s16 field_02;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
} s_800A90FC;

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

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

/** Unknown bodyprog var. Used in `Fs_StartQueueReadAnm`. */
extern s_800A90FC D_800A90FC[];

extern s_800B5508 D_800B2780[];

extern s_800B5508 D_800B3680[];

extern s_800B5508 D_800B4580[];

extern s_800B5508 D_800B5508[];

extern s_800B5508 D_800B55E8;

extern s32 D_800B5480;

extern s32 D_800B5618;

extern s32 D_800B55FC;

/** Unknown bodyprog var. Set in `Fs_DoQueueThingWhenEmpty`. */
extern s32 D_800C489C;

void func_8002E630();

void func_8002E6E4(s32 idx);

void func_8002E730(s32 arg0);

void func_8002E7BC();

void func_8002E830();

void func_8002E85C();

void func_8002E8D4();

s32 func_8002E990();

void func_8002ECE0(s_800B5508* arg0);

void func_800303E4();

/** Bodyprog function that fades the screen out?
 * Called by:
 * - `main` in main.c
 * - 'func_801E709C' in saveload.c */
void func_800314EC(s_FsImageDesc* arg0);

void GFX_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

/** Bodyprog func that searches for English title screen background graphic. */
void GameFS_TitleGfxSeek();

/** Bodyprog entrypoint. Called by `main`. */
void func_80032EE0(void);

/** Unknown bodyprog func. Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 arg0, s32 arg1, void* arg2, s32 arg3);

/** Unknown bodyprog func. Called by `Fs_DoQueueThingWhenEmpty`. */
s32 func_8003c850(void);

/** Unknown bodyprog func. Called by `Fs_WaitForEmptyQueue`. */
void func_80089128(void);

/** Unknown bodyprog func. Called by `Fs_WaitForEmptyQueue` with `0` and then `1`. */
void func_800892A4(s32);

#endif

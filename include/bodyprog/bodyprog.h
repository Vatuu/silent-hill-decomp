#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "common.h"
#include "main/fsqueue.h"

/** Declarations for unknown symbols in bodyprog. */

/** Something related to ANM files. See `D_800A90FC`. */
typedef struct {
  s16 fileno;
  s16 field_02;
  u32 field_04;
  u32 field_08;
  u32 field_0c;
} struct_800A90FC;

/** Unknown bodyprog var. Used in `fsQueueStartReadAnm`. */
extern struct_800A90FC D_800A90FC[];

/** Unknown bodyprog var. Set in `fsQueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

/** Bodyprog function that fades the screen out? Called by `main`. */
void func_800314EC(FsImageDesc *arg0);

/** Bodyprog entrypoint. Called by `main`. */
void func_80032EE0(void);

/** Unknown bodyprog function. Called by `fsQueuePostLoadAnm`. */
void func_80035560(s32, s32, void*, s32);

/** Unknown bodyprog func. Called by `fsQueueDoThingWhenEmpty`. */
s32 func_8003c850(void);

/** Unknown bodyprog func. Called by `fsQueueWaitForEmpty`. */
void func_80089128(void);

/** Unknown bodyprog func. Called by `fsQueueWaitForEmpty` with `0` and then `1`. */
void func_800892A4(s32);

#endif

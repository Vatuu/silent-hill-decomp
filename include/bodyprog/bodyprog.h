#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "common.h"

/** Declarations for unknown symbols in bodyprog. */

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

/** Unknown bodyprog func. Called by `fsQueueDoThingWhenEmpty`. */
s32 func_8003c850();

/** Unknown bodyprog func. Called by `fsQueueWaitForEmpty`. */
extern void func_80089128(void);

/** Unknown bodyprog func. Called by `fsQueueWaitForEmpty` with `0` and then `1`. */
extern void func_800892A4(s32);

#endif

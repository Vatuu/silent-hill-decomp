#ifndef _DYNAMIC_H
#define _DYNAMIC_H

#include "common.h"

/** Declarations for unknown symbols in dynamic overlays. */

/** Dynamic overlay function? Called by `fsQueueWaitForEmpty`. */
extern void func_80089128(void);

/** Dynamic overlay function? Called by `fsQueueWaitForEmpty` with `0` and then `1`. */
extern void func_800892A4(s32);

#endif

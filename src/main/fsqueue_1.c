#include "fsqueue.h"

s32 fsQueueIsEntryLoaded(s32 arg0) {
  return arg0 < g_FsQueue.postload_idx;
}

s32 fsQueueGetLength(void) {
  return g_FsQueue.last_idx + 1 - g_FsQueue.postload_idx;
}

s32 fsQueueDoThingWhenEmpty(void) {
  s32 result;

  D_800C489C = 1;

  result = 0;

  if (fsQueueGetLength() == 0) {
    result = func_8003c850() != 0;
  }

  return result;
}

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueWaitForEmpty);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueStartSeek);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueStartRead);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueStartReadTim);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueStartReadGsThing);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueEnqueue);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueInit);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueReset);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueUpdate);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueUpdateSeek);

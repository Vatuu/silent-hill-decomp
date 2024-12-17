#include "main_2.h"

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

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueWaitForEmpty);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueStartSeek);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueStartRead);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueStartReadTim);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueStartReadGsThing);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueEnqueue);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueInit);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueReset);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueUpdate);

INCLUDE_ASM("asm/main/nonmatchings/main_2", fsQueueUpdateSeek);

#include "fsqueue.h"
#include "fsmem.h"
#include <MEMORY.H>

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

void fsQueueInit(void) {
  bzero(&g_FsQueue, sizeof(g_FsQueue));
  g_FsQueue.last_idx = -1;
  g_FsQueue.last_ptr = &g_FsQueue.entries[FS_QUEUE_MAX - 1];
  g_FsQueue.read_idx = 0;
  g_FsQueue.read_ptr = g_FsQueue.entries;
  g_FsQueue.postload_idx = 0;
  g_FsQueue.postload_ptr = g_FsQueue.entries;
  g_FsQueue.state = 0;
  g_FsQueue.postload_state = 0;
  g_FsQueue.reset_timer_0 = 0;
  g_FsQueue.reset_timer_1 = 0;
  fsMemInit(0x1C0000, 0x20000);
}

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueReset);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueUpdate);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueUpdateSeek);

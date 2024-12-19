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

s32 fsQueueStartSeek(s32 fileno) {
  return fsQueueEnqueue(fileno, FS_OP_SEEK, FS_POSTLOAD_NONE, false, NULL, 0, NULL);
}

s32 fsQueueStartRead(s32 fileno, void* dst) {
  return fsQueueEnqueue(fileno, FS_OP_READ, FS_POSTLOAD_NONE, false, dst, 0, NULL);
}

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueStartReadTim);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueStartReadGsThing);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueEnqueue);

void fsQueueInit(void) {
  bzero(&g_FsQueue, sizeof(g_FsQueue));
  g_FsQueue.last_idx = -1;
  g_FsQueue.last_ptr = &g_FsQueue.entries[FS_QUEUE_LEN - 1];
  g_FsQueue.read_idx = 0;
  g_FsQueue.read_ptr = g_FsQueue.entries;
  g_FsQueue.postload_idx = 0;
  g_FsQueue.postload_ptr = g_FsQueue.entries;
  g_FsQueue.state = 0;
  g_FsQueue.postload_state = 0;
  g_FsQueue.reset_timer_0 = 0;
  g_FsQueue.reset_timer_1 = 0;
  fsMemInit(FS_MEM_BASE, FS_MEM_SIZE);
}

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueReset);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueUpdate);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_1", fsQueueUpdateSeek);

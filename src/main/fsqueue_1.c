#include "main/fsqueue.h"
#include "main/fsmem.h"
#include "bodyprog/bodyprog.h"
#include <MEMORY.H>
#include <LIBETC.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

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

void fsQueueWaitForEmpty(void) {
  func_800892A4(0);
  func_80089128();

  while (true) {
    VSync(0);
    if (fsQueueGetLength() <= 0) {
      break;
    }
    fsQueueUpdate();
  }

  func_800892A4(1);
  DrawSync(0);
  VSync(0);
}

s32 fsQueueStartSeek(s32 fileno) {
  return fsQueueEnqueue(fileno, FS_OP_SEEK, FS_POSTLOAD_NONE, false, NULL, 0, NULL);
}

s32 fsQueueStartRead(s32 fileno, void *dst) {
  return fsQueueEnqueue(fileno, FS_OP_READ, FS_POSTLOAD_NONE, false, dst, 0, NULL);
}

s32 fsQueueStartReadTim(s32 fileno, void *dst, FsImageDesc *image) {
  FsQueueExtra extra;

  if (image != NULL) {
    extra.image = *image;
  } else {
    // u == 0xFF (-1) is a special case for "image descriptor not set"
    extra.image.u = 0xFF;
    extra.image.clut_x = -1;
    extra.image.v = 0xFF;
    extra.image.clut_y = -1;
  }

  return fsQueueEnqueue(fileno, FS_OP_READ, FS_POSTLOAD_TIM, false, dst, 0, &extra);
}

s32 fsQueueStartReadAnm(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
  s32 fileno;
  FsQueueExtra extra;
  fileno = D_800A90FC[arg1].fileno;
  extra.anm.field_04 = arg1;
  extra.anm.field_00 = arg0;
  extra.anm.field_08 = arg3;
  return fsQueueEnqueue(fileno, FS_OP_READ, FS_POSTLOAD_ANM, false, arg2, 0, &extra);
}

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

#include "main/fsqueue.h"
#include "main/fsmem.h"
#include "bodyprog/bodyprog.h"
#include <MEMORY.H>
#include <LIBETC.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBCD.H>

FsQueue g_FsQueue;

s32 fsQueueIsEntryLoaded(s32 arg0) {
  return arg0 < g_FsQueue.postload.idx;
}

s32 fsQueueGetLength(void) {
  return g_FsQueue.last.idx + 1 - g_FsQueue.postload.idx;
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

s32 fsQueueEnqueue(s32 fileno, u8 op, u8 postload, u8 alloc, void *data, u32 unused_1, FsQueueExtra *extra) {
  FsQueueEntry *new_entry;
  FsQueuePtr *lastp;

  // wait for space in queue
  while (fsQueueGetLength() >= FS_QUEUE_LEN) {
    fsQueueUpdate();
  }

  // this is the entire reason I wrapped these pointers and indices into structs
  // if they're left as-is in the queue struct, this does not match unless you manually address them
  lastp = &g_FsQueue.last;
  lastp->idx++;
  lastp->ptr = &g_FsQueue.entries[lastp->idx & (FS_QUEUE_LEN - 1)];

  new_entry = g_FsQueue.last.ptr;
  new_entry->info = &g_FileTable[fileno];
  new_entry->operation = op;
  new_entry->postload = postload;
  new_entry->allocate = alloc;
  new_entry->external_data = data;
  new_entry->unused_1 = unused_1;

  if (extra != NULL) {
    new_entry->extra = *extra;
  }

  return g_FsQueue.last.idx;
}

void fsQueueInit(void) {
  bzero(&g_FsQueue, sizeof(g_FsQueue));
  g_FsQueue.last.idx = -1;
  g_FsQueue.last.ptr = &g_FsQueue.entries[FS_QUEUE_LEN - 1];
  g_FsQueue.read.idx = 0;
  g_FsQueue.read.ptr = g_FsQueue.entries;
  g_FsQueue.postload.idx = 0;
  g_FsQueue.postload.ptr = g_FsQueue.entries;
  g_FsQueue.state = 0;
  g_FsQueue.postload_state = 0;
  g_FsQueue.reset_timer_0 = 0;
  g_FsQueue.reset_timer_1 = 0;
  fsMemInit(FS_MEM_BASE, FS_MEM_SIZE);
}

void fsQueueReset(void) {
  if (fsQueueGetLength() <= 0) {
    return;
  }

  if (g_FsQueue.read.idx <= g_FsQueue.last.idx) {
    g_FsQueue.read.idx = g_FsQueue.read.idx + FS_QUEUE_LEN;
    g_FsQueue.read.ptr = g_FsQueue.entries + (g_FsQueue.read.idx & (FS_QUEUE_LEN - 1));
    g_FsQueue.last = g_FsQueue.read;
  }

  g_FsQueue.postload = g_FsQueue.read;
  g_FsQueue.postload_state = 0;
  g_FsQueue.read.ptr->postload = 0;
}

void fsQueueUpdate(void) {
  FsQueuePtr *read;
  FsQueueEntry *tick;
  s32 tmp = 0;

  tick = g_FsQueue.read.ptr;
  if (g_FsQueue.read.idx <= g_FsQueue.last.idx) {
    // there are pending read/seek operations, tick them
    switch (tick->operation) {
      case FS_OP_SEEK:
        tmp = fsQueueUpdateSeek(tick);
        break;
      case FS_OP_READ:
        tmp = fsQueueUpdateRead(tick);
        break;
    }
    if (tmp == 1) {
      // seek or read done, proceed to the next one
      // alias and tmp use seem to be required for a match for some reason, might be an inline?
      read = &g_FsQueue.read;
      g_FsQueue.state = 0; // FSQS_READ_ALLOCATE or FSQS_SEEK_SETLOC
      g_FsQueue.reset_timer_0 = 0;
      g_FsQueue.reset_timer_1 = 0;
      tmp = ++read->idx;
      read->ptr = g_FsQueue.entries + (tmp & (FS_QUEUE_LEN - 1));
    }
  } else {
    // nothing to read
    g_FsQueue.state = 0; // FSQS_READ_ALLOCATE or FSQS_SEEK_SETLOC
  }

  tick = g_FsQueue.postload.ptr;
  if (g_FsQueue.postload.idx < g_FsQueue.read.idx) {
    // there are operations to postload in the queue, tick them
    tmp = fsQueueUpdatePostLoad(tick);
    if (tmp == 1) {
      g_FsQueue.postload_state = FSQS_POSTLOAD_INIT;
      tmp = ++g_FsQueue.postload.idx;
      g_FsQueue.postload.ptr = g_FsQueue.entries + (tmp & (FS_QUEUE_LEN - 1));
    }
  } else {
    // nothing to postload
    g_FsQueue.postload_state = FSQS_POSTLOAD_INIT;
  }
}

s32 fsQueueUpdateSeek(FsQueueEntry* entry) {
  s32 result = 0;
  s32 state = g_FsQueue.state;

  switch (state) {
    case FSQS_SEEK_SETLOC:
      switch (fsQueueTickSetLoc(entry)) {
        case 0:
          // CdlSetloc failed, reset and retry
          g_FsQueue.state = FSQS_SEEK_RESET;
          break;
        case 1:
          g_FsQueue.state = FSQS_SEEK_SEEKL;
          break;
      }
      break;

    case FSQS_SEEK_SEEKL:
      switch (CdControl(CdlSeekL, NULL, NULL)) {
        case 0:
          // CdlSeekL failed, reset and retry
          g_FsQueue.state = FSQS_SEEK_RESET;
          break;
        case 1:
          g_FsQueue.state = FSQS_SEEK_SYNC;
          break;
      }
      break;

    case FSQS_SEEK_SYNC:
      switch (CdSync(1, NULL)) {
        case CdlNoIntr:
          // wait some more, operation in progress
          break;
        case CdlComplete:
          // we're done seeking
          result = 1;
          break;
        case CdlDiskError:
          // disk error, reset and try again
          g_FsQueue.state = FSQS_SEEK_RESET;
          break;
        default:
          // unknown error, reset and try again
          g_FsQueue.state = FSQS_SEEK_RESET;
          break;
      }
      break;

    case FSQS_SEEK_RESET:
      switch (fsQueueTickReset(entry)) {
        case 0:
          // still resetting
          break;
        case 1:
          // reset done, try again from the beginning
          g_FsQueue.state = FSQS_SEEK_SETLOC;
          break;
      }
      break;
  }

  return result;
}

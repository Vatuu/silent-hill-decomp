#include "main/fsqueue.h"
#include <libcd.h>

s32 fsQueueUpdateRead(FsQueueEntry* entry) {
  s32 status;
  s32 result;

  result = false;

  switch (g_FsQueue.state) {
    case FSQS_READ_ALLOCATE:
      switch (fsQueueAllocEntryData(entry)) {
        case 0:
          // I guess this will just retry until memory is allocated?
          break;
        case 1:
          g_FsQueue.state = FSQS_READ_CHECK;
          break;
      }
      break;

    case FSQS_READ_CHECK:
      switch (fsQueueCanRead(entry)) {
        case 0:
          // can't read yet, memory is in use by another operation, wait until next tick
          break;
        case 1:
          g_FsQueue.state = FSQS_READ_SETLOC;
          break;
      }
      break;

    case FSQS_READ_SETLOC:
      switch (fsQueueTickSetLoc(entry)) {
        case 0:
          // CdlSetloc failed, reset CD
          g_FsQueue.state = FSQS_READ_RESET;
          break;
        case 1:
          g_FsQueue.state = FSQS_READ_READ;
          break;
      }
      break;

    case FSQS_READ_READ:
      switch (fsQueueTickRead(entry)) {
        case 0:
          // CdRead failed, reset CD and retry
          g_FsQueue.state = FSQS_READ_RESET;
          break;
        case 1:
          g_FsQueue.state = FSQS_READ_SYNC;
          break;
      }
      break;

    case FSQS_READ_SYNC:
      // check how the read is going
      switch (CdReadSync(1, NULL)) {
        case -1:
          // CdReadSync failed, reset CD
          g_FsQueue.state = FSQS_READ_RESET;
          break;
        case 0:
          // done reading, no state transition, let caller know that we're done
          result = 1;
          break;
      }
      break;

    case FSQS_READ_RESET:
      switch (fsQueueTickReset(entry)) {
        case 0:
          // still resetting
          break;
        case 1:
          // reset done, try again from the setloc
          g_FsQueue.state = FSQS_READ_SETLOC;
          break;
      }
      break;
  }

  return result;
}

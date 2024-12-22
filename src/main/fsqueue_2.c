#include "main/fsqueue.h"
#include <LIBCD.H>

s32 fsQueueUpdateRead(FsQueueEntry* entry) {
  s32 status;
  s32 result;

  result = false;

  switch (g_FsQueue.state) {
    case FSQS_READ_ALLOCATE:
      status = fsQueueAllocEntryData(entry);
      // these double checks seem to be required for a match
      if (status == 0) {
        // I guess this will just retry until memory is allocated?
        break;
      }
      if (status == 1) {
        g_FsQueue.state = FSQS_READ_CHECK;
      }
      break;

    case FSQS_READ_CHECK:
      status = fsQueueCanRead(entry);
      if (status == 0) {
        // can't read yet, memory is in use by another operation, wait until next tick
        break;
      }
      if (status == 1) {
        g_FsQueue.state = FSQS_READ_SETLOC;
      }
      break;

    case FSQS_READ_SETLOC:
      status = fsQueueTickSetLoc(entry);
      // @FIXME: can't figure out how to get this and other cases to match otherwise,
      // no if/else/break/whatever combination seems to work, but this does
      if (status == 0) {
        // CdlSetloc failed, reset CD
        goto _setloc_fail;
      }
      if (status == 1) {
        goto _setloc_ok;
      }
      break;
_setloc_fail:
      g_FsQueue.state = FSQS_READ_RESET;
      break;
_setloc_ok:
      g_FsQueue.state = FSQS_READ_READ;
      break;

    case FSQS_READ_READ:
      status = fsQueueTickRead(entry);
      if (status == 0) {
        // CdRead failed, reset CD
        goto _read_fail;
      }
      if (status == 1) {
        goto _read_ok;
      }
      break;
_read_fail:
      g_FsQueue.state = FSQS_READ_RESET;
      break;
_read_ok:
      g_FsQueue.state = FSQS_READ_SYNC;
      break;

    case FSQS_READ_SYNC:
      // check how the read is going
      status = CdReadSync(1, NULL);
      if (status == -1) {
        // CdReadSync failed, reset CD
        goto _sync_fail;
      }
      if (status == 0) {
        // finished reading, no state transition
        goto _sync_ok;
      }
      break;
_sync_fail:
      g_FsQueue.state = FSQS_READ_RESET;
      break;
_sync_ok:
      // finished reading, no state transition, let caller know that we're done
      result = 1;
      break;

    case FSQS_READ_RESET:
      status = fsQueueTickReset(entry);
      if (status == 0) {
        break;
      }
      if (status == 1) {
        g_FsQueue.state = FSQS_READ_SETLOC;
      }
      break;
  }

  return result;
}

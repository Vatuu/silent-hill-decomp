#include "main/fsqueue.h"

#include <LIBCD.H>

s32 fsQueueUpdateRead(FsQueueEntry* entry)
{
    s32 status;
    s32 result;

    result = false;
    switch (g_FsQueue.state)
    {
        case FSQS_READ_ALLOCATE:
            switch (fsQueueAllocEntryData(entry))
            {
                // Retry until memory is allocated?
                case 0:
                    break;

                case 1:
                    g_FsQueue.state = FSQS_READ_CHECK;
                    break;
            }

            break;

        case FSQS_READ_CHECK:
            switch (fsQueueCanRead(entry))
            {
                // Can't read yet; memory in use by another operation. Wait until next tick.
                case 0:
                    break;

                case 1:
                    g_FsQueue.state = FSQS_READ_SETLOC;
                    break;
            }

            break;

        case FSQS_READ_SETLOC:
            switch (fsQueueTickSetLoc(entry))
            {
                // CdlSetloc failed; reset CD.
                case 0:
                    g_FsQueue.state = FSQS_READ_RESET;
                    break;

                case 1:
                    g_FsQueue.state = FSQS_READ_READ;
                    break;
            }

            break;

        case FSQS_READ_READ:
            switch (fsQueueTickRead(entry))
            {
                // CdRead failed; reset CD and retry.
                case 0:
                    g_FsQueue.state = FSQS_READ_RESET;
                    break;

                case 1:
                    g_FsQueue.state = FSQS_READ_SYNC;
                    break;
            }

            break;

        // Check how read is going.
        case FSQS_READ_SYNC:
            switch (CdReadSync(1, NULL))
            {
                // CdReadSync failed; reset CD.
                case -1:
                    g_FsQueue.state = FSQS_READ_RESET;
                    break;

                // Done reading; no state transition, let caller know that it's done.
                case 0:
                    result = true;
                    break;
            }

            break;

        case FSQS_READ_RESET:
            switch (fsQueueTickReset(entry))
            {
                // Still resetting.
                case 0:
                    break;

                // Reset done; retry from setloc.
                case 1:
                    g_FsQueue.state = FSQS_READ_SETLOC;
                    break;
            }

            break;
    }

    return result;
}

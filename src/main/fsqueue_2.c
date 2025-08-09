#include "main/fsqueue.h"

#include <libcd.h>

bool Fs_QueueUpdateRead(s_FsQueueEntry* entry)
{
    bool result;

    result = false;
    switch (g_FsQueue.state)
    {
        case FSQS_READ_ALLOCATE:
            switch (Fs_QueueAllocEntryData(entry))
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
            switch (Fs_QueueCanRead(entry))
            {
                // Can't read yet, memory in use by another operation. Wait until next tick.
                case 0:
                    break;

                case 1:
                    g_FsQueue.state = FSQS_READ_SETLOC;
                    break;
            }

            break;

        case FSQS_READ_SETLOC:
            switch (Fs_QueueTickSetLoc(entry))
            {
                // `CdlSetloc` failed, reset CD.
                case 0:
                    g_FsQueue.state = FSQS_READ_RESET;
                    break;

                case 1:
                    g_FsQueue.state = FSQS_READ_READ;
                    break;
            }

            break;

        case FSQS_READ_READ:
            switch (Fs_QueueTickRead(entry))
            {
                // `CdRead` failed, reset CD and retry.
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
                // `CdReadSync` failed, reset CD.
                case NO_VALUE:
                    g_FsQueue.state = FSQS_READ_RESET;
                    break;

                // Done reading and no state transition, let caller know that it's done.
                case 0:
                    result = true;
                    break;
            }

            break;

        case FSQS_READ_RESET:
            switch (Fs_QueueResetTick(entry))
            {
                // Still resetting.
                case 0:
                    break;

                // Reset done, retry from `setloc`.
                case 1:
                    g_FsQueue.state = FSQS_READ_SETLOC;
                    break;
            }

            break;
    }

    return result;
}

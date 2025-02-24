#include "main/fsqueue.h"
#include "main/fsmem.h"
#include "bodyprog/bodyprog.h"

#include <memory.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>

/** The FS queue. See `s_FsQueue`. */
s_FsQueue g_FsQueue;

/** Check if queue entry index has been loaded and post-loaded.
 * 
 * @param queueIdx The index of the queue entry to check.
 * @return 1 if the entry has been fully processed, 0 otherwise.
 */
s32 Fs_IsQueueEntryLoaded(s32 queueIdx)
{
    return queueIdx < g_FsQueue.postLoad.idx;
}

/** Get number of operations currently in the queue.
 * @return Number of operations in the queue. Includes both pending reads and pending post-loads.
 */
s32 Fs_GetQueueLength(void)
{
    return (g_FsQueue.last.idx + 1) - g_FsQueue.postLoad.idx;
}

/** Unknown. If queue is empty, call `func_8003c850`.
 * @return 1 when queue is empty and the call suceeds, 0 otherwise.
 */
s32 Fs_DoQueueThingWhenEmpty(void)
{
    s32 result;

    D_800C489C = 1;

    result = false;

    if (Fs_GetQueueLength() == 0)
    {
        result = func_8003c850() != 0;
    }

    return result;
}

/** Spin-waits for the queue to become empty while calling `Fs_UpdateQueue`.
 * Calls some bodyprog functions before and after the wait, `VSync` in the wait and `DrawSync` after the wait.
 */
void Fs_WaitForEmptyQueue(void)
{
    func_800892A4(0);
    func_80089128();

    while (true)
    {
        VSync(0);
        if (Fs_GetQueueLength() <= 0)
        {
            break;
        }

        Fs_UpdateQueue();
    }

    func_800892A4(1);
    DrawSync(0);
    VSync(0);
}

/** Add a new seek operation to the queue.
 * @param fileIdx File table index of the file to seek to.
 * @return Index of the new queue entry.
 */
s32 Fs_StartQueueSeek(s32 fileIdx)
{
    return Fs_EnqueueQueue(fileIdx, FS_OP_SEEK, FS_POST_LOAD_NONE, false, NULL, 0, NULL);
}

/** Add a new read operation to the queue.
 * 
 * @param fileIdx File table index of the file to read.
 * @param dest Destination buffer. Seems there are no size checks.
 * @return Index of the new queue entry.
 */
s32 Fs_StartQueueRead(s32 fileIdx, void* dest)
{
    return Fs_EnqueueQueue(fileIdx, FS_OP_READ, FS_POST_LOAD_NONE, false, dest, 0, NULL);
}

/** @brief Add a new TIM read operation to the queue.
 * Adds a read operation with `postload = FS_POST_LOAD_TIM`.
 * 
 * @param fileIdx File table index of the file to read.
 * @param dest Destination buffer. Seems there are no size checks.
 * @param image Where to upload the TIM in VRAM.
 * @return Index of the new queue entry.
 */
s32 Fs_StartQueueReadTim(s32 fileIdx, void* dest, s_FsImageDesc* image)
{
    s_FsQueueExtra extra;

    if (image != NULL)
    {
        extra.image = *image;
    }
    else
    {
        // u == 0xFF (-1) is a special case for "image descriptor not set".
        extra.image.u = 0xFF;
        extra.image.clutX = -1;
        extra.image.v = 0xFF;
        extra.image.clutY = -1;
    }

    return Fs_EnqueueQueue(fileIdx, FS_OP_READ, FS_POST_LOAD_TIM, false, dest, 0, &extra);
}

/** @brief Add a new ANM read operation to the queue.
 * Adds a read operation with `postLoad = FS_POST_LOAD_ANM`.
 * 
 * @note Does not actually take a file number, but instead takes one from an array of structs at 0x800a90fc in bodyprog,
 * using `arg1` as an index. Does not seem to take a `s_FsAnmDesc` pointer either. Maybe by value?
 * 
 * @param arg0
 * @param arg1 Index of something in an array in bodyprog.
 * @param arg2 Destination buffer?
 * @param arg3
 * @return Index of the new queue entry.
 */
s32 Fs_StartQueueReadAnm(s32 arg0, s32 arg1, void* arg2, s32 arg3)
{
    s32 fileIdx;
    s_FsQueueExtra extra;

    fileIdx = D_800A90FC[arg1].fileIdx;
    extra.anm.field04 = arg1;
    extra.anm.field00 = arg0;
    extra.anm.field08 = arg3;
    return Fs_EnqueueQueue(fileIdx, FS_OP_READ, FS_POST_LOAD_ANM, false, arg2, 0, &extra);
}

/** @brief Add new operation to the queue.
 *
 * If the queue is full, will spin while calling `Fs_UpdateQueue` and wait until space frees up.
 * Called by all of the `Fs_QueueStart...` functions.
 *
 * @param fileIdx File table index of the file to load/seek.
 * @param op Operation type (`FsQueueOperation`).
 * @param postLoad Postload type (`FsQueuePostLoadType`).
 * @param alloc Whether to allocate owned memory for this operation (`s_FsQueueEntry::allocate`).
 * @param unused1 Value for `s_FsQueueEntry::unused1`. Seems to be unused.
 * @param extra Extra data for operation (`s_FsQueueEntry::extra`).
 * @return Index of the new queue entry.
 */
s32 Fs_EnqueueQueue(s32 fileIdx, u8 op, u8 postLoad, u8 alloc, void* data, u32 unused0, s_FsQueueExtra* extra)
{
    s_FsQueueEntry* newEntry;
    s_FsQueuePtr* lastPtr;

    // Wait for space in queue.
    while (Fs_GetQueueLength() >= FS_QUEUE_LENGTH)
        Fs_UpdateQueue();

    // This is the reason these pointers and indices are wrapped into structs.
    // If left as they are in the queue struct, this doesn't match unless manually addressed.
    lastPtr = &g_FsQueue.last;
    lastPtr->idx++;
    lastPtr->ptr = &g_FsQueue.entries[lastPtr->idx & (FS_QUEUE_LENGTH - 1)];

    newEntry = g_FsQueue.last.ptr;
    newEntry->info = &g_FileTable[fileIdx];
    newEntry->operation = op;
    newEntry->postLoad = postLoad;
    newEntry->allocate = alloc;
    newEntry->externalData = data;
    newEntry->unused1 = unused0;

    if (extra != NULL)
    {
        newEntry->extra = *extra;
    }

    return g_FsQueue.last.idx;
}

/** @brief Initialize FS queue and FS memory.
 * Initializes `g_FsQueue` and calls `Fs_InitializeMem`.
 */
void Fs_InitializeQueue(void)
{
    bzero(&g_FsQueue, sizeof(g_FsQueue));
    g_FsQueue.last.idx = -1;
    g_FsQueue.last.ptr = &g_FsQueue.entries[FS_QUEUE_LENGTH - 1];
    g_FsQueue.read.idx = 0;
    g_FsQueue.read.ptr = g_FsQueue.entries;
    g_FsQueue.postLoad.idx = 0;
    g_FsQueue.postLoad.ptr = g_FsQueue.entries;
    g_FsQueue.state = 0;
    g_FsQueue.postLoadState = 0;
    g_FsQueue.resetTimer0 = 0;
    g_FsQueue.resetTimer1 = 0;
    Fs_InitializeMem(FS_MEM_BASE, FS_MEM_SIZE);
}

/** Seems to clear the queue. */
void Fs_ResetQueue(void)
{
    if (Fs_GetQueueLength() <= 0)
    {
        return;
    }

    if (g_FsQueue.read.idx <= g_FsQueue.last.idx)
    {
        g_FsQueue.read.idx = g_FsQueue.read.idx + FS_QUEUE_LENGTH;
        g_FsQueue.read.ptr = g_FsQueue.entries + (g_FsQueue.read.idx & (FS_QUEUE_LENGTH - 1));
        g_FsQueue.last = g_FsQueue.read;
    }

    g_FsQueue.postLoad = g_FsQueue.read;
    g_FsQueue.postLoadState = 0;
    g_FsQueue.read.ptr->postLoad = 0;
}

/** @brief Ticks the FS queue once.
 *
 * Depending on current read entry's operation type, either ticks reading it (`Fs_UpdateQueueRead`) or seeking it (`Fs_UpdateQueueSeek`).
 * If they return 1, advances `g_FsQueue.read.idx` and `g_FsQueue.read.ptr`.
 *
 * Regardless of the outcome of the above, also ticks postloading (`Fs_UpdateQueuePostLoad`) if there is an entry to postload.
 * If that reports that the current postload entry is done postloading, advances `g_FsQueue.postLoad.idx` and `g_FsQueue.postLoad.ptr`.
 */
void Fs_UpdateQueue(void)
{
    s_FsQueuePtr* read;
    s_FsQueueEntry* tick;
    s32 temp = 0;

    // Pending read/seek operations; tick them.
    tick = g_FsQueue.read.ptr;
    if (g_FsQueue.read.idx <= g_FsQueue.last.idx)
    {
        switch (tick->operation)
        {
            case FS_OP_SEEK:
                temp = Fs_UpdateQueueSeek(tick);
                break;

            case FS_OP_READ:
                temp = Fs_UpdateQueueRead(tick);
                break;
        }

        // Seek or read done; proceed to next one.
        // Alias and tmp use seem to be required for match for some reason, might be an inline?
        if (temp == 1)
        {
            read = &g_FsQueue.read;
            g_FsQueue.state = 0; // FSQS_READ_ALLOCATE or FSQS_SEEK_SETLOC
            g_FsQueue.resetTimer0 = 0;
            g_FsQueue.resetTimer1 = 0;
            temp = ++read->idx;
            read->ptr = g_FsQueue.entries + (temp & (FS_QUEUE_LENGTH - 1));
        }
    }
    // Nothing to read.
    else
    {
        g_FsQueue.state = 0; // FSQS_READ_ALLOCATE or FSQS_SEEK_SETLOC
    }

    // Preparations to post-load in queue; tick them.
    tick = g_FsQueue.postLoad.ptr;
    if (g_FsQueue.postLoad.idx < g_FsQueue.read.idx)
    {
        temp = Fs_UpdateQueuePostLoad(tick);
        if (temp == 1)
        {
            g_FsQueue.postLoadState = FSQS_POST_LOAD_INIT;
            temp = ++g_FsQueue.postLoad.idx;
            g_FsQueue.postLoad.ptr = g_FsQueue.entries + (temp & (FS_QUEUE_LENGTH - 1));
        }
    }
    // Nothing to post-load.
    else
    {
        g_FsQueue.postLoadState = FSQS_POST_LOAD_INIT;
    }
}

/** @brief Ticks a seek operation once.
 *
 * Performs one step in the seeking process according to `g_FsQueue.state`. When the whole process is done, returns 1.
 *
 * @param entry Entry to tick.
 * @return 1 when `entry` is done seeking, 0 otherwise.
 */
s32 Fs_UpdateQueueSeek(s_FsQueueEntry* entry)
{
    s32 result = false;
    s32 state = g_FsQueue.state;

    switch (state)
    {
        case FSQS_SEEK_SET_LOC:
        switch (Fs_TickQueueSetLoc(entry))
        {
            // CdlSetloc failed; reset and retry.
            case 0:
                g_FsQueue.state = FSQS_SEEK_RESET;
                break;

            case 1:
                g_FsQueue.state = FSQS_SEEK_SEEKL;
                break;
        }
        break;

        case FSQS_SEEK_SEEKL:
        switch (CdControl(CdlSeekL, NULL, NULL))
        {
            // CdlSeekL failed; reset and retry.
            case 0:
                g_FsQueue.state = FSQS_SEEK_RESET;
                break;

            case 1:
                g_FsQueue.state = FSQS_SEEK_SYNC;
                break;
        }
        break;

        case FSQS_SEEK_SYNC:
        switch (CdSync(1, NULL))
        {
            // Keep waiting; operation in progress.
            case CdlNoIntr:
                break;

            // Done seeking.
            case CdlComplete:
                result = true;
                break;

            // Disk error; reset and retry.
            case CdlDiskError:
                g_FsQueue.state = FSQS_SEEK_RESET;
                break;

            // Inknown error; reset and retry.
            default:
                g_FsQueue.state = FSQS_SEEK_RESET;
                break;
        }
        break;

        case FSQS_SEEK_RESET:
        switch (Fs_ResetQueueTick(entry))
        {
            // Still resetting.
            case 0:
                break;

            // Reset done; retry from beginning.
            case 1:
                g_FsQueue.state = FSQS_SEEK_SET_LOC;
                break;
        }

        break;
    }

    return result;
}

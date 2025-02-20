#include "main/fsqueue.h"
#include "main/fsmem.h"
#include "bodyprog/bodyprog.h"

#include <MEMORY.H>
#include <LIBETC.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBCD.H>

FsQueue g_FsQueue;

s32 Fs_IsQueueEntryLoaded_80010e58(s32 arg0)
{
    return arg0 < g_FsQueue.postLoad.idx;
}

s32 Fs_GetQueueLength_80010E68(void)
{
    return (g_FsQueue.last.idx + 1) - g_FsQueue.postLoad.idx;
}

s32 Fs_DoQueueThingWhenEmpty_80010e84(void)
{
    s32 result;

    D_800C489C = 1;

    result = false;

    if (Fs_GetQueueLength_80010E68() == 0)
        result = func_8003c850() != 0;

    return result;
}

void Fs_WaitForEmptyQueue_80010ecc(void)
{
    func_800892A4(0);
    func_80089128();

    while (true)
    {
        VSync(0);
        if (Fs_GetQueueLength_80010E68() <= 0)
            break;

        Fs_UpdateQueue_80011260();
    }

    func_800892A4(1);
    DrawSync(0);
    VSync(0);
}

s32 Fs_StartQueueSeek_80010f34(s32 fileIdx)
{
    return Fs_QueueEnqueue_80011074(fileIdx, FS_OP_SEEK, FS_POST_LOAD_NONE, false, NULL, 0, NULL);
}

s32 Fs_StartQueueRead_80010F68(s32 fileIdx, void* dest)
{
    return Fs_QueueEnqueue_80011074(fileIdx, FS_OP_READ, FS_POST_LOAD_NONE, false, dest, 0, NULL);
}

s32 Fs_StartQueueReadTim_80010F9C(s32 fileIdx, void* dest, FsImageDesc* image)
{
    FsQueueExtra extra;

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

    return Fs_QueueEnqueue_80011074(fileIdx, FS_OP_READ, FS_POST_LOAD_TIM, false, dest, 0, &extra);
}

s32 Fs_StartQueueReadAnm_80011018(s32 arg0, s32 arg1, void* arg2, s32 arg3)
{
    s32          fileIdx;
    FsQueueExtra extra;

    fileIdx = D_800A90FC[arg1].fileno;
    extra.anm.field04 = arg1;
    extra.anm.field00 = arg0;
    extra.anm.field08 = arg3;
    return Fs_QueueEnqueue_80011074(fileIdx, FS_OP_READ, FS_POST_LOAD_ANM, false, arg2, 0, &extra);
}

s32 Fs_QueueEnqueue_80011074(s32 fileIdx, u8 op, u8 postLoad, u8 alloc, void* data, u32 unused0, FsQueueExtra* extra)
    {
    FsQueueEntry* newEntry;
    FsQueuePtr*   lastp;

    // Wait for space in queue.
    while (Fs_GetQueueLength_80010E68() >= FS_QUEUE_LEN)
        Fs_UpdateQueue_80011260();

    // This is the reason these pointers and indices are wrapped into structs.
    // If left as they are in the queue struct, this doesn't match unless manually addressed.
    lastp = &g_FsQueue.last;
    lastp->idx++;
    lastp->ptr = &g_FsQueue.entries[lastp->idx & (FS_QUEUE_LEN - 1)];

    newEntry = g_FsQueue.last.ptr;
    newEntry->info = &g_FileTable[fileIdx];
    newEntry->operation = op;
    newEntry->postLoad = postLoad;
    newEntry->allocate = alloc;
    newEntry->externalData = data;
    newEntry->unused1 = unused0;

    if (extra != NULL)
        newEntry->extra = *extra;

    return g_FsQueue.last.idx;
}

void Fs_InitializeQueue_80011170(void)
{
    bzero(&g_FsQueue, sizeof(g_FsQueue));
    g_FsQueue.last.idx = -1;
    g_FsQueue.last.ptr = &g_FsQueue.entries[FS_QUEUE_LEN - 1];
    g_FsQueue.read.idx = 0;
    g_FsQueue.read.ptr = g_FsQueue.entries;
    g_FsQueue.postLoad.idx = 0;
    g_FsQueue.postLoad.ptr = g_FsQueue.entries;
    g_FsQueue.state = 0;
    g_FsQueue.postLoadState = 0;
    g_FsQueue.resetTimer0 = 0;
    g_FsQueue.resetTimer1 = 0;
    Fs_InitializeMem_80011C70(FS_MEM_BASE, FS_MEM_SIZE);
}

void Fs_ResetQueue_800111dc(void)
{
    if (Fs_GetQueueLength_80010E68() <= 0)
        return;

    if (g_FsQueue.read.idx <= g_FsQueue.last.idx)
    {
        g_FsQueue.read.idx = g_FsQueue.read.idx + FS_QUEUE_LEN;
        g_FsQueue.read.ptr = g_FsQueue.entries + (g_FsQueue.read.idx & (FS_QUEUE_LEN - 1));
        g_FsQueue.last = g_FsQueue.read;
    }

    g_FsQueue.postLoad = g_FsQueue.read;
    g_FsQueue.postLoadState = 0;
    g_FsQueue.read.ptr->postLoad = 0;
}

void Fs_UpdateQueue_80011260(void)
{
    FsQueuePtr* read;
    FsQueueEntry* tick;
    s32 tmp = 0;

    // Pending read/seek operations; tick them.
    tick = g_FsQueue.read.ptr;
    if (g_FsQueue.read.idx <= g_FsQueue.last.idx)
    {
        switch (tick->operation)
        {
        case FS_OP_SEEK:
            tmp = Fs_UpdateQueueSeek_8001137C(tick);
            break;

        case FS_OP_READ:
            tmp = Fs_UpdateQueueRead_800114C4(tick);
            break;
        }

        // Seek or read done; proceed to next one.
        // Alias and tmp use seem to be required for match for some reason, might be an inline?
        if (tmp == 1)
        {
            read = &g_FsQueue.read;
            g_FsQueue.state = 0; // FSQS_READ_ALLOCATE or FSQS_SEEK_SETLOC
            g_FsQueue.resetTimer0 = 0;
            g_FsQueue.resetTimer1 = 0;
            tmp = ++read->idx;
            read->ptr = g_FsQueue.entries + (tmp & (FS_QUEUE_LEN - 1));
        }
    }
    // Nothing to read.
    else
    {
        g_FsQueue.state = 0; // FSQS_READ_ALLOCATE or FSQS_SEEK_SETLOC
    }

    // Pperations to post-load in queue; tick them.
    tick = g_FsQueue.postLoad.ptr;
    if (g_FsQueue.postLoad.idx < g_FsQueue.read.idx)
    {
        tmp = Fs_UpdateQueue_80011260postLoad(tick);
        if (tmp == 1)
        {
            g_FsQueue.postLoadState = FSQS_POST_LOAD_INIT;
            tmp = ++g_FsQueue.postLoad.idx;
            g_FsQueue.postLoad.ptr = g_FsQueue.entries + (tmp & (FS_QUEUE_LEN - 1));
        }
    }
    // Nothing to post-load.
    else
    {
        g_FsQueue.postLoadState = FSQS_POST_LOAD_INIT;
    }
}

s32 Fs_UpdateQueueSeek_8001137C(FsQueueEntry* entry)
{
    s32 result = false;
    s32 state = g_FsQueue.state;

    switch (state)
    {
        case FSQS_SEEK_SET_LOC:
        switch (Fs_TickQueueSetLoc_800117E8(entry))
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
        switch (Fs_ResetQueueTick_80011884(entry))
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

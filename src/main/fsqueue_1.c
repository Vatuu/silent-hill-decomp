#include "main/fsqueue.h"
#include "main/fsmem.h"
#include "bodyprog/bodyprog.h"

#include <memory.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>

s_FsQueue g_FsQueue;

s32 Fs_QueueIsEntryLoaded(s32 queueIdx)
{
    return queueIdx < g_FsQueue.postLoad.idx;
}

s32 Fs_QueueGetLength(void)
{
    return (g_FsQueue.last.idx + 1) - g_FsQueue.postLoad.idx;
}

s32 Fs_QueueDoThingWhenEmpty(void)
{
    s32 result;

    D_800C489C = 1;

    result = false;

    if (Fs_QueueGetLength() == 0)
    {
        result = func_8003c850() != 0;
    }

    return result;
}

void Fs_QueueWaitForEmpty(void)
{
    func_800892A4(0);
    func_80089128();

    while (true)
    {
        VSync(0);
        if (Fs_QueueGetLength() <= 0)
        {
            break;
        }

        Fs_QueueUpdate();
    }

    func_800892A4(1);
    DrawSync(0);
    VSync(0);
}

s32 Fs_QueueStartSeek(s32 fileIdx)
{
    return Fs_QueueEnqueue(fileIdx, FS_OP_SEEK, FS_POST_LOAD_NONE, false, NULL, 0, NULL);
}

s32 Fs_QueueStartRead(s32 fileIdx, void* dest)
{
    return Fs_QueueEnqueue(fileIdx, FS_OP_READ, FS_POST_LOAD_NONE, false, dest, 0, NULL);
}

s32 Fs_QueueStartReadTim(s32 fileIdx, void* dest, s_FsImageDesc* image)
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

    return Fs_QueueEnqueue(fileIdx, FS_OP_READ, FS_POST_LOAD_TIM, false, dest, 0, &extra);
}

s32 Fs_QueueStartReadAnm(s32 arg0, s32 arg1, void* arg2, s32 arg3)
{
    s32 fileIdx;
    s_FsQueueExtra extra;

    fileIdx = D_800A90FC[arg1].fileIdx;
    extra.anm.field_4 = arg1;
    extra.anm.field_0 = arg0;
    extra.anm.field_8 = arg3;
    return Fs_QueueEnqueue(fileIdx, FS_OP_READ, FS_POST_LOAD_ANM, false, arg2, 0, &extra);
}

s32 Fs_QueueEnqueue(s32 fileIdx, u8 op, u8 postLoad, u8 alloc, void* data, u32 unused0, s_FsQueueExtra* extra)
{
    s_FsQueueEntry* newEntry;
    s_FsQueuePtr* lastPtr;

    // Wait for space in queue.
    while (Fs_QueueGetLength() >= FS_QUEUE_LENGTH)
        Fs_QueueUpdate();

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

void Fs_QueueInitialize(void)
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

void Fs_QueueReset(void)
{
    if (Fs_QueueGetLength() <= 0)
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

void Fs_QueueUpdate(void)
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
                temp = Fs_QueueUpdateSeek(tick);
                break;

            case FS_OP_READ:
                temp = Fs_QueueUpdateRead(tick);
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
        temp = Fs_QueueUpdatePostLoad(tick);
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

s32 Fs_QueueUpdateSeek(s_FsQueueEntry* entry)
{
    s32 result = false;
    s32 state = g_FsQueue.state;

    switch (state)
    {
        case FSQS_SEEK_SET_LOC:
        switch (Fs_QueueTickSetLoc(entry))
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
        switch (Fs_QueueResetTick(entry))
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

#include "gpu.h"
#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "main/fsqueue.h"
#include "main/fsmem.h"

#include <memory.h>
#include <psyq/libetc.h>
#include <psyq/libcd.h>

s_FsQueue g_FsQueue;

bool Fs_QueueIsEntryLoaded(s32 queueIdx)
{
    return queueIdx < g_FsQueue.postLoad.idx;
}

s32 Fs_QueueGetLength(void)
{
    return (g_FsQueue.last.idx + 1) - g_FsQueue.postLoad.idx;
}

bool Fs_QueueDoThingWhenEmpty(void)
{
    bool result;

    D_800C489C = true;

    result = false;

    if (Fs_QueueGetLength() == 0)
    {
        result = Ipd_ChunkInitCheck() != 0;
    }

    return result;
}

void Fs_QueueWaitForEmpty(void)
{
    func_800892A4(0);
    func_80089128();

    while (true)
    {
        VSync(SyncMode_Wait);
        if (Fs_QueueGetLength() <= 0)
        {
            break;
        }

        Fs_QueueUpdate();
    }

    func_800892A4(1);
    DrawSync(SyncMode_Wait);
    VSync(SyncMode_Wait);
}

s32 Fs_QueueStartSeek(e_FsFile fileIdx)
{
    return Fs_QueueEnqueue(fileIdx, FsQueueOp_Seek, FsQueuePostLoadType_None, false, NULL, 0, NULL);
}

s32 Fs_QueueStartRead(e_FsFile fileIdx, void* dest)
{
    return Fs_QueueEnqueue(fileIdx, FsQueueOp_Read, FsQueuePostLoadType_None, false, dest, 0, NULL);
}

s32 Fs_QueueStartReadTim(e_FsFile fileIdx, void* dest, const s_FsImageDesc* image)
{
    s_FsQueueExtra extra;

    if (image != NULL)
    {
        extra.image = *image;
    }
    else
    {
        extra.image.u     = NO_VALUE;
        extra.image.clutX = NO_VALUE;
        extra.image.v     = NO_VALUE;
        extra.image.clutY = NO_VALUE;
    }

    return Fs_QueueEnqueue(fileIdx, FsQueueOp_Read, FsQueuePostLoadType_Tim, false, dest, 0, &extra);
}

s32 Fs_QueueStartReadAnm(s32 idx, s32 charaId, void* dest, GsCOORDINATE2* coords)
{
    s32            fileIdx;
    s_FsQueueExtra extra;

    fileIdx             = CHARA_FILE_INFOS[charaId].animFileIdx;
    extra.anm.charaId_4 = charaId;
    extra.anm.field_0   = idx;
    extra.anm.coords_8  = coords;
    return Fs_QueueEnqueue(fileIdx, FsQueueOp_Read, FsQueuePostLoadType_Anm, false, dest, 0, &extra);
}

s32 Fs_QueueEnqueue(e_FsFile fileIdx, u8 op, u8 postLoad, u8 alloc, void* data, u32 unused0, s_FsQueueExtra* extra)
{
    s_FsQueueEntry* newEntry;
    s_FsQueuePtr*   lastPtr;

    // Wait for space in queue.
    while (Fs_QueueGetLength() >= FS_QUEUE_LENGTH)
    {
        Fs_QueueUpdate();
    }

    // This is the reason these pointers and indices are wrapped into structs.
    // If left as they are in the queue struct, this doesn't match unless manually addressed.
    lastPtr = &g_FsQueue.last;
    lastPtr->idx++;
    lastPtr->ptr = &g_FsQueue.entries[lastPtr->idx & (FS_QUEUE_LENGTH - 1)];

    newEntry               = g_FsQueue.last.ptr;
    newEntry->info         = &g_FileTable[fileIdx];
    newEntry->operation    = op;
    newEntry->postLoad     = postLoad;
    newEntry->allocate     = alloc;
    newEntry->externalData = data;
    newEntry->unused1      = unused0;

    if (extra != NULL)
    {
        newEntry->extra = *extra;
    }

    return g_FsQueue.last.idx;
}

void Fs_QueueInitialize(void)
{
    bzero(&g_FsQueue, sizeof(g_FsQueue));
    g_FsQueue.last.idx      = NO_VALUE;
    g_FsQueue.last.ptr      = &g_FsQueue.entries[FS_QUEUE_LENGTH - 1];
    g_FsQueue.read.idx      = 0;
    g_FsQueue.read.ptr      = g_FsQueue.entries;
    g_FsQueue.postLoad.idx  = 0;
    g_FsQueue.postLoad.ptr  = g_FsQueue.entries;
    g_FsQueue.state         = 0;
    g_FsQueue.postLoadState = 0;
    g_FsQueue.resetTimer0   = 0;
    g_FsQueue.resetTimer1   = 0;
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
        g_FsQueue.last     = g_FsQueue.read;
    }

    g_FsQueue.postLoad           = g_FsQueue.read;
    g_FsQueue.postLoadState      = 0;
    g_FsQueue.read.ptr->postLoad = 0;
}

void Fs_QueueUpdate(void)
{
    s_FsQueuePtr*   read;
    s_FsQueueEntry* tick;
    s32             temp = 0;

    // Pending read/seek operations; tick them.
    tick = g_FsQueue.read.ptr;
    if (g_FsQueue.read.idx <= g_FsQueue.last.idx)
    {
        switch (tick->operation)
        {
            case FsQueueOp_Seek:
                temp = Fs_QueueUpdateSeek(tick);
                break;

            case FsQueueOp_Read:
                temp = Fs_QueueUpdateRead(tick);
                break;
        }

        // Seek or read done, proceed to next one.
        // Alias and `temp` use seem to be required for match for some reason, might be an inline?
        if (temp == 1)
        {
            read                  = &g_FsQueue.read;
            g_FsQueue.state       = 0; // `FsQueueReadState_Allocate` or `FSQS_SEEK_SETLOC`.
            g_FsQueue.resetTimer0 = 0;
            g_FsQueue.resetTimer1 = 0;
            temp                  = ++read->idx;
            read->ptr             = g_FsQueue.entries + (temp & (FS_QUEUE_LENGTH - 1));
        }
    }
    // Nothing to read.
    else
    {
        g_FsQueue.state = 0; // `FsQueueReadState_Allocate` or `FSQS_SEEK_SETLOC`.
    }

    // Preparations to post-load in queue; tick them.
    tick = g_FsQueue.postLoad.ptr;
    if (g_FsQueue.postLoad.idx < g_FsQueue.read.idx)
    {
        temp = Fs_QueueUpdatePostLoad(tick);
        if (temp == true)
        {
            g_FsQueue.postLoadState = FsQueuePostLoadState_Init;
            temp                    = ++g_FsQueue.postLoad.idx;
            g_FsQueue.postLoad.ptr  = g_FsQueue.entries + (temp & (FS_QUEUE_LENGTH - 1));
        }
    }
    // Nothing to post-load.
    else
    {
        g_FsQueue.postLoadState = FsQueuePostLoadState_Init;
    }
}

bool Fs_QueueUpdateSeek(s_FsQueueEntry* entry)
{
    bool result = false;
    s32  state  = g_FsQueue.state;

    switch (state)
    {
        case FsQueueSeekState_SetLoc:
            switch (Fs_QueueTickSetLoc(entry))
            {
                // CdlSetloc failed, reset and retry.
                case false:
                    g_FsQueue.state = FsQueueSeekState_Reset;
                    break;

                case true:
                    g_FsQueue.state = FsQueueSeekState_SeekL;
                    break;
            }
            break;

        case FsQueueSeekState_SeekL:
            switch (CdControl(CdlSeekL, NULL, NULL))
            {
                // `CdlSeekL` failed, reset and retry.
                case 0:
                    g_FsQueue.state = FsQueueSeekState_Reset;
                    break;

                case 1:
                    g_FsQueue.state = FsQueueSeekState_Sync;
                    break;
            }
            break;

        case FsQueueSeekState_Sync:
            switch (CdSync(1, NULL))
            {
                // Keep waiting, operation in progress.
                case CdlNoIntr:
                    break;

                // Done seeking.
                case CdlComplete:
                    result = true;
                    break;

                // Disk error; reset and retry.
                case CdlDiskError:
                    g_FsQueue.state = FsQueueSeekState_Reset;
                    break;

                // Inknown error, reset and retry.
                default:
                    g_FsQueue.state = FsQueueSeekState_Reset;
                    break;
            }
            break;

        case FsQueueSeekState_Reset:
            switch (Fs_QueueResetTick(entry))
            {
                // Still resetting.
                case 0:
                    break;

                // Reset done, retry from beginning.
                case 1:
                    g_FsQueue.state = FsQueueSeekState_SetLoc;
                    break;
            }
            break;
    }

    return result;
}

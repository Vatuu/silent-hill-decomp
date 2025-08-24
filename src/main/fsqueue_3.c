
#include "main/fsqueue.h"
#include "main/fsmem.h"
#include "bodyprog/bodyprog.h"

#include <libapi.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include <string.h>

bool Fs_QueueAllocEntryData(s_FsQueueEntry* entry)
{
    bool result = false;

    if (entry->allocate)
    {
        entry->data = Fs_AllocMem(ALIGN(entry->info->blockCount_0_13 * FS_BLOCK_SIZE, FS_SECTOR_SIZE));
    }
    else
    {
        entry->data = entry->externalData;
    }

    if (entry->data != 0)
    {
        result = true;
    }

    return result;
}

bool Fs_QueueCanRead(s_FsQueueEntry* entry)
{
    s_FsQueueEntry* other;
    s32             queueLength;
    s32             overlap;
    s32             i;

    queueLength = g_FsQueue.read.idx - g_FsQueue.postLoad.idx;

    for (i = 0; i < queueLength; i++)
    {
        other   = &g_FsQueue.entries[(g_FsQueue.postLoad.idx + i) & (FS_QUEUE_LENGTH - 1)];
        overlap = false;
        if (other->postLoad || other->allocate)
        {
            overlap = Fs_QueueDoBuffersOverlap(entry->data,
                                               ALIGN(entry->info->blockCount_0_13 * FS_BLOCK_SIZE, FS_SECTOR_SIZE),
                                               other->data,
                                               other->info->blockCount_0_13 * FS_BLOCK_SIZE);
        }

        if (overlap == true)
        {
            return false;
        }
    }

    return true;
}

bool Fs_QueueDoBuffersOverlap(u8* data0, u32 size0, u8* data1, u32 size1)
{
    u32 data0Low = (u32)data0 & 0xFFFFFF;
    u32 data1Low = (u32)data1 & 0xFFFFFF;
    if ((data1Low >= data0Low + size0) || (data0Low >= data1Low + size1))
    {
        return false;
    }

    return true;
}

bool Fs_QueueTickSetLoc(s_FsQueueEntry* entry)
{
    CdlLOC cdloc;
    CdIntToPos(entry->info->startSector_0_0, &cdloc);
    return CdControl(CdlSetloc, (u_char*)&cdloc, NULL);
}

bool Fs_QueueTickRead(s_FsQueueEntry* entry)
{
    // Round up to sector boundary. Masking not needed because of `>> 11` below.
    s32 sectorCount = ((entry->info->blockCount_0_13 * FS_BLOCK_SIZE) + FS_SECTOR_SIZE) - 1;
    
    // Overflow check?
    if (sectorCount < 0)
    {
        sectorCount += FS_SECTOR_SIZE - 1;
    }

    return CdRead(sectorCount >> FS_SECTOR_SHIFT, (u32*)entry->data, CdlModeSpeed);
}

bool Fs_QueueResetTick(s_FsQueueEntry* entry)
{
    bool result = false;

    g_FsQueue.resetTimer0++;

    if (g_FsQueue.resetTimer0 >= 8)
    {
        result                = true;
        g_FsQueue.resetTimer0 = 0;
        g_FsQueue.resetTimer1++;
        
        if (g_FsQueue.resetTimer1 >= 9)
        {
            if (CdReset(0) == 1)
            {
                g_FsQueue.resetTimer1 = 0;
            }
            else
            {
                result = false;
            }
        }
    }

    return result;
}

bool Fs_QueueTickReadPcDvr(s_FsQueueEntry* entry)
{
    s32         handle;
    s32         temp;
    s32         retry;
    bool        result;
    s_FileInfo* file = entry->info;
    char        pathBuf[64];
    char        nameBuf[32];

    result = false;

    strcpy(pathBuf, "sim:.\\DATA");
    strcat(pathBuf, g_FilePaths[file->pathIdx_4_0]);
    Fs_GetFileInfoName(nameBuf, file);
    strcat(pathBuf, nameBuf);

    for (retry = 0; retry <= 2; retry++)
    {
        handle = open(pathBuf, 0x4001);
        if (handle == NO_VALUE)
        {
            continue;
        }

        temp = read(handle,entry->data, ALIGN(file->blockCount_0_13 * FS_BLOCK_SIZE, FS_SECTOR_SIZE));
        if (temp == NO_VALUE)
        {
            continue;
        }

        do
        {
            temp = close(handle);
        }
        while (temp == NO_VALUE);

        result = true;
        break;
    }

    return result;
}

bool Fs_QueueUpdatePostLoad(s_FsQueueEntry* entry)
{
    bool result;
    s32  state;
    u8   postLoad;

    result = false;
    state  = g_FsQueue.postLoadState;

    switch (state)
    {
        case FSQS_POST_LOAD_INIT:
            if (entry->allocate)
            {
                g_FsQueue.postLoadState = FSQS_POST_LOAD_SKIP;
            }
            else
            {
                g_FsQueue.postLoadState = FSQS_POST_LOAD_EXEC;
            }
            break;

        // Do nothing.
        case FSQS_POST_LOAD_SKIP:
            break;

        case FSQS_POST_LOAD_EXEC:
            postLoad = entry->postLoad;

            switch (postLoad)
            {
                case FS_POST_LOAD_NONE:
                    result = true;
                    break;

                case FS_POST_LOAD_TIM:
                    result = Fs_QueuePostLoadTim(entry);
                    break;

                case FS_POST_LOAD_ANM:
                    result = Fs_QueuePostLoadAnm(entry);
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    return result;
}

bool Fs_QueuePostLoadTim(s_FsQueueEntry* entry)
{
    TIM_IMAGE tim;
    RECT      tempRect;

    OpenTIM((u64*)entry->externalData);
    ReadTIM(&tim);

    tempRect = *tim.prect;
    if (entry->extra.image.u != 0xFF)
    {
        // This contraption simply extracts XY from tPage value.
        // For some reason it seems to be byte swapped, or maybe tPage is stored as u8[2]?
        // Same as `tempRect.x = (entry->extra.image.tPage & 0x0F) * 64` for normal tPage.
        tempRect.x = entry->extra.image.u + ((entry->extra.image.tPage[1] & 0xF) << 6);

        // Same as `tempRect.y = (entry->extra.image.tPage & 0x10) * 16` for normal tPage.
        tempRect.y = entry->extra.image.v + ((entry->extra.image.tPage[1] << 4) & 0x100);
    }

    LoadImage(&tempRect, tim.paddr);

    if (tim.caddr != NULL)
    {
        tempRect = *tim.crect;
        if (entry->extra.image.clutX != NO_VALUE)
        {
            tempRect.x = entry->extra.image.clutX;
            tempRect.y = entry->extra.image.clutY;
        }

        LoadImage(&tempRect, tim.caddr);
    }

    return true;
}

bool Fs_QueuePostLoadAnm(s_FsQueueEntry* entry)
{
    func_80035560(entry->extra.anm.field_0, entry->extra.anm.charaId_4, entry->externalData, entry->extra.anm.coords_8);
    return true;
}

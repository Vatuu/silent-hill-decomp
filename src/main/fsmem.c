#include "main/fsmem.h"

FsMemState g_FsMemory;

void Fs_InitializeMem_80011C70(u8* start, u32 size)
{
    s32 i;

    // this really wants the start and size to be aligned to 8,
    // but since they're already hardcoded elsewhere, it doesn't really matter
    if ((u32)start & 3)
        size = 0;
    if (size & 3)
        size = 0;

    g_FsMemory.start = start;
    g_FsMemory.size = size;
    g_FsMemory.allocList.next = NULL;
    g_FsMemory.allocList.start = start;
    g_FsMemory.allocList.size = 0;
    g_FsMemory.freeList.next = g_FsMemory.blocks;
    g_FsMemory.freeList.start = NULL;
    g_FsMemory.freeList.size = 0;

    for (i = 0; i < FS_MEM_BLOCK_COUNT; i++)
    {
        g_FsMemory.blocks[i].start = NULL;
        g_FsMemory.blocks[i].size = 0;

        if (i == FS_MEM_BLOCK_COUNT - 1)
        {
            g_FsMemory.blocks[i].next = NULL;
        }
        else
        {
            g_FsMemory.blocks[i].next = &g_FsMemory.blocks[i + 1];
        }
    }
}

void nullsub_80011cfc(void)
{

}

void* Fs_AllocMem_80011D04(s32 size)
{
    FsMemBlock bufferMin; // Seems to use this struct for some reason.
    FsMemBlock* blockMin;
    FsMemBlock* iter;
    s32 clampedSize;
    u8* start;
    u8* end;

    if (size == 0)
        return NULL;

    // Align to 4.
    size = (size + 3) & ~3;

    // No free blocks left.
    if (g_FsMemory.freeList.next == NULL)
        return NULL;

    iter = &g_FsMemory.allocList;
    bufferMin.start = NULL;
    bufferMin.size = 0x0FFFFFFF;
    blockMin = NULL;

    for (; iter != NULL; iter = iter->next)
    {
        // Last allocation; check if there's space left after it.
        if (iter->next == NULL)
        {
            start = iter->start + iter->size;
            end = g_FsMemory.start + g_FsMemory.size;
            clampedSize = Fs_ClampMemBlock_80011E4C(start, end);
        }
        // Check if there's space left between current and nex allocation.
        else
        {
            end = iter->next->start;
            start = iter->start + iter->size;
            clampedSize = Fs_ClampMemBlock_80011E4C(start, end);
        }

        // Track smallest possible hole new block can fit into.
        if (clampedSize >= size && clampedSize < (s32)bufferMin.size)
        {
            blockMin = iter;
            bufferMin.size = clampedSize;
            bufferMin.start = blockMin->start + blockMin->size;
        }
    }

    if (bufferMin.start != NULL)
        Fs_RelinkMemBlock_80011F48(&g_FsMemory.freeList, blockMin, bufferMin.start, size);

    return bufferMin.start;
}

static inline u8* clampToHeapBounds(u8* ptr)
{
    u8* min;
    u8* max;

    min = g_FsMemory.start;
    if (ptr < min)
        return min;

    max = min + g_FsMemory.size;
    if (ptr > max)
        return max;

    return ptr;
}

s32 Fs_ClampMemBlock_80011E4C(u8* start, u8* end)
{
    u8* clampedStart;
    u8* clampedEnd;

    clampedStart = clampToHeapBounds(start);
    clampedEnd = clampToHeapBounds(end);

    if (clampedEnd < clampedStart)
        return 0;

    return clampedEnd - clampedStart;
}

s32 Fs_FreeMem_80011ed0(u8* ptr)
{
    FsMemBlock* iter;
    FsMemBlock* prev = &g_FsMemory.allocList;
    s32 result = false;

    if (prev->next != NULL)
    {
        do
        {
            iter = prev->next;
            if (iter->start == ptr)
            {
                Fs_RelinkMemBlock_80011F48(prev, &g_FsMemory.freeList, NULL, 0U);
                result = true;
                break;
            }
            else
            {
                prev = iter;
            }
        }
        while (iter->next != NULL);
    }

    return result;
}

void Fs_RelinkMemBlock_80011F48(FsMemBlock* from, FsMemBlock* to, u8* start, u32 size)
{
    FsMemBlock* tmp;

    tmp = from->next;
    from->next = tmp->next;

    tmp->next = to->next;
    to->next = tmp;

    tmp->start = start;
    tmp->size = size;
}

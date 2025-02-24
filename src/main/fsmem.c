#include "main/fsmem.h"

/** FS memory heap. */
s_FsMemState g_FsMemory;

/** @brief Initialize FS memory heap.
 * @param start Heap base.
 * @param size Total heap size in bytes.
 */
void Fs_InitializeMem(u8* start, u32 size)
{
    s32 i;

    // This really wants the start and size to be aligned to 8,
    // but since they're already hardcoded elsewhere, it doesn't really matter.
    if ((u32)start & 3)
    {
        size = 0;
    }
    if (size & 3)
    {
        size = 0;
    }

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

/** @brief Allocate FS memory block.
 * @param size Number of bytes to allocate.
 * @return Allocated memory block.
 */
void* Fs_AllocMem(s32 size)
{
    s_FsMemBlock  bufferMin; // Seems to use this struct for some reason.
    s_FsMemBlock* blockMin;
    s_FsMemBlock* iter;
    s32 clampedSize;
    u8* start;
    u8* end;

    if (size == 0)
    {
        return NULL;
    }

    // Align to 4.
    size = (size + 3) & ~3;

    // No free blocks left.
    if (g_FsMemory.freeList.next == NULL)
    {
        return NULL;
    }

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
            clampedSize = Fs_ClampMemBlock(start, end);
        }
        // Check if there's space left between current and nex allocation.
        else
        {
            end = iter->next->start;
            start = iter->start + iter->size;
            clampedSize = Fs_ClampMemBlock(start, end);
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
    {
        Fs_RelinkMemBlock(&g_FsMemory.freeList, blockMin, bufferMin.start, size);
    }

    return bufferMin.start;
}

static inline u8* clampToHeapBounds(u8* ptr)
{
    u8* min;
    u8* max;

    min = g_FsMemory.start;
    if (ptr < min)
    {
        return min;
    }

    max = min + g_FsMemory.size;
    if (ptr > max)
    {
        return max;
    }

    return ptr;
}

/** @brief Clamp memory buffer size to heap bounds.
 * @param start Buffer start.
 * @param size Buffer end.
 * @return New block size, or 0 if it does not fit or is invalid.
 */
s32 Fs_ClampMemBlock(u8* start, u8* end)
{
    u8* clampedStart;
    u8* clampedEnd;

    clampedStart = clampToHeapBounds(start);
    clampedEnd = clampToHeapBounds(end);

    if (clampedEnd < clampedStart)
    {
        return 0;
    }

    return clampedEnd - clampedStart;
}

/** @brief Free FS memory block.
 * @param ptr Address of memory block to free.
 * @return 1 if block was freed, 0 if it wasn't found.
 */
s32 Fs_FreeMem(u8* ptr)
{
    s_FsMemBlock* iter;
    s_FsMemBlock* prev = &g_FsMemory.allocList;
    s32 result = false;

    if (prev->next != NULL)
    {
        do
        {
            iter = prev->next;
            if (iter->start == ptr)
            {
                Fs_RelinkMemBlock(prev, &g_FsMemory.freeList, NULL, 0U);
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

/** @brief Unlink an FS memblock from one list and link it to another.
 *
 * Unlinks `from->next` and links it to `to` (`to->next` becomes `from->next`).
 * Used to both allocate (`from = &free_list`) and free (`from` is in `alloc_list`).
 *
 * @param from List node to unlink from.
 * @param to List node to link to.
 * @param start New block base.
 * @param size New block size.
 */
void Fs_RelinkMemBlock(s_FsMemBlock* from, s_FsMemBlock* to, u8* start, u32 size)
{
    s_FsMemBlock* temp;

    temp = from->next;
    from->next = temp->next;

    temp->next = to->next;
    to->next = temp;

    temp->start = start;
    temp->size = size;
}

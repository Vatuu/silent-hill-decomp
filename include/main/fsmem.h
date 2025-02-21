#ifndef _FSMEM_H
#define _FSMEM_H

#include "common.h"

#define FS_MEM_BLOCK_COUNT 16       /** Number of FS memory blocks that can be allocated. */
#define FS_MEM_BASE        0x1C0000 /** FS heap base (0x801C0000). */
#define FS_MEM_SIZE        0x20000  /** FS heap size (128kb). */

/** @brief FS memory block.
 * Describes one allocation in the FS heap.
 */
typedef struct FsMemBlock
{
    u8*                start; /** Start address. */
    u32                size;  /** Size in bytes. */
    struct FsMemBlock* next;  /** Next block in list. */
} FsMemBlock;

/** @brief State of the FS memory heap.
 * This heap seems to only be used by the FS code.
 */
typedef struct
{
    u8*        start;                      /** Heap base. */
    u32        size;                       /** Total heap size in bytes. */
    FsMemBlock allocList;                  /** Head of list of allocated memory blocks. */
    FsMemBlock freeList;                   /** Head of list of free memory blocks. */
    FsMemBlock blocks[FS_MEM_BLOCK_COUNT]; /** Block pool. */
} FsMemState;

extern FsMemState g_FsMemory;

void nullsub_800120b0(void);
void nullsub_80011cfc(void);

void  Fs_InitializeMem_80011C70(u8* start, u32 size);
void  Fs_RelinkMemBlock_80011F48(FsMemBlock* from, FsMemBlock* to, u8* start, u32 size);
void* Fs_AllocMem_80011D04(s32 size);
s32   Fs_ClampMemBlock_80011E4C(u8* start, u8* end);
s32   Fs_FreeMem_80011ed0(u8* ptr);

#endif

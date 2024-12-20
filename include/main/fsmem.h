#ifndef _FSMEM_H
#define _FSMEM_H

#include "common.h"

#define FS_MEM_NUM_BLOCKS 16 /** Number of FS memory blocks that can be allocated. */
#define FS_MEM_BASE 0x1C0000 /** FS heap base (0x801C0000). */
#define FS_MEM_SIZE 0x20000  /** FS heap size (128kb). */

/** @brief FS memory block.
 * Describes one allocation in the FS heap.
 */
typedef struct FsMemBlock {
  u8 *start;               /** Starting address. */
  u32 size;                /** Size in bytes. */
  struct FsMemBlock *next; /** Next block in list. */
} FsMemBlock;

/** @brief State of the FS memory heap.
 * This heap seems to only be used by the FS code.
 */
typedef struct {
  u8 *start;                            /** Heap base. */
  u32 size;                             /** Total heap size in bytes. */
  FsMemBlock alloc_list;                /** Head of list of allocated memblocks. */
  FsMemBlock free_list;                 /** Head of list of free memblocks. */
  FsMemBlock blocks[FS_MEM_NUM_BLOCKS]; /** Block pool. */
} FsMemState;

/** FS memory heap. */
extern FsMemState g_FsMem;

void nullsub_80011cfc(void);
void nullsub_800120b0(void);

/** @brief Initialize FS memory heap.
 * @param start Heap base.
 * @param size Total heap size in bytes.
 */
void fsMemInit(u8 *start, u32 size);

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
void fsMemRelinkBlock(FsMemBlock *from, FsMemBlock *to, u8 *start, u32 size);

/** @brief Clamp memory buffer size to heap bounds.
 * @param start Buffer start.
 * @param size Buffer end.
 * @return New block size, or 0 if it does not fit or is invalid.
 */
s32 fsMemClampBlock(u8 *start, u8 *end);

/** @brief Allocate FS memory block.
 * @param size Number of bytes to allocate.
 * @return Allocated memory block.
 */
void *fsMemAlloc(u32 size);

/** @brief Free FS memory block.
 * @param ptr Address of memory block to free.
 * @return 1 if block was freed, 0 if it wasn't found.
 */
s32 fsMemFree(u8 *ptr);

#endif

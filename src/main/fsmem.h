#ifndef _FSMEM_H
#define _FSMEM_H

#include "common.h"

#define FS_MEM_NUM_BLOCKS 16

typedef struct FsMemBlock {
  u8 *start;
  u32 size;
  struct FsMemBlock *next;
} FsMemBlock;

typedef struct {
  u8 *start;
  u32 size;
  FsMemBlock alloc_list;
  FsMemBlock free_list;
  FsMemBlock blocks[FS_MEM_NUM_BLOCKS];
} FsMemState;

extern FsMemState g_FsMem;

void fsMemRelinkBlock(FsMemBlock *from, FsMemBlock *to, u8 *start, u32 size);
s32 fsMemClampBlock(u8 *start, u8 *end);

#endif

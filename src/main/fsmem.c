#include "main/fsmem.h"

void fsMemInit(u8 *start, u32 size) {
  s32 i;

  // this really wants the start and size to be aligned to 8,
  // but since they're already hardcoded elsewhere, it doesn't really matter
  if ((u32)start & 3) {
    size = 0;
  }
  if (size & 3) {
    size = 0;
  }

  g_FsMem.start = start;
  g_FsMem.size = size;
  g_FsMem.alloc_list.next = NULL;
  g_FsMem.alloc_list.start = start;
  g_FsMem.alloc_list.size = 0;
  g_FsMem.free_list.next = g_FsMem.blocks;
  g_FsMem.free_list.start = NULL;
  g_FsMem.free_list.size = 0;

  for (i = 0; i < FS_MEM_NUM_BLOCKS; i++) {
    g_FsMem.blocks[i].start = NULL;
    g_FsMem.blocks[i].size = 0;
    if (i == FS_MEM_NUM_BLOCKS - 1) {
      g_FsMem.blocks[i].next = NULL;
    } else {
      g_FsMem.blocks[i].next = &g_FsMem.blocks[i + 1];
    }
  }
}

void nullsub_80011cfc(void) {

}

void *fsMemAlloc(s32 size) {
  FsMemBlock min_buffer; // seems to use this struct for some reason
  FsMemBlock *min_block;
  FsMemBlock *iter;
  s32 clamped_size;
  u8 *start;
  u8 *end;

  if (size == 0) {
    return NULL;
  }

  // align to 4
  size = (size + 3) & ~3;

  if (g_FsMem.free_list.next == NULL) {
    // no free blocks left
    return NULL;
  }

  iter = &g_FsMem.alloc_list;
  min_buffer.start = NULL;
  min_buffer.size = 0x0FFFFFFF;
  min_block = NULL;

  for (; iter != NULL; iter = iter->next) {
    if (iter->next == NULL) {
      // last allocation; check if there is space left after it
      start = iter->start + iter->size;
      end = g_FsMem.start + g_FsMem.size;
      clamped_size = fsMemClampBlock(start, end);
    } else {
      // check if there is space left in between this allocation and the next
      end = iter->next->start;
      start = iter->start + iter->size;
      clamped_size = fsMemClampBlock(start, end);
    }

    if ((clamped_size >= size) && (clamped_size < (s32)min_buffer.size)) {
      // track the smallest possible hole we can fit the new block into
      min_block = iter;
      min_buffer.size = clamped_size;
      min_buffer.start = min_block->start + min_block->size;
    }
  }

  if (min_buffer.start != NULL) {
    fsMemRelinkBlock(&g_FsMem.free_list, min_block, min_buffer.start, size);
  }

  return min_buffer.start;
}

static inline u8 *clampToHeapBounds(u8 *ptr) {
  u8 *min;
  u8 *max;

  min = g_FsMem.start;
  if (ptr < min) {
    return min;
  }

  max = min + g_FsMem.size;
  if (ptr > max) {
    return max;
  }

  return ptr;
}

s32 fsMemClampBlock(u8 *start, u8 *end) {
  u8 *clamped_start;
  u8 *clamped_end;

  clamped_start = clampToHeapBounds(start);
  clamped_end = clampToHeapBounds(end);

  if (clamped_end < clamped_start) {
    return 0;
  }

  return clamped_end - clamped_start;
}

s32 fsMemFree(u8 *ptr) {
  FsMemBlock *iter;
  FsMemBlock *prev = &g_FsMem.alloc_list;
  s32 result = 0;

  if (prev->next != NULL) {
    do {
      iter = prev->next;
      if (iter->start == ptr) {
        fsMemRelinkBlock(prev, &g_FsMem.free_list, NULL, 0U);
        result = 1;
        break;
      } else {
        prev = iter;
      }
    } while (iter->next != NULL);
  }

  return result;
}

void fsMemRelinkBlock(FsMemBlock *from, FsMemBlock *to, u8 *start, u32 size) {
  FsMemBlock *tmp;

  tmp = from->next;
  from->next = tmp->next;

  tmp->next = to->next;
  to->next = tmp;

  tmp->start = start;
  tmp->size = size;
}

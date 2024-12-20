#include "main/fsmem.h"

INCLUDE_ASM("asm/main/nonmatchings/fsmem", fsMemInit);

void nullsub_80011cfc(void) {

}

INCLUDE_ASM("asm/main/nonmatchings/fsmem", fsMemAlloc);

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

INCLUDE_ASM("asm/main/nonmatchings/fsmem", memcpy);

void nullsub_800120b0(void) {

}

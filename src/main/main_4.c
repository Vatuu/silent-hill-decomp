#include "main_4.h"

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsQueueAllocEntryData);

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsQueueCanRead);

s32 fsQueueDoBuffersOverlap(u8 *data1, u32 size1, u8 *data2, u32 size2) {
  u32 data1_low = (u32)data1 & 0xFFFFFF;
  u32 data2_low = (u32)data2 & 0xFFFFFF;
  if ((data2_low >= data1_low + size1) || (data1_low >= data2_low + size2)) {
    return 0;
  }
  return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsQueueTickSetLoc);

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsQueueTickRead);

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsQueueTickReset);

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsFileReadPcDrv);

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsQueueUpdatePostLoad);

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsQueuePostLoadTim);

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsQueuePostLoadGsThing);

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsMemInit);

void nullsub_80011cfc(void) {

}

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsMemAlloc);

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
  u8 *var_a0;
  u8 *var_a1;

  var_a0 = clampToHeapBounds(start);
  var_a1 = clampToHeapBounds(end);

  if (var_a1 < var_a0) {
    return 0;
  }

  return var_a1 - var_a0;
}

INCLUDE_ASM("asm/main/nonmatchings/main_4", fsMemFree);

void fsMemRelinkBlock(FsMemBlock *from, FsMemBlock *to, u8 *start, u32 size) {
  FsMemBlock *tmp;

  tmp = from->next;
  from->next = tmp->next;

  tmp->next = to->next;
  to->next = tmp;

  tmp->start = start;
  tmp->size = size;
}

INCLUDE_ASM("asm/main/nonmatchings/main_4", memcpy);

void nullsub_800120b0(void) {

}

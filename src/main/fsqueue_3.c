#include "fsqueue.h"
#include "fsmem.h"

s32 fsQueueAllocEntryData(FsQueueEntry *entry) {
  s32 result = 0;

  if (entry->allocate) {
    entry->data = fsMemAlloc(ALIGN(entry->info->numblocks * FS_BLOCK_SIZE, FS_SECTOR_SIZE));
  } else {
    entry->data = entry->external_data;
  }

  if (entry->data != 0) {
    result = 1;
  }

  return result;
}

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueueCanRead);

s32 fsQueueDoBuffersOverlap(u8 *data1, u32 size1, u8 *data2, u32 size2) {
  u32 data1_low = (u32)data1 & 0xFFFFFF;
  u32 data2_low = (u32)data2 & 0xFFFFFF;
  if ((data2_low >= data1_low + size1) || (data1_low >= data2_low + size2)) {
    return 0;
  }
  return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueueTickSetLoc);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueueTickRead);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueueTickReset);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsFileReadPcDrv);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueueUpdatePostLoad);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueuePostLoadTim);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueuePostLoadGsThing);

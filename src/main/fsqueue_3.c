#include "fsqueue.h"
#include "fsmem.h"
#include <LIBCD.H>

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

s32 fsQueueTickSetLoc(FsQueueEntry* entry) {
  CdlLOC cdloc;
  CdIntToPos(entry->info->startsector, &cdloc);
  return CdControl(CdlSetloc, (u_char *)&cdloc, NULL);
}

s32 fsQueueTickRead(FsQueueEntry* entry) {
  // round up to sector boundary; masking not needed because of the `>> 11` below
  s32 num_sectors = (entry->info->numblocks * FS_BLOCK_SIZE) + FS_SECTOR_SIZE - 1;
  // overflow check?
  if (num_sectors < 0) {
    num_sectors += FS_SECTOR_SIZE - 1;
  }
  return CdRead(num_sectors >> FS_SECTOR_SHIFT, (u_long *)entry->data, 0x80);
}

s32 fsQueueTickReset(FsQueueEntry *entry) {
  s32 result = false;

  g_FsQueue.reset_timer_0++;

  if (g_FsQueue.reset_timer_0 >= 8) {
    result = true;
    g_FsQueue.reset_timer_0 = 0;
    g_FsQueue.reset_timer_1++;
    if (g_FsQueue.reset_timer_1 >= 9) {
      if (CdReset(0) == 1) {
        g_FsQueue.reset_timer_1 = 0;
      } else {
        result = false;
      }
    }
  }

  return result;
}

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueueTickReadPcDrv);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueueUpdatePostLoad);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueuePostLoadTim);

INCLUDE_ASM("asm/main/nonmatchings/fsqueue_3", fsQueuePostLoadGsThing);

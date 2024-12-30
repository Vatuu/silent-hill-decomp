#include "main/fsqueue.h"
#include "main/fsmem.h"
#include <LIBAPI.H>
#include <LIBCD.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <STRING.H>

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

s32 fsQueueCanRead(FsQueueEntry *entry) {
  FsQueueEntry *other;
  s32 queue_len;
  s32 overlap;
  s32 i;

  queue_len = g_FsQueue.read.idx - g_FsQueue.postload.idx;

  if (queue_len > 0) {
    i = 0;
    do {
      other = &g_FsQueue.entries[(g_FsQueue.postload.idx + i) & (FS_QUEUE_LEN - 1)];
      overlap = false;
      if (other->postload || other->allocate) {
        overlap = fsQueueDoBuffersOverlap(
          entry->data,
          ALIGN(entry->info->numblocks * FS_BLOCK_SIZE, FS_SECTOR_SIZE),
          other->data,
          other->info->numblocks * FS_BLOCK_SIZE
        );
      }
      if (overlap == true) {
        return false;
      }
      i++;
    } while (i < queue_len);
  }

  return true;
}

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
  return CdRead(num_sectors >> FS_SECTOR_SHIFT, (u_long *)entry->data, CdlModeSpeed);
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

s32 fsQueueTickReadPcDrv(FsQueueEntry *entry) {
  s32 handle;
  s32 tmp;
  s32 retry;
  s32 result;
  FileInfo *finfo = entry->info;
  char pathbuf[64];
  char namebuf[32];

  result = 0;

  strcpy(pathbuf, "sim:.\\DATA");
  strcat(pathbuf, g_FilePaths[finfo->pathnum]);
  fsFileInfoGetName(namebuf, finfo);
  strcat(pathbuf, namebuf);

  for (retry = 0; retry <= 2; retry++) {
    handle = open(pathbuf, 0x4001);
    if (handle == -1)
      continue;

    tmp = read(handle,entry->data, ALIGN(finfo->numblocks * FS_BLOCK_SIZE, FS_SECTOR_SIZE));
    if (tmp == -1) {
      continue;
    }

    do {
      tmp = close(handle);
    } while (tmp == -1);

    result = 1;
    break;
  }

  return result;
}

s32 fsQueueUpdatePostLoad(FsQueueEntry *entry) {
  s32 result;
  s32 state;
  u8 postload;

  result = 0;
  state = g_FsQueue.postload_state;

  switch (state) {
    case FSQS_POSTLOAD_INIT:
      if (entry->allocate) {
        g_FsQueue.postload_state = FSQS_POSTLOAD_SKIP;
      } else {
        g_FsQueue.postload_state = FSQS_POSTLOAD_EXEC;
      }
      break;

    case FSQS_POSTLOAD_SKIP:
      /* do nothing */
      break;

    case FSQS_POSTLOAD_EXEC:
      postload = entry->postload;
      switch (postload) {
        case FS_POSTLOAD_NONE:
          result = 1;
          break;
        case FS_POSTLOAD_TIM:
          result = fsQueuePostLoadTim(entry);
          break;
        case FS_POSTLOAD_ANM:
          result = fsQueuePostLoadAnm(entry);
          break;
        default:
          break;
      }
      break;

    default:
      break;
  }

  return result;
}

s32 fsQueuePostLoadTim(FsQueueEntry *entry) {
  TIM_IMAGE tim;
  RECT tmprect;

  OpenTIM((u_long *)entry->external_data);
  ReadTIM(&tim);

  tmprect = *tim.prect;
  if (entry->extra.image.u != 0xFF) {
    // this cursed contraption just extracts the XY from the tpage value
    // for some reason it seems to be byte swapped, or maybe tpage is actually stored as u8[2]?
    // same as tmprect.x = (entry->extra.image.tpage & 0x0F) * 64 for a normal tpage
    tmprect.x = entry->extra.image.u + ((*(((u8*)&entry->extra.image.tpage) + 1) & 0xF) << 6);
    // same as tmprect.y = (entry->extra.image.tpage & 0x10) * 16 for a normal tpage
    tmprect.y = entry->extra.image.v + ((*(((u8*)&entry->extra.image.tpage) + 1) << 4) & 0x100);
  }

  LoadImage(&tmprect, tim.paddr);

  if (tim.caddr != NULL) {
    tmprect = *tim.crect;
    if (entry->extra.image.clut_x != -1) {
      tmprect.x = entry->extra.image.clut_x;
      tmprect.y = entry->extra.image.clut_y;
    }
    LoadImage(&tmprect, tim.caddr);
  }

  return true;
}

s32 fsQueuePostLoadAnm(FsQueueEntry* entry) {
  func_80035560(entry->extra.anm.field_00, entry->extra.anm.field_04, entry->external_data, entry->extra.anm.field_08);
  return true;
}

#ifndef _FSQUEUE_H
#define _FSQUEUE_H

#include "common.h"
#include "filetable.h"

#define FS_QUEUE_MAX 32

typedef union {
  struct {
    u16 tpage;
    u8 u;
    u8 v;
    s16 clut_x;
    s16 clut_y;
  } image;
  struct {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
    u16 field_08;
    u16 field_0a;
  } gs_thing;
} FsQueueExtra;

typedef struct {
  const FileEntry *info;
  u8 operation;
  u8 postload;
  u8 allocate;
  u8 unused_0;
  void *external_data;
  u32 unused_1;
  FsQueueExtra extra;
  void *data;
} FsQueueEntry;

typedef struct {
  FsQueueEntry entries[FS_QUEUE_MAX];
  s32 last_idx;
  FsQueueEntry *last_ptr;
  s32 read_idx;
  FsQueueEntry *read_ptr;
  s32 postload_idx;
  FsQueueEntry *postload_ptr;
  u32 state;
  u32 postload_state;
  s32 reset_timer_0;
  s32 reset_timer_1;
} FsQueue;

extern FsQueue g_FsQueue;
extern s32 D_800C489C;

s32 func_8003c850();
void fsQueueInit(void);
s32 fsQueueIsEntryLoaded(s32 arg0);
s32 fsQueueGetLength(void);
s32 fsQueueDoThingWhenEmpty(void);
s32 fsQueueAllocEntryData(FsQueueEntry *entry);
s32 fsQueueReadPcDrv(FsQueueEntry *entry);
s32 fsQueueCanRead(FsQueueEntry *entry);
s32 fsQueueDoBuffersOverlap(u8 *data1, u32 size1, u8 *data2, u32 size2);
void fsQueueTickSetLoc(FsQueueEntry *entry);
void fsQueueTickRead(FsQueueEntry *entry);
s32 fsQueueTickReset(FsQueueEntry *entry);
void fsQueueUpdate(void);
s32 fsQueueUpdateRead(FsQueueEntry *entry);
s32 fsQueueUpdateSeek(FsQueueEntry *entry);
void fsQueueUpdatePostLoad(FsQueueEntry *entry);
void fsQueuePostLoadTim(FsQueueEntry *entry);
void fsQueuePostLoadGsThing(FsQueueEntry *entry);

#endif

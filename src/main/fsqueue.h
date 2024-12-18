#ifndef MAIN_2_H
#define MAIN_2_H

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
s32 fsQueueIsEntryLoaded(s32 arg0);
s32 fsQueueGetLength(void);
s32 fsQueueDoThingWhenEmpty(void);

#endif

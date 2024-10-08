#ifndef MAIN_4_H
#define MAIN_4_H

#include "common.h"

typedef struct MaybeLinkedList {
  /* 0x00 */ s32                     unk0;
  /* 0x04 */ s32                     unk4;
  /* 0x08 */ struct MaybeLinkedList *next;
} MaybeLinkedList;

void maybeMoveLastElement(MaybeLinkedList *from, MaybeLinkedList *to, s32 data0,
                          s32 data1);

#endif

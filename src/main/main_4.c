#include "main_4.h"

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011630);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_800116BC);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_800117AC);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_800117E8);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_8001182C);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011884);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_8001190c);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011A4C);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011B24);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011C3C);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011C70);

void func_80011cfc(void) {}

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011D04);

static inline u32 maybeClamp(s32 arg0) {
  u32 min;
  u32 max;

  min = D_800230C0.maybeStart;
  if (arg0 < min) {
    return min;
  }

  max = min + D_800230C0.maybeLength;
  if (arg0 > max) {
    return max;
  }

  return arg0;
}

s32 func_80011E4C(s32 arg0, s32 arg1) {
  u32 var_a0;
  u32 var_a1;

  var_a0 = maybeClamp(arg0);
  var_a1 = maybeClamp(arg1);

  if (var_a1 < var_a0) {
    return 0;
  }

  return var_a1 - var_a0;
}

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011ed0);

void maybeMoveLastElement(MaybeLinkedList *from, MaybeLinkedList *to, s32 data0,
                          s32 data1) {
  MaybeLinkedList *tmp;

  tmp        = from->next;
  from->next = tmp->next;

  tmp->next = to->next;
  to->next  = tmp;

  tmp->unk0 = data0;
  tmp->unk4 = data1;
}

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011F78);

void func_800120b0(void) {}

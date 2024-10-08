#include "main_4.h"

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011630);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_800116BC);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_800117AC);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_800117E8);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_8001182C);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011884);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_8001190C);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011A4C);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011B24);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011C3C);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011C70);

void func_80011CFC(void) {}

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011D04);

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011E4C);

INCLUDE_ASM("asm/main/nonmatchings/main_4", func_80011ED0);

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

INCLUDE_ASM("asm/main/nonmatchings/main_4", FUN_80011F78);

void func_800120B0(void) {}

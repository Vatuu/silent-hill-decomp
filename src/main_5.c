#include "common.h"

INCLUDE_ASM("asm/main/nonmatchings/main_5", FUN_800120b8);

extern u32 FUN_800120b8(void);

u32 FUN_800120e4() { return FUN_800120b8() >> 17; }

extern s32 D_80022C90;

s32 FUN_80012104() { return D_80022C90; }

void FUN_80012110(s32 arg0) { D_80022C90 = arg0; }

u32 FUN_8001211c() { return FUN_800120b8() >> 20; }

void FUN_8001213c(int *dst, int *src, int size) {
  int *end;
  int  data;

  if (dst == src) {
    return;
  }

  size >>= 2;

  if (dst < src) {
    end = src + size;

    while (src < end) {
      data   = *src++;
      *dst++ = data;
    }
  } else {
    end = src;

    dst += size;
    src += size;

    while (src > end) {
      *(--dst) = *(--src);
    }
  }
}

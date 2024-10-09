#include "main_5.h"

extern u32 D_80022C90;

u32 ranqd1() {
    u32 next_seed = D_80022C90;
    
    next_seed = (next_seed * 1664525) + 1013904223;
    D_80022C90 = next_seed;
    
    return next_seed;
}

u32 FUN_800120e4() { return ranqd1() >> 17; }

s32 FUN_80012104() { return D_80022C90; }

void FUN_80012110(s32 arg0) { D_80022C90 = arg0; }

u32 FUN_8001211c() { return ranqd1() >> 20; }

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

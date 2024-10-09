#include "common.h"

extern u32 D_80022C90;

/* LCG RNG algorithm based on Numerical Recipes (Second Edition, chapter 7.1, An Even Quicker Generator) */
u32 ranqd1();

u32 FUN_800120e4();

s32 FUN_80012104();

void FUN_80012110(s32 arg0);

u32 FUN_8001211c();

void FUN_8001213c(int *dst, int *src, int size);

#ifndef _RNG_H
#define _RNG_H

#include "common.h"

extern u32 g_RngSeed;

u32  rngRand32(void);
s16  rngRand16(void);
u32  rngGetSeed(void);
void rngSetSeed(u32 newSeed);
u16  rngRand12(void);

#endif

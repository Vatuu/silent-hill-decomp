#ifndef _RNG_H
#define _RNG_H

#include "common.h"

extern u32 g_RngSeed;

u32  Rng_Rand32(void);
s16  Rng_Rand16(void);
u32  Rng_GetSeed(void);
void Rng_SetSeed(u32 newSeed);
u16  Rng_Rand12(void);

#endif

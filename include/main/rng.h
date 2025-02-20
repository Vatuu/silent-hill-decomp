#ifndef _RNG_H
#define _RNG_H

#include "common.h"

extern u32 g_RngSeed;

u32  Rng_Rand32_800120b8(void);
s16  Rng_Rand32_800120e4(void);
u32  Rng_GetSeed_80012104(void);
void Rng_SetSeed_80012110(u32 newSeed);
u16  Rng_Rand12_8001211c(void);

#endif

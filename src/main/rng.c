#include "main/rng.h"

u32 g_RngSeed = 0;

u32 Rng_Rand32(void)
{
    u32 nextSeed = g_RngSeed;

    nextSeed = (nextSeed * 1664525) + 1013904223;
    g_RngSeed = nextSeed;

    return nextSeed;
}

s16 Rng_Rand16(void)
{
    return Rng_Rand32() >> 0x11;
}

u32 Rng_GetSeed(void)
{
    return g_RngSeed;
}

void Rng_SetSeed(u32 nextSeed)
{
    g_RngSeed = nextSeed;
}

u16 Rng_Rand12(void)
{
    return Rng_Rand32() >> 0x14;
}

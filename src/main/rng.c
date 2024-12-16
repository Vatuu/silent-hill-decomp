#include "rng.h"

u32 g_RngSeed = 0;

u32 rngRand32(void) {
  u32 nextseed = g_RngSeed;

  nextseed   = (nextseed * 1664525) + 1013904223;
  g_RngSeed = nextseed;

  return nextseed;
}

s16 rngRand16(void) {
  return rngRand32() >> 0x11;
}

u32 rngGetSeed(void) {
  return g_RngSeed;
}

void rngSetSeed(u32 nextseed) {
  g_RngSeed = nextseed;
}

u16 rngRand12(void) {
  return rngRand32() >> 0x14;
}

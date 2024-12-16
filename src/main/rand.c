#include "rand.h"

u32 g_RandSeed = 0;

u32 ranqd1() {
  u32 next_seed = g_RandSeed;

  next_seed   = (next_seed * 1664525) + 1013904223;
  g_RandSeed = next_seed;

  return next_seed;
}

s16 getPositive16BitRandomNumber() { return ranqd1() >> 0x11; }

u32 getRandomSeed() { return g_RandSeed; }

void setRandomSeed(u32 next_seed) { g_RandSeed = next_seed; }

u16 get12BitRandomNumber() { return ranqd1() >> 0x14; }

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s02.h"
#include "maps/characters/creeper.h"

INCLUDE_RODATA("maps/map3_s02/nonmatchings/map3_s02", D_800C9578);

INCLUDE_RODATA("maps/map3_s02/nonmatchings/map3_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CAB58

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Creeper` split.
#include "../src/maps/characters/creeper.c" // 0x800CCA14

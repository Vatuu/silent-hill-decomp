#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/map4/map4_s04.h"

INCLUDE_RODATA("maps/map4_s04/nonmatchings/map4_s04", D_800C9578);

INCLUDE_RODATA("maps/map4_s04/nonmatchings/map4_s04", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CBC60

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CC054

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CC12C

#include "maps/shared/Particle_Update.h" // 0x800CC448

#include "maps/shared/sharedFunc_800CEFF4_0_s00.h" // 0x800CCA70

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/map3/map3_s06.h"

INCLUDE_RODATA("maps/map3_s06/nonmatchings/map3_s06", D_800C9578);

INCLUDE_RODATA("maps/map3_s06/nonmatchings/map3_s06", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB2E0

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB8AC

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CB984

#include "maps/shared/Particle_Update.h" // 0x800CBC90

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CC260

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

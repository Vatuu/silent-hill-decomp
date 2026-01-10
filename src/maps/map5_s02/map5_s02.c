#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"
#include "maps/map5/map5_s02.h"

INCLUDE_RODATA("maps/map5_s02/nonmatchings/map5_s02", D_800C9578);

INCLUDE_RODATA("maps/map5_s02/nonmatchings/map5_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CB6CC

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Stalker` split.
#include "../src/maps/characters/stalker.c" // 0x800CDC08

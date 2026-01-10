#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/map3/map3_s00.h"

INCLUDE_RODATA("maps/map3_s00/nonmatchings/map3_s00", D_800C9578);

INCLUDE_RODATA("maps/map3_s00/nonmatchings/map3_s00", g_MapOverlayHeader);

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"


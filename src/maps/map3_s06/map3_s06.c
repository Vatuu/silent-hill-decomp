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

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

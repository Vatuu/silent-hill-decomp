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

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

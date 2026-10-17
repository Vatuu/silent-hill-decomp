#include "inline_no_dmpsx.h"
#include <psyq/gtemac.h>
#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map6/map6_s00.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/groaner.h"
#include "maps/characters/player.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

#if !VERSION_IS(USA)
INCLUDE_RODATA("maps/map6_s00/nonmatchings/characters", sharedData_800CA9F0_0_s01);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/characters", sharedData_800CAA00_0_s01);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/characters", sharedData_800CAA18_0_s01);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/characters", sharedData_800CAA30_0_s01);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/characters", sharedData_800CAA48_0_s01);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/characters", sharedData_800CAA98_0_s01);
#endif

#include "../src/maps/characters/air_screamer.c" // 0x800D18FC

#include "../src/maps/characters/groaner.c" // 0x800E2934

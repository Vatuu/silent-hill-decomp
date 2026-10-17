#include "inline_no_dmpsx.h"
#include <psyq/gtemac.h>
#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "bodyprog/sound/sound_system.h"
#include "main/rng.h"
#include "maps/map4/map4_s02.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/groaner.h"
#include "maps/characters/player.h"
#include "maps/characters/romper.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

#if !VERSION_IS(USA)
INCLUDE_RODATA("maps/map4_s02/nonmatchings/characters", sharedData_800CA9F0_0_s01);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/characters", sharedData_800CAA00_0_s01);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/characters", sharedData_800CAA18_0_s01);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/characters", sharedData_800CAA30_0_s01);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/characters", sharedData_800CAA48_0_s01);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/characters", sharedData_800CAA98_0_s01);
#endif

#include "../src/maps/characters/air_screamer.c" // 0x800D0B24

#include "../src/maps/characters/groaner.c" // 0x800E1B5C

#include "../src/maps/characters/romper.c" // 0x800E6134

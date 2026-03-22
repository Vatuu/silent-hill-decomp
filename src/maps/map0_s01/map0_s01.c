#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map0/map0_s01.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/player.h"

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CA9F0);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA00);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA18);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA30);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA48);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
#include "../src/maps/characters/air_screamer.c" // 0x800D2170

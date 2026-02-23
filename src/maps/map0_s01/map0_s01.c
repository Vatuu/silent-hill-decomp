#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map0/map0_s01.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/player.h"

const VECTOR D_800CA5C8 = {};

#include "maps/shared/sharedFunc_800CCB8C_0_s01.h" // 0x800CCB8C

#include "maps/shared/sharedFunc_800CD1F8_0_s01.h" // 0x800CD1F8

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CA9F0);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CA9F4);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA00);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA18);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA30);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA48);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
#include "../src/maps/characters/air_screamer.c" // 0x800D2170

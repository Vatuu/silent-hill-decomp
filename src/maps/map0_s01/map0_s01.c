#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"
#include "maps/characters/air_screamer.h"

const VECTOR D_800CA5C8 = {};

#include "maps/shared/sharedFunc_800CCB8C_0_s01.h" // 0x800CCB8C

#include "maps/shared/sharedFunc_800CD1F8_0_s01.h" // 0x800CD1F8

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CE000

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CE4C4

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CE59C

#include "maps/shared/Particle_Update.h" // 0x800CE8A8

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CEE2C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF2A4

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CF3F4

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CF7BC

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF8E8

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF8F0

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF9A8

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CFA30

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

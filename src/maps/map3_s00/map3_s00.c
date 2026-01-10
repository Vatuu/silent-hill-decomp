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

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB408

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB9D4

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CBAAC

#include "maps/shared/Particle_Update.h" // 0x800CBDB8

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CC388

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC844

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CC994

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CCD5C

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CCE88

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CCE90

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CCF48

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CCFD0

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"


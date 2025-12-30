#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s01.h"

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CE5D4_1_s03.h" // 0x800CBB60

#include "maps/shared/sharedFunc_800CE688_1_s03.h" // 0x800CBC14

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CC2DC

#include "../src/maps/characters/player.c"

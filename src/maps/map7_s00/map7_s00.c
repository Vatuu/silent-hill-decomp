#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s00.h"
#include "maps/characters/lisa.h"

INCLUDE_RODATA("asm/maps/map7_s00/nonmatchings/map7_s00", D_800C9578);

INCLUDE_RODATA("asm/maps/map7_s00/nonmatchings/map7_s00", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CB624

#include "../src/maps/characters/player.c"
#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/map7/map7_s03.h"

INCLUDE_RODATA("maps/map7_s03/nonmatchings/map7_s03", D_800C9578);

INCLUDE_RODATA("maps/map7_s03/nonmatchings/map7_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CD170

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CD608

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CD6E0

#include "maps/shared/Particle_Update.h" // 0x800CD9EC

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CDFAC

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"


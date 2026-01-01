#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s01.h"

// TODO: Func declarations in header.

INCLUDE_RODATA("maps/map4_s01/nonmatchings/map4_s01", D_800C9578);

INCLUDE_RODATA("maps/map4_s01/nonmatchings/map4_s01", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CAAD0_1_s05.h" // 0x800CC19C

#include "maps/shared/sharedFunc_800CABF8_1_s05.h" // 0x800CC2C4

#include "maps/shared/sharedFunc_800CB040_1_s05.h" // 0x800CC70C

#include "maps/shared/sharedFunc_800CB884_1_s05.h" // 0x800CCF50

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CD548

#include "../src/maps/characters/player.c"

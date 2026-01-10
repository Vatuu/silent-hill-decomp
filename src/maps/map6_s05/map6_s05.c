#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/map6/map6_s05.h"

INCLUDE_RODATA("maps/map6_s05/nonmatchings/map6_s05", D_800C9578);

INCLUDE_RODATA("maps/map6_s05/nonmatchings/map6_s05", g_MapOverlayHeader);

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC7A4

#include "maps/shared/sharedFunc_800E1114_6_s04.h" // 0x800CC7B4

#include "maps/shared/sharedFunc_800E1258_6_s04.h" // 0x800CC8F8

#include "maps/shared/sharedFunc_800E1290_6_s04.h" // 0x800CC930

#include "maps/shared/sharedFunc_800E12D0_6_s04.h" // 0x800CC970

// TODO: Might be part of shared block above with `map6_s04::func_800E155C`
void func_800CCBFC(void) {}

INCLUDE_RODATA("maps/map6_s05/nonmatchings/map6_s05", D_800CA62C);

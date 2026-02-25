#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/map6/map6_s05.h"
#include "maps/particle.h"
#include "maps/characters/player.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC7A4

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CC7B4

#include "maps/shared/Map_RoomBgmInit_6_s04.h" // 0x800CC8F8

#include "maps/shared/Map_RoomBgmInit_6_s04_CondTrue.h" // 0x800CC930

#include "maps/shared/Map_RoomBgmInit_6_s04_CondFalse.h" // 0x800CC970

// TODO: Might be part of shared block above with `map6_s04::func_800E155C`
void Gfx_LoadingScreen_StageString(void) {}

INCLUDE_RODATA("maps/map6_s05/nonmatchings/map6_s05", D_800CA62C);

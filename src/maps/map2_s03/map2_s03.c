#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s03.h"

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CA904

#include "../src/maps/characters/player.c"

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC7C0

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CC7D0

#include "maps/shared/sharedFunc_800E7914_2_s00.h" // 0x800CCA1C

void Gfx_LoadingScreen_StageString(void) {} // 0x800CCB24

void Map_WorldObjectsInit(void) {} // 0x800CCB2C

void Map_WorldObjectsUpdate(void) {} // 0x800CCB34

const char* MAP_MESSAGES[] = {
#include "maps/shared/mapMsg_common.h"
    "\tNO_STAGE! ~E "
};


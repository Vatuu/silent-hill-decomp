#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s04.h"

#include "../src/maps/characters/Chara_Alessa.c"

// TODO: Splitting Dahlia to separate file causes alignment issue inside `sharedSymbol_800CD4A0_2_s01` rodata
// (4 bytes inserted between VECTOR3 and jtbl both used in that func)
// Including her here seems to let it work for now.

#include "../src/maps/characters/Chara_Dahlia.c"

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

#include "maps/shared/Ai_Dahlia_Update.h" // 0x800DCA30

#include "maps/shared/sharedFunc_800CD280_2_s01.h" // 0x800DCAA4

#include "maps/shared/sharedFunc_800CD2C8_2_s01.h" // 0x800DCAEC

#include "maps/shared/sharedSymbol_800CD4A0_2_s01.h" // 0x800DCCC4

#include "maps/shared/Ai_Dahlia_Init.h" // 0x800DD57C

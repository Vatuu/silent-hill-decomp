#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s02.h"

// TODO: Merge these into `src/maps/characters/Chara_Lisa.c` once map3_s04/map4_s04/map7_s00 usages of these are made into `Chara_Lisa` splits.

#include "maps/shared/Ai_Lisa_Update.h" // 0x800D5998

#include "maps/shared/sharedFunc_800D08FC_3_s04.h" // 0x800D5A0C

#include "maps/shared/sharedFunc_800D0944_3_s04.h" // 0x800D5A54

#include "maps/shared/sharedSymbol_800D0ADC_3_s04.h" // 0x800D5BEC

#include "maps/shared/Ai_Lisa_Init.h" // 0x800D6460
#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/creeper.h"
#include "maps/characters/player.h"
#include "maps/map3/map3_s02.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Creeper` split.
#include "../src/maps/characters/creeper.c" // 0x800CCA14

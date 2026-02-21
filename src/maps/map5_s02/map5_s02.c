#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"
#include "maps/map5/map5_s02.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Stalker` split.
#include "../src/maps/characters/stalker.c" // 0x800CDC08

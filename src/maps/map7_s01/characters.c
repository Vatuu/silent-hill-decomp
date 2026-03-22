#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map7/map7_s01.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/characters/puppet_nurse.h"

// player.c/puppet_nurse.c have some identical rodata which has to be deduplicated to match.
// More info at `src/maps/map5_s02/characters.c` as that had the same issue.

#include "../src/maps/characters/player.c"

#include "../src/maps/characters/puppet_nurse.c" // 0x800D16A4

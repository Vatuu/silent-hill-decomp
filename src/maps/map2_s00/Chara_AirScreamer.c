#include "inline_no_dmpsx.h"
#include <psyq/gtemac.h>
#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map2/map2_s00.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"

INCLUDE_RODATA("maps/map2_s00/nonmatchings/Chara_AirScreamer", D_800CA860);

INCLUDE_RODATA("maps/map2_s00/nonmatchings/Chara_AirScreamer", D_800CA870);

INCLUDE_RODATA("maps/map2_s00/nonmatchings/Chara_AirScreamer", D_800CA888);

INCLUDE_RODATA("maps/map2_s00/nonmatchings/Chara_AirScreamer", D_800CA8A0);

INCLUDE_RODATA("maps/map2_s00/nonmatchings/Chara_AirScreamer", D_800CA8B8);

INCLUDE_RODATA("maps/map2_s00/nonmatchings/Chara_AirScreamer", sharedData_800CAA98_0_s01);

#include "../src/maps/characters/air_screamer.c" // 0x800D1F40

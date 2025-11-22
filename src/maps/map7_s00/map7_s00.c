#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s00.h"
#include "maps/characters/Chara_Lisa.h"

INCLUDE_RODATA("asm/maps/map7_s00/nonmatchings/map7_s00", D_800C9578);

INCLUDE_RODATA("asm/maps/map7_s00/nonmatchings/map7_s00", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map7_s00/nonmatchings/map7_s00", func_800CB624);

#include "maps/shared/Player.h"
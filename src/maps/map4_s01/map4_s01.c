#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s01.h"

// TODO: Func declarations in header.

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB5F4_3_s05.h" // 0x800CC19C

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", sharedFunc_800CB71C_3_s05);

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", func_800CC70C);

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", func_800CCF50);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CD548

#include "maps/shared/Player.h"

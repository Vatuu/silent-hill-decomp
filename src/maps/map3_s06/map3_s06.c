#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s06.h"

INCLUDE_RODATA("asm/maps/map3_s06/nonmatchings/map3_s06", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s06/nonmatchings/map3_s06", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB2E0

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB8AC

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CB984

#include "maps/shared/Particle_Update.h" // 0x800CBC90

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CC260

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC71C

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CC86C

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CCC34

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CCD60

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CCD68

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CCE20

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CCEA8

#include "../src/maps/characters/player.c"

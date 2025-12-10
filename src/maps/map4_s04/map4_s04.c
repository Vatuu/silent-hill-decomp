#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s04.h"

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CBC60

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CC054

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CC12C

#include "maps/shared/Particle_Update.h" // 0x800CC448

#include "maps/shared/sharedFunc_800CEFF4_0_s00.h" // 0x800CCA70

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CD160

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CD1FC

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CD4E0

INCLUDE_ASM("asm/maps/map4_s04/nonmatchings/map4_s04", sharedFunc_800D0690_1_s03); // 0x800CD5A0

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CD6EC

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CD6F4

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CD7AC

#include "maps/shared/Player.h"
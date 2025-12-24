#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s02.h"
#include "maps/Characters/Chara_Creaper.h"

INCLUDE_RODATA("asm/maps/map3_s02/nonmatchings/map3_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s02/nonmatchings/map3_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CAB58

#include "maps/shared/Player.h"

#include "maps/shared/Ai_Creaper_Update.h" // 0x800CCA14

#include "maps/shared/Ai_Creaper_Init.h" // 0x800CCAA4

#include "maps/shared/sharedFunc_800D7EE8_1_s02.h" // 0x800CCD64

#include "maps/shared/sharedFunc_800D8244_1_s02.h" // 0x800CD0C0

#include "maps/shared/sharedFunc_800D82F0_1_s02.h" // 0x800CD16C

#include "maps/shared/sharedFunc_800D8684_1_s02.h" // 0x800CD500

#include "maps/shared/sharedFunc_800D8F30_1_s02.h" // 0x800CDDAC

#include "maps/shared/sharedFunc_800D9528_1_s02.h" // 0x800CE3A4

#include "maps/shared/sharedFunc_800D9774_1_s02.h" // 0x800CE5F0

#include "maps/shared/sharedFunc_800D983C_1_s02.h" // 0x800CE6B8

#include "maps/shared/sharedFunc_800D9960_1_s02.h" // 0x800CE7DC

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D99D0_1_s02); // 0x800CE84C

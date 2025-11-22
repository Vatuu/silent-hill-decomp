#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s02.h"

INCLUDE_RODATA("asm/maps/map3_s02/nonmatchings/map3_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s02/nonmatchings/map3_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CAB58

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CACC0

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CAE40

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CAEF8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CB05C

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CB07C

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CB8F4

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CBCE0

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CBFD4

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CC400

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CC43C

#include "maps/shared/Player_ControlFreeze.h" // 0x800CC448

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800CC5A8

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800CC780

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CC788

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CC838

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CC850

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CC878

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CC890

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CC8B8

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CC95C

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CC96C

#include "maps/shared/sharedFunc_800D2E6C_0_s00.h" // 0x800CC978

#include "maps/shared/sharedFunc_800D2E74_0_s00.h" // 0x800CC980

#include "maps/shared/sharedFunc_800D2E7C_0_s00.h" // 0x800CC988

#include "maps/shared/sharedFunc_800D2E84_0_s00.h" // 0x800CC990

#include "maps/shared/sharedFunc_800D2E8C_0_s00.h" // 0x800CC998

#include "maps/shared/sharedFunc_800D2E94_0_s00.h" // 0x800CC9A0

#include "maps/shared/sharedFunc_800D2E9C_0_s00.h" // 0x800CC9A8

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CC9B0

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CC9C0

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CCA00

#include "maps/shared/Ai_Creaper_Update.h" // 0x800CCA14

#include "maps/shared/Ai_Creaper_Init.h" // 0x800CCAA4

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D7EE8_1_s02); // 0x800CCD64

#include "maps/shared/sharedFunc_800D8244_1_s02.h" // 0x800CD0C0

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D82F0_1_s02); // 0x800CD16C

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D8684_1_s02); // 0x800CD500

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D8F30_1_s02); // 0x800CDDAC

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D9528_1_s02); // 0x800CE3A4

#include "maps/shared/sharedFunc_800D9774_1_s02.h" // 0x800CE5F0

#include "maps/shared/sharedFunc_800D983C_1_s02.h" // 0x800CE6B8

#include "maps/shared/sharedFunc_800D9960_1_s02.h" // 0x800CE7DC

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D99D0_1_s02); // 0x800CE84C


#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s02.h"

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CE5D4_1_s03.h" // 0x800CABA0

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CAC54);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CB31C);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CB484

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CB604

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CB6BC

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CB820

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CB840

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CC0B8

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CC4A4

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CCCF4

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CD120

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CD15C

#include "maps/shared/Player_ControlFreeze.h" // 0x800CD168

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800CD2C8

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800CD4A0

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CD4A8

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CD558

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CD570

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CD598

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CD5B0

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CD5D8

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CD67C

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CD68C

#include "maps/shared/sharedFunc_800D2E6C_0_s00.h" // 0x800CD698

#include "maps/shared/Player_FallBackward.h" // 0x800CD6A0

#include "maps/shared/sharedFunc_800D2E7C_0_s00.h" // 0x800CD6A8

#include "maps/shared/sharedFunc_800D2E84_0_s00.h" // 0x800CD6B0

#include "maps/shared/sharedFunc_800D2E8C_0_s00.h" // 0x800CD6B8

#include "maps/shared/sharedFunc_800D2E94_0_s00.h" // 0x800CD6C0

#include "maps/shared/sharedFunc_800D2E9C_0_s00.h" // 0x800CD6C8

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CD6D0

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CD6E0

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CD720

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s01.h"

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s01/nonmatchings/map6_s01", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CE5D4_1_s03.h" // 0x800CBB60

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01", func_800CBC14);

INCLUDE_ASM("asm/maps/map6_s01/nonmatchings/map6_s01", func_800CC2DC);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CC444

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CC5C4

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CC67C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CC7E0

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CC800

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CD078

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CD464

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CDABC

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CDEE8

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CDF24

#include "maps/shared/Player_ControlFreeze.h" // 0x800CDF30

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800CE090

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800CE268

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CE270

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CE320

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CE338

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CE360

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CE378

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CE3A0

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CE444

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CE454

#include "maps/shared/sharedFunc_800D2E6C_0_s00.h" // 0x800CE460

#include "maps/shared/sharedFunc_800D2E74_0_s00.h" // 0x800CE468

#include "maps/shared/sharedFunc_800D2E7C_0_s00.h" // 0x800CE470

#include "maps/shared/sharedFunc_800D2E84_0_s00.h" // 0x800CE478

#include "maps/shared/sharedFunc_800D2E8C_0_s00.h" // 0x800CE480

#include "maps/shared/sharedFunc_800D2E94_0_s00.h" // 0x800CE488

#include "maps/shared/sharedFunc_800D2E9C_0_s00.h" // 0x800CE490

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CE498

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CE4A8

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CE4E8

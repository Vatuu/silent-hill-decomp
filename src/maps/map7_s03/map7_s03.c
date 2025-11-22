#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s03.h"

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800C9578);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CD170

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CD608

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CD6E0

#include "maps/shared/Particle_Update.h" // 0x800CD9EC

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CDFAC

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CE358

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CEFD0_1_s02); // 0x800CE4A8

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CE820

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CE954

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CEA60

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CEB18

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CEBA0

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CED20

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CEDD8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CEF70

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CEF90

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CF808

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CFBF4

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800D0640

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D0A84

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D0AC0

#include "maps/shared/Player_ControlFreeze.h" // 0x800D0ACC

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800D0C2C

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800D0E04

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D0E0C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D0EBC

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D0ED4

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D0EFC

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D0F14

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D0F3C

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D0FE0

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D0FF0

#include "maps/shared/sharedFunc_800D2E6C_0_s00.h" // 0x800D0FFC

#include "maps/shared/sharedFunc_800D2E74_0_s00.h" // 0x800D1004

#include "maps/shared/sharedFunc_800D2E7C_0_s00.h" // 0x800D100C

#include "maps/shared/sharedFunc_800D2E84_0_s00.h" // 0x800D1014

#include "maps/shared/sharedFunc_800D2E8C_0_s00.h" // 0x800D101C

#include "maps/shared/sharedFunc_800D2E94_0_s00.h" // 0x800D1024

#include "maps/shared/sharedFunc_800D2E9C_0_s00.h" // 0x800D102C

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D1034

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D1044

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D1084


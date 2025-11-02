#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s00.h"

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800C9578);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CD5C0

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CDC3C

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CDD14

#include "maps/shared/Particle_Update.h" // 0x800CE020

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800CEB24_0_s00); // 0x800CEA04

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF02C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800CEFD0_1_s02); // 0x800CF17C

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CF544

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF670

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF678

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF730

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CF7B8

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CF970

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CFAF0

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CFBA8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CFD40

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CFD60

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800D05D8

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800D09C4

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800D0DC4

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D1214

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D1250

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D125C

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D13BC

s32 func_800D1594()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D159C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D164C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D1664

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D168C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D16A4

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D16CC

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D1770

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D1780

void func_800D178C(void) {}

void func_800D1794(void) {}

void func_800D179C(void) {}

void func_800D17A4(void) {}

void func_800D17AC(void) {}

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D17B4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D1A64);

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D1EDC

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D1EEC

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D1F2C

#include "maps/shared/Ai_AirScreamer_Update.h" // 0x800D1F40

#include "maps/shared/sharedFunc_800D21E4_0_s01.h" // 0x800D1FB4

#include "maps/shared/sharedFunc_800D2200_0_s01.h" // 0x800D1FD0

#include "maps/shared/sharedFunc_800D2274_0_s01.h" // 0x800D2044

#include "maps/shared/sharedFunc_800D2364_0_s01.h" // 0x800D2134

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D2390_0_s01); // 0x800D2160

#include "maps/shared/Ai_AirScreamer_Init.h" // 0x800D2744

#include "maps/shared/sharedFunc_800D2B00_0_s01.h" // 0x800D28D0

#include "maps/shared/sharedFunc_800D2B10_0_s01.h" // 0x800D28E0

#include "maps/shared/sharedFunc_800D2B28_0_s01.h" // 0x800D28F8

#include "maps/shared/sharedFunc_800D2B4C_0_s01.h" // 0x800D291C

#include "maps/shared/sharedFunc_800D2BB0_0_s01.h" // 0x800D2980

#include "maps/shared/sharedFunc_800D2BE4_0_s01.h" // 0x800D29B4

#include "maps/shared/sharedFunc_800D2BF4_0_s01.h" // 0x800D29C4

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", Chara_DamageTake); // 0x800D29DC

#include "maps/shared/sharedFunc_800D2E04_0_s01.h" // 0x800D2BE0

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D2D90);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D31D0_0_s01); // 0x800D2FAC

#include "maps/shared/sharedFunc_800D3430_0_s01.h" // 0x800D320C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D3508_0_s01); // 0x800D32E4

#include "maps/shared/sharedFunc_800D3630_0_s01.h" // 0x800D340C

#include "maps/shared/sharedFunc_800D3758_0_s01.h" // 0x800D3534

#include "maps/shared/sharedFunc_800D3814_0_s01.h" // 0x800D35F0

#include "maps/shared/sharedFunc_800D3928_0_s01.h" // 0x800D3704

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA860);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA864);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA870);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA888);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA8A0);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA8B8);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", sharedData_800CAA98_0_s01);

#include "maps/shared/sharedSymbol_800D3B0C_0_s01.h" // 0x800D37D0

#include "maps/shared/sharedFunc_800D3CC4_0_s01.h" // 0x800D3A30

#include "maps/shared/sharedFunc_800D3DFC_0_s01.h" // 0x800D3B68

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D3C24);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D3E44);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D3FA4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D4358);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D46C8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D4A9C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D4E78);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D5268);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D5554);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D5974);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D5B88);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D5DAC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D603C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D6400);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D6504);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D69A0);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D6A7C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D6E28);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D71A4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D756C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D794C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D7D0C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D80EC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D83F8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D8618);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D8888);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D8C34);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D8D44);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D91A0);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D92B4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D93E8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D94EC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D98DC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D9C60);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DA0D4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DA598);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DA900);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DACA8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DB038);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DB220);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DB54C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DB8AC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DB9B8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DBDEC);

void func_800DBEEC(void) {}

void func_800DBEF4(void) {}

void func_800DBEFC(void) {}

void func_800DBF04(void) {}

void func_800DBF0C(void) {}

void func_800DBF14(void) {}

#include "maps/shared/sharedFunc_800D4A80_0_s01.h" // 0x800DBF1C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DBF88);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC0A8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC0E4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC200);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC30C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC3BC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC438);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC50C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC598);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC67C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC6E4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC894);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DC98C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D4E84_0_s01); // 0x800DCD24

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800DD114

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD13C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD2C4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD4A4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD4EC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD534);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD588);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD834);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DDA80);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DDE14);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DDF74);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DE034);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DE11C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DE1F8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DE250);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DE578);

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800DE598

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DE6A8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DE7E0);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DE940);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DEBCC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DEC64);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DEC84);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DECA4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DECC4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DEE24);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF22C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF24C);

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800DF26C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF2D0);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF358);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF448);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF60C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF710);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF80C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF8A0);

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800DF950

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800DFA7C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DFC40);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DFDC4);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DFF44);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E0034);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E00C8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E012C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E021C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E041C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E04B0);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E0514);

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800E0610

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E0698);

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800E0A70

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800E0AD4

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800E0B3C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D6600_0_s01); // 0x800E0D98

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800E11F8

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800E1414

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D6EC4_0_s01);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D7120_0_s01); // 0x800E18B8

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800E1988

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D72E8_0_s01);

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800E1BD8

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800E1CF8

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800E1E38

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E1EAC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D77D0_0_s01); // 0x800E1F68

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800E2248

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D7B14_0_s01);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D7EBC_0_s01); // 0x800E2620

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800E2914

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D81D0_0_s01); // 0x800E2934

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D8244_0_s01); // 0x800E29A8

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D82B8_0_s01); // 0x800E2A1C

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800E2E78

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800E2F60

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E2F68);

#include "maps/shared/Ai_Groaner_Update.h" // 0x800E2F78

#include "maps/shared/Ai_Groaner_Init.h" // 0x800E3074 - `map2_s00` includes extra block at end of function compared to other maps.

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E33DC_2_s00); // 0x800E33DC

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E384C_2_s00); // 0x800E384C - `map2_s00` version differs to the 4 other maps which share `Ai_Groaner_Update`.

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E39D8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E3E94);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E4830);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E4E84);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E554C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E55B0);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E5930);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E5AA4_2_s00); // 0x800E5AA4

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E5EC4_2_s00); // 0x800E5EC4

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E6338_2_s00); // 0x800E6338

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E71E8_2_s00); // 0x800E71E8

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E76B8

#include "maps/shared/Map_RoomIdxGet.h" // 0x800E76C8

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E7914);

void func_800E7A1C(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800E7A24

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800E7AB8

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tThere_is_a_ ~C2 Steel_pipe ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tWhere_could_Cheryl_have_gone? ",
    "\tI_guess_I'll_check ~N\n\tthat_alley_again. ~E ",
    "~C3\tTo_school ~E ",
    "~J1(2.5)\n\tIsn't_this ~N\n\tCheryl's_sketchbook? ",
    "~J1(3.8)\n\tHmm... ~N\n\tShe's_at_the_school... ~E ",
    "\tSketchbook_cover. ~N\n\tThis_picture..._it's_me. ",
    "\tThe_first_picture_that_Cheryl ~N\n\tdrew_in_the_sketchbook_that_I ~N\n\tgave_on_her_5th_birthday. ~E ",
    "~M ~C3\tDoghouse ~N\n\t\tLevin_st. ~E ",
    "\tNothing_unusual. ~E ",
    "\tProbably_a_doghouse, ~N\n\tthough_I'm_not_sure ~N\n\tsince_there's_no_dog_around. ",
    "\tNothing_in_particular_around. ~E ",
    "\t~C2 House_key ~C7 _was_hidden ~N\n\tin_the_dog_house._Take_it? ~S4 ",
    "\tThere_is_a_ ~C2 Key_of_[Lion] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Key_of_[Woodman] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Key_of_[Scarecrow] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tUsed_the_ ~C2 House_key ~C7 . ~E ",
    "\tUsed_the_ ~C2 Key_of_[Lion] ~C7 . ~E ",
    "\tUsed_the_ ~C2 Key_of_[Woodman] ~C7 . ~E ",
    "\tUsed_the_ ~C2 Key_of_[Scarecrow] ~C7 . ~E ",
    "~J0(20)\tWhat? ~E ",
    "\tIt's_getting_dark_again? ",
    "\tWhat's_going_on!? ~E ",
    "\tA_dog's_head... ~E ",
    "\tUsed_the_ ~C2 K._Gordon_key ~C7 . ~E ",
    "~C3\tMidwich_Elementary_School ~E ",
    "\tNo_reason_to_search ~N\n\tthe_school_anymore. ~E ",
    "~C3\tOrridge_Bridge_Control_Room ~E ",
    "\tThere's_a_keyhole ~N\n\ton_the_control_panel. ~E ",
    "\tThe_machinery_is_running. ~N\n\tDo_you_want_to_press_the_switch? ~S4 ",
    "\tThe_street_is_blocked. ~N\n\tCan't_get_out_of_town_through_here. ~E ",
    "\tMy_car... ~N\n\ttoo_banged_up_to_drive. ",
    "\tWhere's_Cheryl? ~N\n\tHope_she's_safe. ~E ",
    "~C3\tOrridge_Bridge_Control_Room ~E ",
    "~C3\tReservoir. ~N\n\t\tAuthorized_Personnel_only. ~E ",
    "\tHmm..._the_lock_is_worn_out. ",
    "\tI_may_be_able_to_break_it ~N\n\tif_I_hit_it_hard. ~E ",
    "\tSomething_is_written_on_the_map ~N\n\thanging_on_the_wall. ",
    "\tCopied_it_to_the_map. ~E ",
    "\tSomething_is_written_on_the_map ~N\n\thanging_on_the_wall. ~E ",
    " ",
    "\tThere_are_three_locks. ~E ",
    "\tThere_are_two_locks. ~E ",
    "\tThere_is_one_lock. ~E ",
    "\tIt's_unlocked. ~E ",
    "~H\tThere_is_a_ ~C5 Shopping_district_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_special. ~E ",
    "\tThe_drawbridge_is_operating. ~E ",
    "\tThe_drawbridge_is_stopped. ~E ",
    "\tThere's_a_TV_set. ~N\n\tThe_power_must_be_out. ~N\n\tIt_doesn't_work. ~E ",
    "\tNothing_useful. ~E ",
    "\tNothing_special. ~E ",
    "\tThe_refrigerator_is_empty. ~E ",
    "\tThe_garage_door_is_smeared ~N\n\twith_blood. ~E ",
    "~C3\tK._Gordon ~E ",
    "~C3\tBalkan_Church ~E ",
    "\tThere_is_a_ ~C2 Rock_drill ~C7 . ",
    "\tThere_is_no_gasoline. ~N\n\tCan't_use_it. ~E ",
    "\tThere_is_a_ ~C2 Rock_drill ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Chainsaw ~C7 . ",
    "\tThere_is_no_gasoline. ~N\n\tCan't_use_it. ~E ",
    "\tThere_is_a_ ~C2 Chainsaw ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tUsed_the_gasoline. ~E ",
    "\tThis_must_be_that_water_works ~N\n\tLisa_was_talking_about. ~E "
};

void func_800E7B74(void) // 0x800E7B74
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 139:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit0;
            break;

        case 140:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets0;
            break;

        case 141:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets1;
            break;

        case 142:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink0;
            break;

        case 143:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets2;
            break;

        case 144:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M2S00_ShotgunShells0;
            break;

        case 145:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink1;
            break;

        case 146:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets3;
            break;

        case 147:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets4;
            break;

        case 148:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets5;
            break;

        case 149:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets6;
            break;

        case 150:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets7;
            break;

        case 151:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets8;
            break;

        case 152:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink2;
            break;

        case 153:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink3;
            break;
        case 154:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink4;
            break;

        case 155:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets9;
            break;

        case 156:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink5;
            break;

        case 157:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets10;
            break;

        case 158:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink6;
            break;

        case 159:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink7;
            break;

        case 160:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink8;
            break;

        case 161:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink9;
            break;

        case 162:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink10;
            break;

        case 163:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink11;
            break;

        case 164:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M2S00_ShotgunShells1;
            break;

        case 165:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit1;
            break;

        case 166:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets11;
            break;

        case 167:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets12;
            break;

        case 168:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets13;
            break;

        case 169:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets14;
            break;

        case 170:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit2;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800E7D54(void) // 0x800E7D54
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
    {
        // Breaks if there are any characters with IDs in range `[Chara_Harry, Chara_MonsterCybil]` with health above `Q12(0.0f)`.
        if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry &&
            g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil &&
            g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f))
        {
            break;
        }
    }

    if (i != ARRAY_SIZE(g_SysWork.npcs_1A0))
    {
        g_DeltaTime0 = Q12(0.0f);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            MapMsg_DisplayAndHandleSelection(false, 46, 0, 0, 0, false);
            break;

        case 2:
            Event_ItemTake(InventoryItemId_HealthDrink, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupHealthDrink, 6);
            break;
    }
}

void MapEvent_AtWaterWorks(void) // 0x800E7E60
{
    s32 sysState0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-255.78f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-107.46f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(-45.0f);

            ScreenFade_ResetTimestep();
            func_800867B4(0, 1);
            func_800EB824(1);
            SysWork_StateStepIncrement(0);

        case 1:
        case 2:
        case 3:
            func_800692A4(0, 120, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 120, Q12(0.5f));
            func_80067914(1, 0, 120, Q12(0.5f));

            sysState0 = g_SysWork.sysStateStep_C[0];
            switch (sysState0)
            {
                case 2:
                    SysWork_StateStepIncrementDelayed(Q12(3.5f), false);

                    if (g_SysWork.sysStateStep_C[0] == sysState0 &&
                        (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                          g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
                    {
                        SysWork_StateStepSet(0, 3);
                    }
                    break;

                case 3:
                    SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.0f), false);
                    break;

                case 1:
                    SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
                    break;
            }
            break;

        case 4:
            g_SysWork.field_30 = 20;

            func_800867B4(2, 0);
            Camera_PositionSet(NULL, Q12(-254.15f), Q12(-1.95f), Q12(-109.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-257.0398f), Q12(-1.94f), Q12(-106.54f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
            break;

        case 6:
            MapMsg_DisplayAndHandleSelection(false, 78, 0, 0, 0, false); // "This must be the water works."
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_M2S00_WaterWorksCutscene);

            g_SysWork.flags_22A4 &= ~(1 << 4);
            break;
    }
}

void func_800E816C(void) // 0x800E816C
{
    Event_ItemTake(InventoryItemId_RockDrill, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupRockDrill, 73);
}

void func_800E8198(void) // 0x800E8198
{
    Event_ItemTake(InventoryItemId_Chainsaw, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupChainsaw, 76);
}

void MapEvent_MapTake(void) // 0x800E81C4
{
    Event_MapTake(2, EventFlag_M2S00_PickupMap, 60);
}

void MapEvent_SteelPipeTake(void) // 0x800E81EC
{
    #define STATE_TAKE_STEEL_PIPE      5
    #define STATE_DONT_TAKE_STEEL_PIPE 6

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0u, InventoryItemId_SteelPipe, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            func_80086470(1, InventoryItemId_SteelPipe, 0, false);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_M2S00_PickupSteelPipe);

            if (Gfx_PickupItemAnimate(InventoryItemId_SteelPipe))
            {
                MapMsg_DisplayAndHandleSelection(true, 15, STATE_TAKE_STEEL_PIPE, STATE_DONT_TAKE_STEEL_PIPE, 0, false);
            }
            break;

        case STATE_TAKE_STEEL_PIPE:
            func_80086470(3, InventoryItemId_SteelPipe, 1, false);
            SysWork_StateStepSet(0, 7);
            break;

        case STATE_DONT_TAKE_STEEL_PIPE:
            Savegame_EventFlagClear(EventFlag_M2S00_PickupSteelPipe);
            SysWork_StateStepIncrement(0);

        case 7:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_CutsceneExitCafe(void) // 0x800E83C0
{
    s32 zoomX;
    s32 zoomZ;
    s32 zoomHuh;
    s16 curve;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] == 2)
        {
            SysWork_StateStepSet(0, 13);
        }
        else
        {
            if (!D_800F228E)
            {
                if (g_SysWork.sysStateStep_C[0] > 5)
                {
                    if (g_SysWork.sysStateStep_C[0] < 11)
                    {
                        SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                        D_800F228E = 1;
                    }
                }
            }
        }
    }

    if (D_800F228E)
    {
        if (ScreenFade_IsFinished())
        {
            D_800F228E = 0;
            SysWork_StateStepSet(0, 12);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            g_SysWork.field_30 = 20;
            D_800F228C = 0;
            D_800F2290 = 0;

            Savegame_MapMarkingSet(MapMarkFlag_OldTown_CofeArrowOnly);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_CofeSignOnly);

            D_800F228E = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            Camera_PositionSet(NULL, Q12(15.54f), Q12(-1.5f), Q12(55.64f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(19.42f), Q12(-1.75f), Q12(56.6f), 0, 0, 0, 0, true);
            SysWork_StateStepIncrement(0);

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false); // "Where could Cheryl have gone?"
            break;

        case 3:
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 5:
            func_800867B4(0, 1);
            SysWork_StateStepIncrement(0);

        case 6:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 7:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));

            D_800F228C += 0x20;

            func_80088370(D_800F228C, -0xA0, -0xE0, 0x13F, 0x1BF, -0x58, -0xC0, 0x9F, 0xDF);

            if (D_800F228C == 0x1000)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            // Decrement zoom counter.
            D_800F228C -= 0x40;
                 
            func_800692A4(0x48 - FP_MULTIPLY_PRECISE(D_800F228C, 0x48, Q12_SHIFT),
                          0x10 - FP_MULTIPLY_PRECISE(D_800F228C, 0x10, Q12_SHIFT),
                          ((D_800F228C >> 1) + 0x800));

            func_80068E0C(1, 1, 0, 0,
                          0x48 - FP_MULTIPLY_PRECISE(D_800F228C, 0x48, Q12_SHIFT),
                          0x10 - FP_MULTIPLY_PRECISE(D_800F228C, 0x10, Q12_SHIFT),
                          ((D_800F228C >> 1) + 0x800));

            curve = (FP_TO(D_800F228C, 12) / (D_800F228C + Q12(1.0f))) * -1;

            func_80088370(curve, -0xA0, -0xE0, 0x13F, 0x1BF, -0x10, -0xA0, 0, 0);

            if (D_800F228C == 0)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 9:
            func_800692A4(0x48, 0x10, 0x800);
            func_80068E0C(1, 1, 0, 0, 0x48, 0x10, 0x800);
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 10:
            func_800692A4(0x48, 0x10, 0x800);
            func_80068E0C(1, 1, 0, 0, 0x48, 0x10, 0x800);
            func_80068E0C(2, 1, 0x36A, D_800F2290, 0x48, 0x10, 0x800);
            D_800F2290++;

            if (D_800F2290 >= 0x80)
            {
                if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
                {
                    SysWork_StateStepIncrement(0);
                }

                SysWork_StateStepIncrementDelayed(Q12(1.5f), false);

                if (g_SysWork.sysStateStep_C[0] > 11)
                {
                    g_SysWork.sysStateStep_C[0] = 11;
                }

                D_800F2290 = 0x80;
            }
            break;

        case 11:
            func_800692A4(0x48, 0x10, 0x800);
            func_80068E0C(1, 1, 0, 0, 0x48, 0x10, 0x800);
            func_80068E0C(2, 1, 0x36A, 0x80, 0x48, 0x10, 0x800);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 12:
            func_800867B4(2, 0);
            D_800F228E = 0;
            SysWork_StateStepIncrement(0);

        case 13:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 14:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_CherylArrowAndSign);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            g_SysWork.flags_22A4 &= ~(1 << 4);

            func_8003A16C();
            break;
    }
}

void MapEvent_CherylsSketchbook(void) // 0x800E8C0C
{
    s16 curve;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (!D_800F2295)
        {
            if (g_SysWork.sysStateStep_C[0] > 1 && g_SysWork.sysStateStep_C[0] < 10)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                D_800F2295 = 1;
            }
            else if (g_SysWork.sysStateStep_C[0] > 10 && g_SysWork.sysStateStep_C[0] < 16)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                D_800F2295 = 2;
            }
        }
    }

    if (D_800F2295)
    {
        if (ScreenFade_IsFinished())
        {
            if (D_800F2295 == 1)
            {
                SysWork_StateStepSet(0, 21);
            }
            else
            {
                SysWork_StateStepSet(0, 22);
            }

            D_800F2295 = 0;
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Savegame_MapMarkingSet(MapMarkFlag_11);
            func_800862F8(0, FILE_TIM_TOSCHOOL_TIM, false);

            g_MapMsgSoundIdx = 0;
            D_800F2298 = 0;
            D_800F229C = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 18, 0, 0, 0, false); // "To school."
            break;

        case 7:
            g_BackgroundColor = 48;

            func_800862F8(2, 0, false);
            Map_MessageWithAudio(19, &g_MapMsgSoundIdx, &g_MapMsgSounds); // "Isn't this Cheryl's sketchbook?"
            break;

        case 8:
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement(0);

        case 9:
            g_BackgroundColor = 48;

            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 10:
            func_800867B4(0, 1);
            Savegame_EventFlagSet(EventFlag_147);
            SysWork_StateStepIncrement(0);

        case 11:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 12:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            D_800F229C += 0x20;
            func_80088370(D_800F229C, -0xA0, -0xE0, 0x13F, 0x1BF, -0xA0, 8, 0x9F, 0xDF);

            if (D_800F229C == Q12(1.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 13:
            // Decrement zoom counter.
            D_800F229C -= 0x40;
                 
            func_800692A4(0,
                          0x74 - FP_MULTIPLY_PRECISE(D_800F229C, 0x74, 12),
                          ((D_800F229C >> 1) + 0x800));

            func_80068E0C(1, 1, 0, 0, 0,
                          0x74 - FP_MULTIPLY_PRECISE(D_800F229C, 0x74, 12),
                          ((D_800F229C >> 1) + 0x800));

            curve = (FP_TO(D_800F229C, 12) / (D_800F229C + Q12(1.0f))) * -1;

            func_80088370(curve, -0xA0, -0xE0, 0x13F, 0x1BF, -0xA0, 0xF0, 0, 0);

            if (D_800F229C == 0)
            {
                SysWork_StateStepIncrement(0);
                break;
            }
            break;

        case 14:
            func_800692A4(0, 0x74, 0x800);
            func_80068E0C(1, 1, 0, 0, 0, 0x74, 0x800);
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);

            break;
        case 15:
            func_800692A4(0, 0x74, 0x800);
            func_80068E0C(1, 1, 0, 0, 0, 0x74, 0x800);
            func_80068E0C(2, 1, 0x3A2, D_800F2298, 0, 0x74, 0x800);

            D_800F2298++;

            if (D_800F2298 >= 0x80)
            {
                if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
                {
                    SysWork_StateStepIncrement(0);
                }

                SysWork_StateStepIncrementDelayed(Q12(1.5f), false);

                if (g_SysWork.sysStateStep_C[0] > 16)
                {
                    g_SysWork.sysStateStep_C[0] = 16;
                }

                D_800F2298 = 0x80;
            }
            break;

        case 16:
            func_800692A4(0, 0x74, 0x800);
            func_80068E0C(1, 1, 0, 0, 0, 0x74, 0x800);
            func_80068E0C(2, 1, 0x3A2, 0x80, 0, 0x74, 0x800);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 17:
            func_800867B4(2, 0);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_SchoolCircle);

            D_800F2295 = 0;

            SysWork_StateStepIncrement(0);

        case 18:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 19:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        case 22:
            func_800867B4(2, 0);

        case 21:
            Savegame_EventFlagSet(EventFlag_147);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_SchoolCircle);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80086470(3, InventoryItemId_NoteToSchool, 1, false);
            func_8003A16C();
            break;
    }
}

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E9470);

void MapEvent_DoghouseNote(void) // 0x800E95F8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_800862F8(0, FILE_TIM_STKENNEL_TIM, false);
            SysWork_StateStepIncrement(0);
            
        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            Savegame_EventFlagSet(EventFlag_M2S00_DogHouseNoteFound);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 23, 0, 0, 0, false); // "Doghouse Levin St."
            break;

        case 7:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 9:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80086470(3, InventoryItemId_NoteDoghouse, 1, false);
            break;
    }
}

void MapEvent_DoghouseKeyTake(void) // 0x800E97E4
{
    #define STATE_TAKE_KEY      8
    #define STATE_DONT_TAKE_KEY 9

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_800862F8(0, FILE_TIM_INKENNEL_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrement(0);

        case 7:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(true, 27, STATE_TAKE_KEY, STATE_DONT_TAKE_KEY, 0, false); // "House Key in doghouse. Take it?"
            break;

        case STATE_TAKE_KEY:
            func_80086470(3, InventoryItemId_HouseKey, 1, false);
            Savegame_EventFlagSet(EventFlag_M2S00_PickupDogHouseKey);
            Player_ItemRemove(InventoryItemId_NoteDoghouse, 1);
            SysWork_StateStepIncrement(0);

        case STATE_DONT_TAKE_KEY:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 10:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 11:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
        }
}

void func_800E9A0C(void) // 0x800E9A0C
{
    Event_ItemTake(InventoryItemId_KeyOfLion, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupKeyOfLion, 28);

    if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfLion))
    {
        if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_FineyStRightKeyArrow))
        {
            Savegame_MapMarkingSet(MapMarkFlag_53);
        }
    }
}

void func_800E9A74(void) // 0x800E9A74
{
    #define STATE_TAKE_KEY      6
    #define STATE_DONT_TAKE_KEY 7

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0, InventoryItemId_KeyOfWoodman, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 59, false);
            SysWork_StateStepIncrement(0);

        case 3:
            func_80086470(1, InventoryItemId_KeyOfWoodman, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            break;

        case 5:
            if (Gfx_PickupItemAnimate(InventoryItemId_KeyOfWoodman))
            {
                MapMsg_DisplayAndHandleSelection(true, 29, STATE_TAKE_KEY, STATE_DONT_TAKE_KEY, 0, false); // "Key of Woodman. Take it?"
            }

            Savegame_EventFlagSet(EventFlag_M2S00_PickupKeyOfWoodman);
            break;

        case STATE_TAKE_KEY:
            func_80086470(3, InventoryItemId_KeyOfWoodman, 1, false);

            if (g_SavegamePtr->mapMarkingFlags_1D4[1] & 0x400000)
            {
                g_SavegamePtr->mapMarkingFlags_1D4[1] |= 0x800000;
            }

            SysWork_StateStepSet(0, 8);
            break;

        case STATE_DONT_TAKE_KEY:
            Savegame_EventFlagClear(EventFlag_M2S00_PickupKeyOfWoodman);
            SysWork_StateStepIncrement(0);

        case 8:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
        }
}

void func_800E9CB4(void) // 0x800E9CB4
{
    Event_ItemTake(InventoryItemId_KeyOfScarecrow, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupKeyOfScarecrow, 30);

    if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfScarecrow))
    {
        if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_EllroyStKeyCircle))
        {
            Savegame_MapMarkingSet(MapMarkFlag_57);
        }
    }
}

void MapEvent_HouseKeyUse(void) // 0x800E9D1C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_HouseKey, 1);
    Map_MessageWithSfx(31, Sfx_UseKey, &sfxPos); // "Used the House Key."
    Savegame_MapMarkingSet(MapMarkFlag_OldTown_DoghouseDotOnly);
}

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E9DD8);

void MapEvent_DoorOfEclipseEnter(void) // 0x800EA444
{
    s32 tmp;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8003ED74(1, 1);
            func_8003EF10(6, 6, PrimitiveType_S32, &D_800F1A24, 0, Q12(100.0f));

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(147.7f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(376.5f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = Q12(-0.25f);
            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= 1 << 3;

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            g_SysWork.field_28 += g_DeltaTime0;
            tmp = Q12(1.0f) - Math_Cos(g_SysWork.field_28/12);
            D_800F1A24 = FP_MULTIPLY_PRECISE(tmp, Q12(60.0f), Q12_SHIFT) + Q12(40.0f);

            if (g_SysWork.field_28 > Q12(1.5f) && g_SysWork.field_28 < Q12(4.5f))
            {
                MapMsg_DisplayAndHandleSelection(false, 35, 0, 0, 0, false); // "What? It's getting dark again?"
            }

            SysWork_StateStepIncrementDelayed(Q12(6.0f), false);
            break;

        case 2:
            D_800F1A24 = Q12(100.0f);

            Game_TurnFlashlightOff();
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 36, 0, 0, 0, false);
            break;

        case 4:
            func_8003ED74(6, 3);
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_159);

            vcReturnPreAutoCamWork(false);
            break;
    }
}

void func_800EA6E0(void) // 0x800EA6E0
{
    // TODO: Probably inaccurate. Need to figure out what the unknown functions are doing.
    typedef enum _EventState
    {
        EventState_Setup       = 0,
        EventState_FadeOutGame = 1,
        EventState_Load        = 2, // TODO: Something else?
        EventState_FadeInMap   = 3,
        EventState_Msg         = 4,
        EventState_FadeOutMap  = 5,
        EventState_Finish      = 6
    } e_EventState;

    g_BackgroundColor = 72;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case EventState_Setup:
            sharedFunc_800D20E4_0_s00();
            func_800862F8(0, FILE_TIM_KEYMAP_TIM, false);
            SysWork_StateStepIncrement(0);

        case EventState_FadeOutGame:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case EventState_Load:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case EventState_FadeInMap:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case EventState_Msg:
            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_FineyStRightKeyArrow))
            {
                MapMsg_DisplayAndHandleSelection(false, 54, 0, 0, 0, false); // "Something is written on the map on the wall.{E}"
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 52, 0, 0, 0, false); // "... Copied it to the map."
            }

            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case EventState_FadeOutMap:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default: // `EventState_Finish`
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            Savegame_MapMarkingSet(MapMarkFlag_OldTown_FineyStRightKeyArrow);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_DogYardKeyLine);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_EllroyStKeyCircle);
            break;
        }
}

void MapEvent_KGordonKeyUse(void) // 0x800EA894
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_KGordonKey, 1);
    Map_MessageWithSfx(39, Sfx_UseKey, &sfxPos); // "Used the K. Gordon key."

    Savegame_EventFlagSet(EventFlag_M2S00_KGordonDoorOpen);
    g_SavegamePtr->mapMarkingFlags_1D4[1] |= 0x40000;
}

void func_800EA960(void)
{
    s32 vol;
    s32 balance;
    s16 time;
    #define STATE_PRESS_SWITCH      5
    #define STATE_DONT_PRESS_SWITCH NO_VALUE

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 1:
            func_80085DF0();
            break;
        case 2:
            func_8005DC1C(Sfx_Unk1481, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8_CLAMPED(0.5f), 0);
            Savegame_EventFlagSet(EventFlag_164);
            Sd_EngineCmd(Sfx_Unk1482);
            D_800F534C = -1;
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 3:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;
        case 4:
            g_SysWork.silentYesSelection_2350_4 = true;
            // The machinery is running. Do you want to press the switch?
            MapMsg_DisplayAndHandleSelection(true, 44, STATE_PRESS_SWITCH, STATE_DONT_PRESS_SWITCH, 0, false);
            break;
        case STATE_PRESS_SWITCH:
            func_8005DC1C(Sfx_Unk1483, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 6:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;
        case 7:
            Sd_EngineCmd(Sfx_Unk1484);
            D_800F534E = 0;
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 8:
            D_800F534E += ((u16)g_DeltaTime0 * 4);
            if (D_800F534E > Q12(1.0f))
            {
                D_800F534E = Q12(1.0f);
            }

            balance = Sound_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f));
            if ((Q8_CLAMPED(1.0f) - (D_800F534E >> 4)) >= 0)
            {
                vol = ~(D_800F534E >> 4) & Q8_CLAMPED(1.0f);
            }
            else
            {
                vol = 0;
            }
            func_800463C0(Sfx_Unk1484, balance, vol, 0);

            D_800F5344[2] += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x88, Q12_SHIFT);
            if (D_800F5344[2] > 0)
            {
                D_800F5344[2] = 0;
                func_8004690C(Sfx_Unk1484);
                Sd_PlaySfx(Sfx_Unk1485, Sound_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f)), 0);
                SysWork_StateStepIncrement(0);
            }
            break;
        case 9:
            Savegame_EventFlagSet(EventFlag_165);
            Savegame_EventFlagSet(EventFlag_166);
            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_BotBridgeCross))
            {
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotBridgeCorrection);
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotBridgeArrow);
            }
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            break;
    }
    if (Savegame_EventFlagGet(EventFlag_164))
    {
        if (g_SysWork.sysStateStep_C[0] > 4)
        {
            func_800894B8(0x90);
        }
        else
        {
            func_800894B8(0x70);
        }
    }
}

void func_800EAD2C(void) // 0x800EAD2C
{
    #define STATE_PRESS_SWITCH      3
    #define STATE_DONT_PRESS_SWITCH NO_VALUE

    s32 vol;
    s32 balance;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;
        case 2:
            g_SysWork.silentYesSelection_2350_4 = true;

            // "The machinery is running. Do you want to press the switch?"
            MapMsg_DisplayAndHandleSelection(true, 44, STATE_PRESS_SWITCH, STATE_DONT_PRESS_SWITCH, 0, false);
            break;

        case STATE_PRESS_SWITCH:
            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            SysWork_StateStepIncrement(0);

        case 4:
            func_8005DC1C(Sfx_Unk1483, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 6:
            Sd_EngineCmd(Sfx_Unk1484);
            D_800F534E = 0;
            SysWork_StateStepIncrement(0);

        case 7:
            D_800F534E += g_DeltaTime0;
            if (D_800F534E > Q12(1.0f))
            {
                D_800F534E = Q12(1.0f);
            }

            balance = Sound_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f));
            if ((Q8_CLAMPED(1.0f) - (D_800F534E >> 4)) >= 0)
            {
                vol = ~(D_800F534E >> 4) & Q8_CLAMPED(1.0f);
            }
            else
            {
                vol = 0;
            }

            func_800463C0(Sfx_Unk1484, balance, vol, 0);

            D_800F5344[2] += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x88, Q12_SHIFT);
            if (D_800F5344[2] > 0)
            {
                D_800F5344[2] = 0;
                func_8004690C(Sfx_Unk1484);
                Sd_PlaySfx(Sfx_Unk1485, Sound_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f)), 0);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            Savegame_EventFlagSet(EventFlag_165);
            Savegame_EventFlagSet(EventFlag_166);
            
            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_BotBridgeCross))
            {
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotBridgeCorrection);
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotBridgeArrow);
            }

            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            SysWork_StateStepIncrement(0);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    if (g_SysWork.sysStateStep_C[0] > 3)
    {
        func_800894B8(0x90);
    }
    else
    {
        func_800894B8(0x70);
    }
}

void func_800EB090(void) // 0x800EB090
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 61, 0, 0, 0, false); // "Nothing special."
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    func_800894B8(96);
}

void func_800EB174(void)
{
    VECTOR3 soundPos;
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            soundPos.vx = MAP_POINTS[g_MapEventParam->field_5].positionX_0;
            soundPos.vy = Q12(-1.2f);
            soundPos.vz = MAP_POINTS[g_MapEventParam->field_5].positionZ_8;
    
            func_8005DC1C(Sfx_Unk1349, &soundPos, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;
        case 2:
            func_80085DF0();
            break;
        case 3:
            MapMsg_DisplayAndHandleSelection(false, MapMsgIdx_DoorLocked, false, false, 0, false);
            break;
        case 4:
            Camera_PositionSet(NULL, Q12(-261.27f), Q12(-2.11f), Q12(-105.46f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(-262.74f), Q12(0.07f), Q12(-102.45f), 0, 0, 0, 0, true);
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-262.39f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-104.33f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(45.0f);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 2, false, false);
            break;
        case 6:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;
        case 7:
            MapMsg_DisplayAndHandleSelection(false, 50, false, false, 0, false); // "Hmm... the lock is worn out."
            break;
        case 8:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;
        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            Savegame_EventFlagSet(EventFlag_167);
            SysWork_StateStepIncrementAfterFade(false, false, 2, false, false);
            break;
    }
}

void func_800EB3F4(void) // 0x800EB3F4
{
    const static VECTOR3 D_800CD45C = { Q12(-261.977f), Q12(-0.1f),  Q12(-104.286f) };
    const static VECTOR3 D_800CD468 = { Q12(-263.0f),   Q12(-1.25f), Q12(-104.0f)   };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8005DC1C(Sfx_Unk1393, &D_800CD45C, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            Camera_PositionSet(NULL, Q12(-263.03f), Q12(-3.43f), Q12(-105.37f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-261.58f), Q12(-0.08f), Q12(-103.73f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            D_800F22AE = 0;

            Savegame_EventFlagSet(EventFlag_169);

            g_SysWork.field_30 = 20;
            Model_AnimFlagsClear(&g_SysWork.player_4C.chara_0.model_0, AnimFlag_Visible);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1394, &D_800CD468, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);

            // TODO: Odd float values, maybe using different Q format for `s16`?
            D_800F22AE    += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(-0.0277f), Q12_SHIFT);
            D_800F22AE     = MAX(Q12(-0.0137f), D_800F22AE);

            D_800F538C[1] += FP_MULTIPLY_PRECISE(g_DeltaTime0, D_800F22AE, Q12_SHIFT);
            if (D_800F538C[1] < Q12(-0.02222f)) // TODO: `MAX`? Currently doesn't match.
            {
                D_800F538C[1] = Q12(-0.02222f);
            }
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, AnimFlag_Visible);

            if (g_SysWork.playerCombatInfo_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_SysWork.playerCombatInfo_38.weaponAttack_F %= 10; // TODO: Use macro.
            }

            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800EB758(void) // 0x800EB758
{
    func_800EB824(0);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB79C(void) // 0x800EB79C
{
    func_800EB824(1);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB7E0(void) // 0x800EB7E0
{
    func_800EB824(2);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB824(s32 arg0) // 0x800EB824
{
    if (arg0 == 0)
    {
        Savegame_EventFlagSet(EventFlag_172);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_172);
    }

    if (arg0 == 1)
    {
        Savegame_EventFlagSet(EventFlag_173);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_173);
    }

    if (arg0 == 2)
    {
        Savegame_EventFlagSet(EventFlag_174);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_174);
    }

    func_800EE5D0();
}

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800EB908);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800EC080);

s32 func_800EE518(void) // 0x800EE518
{
    s32 ret;

    if (!Savegame_EventFlagGet(EventFlag_172))
    {
        if (Savegame_EventFlagGet(EventFlag_173))
        {
            ret = 1;
        }
        else if (Savegame_EventFlagGet(EventFlag_174))
        {
            ret = 2;
        }
        else
        {
            Savegame_EventFlagSet(EventFlag_172);
            ret = 0;
        }
    }
    else
    {
        ret = 0;
    }

    if (Savegame_EventFlagGet(EventFlag_131) && !Savegame_EventFlagGet(EventFlag_181) && ret == 1)
    {
        ret = 2;
    }

    return ret;
}

u8 func_800EE5A8(u32 arg0) // 0x800EE5A8
{
    if (arg0 < 3) 
    {
        return D_800F1CA8[arg0];
    }

    return 10;
}

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800EE5D0);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800EE660);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CD5A0);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CD5A8);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CD5B4);

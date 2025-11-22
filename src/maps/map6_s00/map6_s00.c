#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s00.h"

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CCB30

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CCFCC

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CD0A4

#include "maps/shared/Particle_Update.h" // 0x800CD3C0

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CDA28

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800CEFF4_0_s00); // 0x800CDDA0

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CE490

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800CEFD0_1_s02); // 0x800CE658

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CECDC

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D0690_1_s03); // 0x800CEDF0

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CEF3C

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CEF44

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CEFFC

#include "maps/shared/Player.h"

#include "maps/shared/Ai_AirScreamer_Update.h" // 0x800D18FC

#include "maps/shared/sharedFunc_800D21E4_0_s01.h" // 0x800D1970

#include "maps/shared/sharedFunc_800D2200_0_s01.h" // 0x800D198C

#include "maps/shared/sharedFunc_800D2274_0_s01.h" // 0x800D1A00

#include "maps/shared/sharedFunc_800D2364_0_s01.h" // 0x800D1AF0

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D2390_0_s01); // 0x800D1B1C

#include "maps/shared/Ai_AirScreamer_Init.h" // 0x800D2100

#include "maps/shared/sharedFunc_800D2B00_0_s01.h" // 0x800D228C

#include "maps/shared/sharedFunc_800D2B10_0_s01.h" // 0x800D229C

#include "maps/shared/sharedFunc_800D2B28_0_s01.h" // 0x800D22B4

#include "maps/shared/sharedFunc_800D2B4C_0_s01.h" // 0x800D22D8

#include "maps/shared/sharedFunc_800D2BB0_0_s01.h" // 0x800D233C

#include "maps/shared/sharedFunc_800D2BE4_0_s01.h" // 0x800D2370

#include "maps/shared/sharedFunc_800D2BF4_0_s01.h" // 0x800D2380

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", Chara_DamageTake); // 0x800D2398

#include "maps/shared/sharedFunc_800D2E04_0_s01.h" // 0x800D259C

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D2FB4_0_s01);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D31D0_0_s01); // 0x800D2968

#include "maps/shared/sharedFunc_800D3430_0_s01.h" // 0x800D2BC8

#include "maps/shared/sharedFunc_800D3508_0_s01.h" // 0x800D2CA0

#include "maps/shared/sharedFunc_800D3630_0_s01.h" // 0x800D2DC8

#include "maps/shared/sharedFunc_800D3758_0_s01.h" // 0x800D2EF0

#include "maps/shared/sharedFunc_800D3814_0_s01.h" // 0x800D2FAC

#include "maps/shared/sharedFunc_800D3928_0_s01.h" // 0x800D30C0

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", D_800CA854);

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", D_800CA858);

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", D_800CA864);

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", D_800CA87C);

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", D_800CA894);

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", D_800CA8AC);

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", sharedData_800CAA98_0_s01);

#include "maps/shared/sharedSymbol_800D3B0C_0_s01.h" // 0x800D318C

#include "maps/shared/sharedFunc_800D3CC4_0_s01.h" // 0x800D33EC

#include "maps/shared/sharedFunc_800D3DFC_0_s01.h" // 0x800D3524

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D35E0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D3800);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D3960);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D3D14);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D4084);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D4458);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D4834);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D4C24);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D4F10);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D5330);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D5544);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D5768);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D59F8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D5DBC);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D5EC0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D635C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D6438);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D67E4);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D6B60);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D6F28);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D7308);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D76C8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D7AA8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D7DB4);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D7FD4);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D8244);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D85F0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D8700);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D8B5C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D8C70);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D8DA4);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D8EA8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D9298);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D961C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D9A90);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800D9F54);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DA2BC);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DA664);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DA9F4);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DABDC);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DAF08);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DB268);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DB374);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DB7A8);

void func_800DB8A8(void) {}

void func_800DB8B0(void) {}

void func_800DB8B8(void) {}

void func_800DB8C0(void) {}

void func_800DB8C8(void) {}

void func_800DB8D0(void) {}

#include "maps/shared/sharedFunc_800D4A80_0_s01.h" // 0x800DB8D8

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DB944);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DBA64);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DBAA0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DBBBC);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DBCC8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DBD78);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DBDF4);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DBEC8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DBF54);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DC038);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DC0A0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DC250);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DC348);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D4E84_0_s01); // 0x800DC6E0

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800DCAD0

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DCAF8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DCC80);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DCE60);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DCEA8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DCEF0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DCF44);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DD1F0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DD43C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DD7D0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DD930);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DD9F0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DDAD8);

#include "maps/shared/sharedFunc_800DE1F8_2_s00.h" // 0x800DDBB4

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800DE250_2_s00); // 0x800DDC0C

#include "maps/shared/sharedFunc_800DE578_2_s00.h" // 0x800DDF34

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800DDF54

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800DE6A8_2_s00);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DE19C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DE2FC);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800DEBCC_2_s00);

#include "maps/shared/sharedFunc_800DEC64_2_s00.h" // 0x800DE620

#include "maps/shared/sharedFunc_800DEC84_2_s00.h" // 0x800DE640

#include "maps/shared/sharedFunc_800DECA4_2_s00.h" // 0x800DE660

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DE680);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DE7E0);

#include "maps/shared/sharedFunc_800DF22C_2_s00.h" // 0x800DEBE8

#include "maps/shared/sharedFunc_800DF24C_2_s00.h" // 0x800DEC08

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800DEC28

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DEC8C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DED14);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DEE04);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DEFC8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DF0CC);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DF1C8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DF25C);

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800DF30C

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800DF438

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DF5FC);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DF780);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DF900);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DF9F0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DFA84);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DFAE8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DFBD8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DFDD8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DFE6C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800DFED0);

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800DFFCC

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E0054);

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800E042C

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800E0490

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800E04F8

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D6600_0_s01); // 0x800E0754

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800E0BB4

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800E0DD0

#include "maps/shared/sharedFunc_800D6EC4_0_s01.h"

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D7120_0_s01); // 0x800E1274

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800E1344

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D72E8_0_s01);

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800E1594

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800E16B4

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800E17F4

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E1868);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D77D0_0_s01); // 0x800E1924

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800E1C04

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D7B14_0_s01);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D7EBC_0_s01); // 0x800E1FDC

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800E22D0

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D81D0_0_s01); // 0x800E22F0

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D8244_0_s01); // 0x800E2364

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800D82B8_0_s01); // 0x800E23D8

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800E2834

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800E291C

#include "maps/shared/sharedFunc_800D8804_0_s01.h" // 0x800E2924

#include "maps/shared/Ai_Groaner_Update.h" // 0x800E2934

#include "maps/shared/Ai_Groaner_Init.h" // 0x800E2A30

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E33DC_2_s00); // 0x800E2C30

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E384C_2_s00); // 0x800E30A0

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E322C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E36E8);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E4084);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E46D8);

#include "maps/shared/sharedFunc_800E554C_2_s00.h" // 0x800E4DA0

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E4E04);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E5184);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E5AA4_2_s00); // 0x800E52F8

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E5EC4_2_s00); // 0x800E5718

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E6338_2_s00); // 0x800E5B8C

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E71E8_2_s00); // 0x800E6A3C

#include "maps/shared/Ai_Romper_Update.h" // 0x800E6F0C

#include "maps/shared/Ai_Romper_Init.h" // 0x800E6FAC

#include "maps/shared/sharedFunc_800E5FC8_2_s02.h" // 0x800E719C

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E60FC_2_s02); // 0x800E72D0

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E6420_2_s02); // 0x800E75F4

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E66E8_2_s02); // 0x800E78BC

#include "maps/shared/sharedFunc_800E6758_2_s02.h" // 0x800E792C

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E7A4C);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E7E14);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E8714);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E8BAC);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E9210);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E932C);

#include "maps/shared/sharedFunc_800E83D4_2_s02.h" // 0x800E95A8

#include "maps/shared/sharedFunc_800E8478_2_s02.h" // 0x800E964C

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800E9654);

#include "maps/shared/sharedFunc_800E86C0_2_s02.h" // 0x800E9894

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E8730_2_s02); // 0x800E9904

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E8A40_2_s02); // 0x800E9C14

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", sharedFunc_800E8DFC_2_s02); // 0x800E9FD0

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800EA570);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800EA688);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800EA8E8);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800EAB00

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800EAB10);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800EAD0C);

void func_800EAFF0(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800EAFF8

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.5)\tWhat's_this! ~E ",
    "~J0(0.1)\t~E ",
    "~J0(0.1)\t~E ",
    "~J0(0.1)\t~E ",
    "~J1(4.0)\tNot_again...!? ~N\n\t\t\tNo,_this_time_it_feels_different. ",
    "~J1(4.5)\tRather_than_shifting ~N\n\t\t\tfrom_reality_to_a_nightmare, ",
    "~J1(4.5)\tthis_is_more_like_reality ~N\n\t\t\tbecoming_a_nightmare. ",
    "~J1(6.0)\tI_don't_like_this_feeling. ~N\n\t\t\tLike_something_bad ~N\n\t\t\twill_happen... ",
    "~J1(4.0)\tNo_doubt,_something_terrible ~N\n\t\t\tis_going_on... ~E ",
    "\tThe_cover_has_been_removed... ",
    "\tCould_Cybil_have_gotten ~N\n\tto_the_Amusement_Park_from_here? ~E ",
    "~C3\tLAKE_SIDE_AMUSEMENT_PARK ~E "
};

void MapEvent_CommonItemTake(void) // 0x800EB090
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 22:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S00_HealthDrink;
            break;

        case 23:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M6S00_ShotgunShells;
            break;

        case 24:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M6S00_FirstAidKit;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800EB11C);

void Map_WorldObjectsInit(void) // 0x800EBCE8
{
    if (!Savegame_EventFlagGet(EventFlag_402))
    {
        D_800A9034.v = 0;
        Fs_QueueStartReadTim(FILE_TIM_GROUND_TIM, IMAGE_BUFFER_4, &D_800A9034);
    }

    WorldObjectNoRotInit(&g_WorldObject_Window, "WINDOW_H", -155.0f, 3.0f, 20.0f);
    WorldObjectNoRotInit(&g_WorldObject_DrOpen1, "DROPEN1_", -190.5f, 0.0f, 132.5f);
    WorldObjectNoRotInit(&g_WorldObject_DrOpen2, "DROPEN2_", -190.5f, -0.05f, 132.214f);
    WorldObjectNoRotInit(&g_WorldObject_DrClose, "DRCLOSE_", -189.5f, 0.0f, 132.5f);

    func_8008D448();
    func_8003EBA0();

    g_SysWork.field_2378 = Q12(1.0f);

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Normal:
            g_SysWork.npcId_2280 = 4;
            break;

        case GameDifficulty_Easy:
            g_SysWork.npcId_2280 = 3;
            break;

        default:
            g_SysWork.npcId_2280 = 5;
            break;
    }

    if (Savegame_EventFlagGet(EventFlag_428))
    {
        Savegame_EventFlagClear(EventFlag_428);
        Game_TurnFlashlightOn();
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800EBEE0);

INCLUDE_ASM("asm/maps/map6_s00/nonmatchings/map6_s00", func_800EC4B4);

INCLUDE_RODATA("asm/maps/map6_s00/nonmatchings/map6_s00", D_800CCB28);

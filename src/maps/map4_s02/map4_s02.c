#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s02.h"

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CC808

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CCBFC

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CCCD4

#include "maps/shared/Particle_Update.h" // 0x800CCFF0

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800CEFF4_0_s00); // 0x800CD634

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CDED8

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CDF74

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CE258

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D0690_1_s03); // 0x800CE32C

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CE478

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CE480

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CE538

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CE5F8

#include "maps/shared/Player.h"

#include "maps/shared/Ai_AirScreamer_Update.h" // 0x800D0B24

#include "maps/shared/sharedFunc_800D21E4_0_s01.h" // 0x800D0B98

#include "maps/shared/sharedFunc_800D2200_0_s01.h" // 0x800D0BB4

#include "maps/shared/sharedFunc_800D2274_0_s01.h" // 0x800D0C28

#include "maps/shared/sharedFunc_800D2364_0_s01.h" // 0x800D0D18

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D2390_0_s01); // 0x800D0D44

#include "maps/shared/Ai_AirScreamer_Init.h" // 0x800D1328

#include "maps/shared/sharedFunc_800D2B00_0_s01.h"// 0x800D14B4

#include "maps/shared/sharedFunc_800D2B10_0_s01.h" // 0x800D14C4

#include "maps/shared/sharedFunc_800D2B28_0_s01.h" // 0x800D14DC

#include "maps/shared/sharedFunc_800D2B4C_0_s01.h" // 0x800D1500

#include "maps/shared/sharedFunc_800D2BB0_0_s01.h" // 0x800D1564

#include "maps/shared/sharedFunc_800D2BE4_0_s01.h" // 0x800D1598

#include "maps/shared/sharedFunc_800D2BF4_0_s01.h" // 0x800D15A8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", Chara_DamageTake); // 0x800D15C0

#include "maps/shared/sharedFunc_800D2E04_0_s01.h" // 0x800D17C4

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D2FB4_0_s01);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D31D0_0_s01); // 0x800D1B90

#include "maps/shared/sharedFunc_800D3430_0_s01.h" // 0x800D1DF0

#include "maps/shared/sharedFunc_800D3508_0_s01.h" // 0x800D1EC8

#include "maps/shared/sharedFunc_800D3630_0_s01.h" // 0x800D1FF0

#include "maps/shared/sharedFunc_800D3758_0_s01.h" // 0x800D2118

#include "maps/shared/sharedFunc_800D3814_0_s01.h" // 0x800D21D4

#include "maps/shared/sharedFunc_800D3928_0_s01.h" // 0x800D22E8

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", D_800CA77C);

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", D_800CA780);

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", D_800CA78C);

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", D_800CA7A4);

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", D_800CA7BC);

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", D_800CA7D4);

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", sharedData_800CAA98_0_s01);

#include "maps/shared/sharedSymbol_800D3B0C_0_s01.h" // 0x800D23B4

#include "maps/shared/sharedFunc_800D3CC4_0_s01.h" // 0x800D2614

#include "maps/shared/sharedFunc_800D3DFC_0_s01.h" // 0x800D274C

#include "maps/shared/sharedFunc_800D3C24_2_s00.h" // 0x800D2808

#include "maps/shared/sharedFunc_800D3E44_2_s00.h" // 0x800D2A28

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D2B88);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D2F3C);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D32AC);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D3680);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D3A5C);

#include "maps/shared/sharedFunc_800D5268_2_s00.h" // 0x800D3E4C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D4138);

#include "maps/shared/sharedFunc_800D5974_2_s00.h" // 0x800D4558

#include "maps/shared/sharedFunc_800D5B88_2_s00.h" // 0x800D476C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D4990);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D4C20);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D4FE4);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D50E8);

#include "maps/shared/sharedFunc_800D69A0_2_s00.h" // 0x800D5584

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D5660);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D5A0C);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D5D88);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D6150);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D6530);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D68F0);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D6CD0);

#include "maps/shared/sharedFunc_800D83F8_2_s00.h" // 0x800D6FDC

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D71FC);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D746C);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D7818);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D7928);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D7D84);

#include "maps/shared/sharedFunc_800D92B4_2_s00.h" // 0x800D7E98

#include "maps/shared/sharedFunc_800D93E8_2_s00.h" // 0x800D7FCC

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D80D0);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D84C0);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D8844);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D8CB8);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D917C);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D94E4);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D988C);

#include "maps/shared/sharedFunc_800DB038_2_s00.h" // 0x800D9C1C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D9E04);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DA130);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DA490);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DA59C);

#include "maps/shared/sharedFunc_800DBDEC_2_s00.h" // 0x800DA9D0

void func_800DAAD0(void) {}

void func_800DAAD8(void) {}

void func_800DAAE0(void) {}

void func_800DAAE8(void) {}

void func_800DAAF0(void) {}

void func_800DAAF8(void) {}

#include "maps/shared/sharedFunc_800D4A80_0_s01.h" // 0x800DAB00

#include "maps/shared/sharedFunc_800DBF88_2_s00.h" // 0x800DAB6C

#include "maps/shared/sharedFunc_800DC0A8_2_s00.h" // 0x800DAC8C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DC0E4_2_s00); // 0x800DACC8

#include "maps/shared/sharedFunc_800DC200_2_s00.h" // 0x800DADE4

#include "maps/shared/sharedFunc_800DC30C_2_s00.h" // 0x800DAEF0

#include "maps/shared/sharedFunc_800DC3BC_2_s00.h" // 0x800DAFA0

#include "maps/shared/sharedFunc_800DC438_2_s00.h" // 0x800DB01C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DB0F0);

#include "maps/shared/sharedFunc_800DC598_2_s00.h" // 0x800DB17C

#include "maps/shared/sharedFunc_800DC67C_2_s00.h" // 0x800DB260

#include "maps/shared/sharedFunc_800DC6E4_2_s00.h" // 0x800DB2C8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DB478);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DC98C_2_s00); // 0x800DB570

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D4E84_0_s01); // 0x800DB908

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800DBCF8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DBD20);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DD2C4_2_s00); // 0x800DBEA8

#include "maps/shared/sharedFunc_800DD4A4_2_s00.h" // 0x800DC088

#include "maps/shared/sharedFunc_800DD4EC_2_s00.h" // 0x800DC0D0

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DC118);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DC16C);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DC418);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DC664);

#include "maps/shared/sharedFunc_800DDE14_2_s00.h" // 0x800DC9F8

#include "maps/shared/sharedFunc_800DDF74_2_s00.h" // 0x800DCB58

#include "maps/shared/sharedFunc_800DE034_2_s00.h" // 0x800DCC18

#include "maps/shared/sharedFunc_800DE11C_2_s00.h" // 0x800DCD00

#include "maps/shared/sharedFunc_800DE1F8_2_s00.h" // 0x800DCDDC

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DE250_2_s00); // 0x800DCE34

#include "maps/shared/sharedFunc_800DE578_2_s00.h" // 0x800DD15C

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800DD17C

#include "maps/shared/sharedFunc_800DE6A8_2_s00.h" // 0x800DD28C

#include "maps/shared/sharedFunc_800DE7E0_2_s00.h" // 0x800DD3C4

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DE940_2_s00); // 0x800DD524

#include "maps/shared/sharedFunc_800DEBCC_2_s00.h" // 0x800DD7B0

#include "maps/shared/sharedFunc_800DEC64_2_s00.h" // 0x800DD848

#include "maps/shared/sharedFunc_800DEC84_2_s00.h" // 0x800DD868

#include "maps/shared/sharedFunc_800DECA4_2_s00.h" // 0x800DD888

#include "maps/shared/sharedFunc_800DECC4_2_s00.h" // 0x800DD8A8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DEE24_2_s00); // 0x800DDA08

#include "maps/shared/sharedFunc_800DF22C_2_s00.h" // 0x800DDE10

#include "maps/shared/sharedFunc_800DF24C_2_s00.h" // 0x800DDE30

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800DDE50

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DF2D0_2_s00); // 0x800DDEB4

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DF358_2_s00); // 0x800DDF3C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DE02C);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DE1F0);

#include "maps/shared/sharedFunc_800DF710_2_s00.h" // 0x800DE2F4

#include "maps/shared/sharedFunc_800DF80C_2_s00.h" // 0x800DE3F0

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DF8A0_2_s00); // 0x800DE484

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800DE534

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800DE660

#include "maps/shared/sharedFunc_800D598C_0_s01.h" // 0x800DE824

#include "maps/shared/sharedFunc_800D5B10_0_s01.h" // 0x800DE9A8

#include "maps/shared/sharedFunc_800D5C90_0_s01.h" // 0x800DEB28

#include "maps/shared/sharedFunc_800D5D80_0_s01.h" // 0x800DEC18

#include "maps/shared/sharedFunc_800D5E14_0_s01.h" // 0x800DECAC

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E012C_2_s00); // 0x800DED10

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800DEE00);

#include "maps/shared/sharedFunc_800E041C_2_s00.h" // 0x800DF000

#include "maps/shared/sharedFunc_800E04B0_2_s00.h" // 0x800DF094

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E0514_2_s00); // 0x800DF0F8

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800DF1F4

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E0698_2_s00); // 0x800DF27C

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800DF654

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800DF6B8

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800DF720

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D6600_0_s01); // 0x800DF97C

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800DFDDC

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800DFFF8

#include "maps/shared/sharedFunc_800D6EC4_0_s01.h"

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D7120_0_s01); // 0x800E049C

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800E056C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D72E8_0_s01);

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800E07BC

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800E08DC

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800E0A1C

#include "maps/shared/sharedFunc_800D7714_0_s01.h" // 0x800E0A90

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D77D0_0_s01); // 0x800E0B4C

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800E0E2C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D7B14_0_s01);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D7EBC_0_s01); // 0x800E1204

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800E14F8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D81D0_0_s01); // 0x800E1518

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D8244_0_s01); // 0x800E158C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D82B8_0_s01); // 0x800E1600

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800E1A5C

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800E1B44

#include "maps/shared/sharedFunc_800D8804_0_s01.h" // 0x800E1B4C

#include "maps/shared/Ai_Groaner_Update.h" // 0x800E1B5C

#include "maps/shared/Ai_Groaner_Init.h" // 0x800E1C58

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E33DC_2_s00); // 0x800E1E58

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E384C_2_s00); // 0x800E22C8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E2454);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E2910);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E32AC);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E3900);

#include "maps/shared/sharedFunc_800E554C_2_s00.h" // 0x800E3FC8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E402C);

#include "maps/shared/sharedFunc_800E5930_2_s00.h" // 0x800E43AC

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E5AA4_2_s00); // 0x800E4520

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E5EC4_2_s00); // 0x800E4940

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E6338_2_s00); // 0x800E4DB4

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E71E8_2_s00); // 0x800E5C64

#include "maps/shared/Ai_Romper_Update.h" // 0x800E6134

#include "maps/shared/Ai_Romper_Init.h" // 0x800E61D4

#include "maps/shared/sharedFunc_800E5FC8_2_s02.h" // 0x800E63C4

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E60FC_2_s02); // 0x800E64F8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E6420_2_s02); // 0x800E681C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E66E8_2_s02); // 0x800E6AE4

#include "maps/shared/sharedFunc_800E6758_2_s02.h" // 0x800E6B54

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E6C74);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E703C);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E793C);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E7DD4);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E8438);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E8554);

#include "maps/shared/sharedFunc_800E83D4_2_s02.h" // 0x800E87D0

#include "maps/shared/sharedFunc_800E8478_2_s02.h" // 0x800E8874

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E887C);

#include "maps/shared/sharedFunc_800E86C0_2_s02.h" // 0x800E8ABC

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E8730_2_s02); // 0x800E8B2C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E8A40_2_s02); // 0x800E8E3C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E8DFC_2_s02); // 0x800E91F8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E9798);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E98B0);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E9B10);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E9D28

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E9D38);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800E9F34);

void func_800EA208(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800EA210

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800EA2A4

void func_800EA338(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~C3\tgreen_lion ~E ",
    "~C3\tAlchemilla_Hospital ~E "
};

void Map_WorldObjectsInit(void) // 0x800EA340
{
    D_800F13AC = 0;

    WorldObjectNoRotInit(&g_WorldObject_Kidn04, "KIDN04_H", -119.8019f, 5.0f, 107.861f);

    WorldObject_ModelNameSet(&g_WorldObject_Fan0, "FAN0_HID");

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 3;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcId_2280 = 4;
    }
    else
    {
        g_SysWork.npcId_2280 = 5;
    }
}

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800EA3F0);

INCLUDE_RODATA("asm/maps/map4_s02/nonmatchings/map4_s02", D_800CC800);

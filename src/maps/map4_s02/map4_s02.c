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

#include "maps/shared/sharedFunc_800CEFF4_0_s00.h" // 0x800CD634

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

#include "maps/shared/sharedFunc_800D4358_2_s00.h" // 0x800D2F3C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D32AC);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D3680);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D3A5C);

#include "maps/shared/sharedFunc_800D5268_2_s00.h" // 0x800D3E4C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D4138);

#include "maps/shared/sharedFunc_800D5974_2_s00.h" // 0x800D4558

#include "maps/shared/sharedFunc_800D5B88_2_s00.h" // 0x800D476C

#include "maps/shared/sharedFunc_800D5DAC_2_s00.h" // 0x800D4990

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D4C20);

#include "maps/shared/sharedFunc_800D6400_2_s00.h" // 0x800D4FE4

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D50E8);

#include "maps/shared/sharedFunc_800D69A0_2_s00.h" // 0x800D5584

#include "maps/shared/sharedFunc_800D6A7C_2_s00.h" // 0x800D5660

#include "maps/shared/sharedFunc_800D6E28_2_s00.h" // 0x800D5A0C

#include "maps/shared/sharedFunc_800D71A4_2_s00.h" // 0x800D5D88

#include "maps/shared/sharedFunc_800D756C_2_s00.h" // 0x800D6150

#include "maps/shared/sharedFunc_800D794C_2_s00.h" // 0x800D6530

#include "maps/shared/sharedFunc_800D7D0C_2_s00.h" // 0x800D68F0

#include "maps/shared/sharedFunc_800D80EC_2_s00.h" // 0x800D6CD0

#include "maps/shared/sharedFunc_800D83F8_2_s00.h" // 0x800D6FDC

#include "maps/shared/sharedFunc_800D8618_2_s00.h" // 0x800D71FC

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D746C);

#include "maps/shared/sharedFunc_800D8C34_2_s00.h" // 0x800D7818

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D7928);

#include "maps/shared/sharedFunc_800D91A0_2_s00.h" // 0x800D7D84

#include "maps/shared/sharedFunc_800D92B4_2_s00.h" // 0x800D7E98

#include "maps/shared/sharedFunc_800D93E8_2_s00.h" // 0x800D7FCC

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D80D0);

#include "maps/shared/sharedFunc_800D98DC_2_s00.h" // 0x800D84C0

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D8844);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D8CB8);

#include "maps/shared/sharedFunc_800DA598_2_s00.h" // 0x800D917C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D94E4);

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", func_800D988C);

#include "maps/shared/sharedFunc_800DB038_2_s00.h" // 0x800D9C1C

#include "maps/shared/sharedFunc_800DB220_2_s00.h" // 0x800D9E04

#include "maps/shared/sharedFunc_800DB54C_2_s00.h" // 0x800DA130

#include "maps/shared/sharedFunc_800DB8AC_2_s00.h" // 0x800DA490

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

#include "maps/shared/sharedFunc_800DC0E4_2_s00.h" // 0x800DACC8

#include "maps/shared/sharedFunc_800DC200_2_s00.h" // 0x800DADE4

#include "maps/shared/sharedFunc_800DC30C_2_s00.h" // 0x800DAEF0

#include "maps/shared/sharedFunc_800DC3BC_2_s00.h" // 0x800DAFA0

#include "maps/shared/sharedFunc_800DC438_2_s00.h" // 0x800DB01C

#include "maps/shared/sharedFunc_800DC50C_2_s00.h" // 0x800DB0F0

#include "maps/shared/sharedFunc_800DC598_2_s00.h" // 0x800DB17C

#include "maps/shared/sharedFunc_800DC67C_2_s00.h" // 0x800DB260

#include "maps/shared/sharedFunc_800DC6E4_2_s00.h" // 0x800DB2C8

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DC894_2_s00); // 0x800DB478

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DC98C_2_s00); // 0x800DB570

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800D4E84_0_s01); // 0x800DB908

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800DBCF8

#include "maps/shared/sharedFunc_800DD13C_2_s00.h" // 0x800DBD20

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DD2C4_2_s00); // 0x800DBEA8

#include "maps/shared/sharedFunc_800DD4A4_2_s00.h" // 0x800DC088

#include "maps/shared/sharedFunc_800DD4EC_2_s00.h" // 0x800DC0D0

#include "maps/shared/sharedFunc_800DD534_2_s00.h" // 0x800DC118

#include "maps/shared/sharedFunc_800DD588_2_s00.h" // 0x800DC16C

#include "maps/shared/sharedFunc_800DD834_2_s00.h" // 0x800DC418

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

#include "maps/shared/sharedFunc_800DF358_2_s00.h" // 0x800DDF3C

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800DF448_2_s00); // 0x800DE02C

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

INCLUDE_ASM("asm/maps/map4_s02/nonmatchings/map4_s02", sharedFunc_800E021C_2_s00); // 0x800DEE00

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

#include "maps/shared/sharedFunc_800D7B14_0_s01.h" // 0x800E0E90

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

#include "maps/shared/sharedFunc_800E55B0_2_s00.h" // 0x800E402C

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

#include "maps/shared/Map_RoomIdxGet.h" // 0x800E9D38

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

void func_800EA3F0(void) // 0x800EA3F0
{
    VECTOR3  objPos;
    SVECTOR3 objRot;
    q19_12   dist0;
    q19_12   dist1;
    s32      tmp0;
    s32      i;
    s32      vol;
    s32      audioBalance;
    s32      var_v0;
    s32      tmp1;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    func_80069844(0xFFFF);

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3)) ||
        (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3)))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObject_Kidn04.object_0, &g_WorldObject_Kidn04.position_1C, &(SVECTOR3){ 0, 0, 0 });
        func_8006982C(2);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (Savegame_EventFlagGet(EventFlag_346))
        {
            func_8006982C(4);

            if (g_SysWork.player_4C.chara_0.position_18.vz < Q12(-68.0f))
            {
                Savegame_EventFlagClear(EventFlag_346);
            }
        }
        else
        {
            func_8006982C(2);
        }
    }

    audioBalance = 0;
    tmp0 = FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);

    for (i = 0; i < ARRAY_SIZE(D_800ED8B0); i++)
    {
        switch (i)
        {
            case 0:
                objPos.vx = Q12(53.211f);
                objPos.vy = Q12(-2.375f);
                objPos.vz = Q12(32.5f);
                Math_SetSVectorFast(&objRot, 0, 0, 0);
                break;

            case 4:
                objPos.vx = Q12(56.575f);
                objPos.vy = Q12(-2.875f);
                objPos.vz = Q12(27.5f);
                break;

            case 7:
                objPos.vx = Q12(65.45f);
                objPos.vy = Q12(-2.875f);
                objPos.vz = Q12(27.5f);
                objRot.vy = FP_ANGLE(180.0f);
                break;

            case 11:
                objPos.vx = Q12(68.8f);
                objPos.vy = Q12(-2.375f);
                objPos.vz = Q12(32.5f);
                break;
        }

        if (i < 7)
        {
            D_800ED8B0[i] -= tmp0;
        }
        else
        {
            D_800ED8B0[i] += tmp0;
        }

        // @hack
        tmp1 = (g_SysWork.player_4C.chara_0.position_18.vx / ((s32)(40.0f * Q12(1.0f))));
        
        objRot.vx = D_800ED8B0[i];
        
        if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Fan0, &objPos, &objRot);
        }

        audioBalance += Sound_StereoBalanceGet(&objPos);
        objPos.vz -= Q12(5.0f);
    }

    if (PLAYER_NEAR_POS(vx, 61.0f, 4.0f) && PLAYER_NEAR_POS(vz, 22.5f, 5.0f))
    {
        vol = Q8(1.0f);
    }
    else
    {        
        dist0 = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - Q12(61.0f), g_SysWork.player_4C.chara_0.position_18.vz - Q12(27.5f));
        dist1 = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - Q12(61.0f), g_SysWork.player_4C.chara_0.position_18.vz - Q12(17.5f));
        if (dist1 >= dist0) 
        {
            tmp0 = dist0;
        }
        else
        {
            tmp0 = dist1;
        }

        if (tmp0 <= Q12(32.0f))
        {
            tmp1 = tmp0 >> 9;
            vol = Q8(1.0f) - tmp1;
        }
        else
        {
            vol = Q8(0.0f);
        }
    }

    if (vol != Q8(0.0f)) 
    {
        if (!D_800F13AC)
        {
            Sd_EngineCmd(Sfx_Unk1542);
            D_800F13AC++;
        }

        func_800463C0(Sfx_Unk1542, audioBalance >> 4, -vol, 0);
    }
    else if (D_800F13AC)
    {
        func_8004690C(Sfx_Unk1542);
        D_800F13AC = 0;
    }
}

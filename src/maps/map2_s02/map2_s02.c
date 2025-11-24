#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s02.h"

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CC8A4

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CCD90

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CCE68

#include "maps/shared/Particle_Update.h" // 0x800CD174

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CD71C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CDBEC

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800CEFD0_1_s02); // 0x800CDD3C

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CE104

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CE230

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CE238

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CE2F0

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CE378

#include "maps/shared/Player.h"

#include "maps/shared/Ai_AirScreamer_Update.h" // 0x800D0728

#include "maps/shared/sharedFunc_800D21E4_0_s01.h" // 0x800D079C

#include "maps/shared/sharedFunc_800D2200_0_s01.h" // 0x800D07B8

#include "maps/shared/sharedFunc_800D2274_0_s01.h" // 0x800D082C

#include "maps/shared/sharedFunc_800D2364_0_s01.h" // 0x800D091C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D2390_0_s01); // 0x800D0948

#include "maps/shared/Ai_AirScreamer_Init.h" // 0x800D0F2C

#include "maps/shared/sharedFunc_800D2B00_0_s01.h" // 0x800D10B8

#include "maps/shared/sharedFunc_800D2B10_0_s01.h" // 0x800D10C8

#include "maps/shared/sharedFunc_800D2B28_0_s01.h" // 0x800D10E0

#include "maps/shared/sharedFunc_800D2B4C_0_s01.h" // 0x800D1104

#include "maps/shared/sharedFunc_800D2BB0_0_s01.h" // 0x800D1168

#include "maps/shared/sharedFunc_800D2BE4_0_s01.h" // 0x800D119C

#include "maps/shared/sharedFunc_800D2BF4_0_s01.h" // 0x800D11AC

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", Chara_DamageTake); // 0x800D11C4

#include "maps/shared/sharedFunc_800D2E04_0_s01.h" // 0x800D13C8

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D2FB4_0_s01);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D31D0_0_s01); // 0x800D1794

#include "maps/shared/sharedFunc_800D3430_0_s01.h" // 0x800D19F4

#include "maps/shared/sharedFunc_800D3508_0_s01.h" // 0x800D1ACC

#include "maps/shared/sharedFunc_800D3630_0_s01.h" // 0x800D1BF4

#include "maps/shared/sharedFunc_800D3758_0_s01.h" // 0x800D1D1C

#include "maps/shared/sharedFunc_800D3814_0_s01.h" // 0x800D1DD8

#include "maps/shared/sharedFunc_800D3928_0_s01.h" // 0x800D1EEC

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", D_800CA7F0);

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", D_800CA7F4);

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", D_800CA800);

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", D_800CA818);

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", D_800CA830);

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", D_800CA848);

INCLUDE_RODATA("asm/maps/map2_s02/nonmatchings/map2_s02", sharedData_800CAA98_0_s01);

#include "maps/shared/sharedSymbol_800D3B0C_0_s01.h" // 0x800D1FB8

#include "maps/shared/sharedFunc_800D3CC4_0_s01.h" // 0x800D2218

#include "maps/shared/sharedFunc_800D3DFC_0_s01.h" // 0x800D2350

#include "maps/shared/sharedFunc_800D3C24_2_s00.h" // 0x800D240C

#include "maps/shared/sharedFunc_800D3E44_2_s00.h" // 0x800D262C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D278C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D2B40);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D2EB0);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D3284);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D3660);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D3A50);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D3D3C);

#include "maps/shared/sharedFunc_800D5974_2_s00.h" // 0x800D415C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D4370);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D4594);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D4824);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D4BE8);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D4CEC);

#include "maps/shared/sharedFunc_800D69A0_2_s00.h" // 0x800D5188

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D5264);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D5610);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D598C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D5D54);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D6134);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D64F4);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D68D4);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D6BE0);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D6E00);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D7070);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D741C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D752C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D7988);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D7A9C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D7BD0);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D7CD4);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D80C4);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D8448);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D88BC);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D8D80);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D90E8);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D9490);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D9820);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D9A08);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800D9D34);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DA094);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DA1A0);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DA5D4);

void func_800DA6D4(void) {}

void func_800DA6DC(void) {}

void func_800DA6E4(void) {}

void func_800DA6EC(void) {}

void func_800DA6F4(void) {}

void func_800DA6FC(void) {}

#include "maps/shared/sharedFunc_800D4A80_0_s01.h" // 0x800DA704

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DA770);

#include "maps/shared/sharedFunc_800DC0A8_2_s00.h" // 0x800DA890

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DA8CC);

#include "maps/shared/sharedFunc_800DC200_2_s00.h" // 0x800DA9E8

#include "maps/shared/sharedFunc_800DC30C_2_s00.h" // 0x800DAAF4

#include "maps/shared/sharedFunc_800DC3BC_2_s00.h" // 0x800DABA4

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DAC20);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DACF4);

#include "maps/shared/sharedFunc_800DC598_2_s00.h" // 0x800DAD80

#include "maps/shared/sharedFunc_800DC67C_2_s00.h" // 0x800DAE64

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DAECC);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DB07C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800DC98C_2_s00); // 0x800DB174

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D4E84_0_s01); // 0x800DB50C

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800DB8FC

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DB924);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800DD2C4_2_s00); // 0x800DBAAC

#include "maps/shared/sharedFunc_800DD4A4_2_s00.h" // 0x800DBC8C

#include "maps/shared/sharedFunc_800DD4EC_2_s00.h" // 0x800DBCD4

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DBD1C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DBD70);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DC01C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DC268);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DC5FC);

#include "maps/shared/sharedFunc_800DDF74_2_s00.h" // 0x800DC75C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DC81C);

#include "maps/shared/sharedFunc_800DE11C_2_s00.h" // 0x800DC904

#include "maps/shared/sharedFunc_800DE1F8_2_s00.h" // 0x800DC9E0

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800DE250_2_s00); // 0x800DCA38

#include "maps/shared/sharedFunc_800DE578_2_s00.h" // 0x800DCD60

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800DCD80

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800DE6A8_2_s00);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DCFC8);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DD128);

#include "maps/shared/sharedFunc_800DEBCC_2_s00.h" // 0x800DD3B4

#include "maps/shared/sharedFunc_800DEC64_2_s00.h" // 0x800DD44C

#include "maps/shared/sharedFunc_800DEC84_2_s00.h" // 0x800DD46C

#include "maps/shared/sharedFunc_800DECA4_2_s00.h" // 0x800DD48C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DD4AC);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DD60C);

#include "maps/shared/sharedFunc_800DF22C_2_s00.h" // 0x800DDA14

#include "maps/shared/sharedFunc_800DF24C_2_s00.h" // 0x800DDA34

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800DDA54

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800DF2D0_2_s00); // 0x800DDAB8

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DDB40);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DDC30);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DDDF4);

#include "maps/shared/sharedFunc_800DF710_2_s00.h" // 0x800DDEF8

#include "maps/shared/sharedFunc_800DF80C_2_s00.h" // 0x800DDFF4

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800DF8A0_2_s00); // 0x800DE088

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800DE138

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800DE264

#include "maps/shared/sharedFunc_800D598C_0_s01.h" // 0x800DE428

#include "maps/shared/sharedFunc_800D5B10_0_s01.h" // 0x800DE5AC

#include "maps/shared/sharedFunc_800D5C90_0_s01.h" // 0x800DE72C

#include "maps/shared/sharedFunc_800D5D80_0_s01.h" // 0x800DE81C

#include "maps/shared/sharedFunc_800D5E14_0_s01.h" // 0x800DE8B0

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DE914);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DEA04);

#include "maps/shared/sharedFunc_800E041C_2_s00.h" // 0x800DEC04

#include "maps/shared/sharedFunc_800E04B0_2_s00.h" // 0x800DEC98

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800DECFC);

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800DEDF8

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E0698_2_s00); // 0x800DEE80

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800DF258

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800DF2BC

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800DF324

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D6600_0_s01); // 0x800DF580

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800DF9E0

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800DFBFC

#include "maps/shared/sharedFunc_800D6EC4_0_s01.h"

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D7120_0_s01); // 0x800E00A0

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800E0170

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D72E8_0_s01);

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800E03C0

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800E04E0

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800E0620

#include "maps/shared/sharedFunc_800D7714_0_s01.h" // 0x800E0694

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D77D0_0_s01); // 0x800E0750

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800E0A30

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D7B14_0_s01);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D7EBC_0_s01); // 0x800E0E08

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800E10FC

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D81D0_0_s01); // 0x800E111C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D8244_0_s01); // 0x800E1190

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800D82B8_0_s01); // 0x800E1204

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800E1660

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800E1748

#include "maps/shared/sharedFunc_800D8804_0_s01.h" // 0x800E1750

#include "maps/shared/Ai_Groaner_Update.h" // 0x800E1760

#include "maps/shared/Ai_Groaner_Init.h" // 0x800E185C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E33DC_2_s00); // 0x800E1A5C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E384C_2_s00); // 0x800E1ECC

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E2058);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E2514);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E2EB0);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E3504);

#include "maps/shared/sharedFunc_800E554C_2_s00.h" // 0x800E3BCC

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E3C30);

#include "maps/shared/sharedFunc_800E5930_2_s00.h" // 0x800E3FB0

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E5AA4_2_s00); // 0x800E4124

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E5EC4_2_s00); // 0x800E4544

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E6338_2_s00); // 0x800E49B8

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E71E8_2_s00); // 0x800E5868

#include "maps/shared/Ai_Romper_Update.h" // 0x800E5D38

#include "maps/shared/Ai_Romper_Init.h" // 0x800E5DD8

#include "maps/shared/sharedFunc_800E5FC8_2_s02.h" // 0x800E5FC8

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E60FC_2_s02);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E6420_2_s02);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E66E8_2_s02);

#include "maps/shared/sharedFunc_800E6758_2_s02.h" // 0x800E6758

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E6878);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E6C40);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E7540);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E79D8);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E803C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E8158);

#include "maps/shared/sharedFunc_800E83D4_2_s02.h" // 0x800E83D4

#include "maps/shared/sharedFunc_800E8478_2_s02.h" // 0x800E8478

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E8480);

#include "maps/shared/sharedFunc_800E86C0_2_s02.h" // 0x800E86C0

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E8730_2_s02);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E8A40_2_s02);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", sharedFunc_800E8DFC_2_s02);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E939C);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E94B4);

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E9714);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E992C

INCLUDE_ASM("asm/maps/map2_s02/nonmatchings/map2_s02", func_800E993C);

void func_800E9B38(void) // 0x800E9B38
{
    s32 flags;
    s32 tmp;

    flags = 1 << 1;
    if (g_SavegamePtr->mapRoomIdx_A5 != 12)
    {
        if ((g_SavegamePtr->mapRoomIdx_A5 == 17) && Savegame_EventFlagGet(EventFlag_295) && !Savegame_EventFlagGet(EventFlag_352))
        {
            flags = (1 << 1) | (1 << 2);
        }
    }
    else if (!Savegame_EventFlagGet(EventFlag_295))
    {
        flags = (1 << 4) | (1 << 1);
    }

    if (Savegame_EventFlagGet(EventFlag_M3S06_PickupAntiqueShopKey))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_AntiqueShopOpen))
        {
            flags |= 1 << 3;
        }
    }

    if (flags & (1 << 3))
    {
        tmp = func_800364BC();
        D_800ED43F = tmp;
    }

    func_80035F4C(flags, Q12(0.1f), &D_800ED43C);
}

void func_800E9C24(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800E9C2C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800E9CC0

void func_800E9D54(void) // 0x800E9D54
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_AntiqueShopKey, 1);
    Map_MessageWithSfx(15, Sfx_UseKey, &sfxPos);
    Savegame_EventFlagSet(EventFlag_M2S02_AntiqueShopOpen);
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tUsed_the_ ~C2 Antique_shop_key ~C7 . ~E ",
    "~C3\tAlchemilla_Hospital ~E ",
    "~C3\tgreen_lion ~E "
};

void func_800E9E10(void) // 0x800E9E10
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 41:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S02_HealthDrink0;
            break;

        case 42:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S02_HealthDrink1;
            break;

        case 43:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S02_HandgunBullets0;
            break;

        case 44:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S02_HandgunBullets1;
            break;

        case 45:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S02_HealthDrink2;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800E9EAC(void) // 0x800E9EAC
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            g_Screen_FadeStatus = 12; // TODO: Can't be created with `ScreenFade_Start` macro?
            func_8004690C(Sfx_Unk1522);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(0, false, 1, Q12(0.25f), false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_191);
            Game_TurnFlashlightOff();
            func_8003A16C();
            break;
    }
}

void func_800E9FDC(void) // 0xfunc_800E9FDC
{
    g_DeltaTime0 = Q12(0.0f);

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);

        case 1:
            if (func_8003599C())
            {
                break;
            }

            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_189);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void func_800EA0E0(void) // 0x800EA0E0
{
    if (Savegame_MapMarkingGet(MapMarkFlag_FogCentralTown_AntiqueWholeSign))
    {
        Savegame_MapMarkingSet(MapMarkFlag_AltCentralTown_AntiqueWholeSign);
    }

    D_800F0B2C = Q12(0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 2;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcId_2280 = 3;
    }
    else
    {
        g_SysWork.npcId_2280 = 4;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void func_800EA1C4(void) // 0x800EA1C4
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    func_80069844(0xFFFF);

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (Savegame_EventFlagGet(EventFlag_346))
        {
            func_8006982C(4);
            func_80069844(2);

            if (g_SysWork.player_4C.chara_0.position_18.vz < Q12(-68.0f))
            {
                Savegame_EventFlagClear(EventFlag_346);
            }
        }
        else
        {
            func_80069844(4);
            func_8006982C(2);
        }
    }

    if (Savegame_EventFlagGet(EventFlag_191) && !Savegame_EventFlagGet(EventFlag_194))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
        {
                if (g_SysWork.player_4C.chara_0.position_18.vx > Q12(-116.0f))
                {
                    if (g_SysWork.player_4C.chara_0.position_18.vy > Q12(0.0f))
                    {
                        if (g_ScreenFadeTimestep > Q12(0.0f))
                        {
                            g_ScreenFadeTimestep = MIN(g_ScreenFadeTimestep + g_DeltaTime0, Q12(3.0f));
                        }
                    }
                }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -6, -1, -6) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
            Game_TurnFlashlightOff();
    }

    if (!Savegame_EventFlagGet(EventFlag_192))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
        {
            if (D_800F0B2C == Q12(0.0f))
            {
                if (Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx + Q12(96.0f),
                                        g_SysWork.player_4C.chara_0.position_18.vz + Q12(89.0f)) < Q12(4.0f))
                {
                    func_8005DC1C(Sfx_Unk1492, &D_800ED938, Q8_CLAMPED(0.766f), 2);
                    D_800F0B2C = Q12(0.3f);
                }
            }
        }

        if (D_800F0B2C > Q12(0.0f))
        {
            D_800F0B2C -= g_DeltaTime0;
            if (D_800F0B2C < Q12(0.0f))
            {
                Savegame_EventFlagSet(EventFlag_192);
                func_8005DC1C(Sfx_Unk1492, &D_800ED938, Q8_CLAMPED(0.766f), 2);
            }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HealthDrink0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HealthDrink1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HandgunBullets0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HandgunBullets1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_HealthDrink2))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }
}

void func_800EAA50(void) // 0x800EAA50
{
    if (Savegame_EventFlagGet(EventFlag_191))
    {
        if (!Savegame_EventFlagGet(EventFlag_194))
        {
            Savegame_EventFlagSet(EventFlag_194);
            func_8003599C();
        }
    }
}

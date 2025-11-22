#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s01.h"

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800CC9A4);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800CD010);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800CDE18);

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", D_800CA5C8);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CDF80

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CE100

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CE1B8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CE31C

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CE33C

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CEBB4

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CEFA0

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800D03B8

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D0808

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D0844

#include "maps/shared/Player_ControlFreeze.h" // 0x800D0850

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800D09B0

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800D0B88

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D1418

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D14C8

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D14E0

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D1508

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D1520

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D1548

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D15EC

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D15FC

#include "maps/shared/sharedFunc_800D2E6C_0_s00.h" // 0x800D1608

#include "maps/shared/sharedFunc_800D2E74_0_s00.h" // 0x800D1610

#include "maps/shared/sharedFunc_800D2E7C_0_s00.h" // 0x800D1618

#include "maps/shared/sharedFunc_800D2E84_0_s00.h" // 0x800D1620

#include "maps/shared/sharedFunc_800D2E8C_0_s00.h" // 0x800D1628

#include "maps/shared/sharedFunc_800D2E94_0_s00.h" // 0x800D1630

#include "maps/shared/sharedFunc_800D2E9C_0_s00.h" // 0x800D1638

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D1640

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D1650

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D1690

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800D16A4

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800D17EC

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800D1914

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800D1934

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D1974);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D19E8);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D1A38);

#include "maps/shared/sharedFunc_800CDA88_3_s03.h" // 0x800D1A7C

#include "maps/shared/Ai_PuppetNurse_UpdateMain.h" // 0x800D1AAC

#include "maps/shared/Ai_PuppetNurse_Init.h" // 0x800D1B50

#include "maps/shared/Ai_PuppetNurse_Update.h" // 0x800D1D24

#include "maps/shared/Ai_PuppetDoctor_Update.h" // 0x800D1D80

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D1DDC);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CDF24_3_s03); // 0x800D1F18

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D20D8);

bool func_800D238C(s32 arg0) // 0x800D238C
{
    return arg0 == 36 || arg0 == 34 || arg0 == 37 || arg0 == 35;
}

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CE3CC_3_s03); // 0x800D23C0

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CE500_3_s03); // 0x800D24F4

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CE5E4_3_s03); // 0x800D25D8

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D27BC);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CEA64_3_s03); // 0x800D2A58

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CEB90_3_s03); // 0x800D2B84

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CEC88_3_s03); // 0x800D2C7C

s32 func_800D2EA0(void) // 0x800D2EA0
{
    s32 temp_a0;

    temp_a0 = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3;
    if (temp_a0 == 0)
    {
        return 0;
    }
    else if (temp_a0 == 2)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D2ED4);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D30A8);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D3288);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CF3AC_3_s03); // 0x800D33A0

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D35F4);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D37E8);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D3900);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CF9F8_3_s03); // 0x800D39EC

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CFD18_3_s03); // 0x800D3D0C

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CFDD4_3_s03); // 0x800D3DC8

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800D0110_3_s03); // 0x800D4104

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", D_800CAD54);

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", D_800CAD58);

#include "maps/shared/Ai_PuppetNurse_Control.h" // 0x800D41C4

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800D02E4_3_s03); // 0x800D42D8

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800D03E4_3_s03); // 0x800D43D8

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800D06AC_3_s03); // 0x800D46A0

#include "maps/shared/sharedFunc_800D0828_3_s03.h" // 0x800D481C

#include "maps/shared/sharedFunc_800D0968_3_s03.h" // 0x800D495C

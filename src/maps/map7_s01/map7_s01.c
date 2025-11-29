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

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CDE18

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", D_800CA5C8);

#include "maps/shared/Player.h"

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800D16A4

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800D17EC

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800D1914

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800D1934

#include "maps/shared/sharedFunc_800CD980_3_s03.h" // 0x800D1974

#include "maps/shared/sharedFunc_800CD9F4_3_s03.h" // 0x800D19E8

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D1A38);

#include "maps/shared/sharedFunc_800CDA88_3_s03.h" // 0x800D1A7C

#include "maps/shared/Ai_PuppetNurse_UpdateMain.h" // 0x800D1AAC

#include "maps/shared/Ai_PuppetNurse_Init.h" // 0x800D1B50

#include "maps/shared/Ai_PuppetNurse_Update.h" // 0x800D1D24

#include "maps/shared/Ai_PuppetDoctor_Update.h" // 0x800D1D80

#include "maps/shared/sharedFunc_800CDDE8_3_s03.h" // 0x800D1DDC

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CDF24_3_s03); // 0x800D1F18

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D20D8);

#include "maps/shared/sharedFunc_800CE398_3_s03.h" // 0x800D238C

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CE3CC_3_s03); // 0x800D23C0

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CE500_3_s03); // 0x800D24F4

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CE5E4_3_s03); // 0x800D25D8

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D27BC);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CEA64_3_s03); // 0x800D2A58

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CEB90_3_s03); // 0x800D2B84

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CEC88_3_s03); // 0x800D2C7C

#include "maps/shared/sharedFunc_800CEEAC_3_s03.h" // 0x800D2EA0

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D2ED4);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D30A8);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D3288);

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800CF3AC_3_s03); // 0x800D33A0

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D35F4);

#include "maps/shared/sharedFunc_800CF7F4_3_s03.h" // 0x800D37E8

#include "maps/shared/sharedFunc_800CF90C_3_s03.h" // 0x800D3900

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

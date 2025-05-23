#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"

//INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", Ai_HangedScratcher_Init); // 0x800CFCA8


#include "maps/shared/Ai_HangedScratcher_Update.h" // 0x800CFC24

#include "maps/shared/Ai_HangedScratcher_Init.h" // 0x800CFCA8

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800CFF74_5_s00); // 0x800CFF74

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D029C_5_s00); // 0x800D029C

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D03F8);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D041C);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D0514);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D063C);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D0C44);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D0F04);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D10B8);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D1274);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D19AC);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D1AD0);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D1C0C);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D1CE4);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D1E84);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D2040);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D2180);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D23E0);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D26D8_5_s00); // 0x800D26D8

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D2844_5_s00); // 0x800D2844

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D2C18_5_s00); // 0x800D2C18

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D3214);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D3300_5_s00); // 0x800D3300

#include "maps/shared/Ai_Creaper_Update.h" // 0x800D387C

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", Ai_Creaper_Init); // 0x800D390C - doesn't fully match `map1_s02` version, small block of code added to end.

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D7EE8_1_s02); // 0x800D3BDC

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D8244_1_s02); // 0x800D3F38

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D3FE4);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D4378);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D4C24);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D521C);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D5468);

#include "maps/shared/sharedFunc_800D983C_1_s02.h" // 0x800D5530

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D9960_1_s02); // 0x800D5654

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", sharedFunc_800D99D0_1_s02); // 0x800D56C4

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D5B00);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D5CC4);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D5D90);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D5EA8);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D5EE8);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D61D4);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D62C8);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D631C);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D63DC);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D6414);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D6490);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D64F8

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D6508);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D6790);

void func_800D67EC(void) {}

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D67F4);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D6888);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D691C);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D69DC);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D6AD4);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D6B00);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D732C);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D75FC);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D7940);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D7C84);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D7F88);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D8280);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D82A8);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D84D8);

INCLUDE_ASM("asm/maps/map5_s00/nonmatchings/map5_s00_2", func_800D8DFC);

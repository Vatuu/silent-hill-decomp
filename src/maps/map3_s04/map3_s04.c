#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s04.h"

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CB37C

#include "maps/shared/Player.h"

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800CD574

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800CD6BC

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800CD7E4

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800CD804

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CD844);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CD8B8);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CD908);

#include "maps/shared/sharedFunc_800CDA88_3_s03.h" // 0x800CD94C

#include "maps/shared/Ai_PuppetNurse_UpdateMain.h" // 0x800CD97C

#include "maps/shared/Ai_PuppetNurse_Init.h" // 0x800CDA20

#include "maps/shared/Ai_PuppetNurse_Update.h" // 0x800CDBF4

#include "maps/shared/Ai_PuppetDoctor_Update.h" // 0x800CDC50

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CDCAC);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CDF24_3_s03); // 0x800CDDE8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CDFA8);

#include "maps/shared/sharedFunc_800CE398_3_s03.h" // 0x800CE25C

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CE3CC_3_s03); // 0x800CE290

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CE500_3_s03); // 0x800CE3C4

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CE5E4_3_s03); // 0x800CE4A8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CE68C);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CEA64_3_s03); // 0x800CE928

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CEB90_3_s03); // 0x800CEA54

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CEC88_3_s03); // 0x800CEB4C

#include "maps/shared/sharedFunc_800CEEAC_3_s03.h" // 0x800CED70

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CEDA4);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CEF78);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CF158);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CF3AC_3_s03); // 0x800CF270

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CF4C4);

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CF6B8);

#include "maps/shared/sharedFunc_800CF90C_3_s03.h" // 0x800CF7D0

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CF9F8_3_s03); // 0x800CF8BC

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CFD18_3_s03); // 0x800CFBDC

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800CFDD4_3_s03); // 0x800CFC98

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D0110_3_s03); // 0x800CFFD4

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CA618);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800CA61C);

#include "maps/shared/Ai_PuppetNurse_Control.h" // 0x800D0094

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D02E4_3_s03); // 0x800D01A8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D03E4_3_s03); // 0x800D02A8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D06AC_3_s03); // 0x800D0570

#include "maps/shared/sharedFunc_800D0828_3_s03.h" // 0x800D06EC

#include "maps/shared/sharedFunc_800D0968_3_s03.h" // 0x800D082C

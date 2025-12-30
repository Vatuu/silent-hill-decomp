#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s04.h"
#include "maps/characters/puppet_nurse.h"

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CB37C

#include "maps/shared/Player.h"

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800CD574

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800CD6BC

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800CD7E4

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800CD804

#include "maps/shared/PuppetNurse_HurtSfxIdGet.h"

#include "maps/shared/Ai_PuppetNurse_SfxPlay.h"

#include "maps/shared/Ai_PuppetNurse_AnimSfxGet.h" // 0x800CD908

#include "maps/shared/sharedFunc_800CDA88_3_s03.h" // 0x800CD94C

#include "maps/shared/Ai_PuppetNurse_UpdateMain.h" // 0x800CD97C

#include "maps/shared/Ai_PuppetNurse_Init.h" // 0x800CDA20

#include "maps/shared/Ai_PuppetNurse_Update.h" // 0x800CDBF4

#include "maps/shared/Ai_PuppetDoctor_Update.h" // 0x800CDC50

#include "maps/shared/Ai_PuppetNurse_SomeAngleCheck.h"

#include "maps/shared/Ai_PuppetNurse_DamageHandle.h" // 0x800CDDE8

#include "maps/shared/Ai_PuppetNurse_Move.h"

#include "maps/shared/sharedFunc_800CE398_3_s03.h" // 0x800CE25C

#include "maps/shared/Ai_PuppetNurse_Control1.h" // 0x800CE290

#include "maps/shared/Ai_PuppetNurse_Control2.h" // 0x800CE3C4

#include "maps/shared/Ai_PuppetNurse_Control3_4.h" // 0x800CE4A8

#include "maps/shared/sharedFunc_800CE7C8_3_s03.h" // 0x800CE68C

#include "maps/shared/Ai_PuppetNurse_Control5.h" // 0x800CE928

#include "maps/shared/Ai_PuppetNurse_Control6_7.h" // 0x800CEA54

#include "maps/shared/Ai_PuppetNurse_Control8.h" // 0x800CEB4C

#include "maps/shared/sharedFunc_800CEEAC_3_s03.h" // 0x800CED70

#include "maps/shared/sharedFunc_800CEEE0_3_s03.h" // 0x800CEDA4

#include "maps/shared/sharedFunc_800CF0B4_3_s03.h" // 0x800CEF78

#include "maps/shared/sharedFunc_800CF294_3_s03.h" // 0x800CF158

#include "maps/shared/Ai_PuppetNurse_Control9.h" // 0x800CF270

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", func_800CF4C4);

#include "maps/shared/sharedFunc_800CF7F4_3_s03.h" // 0x800CF6B8

#include "maps/shared/sharedFunc_800CF90C_3_s03.h" // 0x800CF7D0

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", Ai_PuppetNurse_Control12); // 0x800CF8BC

#include "maps/shared/Ai_PuppetNurse_Control10.h" // 0x800CFBDC

#include "maps/shared/Ai_PuppetNurse_Control11.h" // 0x800CFC98

#include "maps/shared/Ai_PuppetNurse_Control13.h" // 0x800CFFD4

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", g_NursePuppet_SfxOffsets);

INCLUDE_RODATA("asm/maps/map3_s04/nonmatchings/map3_s04", g_PuppetNurse_ModelStates0);

#include "maps/shared/Ai_PuppetNurse_Control.h" // 0x800D0094

#include "maps/shared/sharedFunc_800D02E4_3_s03.h" // 0x800D01A8

INCLUDE_ASM("asm/maps/map3_s04/nonmatchings/map3_s04", sharedFunc_800D03E4_3_s03); // 0x800D02A8

#include "maps/shared/Ai_PuppetNurse_AnimUpdate.h" // 0x800D0570

#include "maps/shared/sharedFunc_800D0828_3_s03.h" // 0x800D06EC

#include "maps/shared/sharedFunc_800D0968_3_s03.h" // 0x800D082C

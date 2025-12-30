#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s01.h"
#include "maps/characters/puppet_nurse.h"

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", g_MapOverlayHeader);

const VECTOR D_800CA5C8 = {};

#include "maps/shared/sharedFunc_800CCB8C_0_s01.h" // 0x800CC9A4

#include "maps/shared/sharedFunc_800CD1F8_0_s01.h" // 0x800CD010

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CDE18

#include "../src/maps/characters/player.c"

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800D16A4

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800D17EC

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800D1914

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800D1934

#include "maps/shared/PuppetNurse_HurtSfxIdGet.h"

#include "maps/shared/Ai_PuppetNurse_SfxPlay.h"

#include "maps/shared/Ai_PuppetNurse_AnimSfxGet.h" // 0x800D1A38

#include "maps/shared/sharedFunc_800CDA88_3_s03.h" // 0x800D1A7C

#include "maps/shared/Ai_PuppetNurse_UpdateMain.h" // 0x800D1AAC

#include "maps/shared/Ai_PuppetNurse_Init.h" // 0x800D1B50

#include "maps/shared/Ai_PuppetNurse_Update.h" // 0x800D1D24

#include "maps/shared/Ai_PuppetDoctor_Update.h" // 0x800D1D80

#include "maps/shared/Ai_PuppetNurse_SomeAngleCheck.h"

#include "maps/shared/Ai_PuppetNurse_DamageHandle.h" // 0x800D1F18

#include "maps/shared/Ai_PuppetNurse_Move.h"

#include "maps/shared/sharedFunc_800CE398_3_s03.h" // 0x800D238C

#include "maps/shared/Ai_PuppetNurse_Control1.h" // 0x800D23C0

#include "maps/shared/Ai_PuppetNurse_Control2.h" // 0x800D24F4

#include "maps/shared/Ai_PuppetNurse_Control3_4.h" // 0x800D25D8

#include "maps/shared/sharedFunc_800CE7C8_3_s03.h" // 0x800D27BC

#include "maps/shared/Ai_PuppetNurse_Control5.h" // 0x800D2A58

#include "maps/shared/Ai_PuppetNurse_Control6_7.h" // 0x800D2B84

#include "maps/shared/Ai_PuppetNurse_Control8.h" // 0x800D2C7C

#include "maps/shared/sharedFunc_800CEEAC_3_s03.h" // 0x800D2EA0

#include "maps/shared/sharedFunc_800CEEE0_3_s03.h" // 0x800D2ED4

#include "maps/shared/sharedFunc_800CF0B4_3_s03.h" // 0x800D30A8

#include "maps/shared/sharedFunc_800CF294_3_s03.h" // 0x800D3288

#include "maps/shared/Ai_PuppetNurse_Control9.h" // 0x800D33A0

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", func_800D35F4);

#include "maps/shared/sharedFunc_800CF7F4_3_s03.h" // 0x800D37E8

#include "maps/shared/sharedFunc_800CF90C_3_s03.h" // 0x800D3900

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", Ai_PuppetNurse_Control12); // 0x800D39EC

#include "maps/shared/Ai_PuppetNurse_Control10.h" // 0x800D3D0C

#include "maps/shared/Ai_PuppetNurse_Control11.h" // 0x800D3DC8

#include "maps/shared/Ai_PuppetNurse_Control13.h" // 0x800D4104

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", g_NursePuppet_SfxOffsets);

INCLUDE_RODATA("asm/maps/map7_s01/nonmatchings/map7_s01", g_PuppetNurse_ModelStates0);

#include "maps/shared/Ai_PuppetNurse_Control.h" // 0x800D41C4

#include "maps/shared/sharedFunc_800D02E4_3_s03.h" // 0x800D42D8

INCLUDE_ASM("asm/maps/map7_s01/nonmatchings/map7_s01", sharedFunc_800D03E4_3_s03); // 0x800D43D8

#include "maps/shared/Ai_PuppetNurse_AnimUpdate.h" // 0x800D46A0

#include "maps/shared/sharedFunc_800D0828_3_s03.h" // 0x800D481C

#include "maps/shared/sharedFunc_800D0968_3_s03.h" // 0x800D495C

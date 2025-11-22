#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s02.h"

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CDC64

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CDDCC

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CDF4C

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CE004

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CE168

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CE188

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CEA00

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CEDEC

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CFC94

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D00E4

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D0120

#include "maps/shared/Player_ControlFreeze.h" // 0x800D012C

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800D028C

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800D0464

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D046C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D051C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D0534

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D055C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D0574

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D059C

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D0640

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D0650

#include "maps/shared/sharedFunc_800D2E6C_0_s00.h" // 0x800D065C

#include "maps/shared/Player_FallBackward.h" // 0x800D0664

#include "maps/shared/sharedFunc_800D2E7C_0_s00.h" // 0x800D066C

#include "maps/shared/sharedFunc_800D2E84_0_s00.h" // 0x800D0674

#include "maps/shared/sharedFunc_800D2E8C_0_s00.h" // 0x800D067C

#include "maps/shared/sharedFunc_800D2E94_0_s00.h" // 0x800D0684

#include "maps/shared/sharedFunc_800D2E9C_0_s00.h" // 0x800D068C

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D0694

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D06A4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D06E4

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D06F8

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D088C

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02", sharedFunc_800D3308_0_s00); // 0x800D0AF8

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D1334

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D16E4

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02", sharedFunc_800D4924_0_s00); // 0x800D16EC

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02", sharedFunc_800D492C_0_s00); // 0x800D22BC

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D2A28

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02", sharedFunc_800D54A8_0_s00); // 0x800D2E38

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D34D8

#include "maps/shared/sharedFunc_800D5C64_0_s00.h" // 0x800D35F4

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D395C

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D3D60

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D3F2C

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D3F34

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D40EC

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D41DC

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02", sharedFunc_800D6970_0_s00); // 0x800D4350

INCLUDE_ASM("asm/maps/map7_s02/nonmatchings/map7_s02", sharedFunc_800D70C4_0_s00); // 0x800D4AA4

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D55C8

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D57E4

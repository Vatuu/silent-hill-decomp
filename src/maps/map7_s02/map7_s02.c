#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s02.h"

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map7_s02/nonmatchings/map7_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CDC64

#include "maps/shared/Player.h"

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D06F8

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D088C

#include "maps/shared/sharedFunc_800D3308_0_s00.h" // 0x800D0AF8

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D1334

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D16E4

#include "maps/shared/sharedFunc_800D4924_0_s00.h" // 0x800D16EC

#include "maps/shared/sharedFunc_800D492C_0_s00.h" // 0x800D22BC

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D2A28

#include "maps/shared/sharedFunc_800D54A8_0_s00.h" // 0x800D2E38

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D34D8

#include "maps/shared/sharedFunc_800D5C64_0_s00.h" // 0x800D35F4

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D395C

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D3D60

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D3F2C

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D3F34

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D40EC

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D41DC

#include "maps/shared/sharedFunc_800D6970_0_s00.h" // 0x800D4350

#include "maps/shared/sharedFunc_800D70C4_0_s00.h" // 0x800D4AA4

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D55C8

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D57E4

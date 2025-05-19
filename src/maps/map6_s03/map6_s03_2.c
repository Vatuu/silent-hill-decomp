#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"

// TODO: Get Makefile to define map define per-map.
// (needed for code differences in `Ai_Stalker_Init`)
#define MAP6_S03 1

#include "maps/shared/Ai_Stalker_Update.h" // 0x800CEFCC

#include "maps/shared/Ai_Stalker_Init.h" // 0x800CF160 - Differs to other maps `Ai_Stalker_Init`.

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D3308_0_s00); // 0x800CF414

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D3B44_0_s00); // 0x800CFC50

void func_800D0000(void) {}

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D0008);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D0BD8);

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D1344

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D1754);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D1DF4);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D1F10);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D2278);

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D267C

void func_800D27F8(void) {}

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D2800

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D29B8

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D2AA8

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D6970_0_s00); // 0x800D2C1C

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D70C4_0_s00); // 0x800D3370

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D7BE8_0_s00); // 0x800D3E94

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D40B0

#include "maps/shared/Ai_HangedScratcher_Update.h" // 0x800D4264

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800CFCA8_5_s00); // 0x800D42E8

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800CFF74_5_s00); // 0x800D45B4

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D029C_5_s00); // 0x800D48DC

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D4A38);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D4A5C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D4B54);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D4C7C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D5284);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D5544);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D56F8);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D58B4);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D5FEC);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D6110);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D624C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D6324);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D64C4);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D6680);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D67C0);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D6A20);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D26D8_5_s00); // 0x800D6D18

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D2844_5_s00); // 0x800D6E84

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D2C18_5_s00); // 0x800D7258

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D7854);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", sharedFunc_800D3300_5_s00); // 0x800D7998

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D7F14

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D7F24);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D7F98);

void func_800D81A4(void) {}

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D81AC);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D822C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D84EC);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D87F0);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D8818);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03_2", func_800D89A0);

void func_800D936C(void) {}

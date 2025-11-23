#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s05.h"

INCLUDE_RODATA("asm/maps/map6_s05/nonmatchings/map6_s05", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s05/nonmatchings/map6_s05", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CA8E8

#include "maps/shared/Player.h"

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC7A4

#include "maps/shared/sharedFunc_800E1114_6_s04.h" // 0x800CC7B4

void func_800CC8F8(s32 arg0)
{
    (arg0 == 1) ? func_800CC930() : func_800CC970();
}

void func_800CC930(void)
{
    func_8003640C(Savegame_EventFlagGet(EventFlag_440) ? 39 : 37);
}

INCLUDE_ASM("asm/maps/map6_s05/nonmatchings/map6_s05", func_800CC970);

void func_800CCBFC(void) {}

INCLUDE_RODATA("asm/maps/map6_s05/nonmatchings/map6_s05", D_800CA62C);

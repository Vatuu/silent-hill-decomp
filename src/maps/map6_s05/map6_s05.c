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

s32 func_800CC7B4(s32 arg0, s32 arg1) // 0x800CC7B4
{
    s32 result;

    if (arg1 > Q12(80.0f))
    {
        result = 5;
    }
    else if (FP_SQUARE_PRECISE(arg0 + Q12(16.0f), Q12_SHIFT) + FP_SQUARE_PRECISE(arg1 + Q12(64.0f), Q12_SHIFT) < Q12(324.0f))
    {
        result = 3;
    }
    else if (FP_SQUARE_PRECISE(arg0 + Q12(-14.0f), Q12_SHIFT) + FP_SQUARE_PRECISE(arg1 + Q12(28.0f), Q12_SHIFT) < Q12(324.0f))
    {
        result = 2;
    }
    else if (FP_SQUARE_PRECISE(arg0 + Q12(14.0f), Q12_SHIFT) + FP_SQUARE_PRECISE(arg1 + Q12(28.0f), Q12_SHIFT) < Q12(25.0f))
    {
        result = 4;
    }
    else
    {
        result = 1;
    }

    return result;
}

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

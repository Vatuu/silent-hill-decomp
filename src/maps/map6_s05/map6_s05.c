#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s05.h"

INCLUDE_RODATA("asm/maps/map6_s05/nonmatchings/map6_s05", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s05/nonmatchings/map6_s05", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CA8E8

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CAA50

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CABD0

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CAC88

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CADEC

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CAE0C

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CB684

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CBA70

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CBD64

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CC190

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CC1CC

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CC1D8

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CC338

s32 func_800CC510()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CC518

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CC5C8

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CC5E0

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CC608

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CC620

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CC648

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CC6EC

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CC6FC

void func_800CC708(void) {}

void func_800CC710(void) {}

void func_800CC718(void) {}

void func_800CC720(void) {}

void func_800CC728(void) {}

s32 func_800CC730()
{
    return 0;
}

void func_800CC738(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CC740

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CC750

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CC790

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC7A4

s32 func_800CC7B4(s32 arg0, s32 arg1)
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

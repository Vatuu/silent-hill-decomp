#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s06.h"

INCLUDE_RODATA("asm/maps/map4_s06/nonmatchings/map4_s06", D_800C9578);

INCLUDE_RODATA("asm/maps/map4_s06/nonmatchings/map4_s06", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CA8D4

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CAA3C

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CABBC

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CAC74

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CADD8

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CADF8

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CB670

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CBA5C

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CBD50

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CC17C

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CC1B8

#include "maps/shared/Player_ControlFreeze.h" // 0x800CC1C4

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800CC324

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800CC4FC

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CC504

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CC5B4

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CC5CC

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CC5F4

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CC60C

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CC634

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CC6D8

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CC6E8

#include "maps/shared/sharedFunc_800D2E6C_0_s00.h" // 0x800CC6F4

#include "maps/shared/sharedFunc_800D2E74_0_s00.h" // 0x800CC6FC

#include "maps/shared/sharedFunc_800D2E7C_0_s00.h" // 0x800CC704

#include "maps/shared/sharedFunc_800D2E84_0_s00.h" // 0x800CC70C

#include "maps/shared/sharedFunc_800D2E8C_0_s00.h" // 0x800CC714

#include "maps/shared/sharedFunc_800D2E94_0_s00.h" // 0x800CC71C

#include "maps/shared/sharedFunc_800D2E9C_0_s00.h" // 0x800CC724

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CC72C

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CC73C

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CC77C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC790

INCLUDE_ASM("asm/maps/map4_s06/nonmatchings/map4_s06", func_800CC7A0);

void func_800CC99C(void) // 0x800CC99C
{
    s32 flags;

    flags = 0x2;

    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 17:
            if (Savegame_EventFlagGet(EventFlag_295) && !Savegame_EventFlagGet(EventFlag_352))
            {
                flags = (1 << 1) | (1 << 2);
            }
            break;

        case 12:
            if (!Savegame_EventFlagGet(EventFlag_295))
            {
                flags = (1 << 1) | (1 << 4);
            }
            break;
    }

    if (Savegame_EventFlagGet(EventFlag_M3S06_PickupAntiqueShopKey))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_AntiqueShopOpen))
        {
            flags |= 1 << 3;
        }
    }

    if (flags & (1 << 3))
    {
        s8 temp_v0 = func_800364BC();
        D_800CCB8F = temp_v0;
    }

    func_80035F4C(flags, Q12(0.1f), D_800CCB8C);
}

void func_800CCA88(void) {}

void func_800CCA90(void) {}

void func_800CCA98(void) {}

INCLUDE_RODATA("asm/maps/map4_s06/nonmatchings/map4_s06", D_800CA618);

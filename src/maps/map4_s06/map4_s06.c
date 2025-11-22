#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s06.h"

INCLUDE_RODATA("asm/maps/map4_s06/nonmatchings/map4_s06", D_800C9578);

INCLUDE_RODATA("asm/maps/map4_s06/nonmatchings/map4_s06", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CA8D4

#include "maps/shared/Player.h"

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

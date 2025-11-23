#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s01.h"

// TODO: Func declarations in header.

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map4_s01/nonmatchings/map4_s01", g_MapOverlayHeader);

void func_800CC19C(void) // 0x800CC19C
{
    s32 i;
    s32 counterC;

    if (D_800D7F20.field_0 & (1 << 0))
    {
        D_800D7F20.field_1A = D_800D7F20.field_1C * 2;
        D_800D7F20.field_18 = D_800D7F20.field_1A;
    }
    else
    {
        D_800D7F20.field_1C = (D_800D7F20.field_18 + D_800D7F20.field_1A) >> 1;
    }

    D_800D7F20.field_16 = D_800D7F20.field_12 - D_800D7F20.field_14;
    if (D_800D7F20.field_1)
    {
        D_800D7F20.field_10 = 0x1000;
    }
    else
    {
        D_800D7F20.field_10 = 0;
    }

    counterC = D_800D7F20.field_C;
    
    for (i = ARRAY_SIZE(D_800D5B20) - 1; i >= 0; i--)
    {
        if (D_800D5B20[i].field_A == 0)
        {
            if (D_800D7F20.field_1 == 0)
            {
                func_800CC2C4(i, 0);
            }
            else
            {
                D_800D5B20[i].field_A = 12;
            }

            counterC--;
            if (!counterC)
            {
                break;
            }
        }
    }

    D_800C4414 |= 1;
}

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", func_800CC2C4);

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", func_800CC70C);

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", func_800CCF50);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CD548

#include "maps/shared/Player.h"

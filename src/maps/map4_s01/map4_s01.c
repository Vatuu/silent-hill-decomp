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
    i = ARRAY_SIZE(D_800D5B20) - 1;
    do
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

        i--;
    }
    while (i >= 0);

    D_800C4414 |= 1;
}

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", func_800CC2C4);

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", func_800CC70C);

INCLUDE_ASM("asm/maps/map4_s01/nonmatchings/map4_s01", func_800CCF50);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h"

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CD6B0

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD830

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD8E8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CDA4C

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CDA6C

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CE2E4

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CE6D0

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CF3B0

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CF7DC

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CF818

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CF824

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CF984

s32 func_800CFB5C() // 0x800CFB5C
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CFB64

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CFC14

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CFC2C

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CFC54

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CFC6C

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CFC94

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CFD38

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CFD48

void func_800CFD54(void) {}

void func_800CFD5C(void) {}

void func_800CFD64(void) {}

void func_800CFD6C(void) {}

void func_800CFD74(void) {}

s32 func_800CFD7C() // 0x800CFD7C
{
    return 0;
}

void func_800CFD84(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CFD8C

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CFD9C

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CFDDC


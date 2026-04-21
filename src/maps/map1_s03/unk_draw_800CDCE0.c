#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map1/map1_s03.h"
#include "maps/particle.h"
#include "maps/characters/creeper.h"
#include "maps/characters/locker_dead_body.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"

void func_800CDCE0(s32 arg0, s32 arg1, s32 arg2) // 0x800CDCE0
{
    s16 tmp0;
    s16 offsetX; // } Implied Q8.
    s16 offsetZ; // }
    s32 zOff2;
    s32 i;

    switch (D_800E3A40[arg1].idx_14)
    {
        case 0:
            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0;
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4;
            break;

        case 1:
            // TODO: Not sure if this fits any RNG macro?
            tmp0 = (Rng_Rand16() % D_800E3A40[arg1].field_C) - (D_800E3A40[arg1].field_C >> 1);
            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0 + FP_FROM((tmp0 * Math_Sin(D_800E3A40[arg1].field_A)), Q12_SHIFT);
            zOff2 = FP_FROM((tmp0 * Math_Cos(D_800E3A40[arg1].field_A)), Q12_SHIFT);
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4 + zOff2;
            break;

        case 2:
            for (i = 0; i < 8; i++)
            {
                offsetX = Rng_GenerateInt(-D_800E3A40[arg1].field_C, D_800E3A40[arg1].field_C - 1);
                offsetZ = Rng_GenerateInt(-D_800E3A40[arg1].field_C, D_800E3A40[arg1].field_C - 1);
                if ((SQUARE(offsetX) + SQUARE(offsetZ)) < (D_800E3A40[arg1].field_C * D_800E3A40[arg1].field_C))
                {
                    break;
                }
            }

            if (i == 8)
            {
                offsetZ = 0;
                offsetX = 0;
            }

            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0 + offsetX;
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4 + offsetZ;
            break;

        case 3:
            offsetX = Rng_GenerateUInt(0, Q12_ANGLE(360.0f) - 1);
            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0 + FP_FROM((D_800E3A40[arg1].field_C * Math_Sin(offsetX)), Q12_SHIFT);
            zOff2 = FP_FROM((D_800E3A40[arg1].field_C * Math_Cos(offsetX)), Q12_SHIFT);
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4 + zOff2;
            break;

        case 4:
            offsetX = Rng_AddGeneratedUInt(D_800E3A40[arg1].field_A, Q12_ANGLE(-90.0f), Q12_ANGLE(90.0f) - 1);
            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0 + FP_FROM((D_800E3A40[arg1].field_C * Math_Sin(offsetX)), Q12_SHIFT);
            zOff2 = FP_FROM((D_800E3A40[arg1].field_C * Math_Cos(offsetX)), Q12_SHIFT);
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4 + zOff2;
            break;
    }

    sharedData_800DFB7C_0_s00[arg0].vy_8 = D_800E3A40[arg1].field_8;

    if (arg2 == 0)
    {
        sharedData_800DFB7C_0_s00[arg0].field_C.s_0.field_0 = Rng_GenerateInt(0, D_800E3A40[arg1].field_10 - 1);
    }
    else
    {
        sharedData_800DFB7C_0_s00[arg0].field_C.s_0.field_0 = sharedData_800DFB7C_0_s00[arg0].field_C.field_0 - D_800E3A40[arg1].field_10;
    }

    sharedData_800DFB7C_0_s00[arg0].field_C.s_1.field_2  = Rng_GenerateUInt(0, 3);
    sharedData_800DFB7C_0_s00[arg0].field_C.s_1.field_3  = Rng_GenerateUInt(96, 159);
    sharedData_800DFB7C_0_s00[arg0].field_10.s_2.field_0 = arg1;
}

void func_800CE0CC(s32 arg0) // 0x800CE0CC
{
    s32 idx;
    s32 i;

    for (i = 0; i < D_800E3A40[arg0].field_12; i++)
    {
        idx = func_8005E7E0(28);
        if (idx == NO_VALUE)
        {
            break;
        }

        func_800CDCE0(idx, arg0, 0);
    }
}

bool func_800CE164(POLY_FT4** poly, s32 idx) // 0x800CE164
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        DVECTOR         field_134;
        s32             field_138;
    } s_ScratchData;

    s_ScratchData* scratch = PSX_SCRATCH;
    s32            idx2;
    s32            var_lo;
    s32            var_a2;
    s32            var_a1;
    s32            rgbColor;

    sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 += g_DeltaTime;

    idx2 = sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0;
    if ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 > D_800E3A40[idx2].field_10)
    {
        func_800CDCE0(idx, idx2, 1);
        return false;
    }

    Math_SetSVectorFastSum(&scratch->field_12C,
                           Q12_TO_Q8(sharedData_800DFB7C_0_s00[idx].field_0.vx_0) - (u16)scratch->field_0.field_0.vx,
                           Q12_TO_Q8((s32)sharedData_800DFB7C_0_s00[idx].vy_8) - scratch->field_0.field_0.vy,
                           Q12_TO_Q8(sharedData_800DFB7C_0_s00[idx].field_4.vz_4) - scratch->field_0.field_0.vz);

    gte_ldv0(&scratch->field_12C);
    gte_rtps();
    gte_stsxy(&scratch->field_134.vx);
    gte_stsz(&scratch->field_138);

    var_lo = FP_TO((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0, Q12_SHIFT) / D_800E3A40[idx2].field_10;

    setPolyFT4(*poly);

    var_a2 = (FP_FROM(Q12_MULT_PRECISE(D_800E3A40[idx2].field_E * sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_3, Math_Sin(var_lo >> 2)), Q12_SHIFT) * scratch->field_0.field_2C) / scratch->field_138;
    var_a1 = (var_a2 * (0x800 - ABS(scratch->field_0.field_30.vx))) >> 10;

    setXY0Fast(*poly, (u16)scratch->field_134.vx - var_a2, scratch->field_134.vy - var_a1);
    setXY1Fast(*poly, (u16)scratch->field_134.vx + var_a2, scratch->field_134.vy - var_a1);
    setXY2Fast(*poly, (u16)scratch->field_134.vx - var_a2, scratch->field_134.vy);
    setXY3Fast(*poly, (u16)scratch->field_134.vx + var_a2, scratch->field_134.vy);

    *(u32*)&(*poly)->u0 = ((sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 13) + 0xE0000);
    *(u32*)&(*poly)->u1 = ((sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 13) + 0x2D003F);
    *(u16*)&(*poly)->u2 = ((sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 13) | 0x1F00);
    *(u16*)&(*poly)->u3 = ((sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 13) | 0x1F3F);

    setSemiTrans(*poly, true);

    if (var_lo < 0x800)
    {
        rgbColor = Q12_MULT_PRECISE((var_lo * 2), 0x80);
    }
    else
    {
        rgbColor = 0x80 - Q12_MULT_PRECISE(((var_lo - 0x800) * 2), 0x80);
    }

    rgbColor = (rgbColor * func_80055D78(sharedData_800DFB7C_0_s00[idx].field_0.vx_0, sharedData_800DFB7C_0_s00[idx].vy_8, sharedData_800DFB7C_0_s00[idx].field_4.vz_4)) >> 7;

    setRGB0Fast(*poly, rgbColor, rgbColor, rgbColor);

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(scratch->field_138 + 256) >> 3], *poly);

    *poly += 1;

    return true;
}

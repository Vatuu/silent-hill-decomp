#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"

void func_800CB0D8(void) // 0x800CB0D8
{
    s32 idx;
    s32 i;

    idx = func_8005E7E0(32);
    if (idx == NO_VALUE)
    {
        return;
    }

    sharedData_800DFB7C_0_s00[idx].field_B = 0;
    sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 = Rng_GenerateInt(0, 2);

    for (i = 0; i < 12; i++)
    {
        idx = func_8005E7E0(32);
        if (idx == NO_VALUE)
        {
            break;
        }

        sharedData_800DFB7C_0_s00[idx].field_B = 1;
        sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = Rng_GenerateInt(Q12(-92.75f), Q12(-91.25f) - 1);
        sharedData_800DFB7C_0_s00[idx].vy_8 = Q12(0.5f);
        sharedData_800DFB7C_0_s00[idx].field_4.vz_4 = Rng_GenerateInt(Q12(7.35f), Q12(8.85f) - 1);
        sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 = Rng_GenerateUInt(0, Q12_CLAMPED(1.0f));
        sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 = Rng_GenerateInt(0, 2);
    }
}

bool func_800CB25C(POLY_FT4** poly, s32 idx) // 0x800CB25C
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C[3];
        DVECTOR         field_144;
        VECTOR3         field_148;
        s32             field_154;
        s32             field_158;
        s32             field_15C;
        s32             field_160;
    } s_func_800CB25C;

    DVECTOR          sp10[5][5];
    s32              sp78[5][5];
    s32              j;
    s32              i;
    s32              var_v0_4;
    s_func_800CB25C* ptr;

    ptr = PSX_SCRATCH;

    if (g_SysWork.playerWork_4C.player_0.position.vx > Q12(-80.0f))
    {
        return false;
    }

    if (g_SysWork.playerWork_4C.player_0.position.vz < Q12(0.0f))
    {
        return false;
    }

    if (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1))
    {
        if (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))
        {
            return false;
        }
    }

    if (sharedData_800DFB7C_0_s00[idx].field_B != 0)
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 += Rng_GenerateUInt(-0x20, 0x20 - 1);
        sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0  = CLAMP_MIN_THEN_LOW(sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0, 0, 0xFFF);

        ptr->field_15C = Q12_MULT_PRECISE(sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0, Q12(1.5f));

        setPolyFT4(*poly);

        Math_SetSVectorFastSum(&ptr->field_12C[0], ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 - ptr->field_15C) >> 4) - (u16)ptr->field_0.field_0.vx,
                               ((sharedData_800DFB7C_0_s00[idx].vy_8) >> 4) - ptr->field_0.field_0.vy,
                               ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ptr->field_15C) >> 4) - ptr->field_0.field_0.vz);

        Math_SetSVectorFastSum(&ptr->field_12C[1], ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ptr->field_15C) >> 4) - (u16)ptr->field_0.field_0.vx,
                               ((sharedData_800DFB7C_0_s00[idx].vy_8) >> 4) - ptr->field_0.field_0.vy,
                               ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ptr->field_15C) >> 4) - ptr->field_0.field_0.vz);

        Math_SetSVectorFastSum(&ptr->field_12C[2], ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 - ptr->field_15C) >> 4) - (u16)ptr->field_0.field_0.vx,
                               ((sharedData_800DFB7C_0_s00[idx].vy_8) >> 4) - ptr->field_0.field_0.vy,
                               ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 - ptr->field_15C) >> 4) - ptr->field_0.field_0.vz);

        gte_ldv3c(&ptr->field_12C);
        gte_rtpt();
        gte_stsxy3_g3(*poly);
        gte_stsz3c(&ptr->field_148);

        Math_SetSVectorFastSum(&ptr->field_12C[0], ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ptr->field_15C) >> 4) - (u16)ptr->field_0.field_0.vx,
                               ((sharedData_800DFB7C_0_s00[idx].vy_8) >> 4) - ptr->field_0.field_0.vy,
                               ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 - ptr->field_15C) >> 4) - ptr->field_0.field_0.vz);

        gte_ldv0(&ptr->field_12C);
        gte_rtps();
        gte_stsxy(&ptr->field_144);
        gte_stsz(&ptr->field_154);

        ptr->field_148.vx = (ptr->field_148.vx + ptr->field_148.vy + ptr->field_148.vz + ptr->field_154) >> 2;

        if (ptr->field_148.vx <= 0 || (ptr->field_148.vx >> 3) >= ORDERING_TABLE_SIZE)
        {
            return false;
        }

        if (ABS(ptr->field_144.vx) > 200 || ABS(ptr->field_144.vy) > 160)
        {
            return false;
        }

        *(s32*)&(*poly)->x3 = *(s32*)&ptr->field_144;
        setSemiTrans(*poly, 1);

        if (CLAMP_LOW(Q12_MULT_PRECISE(0x1000 - sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0, 0x20), 0) < 0x10)
        {
            var_v0_4 = MAX(Q12_MULT_PRECISE(0x1000 - sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0, 0x20), 0);
        }
        else
        {
            var_v0_4 = 0x10;
        }

        ptr->field_160 = var_v0_4;

        setUV0AndClutSum(*poly, 224, 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5), 0x13);
        setUV1AndTPageSum(*poly, 255, 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5), 0x4B);
        setUV2Sum(*poly, 224, 191 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5));
        setUV3Sum(*poly, 255, 191 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5));

        setRGB0Fast(*poly, ptr->field_160, ptr->field_160, ptr->field_160);

        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_148.vx + 0x80) >> 3], *poly);
        *poly += 1;
    }
    else
    {
        for (i = 0; i < 25; i += 3)
        {
            for (j = 0; j < 3; j++)
            {
                Math_SetSVectorFastSum(&ptr->field_12C[j], ((((((i + j) % 5) * Q12(1.5f)) >> 1) - Q12(93.5f)) >> 4) - (u16)ptr->field_0.field_0.vx,
                                       0x80 - ptr->field_0.field_0.vy,
                                       ((0x9999 - ((i + j) / 5 * Q12(1.5f) >> 1)) >> 4) - ptr->field_0.field_0.vz);
            }

            gte_ldv3c(&ptr->field_12C[0]);
            gte_rtpt();
            gte_stsxy3c(&sp10[i / 5][i % 5]);
            gte_stsz3c(&sp78[i / 5][i % 5]);
        }

        Math_SetSVectorFastSum(&ptr->field_12C[0], -0x5A80 - (u16)ptr->field_0.field_0.vx,
                               0x80 - ptr->field_0.field_0.vy,
                               0x699 - ptr->field_0.field_0.vz);

        gte_ldv0(&ptr->field_12C);
        gte_rtps();
        gte_stsxy(&sp10[4][4]);
        gte_stsz(&sp78[4][4]);

        ptr->field_160 = !(func_80055D78(Q12(-92.0f), Q12(0.5f), Q12(8.1f)) < 129) * 8;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (sp78[i][j] <= 0 || (sp78[i][j] >> 3) >= ORDERING_TABLE_SIZE)
                {
                    continue;
                }

                if (ABS(sp10[i][j].vx) > 200 || ABS(sp10[i][j].vy) > 160)
                {
                    continue;
                }

                setPolyFT4(*poly);

                setXY4(*poly,
                       sp10[i][j].vx, sp10[i][j].vy,
                       sp10[i][j + 1].vx, sp10[i][j + 1].vy,
                       sp10[i + 1][j].vx, sp10[i + 1][j].vy,
                       sp10[i + 1][j + 1].vx, sp10[i + 1][j + 1].vy);

                setSemiTrans(*poly, 1);

                *(u16*)&(*poly)->r0 = ptr->field_160;
                (*poly)->b0         = 0;

                setUV0AndClutSum(*poly, 224 + (j * 8), (i * 8) + 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5), 0x0293);
                setUV1AndTPageSum(*poly, 231 + (j * 8), (i * 8) + 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5), 0x2B);
                setUV2Sum(*poly, 224 + (j * 8), (i * 8) + 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5) + 7);
                setUV3Sum(*poly, 231 + (j * 8), (i * 8) + 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5) + 7);

                ptr->field_158 = (sp78[i][j] + sp78[i + 1][j] + sp78[i][j + 1] + sp78[i + 1][j + 1]) >> 2;

                addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_158 + 0x80) >> 3], *poly);
                *poly += 1;
            }
        }
    }

    return true;
}

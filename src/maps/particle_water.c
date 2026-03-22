#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"

#if defined(MAP1_S02)
#include "maps/map1/map1_s02.h" // For `sharedData_800DFB7C_0_s00` size.
#elif defined(MAP1_S03)
#include "maps/map1/map1_s03.h" // For `sharedData_800DFB7C_0_s00` size.
#endif

// Waterfall particle effect? Included in M1S02 and M1S03.
// Called by cutscene event code and M1S02 `Map_WorldObjectsUpdate`, likely draws the water used in the school key puzzle.
// TODO: Make this separate split in each map instead of `#include`.

void sharedFunc_800CBA4C_1_s02(s32 idx, s32 arg1, s32 arg2)
{
    s32 temp_a1;
    s32 var_s2;
    s32 temp;

    var_s2 = arg2;

    if (arg1 == 2)
    {
        var_s2                                              = Rng_Rand16() % sharedData_800E30C8_1_s02.field_78;
        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0 = Rng_Rand16() % sharedData_800E30C8_1_s02.field_28[var_s2];
    }
    else
    {
        var_s2                                               = var_s2 % sharedData_800E30C8_1_s02.field_78;
        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0 = 0;
    }

    sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = sharedData_800E30C8_1_s02.field_0[var_s2];
    sharedData_800DFB7C_0_s00[idx].vy_8         = sharedData_800E30C8_1_s02.field_10[var_s2];
    sharedData_800DFB7C_0_s00[idx].field_4.vz_4 = sharedData_800E30C8_1_s02.field_18[var_s2];

    if (sharedData_800E30C8_1_s02.field_30[var_s2] == 0)
    {
        if (arg1 == 2)
        {
            sharedData_800DFB7C_0_s00[idx].field_0.vx_0 += Q12_MULT(sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0, Math_Sin(sharedData_800E30C8_1_s02.field_34[var_s2]));
            sharedData_800DFB7C_0_s00[idx].field_4.vz_4 += Q12_MULT(sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0, Math_Cos(sharedData_800E30C8_1_s02.field_34[var_s2]));
        }

        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 = (sharedData_800E30C8_1_s02.field_6c[var_s2] * (Rng_GenerateUInt(96, 159))) >> 7;
    }
    else
    {
        if (arg1 == 2)
        {
            sharedData_800DFB7C_0_s00[idx].vy_8 += sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0;
        }

        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 = Rng_GenerateUInt(112, 143);
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2  = 0;
    }

    temp_a1 = Rng_Rand16() % 3;
    temp    = 4;

    sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_0 = (temp_a1 ? (temp_a1 + 1) : 0) + (var_s2 * temp);
}

void sharedFunc_800CBC98_1_s02(void)
{
    s32 idx;
    s32 i;

    for (i = 0; i < sharedData_800E30C8_1_s02.field_74; i++)
    {
        idx = func_8005E7E0(27);
        if (idx == NO_VALUE)
        {
            break;
        }

        sharedFunc_800CBA4C_1_s02(idx, 2, 0);
    }

    for (i = 0; i < sharedData_800E30C8_1_s02.field_78; i++)
    {
        sharedData_800E30C8_1_s02.field_54[i] = 0;
    }

    D_800C4414 |= 1 << 3;
}

void sharedFunc_800CBD58_1_s02(void)
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(sharedData_800DFB7C_0_s00); i++)
    {
        if (sharedData_800DFB7C_0_s00[i].field_A == 27 || sharedData_800DFB7C_0_s00[i].field_A == 28)
        {
            sharedData_800DFB7C_0_s00[i].field_A = 0;
        }
    }

    D_800C4414 &= ~(1 << 3);
}

bool sharedFunc_800CBDA8_1_s02(POLY_FT4** poly, s32 idx)
{
    #define CLAMP_MAX(x, max) \
        (((x) >= (max)) ? (max) : (x))

    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        SVECTOR         field_134;
        SVECTOR         field_13C;
        SVECTOR         field_144;
        DVECTOR         field_14C;
        VECTOR3         field_150;
        s32             field_15C;
        s32             field_160;
        s32             field_164;
        s32             field_168;
        s32             field_16C;
        s32             field_170;
        s16             field_174;
        s16             field_176;
        s16             field_178;
        s16             field_17A;
        u8              field_17C; // Q6
        u8              field_17D; // Q6
        u8              unk_17E[2];
        s32             field_180;
    } s_func_800CBDA8;

    s32              temp_s4;
    s32              temp_v1_5;
    s32              var_s1;
    q19_12           var_s3;
    s32              var_v1;
    s32              idx0;
    u8               temp_v1_13;
    u8               temp_v1_14;
    u8               temp_v1_15;
    u8               temp_v1_16;
    s_func_800CBDA8* ptr;
    volatile s32     pad;

    ptr = PSX_SCRATCH;

    idx0 = sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_0 >> 2;

    if (sharedData_800E30C8_1_s02.field_30[idx0] == 0)
    {
        temp_s4 = Q12_MULT_PRECISE(g_DeltaTime, sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_2);

        if ((sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0 + temp_s4) < sharedData_800E30C8_1_s02.field_28[idx0])
        {
            sharedData_800DFB7C_0_s00[idx].field_0.vx_0 += Q12_MULT(temp_s4, ptr->field_0.field_DC[idx0]);
            sharedData_800DFB7C_0_s00[idx].field_4.vz_4 += Q12_MULT(temp_s4, ptr->field_0.field_E4[idx0]);
        }
        else if ((sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0 + temp_s4) >= (sharedData_800E30C8_1_s02.field_28[idx0] + sharedData_800E30C8_1_s02.field_64[idx0]))
        {
            sharedFunc_800CBA4C_1_s02(idx, 3, idx0 + 1);
            return false;
        }
        else if (sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0 < sharedData_800E30C8_1_s02.field_28[idx0])
        {
            sharedData_800DFB7C_0_s00[idx].field_0.vx_0 += FP_MULTIPLY((sharedData_800E30C8_1_s02.field_28[idx0] -
                                                                        sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0),
                                                                       ptr->field_0.field_DC[idx0], Q12_SHIFT);
            sharedData_800DFB7C_0_s00[idx].field_4.vz_4 += FP_MULTIPLY((sharedData_800E30C8_1_s02.field_28[idx0] -
                                                                        sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0),
                                                                       ptr->field_0.field_E4[idx0], Q12_SHIFT);
        }

        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0 += temp_s4;
        temp_s4                                              = sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0;

        if (temp_s4 < sharedData_800E30C8_1_s02.field_64[idx0])
        {
            var_s3         = TO_FIXED(temp_s4, Q12_SHIFT) / sharedData_800E30C8_1_s02.field_64[idx0];
            ptr->field_17C = Q6(0.0f);
            ptr->field_17D = Q12_TO_Q6(var_s3);
            ptr->field_174 = sharedData_800E30C8_1_s02.field_10[idx0];
        }
        else
        {
            if (sharedData_800E30C8_1_s02.field_28[idx0] < temp_s4)
            {
                var_s3 = TO_FIXED(sharedData_800E30C8_1_s02.field_28[idx0] + sharedData_800E30C8_1_s02.field_64[idx0] - temp_s4, Q12_SHIFT) / sharedData_800E30C8_1_s02.field_64[idx0];

                ptr->field_17C = (Q6(1.0f) - 1) - Q12_TO_Q6(var_s3);
                ptr->field_17D = Q12_TO_Q6(var_s3);
                ptr->field_176 = sharedData_800E30C8_1_s02.field_10[idx0 + 1];
            }
            else
            {
                var_s3         = Q12(1.0f);
                ptr->field_17C = Q6(0.0f);
                ptr->field_17D = Q6(1.0f) - 1;
            }
        }

        if (temp_s4 >= sharedData_800E30C8_1_s02.field_64[idx0])
        {
            ptr->field_174 = (sharedData_800E30C8_1_s02.field_10[idx0] + (((sharedData_800E30C8_1_s02.field_10[idx0 + 1] -
                                                                               sharedData_800E30C8_1_s02.field_10[idx0]) *
                                                                              (temp_s4 - sharedData_800E30C8_1_s02.field_64[idx0])) /
                                                                             sharedData_800E30C8_1_s02.field_28[idx0]));
        }

        if (sharedData_800E30C8_1_s02.field_28[idx0] >= temp_s4)
        {
            ptr->field_176 = (sharedData_800E30C8_1_s02.field_10[idx0] + (((sharedData_800E30C8_1_s02.field_10[idx0 + 1] -
                                                                               sharedData_800E30C8_1_s02.field_10[idx0]) *
                                                                              temp_s4) /
                                                                             sharedData_800E30C8_1_s02.field_28[idx0]));
        }

        if (idx0 == (sharedData_800E30C8_1_s02.field_78 - 1) &&
            (sharedData_800E30C8_1_s02.field_28[idx0] - sharedData_800E30C8_1_s02.field_28[sharedData_800E30C8_1_s02.field_78]) < temp_s4)
        {
            temp_v1_5 = sharedData_800E30C8_1_s02.field_28[idx0] - sharedData_800E30C8_1_s02.field_28[sharedData_800E30C8_1_s02.field_78];

            var_s1 = Q12(CLAMP_MAX(sharedData_800E30C8_1_s02.field_28[idx0], temp_s4) - temp_v1_5) / sharedData_800E30C8_1_s02.field_28[sharedData_800E30C8_1_s02.field_78];

            ptr->field_180 = Q12_MULT_PRECISE(var_s3 >> 5, Math_Cos(var_s1 >> 2));

            ptr->field_178 = Q12_MULT_PRECISE(Q12(1.0f) - var_s1, sharedData_800E30C8_1_s02.field_5C[idx0] >> 1) +
                             Q12_MULT_PRECISE(var_s1, sharedData_800E30C8_1_s02.field_5C[idx0 + 1] >> 1);

            ptr->field_17A = Q12_MULT_PRECISE(Q12(1.0f) - var_s1, sharedData_800E30C8_1_s02.field_64[idx0]) +
                             Q12_MULT_PRECISE(var_s1, sharedData_800E30C8_1_s02.field_64[idx0 + 1]);

            ptr->field_164 = ptr->field_178 * Math_Sin(sharedData_800E30C8_1_s02.field_34[idx0]);
            ptr->field_168 = ptr->field_178 * Math_Cos(sharedData_800E30C8_1_s02.field_34[idx0]);

            ptr->field_16C = Q12_MULT_PRECISE(var_s3, ptr->field_17A * Math_Sin(sharedData_800E30C8_1_s02.field_34[idx0]));
            ptr->field_170 = Q12_MULT_PRECISE(var_s3, ptr->field_17A * Math_Cos(sharedData_800E30C8_1_s02.field_34[idx0]));
        }
        else
        {
            ptr->field_180 = var_s3 >> 5;

            ptr->field_164 = ptr->field_0.u_field_EC.raw_0[idx0];
            ptr->field_168 = ptr->field_0.u_field_FC.raw_0[idx0];

            ptr->field_16C = Q12_MULT_PRECISE(var_s3, ptr->field_0.field_10C[idx0]);
            ptr->field_170 = Q12_MULT_PRECISE(var_s3, ptr->field_0.field_11C[idx0]);
        }

        if (idx0 < (sharedData_800E30C8_1_s02.field_78 - 1))
        {

            if (sharedData_800E30C8_1_s02.field_30[idx0 + 1] == 0)
            {
                var_s1 = ABS(Q12_MULT(sharedData_800E30C8_1_s02.field_5C[idx0 + 1], Math_Sin(sharedData_800E30C8_1_s02.field_34[idx0] - sharedData_800E30C8_1_s02.field_34[idx0 + 1])));
                var_v1 = sharedData_800E30C8_1_s02.field_28[idx0] - temp_s4;

                if (var_v1 < var_s1)
                {
                    if (var_v1 >= 0)
                    {
                        var_v1 = Q12(var_v1) / var_s1;
                    }
                    else
                    {
                        var_v1 = 0;
                    }

                    ptr->field_180 = Q12_MULT_PRECISE(var_v1, ptr->field_180);
                }
            }
        }

        if (idx0 > 0)
        {
            if (sharedData_800E30C8_1_s02.field_30[idx0 - 1] == 0)
            {
                var_s3 = sharedData_800E30C8_1_s02.field_64[idx0];

                if ((sharedData_800E30C8_1_s02.field_5C[idx0 - 1] * Math_Sin(sharedData_800E30C8_1_s02.field_34[idx0 - 1] - sharedData_800E30C8_1_s02.field_34[idx0])) < 0)
                {
                    var_s1 = var_s3 - FP_MULTIPLY(sharedData_800E30C8_1_s02.field_5C[idx0 - 1],
                                                  Math_Sin(sharedData_800E30C8_1_s02.field_34[idx0 - 1] - sharedData_800E30C8_1_s02.field_34[idx0]), Q12_SHIFT);
                }
                else
                {
                    var_s1 = var_s3 + FP_MULTIPLY(sharedData_800E30C8_1_s02.field_5C[idx0 - 1],
                                                  Math_Sin(sharedData_800E30C8_1_s02.field_34[idx0 - 1] - sharedData_800E30C8_1_s02.field_34[idx0]), Q12_SHIFT);
                }

                if (temp_s4 < var_s1)
                {
                    ptr->field_180 = Q12_MULT_PRECISE(Q12(temp_s4) / var_s1, ptr->field_180);
                }
            }
        }

        setPolyFT4(*poly);

        *(s32*)&ptr->field_12C = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + (ptr->field_168 >> Q12_SHIFT)) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                 (((ptr->field_174 >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_12C.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + (-ptr->field_164 >> Q12_SHIFT)) >> 4) - ptr->field_0.field_0.vz;

        *(s32*)&ptr->field_134 = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + (-ptr->field_168 >> Q12_SHIFT)) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                 (((ptr->field_174 >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_134.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + (ptr->field_164 >> Q12_SHIFT)) >> 4) - ptr->field_0.field_0.vz;

        *(s32*)&ptr->field_13C = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ((ptr->field_168 - ptr->field_16C) >> Q12_SHIFT)) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                 (((ptr->field_176 >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_13C.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ((-ptr->field_164 - ptr->field_170) >> Q12_SHIFT)) >> 4) - ptr->field_0.field_0.vz;

        *(s32*)&ptr->field_144 = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ((-ptr->field_168 - ptr->field_16C) >> Q12_SHIFT)) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                 (((ptr->field_176 >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_144.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ((ptr->field_164 - ptr->field_170) >> Q12_SHIFT)) >> 4) - ptr->field_0.field_0.vz;
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 = MIN(sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_2 + ((g_GravitySpeed * sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_2) >> 7),
                                                                 Q12(6.0f));

        temp_s4 = Q12_MULT_PRECISE(g_DeltaTime, sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_2);

        if (sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0 + temp_s4 >= (sharedData_800E30C8_1_s02.field_28[idx0] + sharedData_800E30C8_1_s02.field_64[idx0]))
        {
            sharedFunc_800CBA4C_1_s02(idx, 3, idx0 + 1);
            return false;
        }

        sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0 = sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0 + temp_s4;
        sharedData_800DFB7C_0_s00[idx].vy_8                 = sharedData_800DFB7C_0_s00[idx].vy_8 + temp_s4;

        temp_s4 = sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0;

        if (temp_s4 < sharedData_800E30C8_1_s02.field_64[idx0])
        {
            var_s3 = Q12(temp_s4) / sharedData_800E30C8_1_s02.field_64[idx0];

            ptr->field_17C = Q6(0.0f);
            ptr->field_17D = Q12_TO_Q6(var_s3);
        }
        else
        {
            if (sharedData_800E30C8_1_s02.field_28[idx0] < temp_s4)
            {
                var_s3 = Q12((sharedData_800E30C8_1_s02.field_28[idx0] + sharedData_800E30C8_1_s02.field_64[idx0]) - temp_s4) / sharedData_800E30C8_1_s02.field_64[idx0];

                ptr->field_17C = (Q6(1.0f) - 1) - Q12_TO_Q6(var_s3);
                ptr->field_17D = Q12_TO_Q6(var_s3);
            }
            else
            {
                var_s3 = Q12(1.0f);

                ptr->field_17C = Q6(0.0f);
                ptr->field_17D = Q6(1.0f) - 1;
            }
        }

        ptr->field_180 = var_s3 >> 5;
        ptr->field_16C = Q12_MULT_PRECISE(var_s3, sharedData_800E30C8_1_s02.field_64[idx0]);

        setPolyFT4(*poly);

        *(s32*)&ptr->field_12C = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ptr->field_0.u_field_EC.field_0[idx0].vx) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                 (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_12C.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ptr->field_0.u_field_FC.field_0[idx0].vx) >> 4) - ptr->field_0.field_0.vz;

        *(s32*)&ptr->field_134 = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ptr->field_0.u_field_EC.field_0[idx0].vy) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                 (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_134.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ptr->field_0.u_field_FC.field_0[idx0].vy) >> 4) - ptr->field_0.field_0.vz;

        *(s32*)&ptr->field_13C = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ptr->field_0.u_field_EC.field_0[idx0].vx) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                 ((((sharedData_800DFB7C_0_s00[idx].vy_8 + ptr->field_16C) >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_13C.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ptr->field_0.u_field_FC.field_0[idx0].vx) >> 4) - ptr->field_0.field_0.vz;

        *(s32*)&ptr->field_144 = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ptr->field_0.u_field_EC.field_0[idx0].vy) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                 ((((sharedData_800DFB7C_0_s00[idx].vy_8 + ptr->field_16C) >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_144.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ptr->field_0.u_field_FC.field_0[idx0].vy) >> 4) - ptr->field_0.field_0.vz;
    }

    gte_ldv3c(&ptr->field_12C);
    gte_rtpt();
    gte_stsxy3_g3(*poly);
    gte_stsz3c(&ptr->field_150);
    gte_ldv0(&ptr->field_144);
    gte_rtps();
    gte_stsxy(&ptr->field_14C);
    gte_stsz(&ptr->field_15C);

    ptr->field_160 = (ptr->field_150.vx + ptr->field_150.vy + ptr->field_150.vz + ptr->field_15C) >> 2;

    if (ptr->field_160 <= 0 || (ptr->field_160 >> 3) >= ORDERING_TABLE_SIZE)
    {
        return false;
    }

    if (ABS(ptr->field_14C.vx) > 200)
    {
        return false;
    }

    if (ABS(ptr->field_14C.vy) > 160)
    {
        return false;
    }

    *(s32*)&(*poly)->x3 = *(s32*)&ptr->field_14C;

    temp_v1_13          = sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_0;
    *(s32*)&(*poly)->u0 = ((temp_v1_13 & 0x2) * 16) + 0x40 + ((ptr->field_17C + ((temp_v1_13 & 0x1) << 6)) << 8) + 0xE0000;

    temp_v1_14          = sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_0;
    *(s32*)&(*poly)->u1 = ((temp_v1_14 & 0x2) * 16) + 0x5F + ((ptr->field_17C + ((temp_v1_14 & 0x1) << 6)) << 8) + 0x2D0000;

    temp_v1_15          = sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_0;
    *(u16*)&(*poly)->u2 = ((temp_v1_15 & 0x2) * 16) + 0x40 + ((ptr->field_17D + (ptr->field_17C + ((temp_v1_15 & 1) << 6))) << 8);

    temp_v1_16          = sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_0;
    *(u16*)&(*poly)->u3 = ((temp_v1_16 & 0x2) * 16) + 0x5F + ((ptr->field_17D + (ptr->field_17C + ((temp_v1_16 & 1) << 6))) << 8);

    setSemiTrans(*poly, 1);
    ptr->field_180 = (ptr->field_180 * func_80055D78(sharedData_800DFB7C_0_s00[idx].field_0.vx_0, sharedData_800DFB7C_0_s00[idx].vy_8, sharedData_800DFB7C_0_s00[idx].field_4.vz_4)) >> 7;

    setRGB0Fast(*poly, ptr->field_180, ptr->field_180, ptr->field_180);
    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_160 + 0x100) >> 3], *poly);

    *poly += 1;

    return true;
}

void sharedFunc_800CCE60_1_s02(void)
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        u8              unk_134[8];
        DVECTOR         field_13C[16][2];
        s32             field_1BC[16][2];
        u8              field_23C[16][2];
        s16             field_25C;
        s16             field_25E;
        s16             field_260;
        s16             field_262;
        s16             field_264[2][2];
        s16             field_26C;
        u16             field_26E;
    } s_func_800CCE60;

    POLY_GT4*        poly;
    s32              sp14;
    s32              sp18;
    s32              sp1C;
    s32              sp20;
    s32              temp_lo_3;
    s32              temp_s0;
    s32              temp_v0_8;
    s32              temp_v1_3;
    s32              var_fp;
    s32              var_s2;
    s32              var_s3;
    s32              var_s4;
    s32              var_t2_2;
    s32              var_t3_2;
    s32              var_t5;
    s_func_800CCE60* ptr;

    ptr = PSX_SCRATCH;

    sp14 = 0;

    poly = (POLY_GT4*)GsOUT_PACKET_P;

    ptr->field_260 = 0x4E;
    ptr->field_262 = 0x2D;

    for (sp20 = 0; sp20 < sharedData_800E30C8_1_s02.field_78; sp20++)
    {
        temp_s0 = sharedData_800E30C8_1_s02.field_3C[sp20] >> 1;

        if (sharedData_800E30C8_1_s02.field_30[sp20] == 0)
        {
            ptr->field_25C       = Math_Sin(sharedData_800E30C8_1_s02.field_34[sp20]);
            ptr->field_25E       = Math_Cos(sharedData_800E30C8_1_s02.field_34[sp20]);
            ptr->field_264[0][0] = Q12_MULT(temp_s0, ptr->field_25E);
            ptr->field_264[0][1] = -ptr->field_264[0][0];
            ptr->field_264[1][0] = Q12_MULT(-temp_s0, ptr->field_25C);
            ptr->field_264[1][1] = -ptr->field_264[1][0];
        }
        else
        {
            ptr->field_264[0][0] = Q12_MULT(temp_s0, Math_Sin(ptr->field_0.field_30.vy - 0x400));
            ptr->field_264[1][0] = Q12_MULT(temp_s0, Math_Cos(ptr->field_0.field_30.vy - 0x400));
            ptr->field_264[0][1] = Q12_MULT(temp_s0, Math_Sin(ptr->field_0.field_30.vy + 0x400));
            ptr->field_264[1][1] = Q12_MULT(temp_s0, Math_Cos(ptr->field_0.field_30.vy + 0x400));
        }

        if (sp20 == (sharedData_800E30C8_1_s02.field_78 - 1))
        {
            ptr->field_26E = sharedData_800E30C8_1_s02.field_28[sp20] - sharedData_800E30C8_1_s02.field_28[sharedData_800E30C8_1_s02.field_78];
        }
        else
        {
            ptr->field_26E = 0xFFFF;
        }

        var_s4 = 0;

        for (var_t5 = 0;; var_t5++)
        {
            var_s2 = 0;

            if (sharedData_800E30C8_1_s02.field_30[sp20] == 0)
            {
                if (var_s4 == 0)
                {
                    ptr->field_26C = sharedData_800E30C8_1_s02.field_10[sp20];
                }
                else
                {
                    if (var_s4 == sharedData_800E30C8_1_s02.field_28[sp20])
                    {
                        ptr->field_26C = sharedData_800E30C8_1_s02.field_10[sp20 + 1];
                    }
                    else
                    {
                        ptr->field_26C = sharedData_800E30C8_1_s02.field_10[sp20] + ((sharedData_800E30C8_1_s02.field_10[sp20 + 1] - sharedData_800E30C8_1_s02.field_10[sp20]) * var_s4) / sharedData_800E30C8_1_s02.field_28[sp20];
                    }
                }

                if (ptr->field_26E < var_s4)
                {
                    var_s2 = Q12(var_s4 - ptr->field_26E) / sharedData_800E30C8_1_s02.field_28[sharedData_800E30C8_1_s02.field_78];

                    temp_s0 = Q12_MULT_PRECISE(0x1000 - var_s2, sharedData_800E30C8_1_s02.field_3C[sp20] >> 1) +
                              Q12_MULT_PRECISE(var_s2, sharedData_800E30C8_1_s02.field_3C[sp20 + 1] >> 1);

                    ptr->field_264[0][0] = Q12_MULT(temp_s0, ptr->field_25E);
                    ptr->field_264[0][1] = -ptr->field_264[0][0];
                    ptr->field_264[1][0] = Q12_MULT(-temp_s0, ptr->field_25C);
                    ptr->field_264[1][1] = -ptr->field_264[1][0];
                }
            }

            for (var_s3 = 0; var_s3 < 2; var_s3++)
            {
                if (sharedData_800E30C8_1_s02.field_30[sp20] == 0)
                {
                    var_fp = sharedData_800E30C8_1_s02.field_0[sp20] + ptr->field_264[0][var_s3] + Q12_MULT(var_s4, ptr->field_25C);
                    sp18   = ptr->field_26C;
                    sp1C   = sharedData_800E30C8_1_s02.field_18[sp20] + ptr->field_264[1][var_s3] + Q12_MULT(var_s4, ptr->field_25E);
                }
                else
                {
                    var_fp = sharedData_800E30C8_1_s02.field_0[sp20] + ptr->field_264[0][var_s3];
                    sp18   = sharedData_800E30C8_1_s02.field_10[sp20] + var_s4;
                    sp1C   = sharedData_800E30C8_1_s02.field_18[sp20] + ptr->field_264[1][var_s3];
                }

                ptr->field_23C[var_t5][var_s3] = Q12_MULT_PRECISE(Math_Cos(var_s2 >> 2), func_80055D78(var_fp, sp18, sp1C));

                if (sp20 < (sharedData_800E30C8_1_s02.field_78 - 1) && sharedData_800E30C8_1_s02.field_30[sp20] == 0)
                {
                    temp_s0 = sharedData_800E30C8_1_s02.field_30[sp20 + 1];

                    if (temp_s0 == 0)
                    {
                        temp_v0_8 = Math_Sin(sharedData_800E30C8_1_s02.field_34[sp20] - sharedData_800E30C8_1_s02.field_34[sp20 + 1]);
                        var_s2    = Q12_MULT(sharedData_800E30C8_1_s02.field_5C[sp20 + 1], temp_v0_8);

                        if (var_s3 == 0)
                        {
                            var_s2 = -var_s2;
                        }

                        temp_v1_3 = sharedData_800E30C8_1_s02.field_28[sp20] - var_s4;

                        if (temp_v1_3 < var_s2)
                        {
                            ptr->field_23C[var_t5][var_s3] = Q12_MULT_PRECISE(temp_v1_3 >= 0 ? Q12(temp_v1_3) / var_s2 : temp_s0 / var_s2, ptr->field_23C[var_t5][var_s3]);
                        }
                    }
                }

                if (sp20 > 0)
                {
                    if (sharedData_800E30C8_1_s02.field_30[sp20] == 0 && sharedData_800E30C8_1_s02.field_30[sp20 - 1] == 0)
                    {
                        var_s2 = FP_MULTIPLY(sharedData_800E30C8_1_s02.field_5C[sp20 - 1],
                                             Math_Sin(sharedData_800E30C8_1_s02.field_34[sp20 - 1] - sharedData_800E30C8_1_s02.field_34[sp20]), Q12_SHIFT);

                        if (var_s3 == 0)
                        {
                            var_s2 = -var_s2;
                        }

                        if (var_s4 < var_s2)
                        {
                            ptr->field_23C[var_t5][var_s3] = Q12_MULT_PRECISE(Q12(var_s4) / var_s2, ptr->field_23C[var_t5][var_s3]);
                        }
                    }
                }

                *(s32*)&ptr->field_12C = (((var_fp >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) + (((sp18 >> 4) - ptr->field_0.field_0.vy) << 16);
                ptr->field_12C.vz      = (sp1C >> 4) - ptr->field_0.field_0.vz;

                gte_ldv0(&ptr->field_12C);
                gte_rtps();
                gte_stsxy(&ptr->field_13C[var_t5][var_s3]);
                gte_stsz(&ptr->field_1BC[var_t5][var_s3]);
            }

            if (var_s4 != sharedData_800E30C8_1_s02.field_28[sp20])
            {
                if (var_t5 != 0)
                {
                    if (sharedData_800E30C8_1_s02.field_28[sp20] < var_s4 + sharedData_800E30C8_1_s02.field_44[sp20])
                    {
                        sp14   = sharedData_800E30C8_1_s02.field_28[sp20] - var_s4;
                        var_s4 = sharedData_800E30C8_1_s02.field_28[sp20];
                    }
                    else
                    {
                        var_s4 += sharedData_800E30C8_1_s02.field_44[sp20];
                    }
                }
                else
                {
                    var_s4 += sharedData_800E30C8_1_s02.field_54[sp20];
                }
            }
            else
            {
                break;
            }
        }

        for (var_s3 = 0; var_s3 < var_t5; var_s3++)
        {
            if (var_s3 == 0)
            {
                temp_lo_3 = (sharedData_800E30C8_1_s02.field_54[sp20] << 6) / sharedData_800E30C8_1_s02.field_44[sp20];
                var_t2_2  = temp_lo_3;
                var_t2_2  = 0x7F - var_t2_2;
                var_t3_2  = temp_lo_3;
            }
            else
            {
                var_t2_2 = 0x40;
                if ((var_s3 + 1) == var_t5)
                {
                    var_t3_2 = (sp14 << 6) / sharedData_800E30C8_1_s02.field_44[sp20];
                }
                else
                {
                    var_t3_2 = 0x3F;
                }
            }

            setPolyGT4(poly);

            setXY0Fast(poly, ptr->field_13C[var_s3][0].vx, ptr->field_13C[var_s3][0].vy);
            setXY1Fast(poly, ptr->field_13C[var_s3][1].vx, ptr->field_13C[var_s3][1].vy);
            setXY2Fast(poly, ptr->field_13C[var_s3 + 1][0].vx, ptr->field_13C[var_s3 + 1][0].vy);
            setXY3Fast(poly, ptr->field_13C[var_s3 + 1][1].vx, ptr->field_13C[var_s3 + 1][1].vy);

            setSemiTrans(poly, 1);

            setRGB0Fast(poly, ptr->field_23C[var_s3][0], ptr->field_23C[var_s3][0], ptr->field_23C[var_s3][0]);
            setRGB1Fast(poly, ptr->field_23C[var_s3][1], ptr->field_23C[var_s3][1], ptr->field_23C[var_s3][1]);
            setRGB2Fast(poly, ptr->field_23C[var_s3 + 1][0], ptr->field_23C[var_s3 + 1][0], ptr->field_23C[var_s3 + 1][0]);
            setRGB3Fast(poly, ptr->field_23C[var_s3 + 1][1], ptr->field_23C[var_s3 + 1][1], ptr->field_23C[var_s3 + 1][1]);

            *(s32*)&poly->u0 = (var_t2_2 << 8) + 0x40 + (ptr->field_260 << 16);
            *(s32*)&poly->u1 = (var_t2_2 << 8) + 0x5F + (ptr->field_262 << 16);
            *(u16*)&poly->u2 = ((var_t2_2 + var_t3_2) << 8) + 0x40;
            *(u16*)&poly->u3 = ((var_t2_2 + var_t3_2) << 8) + 0x5F;

            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(((ptr->field_1BC[var_s3][0] + ptr->field_1BC[var_s3][1] + ptr->field_1BC[var_s3 + 1][0] + ptr->field_1BC[var_s3 + 1][1]) >> 2) + 0x100) >> 3], poly);
            poly++;
        }

        sharedData_800E30C8_1_s02.field_54[sp20] += Q12_MULT_PRECISE(g_DeltaTime, sharedData_800E30C8_1_s02.field_4C[sp20]);

        while (sharedData_800E30C8_1_s02.field_54[sp20] >= sharedData_800E30C8_1_s02.field_44[sp20])
        {
            sharedData_800E30C8_1_s02.field_54[sp20] -= sharedData_800E30C8_1_s02.field_44[sp20];
        }
    }

    GsOUT_PACKET_P = (PACKET*)poly;
}

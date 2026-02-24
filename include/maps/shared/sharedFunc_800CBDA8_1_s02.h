#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

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

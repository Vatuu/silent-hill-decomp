#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

void sharedFunc_800CCB8C_0_s01(VECTOR* arg0, VECTOR* arg1, s16 arg2, s32 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7)
{
    typedef struct
    {
        VECTOR3 field_0;
        MATRIX  field_C;
        SVECTOR field_2C;
        VECTOR  field_34;
        s32     field_44;
        s16     field_48;
        s16     field_4A;
        s32     field_4C;
    } s_sharedFunc_800CCB8C_0_s01;

    s32                          sp20;
    s32                          sp24;
    s32                          var_s5;
    s32                          var_s7;
    s32                          temp_lo;
    s32                          temp_lo_2;
    s32                          temp_s0_2;
    s32                          temp_v0_8;
    s16                          var_s1;
    s32                          var_v0_2;
    s_sharedFunc_800CCB8C_0_s01* ptr;

    ptr = PSX_SCRATCH;

    sharedData_800DFB10_0_s01[arg7].vx = arg0->vx;
    sharedData_800DFB10_0_s01[arg7].vy = arg0->vz;
    sharedData_800DFB10_0_s01[arg7].vz = arg3;

    var_s1 = arg5;

    if (var_s1 != 0)
    {
        ptr->field_4C = 0;
    }
    else
    {
        ptr->field_4C = 1;
        var_s1        = arg4;
    }

    ptr->field_0.vx = arg0->vx - arg1->vx;
    ptr->field_0.vy = arg0->vy - arg1->vy;
    ptr->field_0.vz = arg0->vz - arg1->vz;

    ptr->field_48 = ratan2(ptr->field_0.vy, ptr->field_0.vz);
    ptr->field_4A = ratan2(ptr->field_0.vx, ptr->field_0.vz);

    *(s32*)&ptr->field_2C = (u16)ptr->field_48 + (ptr->field_4A << 16);
    ptr->field_2C.vz      = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_2C, &ptr->field_C);
    TransMatrix(&ptr->field_C, &D_800CA5C8);

    gte_SetRotMatrix(&ptr->field_C);
    gte_SetTransMatrix(&ptr->field_C);

    ptr->field_44 = Math_Vector2MagCalc(var_s1, arg4) + 1;

    for (var_s7 = -arg4; arg4 >= var_s7;)
    {
        sp24 = arg6 * 3;

        for (var_s5 = -var_s1; var_s1 >= var_s5;)
        {
            sp20 = SQUARE(var_s7 >> 6);

            if (ptr->field_4C != 0 && SQUARE(arg4 >> 6) < sp20 + SQUARE(var_s5 >> 6))
            {
                continue;
            }

            if ((Rng_Rand16() % (0x20 - (((SquareRoot0(sp20 + SQUARE(var_s5 >> 6)) << 6) * 24) / ptr->field_44))) == 0)
            {
                continue;
            }

            temp_v0_8 = func_8005E7E0(arg7 + 0x17);
            if (temp_v0_8 == -1)
            {
                return;
            }

            *(s32*)&ptr->field_2C = (((var_s7 + (Rng_Rand16() % (arg6 >> 1))) - (arg6 >> 2)) & 0xFFFF) +
                                    (((var_s5 + (Rng_Rand16() % (arg6 >> 1))) - (arg6 >> 2)) << 0x10);
            ptr->field_2C.vz = 0;

            gte_ldv0(&ptr->field_2C);
            gte_rt();
            gte_stlvnl(&ptr->field_34);

            sharedData_800DFB7C_0_s00[temp_v0_8].field_0.s_0.field_0 = ptr->field_34.vx;
            sharedData_800DFB7C_0_s00[temp_v0_8].vy_8                = ptr->field_34.vy + arg0->vy;
            sharedData_800DFB7C_0_s00[temp_v0_8].field_4.s_0.field_0 = ptr->field_34.vz;

            temp_s0_2 = SquareRoot0(SQUARE(ptr->field_34.vx >> 6) + SQUARE(ptr->field_34.vy >> 6) + SQUARE(ptr->field_34.vz >> 6)) << 6;

            sharedData_800DFB7C_0_s00[temp_v0_8].field_10.s_0.field_2 = MIN(temp_s0_2 / (arg2 >> 0xA), 0x1000);

            sharedData_800DFB7C_0_s00[temp_v0_8].field_B = ((Rng_Rand16() % MIN(((temp_s0_2 * 6) / ptr->field_44) + 3, 8)) * 0x10) - 0x80 + Rng_GenerateUInt(0, 15);

            ptr->field_34.vx += ptr->field_0.vx;
            ptr->field_34.vy += ptr->field_0.vy;
            ptr->field_34.vz += ptr->field_0.vz;

            temp_s0_2 = SquareRoot0(SQUARE(ptr->field_34.vx >> 6) + SQUARE(ptr->field_34.vy >> 6) + SQUARE(ptr->field_34.vz >> 6)) << 6;

            sharedData_800DFB7C_0_s00[temp_v0_8].field_C.s_0.field_0  = (arg2 * Rng_GenerateUInt(64, 191) >> 7) * ptr->field_34.vx / temp_s0_2;
            sharedData_800DFB7C_0_s00[temp_v0_8].field_C.s_0.field_2  = (arg2 * Rng_GenerateUInt(64, 191) >> 7) * ptr->field_34.vy / temp_s0_2;
            sharedData_800DFB7C_0_s00[temp_v0_8].field_10.s_0.field_0 = (arg2 * Rng_GenerateUInt(64, 191) >> 7) * ptr->field_34.vz / temp_s0_2;

            sharedData_800DFB7C_0_s00[temp_v0_8].field_0.s_0.field_2 = (ptr->field_48 + Rng_GenerateUInt(0, 511)) - 255; // TODO: `-255` should be lower RNG bound?
            sharedData_800DFB7C_0_s00[temp_v0_8].field_4.s_0.field_2 = (ptr->field_4A + Rng_GenerateUInt(0, 511)) - 255;

            temp_lo  = (var_s5 * arg6) / var_s1;
            var_v0_2 = var_s5 + ((ABS(temp_lo) + sp24) >> 2);
            var_s5   = var_v0_2;
        }

        temp_lo_2 = (var_s7 * arg6) / arg4;
        var_v0_2  = var_s7 + ((ABS(temp_lo_2) + sp24) >> 2);
        var_s7    = var_v0_2;
    }
}

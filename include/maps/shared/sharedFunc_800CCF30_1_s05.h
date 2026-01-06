#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

bool sharedFunc_800CCF30_1_s05(POLY_FT4** poly, s32 idx)
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        s32             field_134;
        s32             field_138;
        DVECTOR         field_13C;
        DVECTOR         field_140;
        DVECTOR         field_144;
        s16             field_148;
        s32             field_14C;
    } s_sharedFunc_800CCF30_1_s05;

    s32                          temp_v1_3;
    s32                          var_a1;
    s32                          var_v0_4;
    s32                          temp_s3;
    s32                          var_a0;
    s32                          temp;
    s_sharedFunc_800CCF30_1_s05* ptr;

    ptr = PSX_SCRATCH;

    temp_s3 = sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0;

    sharedData_800DFB7C_0_s00[idx].field_A     = 0;
    sharedData_800DFB7C_0_s00[temp_s3].field_A = 0;

    *(s32*)&ptr->field_12C = ((sharedData_800DFB7C_0_s00[idx].field_0.s_1.field_0 - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                             ((sharedData_800DFB7C_0_s00[idx].vy_8 - ptr->field_0.field_0.vy) << 0x10);
    ptr->field_12C.vz = sharedData_800DFB7C_0_s00[idx].field_4.s_0.field_0 - ptr->field_0.field_0.vz;

    gte_ldv0(&ptr->field_12C);
    gte_rtps();
    gte_stsxy(&ptr->field_13C);
    gte_stsz(&ptr->field_134);

    if (ABS(ptr->field_13C.vx) > 320 || ABS(ptr->field_13C.vy) > 240)
    {
        return false;
    }

    *(s32*)&ptr->field_12C = ((sharedData_800DFB7C_0_s00[temp_s3].field_0.s_1.field_0 - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                             ((sharedData_800DFB7C_0_s00[temp_s3].vy_8 - ptr->field_0.field_0.vy) << 0x10);
    ptr->field_12C.vz = sharedData_800DFB7C_0_s00[temp_s3].field_4.s_0.field_0 - ptr->field_0.field_0.vz;

    gte_ldv0(&ptr->field_12C);
    gte_rtps();
    gte_stsxy(&ptr->field_140);
    gte_stsz(&ptr->field_138);

    var_a1 = MAX(ptr->field_134, ptr->field_138);

    if (ptr->field_138 >= ptr->field_134)
    {
        var_v0_4 = (ptr->field_134 * 3 + var_a1) >> 2;
    }
    else
    {
        var_v0_4 = (ptr->field_138 * 3 + var_a1) >> 2;
    }

    ptr->field_134 = var_v0_4;

    if (ptr->field_134 <= 0 || (ptr->field_134 >> 3) >= ORDERING_TABLE_SIZE)
    {
        return false;
    }

    ptr->field_148 = ratan2(ptr->field_140.vy - ptr->field_13C.vy, ptr->field_140.vx - ptr->field_13C.vx);

    ptr->field_14C = CLAMP_LOW(
        FP_MULTIPLY_PRECISE(0x1000 - (SquareRoot0(SQUARE((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 - sharedData_800DFB7C_0_s00[temp_s3].field_0.vx_0) >> 6) +
                                                  SQUARE((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 - sharedData_800DFB7C_0_s00[temp_s3].field_4.vz_4) >> 6))
                                      << 6),
                            0x18, Q12_SHIFT) *
            ptr->field_0.field_2C / ptr->field_134,
        1);

    ptr->field_144.vx = Q12_MULT(ptr->field_14C, Math_Sin(ptr->field_148));
    ptr->field_144.vy = Q12_MULT(ptr->field_14C, Math_Cos(ptr->field_148));

    setXY0Fast(*poly, (u16)ptr->field_13C.vx - (u16)ptr->field_144.vx, ptr->field_13C.vy - ptr->field_144.vy);
    setXY1Fast(*poly, (u16)ptr->field_140.vx - (u16)ptr->field_144.vx, ptr->field_140.vy - ptr->field_144.vy);
    setXY2Fast(*poly, (u16)ptr->field_13C.vx + (u16)ptr->field_144.vx, ptr->field_13C.vy + ptr->field_144.vy);
    setXY3Fast(*poly, (u16)ptr->field_140.vx + (u16)ptr->field_144.vx, ptr->field_140.vy + ptr->field_144.vy);

    *(u32*)&(*poly)->u0 = (sharedData_800DFB7C_0_s00[idx].field_B * 0xC00) + 0x010E4000;
    *(u32*)&(*poly)->u1 = (sharedData_800DFB7C_0_s00[idx].field_B * 0xC00) + 0x6D407F;
    *(u16*)&(*poly)->u2 = (sharedData_800DFB7C_0_s00[idx].field_B * 0xC00) + 0x4B00;
    *(u16*)&(*poly)->u3 = (sharedData_800DFB7C_0_s00[idx].field_B * 0xC00) + 0x4B7F;

    temp = func_80055D78(((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + sharedData_800DFB7C_0_s00[temp_s3].field_0.vx_0) * 0x10) >> 1,
                         (sharedData_800DFB7C_0_s00[idx].vy_8 + sharedData_800DFB7C_0_s00[temp_s3].vy_8) * 8,
                         ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + sharedData_800DFB7C_0_s00[temp_s3].field_4.vz_4) * 0x10) >> 1);

    temp_v1_3 = (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 * temp) >> 6;

    if (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 >= temp_v1_3)
    {
        var_a0 = temp_v1_3;
    }
    else
    {
        var_a0 = sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2;
    }
    temp_v1_3 = var_a0;

    setRGBC0(*poly, temp_v1_3, temp_v1_3, temp_v1_3, 0x2E);
    addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_134 >> 3], *poly, 9);
    *poly += 1;

    return true;
}

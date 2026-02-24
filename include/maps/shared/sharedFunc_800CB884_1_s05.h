#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

bool sharedFunc_800CB884_1_s05(POLY_FT4** poly, s32 idx) // 0x800CCF50
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        s32             field_134;
        s32             field_138;
        s32             field_13C;
        DVECTOR         field_140;
        s16             field_144;
    } s_func_800CB884;

    s32              var_s1;
    s_func_800CB884* ptr;

    ptr = PSX_SCRATCH;

    if (sharedData_800DFB7C_0_s00[idx].field_A == 9)
    {
        *(s32*)&(*poly)->u0 = 0x024EC000;
        *(s32*)&(*poly)->u1 = 0x4DC03F;
        *(u16*)&(*poly)->u2 = 0xFF00;
        *(u16*)&(*poly)->u3 = 0xFF3F;

        ptr->field_144 = (sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 >> 6) + 0x24;

        var_s1 = MAX(0x40 - (sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 >> 6), 0);

        setRGBC0(*poly, var_s1, var_s1, var_s1, 0x2E);
    }
    else
    {
        *(s32*)&(*poly)->u0 = 0x020E7800;
        *(s32*)&(*poly)->u1 = 0xD7807;
        *(u16*)&(*poly)->u2 = 0x7F00;
        *(u16*)&(*poly)->u3 = 0x7F07;

        ptr->field_144 = 2;

        setRGBC0(*poly, 0xFF, CLAMP_LOW(0xC0 - (sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 >> 6), 0), 0x80, 0x2E);
    }

    sharedData_800DFB7C_0_s00[idx].vy_8 = sharedData_800DFB7C_0_s00[idx].vy_8 + ptr->field_0.field_C4;

    var_s1 = (sharedData_800D8568_1_s05.field_8 * sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_1) >> 8;

    ptr->field_134 = sharedData_800D8568_1_s05.field_20 + sharedData_800DFB7C_0_s00[idx].field_0.vx_0 +
                     Q12_MULT(Math_Sin(sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2), var_s1);

    ptr->field_138 = sharedData_800D8568_1_s05.field_24 + sharedData_800DFB7C_0_s00[idx].field_4.vz_4 +
                     Q12_MULT(Math_Cos(sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2), var_s1);

    *(s32*)&ptr->field_12C = (((ptr->field_134 >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                             (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 16);
    ptr->field_12C.vz = (ptr->field_138 >> 4) - ptr->field_0.field_0.vz;

    if (sharedData_800DFB7C_0_s00[idx].field_B & 1)
    {
        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 += Q12_MULT_PRECISE(g_DeltaTime, (ptr->field_0.field_C6 * sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0) >> 8);
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 -= Q12_MULT_PRECISE(g_DeltaTime, (ptr->field_0.field_C6 * sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0) >> 8);
    }

    sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 += ptr->field_0.field_CE;

    if (sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 > Q12(1.0f))
    {
        sharedFunc_800CABF8_1_s05(idx, 1);
        return false;
    }

    gte_ldv0(&ptr->field_12C);
    gte_rtps();
    gte_stsxy(&ptr->field_140);
    gte_stsz(&ptr->field_13C);

    if (ptr->field_13C <= 0 || (ptr->field_13C >> 3) >= ORDERING_TABLE_SIZE)
    {
        return false;
    }

    if (ABS(ptr->field_140.vx) > 200)
    {
        return false;
    }

    if (ABS(ptr->field_140.vy) > 160)
    {
        return false;
    }

    var_s1 = (ptr->field_144 * ptr->field_0.field_2C) / ptr->field_13C;
    if (var_s1 != 0)
    {
        setXY0Fast(*poly, (u16)ptr->field_140.vx - var_s1, ptr->field_140.vy - var_s1);
        setXY1Fast(*poly, (u16)ptr->field_140.vx + var_s1, ptr->field_140.vy - var_s1);
        setXY2Fast(*poly, (u16)ptr->field_140.vx - var_s1, ptr->field_140.vy + var_s1);
        setXY3Fast(*poly, (u16)ptr->field_140.vx + var_s1, ptr->field_140.vy + var_s1);
    }
    else
    {
        setXY0Fast(*poly, ptr->field_140.vx, ptr->field_140.vy);
        setXY1Fast(*poly, (u16)ptr->field_140.vx + 1, ptr->field_140.vy);
        setXY2Fast(*poly, ptr->field_140.vx, ptr->field_140.vy + 1);
        setXY3Fast(*poly, (u16)ptr->field_140.vx + 1, ptr->field_140.vy + 1);
    }

    addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_13C >> 3], *poly, 9);
    *poly += 1;

    return true;
}

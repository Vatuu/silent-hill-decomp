#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

bool sharedFunc_800CC004_4_s03(POLY_FT4** poly, s32 arg1)
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        DVECTOR         field_134;
        s32             field_138;
        s32             field_13C;
        s32             field_140;
    } s_func_800CC004;

    POLY_FT4*        next;
    s_func_800CC004* ptr;

    ptr = PSX_SCRATCH;

    sharedData_800DFB7C_0_s00[arg1].field_C.s_0.field_0 += g_DeltaTime;

    if (sharedData_800DFB7C_0_s00[arg1].field_C.s_2.field_0 > Q12(1.4f))
    {
        sharedData_800DFB7C_0_s00[arg1].field_A = 0;
        return false;
    }

    Math_SetSVectorFastSum(&ptr->field_12C, (sharedData_800DFB7C_0_s00[arg1].field_0.vx_0 >> 4) - (u16)ptr->field_0.field_0.vx,
                           (sharedData_800DFB7C_0_s00[arg1].vy_8 >> 4) - ptr->field_0.field_0.vy, (sharedData_800DFB7C_0_s00[arg1].field_4.vz_4 >> 4) - ptr->field_0.field_0.vz);

    gte_ldv0(&ptr->field_12C);
    gte_rtps();
    gte_stsxy(&ptr->field_134);
    gte_stsz(&ptr->field_138);

    if (ptr->field_138 <= 0 || (ptr->field_138 >> 3) >= ORDERING_TABLE_SIZE)
    {
        return false;
    }

    if (ABS(ptr->field_134.vx) > 200 || ABS(ptr->field_134.vy) > 160)
    {
        return false;
    }

    setPolyFT4(*poly);

    ptr->field_13C = (ptr->field_0.field_2C * Q12_MULT_PRECISE(sharedData_800DFB7C_0_s00[arg1].field_C.s_2.field_2,
                                                               Q12(sharedData_800DFB7C_0_s00[arg1].field_C.s_2.field_0 >> 1) /
                                                               5734 + 0x800) /
                                              ptr->field_138) >> 4;

    setXY0Fast(*poly, (u16)ptr->field_134.vx - (u16)ptr->field_13C, ptr->field_134.vy + ptr->field_13C);
    setXY1Fast(*poly, (u16)ptr->field_134.vx + (u16)ptr->field_13C, ptr->field_134.vy + ptr->field_13C);
    setXY2Fast(*poly, (u16)ptr->field_134.vx - (u16)ptr->field_13C, ptr->field_134.vy - ptr->field_13C);
    setXY3Fast(*poly, (u16)ptr->field_134.vx + (u16)ptr->field_13C, ptr->field_134.vy - ptr->field_13C);

    if (sharedData_800DFB7C_0_s00[arg1].field_C.s_2.field_0 > Q12(0.4f))
    {
        ptr->field_140 = sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 - (sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 * (sharedData_800DFB7C_0_s00[arg1].field_C.s_2.field_0 - Q12(0.4f))) / Q12(1.0f);
    }
    else
    {
        ptr->field_140 = (sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 * sharedData_800DFB7C_0_s00[arg1].field_C.s_2.field_0) / Q12(0.4f);
    }

    ptr->field_140 = (ptr->field_140 * (func_80055D78(sharedData_800DFB7C_0_s00[arg1].field_0.vx_0, sharedData_800DFB7C_0_s00[arg1].vy_8, sharedData_800DFB7C_0_s00[arg1].field_4.vz_4))) >> 8;

    setRGB0Fast(*poly, ptr->field_140 >> 1, ptr->field_140 >> 1, ptr->field_140 >> 1);
    setSemiTrans(*poly, 1);

    *(s32*)&(*poly)->u0 = (((sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 & 1) == 0) << 6) +
                          (!(sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 & 2) ? 0xE4000 : 0xE0000);

    *(s32*)&(*poly)->u1 = (!(sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 & 1) ? 0x7F : 0x3F) +
                          (!(sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 & 2) ? 0x2D4000 : 0x2D0000);

    *(u16*)&(*poly)->u2 = (((sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 & 1) == 0) << 6) |
                          (!(sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 & 2) ? 0x7F00 : 0x3F00);

    *(u16*)&(*poly)->u3 = (!(sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 & 1) ? 0x7F : 0x3F) |
                          (!(sharedData_800DFB7C_0_s00[arg1].field_10.s_2.field_0 & 2) ? 0x7F00 : 0x3F00);

    if (sharedData_800DFB7C_0_s00[arg1].field_B != 0)
    {
        ptr->field_138 -= 0x80;
    }
    else
    {
        ptr->field_138 -= 0x10;
    }

    next  = *poly + 1;
    *next = *(*poly);

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_138 >> 3], *poly);
    *poly += 1;

    setRGB0Fast(*poly, ptr->field_140, ptr->field_140, ptr->field_140);

    (*poly)->tpage = 77;
    (*poly)->clut  = 78;

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_138 >> 3], *poly);
    *poly += 1;

    return true;
}

#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

bool sharedFunc_800CBF74_1_s05(POLY_FT4** poly, s32 idx)
{
    typedef struct
    {
        s_func_8005E89C field_0;
        s_Collision     field_12C;
        SVECTOR         field_138;
        s32             field_140;
        DVECTOR         field_144;
        s32             field_148;
        s32             field_14C;
    } s_sharedFunc_800CBF74_1_s05;

    VECTOR3                      sp10;
    s32                          temp_v0;
    s32                          temp_v0_2;
    s32                          var_v1;
    s_sharedFunc_800CBF74_1_s05* ptr;

    ptr = PSX_SCRATCH;

    temp_v0 = Q12_MULT(sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2, Math_Sin(sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0));

    sharedData_800DFB7C_0_s00[idx].vy_8         += Q12_MULT_PRECISE(g_DeltaTime, sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0);
    sharedData_800DFB7C_0_s00[idx].field_0.vx_0 += Q12_MULT_PRECISE(g_DeltaTime, temp_v0);

    temp_v0_2 = Q12_MULT(sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2, Math_Cos(sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0));

    sharedData_800DFB7C_0_s00[idx].field_4.vz_4        += Q12_MULT_PRECISE(g_DeltaTime, temp_v0_2);
    sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 += g_GravitySpeed >> 1;
    sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2  = CLAMP_LOW(sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 - Q12_MULT_PRECISE(g_DeltaTime, 0x800), 0);

    Collision_Get(&ptr->field_12C, sharedData_800DFB7C_0_s00[idx].field_0.vx_0, sharedData_800DFB7C_0_s00[idx].field_4.vz_4);

    if (ptr->field_12C.groundHeight_0 < sharedData_800DFB7C_0_s00[idx].vy_8 || sharedData_800DFB7C_0_s00[idx].vy_8 > 0)
    {
        sharedData_800DFB7C_0_s00[idx].vy_8                = MIN(ptr->field_12C.groundHeight_0, 0);
        sharedData_800DFB7C_0_s00[idx].field_B             = 1;
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = 0;

        sp10.vx = sharedData_800DFB7C_0_s00[idx].field_0.vx_0;
        sp10.vy = sharedData_800DFB7C_0_s00[idx].vy_8;
        sp10.vz = sharedData_800DFB7C_0_s00[idx].field_4.vz_4;

        func_8005DC1C(0x5C4, &sp10, 0x80, 0);
    }

    gte_SetRotMatrix(&ptr->field_0.field_C);
    gte_SetTransMatrix(&ptr->field_0.field_C);

    if (ABS(g_SysWork.playerWork_4C.player_0.position_18.vx - sharedData_800DFB7C_0_s00[idx].field_0.vx_0) +
            ABS(g_SysWork.playerWork_4C.player_0.position_18.vz - sharedData_800DFB7C_0_s00[idx].field_4.vz_4) >
        0x14000)
    {
        return false;
    }

    *(s32*)&ptr->field_138 = (((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                             (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 0x10);
    ptr->field_138.vz = (sharedData_800DFB7C_0_s00[idx].field_4.vz_4 >> 4) - ptr->field_0.field_0.vz;

    gte_ldv0(&ptr->field_138);
    gte_rtps();
    gte_stsxy(&ptr->field_144);
    gte_stsz(&ptr->field_140);

    if (ptr->field_140 - 0x10 <= 0 || ((ptr->field_140 - 0x10) >> 3) >= ORDERING_TABLE_SIZE ||
        ABS(ptr->field_144.vx) > 200 || ABS(ptr->field_144.vy) > 160)
    {
        return false;
    }

    vwGetViewAngle(&ptr->field_138);

    ptr->field_148 = ptr->field_0.field_2C * 4 / ptr->field_140;
    ptr->field_14C = ((((ptr->field_138.vx + 0x400) >> 9) + 7) * ptr->field_0.field_2C) / ptr->field_140;

    setXY0Fast(*poly, (u16)ptr->field_144.vx - (u16)ptr->field_148, ptr->field_144.vy - ptr->field_14C);
    setXY1Fast(*poly, (u16)ptr->field_144.vx + (u16)ptr->field_148, ptr->field_144.vy - ptr->field_14C);
    setXY2Fast(*poly, (u16)ptr->field_144.vx - (u16)ptr->field_148, ptr->field_144.vy + ptr->field_14C);
    setXY3Fast(*poly, (u16)ptr->field_144.vx + (u16)ptr->field_148, ptr->field_144.vy + ptr->field_14C);

    *(u32*)&(*poly)->u0 = 0x530000;
    *(u32*)&(*poly)->u1 = 0x6B001F;
    *(u16*)&(*poly)->u2 = 0x1F00;
    *(u16*)&(*poly)->u3 = 0x1F1F;

    var_v1 = ((u32)func_80055D78(sharedData_800DFB7C_0_s00[idx].field_0.vx_0, sharedData_800DFB7C_0_s00[idx].vy_8, sharedData_800DFB7C_0_s00[idx].field_4.vz_4) * 0x31) >> 5;
    var_v1 = MIN(var_v1, 0xC4);

    setRGBC0(*poly, var_v1, var_v1, var_v1, 0x2E);
    addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_140 - 8) >> 3], *poly, 9);
    *poly += 1;

    return true;
}

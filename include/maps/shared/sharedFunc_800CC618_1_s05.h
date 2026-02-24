#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

bool sharedFunc_800CC618_1_s05(POLY_FT4** poly, s32 idx)
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        SVECTOR         field_134;
        SVECTOR         field_13C;
        SVECTOR         field_144;
        VECTOR3         field_14C;
        s32             field_158;
        DVECTOR         field_15C;
        s32             field_160;
        s32             field_164;
        s32             field_168;
        s32             field_16C;
        s32             field_170;
        s32             field_174;
        s32             field_178;
        s32             field_17C;
        s32             field_180;
        s32             field_184;
        s32             field_188;
        s32             field_18C;
        s32             field_190;
    } s_sharedFunc_800CC618_1_s05;

    s32                          temp_v1_7;
    s32                          temp_v1_8;
    s32                          var_v0_4;
    s32                          temp_a0_3;
    u32                          temp_v1_6;
    s32                          temp;
    s32                          temp2;
    s32                          temp3;
    s_sharedFunc_800CC618_1_s05* ptr;

    ptr = PSX_SCRATCH;

    ptr->field_160 = MAX(0xFF - (sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 * 0x10 / 1228), 0);

    sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 += g_DeltaTime;

    if (sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 > 0x4CC0)
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 0;
    }

    if (ABS(g_SysWork.playerWork_4C.player_0.position_18.vx - sharedData_800DFB7C_0_s00[idx].field_0.vx_0) +
            ABS(g_SysWork.playerWork_4C.player_0.position_18.vz - sharedData_800DFB7C_0_s00[idx].field_4.vz_4) >
        0x14000)
    {
        return false;
    }

    ptr->field_168 = CLAMP_HIGH(sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_2, ((sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 * sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_2) / 2456) + 8);

    *(s32*)&ptr->field_12C = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 >> 4) - (u16)ptr->field_0.field_0.vx) - (u16)ptr->field_168) & 0xFFFF) +
                             (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 0x10);
    ptr->field_12C.vz = (sharedData_800DFB7C_0_s00[idx].field_4.vz_4 >> 4) - ptr->field_0.field_0.vz + (u16)ptr->field_168;

    *(s32*)&ptr->field_134 = (((u16)ptr->field_168 + ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 >> 4) - (u16)ptr->field_0.field_0.vx)) & 0xFFFF) +
                             (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 0x10);
    temp              = (u16)ptr->field_168;
    ptr->field_134.vz = temp + ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 >> 4) - ptr->field_0.field_0.vz);

    *(s32*)&ptr->field_13C = ((((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 >> 4) - (u16)ptr->field_0.field_0.vx) - (u16)ptr->field_168) & 0xFFFF) +
                             (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 0x10);
    temp2             = (u16)ptr->field_168;
    ptr->field_13C.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 >> 4) - ptr->field_0.field_0.vz) - temp2;

    *(s32*)&ptr->field_144 = (((u16)ptr->field_168 + ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 >> 4) - (u16)ptr->field_0.field_0.vx)) & 0xFFFF) +
                             (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 0x10);
    temp3             = (u16)ptr->field_168;
    ptr->field_144.vz = ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 >> 4) - ptr->field_0.field_0.vz) - temp3;

    gte_ldv3c(&ptr->field_12C);
    gte_rtpt();
    gte_stsxy3_g3(*poly);
    gte_stsz3c(&ptr->field_14C);
    gte_ldv0(&ptr->field_144);
    gte_rtps();
    gte_stsxy(&ptr->field_15C);
    gte_stsz(&ptr->field_158);

    ptr->field_14C.vx = (ptr->field_14C.vx + ptr->field_14C.vy + ptr->field_14C.vz + ptr->field_158) >> 2;

    if (ptr->field_14C.vx - 0x10 <= 0 || ((ptr->field_14C.vx - 0x10) >> 3) >= ORDERING_TABLE_SIZE ||
        ABS(ptr->field_15C.vx) > 200 || ABS(ptr->field_15C.vy) > 160)
    {
        return false;
    }

    *(s32*)&(*poly)->x3 = *(s32*)&ptr->field_15C;

    ptr->field_164 = (ptr->field_160 * (func_80055D78(sharedData_800DFB7C_0_s00[idx].field_0.vx_0, sharedData_800DFB7C_0_s00[idx].vy_8, sharedData_800DFB7C_0_s00[idx].field_4.vz_4))) >> 7;
    ptr->field_160 = CLAMP_HIGH(ptr->field_160, ptr->field_164);

    temp_a0_3      = sharedData_800DFB7C_0_s00[idx].field_10.s_1.field_3 & 7;
    ptr->field_16C = (!(sharedData_800DFB7C_0_s00[idx].field_10.s_1.field_3 & 8)) << 5;
    ptr->field_180 = MIN(sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 / 2456, 7) << 5;

    temp_v1_7 = temp_a0_3 ^ 0x1;
    temp_v1_7 = temp_v1_7 & 0x1;

    temp_v1_8 = (u32)temp_a0_3 >> 1;
    temp_v1_8 = temp_v1_8 ^ 0x1;
    temp_v1_8 = temp_v1_8 & 0x1;

    temp_v1_8 = temp_v1_7 ^ temp_v1_8;
    temp_v1_7 = (((temp_a0_3 >> 1) ^ 1) & 1) ^ ((temp_a0_3 ^ 1) & 1);

    if ((!(temp_a0_3 & 4) && (temp_v1_8 ^ 1) != 0) || ((temp_a0_3 & 4) && (temp_v1_8) != 0))
    {
        var_v0_4 = 0;
    }
    else
    {
        var_v0_4 = 0x1F;
    }
    ptr->field_170 = var_v0_4;

    if (temp_a0_3 >= 4)
    {
        ptr->field_184 = 0x1F;
    }
    else
    {
        ptr->field_184 = 0;
    }

    temp_v1_8 = temp_a0_3 ^ 0x1;
    temp_v1_8 = temp_v1_8 & 0x1;

    if ((!(temp_a0_3 & 4) && (temp_v1_8 ^ 1) != 0) || ((temp_a0_3 & 4) && (temp_v1_8) != 0))
    {
        var_v0_4 = 0;
    }
    else
    {
        var_v0_4 = 0x1F;
    }
    ptr->field_174 = var_v0_4;

    temp_v1_8 = (u32)temp_a0_3 >> 1;
    temp_v1_8 = temp_v1_8 ^ 1;
    temp_v1_8 = temp_v1_8 & 1;

    if ((!(temp_a0_3 & 0x4) && (temp_v1_8 ^ 0x1) != 0) || ((temp_a0_3 & 0x4) && temp_v1_8 != 0))
    {
        var_v0_4 = 0x1F;
    }
    else
    {
        var_v0_4 = 0;
    }
    ptr->field_188 = var_v0_4;

    temp_v1_8 = temp_a0_3 ^ 0x1;
    temp_v1_8 = temp_v1_8 & 0x1;

    if ((!(temp_a0_3 & 0x4) && (temp_v1_8 ^ 0x1) != 0) || ((temp_a0_3 & 0x4) && temp_v1_8 != 0))
    {
        var_v0_4 = 0x1F;
    }
    else
    {
        var_v0_4 = 0;
    }
    ptr->field_178 = var_v0_4;

    temp_v1_8 = (u32)temp_a0_3 >> 1;
    temp_v1_8 = temp_v1_8 ^ 1;
    temp_v1_8 = temp_v1_8 & 1;

    if ((!(temp_a0_3 & 0x4) && (temp_v1_8 ^ 0x1) != 0) || ((temp_a0_3 & 0x4) && temp_v1_8 != 0))
    {
        var_v0_4 = 0;
    }
    else
    {
        var_v0_4 = 0x1F;
    }
    ptr->field_18C = var_v0_4;

    temp_v1_7 = temp_a0_3 ^ 0x1;
    temp_v1_7 = temp_v1_7 & 0x1;

    temp_v1_8 = (u32)temp_a0_3 >> 1;
    temp_v1_8 = temp_v1_8 ^ 0x1;
    temp_v1_8 = temp_v1_8 & 0x1;

    temp_v1_8 = temp_v1_7 ^ temp_v1_8;

    if ((!(temp_a0_3 & 0x4) && (temp_v1_8 ^ 0x1) != 0) || ((temp_a0_3 & 0x4) && temp_v1_8 != 0))
    {
        var_v0_4 = 0x1F;
    }
    else
    {
        var_v0_4 = 0;
    }
    ptr->field_17C = var_v0_4;

    if (temp_a0_3 < 4)
    {
        ptr->field_190 = 0x1F;
    }
    else
    {
        ptr->field_190 = 0;
    }

    *(u32*)&(*poly)->u0 = ptr->field_16C + ptr->field_170 + ((ptr->field_180 + ptr->field_184) << 8) + 0x530000;
    *(u32*)&(*poly)->u1 = ptr->field_16C + ptr->field_174 + ((ptr->field_180 + ptr->field_188) << 8) + 0x6B0000;
    *(u16*)&(*poly)->u2 = ptr->field_16C + ptr->field_178 + ((ptr->field_180 + ptr->field_18C) << 8);
    *(u16*)&(*poly)->u3 = ptr->field_16C + ptr->field_17C + ((ptr->field_180 + ptr->field_190) << 8);

    setRGBC0(*poly, ptr->field_160, ptr->field_160, ptr->field_160, 0x2E);
    addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_14C.vx - 0x10) >> 3], *poly, 9);
    *poly += 1;

    return true;
}

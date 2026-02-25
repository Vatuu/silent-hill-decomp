#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

bool sharedFunc_800CB040_1_s05(POLY_FT4** poly, s32 idx)
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
    } s_func_800CB040;

    s32              var_s1;
    s32              halfSizeCeil;
    s32              halfSizeFloor;
    s_func_800CB040* ptr;

    ptr = PSX_SCRATCH;

    if (sharedData_800DFB7C_0_s00[idx].field_A == 8)
    {
        *(s32*)&(*poly)->u0 = ((sharedData_800DFB7C_0_s00[idx].field_B >= 2) << 6) + ((sharedData_800DFB7C_0_s00[idx].field_B >= 3) ? 0x020EC000 : 0x020E8000);

        *(s32*)&(*poly)->u1 = ((sharedData_800DFB7C_0_s00[idx].field_B >= 2) ? 0x7F : 0x3F) + (sharedData_800DFB7C_0_s00[idx].field_B >= 3 ? 0x6DC000 : 0x6D8000);

        *(s16*)&(*poly)->u2 = ((sharedData_800DFB7C_0_s00[idx].field_B >= 2) << 6) | ((sharedData_800DFB7C_0_s00[idx].field_B >= 3) ? 0xFF00 : 0xBF00);

        *(s16*)&(*poly)->u3 = ((sharedData_800DFB7C_0_s00[idx].field_B >= 2) ? 0x7F : 0x3F) | ((sharedData_800DFB7C_0_s00[idx].field_B >= 3) ? 0xFF00 : 0xBF00);

        // TODO: Might be single line statements / macros like above?
        if ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 < 0xE00)
        {
            POLY_FT4* poly2     = *poly;
            s32       var_v1_3  = 0xB4 + ((0xC4 - ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 >> 5)) << 8) + -(((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 >> 7));
            s32       var_v0_6  = var_v1_3 + (MAX(0, 0xC4 - ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 >> 4)) << 0x10) + 0x2E000000;
            *(s32*)&(poly2->r0) = var_v0_6;
        }
        else
        {
            POLY_FT4* poly2     = *poly;
            s32       var_a0    = MAX(0, 0x418 - ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 >> 2));
            s32       var_v0_7  = var_a0 + (MAX(0, 0x3D4 - ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 >> 2)) << 8) + 0x2E000000;
            *(s32*)&(poly2->r0) = var_v0_7;
        }
    }
    else
    {
        *(s32*)&(*poly)->u0 = 0x024E7800;
        *(s32*)&(*poly)->u1 = 0x4D7807;
        *(u16*)&(*poly)->u2 = 0x7F00;
        *(u16*)&(*poly)->u3 = 0x7F07;

        setRGBC0(*poly, 0x78, 0x80, 0x80, PRIM_POLY | 0xC | RECT_BLEND);
    }

    sharedData_800DFB7C_0_s00[idx].vy_8 = sharedData_800DFB7C_0_s00[idx].vy_8 + ptr->field_0.field_C4;

    var_s1 = (sharedData_800D8568_1_s05.field_8 * sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_1) >> 8;

    ptr->field_134 = sharedData_800DFB7C_0_s00[idx].field_0.vx_0 +
                     Q12_MULT(Math_Sin(sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2), var_s1);

    ptr->field_138 = sharedData_800DFB7C_0_s00[idx].field_4.vz_4 +
                     Q12_MULT(Math_Cos(sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2), var_s1);

    if ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 < (u16)ptr->field_0.field_C8)
    {
        q19_12 angle = func_8005C7B0(Q12_ANGLE(90.0f) - (((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 << 6) / sharedData_800D8568_1_s05.field_4));
        var_s1    = Q12_MULT((u16)ptr->field_0.field_CA, Math_Sin(angle)) + (u16)ptr->field_0.field_CC;

        ptr->field_134 = Q12_MULT(ptr->field_134, var_s1);
        ptr->field_138 = Q12_MULT(ptr->field_138, var_s1);
    }

    ptr->field_134 += ptr->field_0.field_D0;
    ptr->field_138 += ptr->field_0.field_D4;

    *(s32*)&ptr->field_12C = (((ptr->field_134 >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                             (((sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - ptr->field_0.field_0.vy) << 16);
    ptr->field_12C.vz = (ptr->field_138 >> 4) - ptr->field_0.field_0.vz;

    if (sharedData_800DFB7C_0_s00[idx].field_B & 1)
    {
        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 += Q12_MULT_PRECISE(g_DeltaTime, ((u16)sharedData_800D8568_1_s05.field_A * sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0) >> 8);
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 -= Q12_MULT_PRECISE(g_DeltaTime, ((u16)sharedData_800D8568_1_s05.field_A * sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0) >> 8);
    }

    sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 += ptr->field_0.field_CE;
    sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 += ptr->field_0.field_CE;

    if ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 >= Q12_ANGLE(360.0f))
    {
        if (sharedData_800D8568_1_s05.flags_0 & (1 << 1) && sharedData_800DFB7C_0_s00[idx].field_A == 8)
        {
            sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = (u16)sharedData_800D8568_1_s05.field_10 + Rng_GenerateUInt(0, 0xFFF);
            if ((sharedData_800D8568_1_s05.flags_0 & (1 << 3)) &&
                Rng_GenerateUInt(0, 15) == 0) // 1 in 16 chance.
            {
                sharedData_800DFB7C_0_s00[idx].field_A = 11;
            }
            else
            {
                sharedData_800DFB7C_0_s00[idx].field_A = 9;
            }
        }
        else
        {
            if (sharedData_800D8568_1_s05.flags_0 & (1 << 3) &&
                Rng_GenerateUInt(0, 15) == 0) // 1 in 16 chance.
            {
                s32 randVal                                        = Rng_GenerateUInt(Q12(0.5f), Q12_CLAMPED(1.0f));
                sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = randVal + (sharedData_800D8568_1_s05.field_10 >> 1);
                sharedData_800DFB7C_0_s00[idx].field_A             = 11;
            }
            else
            {
                sharedFunc_800CABF8_1_s05(idx, true);
            }

            return 0;
        }
    }

    gte_ldv0(&ptr->field_12C);
    gte_rtps();
    gte_stsxy(&ptr->field_140);
    gte_stsz(&ptr->field_13C);

    if (ptr->field_13C <= 0 || (ptr->field_13C >> 3) >= ORDERING_TABLE_SIZE ||
        ABS(ptr->field_140.vx) > 200 ||
        ABS(ptr->field_140.vy) > 160)
    {
        return false;
    }

    if (sharedData_800DFB7C_0_s00[idx].field_A != 8)
    {
        var_s1 = (ptr->field_0.field_2C * 4) / ptr->field_13C;
    }
    else
    {
        var_s1 = ptr->field_0.field_D8 / ptr->field_13C;
    }

    var_s1 = MAX(var_s1, 2);

    // `ptr->field_140` contains a base X/Y position for the poly.
    // Signed half-size offsets are then added (ceil/floor) to generate
    // four corner vertices of a centered quad.
    halfSizeCeil  = (var_s1 + 1) >> 1;
    halfSizeFloor = -(var_s1 >> 1);

    *(s32*)&(*poly)->x0 = *(s32*)&ptr->field_140 + halfSizeCeil + (halfSizeCeil << 16);
    *(s32*)&(*poly)->x1 = *(s32*)&ptr->field_140 + halfSizeFloor + (halfSizeCeil << 16);
    *(s32*)&(*poly)->x2 = *(s32*)&ptr->field_140 + halfSizeCeil + (halfSizeFloor << 16);
    *(s32*)&(*poly)->x3 = *(s32*)&ptr->field_140 + halfSizeFloor + (halfSizeFloor << 16);

    addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_13C >> 3], *poly, 9);
    *poly += 1;

    return true;
}

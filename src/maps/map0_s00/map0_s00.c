#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s00.h"

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB6B0

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CBBBC

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CBC94

void func_800CBFB0(s_800E34FC* arg0, s_800E330C* arg1, s32 mapId) // 0x800CBFB0
{
    VECTOR3 vecs[4] = {
        VECTOR3(-258.0f, -1.4f, 244.1f),
        VECTOR3(-254.5f,  0.0f, 220.5f),
        VECTOR3(-249.4f,  0.0f, 219.5f),
        VECTOR3(-250.5f,  0.0f, 217.7f)
    };

    GsInitCoordinate2(NULL, &g_SysWork.coord_22F8);
    D_800DD594 = true;
    D_800DD593 = true;
    D_800E34EC = ARRAY_SIZE(sharedData_800E330C_0_s00);
    D_800E39AC = ARRAY_SIZE(sharedData_800E34FC_0_s00);
    func_800D0394(2, vecs);
}

#include "maps/shared/Particle_Update.h" // 0x800CC04C

bool func_800CC6E8(s_800E34FC* arg0, s_800E330C* arg1, s32 mapId) // 0x800CC6E8
{
    MATRIX      sp10;
    MATRIX      sp30;
    MATRIX      sp50;      // @hack Guessed type based on `func_800CC8FC`. It doesn't fully match at first glance.
    MATRIX      sp70;      // @hack Unused or `sp50` and `sp70` are one big type together.
    VECTOR3     sp90[12];  // @hack Guessed type based on func_800CC8FC. This one is fairly certain.
    s32         sp120[32]; // @hack Unknown type, it's passed to `func_800CC8FC` but it's an unused parameter. 
    s32         temp_s4;
    s32         i;
    s_800E330C* curArg1;
    s_800E34FC* curArg0;

    if (g_SysWork.field_234B_4 == 0)
    {
        return false;
    }

    if (g_SysWork.field_234B_4 == 2 && !func_800D0600())
    {
        return false;
    }

    curArg0 = arg0;
    curArg1 = arg1;

    if (!Game_FlashlightIsOn())
    {
        D_800E0C64 = -0x400;
    }

    temp_s4 = func_800CC8FC(&sp90, &sp120, &sp50);
    GsInitCoordinate2(NULL, &g_SysWork.coord_22F8);

    g_SysWork.coord_22F8.coord.t[2] = Q8(0.0f);
    g_SysWork.coord_22F8.coord.t[1] = Q8(0.0f);
    g_SysWork.coord_22F8.coord.t[0] = Q8(0.0f);
    g_SysWork.coord_22F8.flg        = false;

    func_80049B6C(&g_SysWork.coord_22F8, &sp10, &sp30);
    gte_SetRotMatrix(&sp30);
    gte_SetTransMatrix(&sp30);

    if (D_800DD593)
    {
        for (i = 0; i < D_800E39AC; i++, curArg0++)
        {
            func_800CE02C(i, func_800D012C(&curArg0->field_0, &sp50, temp_s4), curArg0, mapId);
        }
    }

    if (D_800DD594)
    {
        for (i = 0; i < D_800E34EC; i++, curArg1++)
        {
            func_800CD8E8(i, (s32)(Rng_Rand16() % 65) >> 6, curArg1);
        }
    }

    return false;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC8FC);

void func_800CD1F4(s32 arg0, s32 arg1, s_func_800CD1F4* arg2) // 0x800CD1F4
{
    VECTOR3 pos; // Q23.8
    q3_12   angle0;
    q3_12   angle1;
    s32     temp_s0_3;
    s32     var_s0;

    if (sharedData_800DD584_0_s00 != 0)
    {
        return;
    }

    arg2->field_0.vx += TIMESTEP_SCALE(g_DeltaTime0, arg2->field_C.vx);
    arg2->field_0.vy += TIMESTEP_SCALE(g_DeltaTime0, arg2->field_C.vy);
    arg2->field_0.vz += TIMESTEP_SCALE(g_DeltaTime0, arg2->field_C.vz);

    limitRange(arg2->field_C.vx, -0x100, 0xFF);
    limitRange(arg2->field_C.vy, -0xFF, 0xFF);
    limitRange(arg2->field_C.vz, -0xFF, 0xFF);

    switch (arg2->field_15)
    {
        case 1:
            arg2->field_C.vy += Rng_GenerateInt(Rng_Rand16(), -4, 4);
            limitRange(arg2->field_C.vy, -16, 16);

            arg2->field_C.vx += FP_MULTIPLY(Math_Sin((arg2->field_16 + arg0) << 5), Q12(0.01f), Q12_SHIFT);
            arg2->field_C.vz += FP_MULTIPLY(Math_Cos((arg2->field_16 + arg0) << 5), Q12(0.01f), Q12_SHIFT);

            var_s0 = arg2->field_16;

            if ((Rng_TestProbabilityBits(5) + 0x80) < var_s0)
            {
                arg2->field_15 = Rng_GenerateInt(Rng_Rand16(), 1, 3);
                arg2->field_16 = 0;
            }
            else
            {
                arg2->field_16++;
            }

            if (arg1 != 0)
            {
                arg2->field_15 = 5;
                arg2->field_16 = 0;
            }
            break;

        case 2:
            arg2->field_C.vy += Rng_GenerateInt(Rng_Rand16(), -4, 4);
            limitRange(arg2->field_C.vy, -16, 16);

            arg2->field_C.vx += FP_MULTIPLY(Math_Sin((arg2->field_16 + arg0) << 5), Q12(0.01f), Q12_SHIFT);
            arg2->field_C.vz += FP_MULTIPLY(Math_Cos((arg2->field_16 + arg0) << 6), Q12(0.01f), Q12_SHIFT);

            var_s0 = arg2->field_16;

            if ((Rng_TestProbabilityBits(6) + 0x80) < var_s0)
            {
                arg2->field_15 = Rng_GenerateInt(Rng_Rand16(), 1, 3);
                arg2->field_16 = 0;
            }
            else
            {
                arg2->field_16++;
            }

            if (arg1 != 0)
            {
                arg2->field_15 = 5;
                arg2->field_16 = 0;
            }
            break;

        case 3:
            arg2->field_C.vy += Rng_GenerateInt(Rng_Rand16(), -4, 4);
            limitRange(arg2->field_C.vy, -16, 16);

            if (arg2->field_16 == 0)
            {
                angle0 = Rng_GenerateInt(Rng_Rand16(), 0, Q12(1.0f) - 1);

                arg2->field_C.vx = (u32)(Math_Sin(angle0) * 5) >> 7;
                arg2->field_C.vz = (u32)(Math_Sin(angle0) * 5) >> 7;
            }

            var_s0 = arg2->field_16;

            if ((Rng_TestProbabilityBits(7) + 0x64) < var_s0)
            {
                arg2->field_15 = Rng_GenerateInt(Rng_Rand16(), 1, 3);
                arg2->field_16 = 0;
            }
            else
            {
                arg2->field_16++;
            }

            if (arg1 != 0)
            {
                arg2->field_15 = 5;
                arg2->field_16 = 0;
            }
            break;

        case 5:
            if (arg0 < Rng_GenerateInt(Rng_Rand16(), 10, 19) || g_SysWork.field_2358 == 0)
            {
                pos.vx = Q12_TO_Q8(D_800E32DC->vx - arg2->field_0.vx);
                pos.vy = Q12_TO_Q8(D_800E32DC->vy - arg2->field_0.vy);
                pos.vz = Q12_TO_Q8(D_800E32DC->vz - arg2->field_0.vz);
            }
            else
            {
                pos.vx = g_SysWork.playerBoneCoords_890[HarryBone_RightHand].workm.t[0] - Q12_TO_Q8(arg2->field_0.vx);
                pos.vy = g_SysWork.playerBoneCoords_890[HarryBone_RightHand].workm.t[1] - Q12_TO_Q8(arg2->field_0.vy);
                pos.vz = g_SysWork.playerBoneCoords_890[HarryBone_RightHand].workm.t[2] - Q12_TO_Q8(arg2->field_0.vz);
            }

            temp_s0_3 = SquareRoot0(SQUARE(pos.vx) + SQUARE(pos.vz));
            angle0    = ratan2(pos.vx, pos.vz);
            angle1    = ratan2(pos.vy, temp_s0_3);

            arg2->field_C.vx += FP_MULTIPLY(Math_Sin(angle0), Q12(0.02f) - 1, Q12_SHIFT);
            arg2->field_C.vz += FP_MULTIPLY(Math_Cos(angle0), Q12(0.02f) - 1, Q12_SHIFT);
            arg2->field_C.vy += FP_MULTIPLY(Math_Sin(angle1), Q12(0.01f),     Q12_SHIFT);

            var_s0 = arg2->field_16;

            if ((Rng_TestProbabilityBits(6) + 80) < var_s0 || (arg1 != 0 && arg2->field_16 > 80))
            {
                arg2->field_16 = 0;
                arg2->field_15 = Rng_GenerateInt(Rng_Rand16(), 1, 3);
            }
            else
            {
                arg2->field_16++;
            }
            break;
    }
}

INCLUDE_RODATA("asm/maps/map0_s00/nonmatchings/map0_s00", D_800CA7CC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD8E8);

void func_800CE02C(s32 arg0, s32 arg1, s_800E34FC* pos, s32 mapId) // 0x800CE02C
{
    SVECTOR3  posQ8;
    POLY_FT4* poly;
    s32       depth;
    s32       depthDiv16;

    func_800CE544(arg0, arg1, pos);

    poly = (POLY_FT4*)GsOUT_PACKET_P;
    setPolyFT4(poly);
    setSemiTrans(poly, true);

    poly->tpage = 76;
    poly->clut  = 76;

    if (sharedData_800DD584_0_s00 != 0)
    {
        switch (arg0 & 3)
        {
            case 0:
                poly->u0 = 64;
                poly->v0 = 240;
                poly->u1 = 64;
                poly->v1 = 255;
                poly->u2 = 80;
                poly->v2 = 240;
                poly->u3 = 80;
                poly->v3 = 255;
                break;

            case 1:
                poly->u0 = 80;
                poly->v0 = 240;
                poly->u1 = 80;
                poly->v1 = 255;
                poly->u2 = 96;
                poly->v2 = 240;
                poly->u3 = 96;
                poly->v3 = 255;
                break;

            case 2:
                poly->u0 = 96;
                poly->v0 = 240;
                poly->u1 = 96;
                poly->v1 = 255;
                poly->u2 = 112;
                poly->v2 = 240;
                poly->u3 = 112;
                poly->v3 = 255;
                break;

            case 3:
                poly->u0 = 112;
                poly->v0 = 240;
                poly->u1 = 112;
                poly->v1 = 255;
                poly->u2 = 128;
                poly->v2 = 240;
                poly->u3 = 128;
                poly->v3 = 255;
                break;
        }
    }
    else
    {
        switch (g_SysWork.timer_1C & 7)
        {
            case 0:
            case 1:
                switch (arg0 & 3)
                {
                    case 0:
                        poly->u0 = 64;
                        poly->v0 = 240;
                        poly->u1 = 64;
                        poly->v1 = 255;
                        poly->u2 = 80;
                        poly->v2 = 240;
                        poly->u3 = 80;
                        poly->v3 = 255;
                        break;

                    case 1:
                        poly->u0 = 80;
                        poly->v0 = 240;
                        poly->u1 = 80;
                        poly->v1 = 255;
                        poly->u2 = 96;
                        poly->v2 = 240;
                        poly->u3 = 96;
                        poly->v3 = 255;
                        break;

                    case 2:
                        poly->u0 = 96;
                        poly->v0 = 240;
                        poly->u1 = 96;
                        poly->v1 = 255;
                        poly->u2 = 112;
                        poly->v2 = 240;
                        poly->u3 = 112;
                        poly->v3 = 255;
                        break;

                    case 3:
                        poly->u0 = 112;
                        poly->v0 = 240;
                        poly->u1 = 112;
                        poly->v1 = 255;
                        poly->u2 = 128;
                        poly->v2 = 240;
                        poly->u3 = 128;
                        poly->v3 = 255;
                        break;
                }
                break;

            case 2:
            case 3:
                switch (arg0 & 3)
                {
                    case 0:
                        poly->u0 = 80;
                        poly->v0 = 240;
                        poly->u1 = 80;
                        poly->v1 = 255;
                        poly->u2 = 96;
                        poly->v2 = 240;
                        poly->u3 = 96;
                        poly->v3 = 255;
                        break;

                    case 1:
                        poly->u0 = 96;
                        poly->v0 = 240;
                        poly->u1 = 96;
                        poly->v1 = 255;
                        poly->u2 = 112;
                        poly->v2 = 240;
                        poly->u3 = 112;
                        poly->v3 = 255;
                        break;

                    case 2:
                        poly->u0 = 112;
                        poly->v0 = 240;
                        poly->u1 = 112;
                        poly->v1 = 255;
                        poly->u2 = 128;
                        poly->v2 = 240;
                        poly->u3 = 128;
                        poly->v3 = 255;
                        break;

                    case 3:
                        poly->u0 = 64;
                        poly->v0 = 240;
                        poly->u1 = 64;
                        poly->v1 = 255;
                        poly->u2 = 80;
                        poly->v2 = 240;
                        poly->u3 = 80;
                        poly->v3 = 255;
                        break;
                }
                break;

            case 4:
            case 5:
                switch (arg0 & 3)
                {
                    case 0:
                        poly->u0 = 96;
                        poly->v0 = 240;
                        poly->u1 = 96;
                        poly->v1 = 255;
                        poly->u2 = 112;
                        poly->v2 = 240;
                        poly->u3 = 112;
                        poly->v3 = 255;
                        break;

                    case 1:
                        poly->u0 = 112;
                        poly->v0 = 240;
                        poly->u1 = 112;
                        poly->v1 = 255;
                        poly->u2 = 128;
                        poly->v2 = 240;
                        poly->u3 = 128;
                        poly->v3 = 255;
                        break;

                    case 2:
                        poly->u0 = 64;
                        poly->v0 = 240;
                        poly->u1 = 64;
                        poly->v1 = 255;
                        poly->u2 = 80;
                        poly->v2 = 240;
                        poly->u3 = 80;
                        poly->v3 = 255;
                        break;

                    case 3:
                        poly->u0 = 80;
                        poly->v0 = 240;
                        poly->u1 = 80;
                        poly->v1 = 255;
                        poly->u2 = 96;
                        poly->v2 = 240;
                        poly->u3 = 96;
                        poly->v3 = 255;
                        break;
                }
                break;

            case 6:
            case 7:
                switch (arg0 & 3)
                {
                    case 0:
                        poly->u0 = 112;
                        poly->v0 = 240;
                        poly->u1 = 112;
                        poly->v1 = 255;
                        poly->u2 = 128;
                        poly->v2 = 240;
                        poly->u3 = 128;
                        poly->v3 = 255;
                        break;

                    case 1:
                        poly->u0 = 64;
                        poly->v0 = 240;
                        poly->u1 = 64;
                        poly->v1 = 255;
                        poly->u2 = 80;
                        poly->v2 = 240;
                        poly->u3 = 80;
                        poly->v3 = 255;
                        break;

                    case 2:
                        poly->u0 = 80;
                        poly->v0 = 240;
                        poly->u1 = 80;
                        poly->v1 = 255;
                        poly->u2 = 96;
                        poly->v2 = 240;
                        poly->u3 = 96;
                        poly->v3 = 255;
                        break;

                    case 3:
                        poly->u0 = 96;
                        poly->v0 = 240;
                        poly->u1 = 96;
                        poly->v1 = 255;
                        poly->u2 = 112;
                        poly->v2 = 240;
                        poly->u3 = 112;
                        poly->v3 = 255;
                        break;
                }
        }
    }

    poly->b0 = poly->g0 = poly->r0 = 0x80;

    posQ8.vx = Q12_TO_Q8(pos->field_0.vx);
    posQ8.vy = Q12_TO_Q8(pos->field_0.vy);
    posQ8.vz = Q12_TO_Q8(pos->field_0.vz);

    gte_ldv0(&posQ8);
    gte_rtps();
    gte_stsxy(&poly->x0);
    gte_stszotz(&depth);

    depthDiv16 = depth >> 4;
    depth      = depth >> 1;

    if (depth >= 33 && depth < 1023)
    {
        u8 var_a1;

        if (depthDiv16 >= 13)
        {
            var_a1 = 3;
        }
        else
        {
            var_a1 = 16 - depthDiv16;
        }

        if (var_a1 >= 3)
        {
            if (var_a1 >= 17)
            {
                var_a1 = 16;
            }
        }
        else
        {
            var_a1 = 3;
        }

        poly->x1 = poly->x0;
        poly->x2 = poly->x3 = poly->x0 + var_a1;
        poly->y2            = poly->y0;
        poly->y1 = poly->y3 = poly->y0 + var_a1;

        GsOUT_PACKET_P = (PACKET*)&poly[1];
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[depth], poly);
    }
}

void func_800CE544(s32 idx0, s32 arg1, s_800E34FC* arg2) // 0x800CE544
{
    s16     rng0;
    q3_12   angle;
    s32     someMax;
    s32     someMin;
    VECTOR3 vecCpy;

    if (sharedData_800DD584_0_s00 == 0)
    {
        arg2->field_0.vx += TIMESTEP_SCALE(g_DeltaTime0, arg2->field_C);
        arg2->field_0.vz += TIMESTEP_SCALE(g_DeltaTime0, arg2->field_E);

        switch (arg2->field_11)
        {
            case 1:
                arg2->field_12++;
                if (arg1)
                {
                    if (Rng_Rand16() & 0x1)
                    {
                        arg2->field_11 = 5;
                        arg2->field_12 = 0;
                    }
                    else
                    {
                        arg2->field_11 = 6;
                    }
                }

                if (arg2->field_12 > Rng_GenerateInt((u32)Rng_Rand16(), 100, 227))
                {
                    arg2->field_11 = ((Rng_Rand16() & 1) * 3) + 1;
                    arg2->field_12 = 0;
                }

                arg2->field_C += Rng_GenerateInt(Rng_Rand16(), -4, 4);
                arg2->field_E += Rng_GenerateInt(Rng_Rand16(), -4, 4);
                break;

            case 2:
                arg2->field_12++;
                if (arg1)
                {
                    arg2->field_11 = 5;
                    arg2->field_12 = 0;
                }

                arg2->field_C += Rng_GenerateInt(Rng_Rand16(), -4, 4);
                arg2->field_E += Rng_GenerateInt(Rng_Rand16(), -4, 4);

                if (arg2->field_12 > Rng_GenerateInt((u32)Rng_Rand16(), 100, 227))
                {
                    arg2->field_11 = (Rng_Rand16() & 1) + 3;
                    arg2->field_12 = 0;
                    rng0 = Rng_GenerateInt(Rng_Rand16(), 0, 0xfff);
                    arg2->field_C = (u32)(Math_Sin(rng0) * 3) / 0x100;
                    arg2->field_E = (u32)(Math_Cos(rng0) * 3) / 0x100;
                }
                break;

            case 3:
                arg2->field_12++;

                if (arg2->field_12 > Rng_GenerateInt((u32)Rng_Rand16(), 100, 227))
                {
                    arg2->field_11 = 2;
                    arg2->field_E = 0;
                    arg2->field_C = 0;
                    arg2->field_12 = 0;
                }

                if (arg1)
                {
                    arg2->field_11 = 5;
                    arg2->field_12 = 0;
                }
                break;

            case 4:
                arg2->field_12++;

                vecCpy.vx = D_800E32DC[(idx0 / 20) + 1].vx - arg2->field_0.vx;
                vecCpy.vz = D_800E32DC[(idx0 / 20) + 1].vz - arg2->field_0.vz;
                vecCpy.vy = 0;

                angle = ratan2(vecCpy.vx, vecCpy.vz);
                arg2->field_C = (u32)(Math_Sin(angle) * 3) / 0x100;
                arg2->field_E = (u32)(Math_Cos(angle) * 3) / 0x100;

                if (arg1)
                {
                    arg2->field_11 = Rng_GenerateInt((u32)Rng_Rand16(), 5, 6);
                    arg2->field_12 = 0;
                }

                if (arg2->field_12 > 192)
                {
                    arg2->field_11 = Rng_GenerateInt((u32)Rng_Rand16(), 1, 2);
                    arg2->field_E = 0;
                    arg2->field_C = 0;
                    arg2->field_12 = 0;
                }
                break;

            case 5:
                if (arg2->field_12 == 0)
                {
                    vecCpy.vx = (arg2->field_0.vx - g_SysWork.player_4C.chara_0.position_18.vx) >> 4;
                    vecCpy.vz = (arg2->field_0.vz - g_SysWork.player_4C.chara_0.position_18.vz) >> 4;
                    angle = ratan2(vecCpy.vx, vecCpy.vz);
                    arg2->field_C = (u32)(Math_Sin(angle) * 3) / 0x10;
                    arg2->field_E = (u32)(Math_Cos(angle) * 3) / 0x10;
                }

                if (arg1)
                {
                    arg2->field_12 = 0;
                }

                if (arg2->field_12 > 16)
                {
                    arg2->field_11 = 2;
                    arg2->field_12 = 0;
                }

                arg2->field_12++;
                break;

            case 6:
                arg2->field_12++;

                if (arg2->field_12 > Rng_GenerateInt((u32)Rng_Rand16(), 20, 21))
                {
                    if (arg1)
                    {
                        arg2->field_11 = Rng_GenerateInt((u32)Rng_Rand16(), 5, 6);
                        arg2->field_12 = 0;
                    }
                    else
                    {
                        arg2->field_11 = (Rng_GenerateInt((u32)Rng_Rand16(), 0, 1) * 3) + 1;
                    }
                }

                arg2->field_C += Rng_GenerateInt(Rng_Rand16(), -4, 4);
                arg2->field_E += Rng_GenerateInt(Rng_Rand16(), -4, 4);
                break;
        }

        someMin = (arg2->field_11 == 5) ? -64 : -20;
        someMax = (arg2->field_11 == 5) ?  64 :  20;
        arg2->field_C = CLAMP(arg2->field_C, someMin, someMax);
        arg2->field_E = CLAMP(arg2->field_E, someMin, someMax);
    }
}

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CEB24

#include "maps/shared/sharedFunc_800CEFF4_0_s00.h" // 0x800CEFF4

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF2A4

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CF974

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CFFF8

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800D0124

bool func_800D012C(VECTOR3* pos, MATRIX* unused0, s32* unused1) // 0x800D012C
{
    q19_12 deltaX;
    q19_12 deltaZ;

    switch (g_SysWork.field_234B_4)
    {
        case 1:
            return true;

        case 2:
            deltaX = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vx - pos->vx);
            deltaZ = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vz - pos->vz);
            return SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)) < Q8(1.0f);
    }

    return false;
}

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800D01BC

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800D0274

void func_800D0394(s32 arg0, VECTOR3* vecs) // 0x800D0394
{
    VECTOR3*    vec;
    s32         unkZ;
    s32         i;
    s32         var_v0;
    s32         idx;
    s32         rand0;
    s32         rand1;
    s32         rand;
    s32         mult;
    s_800E330C* curUnk;
    s_800E34FC* var_s1;

    g_SysWork.field_234B_4 = arg0;
    if (arg0)
    {
        sharedFunc_800D0A60_0_s00(D_800C39A0);

        if (arg0 == 2)
        {
            for (i = 0; i < ARRAY_SIZE(D_800E32DC); i++, vecs++)
            {
                D_800E32DC[i].vx = vecs->vx;
                D_800E32DC[i].vy = vecs->vy;
                D_800E32DC[i].vz = vecs->vz;
            }

            if (D_800DD593)
            {

                for (i = 0; i < ARRAY_SIZE(sharedData_800E34FC_0_s00); i++)
                {
                    rand = Rng_Rand16();
                    rand0 = rand;
                    var_s1 = &sharedData_800E34FC_0_s00[i];
                    idx = (i / 20) + 1;
                    vec = &D_800E32DC[idx];

                    // TODO: Is this angle math?
                    var_s1->field_0.vx = (vec->vx + Q12_FRACT(rand0)) - Q12(0.5f);
                    var_s1->field_0.vz = (vec->vz + Q12_FRACT(Rng_Rand16())) - Q12(0.5f);
                    var_s1->field_0.vy = vec->vy;
                    var_s1->field_11 = 1;
                    var_s1->field_10 = 1;
                    var_s1->field_12 = 0;
                    var_s1->field_C = 0;
                    var_s1->field_E = 0;
                }
            }

            if (D_800DD594)
            {
                for (i = 0; i < ARRAY_SIZE(sharedData_800E330C_0_s00); i++)
                {
                    curUnk = &sharedData_800E330C_0_s00[i];

                    // TODO: Should be `Rng_GenerateInt(-2.5f, 2.5f)`, but casts in this macro make it not fit here.
                    curUnk->field_0.vx = D_800E32DC[0].vx + (Rng_Rand16() % Q12(5.0f)) - Q12(2.5f);

                    rand0 = -Rng_Rand16();
                    var_v0 = rand0;
                    if (rand0 < 0)
                    {
                        var_v0 = rand0 + (Q12(4.0f) - 1);
                    }

                    curUnk->field_0.vy = D_800E32DC[0].vy + (rand0 - ((var_v0 >> 14) << 14));

                    rand1 = Rng_Rand16();
                    unkZ = D_800E32DC[0].vz;
                    mult = rand1 / Q12(5.0f);
                    rand = rand1 - (mult * Q12(5.0f));

                    curUnk->field_15 = 1;
                    curUnk->field_14 = 1;
                    curUnk->field_C  = 0;
                    curUnk->field_10 = 0;
                    curUnk->field_0.vz = (unkZ + rand) - Q12(2.5f);
                }
            }
        }
    }
}

bool func_800D0600(void) // 0x800D0600
{
    #define DIST_MAX Q12(40.0f)

    if (ABS(g_SysWork.player_4C.chara_0.position_18.vx - D_800E32DC[0].vx) +
        ABS(g_SysWork.player_4C.chara_0.position_18.vz - D_800E32DC[0].vz) < DIST_MAX ||
        ABS(g_SysWork.player_4C.chara_0.position_18.vx - D_800E32DC[1].vx) +
        ABS(g_SysWork.player_4C.chara_0.position_18.vz - D_800E32DC[1].vz) < DIST_MAX)
    {
        return true;
    }

    return false;
}

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800D0700

#include "maps/shared/Player.h"

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D2F08

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D309C

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D3308_0_s00); // 0x800D3308

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D3B44

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D3EF4_0_s00);

void sharedFunc_800D4924_0_s00(s_SubCharacter* chara) {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D492C_0_s00);

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D63D0

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D54A8_0_s00);

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D5B48

#include "maps/shared/sharedFunc_800D5C64_0_s00.h" // 0x800D5C64

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D5FCC

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D63D0

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D654C

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6554

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D670C

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D67FC

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D6970_0_s00); // 0x800D6970

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D70C4_0_s00); // 0x800D70C4

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D7BE8

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D7E04

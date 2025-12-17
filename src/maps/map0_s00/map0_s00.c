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
    s_func_800CC8FC sp50;
    VECTOR3         sp90[12];
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

s32 func_800CC8FC(VECTOR3* arg0, s32* arg1, s_func_800CC8FC* arg2) // 0x800CC8FC
{
    SVECTOR            sp10;
    SVECTOR            sp18;
    SVECTOR            sp20;
    DVECTOR            sp28;
    DVECTOR            sp30[8];
    SVECTOR            sp50[12];
    MATRIX             spB0;
    VECTOR3*           vecPtr;
    s32                temp_a0;
    s32                temp_s4;
    s32                temp_s5;
    s32                temp_s7;
    s32                j;
    s32                i;
    s32                var_s5;
    s_func_800CC8FC_0* ptr;
    DVECTOR*           dVecPtr;

    s16 D_800CA7CC[18][2] = {
        { 0x00, 0x06 },
        { 0x01, 0x07 },
        { 0x02, 0x08 },
        { 0x03, 0x09 },
        { 0x04, 0x0A },
        { 0x05, 0x0B },
        { 0x00, 0x01 },
        { 0x01, 0x02 },
        { 0x02, 0x03 },
        { 0x03, 0x04 },
        { 0x04, 0x05 },
        { 0x05, 0x00 },
        { 0x06, 0x07 },
        { 0x07, 0x08 },
        { 0x08, 0x09 },
        { 0x09, 0x0A },
        { 0x0A, 0x0B },
        { 0x0B, 0x06 },
    };

    temp_s4 = D_800E0C74.field_0 >> 6;
    temp_s7 = D_800E0C74.field_0 >> 3;
    temp_a0 = D_800E0C74.field_0 / 20;
    temp_s5 = D_800E0C74.field_0 / 12;

    for (i = 0; i < 6; i++)
    {
        sp50[i].vx = FP_MULTIPLY(temp_a0, Math_Sin((i * 0x3C000) / 360), 0xC);
        sp50[i].vy = FP_MULTIPLY(temp_a0, Math_Cos((i * 0x3C000) / 360), 0xC);
        sp50[i].vz = -temp_s4;
    }

    for (i = 0; i < 6; i++)
    {
        sp50[i + 6].vx = FP_MULTIPLY(temp_s5, Math_Sin((i * 0x3C000) / 360), 0xC);
        sp50[i + 6].vy = FP_MULTIPLY(temp_s5, Math_Cos((i * 0x3C000) / 360), 0xC);
        sp50[i + 6].vz = temp_s7;
    }

    var_s5 = 0;
    Math_RotMatrixZxyNegGte(&g_ParticleVectors0.svec_18, &spB0);

    for (j = 0; j < 18; j++)
    {
        sp10 = sp50[D_800CA7CC[j][0]];

        PushMatrix();
        ApplyMatrixSV(&spB0, &sp10, &sp18);
        PopMatrix();

        vecPtr = &arg0[D_800CA7CC[j][0]];

        vecPtr->vx = (sp18.vx * 0x10) + (g_ParticleVectors0.vector_0.vx - g_SysWork.player_4C.chara_0.position_18.vx);
        vecPtr->vy = (sp18.vy * 0x10) + (g_ParticleVectors0.vector_0.vy - g_SysWork.player_4C.chara_0.position_18.vy);
        vecPtr->vz = (sp18.vz * 0x10) + (g_ParticleVectors0.vector_0.vz - g_SysWork.player_4C.chara_0.position_18.vz);

        sp18.vx += (g_ParticleVectors0.vector_0.vx - g_SysWork.player_4C.chara_0.position_18.vx) >> 4;
        sp18.vy += (g_ParticleVectors0.vector_0.vy - g_SysWork.player_4C.chara_0.position_18.vy) >> 4;
        sp18.vz += (g_ParticleVectors0.vector_0.vz - g_SysWork.player_4C.chara_0.position_18.vz) >> 4;

        gte_ldv0(&sp18);
        gte_rtps();

        sp10 = sp50[D_800CA7CC[j][1]];

        PushMatrix();
        ApplyMatrixSV(&spB0, &sp10, &sp20);
        PopMatrix();

        vecPtr = &arg0[D_800CA7CC[j][1]];

        vecPtr->vx = (sp20.vx * 0x10) + (g_ParticleVectors0.vector_0.vx - g_SysWork.player_4C.chara_0.position_18.vx);
        vecPtr->vy = (sp20.vy * 0x10) + (g_ParticleVectors0.vector_0.vy - g_SysWork.player_4C.chara_0.position_18.vy);
        vecPtr->vz = (sp20.vz * 0x10) + (g_ParticleVectors0.vector_0.vz - g_SysWork.player_4C.chara_0.position_18.vz);

        sp20.vx += (g_ParticleVectors0.vector_0.vx - g_SysWork.player_4C.chara_0.position_18.vx) >> 4;
        sp20.vy += (g_ParticleVectors0.vector_0.vy - g_SysWork.player_4C.chara_0.position_18.vy) >> 4;
        sp20.vz += (g_ParticleVectors0.vector_0.vz - g_SysWork.player_4C.chara_0.position_18.vz) >> 4;

        if ((sp18.vy >= 0 && sp20.vy < 0) || (sp18.vy < 0 && sp20.vy >= 0))
        {
            sp30[var_s5].vx = sp18.vx - (sp18.vy * (sp20.vx - sp18.vx)) / (sp20.vy - sp18.vy);
            sp30[var_s5].vy = sp18.vz - (sp18.vy * (sp20.vz - sp18.vz)) / (sp20.vy - sp18.vy);
            var_s5++;
        }
    }

    if (var_s5 == 0)
    {
        return 0;
    }

    for (i = 0; i < (var_s5 - 1); i++)
    {
        for (j = i + 1; j < var_s5; j++)
        {
            if (sp30[i].vx > sp30[j].vx)
            {
                sp28    = sp30[i];
                sp30[i] = sp30[j];
                sp30[j] = sp28;
            }
        }
    }

    ptr = arg2->field_0;

    for (j = 0; j < 3; j++)
    {
        ptr[j].field_0 = sp30[j];
    }

    if ((ptr[1].field_0.vx - ptr[0].field_0.vx) * (ptr[2].field_0.vy - ptr[0].field_0.vy) <=
        (ptr[1].field_0.vy - ptr[0].field_0.vy) * (ptr[2].field_0.vx - ptr[0].field_0.vx))
    {
        sp28           = ptr[1].field_0;
        ptr[1].field_0 = ptr[2].field_0;
        ptr[2].field_0 = sp28;
    }

    for (j = 0; j < 3; j++)
    {
        ptr[j].field_4 = j - 1;
        ptr[j].field_5 = j + 1;
    }

    ptr[0].field_4 = 2;
    ptr[2].field_5 = 0;

    ptr = arg2->field_0;

    for (i = 3; i < var_s5; i++)
    {
        dVecPtr = &sp10;

        j = 0;

        while ((ptr[ptr[j].field_5].field_0.vx - ptr[j].field_0.vx) * (dVecPtr[i + 8].vy - ptr[j].field_0.vy) >
               (ptr[ptr[j].field_5].field_0.vy - ptr[j].field_0.vy) * (dVecPtr[i + 8].vx - ptr[j].field_0.vx))
        {
            j = ptr[j].field_5;
        }

        ptr[i].field_7 = j;

        j = 0;

        while ((ptr[j].field_0.vx - ptr[ptr[j].field_4].field_0.vx) * (dVecPtr[i + 8].vy - ptr[ptr[j].field_4].field_0.vy) >
               (ptr[j].field_0.vy - ptr[ptr[j].field_4].field_0.vy) * (dVecPtr[i + 8].vx - ptr[ptr[j].field_4].field_0.vx))
        {
            j = ptr[j].field_5;
        }

        ptr[i].field_6 = j;

        ptr[ptr[i].field_7].field_5 = i;
        ptr[ptr[i].field_6].field_4 = i;

        ptr[i].field_5 = ptr[i].field_6;
        ptr[i].field_4 = ptr[i].field_7;

        ptr[i].field_0 = sp30[i];
    }

    D_800DFB54 = 1;

    for (i = 0; ptr[i].field_5 != 0; D_800DFB54++)
    {
        i = ptr[i].field_5;
    }

    return D_800DFB54;
}

void func_800CD1F4(s32 arg0, s32 arg1, s_800E330C* arg2) // 0x800CD1F4
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

void func_800CD8E8(s32 arg0, s32 arg1, s_800E330C* arg2) // 0x800CD8E8
{
    SVECTOR   pos; // Q23.8
    s32       depth;
    u8        temp_v0;
    POLY_FT4* poly;

    func_800CD1F4(arg0, arg1, arg2);

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    // Set as `POLY_FT4` with `tpage = 44`.
    setPolyFT4TPage(poly, 44);

    poly->clut = 12;

    if (sharedData_800DD584_0_s00 != 0)
    {
        switch (arg0 & 3)
        {
            case 0:
                setUV4(poly, 0, 240, 0, 255, 16, 240, 16, 255);
                break;

            case 1:
                setUV4(poly, 16, 240, 16, 255, 32, 240, 32, 255);
                break;

            case 2:
                setUV4(poly, 32, 240, 32, 255, 48, 240, 48, 255);
                break;

            case 3:
                setUV4(poly, 48, 240, 48, 255, 64, 240, 64, 255);
                break;
        }
    }
    else
    {
        switch (g_SysWork.timer_1C & 0x7)
        {
            case 0:
            case 1:
                switch (arg0 & 3)
                {
                    case 0:
                        setUV4(poly, 0, 240, 0, 255, 16, 240, 16, 255);
                        break;

                    case 1:
                        setUV4(poly, 16, 240, 16, 255, 32, 240, 32, 255);
                        break;

                    case 2:
                        setUV4(poly, 32, 240, 32, 255, 48, 240, 48, 255);
                        break;

                    case 3:
                        setUV4(poly, 48, 240, 48, 255, 64, 240, 64, 255);
                        break;
                }
                break;

            case 2:
            case 3:
                switch (arg0 & 0x3)
                {
                    case 0:
                        setUV4(poly, 16, 240, 16, 255, 32, 240, 32, 255);
                        break;

                    case 1:
                        setUV4(poly, 32, 240, 32, 255, 48, 240, 48, 255);
                        break;

                    case 2:
                        setUV4(poly, 48, 240, 48, 255, 64, 240, 64, 255);
                        break;

                    case 3:
                        setUV4(poly, 0, 240, 0, 255, 16, 240, 16, 255);
                        break;
                }
                break;

            case 4:
            case 5:
                switch (arg0 & 0x3)
                {
                    case 0:
                        setUV4(poly, 32, 240, 32, 255, 48, 240, 48, 255);
                        break;

                    case 1:
                        setUV4(poly, 48, 240, 48, 255, 64, 240, 64, 255);
                        break;

                    case 2:
                        setUV4(poly, 0, 240, 0, 255, 16, 240, 16, 255);
                        break;

                    case 3:
                        setUV4(poly, 16, 240, 16, 255, 32, 240, 32, 255);
                        break;
                }
                break;

            case 6:
            case 7:
                switch (arg0 & 0x3)
                {
                    case 0:
                        setUV4(poly, 48, 240, 48, 255, 64, 240, 64, 255);
                        break;

                    case 1:
                        setUV4(poly, 0, 240, 0, 255, 16, 240, 16, 255);
                        break;

                    case 2:
                        setUV4(poly, 16, 240, 16, 255, 32, 240, 32, 255);
                        break;

                    case 3:
                        setUV4(poly, 32, 240, 32, 255, 48, 240, 48, 255);
                        break;
                }
                break;
        }
    }

    if (Game_FlashlightIsOn())
    {
        temp_v0 = func_80055D78(g_SysWork.player_4C.chara_0.position_18.vx + arg2->field_0.vx,
                                g_SysWork.player_4C.chara_0.position_18.vy + arg2->field_0.vy,
                                g_SysWork.player_4C.chara_0.position_18.vz + arg2->field_0.vz);

        temp_v0 = (temp_v0 != 0) ? ((temp_v0 >= 0 && temp_v0 <= 176) ? temp_v0 : 176) : 1;

        switch (D_800C39A0)
        {
            case 1:
            case 4:
            case 10:
                poly->r0 = temp_v0 + sharedData_800E3258_0_s00.r;
                poly->g0 = temp_v0 + sharedData_800E3258_0_s00.g;
                poly->b0 = temp_v0 + sharedData_800E3258_0_s00.b;
                break;

            default:
                temp_v0 = func_80055D78(g_SysWork.player_4C.chara_0.position_18.vx + arg2->field_0.vx,
                                        g_SysWork.player_4C.chara_0.position_18.vy + arg2->field_0.vy,
                                        g_SysWork.player_4C.chara_0.position_18.vz + arg2->field_0.vz);
                temp_v0 = (temp_v0 != 0) ? ((temp_v0 >= 0 && temp_v0 <= 176) ? temp_v0 : 176) : 1;

                temp_v0 >>= 3;
                poly->r0  = sharedData_800E3258_0_s00.r + temp_v0;
                poly->g0  = sharedData_800E3258_0_s00.g + temp_v0;
                poly->b0  = sharedData_800E3258_0_s00.b + temp_v0;
                break;

            case 7:
            case 9:
            case 11:
                poly->r0 = sharedData_800E3258_0_s00.r;
                poly->g0 = sharedData_800E3258_0_s00.g;
                poly->b0 = sharedData_800E3258_0_s00.b;
                break;
        }
    }
    else
    {
        switch (D_800C39A0)
        {
            case 1:
            case 4:
            case 10:
                temp_v0 = func_80055D78(g_SysWork.player_4C.chara_0.position_18.vx + arg2->field_0.vx,
                                        g_SysWork.player_4C.chara_0.position_18.vy + arg2->field_0.vy,
                                        g_SysWork.player_4C.chara_0.position_18.vz + arg2->field_0.vz);
                temp_v0 = (temp_v0 != 0) ? ((temp_v0 >= 0 && temp_v0 <= 176) ? temp_v0 : 176) : 1;

                poly->r0 = temp_v0 + sharedData_800E3258_0_s00.r;
                poly->g0 = temp_v0 + sharedData_800E3258_0_s00.g;
                poly->b0 = temp_v0 + sharedData_800E3258_0_s00.b;
                break;

            default:
                poly->r0 = sharedData_800E3258_0_s00.r;
                poly->g0 = sharedData_800E3258_0_s00.g;
                poly->b0 = sharedData_800E3258_0_s00.b;
                break;
        }
    }

    pos.vx = Q12_TO_Q8(arg2->field_0.vx);
    pos.vy = Q12_TO_Q8(arg2->field_0.vy);
    pos.vz = Q12_TO_Q8(arg2->field_0.vz);

    gte_ldv0(&pos);
    gte_rtps();
    gte_stsxy(&poly->x0);
    gte_stszotz(&depth);

    depth = depth >> 1;

    if (depth >= 1 && depth < (ORDERING_TABLE_SIZE / 2) - 1)
    {
        u8 temp_a1;

        if ((depth >> 3) >= 13)
        {
            temp_a1 = 3;
        }
        else
        {
            temp_a1 = 16 - (depth >> 3);
        }

        if (temp_a1 < 0 || temp_a1 >= 3)
        {
            if (temp_a1 > 16)
            {
                temp_a1 = 16;
            }
        }
        else
        {
            temp_a1 = 3;
        }

        poly->x1 = poly->x0;
        poly->x2 = poly->x3 = poly->x0 + temp_a1;
        poly->y2            = poly->y0;
        poly->y1 = poly->y3 = poly->y0 + temp_a1;

        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[depth], poly);

        GsOUT_PACKET_P = poly + 1;
    }
}

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
                setUV4(poly, 64, 240, 64, 255, 80, 240, 80, 255);
                break;

            case 1:
                setUV4(poly, 80, 240, 80, 255, 96, 240, 96, 255);
                break;

            case 2:
                setUV4(poly, 96, 240, 96, 255, 112, 240, 112, 255);
                break;

            case 3:
                setUV4(poly, 112, 240, 112, 255, 128, 240, 128, 255);
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
                        setUV4(poly, 64, 240, 64, 255, 80, 240, 80, 255);
                        break;

                    case 1:
                        setUV4(poly, 80, 240, 80, 255, 96, 240, 96, 255);
                        break;

                    case 2:
                        setUV4(poly, 96, 240, 96, 255, 112, 240, 112, 255);
                        break;

                    case 3:
                        setUV4(poly, 112, 240, 112, 255, 128, 240, 128, 255);
                        break;
                }
                break;

            case 2:
            case 3:
                switch (arg0 & 3)
                {
                    case 0:
                        setUV4(poly, 80, 240, 80, 255, 96, 240, 96, 255);
                        break;

                    case 1:
                        setUV4(poly, 96, 240, 96, 255, 112, 240, 112, 255);
                        break;

                    case 2:
                        setUV4(poly, 112, 240, 112, 255, 128, 240, 128, 255);
                        break;

                    case 3:
                        setUV4(poly, 64, 240, 64, 255, 80, 240, 80, 255);
                        break;
                }
                break;

            case 4:
            case 5:
                switch (arg0 & 3)
                {
                    case 0:
                        setUV4(poly, 96, 240, 96, 255, 112, 240, 112, 255);
                        break;

                    case 1:
                        setUV4(poly, 112, 240, 112, 255, 128, 240, 128, 255);
                        break;

                    case 2:
                        setUV4(poly, 64, 240, 64, 255, 80, 240, 80, 255);
                        break;

                    case 3:
                        setUV4(poly, 80, 240, 80, 255, 96, 240, 96, 255);
                        break;
                }
                break;

            case 6:
            case 7:
                switch (arg0 & 3)
                {
                    case 0:
                        setUV4(poly, 112, 240, 112, 255, 128, 240, 128, 255);
                        break;

                    case 1:
                        setUV4(poly, 64, 240, 64, 255, 80, 240, 80, 255);
                        break;

                    case 2:
                        setUV4(poly, 80, 240, 80, 255, 96, 240, 96, 255);
                        break;

                    case 3:
                        setUV4(poly, 96, 240, 96, 255, 112, 240, 112, 255);
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

    if (depth > 32 && depth < (ORDERING_TABLE_SIZE / 2) - 1)
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

        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[depth], poly);

        GsOUT_PACKET_P = (PACKET*)&poly[1];
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

bool func_800D012C(VECTOR3* pos, s_func_800CC8FC* unused0, s32* unused1) // 0x800D012C
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
                    curUnk->field_C.vx = 0;
                    curUnk->field_C.vz = 0;
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

#include "maps/shared/sharedFunc_800D3308_0_s00.h" // 0x800D3308

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D3B44

#include "maps/shared/sharedFunc_800D3EF4_0_s00.h" // 0x800D3EF4

void sharedFunc_800D4924_0_s00(s_SubCharacter* chara) {}

#include "maps/shared/sharedFunc_800D492C_0_s00.h" // 0x800D492C

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D63D0

#include "maps/shared/sharedFunc_800D54A8_0_s00.h" // 0x800D54A8

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D5B48

#include "maps/shared/sharedFunc_800D5C64_0_s00.h" // 0x800D5C64

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D5FCC

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D63D0

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D654C

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6554

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D670C

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D67FC

#include "maps/shared/sharedFunc_800D6970_0_s00.h" // 0x800D6970

#include "maps/shared/sharedFunc_800D70C4_0_s00.h" // 0x800D70C4

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D7BE8

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D7E04

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
    D_800DD594 = 1;
    D_800DD593 = 1;
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
    g_SysWork.coord_22F8.flg = false;

    func_80049B6C(&g_SysWork.coord_22F8, &sp10, &sp30);
    gte_SetRotMatrix(&sp30);
    gte_SetTransMatrix(&sp30);

    if (D_800DD593 != 0)
    {
        for (i = 0; i < D_800E39AC; i++, curArg0++)
        {
            func_800CE02C(i, func_800D012C(&curArg0->field_0, &sp50, temp_s4), curArg0, mapId);
        }

    }

    if (D_800DD594 != 0)
    {
        for (i = 0; i < D_800E34EC; i++, curArg1++)
        {
            func_800CD8E8(i, (s32)(Rng_Rand16() % 65) >> 6, curArg1);
        }
    }

    return false;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC8FC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD1F4);

INCLUDE_RODATA("asm/maps/map0_s00/nonmatchings/map0_s00", D_800CA7CC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD8E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE02C);

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

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800CEB24_0_s00); // 0x800CEB24

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800CEFF4_0_s00); // 0x800CEFF4

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF2A4

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800CEFD0_1_s02); // 0x800CF974

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CFFF8

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800D0124

bool func_800D012C(VECTOR3* pos, MATRIX* unused0, s32* unused1) // 0x800D012C
{
    s32 deltaX;
    s32 deltaZ;

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

bool func_800D0600() // 0x800D0600
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

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800D08B8

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800D0A60

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800D0B18

#include "maps/shared/sharedFunc_800D0CB8_0_s00.h" // 0x800D0CB8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800D0E04

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800D0E24

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800D0E2C

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800D0E34

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800D1C38

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D209C

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D20D8

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D20E4

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D2244

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D23EC);

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D2C7C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D2D2C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D2D44

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D2D6C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D2D84

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D2DAC

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D2E50

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D2E60

void func_800D2E6C() {}

void func_800D2E74() {}

void func_800D2E7C() {}

void func_800D2E84() {}

void func_800D2E8C() {}

s32 func_800D2E94() // 0x800D2E94
{
    return 0;
}

void func_800D2E9C() {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D2EA4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D2EB4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D2EF4

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

#include "maps/shared/sharedFunc_800D5C64_0_s00.h"

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

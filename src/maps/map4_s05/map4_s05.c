#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/floatstinger.h"
#include "maps/characters/player.h"
#include "maps/map4/map4_s05.h"

INCLUDE_RODATA("maps/map4_s05/nonmatchings/map4_s05", D_800C9578);

INCLUDE_RODATA("maps/map4_s05/nonmatchings/map4_s05", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB0A4_4_s03.h" // 0x800CACA4

#include "maps/shared/sharedFunc_800CB1B0_4_s03.h" // 0x800CADB0

#include "maps/shared/sharedFunc_800CBE54_4_s03.h" // 0x800CBA54

#include "maps/shared/sharedFunc_800CC004_4_s03.h" // 0x800CBC04

#include "maps/shared/sharedFunc_800CE5D4_1_s03.h" // 0x800CC300

#include "maps/shared/sharedFunc_800CE688_1_s03.h" // 0x800CC3B4

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

void Ai_Floatstinger_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D16FC
{
    D_800DB928 = coords;

    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_Floatstinger_Init(chara);
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_800D1968(chara);
        func_800D1B98(chara);
        func_800D35F0(chara);
    }

    func_800D37E8(chara, anmHdr);
    func_800D3AD4(chara);

    chara->properties_E4.dummy.properties_E8[1].val16[0] = chara->rotation_24.vy;
}

void Ai_Floatstinger_Init(s_SubCharacter* floatstinger) // 0x800D1790
{
    s32 i;

    floatstinger->properties_E4.dummy.properties_E8[0].val16[0] = 0;
    floatstinger->model_0.anim_4.alpha_A = Q12(0.0f);

    // Set health.
    floatstinger->health_B0 = Q12(4000.0f);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        floatstinger->health_B0 = Q12(6000.0f);
    }
    else
    {
        
    }

    floatstinger->moveSpeed_38 = Q12(0.0f);
    floatstinger->field_34     = 0;
    floatstinger->field_E1_0   = 4;

    for (i = 0; i < 16; i++)
    {
        floatstinger->properties_E4.dummy.properties_E8[i].val32 = 0;
    }

    switch (floatstinger->model_0.stateStep_3)
    {
        case 3:
            floatstinger->model_0.controlState_2 = 5;
            Character_AnimSet(floatstinger, ANIM_STATUS(FloatstingerAnim_9, true), 191);

            floatstinger->properties_E4.dummy.properties_E8[7].val16[1] = -0x90; // Could be `FP_ANGLE(-12.7f)`?
            break;

        case 4:
            floatstinger->position_18.vx = Q12(-114.5f);
            floatstinger->position_18.vy = Q12(2.0f);
            floatstinger->position_18.vz = Q12(108.0f);

            floatstinger->model_0.controlState_2 = 2;
            Character_AnimSet(floatstinger, ANIM_STATUS(FloatstingerAnim_9, true), 191);
            floatstinger->rotation_24.vy = FP_ANGLE(-90.0f);
            break;
    }

    floatstinger->model_0.stateStep_3 = 0;

    ModelAnim_AnimInfoSet(&floatstinger->model_0.anim_4, FLOATSTINGER_ANIM_INFOS);

    Chara_DamageClear(floatstinger);

    D_800DB89C = 0;
    D_800DB898 = 0;

    floatstinger->headingAngle_3C = floatstinger->rotation_24.vy;

    for (i = 0; i < 15; i++)
    {
        D_800DB8A8[i] = 0;
    }

    floatstinger->properties_E4.dummy.properties_E8[1].val16[0] = floatstinger->rotation_24.vy;
    floatstinger->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;

    D_800D7858 = 0;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        D_800D785C = Q12(2.4f);
        floatstinger->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 0;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        D_800D785C = Q12(4.0f);
    }
    else
    {
        D_800D785C = Q12(3.2f);
    }
}

void func_800D1968(s_SubCharacter* arg0) // 0x800D1968
{
    VECTOR3 sp10;
    u8      sp20;
    s32     var_a1;
    s32     var_v0;

    arg0->properties_E4.floatstinger.field_108 = MAX(arg0->properties_E4.floatstinger.field_108 -
                                                         Q12_MULT_PRECISE(g_DeltaTime0, 0x96000),
                                                     0);

    if (arg0->damage_B4.amount_C > 0)
    {
        if (g_SavegamePtr->gameDifficulty_260 == -1)
        {
            var_a1 = 0x1F4000;
        }
        else
        {
            var_a1 = 0x12C000;
        }

        arg0->properties_E4.floatstinger.field_108 += arg0->damage_B4.amount_C;

        if (var_a1 < arg0->properties_E4.floatstinger.field_108)
        {
            arg0->damage_B4.amount_C                  -= arg0->properties_E4.floatstinger.field_108 - var_a1;
            arg0->properties_E4.floatstinger.field_108 = var_a1;

            if (arg0->damage_B4.amount_C < 0)
            {
                arg0->damage_B4.amount_C = 0;
            }
        }

        Player_DisableDamage(&sp20, 0U);

        var_v0 = arg0->health_B0 - arg0->damage_B4.amount_C;

        if (sp20 != 0)
        {
            if (var_v0 <= 0)
            {
                var_v0 = 1;
            }
        }
        else if (var_v0 < 0)
        {
            var_v0 = 0;
        }
        arg0->health_B0 = var_v0;

        arg0->properties_E4.floatstinger.field_F8 += (arg0->damage_B4.amount_C >> 0xC);
        arg0->properties_E4.floatstinger.field_FA += (arg0->damage_B4.amount_C >> 0xC);

        func_8005DC1C(0x622, &sp10, 0x80, 0);

        if (arg0->health_B0 == 0 || (arg0->properties_E4.floatstinger.field_F8 > 0x3E8 || arg0->properties_E4.floatstinger.field_FA > 0x4B0) &&
                                        arg0->model_0.controlState_2 == 2 && arg0->model_0.anim_4.status_0 == 0x13)
        {
            arg0->properties_E4.floatstinger.field_F8 = 0;
            arg0->model_0.controlState_2              = 3;

            if (arg0->properties_E4.floatstinger.field_FA > 0x4B0)
            {
                arg0->properties_E4.floatstinger.field_FA  = 0;
                arg0->properties_E4.floatstinger.field_E8 |= 2;
            }
        }
    }

    if (arg0->properties_E4.floatstinger.field_FA > 0x4B0 && arg0->model_0.controlState_2 == 2 &&
        arg0->model_0.anim_4.status_0 == 0x13)
    {
        arg0->properties_E4.floatstinger.field_F8  = 0;
        arg0->properties_E4.floatstinger.field_FA  = 0;
        arg0->model_0.controlState_2               = 3;
        arg0->properties_E4.floatstinger.field_E8 |= 2;
    }

    arg0->damage_B4.amount_C      = 0;
    arg0->damage_B4.position_0.vz = 0;
    arg0->damage_B4.position_0.vy = 0;
    arg0->damage_B4.position_0.vx = 0;

    Player_DisableDamage(&sp20, arg0->health_B0 == 0);
}

void func_800D1B98(s_SubCharacter* arg0) // 0x800D1B98
{
    if (arg0->model_0.anim_4.status_0 != 3)
    {
        arg0->field_44.field_0                     = 0;
        arg0->properties_E4.floatstinger.field_E8 &= 0xFFFB;
    }

    if (D_800D7A04[arg0->model_0.controlState_2] != NULL)
    {
        D_800D7A04[arg0->model_0.controlState_2]();
    }
}

void func_800D1BF8(s_SubCharacter* arg0) // 0x800D1BF8
{
    typedef struct
    {
        MATRIX field_0;
        VECTOR field_20[2];
    } s_func_800D1BF8;

    VECTOR3          sp20[3];
    VECTOR3          sp48;
    VECTOR3          sp58;
    VECTOR3          sp68;
    s16              temp_v0_4;
    s32              temp_v0_14;
    s32              var_v1;
    s32              temp_v1_2;
    s32              temp_v1_12;
    s32              temp_a0;
    s32              temp_a1;
    s32              temp_a2;
    s32              temp_a2_2;
    s32              temp_s0_3;
    s32              temp_s0_4;
    s16              temp_s1;
    s32              temp_s3_2;
    s32              i;
    s32              var_s5;
    s_func_800D1BF8* ptr;
    s16              temp_s2_2;
    s32              temp2;
    s32              temp;
    s16              temp3;

    if (g_SysWork.playerWork_4C.player_0.position_18.vx > -0x78000 && g_SysWork.playerWork_4C.player_0.position_18.vx < -0x73000 &&
        (g_SysWork.playerWork_4C.player_0.position_18.vz > 0x60000 && g_SysWork.playerWork_4C.player_0.position_18.vz < 0x67000))
    {
        var_s5     = 0;
        temp_v0_14 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx + 0x75800,
                                         g_SysWork.playerWork_4C.player_0.position_18.vz - 0x64000);

        temp_s2_2 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx + 0x75800,
                           g_SysWork.playerWork_4C.player_0.position_18.vz - 0x64000);

        temp_a0 = Math_Sin(temp_s2_2);

        sp58.vx = arg0->model_0.anim_4.status_0 == 3 ? Q12_MULT(temp_v0_14 + 0x999, temp_a0) - 0x75800 : Q12_MULT(temp_v0_14 + 0x1333, temp_a0) - 0x75800;

        sp58.vy = -0x1000;

        temp_a0 = Math_Cos(temp_s2_2);

        sp58.vz = arg0->model_0.anim_4.status_0 == 3 ? Q12_MULT(temp_v0_14 + 0x999, temp_a0) + 0x64000 : Q12_MULT(temp_v0_14 + 0x1333, temp_a0) + 0x64000;
    }
    else if (g_SysWork.playerWork_4C.player_0.position_18.vx > -0x79000 && g_SysWork.playerWork_4C.player_0.position_18.vx < -0x78000 &&
             (g_SysWork.playerWork_4C.player_0.position_18.vz > 0x60000 && g_SysWork.playerWork_4C.player_0.position_18.vz < 0x67000))
    {
        var_s5  = 1;
        sp58.vx = g_SysWork.playerWork_4C.player_0.position_18.vx - 0x2800;
        sp58.vz = g_SysWork.playerWork_4C.player_0.position_18.vz;
        sp58.vy = g_SysWork.playerWork_4C.player_0.position_18.vy + 0xCCC;
    }
    else
    {
        var_s5    = 2;
        temp_s2_2 = ratan2(arg0->position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx,
                           arg0->position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz);

        temp_a0 = Math_Sin(temp_s2_2);
        temp_a1 = g_SysWork.playerWork_4C.player_0.position_18.vx;

        sp48.vx = arg0->model_0.anim_4.status_0 == 3 ? temp_a1 + Q12_MULT(temp_a0 * 39, 0x3F) : temp_a1 + Q12_MULT(temp_a0, 0x1333);

        sp48.vy = 0x2000;

        temp2   = Math_Cos(temp_s2_2);
        temp_a2 = g_SysWork.playerWork_4C.player_0.position_18.vz;

        sp48.vz = arg0->model_0.anim_4.status_0 == 3 ? temp_a2 + Q12_MULT(temp2 * 39, 0x3F) : temp_a2 + Q12_MULT(temp2, 0x1333);

        func_800D4458(arg0, &sp48, temp_a2);

        sp58.vx = sp48.vx + D_800DB898;
        sp58.vy = sp48.vy;
        sp58.vz = sp48.vz + D_800DB89C;
    }

    temp_a2_2 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - sp58.vx,
                       g_SysWork.playerWork_4C.player_0.position_18.vz - sp58.vz);

    if (arg0->model_0.anim_4.status_0 == 0x13)
    {
        func_800D4A3C(arg0, &sp58, temp_a2_2);

        arg0->properties_E4.floatstinger.field_100 -= g_DeltaTime0;

        if (arg0->properties_E4.floatstinger.field_100 < 0)
        {
            arg0->properties_E4.floatstinger.field_100 = 0;
        }

        if (arg0->properties_E4.floatstinger.field_E8 & 8)
        {
            temp_v1_2 = arg0->properties_E4.floatstinger.field_FC;

            arg0->properties_E4.floatstinger.field_FC = MAX(0, temp_v1_2 - g_DeltaTime0);

            if (!(arg0->properties_E4.floatstinger.field_FC & 0xFFFF))
            {
                arg0->properties_E4.floatstinger.field_E8 &= 0xFFF7;
            }
        }

        temp_s2_2 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx,
                           g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);

        if (ABS(g_SysWork.playerWork_4C.player_0.position_18.vy - arg0->position_18.vy) < 0xCC &&
            Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) < 0x1800 &&
            ((var_s5 == 0 && Rng_TestProbabilityBits(2)) || (var_s5 == 2 && Rng_TestProbabilityBits(2))))
        {
            if (g_SysWork.playerWork_4C.player_0.health_B0 > 0 && ABS(func_8005BF38(temp_s2_2 - arg0->headingAngle_3C)) < 0x400 &&
                ABS(func_8005BF38(temp_s2_2 - arg0->rotation_24.vy)) < 0x155 && !(g_SysWork.playerWork_4C.player_0.flags_3E & 8) && !Rng_TestProbabilityBits(3))
            {
                arg0->model_0.anim_4.status_0              = 2;
                arg0->properties_E4.floatstinger.field_E8 &= 0xFFEF;
            }
        }
        else if (!(arg0->properties_E4.floatstinger.field_E8 & 8) &&
                 Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx,
                                     g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) < 0x6800)
        {
            if (ABS(func_8005BF38(temp_s2_2 - arg0->headingAngle_3C)) < 0x400 &&
                ABS(func_8005BF38(temp_s2_2 - arg0->rotation_24.vy)) < 0xAA)
            {
                var_v1 = ABS(arg0->position_18.vy);

                if (var_v1 < 0x8000 && !(g_SysWork.playerWork_4C.player_0.flags_3E & 8) && !Rng_TestProbabilityBits(2))
                {
                    arg0->model_0.anim_4.status_0 = 0x18;
                }
            }
        }
    }
    else if (arg0->model_0.anim_4.status_0 == 3)
    {
        if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0 && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x12)
        {
            func_800D4A3C(arg0, &sp58, temp_a2_2);
            arg0->properties_E4.floatstinger.field_104 = 0;
        }
        else if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0x11 && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x19)
        {
            arg0->moveSpeed_38 = 0;
            if (!(arg0->properties_E4.floatstinger.field_E8 & 4))
            {
                arg0->field_44.field_0++;
                arg0->properties_E4.floatstinger.field_E8 |= 4;
            }

            for (i = 0; i < 2; i++)
            {
                ptr = PSX_SCRATCH;

                Vw_CoordHierarchyMatrixCompute(&D_800DB928[5], &ptr->field_0);
                gte_SetRotMatrix(&ptr->field_0);
                gte_SetTransMatrix(&ptr->field_0);
                gte_ldv0(&D_800D7A20[i]);
                gte_rt();
                gte_stlvnl(&ptr->field_20[i]);

                sp20[i].vx = (ptr->field_20[i].vx * 0x10);
                sp20[i].vy = (ptr->field_20[i].vy * 0x10);
                sp20[i].vz = (ptr->field_20[i].vz * 0x10);
            }

            if (arg0->properties_E4.floatstinger.field_104 == 0)
            {
                sp68.vx = arg0->position_18.vx;
                sp68.vy = arg0->position_18.vy - 0x1000;
                sp68.vz = arg0->position_18.vz;

                func_8005DC1C(0x623, &sp68, 0x80, 0);
                arg0->properties_E4.floatstinger.field_104++;
            }

            func_8008A0E4(1, 0x3B, arg0, &sp20[0], &g_SysWork.playerWork_4C.player_0, ratan2(sp20[1].vx - sp20[0].vx, sp20[1].vz - sp20[0].vz),
                          ratan2(Math_Vector2MagCalc(sp20[1].vx - sp20[0].vx, sp20[1].vz - sp20[0].vz), sp20[1].vy - sp20[0].vy));

            if (g_SavegamePtr->gameDifficulty_260 != 1 && arg0->properties_E4.floatstinger.field_100 == 0)
            {
                arg0->properties_E4.floatstinger.field_E8 &= 0xFFFE;
            }
        }
    }
    else if (arg0->model_0.anim_4.status_0 == 0x19)
    {
        if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0 && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x12)
        {
            func_800D4A3C(arg0, &sp58, temp_a2_2);
        }
        else
        {
            arg0->moveSpeed_38 = 0;

            if (!(arg0->properties_E4.floatstinger.field_E8 & 8))
            {
                ptr = PSX_SCRATCH;
                Vw_CoordHierarchyMatrixCompute(&D_800DB928[9], &ptr->field_0);
                gte_SetRotMatrix(&ptr->field_0);
                gte_SetTransMatrix(&ptr->field_0);
                gte_ldv0(&D_800D7A30);
                gte_rt();
                gte_stlvnl(&ptr->field_20[0]);

                sp20[0].vx = ptr->field_20[0].vx * 0x10;
                sp20[0].vy = ptr->field_20[0].vy * 0x10;
                sp20[0].vz = ptr->field_20[0].vz * 0x10;

                temp_s1 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - D_800DB8C8[7].vx,
                                 g_SysWork.playerWork_4C.player_0.position_18.vz - D_800DB8C8[7].vz);

                temp_s0_3 = SquareRoot0(SQUARE((D_800DB8C8[7].vx - g_SysWork.playerWork_4C.player_0.position_18.vx) >> 6) +
                                        SQUARE((D_800DB8C8[7].vz - g_SysWork.playerWork_4C.player_0.position_18.vz) >> 6));

                temp       = Rng_TestProbabilityBits(12) + 0x1000;
                temp_s0_3  = temp_s0_3 << 6;
                temp_v0_14 = Q12_MULT_PRECISE(temp_s0_3, temp);

                sp20[1].vx = g_SysWork.playerWork_4C.player_0.position_18.vx + g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 +
                             Q12_MULT(temp_v0_14, Math_Sin(temp_s1));
                sp20[1].vz = g_SysWork.playerWork_4C.player_0.position_18.vz + g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 +
                             Q12_MULT(temp_v0_14, Math_Cos(temp_s1));

                temp_v0_4 = Q12_MULT_PRECISE(g_SysWork.playerWork_4C.player_0.position_18.vy - D_800DB8C8[7].vy, Rng_TestProbabilityBits(12) + 0x1000);

                temp_a2_2 = g_SysWork.playerWork_4C.player_0.field_C8.field_6;

                sp20[1].vy = MAX(g_SysWork.playerWork_4C.player_0.position_18.vy + temp_v0_4, -0x1000) <= 0x2000 ? temp_a2_2 + MAX(g_SysWork.playerWork_4C.player_0.position_18.vy + temp_v0_4, -0x1000) : temp_a2_2 + 0x2000;

                sp68.vx = arg0->position_18.vx;
                sp68.vy = arg0->position_18.vy - 0x3800;
                sp68.vz = arg0->position_18.vz;

                func_8005DC1C(0x624, &sp68, 0x80, 0);
                sharedFunc_800CB0A4_4_s03(&sp20[0], &sp20[1]);

                if (arg0->properties_E4.floatstinger.field_E8 & 1)
                {
                    for (i = 0; i < 2; i++)
                    {
                        temp_s3_2 = Rng_TestProbabilityBits(11);
                        temp_s2_2 = Rng_TestProbabilityBits(12);
                        temp_s0_4 = Math_Sin(temp_s2_2);

                        sp20[2].vx = sp20[1].vx + Q12_MULT(temp_s3_2, temp_s0_4) +
                                     Math_Sin(arg0->rotation_24.vy + (i != 0 ? 0x400 : -0x400));

                        temp_a0   = temp_s2_2;
                        temp_s0_4 = Math_Cos(temp_a0);

                        sp20[2].vz = sp20[1].vz + Q12_MULT(temp_s3_2, temp_s0_4) +
                                     Math_Cos(arg0->rotation_24.vy + (i != 0 ? 0x400 : -0x400));

                        temp3      = Rng_TestProbabilityBits(11) - 0x400;
                        temp_v1_12 = sp20[1].vy + temp3;

                        temp2 = g_SysWork.playerWork_4C.player_0.field_C8.field_6;

                        sp20[2].vy = g_SysWork.playerWork_4C.player_0.field_C8.field_6 <
                                             MAX(temp_v1_12, temp2 - 0x3000)
                                         ? g_SysWork.playerWork_4C.player_0.field_C8.field_6
                                         : MAX(temp_v1_12, g_SysWork.playerWork_4C.player_0.field_C8.field_6 - 0x3000);

                        sharedFunc_800CB0A4_4_s03(&sp20[0], &sp20[2]);
                    }
                }

                arg0->properties_E4.floatstinger.field_FC  = Q12_MULT_PRECISE(D_800D785C, Rng_TestProbabilityBits(10) + 0xC00);
                arg0->properties_E4.floatstinger.field_E8 |= 8;

                if (g_SavegamePtr->gameDifficulty_260 != 1 && arg0->properties_E4.floatstinger.field_100 == 0)
                {
                    arg0->properties_E4.floatstinger.field_E8 &= 0xFFFE;
                }
            }
        }
    }

    for (i = 6; i >= 0; i--)
    {
        D_800DB8C8[i + 1].vx = D_800DB8C8[i].vx;
        D_800DB8C8[i + 1].vy = D_800DB8C8[i].vy;
        D_800DB8C8[i + 1].vz = D_800DB8C8[i].vz;
    }

    D_800DB8C8[0].vx = g_SysWork.playerWork_4C.player_0.position_18.vx;
    D_800DB8C8[0].vy = g_SysWork.playerWork_4C.player_0.position_18.vy;
    D_800DB8C8[0].vz = g_SysWork.playerWork_4C.player_0.position_18.vz;
}

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D2B90);

void func_800D341C(void) {}

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D3424);

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D3564);

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D35F0);

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D37E8);

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D3AD4);

void func_800D3F84(VECTOR3* arg0, s32 arg1, s32 arg2) // 0x800D3F84
{
    VECTOR  sp10;
    MATRIX  sp20;
    SVECTOR sp40;
    VECTOR  sp48;
    s32     sp58;
    TILE*   tile;
    s16     colR;
    s16     colRG;

    sp10.vx = Q12(FP_FROM(g_SysWork.playerWork_4C.player_0.position_18.vx, Q12_SHIFT));
    sp10.vy = Q12(FP_FROM(g_SysWork.playerWork_4C.player_0.position_18.vy, Q12_SHIFT));
    sp10.vz = Q12(FP_FROM(g_SysWork.playerWork_4C.player_0.position_18.vz, Q12_SHIFT));

    func_80049C2C(&sp20, sp10.vx, sp10.vy, sp10.vz);

    gte_SetRotMatrix(&sp20);
    gte_SetTransMatrix(&sp20);
    gte_ReadGeomScreen(&sp58);

    tile = GsOUT_PACKET_P;

    Math_SetSVectorFastSum(&sp40, Q12_TO_Q8(arg0->vx - sp10.vx), Q12_TO_Q8(arg0->vy - sp10.vy), Q12_TO_Q8(arg0->vz - sp10.vz));
    gte_ldv0(&sp40);
    gte_rt();
    gte_stlvnl(&sp48);

    if (sp48.vz >= sp58)
    {
        s32 x = (sp48.vx * sp58) / sp48.vz;
        s32 y = (sp48.vy * sp58) / sp48.vz;
        setXY0(tile, x, y);

        // `setTile(tile)` in reverse order?
        setcode(tile, 0x60);
        setlen(tile, 3);

        setSemiTrans(tile, false);

        setRGB0Fast(tile, (arg1 & 4) ? 0xC4 : 0, (arg1 & 2) ? 0xC4 : 0, (arg1 & 1) ? 0xC4 : 0);

        tile->w = arg2;
        tile->h = arg2;

        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[12], tile);
        tile++;
        GsOUT_PACKET_P = tile;
    }
}

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D41F0);

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D4458);

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D48A4);

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D4A3C);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D5AFC

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D5B0C

#include "maps/shared/Map_RoomBgmInit_4_s02.h" // 0x800D5D08

void func_800D5FDC(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D5FE4

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D607C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D6110

void func_800D61A4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E ",
    "\tThe_stairs_are_wrecked! ~E ",
    "~C3\tAlchemilla_Hospital ~E "
};

INCLUDE_RODATA("maps/map4_s05/nonmatchings/map4_s05", D_800CABE4);

INCLUDE_ASM("maps/map4_s05/nonmatchings/map4_s05", func_800D61AC);

void func_800D6800(void) // 0x800D6800
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            g_SysWork.field_30 = 20;

            MAP_POINTS[14].positionX_0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
            MAP_POINTS[14].positionZ_8 = g_SysWork.playerWork_4C.player_0.position_18.vz;
            // TODO: Likely wrong union field.
            MAP_POINTS[14].data.spawnInfo.flags_6 = ((u32)func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy) + Q12(1.0f)) >> 4;

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 52, false);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-118.22f), Q12(1.46f), Q12(105.67f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-119.97f), Q12(-1.4f), Q12(107.85f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_8005E70C();

            D_800D7D80 = Q12(0.0f);
            D_800D7D82 = 0;

            SysWork_StateStepIncrement(0);

        case 3:
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-120.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(2.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(104.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = 0;

            // Warp NPC.
            g_SysWork.npcs_1A0[0].position_18.vx = Q12(-120.0f);
            g_SysWork.npcs_1A0[0].position_18.vy = Q12(2.0f);
            g_SysWork.npcs_1A0[0].position_18.vz = Q12(108.0f);
            g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(180.0f);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_351);
            SysWork_StateStepIncrementAfterFade(0, true, 1, Q12(0.2f), false);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        default:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_352);
            break;
    }

    if (D_800D7D80 == 0)
    {
        SD_Call(Sfx_Unk1522);
        D_800D7D82++;
    }

    D_800D7D80 = MIN(D_800D7D80 + ((g_DeltaTime0 * 2) / 3), Q12(1.0f));
    Sd_SfxAttributesUpdate(Sfx_Unk1522, 0, -(D_800D7D80 >> 4) & 0xFF, 0);

    if (D_800D7D80 == Q12(1.0f) && D_800D7D82 >= 0 && D_800D7D82 < 3)
    {
        D_800D7D80 = 0;
    }
}

void func_800D6BC0(void) // 0x800D6BC0
{
    s32    pitch;
    s32    tmp0;
    s32    tmp1;
    q19_12 cos0;
    q19_12 sin0;

    tmp0  = D_800D7D6C;
    tmp1  = tmp0 >> 1;
    sin0  = Math_Sin(tmp1);
    cos0  = Math_Cos(tmp0 >> 4);
    pitch = ((sin0 * 2) + cos0 + Math_Cos(Math_Cos(tmp1))) >> 9;

    D_800D7D6C += g_DeltaTime0;

    if (g_SysWork.sysStateStep_C[0] >= 10)
    {
        D_800D7D70 -= Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.5f));
        if (D_800D7D70 < 0)
        {
            D_800D7D70 = 0;
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800D7D70 >> 4), pitch);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800D7D70 += Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.25f));
        if (D_800D7D70 > Q12(0.9961f))
        {
            D_800D7D70 = Q12(0.9961f);
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800D7D70 >> 4), pitch);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800D7D94 = 0;

            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800D7D64);
            Fs_QueueStartRead(FILE_ANIM_UFO2_DMS, FS_BUFFER_19);

            D_800DB954 = NO_VALUE;
            ScreenFade_ResetTimestep();

            SD_Call(Sfx_Unk1467);
            Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, Q8_CLAMPED(1.0f), 0);

            D_800D7D70 = 0;
            D_800D7D6C = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            D_800DB954 = 0;

            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            DmsHeader_FixOffsets(FS_BUFFER_19);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();

            D_800D7D88.vx = Q12(155.0f);
            D_800D7D88.vy = Q12(-16.0f);
            D_800D7D88.vz = Q12(28.0f);
            D_800D7D95    = 0;

            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 5:
            Map_MessageWithAudio(15, &D_800D7D94, &D_800D7D74);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800DB954, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false);
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);
            break;

        case 8:
            func_80080B58(&g_SysWork.playerBoneCoords_890[2], &(SVECTOR3){ 0, 0, 0 }, &QVECTOR3(154.31f, -15.5f, 24.07f));
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(1.0f), Q12(0.2f), 1);
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 9:
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);

            g_SysWork.field_28 += g_DeltaTime0;
            if (g_SysWork.field_28 > Q12(1.5f))
            {
                if (D_800D7D95 != 0)
                {
                    D_800D7D88.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12(3.5f));
                    if (D_800D7D88.vy < Q12(-17.5f))
                    {
                        D_800D7D95 = 0;
                    }
                }
                else
                {
                    D_800D7D88.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12(3.5f));
                    if (D_800D7D88.vy > Q12(-14.5f))
                    {
                        D_800D7D95 = 1;
                    }
                }
            }

            if (g_SysWork.field_28 > Q12(0.5f))
            {
                D_800D7D88.vx -= Q12_MULT_PRECISE(g_DeltaTime0, Q12(2.5f));
            }

            if (g_SysWork.field_28 > Q12(6.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            vcReturnPreAutoCamWork(true);

            Savegame_EventFlagSet(EventFlag_457);
            func_80086470(3, InventoryItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            D_800DB954 = NO_VALUE;

            break;
    }

    if (D_800DB954 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800DB954, FS_BUFFER_19);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800DB938, &D_800DB948, NULL, D_800DB954, FS_BUFFER_19));
        vcUserCamTarget(&D_800DB938, NULL, true);
        vcUserWatchTarget(&D_800DB948, NULL, true);
    }
}

void Map_WorldObjectsInit(void) // 0x800D723C
{
    D_800DB9B0 = 0;

    WorldObjectNoRotInit(&g_WorldObject_Kidn04, "KIDN04_H", -119.8019f, 5.0f, 107.861f);

    WorldObjectNoRotInit(&g_WorldObject_Kidn05, "KIDN05_H", -114.89f, 5.0f, 108.36f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        D_800C4418.field_0 = Q12(5.5f);
    }
    else
    {
        D_800C4418.field_0 = Q12(3.75f);
    }

    D_800C4418.field_2 = Q12(0.2f);
    D_800C4418.field_4 = Q12(0.1f);
    D_800C4418.field_6 = Q12(0.45f);
    D_800C4418.field_8 = Q12(6.0f);
    D_800C4418.field_A = Q12(0.55f);
    D_800C4418.field_C = 18;

    if (Savegame_EventFlagGet(EventFlag_349) && !Savegame_EventFlagGet(EventFlag_350))
    {
        func_80088FF4(Chara_Floatstinger, 0, 4);
    }
}

void Map_WorldObjectsUpdate(void) // 0x800D7360
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    func_80069844(0xFFFF);
    
    if (PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (D_800DB9B0 == 0)
        {
            Gfx_MapInitMapEffectsUpdate(6, 12);
            D_800DB9B0++;
        }

        if (Savegame_EventFlagGet(EventFlag_348))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Kidn05.object_0, &g_WorldObject_Kidn05.position_1C, &(SVECTOR3){ FP_ANGLE(0.0f), FP_ANGLE(0.0f), FP_ANGLE(0.0f) });
            func_8006982C(4);
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Kidn04.object_0, &g_WorldObject_Kidn04.position_1C, &(SVECTOR3){ FP_ANGLE(0.0f), FP_ANGLE(0.0f), FP_ANGLE(0.0f) });
            func_8006982C(2);
        }
    }

    else if (PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (Savegame_EventFlagGet(EventFlag_346))
        {
            func_8006982C(4);

            if (g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(212.0f))
            {
                Savegame_EventFlagClear(EventFlag_346);
            }
        } 
        else
        {
            func_8006982C(2);
        }
    }
    else
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 5, -1, 5))
        {
            Savegame_MapMarkingSet(MapMarkFlag_AltCentralTown_KoontzStBigCross);
            Savegame_MapMarkingSet(MapMarkFlag_AltCentralTown_CrichtonKoontzBigCross);
        }

        func_80069844(0xFFFF);
    }
}

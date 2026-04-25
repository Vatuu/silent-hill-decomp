#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/dms.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map4/map4_s05.h"
#include "maps/particle.h"
#include "maps/characters/floatstinger.h"
#include "maps/characters/player.h"

#define floatstingerProps floatstinger->properties.floatstinger

void Ai_Floatstinger_Update(s_SubCharacter* floatstinger, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D16FC
{
    D_800DB928 = coords;

    if (floatstinger->model.controlState == 0)
    {
        Ai_Floatstinger_Init(floatstinger);
    }

    if (g_DeltaTime != Q12(0.0f))
    {
        func_800D1968(floatstinger);
        Ai_Floatstinger_ControlUpdate(floatstinger);
        func_800D35F0(floatstinger);
    }

    func_800D37E8(floatstinger, anmHdr);
    func_800D3AD4(floatstinger);

    floatstinger->properties.dummy.properties_E8[1].val16[0] = floatstinger->rotation.vy;
}

void Ai_Floatstinger_Init(s_SubCharacter* floatstinger) // 0x800D1790
{
    s32 i;

    floatstinger->properties.dummy.properties_E8[0].val16[0] = 0;
    floatstinger->model.anim.alpha = Q12(0.0f);

    // Set health.
    floatstinger->health = Q12(4000.0f);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        floatstinger->health = Q12(6000.0f);
    }
    else
    {
    }

    floatstinger->moveSpeed = Q12(0.0f);
    floatstinger->fallSpeed = Q12(0.0f);
    floatstinger->field_E1_0   = 4;
    Chara_PropertiesClear(floatstinger);

    switch (floatstinger->model.stateStep)
    {
        case 3:
            floatstinger->model.controlState = FloatstingerControl_5;
            Character_AnimSet(floatstinger, ANIM_STATUS(FloatstingerAnim_9, true), 191);

            floatstinger->properties.dummy.properties_E8[7].val16[1] = -0x90; // Could be `Q12_ANGLE(-12.7f)`?
            break;

        case 4:
            floatstinger->position.vx = Q12(-114.5f);
            floatstinger->position.vy = Q12(2.0f);
            floatstinger->position.vz = Q12(108.0f);

            floatstinger->model.controlState = FloatstingerControl_2;
            Character_AnimSet(floatstinger, ANIM_STATUS(FloatstingerAnim_9, true), 191);
            floatstinger->rotation.vy = Q12_ANGLE(-90.0f);
            break;
    }

    floatstinger->model.stateStep = 0;
    ModelAnim_AnimInfoSet(&floatstinger->model.anim, FLOATSTINGER_ANIM_INFOS);
    Chara_DamageClear(floatstinger);

    D_800DB89C = 0;
    D_800DB898 = 0;
    floatstinger->headingAngle = floatstinger->rotation.vy;

    for (i = 0; i < 15; i++)
    {
        D_800DB8A8[i] = 0;
    }

    floatstinger->properties.dummy.properties_E8[1].val16[0] = floatstinger->rotation.vy;
    floatstinger->flags |= CharaFlag_Unk9 | CharaFlag_Unk3;

    D_800D7858 = 0;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        D_800D785C = Q12(2.4f);
        floatstinger->properties.dummy.properties_E8[0].val16[0] |= 1 << 0;
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

void func_800D1968(s_SubCharacter* floatstinger) // 0x800D1968
{
    VECTOR3 sp10;
    u8      sp20;
    s32     var_a1;
    q19_12  newHealth;

    floatstingerProps.field_108 = MAX(floatstingerProps.field_108 -
                                                             Q12_MULT_PRECISE(g_DeltaTime, Q12(150.0f)),
                                                             Q12(0.0f));

    if (floatstinger->damage.amount > Q12(0.0f))
    {
        if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
        {
            var_a1 = Q12(500.0f);
        }
        else
        {
            var_a1 = Q12(300.0f);
        }

        floatstingerProps.field_108 += floatstinger->damage.amount;

        if (var_a1 < floatstingerProps.field_108)
        {
            floatstinger->damage.amount -= floatstingerProps.field_108 - var_a1;
            floatstingerProps.field_108       = var_a1;
            if (floatstinger->damage.amount < Q12(0.0f))
            {
                floatstinger->damage.amount = Q12(0.0f);
            }
        }

        Player_DisableDamage(&sp20, 0u);

        newHealth = floatstinger->health - floatstinger->damage.amount;
        if (sp20 != 0)
        {
            if (newHealth <= Q12(0.0f))
            {
                newHealth = 1;
            }
        }
        else if (newHealth < Q12(0.0f))
        {
            newHealth = Q12(0.0f);
        }
        floatstinger->health = newHealth;

        floatstingerProps.field_F8 += FP_FROM(floatstinger->damage.amount, Q12_SHIFT);
        floatstingerProps.field_FA += FP_FROM(floatstinger->damage.amount, Q12_SHIFT);

        func_8005DC1C(Sfx_Unk1570, &sp10, Q8(0.5f), 0);

        if (floatstinger->health == Q12(0.0f) ||
            ((floatstingerProps.field_F8 > 1000 || floatstingerProps.field_FA > 1200) &&
             floatstinger->model.controlState == FloatstingerControl_2 &&
             floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_9, true)))
        {
            floatstingerProps.field_F8 = 0;
            floatstinger->model.controlState              = FloatstingerControl_3;

            if (floatstingerProps.field_FA > 1200)
            {
                floatstingerProps.field_FA  = 0;
                floatstingerProps.flags_E8 |= FloatstingerFlag_1;
            }
        }
    }

    if (floatstingerProps.field_FA > 1200 && floatstinger->model.controlState == 2 &&
        floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_9, true))
    {
        floatstingerProps.field_F8  = 0;
        floatstingerProps.field_FA  = 0;
        floatstinger->model.controlState               = FloatstingerControl_3;
        floatstingerProps.flags_E8 |= FloatstingerFlag_1;
    }

    Chara_DamageClear(floatstinger);

    Player_DisableDamage(&sp20, floatstinger->health == Q12(0.0f));
}

void Ai_Floatstinger_ControlUpdate(s_SubCharacter* floatstinger) // 0x800D1B98
{
    if (floatstinger->model.anim.status != ANIM_STATUS(FloatstingerAnim_1, true))
    {
        floatstinger->field_44.field_0                     = 0;
        floatstingerProps.flags_E8 &= ~FloatstingerFlag_2;
    }

    // Handle control state.
    if (D_800D7A04[floatstinger->model.controlState] != NULL)
    {
        D_800D7A04[floatstinger->model.controlState]();
    }
}

void func_800D1BF8(s_SubCharacter* floatstinger) // 0x800D1BF8
{
    typedef struct
    {
        MATRIX field_0;
        VECTOR field_20[2]; // Q23.8
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
    q19_12           sinCosAngle;
    s32              temp_a1;
    s32              temp_a2;
    s32              temp_a2_2;
    s32              temp_s0_3;
    s32              temp_s0_4;
    s16              temp_s1;
    s32              temp_s3_2;
    s32              i;
    s32              var_s5;
    q3_12            angle;
    s32              temp2;
    s32              temp;
    s16              temp3;
    s_func_800D1BF8* ptr;

    if (g_SysWork.playerWork.player.position.vx > Q12(-120.0f) && g_SysWork.playerWork.player.position.vx < Q12(-115.0f) &&
        (g_SysWork.playerWork.player.position.vz > Q12(96.0f) && g_SysWork.playerWork.player.position.vz < Q12(103.0f)))
    {
        var_s5     = 0;
        temp_v0_14 = Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx + Q12(117.5f),
                                         g_SysWork.playerWork.player.position.vz - Q12(100.0f));

        angle = ratan2(g_SysWork.playerWork.player.position.vx + Q12(117.5f),
                           g_SysWork.playerWork.player.position.vz - Q12(100.0f));

        sinCosAngle = Math_Sin(angle);
        sp58.vx = (floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_1, true)) ? (Q12_MULT(temp_v0_14 + Q12(0.6f), sinCosAngle) - Q12(117.5f)) :
                                                                                    (Q12_MULT(temp_v0_14 + Q12(1.2f), sinCosAngle) - Q12(117.5f));

        sp58.vy = Q12(-1.0f);

        sinCosAngle = Math_Cos(angle);
        sp58.vz = (floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_1, true)) ? (Q12_MULT(temp_v0_14 + Q12(0.6f), sinCosAngle) + Q12(100.0f)) :
                                                                                    (Q12_MULT(temp_v0_14 + Q12(1.2f), sinCosAngle) + Q12(100.0f));
    }
    else if (g_SysWork.playerWork.player.position.vx > Q12(-121.0f) && g_SysWork.playerWork.player.position.vx < Q12(-120.0f) &&
             (g_SysWork.playerWork.player.position.vz > Q12(96.0f) && g_SysWork.playerWork.player.position.vz < Q12(103.0f)))
    {
        var_s5  = 1;
        sp58.vx = g_SysWork.playerWork.player.position.vx - Q12(2.5f);
        sp58.vz = g_SysWork.playerWork.player.position.vz;
        sp58.vy = g_SysWork.playerWork.player.position.vy + Q12(0.8f);
    }
    else
    {
        var_s5    = 2;
        angle = ratan2(floatstinger->position.vx - g_SysWork.playerWork.player.position.vx,
                           floatstinger->position.vz - g_SysWork.playerWork.player.position.vz);

        sinCosAngle = Math_Sin(angle);
        temp_a1 = g_SysWork.playerWork.player.position.vx;

        sp48.vx = (floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_1, true)) ? (temp_a1 + Q12_MULT(sinCosAngle * 39, 0x3F)) :
                                                                                    (temp_a1 + Q12_MULT(sinCosAngle, Q12(1.2f)));

        sp48.vy = Q12(2.0f);

        temp2   = Math_Cos(angle);
        temp_a2 = g_SysWork.playerWork.player.position.vz;

        sp48.vz = (floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_1, true)) ? (temp_a2 + Q12_MULT(temp2 * 39, 0x3F)) :
                                                                                    (temp_a2 + Q12_MULT(temp2, Q12(1.2f)));

        func_800D4458(floatstinger, &sp48);

        sp58.vx = sp48.vx + D_800DB898;
        sp58.vy = sp48.vy;
        sp58.vz = sp48.vz + D_800DB89C;
    }

    temp_a2_2 = ratan2(g_SysWork.playerWork.player.position.vx - sp58.vx,
                       g_SysWork.playerWork.player.position.vz - sp58.vz);

    if (floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_9, true))
    {
        func_800D4A3C(floatstinger, &sp58, temp_a2_2);

        floatstingerProps.field_100 -= g_DeltaTime;
        if (floatstingerProps.field_100 < Q12(0.0f))
        {
            floatstingerProps.field_100 = Q12(0.0f);
        }

        if (floatstingerProps.flags_E8 & FloatstingerFlag_3)
        {
            temp_v1_2 = floatstingerProps.field_FC;

            floatstingerProps.field_FC = MAX(0, temp_v1_2 - g_DeltaTime);

            if (!(floatstingerProps.field_FC & 0xFFFF))
            {
                floatstingerProps.flags_E8 &= ~FloatstingerFlag_3;
            }
        }

        angle = ratan2(g_SysWork.playerWork.player.position.vx - floatstinger->position.vx,
                       g_SysWork.playerWork.player.position.vz - floatstinger->position.vz);

        if (ABS(g_SysWork.playerWork.player.position.vy - floatstinger->position.vy) < Q12(0.05f) &&
            Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx - floatstinger->position.vx,
                                g_SysWork.playerWork.player.position.vz - floatstinger->position.vz) < Q12(1.5f) &&
            ((var_s5 == 0 && Rng_GenerateUInt(0, 3)) || (var_s5 == 2 && Rng_GenerateUInt(0, 3)))) // 1 in 4 chance.
        {
            if (g_SysWork.playerWork.player.health > Q12(0.0f) &&
                ABS(Math_AngleNormalizeSigned(angle - floatstinger->headingAngle)) < Q12_ANGLE(90.0f) &&
                ABS(Math_AngleNormalizeSigned(angle - floatstinger->rotation.vy)) < Q12_ANGLE(30.0f) &&
                !(g_SysWork.playerWork.player.flags & (1 << 3)) &&
                !Rng_GenerateUInt(0, 7)) // 1 in 8 chance.
            {
                floatstinger->model.anim.status              = ANIM_STATUS(FloatstingerAnim_1, false);
                floatstingerProps.flags_E8 &= ~FloatstingerFlag_4;
            }
        }
        else if (!(floatstingerProps.flags_E8 & FloatstingerFlag_3) &&
                 Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx - floatstinger->position.vx,
                                     g_SysWork.playerWork.player.position.vz - floatstinger->position.vz) < Q12(6.5f))
        {
            if (ABS(Math_AngleNormalizeSigned(angle - floatstinger->headingAngle)) < Q12_ANGLE(90.0f) &&
                ABS(Math_AngleNormalizeSigned(angle - floatstinger->rotation.vy)) < Q12_ANGLE(15.0f))
            {
                var_v1 = ABS(floatstinger->position.vy);

                if (var_v1 < Q12(8.0f) && !(g_SysWork.playerWork.player.flags & (1 << 3)) &&
                    !Rng_GenerateUInt(0, 3)) // 1 in 4 chance.
                {
                    floatstinger->model.anim.status = ANIM_STATUS(FloatstingerAnim_12, false);
                }
            }
        }
    }
    else if (floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_1, true))
    {
        if (FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) > 0 &&
            FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) < 18)
        {
            func_800D4A3C(floatstinger, &sp58, temp_a2_2);
            floatstingerProps.field_104 = 0;
        }
        else if (FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) > 17 &&
                 FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) < 25)
        {
            floatstinger->moveSpeed = Q12(0.0f);
            if (!(floatstingerProps.flags_E8 & FloatstingerFlag_2))
            {
                floatstinger->field_44.field_0++;
                floatstingerProps.flags_E8 |= FloatstingerFlag_2;
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

                sp20[i].vx = Q8_TO_Q12(ptr->field_20[i].vx);
                sp20[i].vy = Q8_TO_Q12(ptr->field_20[i].vy);
                sp20[i].vz = Q8_TO_Q12(ptr->field_20[i].vz);
            }

            if (floatstingerProps.field_104 == 0)
            {
                sp68.vx = floatstinger->position.vx;
                sp68.vy = floatstinger->position.vy - Q12(1.0f);
                sp68.vz = floatstinger->position.vz;

                func_8005DC1C(1571, &sp68, Q8(0.5f), 0);
                floatstingerProps.field_104++;
            }

            func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_Unk59, AttackInputType_Tap), floatstinger, &sp20[0], &g_SysWork.playerWork.player, ratan2(sp20[1].vx - sp20[0].vx, sp20[1].vz - sp20[0].vz),
                          ratan2(Math_Vector2MagCalc(sp20[1].vx - sp20[0].vx, sp20[1].vz - sp20[0].vz), sp20[1].vy - sp20[0].vy));

            if (g_SavegamePtr->gameDifficulty_260 != 1 && floatstingerProps.field_100 == 0)
            {
                floatstingerProps.flags_E8 &= ~FloatstingerFlag_0;
            }
        }
    }
    else if (floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_12, true))
    {
        if (FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) > 0 &&
            FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) < 18)
        {
            func_800D4A3C(floatstinger, &sp58, temp_a2_2);
        }
        else
        {
            floatstinger->moveSpeed = Q12(0.0f);

            if (!(floatstingerProps.flags_E8 & FloatstingerFlag_3))
            {
                ptr = PSX_SCRATCH;
                Vw_CoordHierarchyMatrixCompute(&D_800DB928[9], &ptr->field_0);
                gte_SetRotMatrix(&ptr->field_0);
                gte_SetTransMatrix(&ptr->field_0);
                gte_ldv0(&D_800D7A30);
                gte_rt();
                gte_stlvnl(&ptr->field_20[0]);

                sp20[0].vx = Q8_TO_Q12(ptr->field_20[0].vx);
                sp20[0].vy = Q8_TO_Q12(ptr->field_20[0].vy);
                sp20[0].vz = Q8_TO_Q12(ptr->field_20[0].vz);

                temp_s1 = ratan2(g_SysWork.playerWork.player.position.vx - D_800DB8C8[7].vx,
                                 g_SysWork.playerWork.player.position.vz - D_800DB8C8[7].vz);

                temp_s0_3 = SquareRoot0(SQUARE((D_800DB8C8[7].vx - g_SysWork.playerWork.player.position.vx) >> 6) +
                                        SQUARE((D_800DB8C8[7].vz - g_SysWork.playerWork.player.position.vz) >> 6));

                temp       = Rng_GenerateUInt(Q12(1.0f), Q12(2.0f) - 1);
                temp_s0_3  = temp_s0_3 << 6;
                temp_v0_14 = Q12_MULT_PRECISE(temp_s0_3, temp);

                sp20[1].vx = g_SysWork.playerWork.player.position.vx + g_SysWork.playerWork.player.field_D8.offsetX_0 +
                             Q12_MULT(temp_v0_14, Math_Sin(temp_s1));
                sp20[1].vz = g_SysWork.playerWork.player.position.vz + g_SysWork.playerWork.player.field_D8.offsetZ_2 +
                             Q12_MULT(temp_v0_14, Math_Cos(temp_s1));

                temp_v0_4 = Q12_MULT_PRECISE(g_SysWork.playerWork.player.position.vy - D_800DB8C8[7].vy, Rng_GenerateUInt(Q12(1.0f), Q12(2.0f) - 1));

                temp_a2_2 = g_SysWork.playerWork.player.field_C8.field_6;

                sp20[1].vy = MAX(g_SysWork.playerWork.player.position.vy + temp_v0_4, Q12(-1.0f)) <= Q12(2.0f) ? (temp_a2_2 + MAX(g_SysWork.playerWork.player.position.vy + temp_v0_4, Q12(-1.0f))) :
                                                                                                                         (temp_a2_2 + Q12(2.0f));

                sp68.vx = floatstinger->position.vx;
                sp68.vy = floatstinger->position.vy - Q12(3.5f);
                sp68.vz = floatstinger->position.vz;

                func_8005DC1C(Sfx_Unk1572, &sp68, Q8(0.5f), 0);
                sharedFunc_800CB0A4_4_s03(&sp20[0], &sp20[1]);

                if (floatstingerProps.flags_E8 & FloatstingerFlag_0)
                {
                    for (i = 0; i < 2; i++)
                    {
                        temp_s3_2 = Rng_GenerateUInt(0, Q12_ANGLE(180.0f) - 1);
                        angle = Rng_GenerateUInt(0, Q12_ANGLE(360.0f) - 1);
                        temp_s0_4 = Math_Sin(angle);

                        sp20[2].vx = sp20[1].vx + Q12_MULT(temp_s3_2, temp_s0_4) +
                                     Math_Sin(floatstinger->rotation.vy + ((i != 0) ? Q12_ANGLE(90.0f) : Q12_ANGLE(-90.0f)));

                        sinCosAngle   = angle;
                        temp_s0_4 = Math_Cos(sinCosAngle);

                        sp20[2].vz = sp20[1].vz + Q12_MULT(temp_s3_2, temp_s0_4) +
                                     Math_Cos(floatstinger->rotation.vy + ((i != 0) ? Q12_ANGLE(90.0f) : Q12_ANGLE(-90.0f)));

                        temp3      = Rng_GenerateUInt(Q12(-0.25f), Q12(0.25f) - 1);
                        temp_v1_12 = sp20[1].vy + temp3;

                        temp2 = g_SysWork.playerWork.player.field_C8.field_6;

                        sp20[2].vy = g_SysWork.playerWork.player.field_C8.field_6 < MAX(temp_v1_12, temp2 - Q12(3.0f)) ?
                                                                                         g_SysWork.playerWork.player.field_C8.field_6 :
                                                                                         MAX(temp_v1_12, g_SysWork.playerWork.player.field_C8.field_6 - Q12(3.0f));

                        sharedFunc_800CB0A4_4_s03(&sp20[0], &sp20[2]);
                    }
                }

                floatstingerProps.field_FC  = Q12_MULT_PRECISE(D_800D785C, Rng_GenerateUInt(Q12(0.75f), Q12_CLAMPED(1.0f)));
                floatstingerProps.flags_E8 |= FloatstingerFlag_3;

                if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard && floatstingerProps.field_100 == 0)
                {
                    floatstingerProps.flags_E8 &= ~FloatstingerFlag_0;
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

    D_800DB8C8[0].vx = g_SysWork.playerWork.player.position.vx;
    D_800DB8C8[0].vy = g_SysWork.playerWork.player.position.vy;
    D_800DB8C8[0].vz = g_SysWork.playerWork.player.position.vz;
}

void func_800D2B90(s_SubCharacter* floatstinger) // 0x800D2B90
{
    s32    temp_a0_6;
    q19_12 var_a1;
    s32    temp_s0;
    q19_12 temp_v0;
    s32    i;
    s32    temp_v0_7;

    if (floatstinger->health == Q12(0.0f))
    {
        Savegame_EventFlagSet(EventFlag_350);
    }

    D_800D7860 = Q12(13.0f);
    var_a1 = (floatstingerProps.flags_E8 & FloatstingerFlag_1) ? Q12(0.6f) : Q12(0.4f);
    temp_v0 = D_800D7858;

    if (((floatstingerProps.flags_E8 & FloatstingerFlag_1) && (var_a1 + Q12(1.0f)) < temp_v0) ||
        (!(floatstingerProps.flags_E8 & FloatstingerFlag_1) && (var_a1 + Q12(0.7f)) < temp_v0))
    {
        D_800D7858 = 0;
        for (i = 14; i >= 0; i--)
        {
            D_800DB8A8[i] = 0;
        }

        if (floatstingerProps.flags_E8 & FloatstingerFlag_1)
        {
            floatstingerProps.field_100 = Rng_GenerateInt(Q12(24.0f), Q12(40.0f) - 1);
            floatstingerProps.flags_E8 &= ~FloatstingerFlag_1;
            floatstingerProps.flags_E8 |= FloatstingerFlag_0;
        }

        if (floatstinger->health != Q12(0.0f))
        {
            floatstinger->model.controlState = FloatstingerControl_2;
        }
        else
        {
            floatstinger->model.controlState = FloatstingerControl_6;
        }
    }
    else
    {
        D_800D7858 += g_DeltaTime;

        floatstinger->moveSpeed = CLAMP_LOW(floatstinger->moveSpeed - Q12_MULT_PRECISE(g_DeltaTime, (floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12(2.5f) : Q12(1.5f)), Q12(0.0f));

        if (floatstinger->fallSpeed > Q12(0.0f))
        {
            floatstinger->fallSpeed = CLAMP_LOW(floatstinger->fallSpeed - Q12_MULT_PRECISE(g_DeltaTime, (floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12(4.5f) : Q12(1.8f)), Q12(0.0f));
        }
        else
        {
            floatstinger->fallSpeed = MIN(floatstinger->fallSpeed - Q12_MULT_PRECISE(g_DeltaTime, (floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12(-3.0f) : Q12(-0.8f)), Q12(0.0f));
        }

        temp_v0 = D_800D7858;

        if (((floatstingerProps.flags_E8 & FloatstingerFlag_1) && temp_v0 < Q12(0.6f)) ||
            (!(floatstingerProps.flags_E8 & FloatstingerFlag_1) && temp_v0 < Q12(0.4f)))
        {
            for (i = 0; i < (temp_v0 = 15); i++) // @hack
            {
                temp_s0 = D_800D7A38[i] * D_800D7858;
                var_a1  = D_800D7858 << 10;

                D_800DB8A8[i] = (((floatstingerProps.flags_E8 & FloatstingerFlag_1) ? (temp_s0 / 2457) : (temp_s0 / 1638)) +
                                 Q12_MULT(D_800D7A38[i], Q12(1.0f) - Math_Cos((floatstingerProps.flags_E8 & FloatstingerFlag_1) ? (var_a1 / 2457) : (var_a1 / 1638)))) >> 1;
            }
        }
        else
        {
            for (i = 0; i < (temp_v0 = 15); i++) // @hack
            {
                temp_s0 = D_800D7A38[i] * ((floatstingerProps.flags_E8 & FloatstingerFlag_1) ? (D_800D7858 - Q12(0.6f)) : (D_800D7858 - Q12(0.4f)));

                var_a1        = ((floatstingerProps.flags_E8 & FloatstingerFlag_1) ? (D_800D7858 - Q12(0.6f)) : (D_800D7858 - Q12(0.4f))) << 10;
                var_a1        = Q12_MULT(D_800D7A38[i], Q12(1.0f) - Math_Cos((floatstingerProps.flags_E8 & FloatstingerFlag_1) ? (var_a1 / Q12(1.0f)) : (var_a1 / 2867)));
                temp_v0_7     = D_800D7A38[i];
                temp_a0_6     = (((floatstingerProps.flags_E8 & FloatstingerFlag_1) ? (temp_s0 / Q12(1.0f)) : (temp_s0 / 2867)) + var_a1) >> 1;
                D_800DB8A8[i] = temp_v0_7 - temp_a0_6;
            }
        }
    }
}

void func_800D341C(void) {}

void func_800D3424(s_SubCharacter* floatstinger) // 0x800D3424
{
    VECTOR3 sp10;

    switch (floatstinger->model.stateStep)
    {
        case 0:
            if (Savegame_EventFlagGet(EventFlag_349))
            {
                floatstinger->position.vx                       = Q12(-114.5f);
                floatstinger->position.vy                       = Q12(2.0f);
                floatstinger->position.vz                       = Q12(108.0f);
                floatstinger->model.stateStep                  = 4;
                floatstinger->model.controlState               = FloatstingerControl_None;
                floatstingerProps.field_106 = 64;
            }
            else
            {
                floatstinger->position.vx          = Q12(-113.5f);
                floatstinger->position.vy          = Q12(8.0f);
                floatstinger->position.vz          = Q12(108.0f);
                floatstinger->rotation.vy          = Q12_ANGLE(-90.0f);
                floatstinger->model.anim.flags &= ~(1 << 1);
            }
            break;

        case 2:
            floatstinger->model.controlState = FloatstingerControl_None;
            floatstinger->model.stateStep    = 4;

        case 1:
            floatstinger->model.anim.flags |= 1 << 1;
            sp10.vx                       = floatstinger->position.vx;
            sp10.vy                       = Q12(2.0f);
            sp10.vz                       = floatstinger->position.vz;
            func_800D4A3C(floatstinger, &sp10, Q12_ANGLE(-90.0f));
            break;
    }

    floatstingerProps.field_106++;
    if (floatstingerProps.field_106 > 64)
    {
        floatstingerProps.field_106 = 64;
    }
}

void func_800D3564(s_SubCharacter* floatstinger) // 0x800D3564
{
    VECTOR3 sp10;

    D_800D7860                                = Q12(13.0f);
    floatstingerProps.field_EE = 0;
    floatstinger->moveSpeed                        = 0;

    if ((floatstinger->model.anim.status >> 1) != FloatstingerAnim_5 && (s32)g_SavegamePtr->eventFlags_168[10] < 0)
    {
        floatstinger->model.anim.status = ANIM_STATUS(FloatstingerAnim_5, false);
        sp10.vx                       = floatstinger->position.vx;
        sp10.vy                       = floatstinger->position.vy - Q12(3.5f);
        sp10.vz                       = floatstinger->position.vz;

        func_8005DC1C(Sfx_Unk1573, &sp10, Q8(0.5f), 0);
    }
}

void func_800D35F0(s_SubCharacter* floatstinger) // 0x800D35F0
{
    s_CollisionResult sp10;
    VECTOR3    sp30;
    q3_12      headingAngle;
    s32        temp_s0;
    s32        temp_s2;
    s32        temp_s3;
    q19_12     offsetY;

    headingAngle = floatstinger->headingAngle;
    temp_s0 = Q12_MULT_PRECISE(g_DeltaTime, floatstinger->moveSpeed);
    temp_s2 = (temp_s0 <= Q12(-8.0f) || temp_s0 >= Q12(8.0f)) * 4;
    temp_s3 = temp_s2 >> 1;

    sp30.vx = Q12_MULT_PRECISE(temp_s0 >> temp_s3, Math_Sin(headingAngle) >> temp_s3) << temp_s2;
    sp30.vz = Q12_MULT_PRECISE(temp_s0 >> temp_s3, Math_Cos(headingAngle) >> temp_s3) << temp_s2;
    sp30.vy = Q12_MULT_PRECISE(g_DeltaTime, floatstinger->fallSpeed);

    Collision_WallDetect(&sp10, &sp30, floatstinger);

    offsetY = sp10.offset_0.vy;
    floatstinger->position.vx += sp10.offset_0.vx;
    floatstinger->position.vz += sp10.offset_0.vz;

    func_800D4458(floatstinger, &floatstinger->position);

    sp30.vy = Q12(0.0f);
    sp30.vx = D_800DB898;
    sp30.vz = D_800DB89C;

    Collision_WallDetect(&sp10, &sp30, floatstinger);
    floatstinger->position.vx += sp10.offset_0.vx;
    floatstinger->position.vz += sp10.offset_0.vz;

    sp30.vx = floatstinger->position.vx;
    sp30.vy = floatstinger->position.vy + offsetY;
    sp30.vz = floatstinger->position.vz;

    if (!func_800D4458(floatstinger, &sp30))
    {
        floatstinger->position.vy += offsetY;
    }
}

void func_800D37E8(s_SubCharacter* floatstinger, s_AnmHeader* anmHdr) // 0x800D37E8
{
    typedef struct
    {
        MATRIX  field_0;
        SVECTOR field_20;
    } s_func_800D37E8;

    VECTOR3          vec;
    s32              i;
    s_AnimInfo*      anim;
    s_func_800D37E8* ptr;
    q19_12*          time;

    switch (floatstinger->model.anim.status)
    {
        case ANIM_STATUS(FloatstingerAnim_1, true):
            if (FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) > 0 &&
                FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) < 4)
            {
                if (!(floatstingerProps.flags_E8 & FloatstingerFlag_4))
                {
                    vec.vx = floatstinger->position.vx;
                    vec.vy = floatstinger->position.vy - Q12(4.0f);
                    vec.vz = floatstinger->position.vz;

                    func_8005DC1C(Sfx_Unk1569, &vec, 0x20, 0);
                    floatstingerProps.flags_E8 |= FloatstingerFlag_4;
                }
            }
            else
            {
                floatstingerProps.flags_E8 &= ~FloatstingerFlag_4;
            }

            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                FLOATSTINGER_ANIM_INFOS[floatstinger->model.anim.status].duration.constant = Q12(26.0f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
            {
                FLOATSTINGER_ANIM_INFOS[floatstinger->model.anim.status].duration.constant = Q12(38.0f);
            }
            else
            {
                FLOATSTINGER_ANIM_INFOS[floatstinger->model.anim.status].duration.constant = Q12(32.0f);
            }
            break;

        case ANIM_STATUS(FloatstingerAnim_9, true):
            D_800D799C = D_800D7860;

            time = &floatstinger->model.anim.time;

            if ((FP_FROM(*time, Q12_SHIFT) > 190 && FP_FROM(*time, Q12_SHIFT) < 194) ||
                (FP_FROM(*time, Q12_SHIFT) > 206 && FP_FROM(*time, Q12_SHIFT) < 210))
            {
                if (!(floatstingerProps.flags_E8 & FloatstingerFlag_4))
                {
                    if (floatstingerProps.field_106 > 0)
                    {
                        vec.vx = floatstinger->position.vx;
                        vec.vy = floatstinger->position.vy - Q12(4.0f);
                        vec.vz = floatstinger->position.vz;

                        func_8005DC1C(0x620, &vec, floatstingerProps.field_106 >> 1, 0);
                        floatstingerProps.flags_E8 |= FloatstingerFlag_4;
                    }
                }
            }
            else
            {
                floatstingerProps.flags_E8 &= ~FloatstingerFlag_4;
            }
            break;
    }

    Math_MatrixTransform(&floatstinger->position, (SVECTOR*)&floatstinger->rotation, D_800DB928);

    anim = &FLOATSTINGER_ANIM_INFOS[floatstinger->model.anim.status];
    anim->playbackFunc(&floatstinger->model, anmHdr, D_800DB928, anim);

    ptr = PSX_SCRATCH;

    for (i = 0; i < 15; i++)
    {
        if (i < 3)
        {
            Math_SetSVectorFastSum(&ptr->field_20, 0, 0, D_800DB8A8[i]);
        }
        else if (i & 1)
        {
            Math_SetSVectorFastSum(&ptr->field_20, D_800DB8A8[i], 0, 0);
        }
        else
        {
            Math_SetSVectorFastSum(&ptr->field_20, 0, D_800DB8A8[i], 0);
        }

        Math_RotMatrixZxyNegGte(&ptr->field_20, &ptr->field_0);
        MulMatrix(&D_800DB928[D_800D7848[i]].coord, &ptr->field_0);
    }
}

void func_800D3AD4(s_SubCharacter* floatstinger) // 0x800D3AD4
{
    typedef struct
    {
        MATRIX  field_0;
        VECTOR  field_20[3];
        VECTOR3 field_50[3];
    } s_func_800D3AD4;

    s32              i;
    s16              var_v1;
    s_func_800D3AD4* ptr;

    ptr = PSX_SCRATCH;

    for (i = 0; i < 3; i++)
    {
        Vw_CoordHierarchyMatrixCompute(&D_800DB928[D_800D7A58[i]], &ptr->field_0);

        gte_SetRotMatrix(&ptr->field_0);
        gte_SetTransMatrix(&ptr->field_0);
        gte_ldv0(&D_800D7A5C[i]);
        gte_rt();
        gte_stlvnl(&ptr->field_20[i]);

        ptr->field_50[i].vx = Q8_TO_Q12(ptr->field_20[i].vx);
        ptr->field_50[i].vy = Q8_TO_Q12(ptr->field_20[i].vy);
        ptr->field_50[i].vz = Q8_TO_Q12(ptr->field_20[i].vz);
    }

    if ((g_SysWork.playerWork.player.position.vy - Q12(1.35f)) < ptr->field_50[0].vy)
    {
        floatstinger->field_C8.field_0   = ptr->field_50[1].vy - floatstinger->position.vy;
        floatstinger->field_C8.field_4   = ptr->field_50[0].vy - floatstinger->position.vy;
        floatstinger->field_D4.radius_0  = Q12(0.4f);
        floatstinger->field_D4.field_2   = Q12(0.4f);
        floatstinger->field_D8.offsetX_0 = ((ptr->field_50[0].vx + ptr->field_50[1].vx) >> 1) - floatstinger->position.vx;
        floatstinger->field_D8.offsetX_4 = floatstinger->field_D8.offsetX_0;
        floatstinger->field_D8.offsetZ_2 = (ptr->field_50[0].vz + ptr->field_50[1].vz >> 1) - floatstinger->position.vz;
        floatstinger->field_D8.offsetZ_6 = floatstinger->field_D8.offsetZ_2;
    }
    else
    {
        floatstinger->field_C8.field_0   = ptr->field_50[0].vy - floatstinger->position.vy;
        floatstinger->field_C8.field_4   = ptr->field_50[2].vy - floatstinger->position.vy;
        floatstinger->field_D4.radius_0  = Q12(0.5f);
        floatstinger->field_D4.field_2   = Q12(0.5f);
        floatstinger->field_D8.offsetX_0 = ((ptr->field_50[0].vx + ptr->field_50[2].vx) >> 1) - floatstinger->position.vx;
        floatstinger->field_D8.offsetX_4 = floatstinger->field_D8.offsetX_0;
        floatstinger->field_D8.offsetZ_2 = (ptr->field_50[0].vz + ptr->field_50[2].vz >> 1) - floatstinger->position.vz;
        floatstinger->field_D8.offsetZ_6 = floatstinger->field_D8.offsetZ_2;
    }

    if (((ptr->field_50[0].vy + ptr->field_50[1].vy) >> 1) > (g_SysWork.playerWork.player.position.vy - Q12(1.4f)))
    {
        floatstinger->field_C8.field_6 = ((ptr->field_50[0].vy + ptr->field_50[1].vy) >> 1) - floatstinger->position.vy;
    }
    else if (((ptr->field_50[0].vy + ptr->field_50[2].vy) >> 1) < (g_SysWork.playerWork.player.position.vy - Q12(1.4f)))
    {
        floatstinger->field_C8.field_6 = ((ptr->field_50[0].vy + ptr->field_50[2].vy) >> 1) - floatstinger->position.vy;
    }
    else
    {
        var_v1                 = floatstinger->position.vy + Q12(1.4f);
        floatstinger->field_C8.field_6 = g_SysWork.playerWork.player.position.vy - var_v1;
    }

    if (floatstinger->model.anim.status == ANIM_STATUS(FloatstingerAnim_1, true))
    {
        if (FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) > 15 &&
            FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) < 27)
        {
            floatstinger->field_D4.radius_0 = Q12_MULT_PRECISE(floatstinger->field_D4.radius_0, Q12(0.3f));
        }
        else if (FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) > 11 &&
                 FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) < 16)
        {
            floatstinger->field_D4.radius_0 = Q12_MULT_PRECISE(floatstinger->field_D4.radius_0, Q12(1.0f) - Q12_MULT_PRECISE((floatstinger->model.anim.time - Q12(12.0f)) >> 2, Q12(0.7f)));
        }
        else if (FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) > 26 &&
                 FP_FROM(floatstinger->model.anim.time, Q12_SHIFT) < 31)
        {
            floatstinger->field_D4.radius_0 = Q12_MULT_PRECISE(floatstinger->field_D4.radius_0, Q12_MULT_PRECISE((Q12(31.0f) - floatstinger->model.anim.time) >> 2, Q12(0.7f)) + Q12(0.3f));
        }
    }

    if (g_SysWork.playerWork.player.health <= Q12(0.0f))
    {
        floatstinger->field_C8.field_2 = Q12(-2.0f);
    }
    else
    {
        floatstinger->field_C8.field_2 = Q12(-1.46f);
    }
}

void func_800D3F84(VECTOR3* floatstinger, s32 arg1, s32 arg2) // 0x800D3F84
{
    VECTOR  sp10;
    MATRIX  sp20;
    SVECTOR sp40;
    VECTOR  sp48;
    s32     sp58;
    s16     colR;
    s16     colRG;
    TILE*   tile;

    sp10.vx = Q12(FP_FROM(g_SysWork.playerWork.player.position.vx, Q12_SHIFT));
    sp10.vy = Q12(FP_FROM(g_SysWork.playerWork.player.position.vy, Q12_SHIFT));
    sp10.vz = Q12(FP_FROM(g_SysWork.playerWork.player.position.vz, Q12_SHIFT));

    Vw_WorldScreenMatrixAtPositionGet(&sp20, sp10.vx, sp10.vy, sp10.vz);

    gte_SetRotMatrix(&sp20);
    gte_SetTransMatrix(&sp20);
    gte_ReadGeomScreen(&sp58);

    tile = GsOUT_PACKET_P;

    Math_SetSVectorFastSum(&sp40, Q12_TO_Q8(floatstinger->vx - sp10.vx), Q12_TO_Q8(floatstinger->vy - sp10.vy), Q12_TO_Q8(floatstinger->vz - sp10.vz));
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

void func_800D41F0(s_SubCharacter* floatstinger) // 0x800D41F0
{
    s16 temp_v1;
    s16 temp_s0;
    s32 temp_t0;
    s16 temp_v0;
    s32 var_a1;
    s32 var_v0;
    s16 temp_s1;

    temp_s0 = Q12_MULT(floatstinger->moveSpeed, Math_Sin(floatstinger->headingAngle));
    temp_s1 = floatstinger->fallSpeed;
    temp_v0 = Q12_MULT(floatstinger->moveSpeed, Math_Cos(floatstinger->headingAngle));
    temp_v1 = Math_Vector3MagCalc(temp_s0, temp_s1, temp_v0);
    temp_t0 = (Q12_MULT_PRECISE(temp_v1, Q12(15.0f) - temp_v1) >> 1) + Q12(13.0f);

    if (floatstingerProps.field_EE == 0)
    {
        var_v0 = Q12(13.0f);
    }
    else if (floatstingerProps.field_EE >= 0)
    {
        var_v0 = Q12_MULT_PRECISE(floatstingerProps.field_EE, Q12(24.0f)) + Q12(21.0f);
    }
    else
    {
        var_v0 = Q12_MULT_PRECISE(-floatstingerProps.field_EE, Q12(24.0f)) + Q12(21.0f);
    }

    if (var_v0 < temp_t0)
    {
        var_a1 = temp_t0;
    }
    else
    {
        var_a1 = var_v0;
    }

    if (var_a1 < D_800D7860)
    {
        D_800D7860 = CLAMP_HIGH(var_a1, D_800D7860 + Q12_MULT_PRECISE(g_DeltaTime, Q12(6.0f)));
    }
    else
    {
        D_800D7860 = MAX(var_a1, D_800D7860 - Q12_MULT_PRECISE(g_DeltaTime, Q12(6.0f)));
    }
}

bool func_800D4458(s_SubCharacter* floatstinger, VECTOR3* arg1) // 0x800D4458
{
    q19_12 angle0;
    q19_12 angle1;
    q19_12 angle2;
    s32    i;
    s32    var_s0;
    s32    var_s3;
    s32    caseVar;

    var_s3 = 0;
    angle0 = 0;

    D_800DB898 = 0;
    D_800DB89A = 0;
    D_800DB89C = 0;

    for (i = 0; i < 3; i++)
    {
        if (arg1->vy + floatstinger->field_C8.field_2 >= D_800D780C[i].field_10)
        {
            break;
        }
    }

    if (i == 3)
    {
        return false;
    }

    D_800DB89A = D_800D780C[i].field_10 - (arg1->vy + floatstinger->field_C8.field_2);

    if (D_800D780C[i].field_0[0] <= arg1->vx)
    {
        if (D_800D780C[i].field_0[1] < arg1->vx)
        {
            caseVar = 2;
        }
        else
        {
            caseVar = 1;
        }
    }
    else
    {
        caseVar = 0;
    }

    if (D_800D780C[i].field_8[0] <= arg1->vz)
    {
        if (D_800D780C[i].field_8[1] < arg1->vz)
        {
            caseVar += 6;
        }
        else
        {
            caseVar += 3;
        }
    }

    switch (caseVar)
    {
        case 0:
        case 2:
        case 6:
        case 8:
            var_s3 = Math_Vector2MagCalc(arg1->vx - D_800D780C[i].field_0[(caseVar % 6) != 0],
                                         arg1->vz - D_800D780C[i].field_8[caseVar > 2]);

            angle0 = ratan2(arg1->vx - D_800D780C[i].field_0[(caseVar % 6) != 0],
                            arg1->vz - D_800D780C[i].field_8[caseVar > 2]);
            break;

        case 1:
            angle0 = Q12_ANGLE(180.0f);
            var_s3 = D_800D780C[i].field_8[0] - arg1->vz;
            break;

        case 3:
            angle0 = Q12_ANGLE(270.0f);
            var_s3 = D_800D780C[i].field_0[0] - arg1->vx;
            break;

        case 5:
            angle0 = Q12_ANGLE(90.0f);
            var_s3 = arg1->vx - D_800D780C[i].field_0[1];
            break;

        case 7:
            angle0 = Q12_ANGLE(0.0f);
            var_s3 = arg1->vz - D_800D780C[i].field_8[1];
            break;
    }


    angle1 = ABS(Math_AngleNormalizeSigned(angle0 - floatstinger->rotation.vy));
    if ((Q12_ANGLE(90.0f) - angle1) < Q12_ANGLE(0.0f))
    {
        angle2 = Q12_ANGLE(180.0f) - angle1;
    }
    else
    {
        angle2 = angle1;
    }

    if (angle1 > Q12_ANGLE(90.0f))
    {
        var_s0 = ((angle2 << 13) >> 10) + Q12(1.0f);
    }
    else
    {
        var_s0 = ((angle2 << 12) >> 10) + Q12(2.0f);
    }

    if (var_s3 < var_s0)
    {
        D_800DB898 = Q12_MULT(var_s0 - var_s3, Math_Sin(angle0));
        D_800DB89C = Q12_MULT(var_s0 - var_s3, Math_Cos(angle0));
        return true;
    }
    else
    {
        return false;
    }
}

s32 func_800D48A4(s_SubCharacter* floatstinger, s16 arg1, s16 arg2) // 0x800D48A4
{
    s_RayData ray;
    VECTOR3   sp30;
    VECTOR3   sp40;
    s16       var_s1;
    s32       temp_s0;
    s32       temp_s4;
    s32       i;

    temp_s4 = Rng_Rand16() & 0xFF;
    temp_s4 = !(temp_s4 < 0x80);

    sp30.vx = floatstinger->position.vx;
    sp30.vy = floatstinger->position.vy + floatstinger->field_C8.field_2;
    sp30.vz = floatstinger->position.vz;

    for (i = temp_s4; i < (temp_s4 + 8); i++)
    {
        if (i & 1)
        {
            var_s1 = (0x100 << ((i + 1) >> 1)) + (Rng_Rand16() & 0x3F);
        }
        else
        {
            var_s1 = -((0x100 << ((i + 2) >> 1)) + (Rng_Rand16() & 0x3F));
        }

        temp_s0 = var_s1 + arg2;

        sp40.vx = Q12_MULT(arg1, Math_Sin(temp_s0));
        sp40.vy = 0;
        sp40.vz = Q12_MULT(arg1, Math_Cos(temp_s0));

        if (func_8006DA08(&ray, &sp30, &sp40, floatstinger) == false)
        {
            return Math_AngleNormalizeSigned(arg2 + var_s1);
        }
    }

    return arg2;
}

void func_800D4A3C(s_SubCharacter* floatstinger, VECTOR3* pos, q3_12 newRotY) // 0x800D4A3C
{
    VECTOR3 newPos;
    q19_12  dist;
    q3_12   angle1;
    q3_12   rotY;
    q19_12  dist0;
    s16     var_s3;
    s32     temp_t2;
    s32     temp_v0_13;
    s32     temp_v0_14;
    q3_12   unkAngle;
    s16     var_s4;
    s32     var_v0_11;
    s32     var_v1_4;

    dist = Math_Vector2MagCalc(pos->vx - floatstinger->position.vx, pos->vz - floatstinger->position.vz);
    unkAngle = ratan2(pos->vx - floatstinger->position.vx, pos->vz - floatstinger->position.vz);

    if (dist > Q12(6.5f))
    {
        rotY = floatstinger->rotation.vy;
        rotY = unkAngle - rotY;
    }
    else
    {
        rotY = floatstinger->rotation.vy;
        rotY = newRotY - rotY;
    }

    angle1 = Math_AngleNormalizeSigned(rotY);
    if (ABS(angle1) > ((floatstingerProps.flags_E8 & FloatstingerFlag_0) ? ABS(((Q12_MULT_PRECISE(floatstingerProps.field_EE, g_DeltaTime) * 3) >> 4) + 1) : ABS((Q12_MULT_PRECISE(floatstingerProps.field_EE, g_DeltaTime) >> 1) + 1)))
    {
        if (angle1 > Q12_ANGLE(0.0f))
        {
            floatstingerProps.field_EE = CLAMP_HIGH((floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12_ANGLE(135.0f) : Q12_ANGLE(90.0f),
                                                    floatstingerProps.field_EE + ((floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(135.0f)) :
                                                                                                                                      Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f))));
        }
        else
        {
            floatstingerProps.field_EE = MAX((floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12_ANGLE(-135.0f) : Q12_ANGLE(-90.0f),
                                             floatstingerProps.field_EE - ((floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(135.0f)) :
                                                                                                                               Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f))));
        }

        floatstinger->rotation.vy = Math_AngleNormalizeSigned(Q12_MULT_PRECISE(g_DeltaTime, floatstingerProps.field_EE) + floatstinger->rotation.vy);
    }
    else
    {
        floatstinger->rotation.vy                      = newRotY;
        floatstingerProps.field_EE = APPROACH_ALT2(floatstingerProps.field_EE, Q12_ANGLE(0.0f),
                                                   (floatstingerProps.flags_E8 & FloatstingerFlag_0) ? (Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(135.0f)) * 2) :
                                                                                                       (Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f)) * 2));
    }

    if (floatstingerProps.field_F0 == Q12(0.0f) || dist < Q12(4.0f))
    {
        dist0 = MIN(dist, Q12(3.5f));

        newPos.vx = floatstinger->position.vx + Q12_MULT(dist0, Math_Sin(unkAngle));
        newPos.vy = floatstinger->position.vy;
        newPos.vz = floatstinger->position.vz + Q12_MULT(dist0, Math_Cos(unkAngle));

        if (func_800D4458(floatstinger, &newPos))
        {
            if (floatstingerProps.field_10E != Q12(0.0f))
            {
                floatstingerProps.field_F4  = floatstingerProps.field_10C;
                floatstingerProps.field_10E = CLAMP_LOW(floatstingerProps.field_10E - g_DeltaTime, Q12(0.0f));
            }
            else
            {
                floatstingerProps.field_F4  = func_800D48A4(floatstinger, dist0, unkAngle);
                floatstingerProps.field_10C = floatstingerProps.field_F4;
                floatstingerProps.field_10E = Rng_GenerateInt(Q12(0.4f), Q12(1.0f) - 2);
            }
        }
        else
        {
            floatstingerProps.field_F4  = unkAngle;
            floatstingerProps.field_10E = Q12(0.0f);
        }
    }
    else
    {
        floatstingerProps.field_F0 += g_DeltaTime;
        if (floatstingerProps.field_F0 > Q12(0.8f) &&
            !Rng_GenerateUInt(0, 15)) // 1 in 16 chance.
        {
            floatstingerProps.field_F0 = Q12(0.0f);
        }
    }

    var_s4 = Q12_MULT(Math_Sin(floatstingerProps.field_F4),
                      Q12_MULT_PRECISE(g_DeltaTime, (floatstingerProps.flags_E8 & FloatstingerFlag_0 ? Q12(2.5f) : Q12(1.5f))));

    var_s3 = Q12_MULT(Math_Cos(floatstingerProps.field_F4),
                      Q12_MULT_PRECISE(g_DeltaTime, (floatstingerProps.flags_E8 & FloatstingerFlag_0 ? Q12(2.5f) : Q12(1.5f))));

    if ((var_s4 * Math_Sin(floatstinger->headingAngle)) > Q12(0.0f))
    {
        var_s4 += Q12_MULT(floatstinger->moveSpeed, Math_Sin(floatstinger->headingAngle));
    }
    else
    {
        var_v0_11 = Q12_MULT(floatstinger->moveSpeed, Math_Sin(floatstinger->headingAngle));
        var_s4   += (floatstingerProps.flags_E8 & FloatstingerFlag_0) ? (var_v0_11 >> 3) : (var_v0_11 >> 2);
    }

    if ((var_s3 * Math_Cos(floatstinger->headingAngle)) > Q12(0.0f))
    {
        var_s3 += Q12_MULT(floatstinger->moveSpeed, Math_Cos(floatstinger->headingAngle));
    }
    else
    {
        temp_v0_13 = Q12_MULT(floatstinger->moveSpeed, Math_Cos(floatstinger->headingAngle));
        var_s3    += (floatstingerProps.flags_E8 & FloatstingerFlag_0) ? (temp_v0_13 >> 3) : (temp_v0_13 >> 2);
    }

    floatstinger->headingAngle = ratan2(var_s4, var_s3);

    temp_v0_14 = Math_Vector2MagCalc(var_s4, var_s3);

    if (((floatstingerProps.flags_E8 & FloatstingerFlag_0) && temp_v0_14 > Q12(3.5f)) ||
        (!(floatstingerProps.flags_E8 & FloatstingerFlag_0) && temp_v0_14 > Q12(2.0f)))
    {
        var_v1_4 = Math_Vector2MagCalc(var_s4, var_s3);
    }
    else
    {
        if (floatstingerProps.flags_E8 & FloatstingerFlag_0)
        {
            var_v1_4 = Q12(3.5f);
        }
        else
        {
            var_v1_4 = Q12(2.0f);
        }
    }

    floatstinger->moveSpeed = var_v1_4;

    if (dist < Q12(4.0f))
    {
        if (dist < Q12(0.05f))
        {
            floatstinger->moveSpeed    = Q12(0.0f);
            floatstinger->headingAngle = floatstinger->rotation.vy;
            floatstinger->position.vx  = pos->vx;
            floatstinger->position.vz  = pos->vz;
        }
        else
        {
            floatstinger->moveSpeed = (floatstinger->moveSpeed + ((floatstinger->moveSpeed * dist) / Q12(4.0f))) >> 1;

            if (ABS(Math_AngleNormalizeSigned(unkAngle - floatstinger->headingAngle)) > Q12_ANGLE(45.0f))
            {
                floatstinger->moveSpeed = Q12_MULT_PRECISE(floatstinger->moveSpeed, (ABS(Math_AngleNormalizeSigned(unkAngle - floatstinger->headingAngle)) << 1) + Q12_ANGLE(45.0f));
            }
        }
    }

    temp_t2 = pos->vy - floatstinger->position.vy;

    if (temp_t2 < 0)
    {
        if (ABS(temp_t2) > 81)
        {
            floatstinger->fallSpeed = MAX((floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12(-5.0f) : Q12(-1.0f),
                                             floatstinger->fallSpeed + Q12_MULT_PRECISE(g_DeltaTime, floatstingerProps.flags_E8 & 1 ? Q12(-3.0f) : Q12(-0.8f)));

            if (ABS(temp_t2) < Q12(1.0f))
            {
                floatstinger->fallSpeed = floatstinger->fallSpeed + ((floatstinger->fallSpeed * ABS(temp_t2)) / Q12(1.0f)) >> 1;
            }
        }
        else
        {
            floatstinger->fallSpeed   = Q12(0.0f);
            floatstinger->position.vy = pos->vy;
        }
    }
    else
    {
        if (ABS(temp_t2) > 81)
        {
            floatstinger->fallSpeed = CLAMP_HIGH((floatstingerProps.flags_E8 & FloatstingerFlag_0) ? Q12(9.0f) : Q12(3.0f),
                                                    floatstinger->fallSpeed + Q12_MULT_PRECISE(g_DeltaTime, floatstingerProps.flags_E8 & 1 ? 0x4800 : 0x1CCC));

            if (ABS(temp_t2) < Q12(1.0f))
            {
                floatstinger->fallSpeed = floatstinger->fallSpeed + (floatstinger->fallSpeed * ABS(temp_t2) / Q12(1.0f)) >> 1;
            }
        }
        else
        {
            floatstinger->fallSpeed   = Q12(0.0f);
            floatstinger->position.vy = pos->vy;
        }
    }

    func_800D41F0(floatstinger);
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D5AFC

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D5B0C

#include "maps/shared/Map_RoomBgmInit_4_s02.h" // 0x800D5D08

void GameBoot_LoadScreen_StageString(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D5FE4

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D607C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D6110

void func_800D61A4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/map_msg_common.h"
    /* 15 */ "~J0(1.0)\tWhat? ~E ",
    /* 16 */ "~J0(2.5)\tThat_light!? ~E ",
    /* 17 */ "\tThe_stairs_are_wrecked! ~E ",
    /* 18 */ "~C3\tAlchemilla_Hospital ~E "
};

const VECTOR3 D_800CABE4 = { 0xFFF8C800, 0x00002000, 0x0006E800 };

void func_800D61AC(void) // 0x800D61AC
{
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.skip) &&
        g_SysWork.sysStateSteps[0] > 0 && g_SysWork.sysStateSteps[0] < 12)
    {
        // Warp player.
        g_SysWork.playerWork.player.position.vx = Q12(-120.0f);
        g_SysWork.playerWork.player.position.vz = Q12(109.0f);
        g_SysWork.playerWork.player.rotation.vy = Q12(0.25f);

        // Warp NPC.
        g_SysWork.npcs[0].position.vx = Q12(-114.5f);
        g_SysWork.npcs[0].position.vy = Q12(2.0f);
        g_SysWork.npcs[0].position.vz = Q12(108.0f);

        vcReturnPreAutoCamWork(true);
        SysWork_StateStepReset();
        Savegame_EventFlagSet(EventFlag_348);
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            Game_TurnFlashlightOn();

            // Warp player.
            g_SysWork.playerWork.player.position.vy = Q12(4.5f);
            g_SysWork.playerWork.player.position.vx = Q12(-115.5f);
            g_SysWork.playerWork.player.position.vz = Q12(106.65f);
            g_SysWork.playerWork.player.rotation.vy = Q12_ANGLE(0.0f);
            g_SysWork.field_30                              = 20;

            func_800865FC(true, 0, 0, 0, Q12(-115.5f), Q12(110.0f));
            func_800865FC(true, 0, 1, 0, Q12(-115.6f), Q12(110.1f));
            func_800865FC(true, 0, 2, Q12_ANGLE(-90.0f), Q12(-115.8f), Q12(110.5f));
            func_800865FC(true, 0, 3, Q12_ANGLE(-90.0f), Q12(-115.9f), Q12(110.6f));
            func_800865FC(true, 0, 4, Q12_ANGLE(-90.0f), Q12(-116.08f), Q12(110.7f));

            Camera_PositionSet(NULL, Q12(-103.27f), Q12(2.02f), Q12(104.6f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(-107.06f), Q12(2.18f), Q12(105.87f), 0, 0, 0, 0, true);

            SysWork_StateStepIncrement(0);

        case 1:
            func_800866D4(53, 5, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 2:
            func_800866D4(53, 5, false);
            SysWork_StateStepIncrementDelayed(Q12(1.8f), false);
            break;

        case 3:
            Camera_PositionSet(NULL, g_SysWork.playerWork.player.position.vx + Q12(4.0f), Q12(-1.12f), Q12(113.08f), 0, 0, 0, 0, true);
            Camera_LookAtSet(&g_SysWork.playerWork.player.position, 0, Q12(-1.5f), 0, 0, 0, 0, 0, true);
            SysWork_StateStepIncrement(0);

        case 4:
            Camera_PositionSet(NULL, g_SysWork.playerWork.player.position.vx + Q12(4.0f), Q12(-1.12f), Q12(113.08f), 0, 0, 0, 0, true);
            Camera_LookAtSet(&g_SysWork.playerWork.player.position, 0, Q12(-1.5f), 0, 0, 0, 0, 0, false);
            func_800866D4(53, 5, false);
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            func_800865FC(true, 0, 0, Q12_ANGLE(-112.5f), Q12(-120.0f), Q12(109.0f));
            break;

        case 6:
            Camera_PositionSet(NULL, g_SysWork.playerWork.player.position.vx + Q12(4.0f), Q12(-1.12f), Q12(113.08f), 0, 0, 0, 0, true);
            Camera_LookAtSet(&g_SysWork.playerWork.player.position, 0, Q12(-1.5f), 0, 0, 0, 0, 0, false);
            func_800866D4(53, 1, false);
            break;

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 8:
            func_8005DC1C(Sfx_Unk1574, &D_800CABE4, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 9:
            func_80086C58(&g_SysWork.playerWork.player, 109);
            break;

        case 10:
            // Warp player.
            g_SysWork.playerWork.player.rotation.vy = Q12_ANGLE(90.0f);

            // Warp NPC.
            g_SysWork.npcs[0].position.vx      = Q12(-114.5f);
            g_SysWork.npcs[0].position.vy      = Q12(3.0f);
            g_SysWork.npcs[0].position.vz      = Q12(108.0f);
            g_SysWork.npcs[0].model.stateStep = 1;

            Savegame_EventFlagSet(EventFlag_348);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-122.73f), Q12(-0.2f), Q12(112.85f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(-119.67f), Q12(0.23f), Q12(110.31f), 0, 0, 0, 0, true);

            Player_ControlUnfreeze(true);
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);

            Savegame_EventFlagSet(EventFlag_349);
            g_SysWork.npcs[0].model.stateStep = 2;

            func_8003A16C();
            break;
    }
}

void func_800D6800(void) // 0x800D6800
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            g_SysWork.field_30 = 20;

            MAP_POINTS[14].positionX_0 = g_SysWork.playerWork.player.position.vx;
            MAP_POINTS[14].positionZ_8 = g_SysWork.playerWork.player.position.vz;
            // TODO: Likely wrong union field.
            MAP_POINTS[14].triggerParam0_4_16 = ((u32)Math_AngleNormalizeSigned(g_SysWork.playerWork.player.rotation.vy) + Q12(1.0f)) >> 4;

            func_80085EB8(0, &g_SysWork.playerWork.player, 52, false);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-118.22f), Q12(1.46f), Q12(105.67f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-119.97f), Q12(-1.4f), Q12(107.85f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_8005E70C();

            D_800D7D80 = Q12(0.0f);
            D_800D7D82 = 0;

            SysWork_StateStepIncrement(0);

        case 3:
            func_80085EB8(2, &g_SysWork.playerWork.player, 0, false);
            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);

            // Warp player.
            g_SysWork.playerWork.player.position.vx = Q12(-120.0f);
            g_SysWork.playerWork.player.position.vy = Q12(2.0f);
            g_SysWork.playerWork.player.position.vz = Q12(104.0f);
            g_SysWork.playerWork.player.rotation.vy = 0;

            // Warp NPC.
            g_SysWork.npcs[0].position.vx = Q12(-120.0f);
            g_SysWork.npcs[0].position.vy = Q12(2.0f);
            g_SysWork.npcs[0].position.vz = Q12(108.0f);
            g_SysWork.npcs[0].rotation.vy = Q12_ANGLE(180.0f);
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
            func_80085EB8(3, &g_SysWork.playerWork.player, 0, false);

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

    D_800D7D80 = MIN(D_800D7D80 + ((g_DeltaTime * 2) / 3), Q12(1.0f));
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

    D_800D7D6C += g_DeltaTime;

    if (g_SysWork.sysStateSteps[0] >= 10)
    {
        D_800D7D70 -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
        if (D_800D7D70 < 0)
        {
            D_800D7D70 = 0;
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800D7D70 >> 4), pitch);
    }
    else if (g_SysWork.sysStateSteps[0] > 0)
    {
        D_800D7D70 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
        if (D_800D7D70 > Q12(0.9961f))
        {
            D_800D7D70 = Q12(0.9961f);
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800D7D70 >> 4), pitch);
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800D7D94 = 0;

            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800D7D64);
            Fs_QueueStartRead(FILE_ANIM_UFO2_DMS, FS_BUFFER_19);

            g_Cutscene_Timer = NO_VALUE;
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
            if (Fs_QueueChunksLoad())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            g_Cutscene_Timer = Q12(0.0f);

            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            Dms_HeaderFixOffsets(FS_BUFFER_19);
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
            SysWork_StateStepIncrementAfterTime(&g_Cutscene_Timer, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false);
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);
            break;

        case 8:
            func_80080B58(&g_SysWork.playerBoneCoords[HarryBone_Head], &(SVECTOR3){ 0, 0, 0 }, &QVECTOR3(154.31f, -15.5f, 24.07f));
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(1.0f), Q12(0.2f), 1);
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 9:
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);

            g_SysWork.field_28 += g_DeltaTime;
            if (g_SysWork.field_28 > Q12(1.5f))
            {
                if (D_800D7D95 != 0)
                {
                    D_800D7D88.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(3.5f));
                    if (D_800D7D88.vy < Q12(-17.5f))
                    {
                        D_800D7D95 = 0;
                    }
                }
                else
                {
                    D_800D7D88.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(3.5f));
                    if (D_800D7D88.vy > Q12(-14.5f))
                    {
                        D_800D7D95 = 1;
                    }
                }
            }

            if (g_SysWork.field_28 > Q12(0.5f))
            {
                D_800D7D88.vx -= Q12_MULT_PRECISE(g_DeltaTime, Q12(2.5f));
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
            func_80086470(3, InvItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            g_Cutscene_Timer = NO_VALUE;

            break;
    }

    if (g_Cutscene_Timer >= Q12(0.0f))
    {
        Dms_CharacterTransformGet(&g_SysWork.playerWork.player.position, &g_SysWork.playerWork.player.rotation, "HERO", g_Cutscene_Timer, FS_BUFFER_19);
        vcChangeProjectionValue(Dms_CameraTargetGet(&g_Cutscene_CameraPositionTarget, &g_Cutscene_CameraLookAtTarget, NULL, g_Cutscene_Timer, FS_BUFFER_19));
        vcUserCamTarget(&g_Cutscene_CameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_Cutscene_CameraLookAtTarget, NULL, true);
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
        Chara_SpawnFlagsSet(Chara_Floatstinger, 0, SpawnFlag_2);
    }
}

void Map_WorldObjectsUpdate(void) // 0x800D7360
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    func_80069844(CollisionFlag_All);

    if (PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (D_800DB9B0 == 0)
        {
            Gfx_MapInitMapEffectsUpdate(6, 12);
            D_800DB9B0++;
        }

        if (Savegame_EventFlagGet(EventFlag_348))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Kidn05.object_0, &g_WorldObject_Kidn05.position_1C, &(SVECTOR3){ Q12_ANGLE(0.0f), Q12_ANGLE(0.0f), Q12_ANGLE(0.0f) });
            Collision_FlagBitsSet(4);
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Kidn04.object_0, &g_WorldObject_Kidn04.position_1C, &(SVECTOR3){ Q12_ANGLE(0.0f), Q12_ANGLE(0.0f), Q12_ANGLE(0.0f) });
            Collision_FlagBitsSet(2);
        }
    }

    else if (PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (Savegame_EventFlagGet(EventFlag_346))
        {
            Collision_FlagBitsSet(CollisionFlag_2);

            if (g_SysWork.playerWork.player.position.vz < Q12(212.0f))
            {
                Savegame_EventFlagClear(EventFlag_346);
            }
        }
        else
        {
            Collision_FlagBitsSet(CollisionFlag_1);
        }
    }
    else
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 5, -1, 5))
        {
            Savegame_EventFlagSet(EventFlag_MapMark_AltCentralTown_KoontzStBigCross);
            Savegame_EventFlagSet(EventFlag_MapMark_AltCentralTown_CrichtonKoontzBigCross);
        }

        func_80069844(CollisionFlag_All);
    }
}

#undef floatstingerProps

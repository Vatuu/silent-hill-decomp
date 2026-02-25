#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/groaner.h"

#define groanerProps groaner->properties_E4.groaner

void Ai_Groaner_Update(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    u8 prevControlState;

    // Initialize.
    if (groaner->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_Groaner_Init(groaner);
    }

    prevControlState = groaner->model_0.controlState_2;

    if (g_DeltaTime != Q12(0.0f))
    {
        sharedFunc_800E33DC_2_s00(groaner);
        sharedFunc_800E384C_2_s00(groaner);
        sharedFunc_800E5AA4_2_s00(groaner);
    }

    sharedFunc_800E5EC4_2_s00(groaner, anmHdr, coords);

    if (g_DeltaTime != Q12(0.0f))
    {
        sharedFunc_800E6338_2_s00(groaner); // Control func with state machine?
        sharedFunc_800E71E8_2_s00(groaner);

        if (groaner->model_0.controlState_2 != prevControlState)
        {
            groanerProps.flags_E8.val16[0] &= ~GroanerFlag_8;
        }

        if (groanerProps.flags_E8.val16[0] & GroanerFlag_7)
        {
            groaner->flags_3E |= CharaFlag_Unk3;
        }
    }
}

void Ai_Groaner_Init(s_SubCharacter* groaner)
{
    #define HEALTH_BASE      Q12(210.0f)
    #define HEALTH_BONUS_MAX Q12(70.0f)

    s32 i;

    Chara_PropertiesClear(groaner);
    groanerProps.flags_E8.val16[0]  = 0;
    groaner->model_0.anim_4.alpha_A = Q12(0.0f);

    groaner->health_B0 = HEALTH_BASE + (Rng_Rand16() % HEALTH_BONUS_MAX);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal &&
        Rng_GenerateInt(0, 7) == 0) // 1 in 8 chance.
    {
        groaner->health_B0 *= 2;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard &&
        Rng_GenerateInt(0, 3) == 0)// 1 in 4 chance.
    {
        groaner->health_B0 *= 2;
    }

    groaner->moveSpeed_38    = Q12(0.0f);
    groaner->field_E1_0      = 3;
    groaner->headingAngle_3C = groaner->rotation_24.vy;

    groanerProps.field_114 = Rng_GenerateUInt(Q12(0.9375f), Q12(1.0625f) - 1);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        groanerProps.field_114 += (u32)groanerProps.field_114 / 8;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        groanerProps.field_114 -= ((s32)((u16)groanerProps.field_114 << 16) >> 20); // (value * 0x10000) / 0x100000
    }

    ModelAnim_AnimInfoSet(&groaner->model_0.anim_4, GROANER_ANIM_INFOS);
    Chara_DamageClear(groaner);

    if (groaner->model_0.stateStep_3 == GroanerStateStep_3)
    {
        groaner->model_0.controlState_2 = 1;
        Character_AnimSet(groaner, ANIM_STATUS(GroanerAnim_17, true), 371);
        groanerProps.flags_E8.val16[0] |= GroanerFlag_5;
    }

    groaner->model_0.stateStep_3 = GroanerStateStep_0;

    groanerProps.targetPositionX_F4 = groaner->position_18.vx;
    groanerProps.targetPositionZ_F8 = groaner->position_18.vz;

#ifdef MAP2_S00
    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard)
    {
        if (!Savegame_EventFlagGet(EventFlag_134))
        {
            groanerProps.field_114 = Q12_MULT_FLOAT_PRECISE(groanerProps.field_114, 0.8f);
        }
        else
        {
            groanerProps.field_114 = Q12_MULT_FLOAT_PRECISE(groanerProps.field_114, 0.9f);
        }
    }
#endif

    #undef HEALTH_BASE
    #undef HEALTH_BONUS_MAX
}

void sharedFunc_800E33DC_2_s00(s_SubCharacter* groaner)
{
    s_Collision coll;
    q3_12       newHeadingAngle;
    q3_12       unkAngle;
    q19_12      unkDist;
    s32         temp_v0;
    s32         prevControlState;

    if (groaner->health_B0 > Q12(0.0f))
    {
        Collision_Get(&coll, groaner->position_18.vx, groaner->position_18.vz);

        if (coll.field_8 == 12 && Rng_GenerateInt(Q12(4.0f), Q12(7.0f) - 1) < groaner->position_18.vy)
        {
            groaner->damage_B4.amount_C = Q12(1000.0f);
        }
    }

    if (groaner->damage_B4.amount_C == Q12(0.0f))
    {
        return;
    }

    if (groaner->health_B0 < Q12(0.0f))
    {
        return;
    }

    prevControlState = groaner->model_0.controlState_2;

    if (groaner->health_B0 > Q12(0.0f))
    {
        groanerProps.field_10F = 4;
    }

    groanerProps.targetPositionX_F4     = g_SysWork.playerWork_4C.player_0.position_18.vx;
    groanerProps.targetPositionZ_F8     = g_SysWork.playerWork_4C.player_0.position_18.vz;
    groanerProps.flags_E8.val16[0]     |= GroanerFlag_7;

    groaner->health_B0 = MAX(groaner->health_B0 - groaner->damage_B4.amount_C, Q12(0.0f));
    unkDist         = Math_Vector2MagCalc(groaner->damage_B4.position_0.vx, groaner->damage_B4.position_0.vz);

    // Set new heading angle.
    if (groaner->damage_B4.position_0.vx != Q12(0.0f) ||
        groaner->damage_B4.position_0.vz != Q12(0.0f))
    {
        newHeadingAngle = ratan2(groaner->damage_B4.position_0.vx, groaner->damage_B4.position_0.vz);
    }
    else
    {
        newHeadingAngle = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    }

    unkAngle = func_8005BF38((newHeadingAngle - groaner->rotation_24.vy) + Q12_ANGLE(180.0f));

    // TODO: Unsure if `field_FE` is an angle.
    groanerProps.field_FE = CLAMP_LOW(unkDist >> 2, Q12_ANGLE(90.0f));

    temp_v0 = FP_TO(groaner->damage_B4.position_0.vy, Q12_SHIFT);

    groaner->headingAngle_3C = newHeadingAngle;

    Chara_DamageClear(groaner);

    groanerProps.flags_E8.val16[0] |= GroanerFlag_1;
    groaner->moveSpeed_38           = FP_TO(unkDist, Q12_SHIFT) / Q12(1.2f);
    groaner->fallSpeed_34          += temp_v0 / Q12(1.2f);

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_3)
    {
        groanerProps.field_FE = 0;

        if (groaner->health_B0 != Q12(0.0f))
        {
            if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == ANIM_STATUS(GroanerAnim_2, false))
            {
                if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_4, true))
                {
                    groanerProps.relKeyframeIdx_100 = 0;
                }
                else
                {
                    groanerProps.relKeyframeIdx_100 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 78;
                }

                groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_21, false);
            }
            else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_8)
            {
                if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_8, true))
                {
                    groanerProps.relKeyframeIdx_100 = 0;
                }
                else
                {
                    groanerProps.relKeyframeIdx_100 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 165;
                }

                groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_22, false);
            }
            else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_14)
            {
                if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_14, true))
                {
                    groanerProps.relKeyframeIdx_100 = 0;
                }
                else
                {
                    groanerProps.relKeyframeIdx_100 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 319;
                }

                groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_23, false);
            }
        }
    }
    else if (groaner->health_B0 > Q12(100.0f))
    {
        if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_10))
        {
            if (ABS(unkAngle) < Q12_ANGLE(45.0f))
            {
                if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_2)
                {
                    groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_2, false);
                }
            }
            else
            {
                if (unkAngle > Q12_ANGLE(0.0f))
                {
                    if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_6)
                    {
                        groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_6, false);
                    }
                }
                else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_12)
                {
                    groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_12, false);
                }
            }

            groaner->model_0.controlState_2 = GroanerControl_5;
        }
    }
    else
    {
        Savegame_EnemyStateUpdate(groaner);

        groaner->flags_3E                                      |= CharaFlag_Unk2;
        groanerProps.flags_E8.val16[0]                         |= GroanerFlag_3 | GroanerFlag_12;

        if (ABS(unkAngle) < Q12_ANGLE(45.0f))
        {
            groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_3, false);
            groaner->model_0.controlState_2  = GroanerControl_6;
        }
        else if (unkAngle > Q12_ANGLE(0.0f))
        {
            groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_7, false);
            groaner->model_0.controlState_2  = GroanerControl_7;
        }
        else
        {
            groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_13, false);
            groaner->model_0.controlState_2  = GroanerControl_8;
        }
    }

    if (prevControlState != groaner->model_0.controlState_2 && prevControlState == GroanerControl_3)
    {
        g_SysWork.field_2284[3] &= ~(1 << 1);
    }
}

typedef struct
{
    s32 field_0;
    s32 field_4;
} s_800EEE3C;

extern s_800EEE3C sharedData_800EEE3C_2_s00[];

#if defined(MAP2_S00)
    #define UNK_VAL Q12(0.6f)
#else
    #define UNK_VAL Q12(1.0f)
#endif

void sharedFunc_800E384C_2_s00(s_SubCharacter* groaner)
{
    extern void (*sharedData_800EEE14_2_s00[])(s_SubCharacter* chara);

    #define getIndex() \
        ((((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 3) == 0) * 2) + ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) == 2))

    if (func_80070360(groaner, Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
            g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz), UNK_VAL) != 0 ||
        func_8006FD90(groaner, 1, sharedData_800EEE3C_2_s00[getIndex()].field_0, sharedData_800EEE3C_2_s00[getIndex()].field_4))
    {
        groanerProps.flags_E8.val16[0] |= GroanerFlag_7;

        if (groanerProps.flags_E8.val16[0] & GroanerFlag_5)
        {
            groanerProps.targetPositionX_F4 = g_SysWork.playerWork_4C.player_0.position_18.vx;
            groanerProps.targetPositionZ_F8 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        }
    }
    else
    {
        groanerProps.flags_E8.val16[0] &= ~GroanerFlag_7;
    }

    if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_10, true))
    {
        groaner->field_44.field_0 = 0;
    }

    sharedData_800EEE14_2_s00[groaner->model_0.controlState_2](groaner);
}

void sharedFunc_800E39D8_2_s00(s_SubCharacter* groaner)
{
    q3_12  unkAngleDelta;
    q19_12 targetPosX;
    q19_12 targetPosZ;
    q19_12 unkRand;
    q19_12 randTargetPosX;
    q19_12 posX;
    q19_12 posZ;

    Chara_MoveSpeedUpdate4(groaner, Q12(6.0f), Q12_MULT_PRECISE(groanerProps.field_114, Q12(0.5f)));

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_0)
    {
        unkAngleDelta = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);
        if (TIMESTEP_ANGLE(3, 2) < ABS(unkAngleDelta))
        {
            if (unkAngleDelta > Q12_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(60.0f));
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(60.0f));
            }
        }
        else
        {
            groaner->rotation_24.vy = groanerProps.angle_FC;
            groanerProps.flags_E8.val16[0] &= ~GroanerFlag_0;
        }
    }
    else
    {
        if (func_8007029C(groaner, Q12_ANGLE(306.0f), groaner->rotation_24.vy))
        {
            groanerProps.angle_FC = func_8006F99C(groaner, Q12_ANGLE(306.0f), groaner->rotation_24.vy);
            if (groanerProps.angle_FC == Q12_ANGLE(360.0f))
            {
                groanerProps.angle_FC = -groaner->rotation_24.vy;
            }

            groanerProps.flags_E8.val16[0] |= GroanerFlag_0;
        }
        else
        {
            unkRand = Rng_GenerateInt(Q12(2.0f), Q12(6.0f) - 1);

            posX       = groaner->position_18.vx;
            targetPosX = groanerProps.targetPositionX_F4;
            posZ       = groaner->position_18.vz;
            targetPosZ = groanerProps.targetPositionZ_F8;

            // TODO: Demangle condition.
            if (unkRand < (((posX - targetPosX) > (posZ - targetPosZ)) ? ABS(posX - targetPosX) + ABS((posZ - targetPosZ) >> 1) :
                                                                         ABS((posX - targetPosX) >> 1) + ABS(posZ - targetPosZ)))
            {
                // TODO: Cleaner random angle generation.
                if (ABS(func_8005BF38(groaner->rotation_24.vy - ratan2(groaner->position_18.vx - groanerProps.targetPositionX_F4,
                                                                       groaner->position_18.vz - groanerProps.targetPositionZ_F8))) < (Rng_GenerateUInt(Q12_ANGLE(45.0f), Q12_ANGLE(50.7f) - 1)))
                {
                    randTargetPosX        = groanerProps.targetPositionX_F4 + Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1);
                    groanerProps.angle_FC = Chara_HeadingAngleGet(groaner, Q12_ANGLE(306.0f),
                                                                  randTargetPosX, groanerProps.targetPositionZ_F8 + Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1),
                                                                  Q12_ANGLE(360.0f), true);
                    if (groanerProps.angle_FC == Q12_ANGLE(360.0f))
                    {
                        groanerProps.angle_FC = -groaner->rotation_24.vy;
                    }

                    groanerProps.flags_E8.val16[0] |= GroanerFlag_0;
                }
            }
        }
    }

    if (groaner->model_0.anim_4.status_0 == ANIM_STATUS(GroanerAnim_17, true) &&
        (groanerProps.flags_E8.val32 & (GroanerFlag_5 | GroanerFlag_7)) == (GroanerFlag_5 | GroanerFlag_7))
    {
        groaner->model_0.controlState_2 = GroanerControl_2;
        groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_16, false);
        groanerProps.flags_E8.val16[0] &= ~GroanerFlag_0;
        groanerProps.flags_E8.val16[0] |= GroanerFlag_10;
    }
}

void sharedFunc_800E3E94_2_s00(s_SubCharacter* groaner)
{
    s16           temp_v0_10;
    q3_12         angle0;
    q3_12         angleDeltaToTarget;
    q19_12        headingAngle;
    s32           temp_s2;
    s32           temp_s4;
    q19_12        distToPlayer;
    bool          temp_s6;
    bool          cond;
    s32           var_a1;
    s32           i;
    q19_12        distToPlayerMax;

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_1)
    {
        return;
    }

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_8)
    {
        groanerProps.timer_104          = Q12(0.0f);
        groanerProps.flags_E8.val16[0] |= GroanerFlag_8;
    }

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);
    distToPlayerMax = Rng_GenerateInt(Q12(4.0f), Q12(8.0f) - 1);
    temp_s6 = func_800700F8(groaner, &g_SysWork.playerWork_4C.player_0);

    if (distToPlayer < distToPlayerMax && !temp_s6)
    {
        groanerProps.angle_FC = Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18);
    }
    else
    {
        temp_s2 = Q12(0.9f) - Rng_GenerateInt(0, 920);
        temp_s4 = func_8007029C(groaner, temp_s2, groaner->rotation_24.vy);

        if ((groanerProps.timer_104 >= Q12(0.0f) && ((temp_s4 != 0 && (temp_s6 || distToPlayer < temp_s2)) ||
             groanerProps.timer_104 == Q12(0.0f))) ||
            !Rng_GenerateUInt(0, 31))
        {
            if (temp_s4 != 0)
            {
                var_a1 = temp_s2 + Rng_GenerateInt(0, (temp_s2 >> 2) - 1);
            }
            else
            {
                var_a1 = Rng_GenerateInt(Q12(1.5f), Q12(1.875f) - 1);
            }

            headingAngle = Chara_HeadingAngleGet(groaner, var_a1, groanerProps.targetPositionX_F4, groanerProps.targetPositionZ_F8,
                                                 Q12_ANGLE(360.0f), true);
            if (headingAngle == Q12_ANGLE(360.0f))
            {
                headingAngle = func_8006F99C(groaner, (temp_s2 * 3) >> 2, groaner->rotation_24.vy);
            }

            if (temp_s4 != 0)
            {
                groanerProps.timer_104 = -(Rng_GenerateInt(Q12(0.375f), Q12(0.75f) - 1));
            }
            else
            {
                groanerProps.timer_104 = Rng_GenerateInt(Q12(0.375f), Q12(1.5f) - 1);
            }

            groanerProps.angle_FC = headingAngle;
        }
    }

    if (groanerProps.timer_104 > Q12(0.0f))
    {
        groanerProps.timer_104 -= g_DeltaTime;
        if (groanerProps.timer_104 < Q12(0.0f))
        {
            groanerProps.timer_104 = Q12(0.0f);
        }
    }
    else
    {
        groanerProps.timer_104 += g_DeltaTime;
        if (groanerProps.timer_104 > Q12(0.0f))
        {
            groanerProps.timer_104 = Q12(0.0f);
        }
    }

    for (i = 0; i < 3; i++)
    {
        angle0 = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);

        if (((g_DeltaTime >> 3) + 1) < ABS(angle0))
        {
            if (angle0 > Q12_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
        }
        else
        {
            groaner->rotation_24.vy = groanerProps.angle_FC;
        }
    }

    angleDeltaToTarget = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);
    if (angleDeltaToTarget < Q12_ANGLE(20.0f))
    {
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)));
    }
    else
    {
        temp_v0_10 = Q12(1.0f) - (((angleDeltaToTarget - Q12_ANGLE(20.0f)) * 3) >> 1);
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)), temp_v0_10));
    }

    if (distToPlayer > Q12(3.0f))
    {
        cond = false;
    }
    else if (distToPlayer < Q12(1.5f))
    {
        cond = true;
    }
    else
    {
        cond = Rng_TestProbabilityBits(12) > (FP_TO(distToPlayer, Q12_SHIFT) / Q12(3.0f)) >> 2;
    }

    if (cond && !temp_s6)
    {
        if (!Chara_HasFlag(&g_SysWork.playerWork_4C.player_0, CharaFlag_Unk4) &&
            !(g_SysWork.field_2284[3] & 2) &&
            g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f) &&
            g_SysWork.sysState_8 == 0 &&
            (groaner->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy) > Q12(-0.8f))
        {
            if (groaner->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy < Q12(0.8f))
            {
                if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz) -
                                      groaner->rotation_24.vy)) < Q12_ANGLE(30.0f))
                {
                    g_SysWork.field_2284[3]      |= 2;
                    groaner->model_0.controlState_2  = GroanerControl_3;
                    groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_15, false);
                    return;
                }
            }
        }
    }

    if (distToPlayer < Q12(1.2f))
    {
        if (Chara_HasFlag(&g_SysWork.playerWork_4C.player_0, CharaFlag_Unk4) ||
            (g_SysWork.field_2284[3] & 2) ||
            g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f) ||
            g_SysWork.sysState_8 != 0 ||
            !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
        {
            groaner->model_0.controlState_2 = GroanerControl_4;
            return;
        }
    }

    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_7) &&
        (distToPlayer > Q12(12.0f) || (!Rng_GenerateUInt(0, 127) && distToPlayer > Q12(6.0f))))
    {
        groaner->model_0.controlState_2                         = GroanerControl_1;
        groaner->model_0.anim_4.status_0                        = ANIM_STATUS(GroanerAnim_17, false);
        groanerProps.relKeyframeIdx_100  = 100;
        groanerProps.flags_E8.val16[0] &= ~GroanerFlag_10;
    }
}

void sharedFunc_800E4830_2_s00(s_SubCharacter* groaner)
{
    VECTOR3 sp20;
    q3_12   angleDeltaToPlayer0;
    q3_12   angleDeltaToPlayer1;
    s32     temp_a2;
    q19_12  distToPlayer;
    q19_12  deltaX;
    q19_12  deltaZ;
    q19_12  deltaY;
    s32     temp_v1;
    q19_12  rotMax;
    s32     var_v0;
    s32     temp1;
    s32     temp2;

    // TODO: Use macro.
    deltaX       = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx);
    deltaZ       = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);
    distToPlayer = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    angleDeltaToPlayer0 = func_8005BF38(Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                        groaner->rotation_24.vy);

    if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_15 ||
        ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model_0.anim_4.time_4, 214) < 9u)
    {
        temp_v1 = TIMESTEP_ANGLE(1, 3);

        if ((angleDeltaToPlayer0 >= Q12_ANGLE(0.0f) && temp_v1 <  angleDeltaToPlayer0) ||
            (angleDeltaToPlayer0 <  Q12_ANGLE(0.0f) && temp_v1 < -angleDeltaToPlayer0))
        {
            if (angleDeltaToPlayer0 > Q12_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
            }

            angleDeltaToPlayer1 = func_8005BF38(Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                                groaner->rotation_24.vy);

            rotMax = TIMESTEP_ANGLE(1, 3);
            if ((angleDeltaToPlayer1 >= Q12_ANGLE(0.0f) && rotMax <  angleDeltaToPlayer1) ||
                (angleDeltaToPlayer1 <  Q12_ANGLE(0.0f) && rotMax < -angleDeltaToPlayer1))
            {
                if (angleDeltaToPlayer1 > Q12_ANGLE(0.0f))
                {
                    groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
                }
                else
                {
                    groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
                }
            }
            else
            {
                groaner->rotation_24.vy = Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18);
            }
        }
        else
        {
            groaner->rotation_24.vy = Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
        groaner->headingAngle_3C = groaner->rotation_24.vy;
    }
    else
    {
        // TODO: Convert 771. Maybe some fraction?
        temp1 = groaner->rotation_24.vy + Q12(0.125f);
        temp2 = groaner->headingAngle_3C + Q12_MULT_PRECISE(g_DeltaTime, 771);

        if (temp2 < temp1)
        {
            groaner->headingAngle_3C += Q12_MULT_PRECISE(g_DeltaTime, 771);
        }
        else
        {
            groaner->headingAngle_3C = groaner->rotation_24.vy + Q12(0.125f);
        }
    }

    if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_15)
    {
        Chara_MoveSpeedUpdate3(groaner, Q12(9.5f), Q12(0.0f));
    }
    else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_10)
    {
        if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_9))
        {
            groanerProps.flags_E8.val16[0]                         |= GroanerFlag_9;
            var_v0                                                = g_SysWork.playerWork_4C.player_0.field_D4.field_2 + 573;
            var_v0                                                = (distToPlayer - var_v0) << 1;
            groaner->moveSpeed_38                                   = MIN(var_v0, Q12(4.5f));

            deltaY                                           = g_SysWork.playerWork_4C.player_0.position_18.vy - groaner->position_18.vy;
            groaner->field_44.field_0                             = 1;
            groanerProps.field_10F                                = 2;
            groaner->fallSpeed_34                                 = Q12_MULT_PRECISE(deltaY - Q12(1.4f), Q12(2.35f));
        }
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model_0.anim_4.time_4, 222)) < 2u)
    {
        sp20.vx = groaner->position_18.vx + groaner->field_D8.offsetX_4;
        sp20.vy = groaner->position_18.vy - Q12(0.8f);
        sp20.vz = groaner->position_18.vz + groaner->field_D8.offsetZ_6;
        func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Hold), groaner, &sp20, &g_SysWork.playerWork_4C.player_0, groaner->rotation_24.vy, Q12_ANGLE(90.0f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model_0.anim_4.time_4, 222)) < 14u)
    {
        groaner->fallSpeed_34 += g_GravitySpeed;

        Chara_MoveSpeedUpdate3(groaner, Q12(0.3f), Q12(0.0f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model_0.anim_4.time_4, 236)) < 7u)
    {
        Chara_MoveSpeedUpdate3(groaner, Q12(1.2f), Q12(0.0f));
    }

    if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_16)
    {
        groaner->model_0.controlState_2                         = GroanerControl_4;
        groaner->rotation_24.vy                                += Q12(0.125f);
        groanerProps.angle_EC += Q12(0.125f);
        g_SysWork.field_2284[3]                              &= ~(1 << 1);

        Character_AnimSet(groaner, ANIM_STATUS(GroanerAnim_16, true), 363);
        groanerProps.flags_E8.val16[0]                         &= ~GroanerFlag_9;
    }
}

void sharedFunc_800E4E84_2_s00(s_SubCharacter* groaner)
{
    s32    temp_a3;
    s32    temp_s1;
    s32    temp_s4;
    q19_12 distToPlayer;
    q19_12 var_s0_2;
    s32    i;

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_1)
    {
        return;
    }

    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_8))
    {
        groanerProps.field_108          = 0;
        groanerProps.timer_104          = Q12(0.0f);
        groanerProps.flags_E8.val16[0] |= GroanerFlag_8;
    }

    // TODO: Cleaner random angle generation.
    temp_s4 = func_8007029C(groaner, Q12(0.9f) - Rng_GenerateInt(0, 920), groaner->rotation_24.vy);

    if (groanerProps.timer_104 == Q12(0.0f) || !Rng_GenerateUInt(0, 31) ||
        (temp_s4 != 0 && groanerProps.timer_104 >= Q12(0.0f)))
    {
        temp_s1 = Q12(1.5f) - Rng_GenerateInt(0, 1535);
        groanerProps.angle_FC = Chara_HeadingAngleGet(groaner, temp_s1, groanerProps.targetPositionX_F4,
                                                                     groanerProps.targetPositionZ_F8, Q12(1.0f), false);
        if (groanerProps.angle_FC == Q12_ANGLE(360.0f))
        {
            groanerProps.angle_FC = func_8006F99C(groaner, (temp_s1 * 3) >> 2, groaner->rotation_24.vy);
        }

        if (temp_s4 != 0)
        {
            groanerProps.timer_104 = -(Rng_GenerateInt(Q12(0.375), Q12(0.75f) - 1));
        }
        else
        {
            groanerProps.timer_104 = Rng_GenerateInt(Q12(0.75f), Q12(1.5f) - 1);
        }
    }

    if (groanerProps.timer_104 > Q12(0.0f))
    {
        groanerProps.timer_104 -= g_DeltaTime;
        if (groanerProps.timer_104 < Q12(0.0f))
        {
            groanerProps.timer_104 = Q12(0.0f);
        }
    }
    else
    {
        groanerProps.timer_104 += g_DeltaTime;
        if (groanerProps.timer_104 > Q12(0.0f))
        {
            groanerProps.timer_104 = Q12(0.0f);
        }
    }

    for (i = 0; i < 2; i++)
    {
        temp_a3 = func_8005BF38((groanerProps.angle_FC - groaner->rotation_24.vy));
        if (((g_DeltaTime >> 3) + 1) < ABS(temp_a3))
        {
            if (temp_a3 > Q12_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
        }
        else
        {
            groaner->rotation_24.vy = groanerProps.angle_FC;
        }
    }

    temp_a3 = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);

    if (groanerProps.timer_104 >= Q12(0.0f))
    {
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)));
    }
    else
    {
        temp_a3 = Q12(1.0f) - (((temp_a3 - 227) * 3) >> 1);
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(temp_a3, Q12_MULT_PRECISE(groanerProps.field_114, 0x3999)));
    }

    var_s0_2                               = 0;
    groanerProps.field_108                += g_DeltaTime;

    if (groanerProps.field_108 > Q12(6.0f))
    {
        if (groanerProps.field_108 > Q12(7.5f))
        {
            var_s0_2 = Q12(0.5f);
        }
        else
        {
            var_s0_2 = (Q12_MULT_PRECISE(groanerProps.field_108 - Q12(6.0f), Q12(1.5f)) >> 2) + Q12(0.25f);
        }
    }

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);
    if (distToPlayer > Q12(3.5f))
    {
        if (distToPlayer > Q12(5.25f))
        {
            var_s0_2 += Q12(0.5f);
        }
        else
        {
            var_s0_2 += Q12(0.25f) + (Q12_MULT_PRECISE(distToPlayer - Q12(3.5f), Q12(1.75f)) >> 2);
        }
    }

    if (Rng_GenerateUInt(0, Q12_CLAMPED(1.0f)) < var_s0_2)
    {
        groaner->model_0.controlState_2 = GroanerControl_2;
    }
}

void sharedFunc_800E554C_2_s00(s_SubCharacter* groaner)
{
    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_1) &&
        groaner->model_0.anim_4.status_0 == ANIM_STATUS(GroanerAnim_9, true) &&
        !Rng_GenerateInt(0, 7)) // 1 in 8 chance.
    {
        groaner->model_0.controlState_2         = GroanerControl_1;
        groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_17, false);
    }
}

void sharedFunc_800E55B0_2_s00(s_SubCharacter* groaner)
{
    q3_12  timeScaled;
    s32    animTime;
    u32    animIdx;
    u8     newAnimStatus;

    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_1))
    {
        Chara_MoveSpeedUpdate(groaner, Q12(1.8f));
    }

    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_2))
    {
        groanerProps.flags_E8.val16[0] &= ~GroanerFlag_4;
    }

    if (groaner->model_0.controlState_2 == GroanerControl_6)
    {
        if (ANIM_TIME_RANGE_CHECK(groaner->model_0.anim_4.time_4, 39, 48))
        {
            groanerProps.flags_E8.val16[0] |= GroanerFlag_4;
        }

        if (groanerProps.flags_E8.val16[0] & GroanerFlag_4)
        {
            // TODO: Uncleanr float.
            if (groanerProps.flags_E8.val16[0] & GroanerFlag_5)
            {
                timeScaled = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 5.3333f);
            }
            else
            {
                timeScaled = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 3.2188f);
            }

            groanerProps.field_F0 = FP_FROM(timeScaled * Math_Sin(groaner->rotation_24.vy + Q12_ANGLE(180.0f)), Q12_SHIFT);
            groanerProps.field_F2 = FP_FROM(timeScaled * Math_Cos(groaner->rotation_24.vy + Q12_ANGLE(180.0f)), Q12_SHIFT);
        }

        if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_4)
        {
            return;
        }
    }
    else
    {
        animTime = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT);
        if ((animTime >= 134 && animTime < 157) ||
            (animTime >= 288 && animTime < 311))
        {
            groanerProps.flags_E8.val16[0] |= GroanerFlag_4;
        }

        if (groanerProps.flags_E8.val16[0] & GroanerFlag_4)
        {
            if (groanerProps.flags_E8.val16[0] & GroanerFlag_5)
            {
                timeScaled = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 1.6954f);
            }
            else
            {
                timeScaled = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.9781f);
            }

            if (groaner->model_0.controlState_2 == GroanerControl_7)
            {
                groanerProps.field_F0 = Q12_MULT(timeScaled, Math_Sin(groaner->rotation_24.vy - Q12_ANGLE(90.0f)));
                groanerProps.field_F2 = Q12_MULT(timeScaled, Math_Cos(groaner->rotation_24.vy - Q12_ANGLE(90.0f)));

                if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_8)
                {
                    return;
                }
            }
            else
            {
                groanerProps.field_F0 = Q12_MULT(timeScaled, Math_Sin(groaner->rotation_24.vy + Q12_ANGLE(90.0f)));
                groanerProps.field_F2 = Q12_MULT(timeScaled, Math_Cos(groaner->rotation_24.vy + Q12_ANGLE(90.0f)));

                if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_14)
                {
                    return;
                }
            }
        }
    }

    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_2) && groaner->health_B0 == Q12(0.0f))
    {
        animIdx       = ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0);
        newAnimStatus = ANIM_STATUS((animIdx == GroanerAnim_4) ? GroanerAnim_1 : GroanerAnim_Still, false);
        groaner->flags_3E &= ~CharaFlag_Unk2;

        if (animIdx == GroanerAnim_8)
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_5, false);
        }
        if (animIdx == GroanerAnim_14)
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_11, false);
        }

        if (newAnimStatus != GroanerAnim_Still)
        {
            groanerProps.relKeyframeIdx_100 = 0;
            groaner->model_0.anim_4.status_0                               = newAnimStatus;
            groaner->model_0.controlState_2                                       = GroanerControl_9;
        }
    }
}

void sharedFunc_800E5930_2_s00(s_SubCharacter* groaner)
{
    s32 newAnimStatus;
    u32 animStatus;

    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_1))
    {
        Chara_MoveSpeedUpdate(groaner, Q12(1.8f));
    }

    if (groaner->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != Chara_NpcIdxGet(groaner))
        {
            groaner->health_B0  = NO_VALUE;
            groaner->field_E1_0 = 0;
        }
    }

    if (!(groanerProps.flags_E8.val32 & (GroanerFlag_2 | GroanerFlag_6)) &&
        groaner->moveSpeed_38 == Q12(0.0f))
    {
        animStatus    = ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0);
        newAnimStatus = ANIM_STATUS(GroanerAnim_Still, false);
        if (animStatus == ANIM_STATUS(GroanerAnim_9, false))
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_2, true);
        }
        if (animStatus == ANIM_STATUS(GroanerAnim_9, true))
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_3, false);
        }
        if (animStatus == ANIM_STATUS(GroanerAnim_10, false))
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_3, true);
        }

        if (newAnimStatus != ANIM_STATUS(GroanerAnim_Still, false))
        {
            func_800622B8(3, groaner, newAnimStatus, 6);
            groanerProps.flags_E8.val16[0] |= GroanerFlag_6;
        }
    }
}

void sharedFunc_800E5AA4_2_s00(s_SubCharacter* groaner)
{
    s_800C4590 sp10;
    q3_12      angleDeltaToHeading;

    if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_10, true))
    {
        groaner->fallSpeed_34 += g_GravitySpeed;
    }
    else
    {
        groaner->fallSpeed_34 += g_GravitySpeed >> 1;
    }

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_1)
    {
        if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_2))
        {
            if (groaner->model_0.anim_4.status_0 == ANIM_STATUS(GroanerAnim_16, true))
            {
                Chara_MoveSpeedUpdate(groaner, Q12(7.2f) - 3);
            }
            else
            {
                Chara_MoveSpeedUpdate(groaner, Q12(1.8f));
            }
        }

        if (groanerProps.field_FE > Q12(0.0f))
        {
            angleDeltaToHeading = func_8005BF38((groaner->headingAngle_3C - groaner->rotation_24.vy) + Q12_ANGLE(180.0f));
            if (ABS(angleDeltaToHeading) < Q12_ANGLE(45.0f))
            {
                angleDeltaToHeading = Q12_ANGLE(-180.0f);
            }
            else if (angleDeltaToHeading > Q12_ANGLE(0.0f))
            {
                angleDeltaToHeading = Q12_ANGLE(-90.0f);
            }
            else
            {
                angleDeltaToHeading = Q12_ANGLE(90.0f);
            }

            if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + angleDeltaToHeading)) > Q12_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, groanerProps.field_FE);

                if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + angleDeltaToHeading)) <= Q12_ANGLE(0.0f))
                {
                    groanerProps.field_FE = Q12(0.0f);
                    groaner->rotation_24.vy                 = groaner->headingAngle_3C - angleDeltaToHeading;
                }
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, groanerProps.field_FE);

                if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + angleDeltaToHeading)) >= Q12_ANGLE(0.0f))
                {
                    groanerProps.field_FE = Q12(0.0f);
                    groaner->rotation_24.vy                 = groaner->headingAngle_3C - angleDeltaToHeading;
                }
            }

            groanerProps.field_FE = CLAMP_LOW(groanerProps.field_FE - FP_MULTIPLY_PRECISE(g_DeltaTime,
                                                                                          Q12(1.0f / 3.0f),
                                                                                          Q12_SHIFT),
                                              Q12(0.0f));
        }
        else if (groaner->moveSpeed_38 < Q12(0.225f))
        {
            groanerProps.flags_E8.val16[0] &= ~GroanerFlag_1;
        }
    }
    else if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_10, true))
    {
        groaner->headingAngle_3C = groaner->rotation_24.vy;
    }

    func_8005CB20(groaner, &sp10, groanerProps.field_F0, groanerProps.field_F2);

    groanerProps.field_F2 = Q12(0.0f);
    groanerProps.field_F0 = Q12(0.0f);

    if (groaner->position_18.vy == sp10.field_C)
    {
        groanerProps.flags_E8.val16[0] &= ~GroanerFlag_2;
    }
    else
    {
        groanerProps.flags_E8.val16[0] |= GroanerFlag_2;
    }
}

void sharedFunc_800E5EC4_2_s00(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    typedef struct
    {
        SVECTOR field_0;
        MATRIX  field_8;
    } s_sharedFunc_800E5EC4_2_s00;

    q3_12                        angle1;
    q3_12                        angleDeltaToTarget;
    q3_12                        angle0;
    q19_12                       constantDur;
    s_AnimInfo*                  animInfo;
    s_sharedFunc_800E5EC4_2_s00* ptr;

    switch (groaner->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(GroanerAnim_10, true):
            if (ANIM_TIME_RANGE_CHECK(groaner->model_0.anim_4.time_4, 207, 219))
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = Q12(24.0f);
            }

            if (ANIM_TIME_RANGE_CHECK(groaner->model_0.anim_4.time_4, 220, 225))
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = Q12(24.0f);
            }

            if (ANIM_TIME_RANGE_CHECK(groaner->model_0.anim_4.time_4, 226, 243))
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = Q12(30.0f);
            }
            break;

        case ANIM_STATUS(GroanerAnim_3, true):
            if (groanerProps.flags_E8.val16[0] & GroanerFlag_5)
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = Q12(32.0f);
            }
            else
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = Q12(25.75f);
            }
            break;

        case ANIM_STATUS(GroanerAnim_7, true):
        case ANIM_STATUS(GroanerAnim_13, true):
            if (groanerProps.flags_E8.val16[0] & GroanerFlag_5)
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = Q12(30.0f);
            }
            else
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = Q12(22.5f);
            }
            break;

        case ANIM_STATUS(GroanerAnim_16, true):
            if (groanerProps.angle_EC == groaner->rotation_24.vy)
            {
                constantDur = groaner->moveSpeed_38;
            }
            else
            {
                if (groaner->moveSpeed_38 >= Q12(1.0f))
                {
                    constantDur = groaner->moveSpeed_38;
                }
                else
                {
                    constantDur = Q12(1.0f);
                }
            }

            constantDur                                                              = Q12_DIV(constantDur * 20, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)));
            GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = constantDur;
            break;
    }

    Math_MatrixTransform(&groaner->position_18, (SVECTOR*)&groaner->rotation_24, coords);

    animInfo = &GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&groaner->model_0, anmHdr, coords, animInfo);

    ptr = PSX_SCRATCH;

    switch (groaner->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(GroanerAnim_17, false):
        case ANIM_STATUS(GroanerAnim_17, true):
            angle1    = Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            angle0    = Q12_ANGLE(33.75f);
            break;

        case ANIM_STATUS(GroanerAnim_10, false):
        case ANIM_STATUS(GroanerAnim_10, true):
        case ANIM_STATUS(GroanerAnim_15, false):
        case ANIM_STATUS(GroanerAnim_15, true):
        case ANIM_STATUS(GroanerAnim_16, false):
        case ANIM_STATUS(GroanerAnim_16, true):
            angle1    = Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(135.0f));
            angle0    = Q12_ANGLE(56.25f);
            break;

        default:
            angle1    = Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(135.0f));
            angle0    = Q12_ANGLE(0.0f);
            break;
    }

    angleDeltaToTarget = func_8005BF38(groanerProps.angle_EC - groaner->rotation_24.vy);
    if (angleDeltaToTarget == Q12_ANGLE(0.0f))
    {
        angle0 = Q12_ANGLE(0.0f);
    }
    else if (angleDeltaToTarget < Q12_ANGLE(0.0f))
    {
        angle0 = -angle0;
    }

    if (groanerProps.field_EE > angle0)
    {
        groanerProps.field_EE = MAX(angle0, groanerProps.field_EE - angle1);
    }
    else
    {
        groanerProps.field_EE = CLAMP_HIGH(angle0, groanerProps.field_EE + angle1);
    }

    *(s32*)&ptr->field_0 = (groanerProps.field_EE >> 2) << 16;
    ptr->field_0.vz      = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_0, &ptr->field_8);
    MulMatrix(&coords[3].coord, &ptr->field_8);
    MulMatrix(&coords[4].coord, &ptr->field_8);

    *(s32*)&ptr->field_0.vx = groanerProps.field_EE << 16;
    ptr->field_0.vz         = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_0, &ptr->field_8);
    MulMatrix(&coords[1].coord, &ptr->field_8);

    groaner->rotation_24.vy                 = func_8005BF38(groaner->rotation_24.vy);
    groanerProps.angle_EC = groaner->rotation_24.vy;
}

extern s_Keyframe sharedData_800EEE54_2_s00[];
extern s_Keyframe sharedData_800EF0AC_2_s00[];
extern s_Keyframe sharedData_800EF19C_2_s00;
extern s_Keyframe sharedData_800EF1B0_2_s00[];
extern s_Keyframe sharedData_800EF250_2_s00[];
extern s_Keyframe sharedData_800EF28C_2_s00[];
extern s_Keyframe sharedData_800EF368_2_s00[];
extern s_Keyframe sharedData_800EF4BC_2_s00;
extern s_Keyframe sharedData_800EF4D0_2_s00[];
extern s_Keyframe sharedData_800EF624_2_s00;
extern s_Keyframe sharedData_800EF638_2_s00[];
extern s_Keyframe sharedData_800EF7A0_2_s00;
extern s_Keyframe sharedData_800EF7B4_2_s00[];
extern s_Keyframe sharedData_800EFA84_2_s00[];
extern s_Keyframe sharedData_800EFCDC_2_s00[];
extern s_Keyframe sharedData_800EFF48_2_s00[];
extern s_Keyframe sharedData_800F0038_2_s00[];
extern s_Keyframe sharedData_800F00EC_2_s00[];
extern s_Keyframe sharedData_800F0268_2_s00[];
extern s_Keyframe sharedData_800F03A8_2_s00[];
extern s_Keyframe sharedData_800F04C0_2_s00[];

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
    s32 __temp2;                              \
                                              \
    arg0->field_C8.field_0 = data.field_0;    \
                                              \
    __temp                 = data.field_2;    \
    arg0->field_C8.field_2 = __temp;          \
    arg0->field_C8.field_4 = data.field_4;    \
                                              \
    __temp                   = data.field_6;  \
    arg0->field_C8.field_6   = __temp;        \
    arg0->field_D8.offsetX_4 = data.field_10; \
                                              \
    __temp                   = data.field_12; \
    arg0->field_D8.offsetZ_6 = __temp;        \
    arg0->field_D4.radius_0  = data.field_8;  \
    arg0->field_D8.offsetX_0 = data.field_C;  \
                                              \
    __temp                   = data.field_E;  \
    arg0->field_D8.offsetZ_2 = __temp;        \
                                              \
    __temp2                = data.field_A;    \
    arg0->field_D4.field_2 = __temp2;         \
}

#define ANIM_INDEX_FROM_KEYFRAME(offset, keyframe, max, count) \
    ((offset) - ((keyframe) > (count)) < (max) ? ((offset) - ((keyframe) > (count))) : ((max) - 1))

void sharedFunc_800E6338_2_s00(s_SubCharacter* groaner)
{
    s32 keyframeIdx2;
    s32 keyframeIdx1;
    s32 keyframeIdx0;
    s32 temp;

    switch (groaner->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(GroanerAnim_9, false):
            if (groanerProps.relKeyframeIdx_100 == 5)
            {
                func_80070400(groaner, &sharedData_800EF4BC_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            else if (groanerProps.relKeyframeIdx_100 == 13)
            {
                func_80070400(groaner, &sharedData_800EF624_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            else if (groanerProps.relKeyframeIdx_100 == 25)
            {
                func_80070400(groaner, &sharedData_800EF7A0_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            break;

        case ANIM_STATUS(GroanerAnim_9, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 191;
            keyframeIdx0 = !(keyframeIdx2 < 5) + !(keyframeIdx2 < 12);
            keyframeIdx1 = !(keyframeIdx2 < 4) + !(keyframeIdx2 < 11);

            if (keyframeIdx2 == 15)
            {
                keyframeIdx1 -= 2;
            }

            func_80070400(groaner, &sharedData_800EF250_2_s00[keyframeIdx0], &sharedData_800EF250_2_s00[keyframeIdx1]);
            groanerProps.relKeyframeIdx_100 = keyframeIdx2;
            break;

        case ANIM_STATUS(GroanerAnim_17, false):
            if (groanerProps.relKeyframeIdx_100 != 100)
            {
                keyframeIdx2      = groanerProps.relKeyframeIdx_100;
                keyframeIdx0 = !(keyframeIdx2 < 5) + !(keyframeIdx2 < 12);
                func_80070400(groaner, &sharedData_800EF250_2_s00[keyframeIdx0], &sharedData_800EF28C_2_s00[0]);
            }
            else
            {
                CopyData(groaner, sharedData_800EF28C_2_s00[0]);
            }
            break;

        case ANIM_STATUS(GroanerAnim_17, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 371;

            if (keyframeIdx2 < 12)
            {
                if (keyframeIdx2 < 9)
                {
                    if (keyframeIdx2 < 4)
                    {
                        keyframeIdx0 = keyframeIdx2;
                    }
                    else
                    {
                        keyframeIdx0 = 3;
                    }
                }
                else
                {
                    keyframeIdx0 = 4;
                }
            }
            else if (keyframeIdx2 < 22)
            {
                if (((keyframeIdx2 >> 1) - 1) < 8)
                {
                    keyframeIdx0 = (keyframeIdx2 >> 1) - 1;
                }
                else
                {
                    keyframeIdx0 = 7;
                }
            }
            else
            {
                keyframeIdx0 = keyframeIdx2 - 14 - !(keyframeIdx2 < 24);
            }

            if (keyframeIdx2 < 11)
            {
                if (keyframeIdx2 < 8)
                {
                    if ((keyframeIdx2 + 1) < 4)
                    {
                        keyframeIdx1 = keyframeIdx2 + 1;
                    }
                    else
                    {
                        keyframeIdx1 = 3;
                    }
                }
                else
                {
                    keyframeIdx1 = 4;
                }
            }
            else if (keyframeIdx2 < 21)
            {
                if (((keyframeIdx2 - 1) >> 1) < 8)
                {
                    keyframeIdx1 = (keyframeIdx2 - 1) >> 1;
                }
                else
                {
                    keyframeIdx1 = 7;
                }
            }
            else if (keyframeIdx2 != 25)
            {
                keyframeIdx1 = (keyframeIdx2 - 13) - !(keyframeIdx2 < 23);
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(groaner, &sharedData_800EF28C_2_s00[keyframeIdx0], &sharedData_800EF28C_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_2, false):
            CopyData(groaner, sharedData_800EF368_2_s00[2]);
            break;

        case ANIM_STATUS(GroanerAnim_2, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 16;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 10);
            keyframeIdx1 = (keyframeIdx2 - !(keyframeIdx2 < 9)) - !(keyframeIdx2 < 19);
            func_80070400(groaner, &sharedData_800EF368_2_s00[keyframeIdx0], &sharedData_800EF368_2_s00[keyframeIdx1]);

            groanerProps.relKeyframeIdx_100 = 5;
            break;

        case ANIM_STATUS(GroanerAnim_6, false):
            CopyData(groaner, sharedData_800EF4D0_2_s00[2]);
            break;

        case ANIM_STATUS(GroanerAnim_6, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 111;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 11);
            keyframeIdx1 = keyframeIdx2 - !(keyframeIdx2 < 10);
            func_80070400(groaner, &sharedData_800EF4D0_2_s00[keyframeIdx0], &sharedData_800EF4D0_2_s00[keyframeIdx1]);

            groanerProps.relKeyframeIdx_100 = 13;
            break;

        case ANIM_STATUS(GroanerAnim_12, false):
            CopyData(groaner, sharedData_800EF638_2_s00[3]);
            break;

        case ANIM_STATUS(GroanerAnim_12, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 265;
            keyframeIdx0 = (keyframeIdx2 - !(keyframeIdx2 < 9));
            keyframeIdx1 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 264) - !(keyframeIdx2 < 8);
            func_80070400(groaner, &sharedData_800EF638_2_s00[keyframeIdx0], &sharedData_800EF638_2_s00[keyframeIdx1]);

            groanerProps.relKeyframeIdx_100 = 25;
            break;

        case ANIM_STATUS(GroanerAnim_3, false):
            CopyData(groaner, sharedData_800EF7B4_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_3, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 37;
            keyframeIdx0 = ((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 39) - !(keyframeIdx2 < 17)) - !(keyframeIdx2 < 38);
            keyframeIdx1 = (((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 38) - !(keyframeIdx2 < 16)) - !(keyframeIdx2 < 37)) - !(keyframeIdx2 < 39);
            func_80070400(groaner, &sharedData_800EF7B4_2_s00[keyframeIdx0], &sharedData_800EF7B4_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_7, false):
            CopyData(groaner, sharedData_800EFA84_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_7, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 131;
            keyframeIdx0 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 134) - !(keyframeIdx2 < 31);
            keyframeIdx1 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 133) - !(keyframeIdx2 < 30);
            func_80070400(groaner, &sharedData_800EFA84_2_s00[keyframeIdx0], &sharedData_800EFA84_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_13, false):
            CopyData(groaner, sharedData_800EFCDC_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_13, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 285;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 31);
            keyframeIdx1 = (keyframeIdx2 - !(keyframeIdx2 < 30)) - !(keyframeIdx2 < 32);
            func_80070400(groaner, &sharedData_800EFCDC_2_s00[keyframeIdx0], &sharedData_800EFCDC_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_4, false):
            CopyData(groaner, sharedData_800EFF48_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_4, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 78;
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 82;

            if (keyframeIdx2 < 9)
            {
                if (keyframeIdx2 <= 0)
                {
                    if (keyframeIdx2 < 6)
                    {
                        keyframeIdx0 = keyframeIdx2 - (keyframeIdx2 > 0);
                    }
                    else
                    {
                        keyframeIdx0 = 5;
                    }
                }
                else
                {
                    if (keyframeIdx2 - 1 < 6)
                    {
                        keyframeIdx0 = keyframeIdx2 - (keyframeIdx2 > 0);
                    }
                    else
                    {
                        keyframeIdx0 = 5;
                    }
                }
            }

            if (keyframeIdx2 != 15)
            {
                if (keyframeIdx2 < 8)
                {
                    if (keyframeIdx2 < 6)
                    {
                        keyframeIdx1 = keyframeIdx2;
                    }
                    else
                    {
                        keyframeIdx1 = 5;
                    }
                }
                else
                {
                    keyframeIdx1 = keyframeIdx2 - 3;
                }
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(groaner, &sharedData_800EFF48_2_s00[keyframeIdx0], &sharedData_800EFF48_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_8, false):
            CopyData(groaner, sharedData_800F0038_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_8, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 165;
            if (keyframeIdx2 < 10)
            {
                if (keyframeIdx2 < 6)
                {
                    keyframeIdx0 = 1;
                    keyframeIdx1 = keyframeIdx2 >> 1;
                    if (keyframeIdx1 < 2)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
                else
                {
                    keyframeIdx0 = 4;
                    keyframeIdx1 = keyframeIdx2 - 4;
                    if (keyframeIdx1 < 5)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
            }
            else
            {
                if (keyframeIdx2 >= 18)
                {
                    keyframeIdx0 = 8;
                    keyframeIdx1 = (keyframeIdx2 >> 1) - 3;
                    if (keyframeIdx1 < 9)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
                else
                {
                    keyframeIdx0 = 5;
                }
            }

            if (keyframeIdx2 < 17)
            {
                if (keyframeIdx2 < 5)
                {
                    if (keyframeIdx2 < 2)
                    {
                        keyframeIdx1 = keyframeIdx2;
                    }
                    else
                    {
                        keyframeIdx1 = 1;
                    }
                }
                else
                {
                    keyframeIdx1 = ANIM_INDEX_FROM_KEYFRAME(keyframeIdx2 - 3, keyframeIdx2, 6, 7);
                }
            }
            else
            {
                if (keyframeIdx2 != 25)
                {
                    if ((((keyframeIdx2 - 1) >> 1) - 2) < 9)
                    {
                        keyframeIdx1 = ((keyframeIdx2 - 1) >> 1) - 2;
                    }
                    else
                    {
                        keyframeIdx1 = 8;
                    }
                }
                else
                {
                    keyframeIdx1 = 0;
                }
            }

            func_80070400(groaner, &sharedData_800F0038_2_s00[keyframeIdx0], &sharedData_800F0038_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_14, false):
            CopyData(groaner, sharedData_800F00EC_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_14, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 319;
            keyframeIdx0 = keyframeIdx2 >> 1;

            if (keyframeIdx2 >= 7)
            {
                if (keyframeIdx2 < 16)
                {
                    keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(keyframeIdx2 - 3, keyframeIdx2, 9, 9);
                }
                else
                {
                    keyframeIdx0 = (keyframeIdx2 - 7) - !(keyframeIdx2 < 20);
                }
            }

            if (keyframeIdx2 < 9)
            {
                keyframeIdx1 = keyframeIdx2 - !(keyframeIdx2 < 2) - !(keyframeIdx2 < 4);
            }
            else
            {
                if (keyframeIdx2 < 15)
                {
                    if ((keyframeIdx2 - 5) < 9)
                    {
                        keyframeIdx1 = keyframeIdx2 - 5;
                    }
                    else
                    {
                        keyframeIdx1 = 8;
                    }
                }
                else
                {
                    if (keyframeIdx2 != 26)
                    {
                        keyframeIdx1 = (keyframeIdx2 - 6) - !(keyframeIdx2 < 19);
                    }
                    else
                    {
                        keyframeIdx1 = 0;
                    }
                }
            }

            func_80070400(groaner, &sharedData_800F00EC_2_s00[keyframeIdx0], &sharedData_800F00EC_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_1, false):
        case ANIM_STATUS(GroanerAnim_21, false):
            keyframeIdx2 = groanerProps.relKeyframeIdx_100;
            if (keyframeIdx2 < 9)
            {
                keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(keyframeIdx2, keyframeIdx2, 6, 0);
            }
            else
            {
                keyframeIdx0 = keyframeIdx2 - 4;
            }

            func_80070400(groaner, &sharedData_800EFF48_2_s00[keyframeIdx0], &sharedData_800F0268_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_1, true):
        case ANIM_STATUS(GroanerAnim_21, true):
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1 = keyframeIdx0 + 1;
            func_80070400(groaner, &sharedData_800F0268_2_s00[keyframeIdx0], &sharedData_800F0268_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_18, false):
        case ANIM_STATUS(GroanerAnim_18, true):
            CopyData(groaner, sharedData_800F0268_2_s00[15]);
            break;

        case ANIM_STATUS(GroanerAnim_5, false):
        case ANIM_STATUS(GroanerAnim_22, false):
            keyframeIdx2 = groanerProps.relKeyframeIdx_100;
            if (keyframeIdx2 < 10)
            {
                if (keyframeIdx2 < 6)
                {
                    keyframeIdx0 = 1;
                    keyframeIdx1 = keyframeIdx2 >> 1;
                    if (keyframeIdx1 < 2)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
                else
                {
                    keyframeIdx0 = 4;
                    keyframeIdx1 = keyframeIdx2 - 4;
                    if (keyframeIdx1 < 5)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
            }
            else if (keyframeIdx2 >= 18)
            {
                keyframeIdx0 = 8;
                keyframeIdx1 = (keyframeIdx2 >> 1) - 3;
                if (keyframeIdx1 < 9)
                {
                    keyframeIdx0 = keyframeIdx1;
                }
            }
            else
            {
                keyframeIdx0 = 5;
            }

            func_80070400(groaner, &sharedData_800F0038_2_s00[keyframeIdx0], &sharedData_800F03A8_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_5, true):
        case ANIM_STATUS(GroanerAnim_22, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 94;
            keyframeIdx0 = (keyframeIdx2 - !(keyframeIdx2 < 13)) - !(keyframeIdx2 < 15);
            keyframeIdx1 = (((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 93) - !(keyframeIdx2 < 12)) - !(keyframeIdx2 < 14)) - !(keyframeIdx2 < 15);
            func_80070400(groaner, &sharedData_800F03A8_2_s00[keyframeIdx0], &sharedData_800F03A8_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_19, false):
        case ANIM_STATUS(GroanerAnim_19, true):
            CopyData(groaner, sharedData_800F03A8_2_s00[13]);
            break;

        case ANIM_STATUS(GroanerAnim_11, false):
        case ANIM_STATUS(GroanerAnim_23, false):
            keyframeIdx2      = groanerProps.relKeyframeIdx_100;
            keyframeIdx0 = keyframeIdx2 >> 1;
            if (keyframeIdx2 >= 7)
            {
                if (keyframeIdx2 < 16)
                {
                    keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(keyframeIdx2 - 3, keyframeIdx2, 9, 9);
                }
                else
                {
                    keyframeIdx0 = (keyframeIdx2 - 7) - !(keyframeIdx2 < 20);
                }
            }

            func_80070400(groaner, &sharedData_800F00EC_2_s00[keyframeIdx0], &sharedData_800F04C0_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_11, true):
        case ANIM_STATUS(GroanerAnim_23, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 244;
            if (keyframeIdx2 < 12)
            {
                keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 9);
            }
            else
            {
                temp = keyframeIdx2 >> 1;
                if (keyframeIdx2 >= 16)
                {
                    keyframeIdx0 = temp + 3;
                }
                else
                {
                    keyframeIdx0 = temp + 4;
                }
            }

            if (keyframeIdx2 < 12)
            {
                keyframeIdx1 = keyframeIdx2 - !(keyframeIdx2 < 8);
            }
            else
            {
                temp = (keyframeIdx2 - 1) >> 1;
                if (keyframeIdx2 >= 15)
                {
                    keyframeIdx1 = temp + 4;
                }
                else
                {
                    keyframeIdx1 = temp + 5;
                }
            }

            func_80070400(groaner, &sharedData_800F04C0_2_s00[keyframeIdx0], &sharedData_800F04C0_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_20, false):
        case ANIM_STATUS(GroanerAnim_20, true):
            CopyData(groaner, sharedData_800F04C0_2_s00[13]);
            break;

        case ANIM_STATUS(GroanerAnim_16, false):
            CopyData(groaner, sharedData_800EF1B0_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_16, true):
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 363;
            func_80070400(groaner, &sharedData_800EF1B0_2_s00[keyframeIdx0], &sharedData_800EF1B0_2_s00[(FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 362) & 0x7]);
            break;

        case ANIM_STATUS(GroanerAnim_15, false):
            CopyData(groaner, sharedData_800EF0AC_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_15, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 346;
            keyframeIdx0 = (((keyframeIdx2 - !(keyframeIdx2 < 3)) - !(keyframeIdx2 < 9)) - !(keyframeIdx2 < 12)) - !(keyframeIdx2 < 13);
            keyframeIdx1 = ((((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 345) - !(keyframeIdx2 < 2)) - !(keyframeIdx2 < 8)) - !(keyframeIdx2 < 11)) - !(keyframeIdx2 < 12);
            func_80070400(groaner, &sharedData_800EF0AC_2_s00[keyframeIdx0], &sharedData_800EF0AC_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_10, false):
            func_80070400(groaner, &sharedData_800EF19C_2_s00, &sharedData_800EEE54_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_10, true):
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 214;
            keyframeIdx1 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 213;
            func_80070400(groaner, &sharedData_800EEE54_2_s00[keyframeIdx0], &sharedData_800EEE54_2_s00[keyframeIdx1]);

            groaner->field_C8.field_8 = Q12(-0.8f);
            break;
    }

    func_8005C814(&groaner->field_D8, groaner);
}

void sharedFunc_800E71E8_2_s00(s_SubCharacter* groaner)
{
    s32    keyframeIdx;
    q19_12 sfxVol;
    s32    sfxPitch;
    s32    temp_a0;

    if (groanerProps.timer_10C > Q12(0.0f))
    {
        groanerProps.timer_10C -= g_DeltaTime;
        if (groanerProps.timer_10C <= Q12(0.0f))
        {
            groanerProps.timer_10C = Q12(0.0f);
            groanerProps.field_10E = 0;
        }
    }
    else if (groanerProps.timer_10C < Q12(0.0f))
    {
        groanerProps.timer_10C += g_DeltaTime;
        if (groanerProps.timer_10C >= Q12(0.0f))
        {
            func_8005DC1C(Sfx_Unk1411, &groaner->position_18, Q8(0.5f), 0);
            groanerProps.timer_10C = Q12(2.0f);
        }
    }

    switch (groanerProps.field_10E)
    {
        default:
            temp_a0 = groanerProps.field_10F;
            if (temp_a0 == 4)
            {
                groanerProps.timer_10C = Q12(1.0f);
                groanerProps.field_10E = temp_a0;

                if (groaner->health_B0 > Q12(0.0f) &&
                    (groanerProps.flags_E8.val32 & (GroanerFlag_3 | GroanerFlag_12)) == GroanerFlag_3)
                {
                    func_8005DC1C(Sfx_Unk1409, &groaner->position_18, Q8(0.5f), 0);
                }
                else
                {
                    func_8005DC1C(Sfx_Unk1414, &groaner->position_18, Q8(0.5f), 0);
                }

                groanerProps.flags_E8.val16[0] &= ~GroanerFlag_12;
                break;
            }
            else if (groanerProps.field_10E != 2 && temp_a0 == 2)
            {
                groanerProps.timer_10C = Q12(-0.3f);
                groanerProps.field_10E = temp_a0;
                break;
            }

        case 4:
            if (groanerProps.field_10E == 0 && groanerProps.field_10F == 0 &&
                (groaner->health_B0 > Q12(0.0f)))
            {
                if (groaner->model_0.anim_4.status_0 == 33)
                {
                    func_8005DC1C(Sfx_Unk1410, &groaner->position_18, Q8(0.25f), 0);
                    groanerProps.timer_10C = Rng_GenerateInt(Q12(0.5f), Q12(0.6f) - 1);
                    groanerProps.field_10E = 3;
                }
                else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_10 &&
                         ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_15 &&
                         !Rng_GenerateUInt(0, 15))
                {
                    func_8005DC1C(Sfx_Unk1406, &groaner->position_18, (Q12_DIV(groaner->health_B0, Q12(280.0f)) >> 7) + 32, 0);
                    groanerProps.timer_10C = Rng_GenerateInt(Q12(4.8f), Q12(8.0f) - 2);
                    groanerProps.field_10E = 1;
                }
            }
            break;
    }

    groanerProps.field_10F = 0;

    keyframeIdx = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT);
    sfxVol      = (Q12_DIV(groaner->moveSpeed_38, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f))) >> 6) + 64;
    sfxPitch    = (Q12_DIV(groaner->moveSpeed_38, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f))) >> 7) + Rng_GenerateUInt(0, 7);

    if ((keyframeIdx > 365 && keyframeIdx < 370) ||
        (keyframeIdx > 374 && keyframeIdx < 382))
    {
        if (groanerProps.field_110 == 0)
        {
            func_8005DD44(Sfx_Unk1413, &groaner->position_18, sfxVol, sfxPitch);
            groanerProps.field_110++;
        }
    }
    else
    {
        groanerProps.field_110 = 0;
    }

    if ((keyframeIdx > 367 && keyframeIdx < 373) ||
        (keyframeIdx > 390 && keyframeIdx < 397))
    {
        if (groanerProps.field_111 == 0)
        {
            func_8005DD44(Sfx_Unk1413, &groaner->position_18, sfxVol, sfxPitch);
            groanerProps.field_111++;
        }
    }
    else
    {
        groanerProps.field_111 = 0;
    }
}

#undef groanerProps

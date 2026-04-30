#include "bodyprog/bodyprog.h"
#include "bodyprog/events/npc_main.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/groaner.h"

#define groanerProps groaner->properties.groaner

// @hack Needed to fix mismatch in `sharedFunc_800E39D8_2_s00`.
// Same as version in `rng.h` but without parenthesess around it.
// TODO: Changing `rng.h` version still doesn't let it match though?
#define Rng_GenerateIntFromInput(rand, low, high) \
    (s32)((rand) % (((high) - (low)) + 1)) + (low)

void Ai_Groaner_Update(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    u8 prevControlState;

    // Initialize.
    if (groaner->model.controlState == GroanerControl_0)
    {
        Ai_Groaner_Init(groaner);
    }

    prevControlState = groaner->model.controlState;

    if (g_DeltaTime != Q12(0.0f))
    {
        sharedFunc_800E33DC_2_s00(groaner);
        sharedFunc_800E384C_2_s00(groaner);
        sharedFunc_800E5AA4_2_s00(groaner);
    }

    sharedFunc_800E5EC4_2_s00(groaner, anmHdr, boneCoords);

    if (g_DeltaTime != Q12(0.0f))
    {
        sharedFunc_800E6338_2_s00(groaner); // Control func with state machine?
        sharedFunc_800E71E8_2_s00(groaner);

        if (groaner->model.controlState != prevControlState)
        {
            groanerProps.flags.val16[0] &= ~GroanerFlag_8;
        }

        if (groanerProps.flags.val16[0] & GroanerFlag_7)
        {
            groaner->flags |= CharaFlag_Unk3;
        }
    }
}

void Ai_Groaner_Init(s_SubCharacter* groaner)
{
    #define HEALTH_BASE      Q12(210.0f)
    #define HEALTH_BONUS_MAX Q12(70.0f)

    s32 i;

    Chara_PropertiesClear(groaner);
    groanerProps.flags.val16[0]  = 0;
    groaner->model.anim.alpha = Q12(0.0f);

    groaner->health = HEALTH_BASE + (Rng_Rand16() % HEALTH_BONUS_MAX);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal &&
        Rng_GenerateInt(0, 7) == 0) // 1 in 8 chance.
    {
        groaner->health *= 2;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard &&
        Rng_GenerateInt(0, 3) == 0)// 1 in 4 chance.
    {
        groaner->health *= 2;
    }

    groaner->moveSpeed    = Q12(0.0f);
    groaner->collision.state      = 3;
    groaner->headingAngle = groaner->rotation.vy;

    groanerProps.field_114 = Rng_GenerateUInt(Q12(0.9375f), Q12(1.0625f) - 1);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        groanerProps.field_114 += (u32)groanerProps.field_114 / 8;
    }
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        groanerProps.field_114 -= ((s32)((u16)groanerProps.field_114 << 16) >> 20); // (value * Q12(16.0f)) / Q12(256.0f)
    }

    ModelAnim_AnimInfoSet(&groaner->model.anim, GROANER_ANIM_INFOS);
    Chara_DamageClear(groaner);

    if (groaner->model.stateStep == GroanerStateStep_3)
    {
        groaner->model.controlState = GroanerControl_1;
        Character_AnimSet(groaner, ANIM_STATUS(GroanerAnim_17, true), 371);
        groanerProps.flags.val16[0] |= GroanerFlag_5;
    }

    groaner->model.stateStep = GroanerStateStep_0;

    groanerProps.targetPositionX = groaner->position.vx;
    groanerProps.targetPositionZ = groaner->position.vz;

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

    if (groaner->health > Q12(0.0f))
    {
        Collision_Get(&coll, groaner->position.vx, groaner->position.vz);

        if (coll.field_8 == 12 && Rng_GenerateInt(Q12(4.0f), Q12(7.0f) - 1) < groaner->position.vy)
        {
            groaner->damage.amount = Q12(1000.0f);
        }
    }

    if (groaner->damage.amount == Q12(0.0f))
    {
        return;
    }

    if (groaner->health < Q12(0.0f))
    {
        return;
    }

    prevControlState = groaner->model.controlState;

    if (groaner->health > Q12(0.0f))
    {
        groanerProps.field_10F = 4;
    }

    groanerProps.targetPositionX     = g_SysWork.playerWork.player.position.vx;
    groanerProps.targetPositionZ     = g_SysWork.playerWork.player.position.vz;
    groanerProps.flags.val16[0]     |= GroanerFlag_7;

    groaner->health = MAX(groaner->health - groaner->damage.amount, Q12(0.0f));
    unkDist         = Math_Vector2MagCalc(groaner->damage.position.vx, groaner->damage.position.vz);

    // Set new heading angle.
    if (groaner->damage.position.vx != Q12(0.0f) ||
        groaner->damage.position.vz != Q12(0.0f))
    {
        newHeadingAngle = ratan2(groaner->damage.position.vx, groaner->damage.position.vz);
    }
    else
    {
        newHeadingAngle = g_SysWork.playerWork.player.rotation.vy;
    }

    unkAngle = Math_AngleNormalizeSigned((newHeadingAngle - groaner->rotation.vy) + Q12_ANGLE(180.0f));

    // TODO: Unsure if `field_FE` is an angle.
    groanerProps.field_FE = CLAMP_LOW(unkDist >> 2, Q12_ANGLE(90.0f));

    temp_v0 = FP_TO(groaner->damage.position.vy, Q12_SHIFT);

    groaner->headingAngle = newHeadingAngle;

    Chara_DamageClear(groaner);

    groanerProps.flags.val16[0] |= GroanerFlag_1;
    groaner->moveSpeed           = FP_TO(unkDist, Q12_SHIFT) / Q12(1.2f);
    groaner->fallSpeed          += temp_v0 / Q12(1.2f);

    if (groanerProps.flags.val16[0] & GroanerFlag_3)
    {
        groanerProps.field_FE = 0;

        if (groaner->health != Q12(0.0f))
        {
            if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) == ANIM_STATUS(GroanerAnim_2, false))
            {
                if (groaner->model.anim.status != ANIM_STATUS(GroanerAnim_4, true))
                {
                    groanerProps.relKeyframeIdx_100 = 0;
                }
                else
                {
                    groanerProps.relKeyframeIdx_100 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 78;
                }

                groaner->model.anim.status = ANIM_STATUS(GroanerAnim_21, false);
            }
            else if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) == GroanerAnim_8)
            {
                if (groaner->model.anim.status != ANIM_STATUS(GroanerAnim_8, true))
                {
                    groanerProps.relKeyframeIdx_100 = 0;
                }
                else
                {
                    groanerProps.relKeyframeIdx_100 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 165;
                }

                groaner->model.anim.status = ANIM_STATUS(GroanerAnim_22, false);
            }
            else if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) == GroanerAnim_14)
            {
                if (groaner->model.anim.status != ANIM_STATUS(GroanerAnim_14, true))
                {
                    groanerProps.relKeyframeIdx_100 = 0;
                }
                else
                {
                    groanerProps.relKeyframeIdx_100 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 319;
                }

                groaner->model.anim.status = ANIM_STATUS(GroanerAnim_23, false);
            }
        }
    }
    else if (groaner->health > Q12(100.0f))
    {
        if (!(groanerProps.flags.val16[0] & GroanerFlag_10))
        {
            if (ABS(unkAngle) < Q12_ANGLE(45.0f))
            {
                if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) != GroanerAnim_2)
                {
                    groaner->model.anim.status = ANIM_STATUS(GroanerAnim_2, false);
                }
            }
            else
            {
                if (unkAngle > Q12_ANGLE(0.0f))
                {
                    if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) != GroanerAnim_6)
                    {
                        groaner->model.anim.status = ANIM_STATUS(GroanerAnim_6, false);
                    }
                }
                else if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) != GroanerAnim_12)
                {
                    groaner->model.anim.status = ANIM_STATUS(GroanerAnim_12, false);
                }
            }

            groaner->model.controlState = GroanerControl_5;
        }
    }
    else
    {
        Savegame_EnemyStateUpdate(groaner);

        groaner->flags                                      |= CharaFlag_Unk2;
        groanerProps.flags.val16[0]                         |= GroanerFlag_3 | GroanerFlag_12;

        if (ABS(unkAngle) < Q12_ANGLE(45.0f))
        {
            groaner->model.anim.status  = ANIM_STATUS(GroanerAnim_3, false);
            groaner->model.controlState = GroanerControl_6;
        }
        else if (unkAngle > Q12_ANGLE(0.0f))
        {
            groaner->model.anim.status  = ANIM_STATUS(GroanerAnim_7, false);
            groaner->model.controlState = GroanerControl_7;
        }
        else
        {
            groaner->model.anim.status  = ANIM_STATUS(GroanerAnim_13, false);
            groaner->model.controlState = GroanerControl_8;
        }
    }

    if (prevControlState != groaner->model.controlState && prevControlState == GroanerControl_3)
    {
        g_SysWork.charaGroupFlags[3] &= ~CharaGroupFlag_1;
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

    if (func_80070360(groaner, Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx - groaner->position.vx,
            g_SysWork.playerWork.player.position.vz - groaner->position.vz), UNK_VAL) != 0 ||
        func_8006FD90(groaner, 1, sharedData_800EEE3C_2_s00[getIndex()].field_0, sharedData_800EEE3C_2_s00[getIndex()].field_4))
    {
        groanerProps.flags.val16[0] |= GroanerFlag_7;

        if (groanerProps.flags.val16[0] & GroanerFlag_5)
        {
            groanerProps.targetPositionX = g_SysWork.playerWork.player.position.vx;
            groanerProps.targetPositionZ = g_SysWork.playerWork.player.position.vz;
        }
    }
    else
    {
        groanerProps.flags.val16[0] &= ~GroanerFlag_7;
    }

    if (groaner->model.anim.status != ANIM_STATUS(GroanerAnim_10, true))
    {
        groaner->field_44.field_0 = 0;
    }

    sharedData_800EEE14_2_s00[groaner->model.controlState](groaner);
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

    if (groanerProps.flags.val16[0] & GroanerFlag_0)
    {
        unkAngleDelta = Math_AngleNormalizeSigned(groanerProps.angleToTarget - groaner->rotation.vy);
        if (TIMESTEP_ANGLE(3, 2) < ABS(unkAngleDelta))
        {
            if (unkAngleDelta > Q12_ANGLE(0.0f))
            {
                groaner->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(60.0f));
            }
            else
            {
                groaner->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(60.0f));
            }
        }
        else
        {
            groaner->rotation.vy = groanerProps.angleToTarget;
            groanerProps.flags.val16[0] &= ~GroanerFlag_0;
        }
    }
    else
    {
        if (Ray_CharaLosHitCheck(groaner, Q12_ANGLE(306.0f), groaner->rotation.vy))
        {
            groanerProps.angleToTarget = func_8006F99C(groaner, Q12_ANGLE(306.0f), groaner->rotation.vy);
            if (groanerProps.angleToTarget == Q12_ANGLE(360.0f))
            {
                groanerProps.angleToTarget = -groaner->rotation.vy;
            }

            groanerProps.flags.val16[0] |= GroanerFlag_0;
        }
        else
        {
            unkRand = Rng_GenerateInt(Q12(2.0f), Q12(6.0f) - 1);

            posX       = groaner->position.vx;
            targetPosX = groanerProps.targetPositionX;
            posZ       = groaner->position.vz;
            targetPosZ = groanerProps.targetPositionZ;

            // TODO: Demangle condition.
            if (unkRand < (((posX - targetPosX) > (posZ - targetPosZ)) ? ABS(posX - targetPosX) + ABS((posZ - targetPosZ) >> 1) :
                                                                         ABS((posX - targetPosX) >> 1) + ABS(posZ - targetPosZ)))
            {
                // TODO: Cleaner random angle generation.
                if (ABS(Math_AngleNormalizeSigned(groaner->rotation.vy - ratan2(groaner->position.vx - groanerProps.targetPositionX,
                                                                                groaner->position.vz - groanerProps.targetPositionZ))) < (Rng_GenerateUInt(Q12_ANGLE(45.0f), Q12_ANGLE(50.7f) - 1)))
                {
                    randTargetPosX        = groanerProps.targetPositionX + Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1);
                    groanerProps.angleToTarget = Chara_HeadingAngleGet(groaner, Q12_ANGLE(306.0f),
                                                                  randTargetPosX, groanerProps.targetPositionZ + Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1),
                                                                  Q12_ANGLE(360.0f), true);
                    if (groanerProps.angleToTarget == Q12_ANGLE(360.0f))
                    {
                        groanerProps.angleToTarget = -groaner->rotation.vy;
                    }

                    groanerProps.flags.val16[0] |= GroanerFlag_0;
                }
            }
        }
    }

    if (groaner->model.anim.status == ANIM_STATUS(GroanerAnim_17, true) &&
        (groanerProps.flags.val32 & (GroanerFlag_5 | GroanerFlag_7)) == (GroanerFlag_5 | GroanerFlag_7))
    {
        groaner->model.controlState = GroanerControl_2;
        groaner->model.anim.status  = ANIM_STATUS(GroanerAnim_16, false);
        groanerProps.flags.val16[0] &= ~GroanerFlag_0;
        groanerProps.flags.val16[0] |= GroanerFlag_10;
    }
}

void sharedFunc_800E3E94_2_s00(s_SubCharacter* groaner)
{
    s16    temp_v0_10;
    q3_12  angle0;
    q3_12  angleDeltaToTarget;
    q19_12 headingAngle;
    s32    losDist;
    bool   hasLosHit;
    q19_12 distToPlayer;
    bool   hasLosToPlayer;
    bool   cond;
    s32    var_a1;
    s32    i;
    q19_12 distToPlayerMax;

    if (groanerProps.flags.val16[0] & GroanerFlag_1)
    {
        return;
    }

    if (groanerProps.flags.val16[0] & GroanerFlag_8)
    {
        groanerProps.timer_104          = Q12(0.0f);
        groanerProps.flags.val16[0] |= GroanerFlag_8;
    }

    distToPlayer    = Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx - groaner->position.vx,
                                          g_SysWork.playerWork.player.position.vz - groaner->position.vz);
    distToPlayerMax = Rng_GenerateInt(Q12(4.0f), Q12(8.0f) - 1);
    hasLosToPlayer  = Ray_NpcToPlayerLosCheck(groaner, &g_SysWork.playerWork.player);
    if (distToPlayer < distToPlayerMax && !hasLosToPlayer)
    {
        groanerProps.angleToTarget = Math_AngleBetweenPositionsGet(groaner->position, g_SysWork.playerWork.player.position);
    }
    else
    {
        losDist   = Q12(0.9f) - Rng_GenerateInt(Q12(0.0f), Q12(0.2247f));
        hasLosHit = Ray_CharaLosHitCheck(groaner, losDist, groaner->rotation.vy);

        if ((groanerProps.timer_104 >= Q12(0.0f) && ((hasLosHit && (hasLosToPlayer || distToPlayer < losDist)) ||
             groanerProps.timer_104 == Q12(0.0f))) ||
            !Rng_GenerateUInt(0, 31))
        {
            if (hasLosHit)
            {
                var_a1 = losDist + Rng_GenerateInt(Q12(0.0f), (losDist >> 2) - 1);
            }
            else
            {
                var_a1 = Rng_GenerateInt(Q12(1.5f), Q12(1.875f) - 1);
            }

            headingAngle = Chara_HeadingAngleGet(groaner, var_a1, groanerProps.targetPositionX, groanerProps.targetPositionZ,
                                                 Q12_ANGLE(360.0f), true);
            if (headingAngle == Q12_ANGLE(360.0f))
            {
                headingAngle = func_8006F99C(groaner, (losDist * 3) >> 2, groaner->rotation.vy);
            }

            if (hasLosHit)
            {
                groanerProps.timer_104 = -(Rng_GenerateInt(Q12(0.375f), Q12(0.75f) - 1));
            }
            else
            {
                groanerProps.timer_104 = Rng_GenerateInt(Q12(0.375f), Q12(1.5f) - 1);
            }

            groanerProps.angleToTarget = headingAngle;
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
        angle0 = Math_AngleNormalizeSigned(groanerProps.angleToTarget - groaner->rotation.vy);

        if (((g_DeltaTime >> 3) + 1) < ABS(angle0))
        {
            if (angle0 > Q12_ANGLE(0.0f))
            {
                groaner->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
            else
            {
                groaner->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
        }
        else
        {
            groaner->rotation.vy = groanerProps.angleToTarget;
        }
    }

    angleDeltaToTarget = Math_AngleNormalizeSigned(groanerProps.angleToTarget - groaner->rotation.vy);
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

    if (cond && !hasLosToPlayer)
    {
        if (!Chara_HasFlag(&g_SysWork.playerWork.player, CharaFlag_Unk4) &&
            !(g_SysWork.charaGroupFlags[3] & CharaGroupFlag_1) &&
            g_SysWork.playerWork.player.health > Q12(0.0f) &&
            g_SysWork.sysState == 0 &&
            (groaner->position.vy - g_SysWork.playerWork.player.position.vy) > Q12(-0.8f))
        {
            if (groaner->position.vy - g_SysWork.playerWork.player.position.vy < Q12(0.8f))
            {
                if (ABS(Math_AngleNormalizeSigned(ratan2(g_SysWork.playerWork.player.position.vx - groaner->position.vx,
                                                         g_SysWork.playerWork.player.position.vz - groaner->position.vz) -
                                                  groaner->rotation.vy)) < Q12_ANGLE(30.0f))
                {
                    g_SysWork.charaGroupFlags[3] |= CharaGroupFlag_1;
                    groaner->model.controlState   = GroanerControl_3;
                    groaner->model.anim.status    = ANIM_STATUS(GroanerAnim_15, false);
                    return;
                }
            }
        }
    }

    if (distToPlayer < Q12(1.2f))
    {
        if (Chara_HasFlag(&g_SysWork.playerWork.player, CharaFlag_Unk4) ||
            (g_SysWork.charaGroupFlags[3] & CharaGroupFlag_1) ||
            g_SysWork.playerWork.player.health <= Q12(0.0f) ||
            g_SysWork.sysState != 0 ||
            !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
        {
            groaner->model.controlState = GroanerControl_4;
            return;
        }
    }

    if (!(groanerProps.flags.val16[0] & GroanerFlag_7) &&
        (distToPlayer > Q12(12.0f) || (!Rng_GenerateUInt(0, 127) && distToPlayer > Q12(6.0f))))
    {
        groaner->model.controlState = GroanerControl_1;
        groaner->model.anim.status  = ANIM_STATUS(GroanerAnim_17, false);
        groanerProps.relKeyframeIdx_100 = 100;
        groanerProps.flags.val16[0] &= ~GroanerFlag_10;
    }
}

void sharedFunc_800E4830_2_s00(s_SubCharacter* groaner)
{
    VECTOR3 newPos; // Q19.12
    q3_12   angleDeltaToPlayer0;
    q3_12   angleDeltaToPlayer1;
    s32     temp_a2;
    q19_12  distToPlayer;
    q19_12  deltaX;
    q19_12  deltaZ;
    q19_12  deltaY;
    q19_12  unkAngle;
    q19_12  rotMax;
    s32     var_v0;
    s32     temp1;
    s32     temp2;

    // TODO: Use macro.
    deltaX       = Q12_TO_Q6(g_SysWork.playerWork.player.position.vx - groaner->position.vx);
    deltaZ       = Q12_TO_Q6(g_SysWork.playerWork.player.position.vz - groaner->position.vz);
    distToPlayer = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    angleDeltaToPlayer0 = Math_AngleNormalizeSigned(Math_AngleBetweenPositionsGet(groaner->position, g_SysWork.playerWork.player.position) -
                                        groaner->rotation.vy);

    if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) == GroanerAnim_15 ||
        ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model.anim.time, 214) < 9u)
    {
        unkAngle = TIMESTEP_ANGLE(1, 3);
        if ((angleDeltaToPlayer0 >= Q12_ANGLE(0.0f) && unkAngle <  angleDeltaToPlayer0) ||
            (angleDeltaToPlayer0 <  Q12_ANGLE(0.0f) && unkAngle < -angleDeltaToPlayer0))
        {
            if (angleDeltaToPlayer0 > Q12_ANGLE(0.0f))
            {
                groaner->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
            }
            else
            {
                groaner->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
            }

            angleDeltaToPlayer1 = Math_AngleNormalizeSigned(Math_AngleBetweenPositionsGet(groaner->position, g_SysWork.playerWork.player.position) -
                                                groaner->rotation.vy);

            rotMax = TIMESTEP_ANGLE(1, 3);
            if ((angleDeltaToPlayer1 >= Q12_ANGLE(0.0f) && rotMax <  angleDeltaToPlayer1) ||
                (angleDeltaToPlayer1 <  Q12_ANGLE(0.0f) && rotMax < -angleDeltaToPlayer1))
            {
                if (angleDeltaToPlayer1 > Q12_ANGLE(0.0f))
                {
                    groaner->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
                }
                else
                {
                    groaner->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
                }
            }
            else
            {
                groaner->rotation.vy = Math_AngleBetweenPositionsGet(groaner->position, g_SysWork.playerWork.player.position);
            }
        }
        else
        {
            groaner->rotation.vy = Math_AngleBetweenPositionsGet(groaner->position, g_SysWork.playerWork.player.position);
        }
        groaner->headingAngle = groaner->rotation.vy;
    }
    else
    {
        temp1 = groaner->rotation.vy + Q12(0.125f);
        temp2 = groaner->headingAngle + Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(67.8f));
        if (temp2 < temp1)
        {
            groaner->headingAngle += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(67.8f));
        }
        else
        {
            groaner->headingAngle = groaner->rotation.vy + Q12(0.125f);
        }
    }

    if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) == GroanerAnim_15)
    {
        Chara_MoveSpeedUpdate3(groaner, Q12(9.5f), Q12(0.0f));
    }
    else if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) == GroanerAnim_10)
    {
        if (!(groanerProps.flags.val16[0] & GroanerFlag_9))
        {
            groanerProps.flags.val16[0] |= GroanerFlag_9;
            var_v0                       = g_SysWork.playerWork.player.collision.cylinder.field_2 + 573;
            var_v0                       = (distToPlayer - var_v0) << 1;
            groaner->moveSpeed           = MIN(var_v0, Q12(4.5f));

            deltaY                    = g_SysWork.playerWork.player.position.vy - groaner->position.vy;
            groaner->field_44.field_0 = 1;
            groanerProps.field_10F    = 2;
            groaner->fallSpeed        = Q12_MULT_PRECISE(deltaY - Q12(1.4f), Q12(2.35f));
        }
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model.anim.time, 222)) < 2u)
    {
        newPos.vx = groaner->position.vx + groaner->collision.shapeOffsets.cylinder.vx;
        newPos.vy = groaner->position.vy - Q12(0.8f);
        newPos.vz = groaner->position.vz + groaner->collision.shapeOffsets.cylinder.vz;
        func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Hold), groaner, &newPos, &g_SysWork.playerWork.player, groaner->rotation.vy, Q12_ANGLE(90.0f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model.anim.time, 222)) < 14u)
    {
        groaner->fallSpeed += g_GravitySpeed;

        Chara_MoveSpeedUpdate3(groaner, Q12(0.3f), Q12(0.0f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model.anim.time, 236)) < 7u)
    {
        Chara_MoveSpeedUpdate3(groaner, Q12(1.2f), Q12(0.0f));
    }

    if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) == GroanerAnim_16)
    {
        groaner->model.controlState = GroanerControl_4;
        groaner->rotation.vy       += Q12(0.125f);
        groanerProps.angle_EC += Q12(0.125f);
        g_SysWork.charaGroupFlags[3] &= ~CharaGroupFlag_1;

        Character_AnimSet(groaner, ANIM_STATUS(GroanerAnim_16, true), 363);
        groanerProps.flags.val16[0] &= ~GroanerFlag_9;
    }
}

void sharedFunc_800E4E84_2_s00(s_SubCharacter* groaner)
{
    s32    temp_a3;
    s32    distMax;
    bool   hasLosHit;
    q19_12 distToPlayer;
    q19_12 var_s0_2;
    s32    i;

    if (groanerProps.flags.val16[0] & GroanerFlag_1)
    {
        return;
    }

    if (!(groanerProps.flags.val16[0] & GroanerFlag_8))
    {
        groanerProps.field_108          = 0;
        groanerProps.timer_104          = Q12(0.0f);
        groanerProps.flags.val16[0] |= GroanerFlag_8;
    }

    hasLosHit = Ray_CharaLosHitCheck(groaner, Q12(0.9f) - Rng_GenerateInt(Q12(0.0f), Q12(0.2247f)), groaner->rotation.vy);

    if (groanerProps.timer_104 == Q12(0.0f) || !Rng_GenerateUInt(0, 31) || // 1 in 32 chance.
        (hasLosHit && groanerProps.timer_104 >= Q12(0.0f)))
    {
        distMax = Q12(1.5f) - Rng_GenerateInt(Q12(0.0f), Q12(0.3748f));
        groanerProps.angleToTarget = Chara_HeadingAngleGet(groaner, distMax, groanerProps.targetPositionX,
                                                           groanerProps.targetPositionZ, Q12(1.0f), false);
        if (groanerProps.angleToTarget == Q12_ANGLE(360.0f))
        {
            groanerProps.angleToTarget = func_8006F99C(groaner, (distMax * 3) >> 2, groaner->rotation.vy);
        }

        if (hasLosHit)
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
        temp_a3 = Math_AngleNormalizeSigned((groanerProps.angleToTarget - groaner->rotation.vy));
        if (((g_DeltaTime >> 3) + 1) < ABS(temp_a3))
        {
            if (temp_a3 > Q12_ANGLE(0.0f))
            {
                groaner->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
            else
            {
                groaner->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
        }
        else
        {
            groaner->rotation.vy = groanerProps.angleToTarget;
        }
    }

    temp_a3 = Math_AngleNormalizeSigned(groanerProps.angleToTarget - groaner->rotation.vy);

    if (groanerProps.timer_104 >= Q12(0.0f))
    {
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)));
    }
    else
    {
        temp_a3 = Q12(1.0f) - (((temp_a3 - 227) * 3) >> 1);
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(temp_a3, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f))));
    }

    var_s0_2                = 0;
    groanerProps.field_108 += g_DeltaTime;

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

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx - groaner->position.vx,
                                       g_SysWork.playerWork.player.position.vz - groaner->position.vz);
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
        groaner->model.controlState = GroanerControl_2;
    }
}

void sharedFunc_800E554C_2_s00(s_SubCharacter* groaner)
{
    if (!(groanerProps.flags.val16[0] & GroanerFlag_1) &&
        groaner->model.anim.status == ANIM_STATUS(GroanerAnim_9, true) &&
        !Rng_GenerateInt(0, 7)) // 1 in 8 chance.
    {
        groaner->model.controlState = GroanerControl_1;
        groaner->model.anim.status  = ANIM_STATUS(GroanerAnim_17, false);
    }
}

void sharedFunc_800E55B0_2_s00(s_SubCharacter* groaner)
{
    q3_12  timeScaled;
    s32    animTime;
    u32    animIdx;
    u8     newAnimStatus;

    if (!(groanerProps.flags.val16[0] & GroanerFlag_1))
    {
        Chara_MoveSpeedUpdate(groaner, Q12(1.8f));
    }

    if (!(groanerProps.flags.val16[0] & GroanerFlag_2))
    {
        groanerProps.flags.val16[0] &= ~GroanerFlag_4;
    }

    if (groaner->model.controlState == GroanerControl_6)
    {
        if (ANIM_TIME_RANGE_CHECK(groaner->model.anim.time, 39, 48))
        {
            groanerProps.flags.val16[0] |= GroanerFlag_4;
        }

        if (groanerProps.flags.val16[0] & GroanerFlag_4)
        {
            // TODO: Uncleanr float.
            if (groanerProps.flags.val16[0] & GroanerFlag_5)
            {
                timeScaled = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 5.3333f);
            }
            else
            {
                timeScaled = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 3.2188f);
            }

            groanerProps.field_F0 = FP_FROM(timeScaled * Math_Sin(groaner->rotation.vy + Q12_ANGLE(180.0f)), Q12_SHIFT);
            groanerProps.field_F2 = FP_FROM(timeScaled * Math_Cos(groaner->rotation.vy + Q12_ANGLE(180.0f)), Q12_SHIFT);
        }

        if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) != GroanerAnim_4)
        {
            return;
        }
    }
    else
    {
        animTime = FP_FROM(groaner->model.anim.time, Q12_SHIFT);
        if ((animTime >= 134 && animTime < 157) ||
            (animTime >= 288 && animTime < 311))
        {
            groanerProps.flags.val16[0] |= GroanerFlag_4;
        }

        if (groanerProps.flags.val16[0] & GroanerFlag_4)
        {
            if (groanerProps.flags.val16[0] & GroanerFlag_5)
            {
                timeScaled = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 1.6954f);
            }
            else
            {
                timeScaled = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.9781f);
            }

            if (groaner->model.controlState == GroanerControl_7)
            {
                groanerProps.field_F0 = Q12_MULT(timeScaled, Math_Sin(groaner->rotation.vy - Q12_ANGLE(90.0f)));
                groanerProps.field_F2 = Q12_MULT(timeScaled, Math_Cos(groaner->rotation.vy - Q12_ANGLE(90.0f)));

                if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) != GroanerAnim_8)
                {
                    return;
                }
            }
            else
            {
                groanerProps.field_F0 = Q12_MULT(timeScaled, Math_Sin(groaner->rotation.vy + Q12_ANGLE(90.0f)));
                groanerProps.field_F2 = Q12_MULT(timeScaled, Math_Cos(groaner->rotation.vy + Q12_ANGLE(90.0f)));

                if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) != GroanerAnim_14)
                {
                    return;
                }
            }
        }
    }

    if (!(groanerProps.flags.val16[0] & GroanerFlag_2) && groaner->health == Q12(0.0f))
    {
        animIdx        = ANIM_STATUS_IDX_GET(groaner->model.anim.status);
        newAnimStatus  = ANIM_STATUS((animIdx == GroanerAnim_4) ? GroanerAnim_1 : GroanerAnim_Still, false);
        groaner->flags &= ~CharaFlag_Unk2;

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
            groaner->model.anim.status  = newAnimStatus;
            groaner->model.controlState = GroanerControl_9;
        }
    }
}

void sharedFunc_800E5930_2_s00(s_SubCharacter* groaner)
{
    s32 newAnimStatus;
    u32 animStatus;

    if (!(groanerProps.flags.val16[0] & GroanerFlag_1))
    {
        Chara_MoveSpeedUpdate(groaner, Q12(1.8f));
    }

    if (groaner->health == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx != Chara_NpcIdxGet(groaner))
        {
            groaner->health  = NO_VALUE;
            groaner->collision.state = 0;
        }
    }

    if (!(groanerProps.flags.val32 & (GroanerFlag_2 | GroanerFlag_6)) &&
        groaner->moveSpeed == Q12(0.0f))
    {
        animStatus    = ANIM_STATUS_IDX_GET(groaner->model.anim.status);
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
            groanerProps.flags.val16[0] |= GroanerFlag_6;
        }
    }
}

void sharedFunc_800E5AA4_2_s00(s_SubCharacter* groaner)
{
    s_CollisionResult collResult;
    q3_12             angleDeltaToHeading;

    if (groaner->model.anim.status != ANIM_STATUS(GroanerAnim_10, true))
    {
        groaner->fallSpeed += g_GravitySpeed;
    }
    else
    {
        groaner->fallSpeed += g_GravitySpeed >> 1;
    }

    if (groanerProps.flags.val16[0] & GroanerFlag_1)
    {
        if (!(groanerProps.flags.val16[0] & GroanerFlag_2))
        {
            if (groaner->model.anim.status == ANIM_STATUS(GroanerAnim_16, true))
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
            angleDeltaToHeading = Math_AngleNormalizeSigned((groaner->headingAngle - groaner->rotation.vy) + Q12_ANGLE(180.0f));
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

            if (Math_AngleNormalizeSigned(groaner->headingAngle - (groaner->rotation.vy + angleDeltaToHeading)) > Q12_ANGLE(0.0f))
            {
                groaner->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, groanerProps.field_FE);

                if (Math_AngleNormalizeSigned(groaner->headingAngle - (groaner->rotation.vy + angleDeltaToHeading)) <= Q12_ANGLE(0.0f))
                {
                    groanerProps.field_FE = Q12(0.0f);
                    groaner->rotation.vy = groaner->headingAngle - angleDeltaToHeading;
                }
            }
            else
            {
                groaner->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, groanerProps.field_FE);

                if (Math_AngleNormalizeSigned(groaner->headingAngle - (groaner->rotation.vy + angleDeltaToHeading)) >= Q12_ANGLE(0.0f))
                {
                    groanerProps.field_FE = Q12(0.0f);
                    groaner->rotation.vy = groaner->headingAngle - angleDeltaToHeading;
                }
            }

            groanerProps.field_FE = CLAMP_LOW(groanerProps.field_FE - FP_MULTIPLY_PRECISE(g_DeltaTime,
                                                                                          Q12(1.0f / 3.0f),
                                                                                          Q12_SHIFT),
                                              Q12(0.0f));
        }
        else if (groaner->moveSpeed < Q12(0.225f))
        {
            groanerProps.flags.val16[0] &= ~GroanerFlag_1;
        }
    }
    else if (groaner->model.anim.status != ANIM_STATUS(GroanerAnim_10, true))
    {
        groaner->headingAngle = groaner->rotation.vy;
    }

    func_8005CB20(groaner, &collResult, groanerProps.field_F0, groanerProps.field_F2);

    groanerProps.field_F2 = Q12(0.0f);
    groanerProps.field_F0 = Q12(0.0f);

    if (groaner->position.vy == collResult.field_C)
    {
        groanerProps.flags.val16[0] &= ~GroanerFlag_2;
    }
    else
    {
        groanerProps.flags.val16[0] |= GroanerFlag_2;
    }
}

void sharedFunc_800E5EC4_2_s00(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
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

    switch (groaner->model.anim.status)
    {
        case ANIM_STATUS(GroanerAnim_10, true):
            if (ANIM_TIME_RANGE_CHECK(groaner->model.anim.time, 207, 219))
            {
                GROANER_ANIM_INFOS[groaner->model.anim.status].duration.constant = Q12(24.0f);
            }

            if (ANIM_TIME_RANGE_CHECK(groaner->model.anim.time, 220, 225))
            {
                GROANER_ANIM_INFOS[groaner->model.anim.status].duration.constant = Q12(24.0f);
            }

            if (ANIM_TIME_RANGE_CHECK(groaner->model.anim.time, 226, 243))
            {
                GROANER_ANIM_INFOS[groaner->model.anim.status].duration.constant = Q12(30.0f);
            }
            break;

        case ANIM_STATUS(GroanerAnim_3, true):
            if (groanerProps.flags.val16[0] & GroanerFlag_5)
            {
                GROANER_ANIM_INFOS[groaner->model.anim.status].duration.constant = Q12(32.0f);
            }
            else
            {
                GROANER_ANIM_INFOS[groaner->model.anim.status].duration.constant = Q12(25.75f);
            }
            break;

        case ANIM_STATUS(GroanerAnim_7, true):
        case ANIM_STATUS(GroanerAnim_13, true):
            if (groanerProps.flags.val16[0] & GroanerFlag_5)
            {
                GROANER_ANIM_INFOS[groaner->model.anim.status].duration.constant = Q12(30.0f);
            }
            else
            {
                GROANER_ANIM_INFOS[groaner->model.anim.status].duration.constant = Q12(22.5f);
            }
            break;

        case ANIM_STATUS(GroanerAnim_16, true):
            if (groanerProps.angle_EC == groaner->rotation.vy)
            {
                constantDur = groaner->moveSpeed;
            }
            else
            {
                if (groaner->moveSpeed >= Q12(1.0f))
                {
                    constantDur = groaner->moveSpeed;
                }
                else
                {
                    constantDur = Q12(1.0f);
                }
            }

            constantDur                                                      = Q12_DIV(constantDur * 20, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)));
            GROANER_ANIM_INFOS[groaner->model.anim.status].duration.constant = constantDur;
            break;
    }

    Math_MatrixTransform(&groaner->position, (SVECTOR*)&groaner->rotation, boneCoords);

    animInfo = &GROANER_ANIM_INFOS[groaner->model.anim.status];
    animInfo->playbackFunc(&groaner->model, anmHdr, boneCoords, animInfo);

    ptr = PSX_SCRATCH;

    switch (groaner->model.anim.status)
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

    angleDeltaToTarget = Math_AngleNormalizeSigned(groanerProps.angle_EC - groaner->rotation.vy);
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
    MulMatrix(&boneCoords[3].coord, &ptr->field_8);
    MulMatrix(&boneCoords[4].coord, &ptr->field_8);

    *(s32*)&ptr->field_0.vx = groanerProps.field_EE << 16;
    ptr->field_0.vz         = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_0, &ptr->field_8);
    MulMatrix(&boneCoords[1].coord, &ptr->field_8);

    groaner->rotation.vy = Math_AngleNormalizeSigned(groaner->rotation.vy);
    groanerProps.angle_EC = groaner->rotation.vy;
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

#define ANIM_INDEX_FROM_KEYFRAME(offset, keyframe, max, count) \
    ((offset) - ((keyframe) > (count)) < (max) ? ((offset) - ((keyframe) > (count))) : ((max) - 1))

void sharedFunc_800E6338_2_s00(s_SubCharacter* groaner)
{
    s32 keyframeIdx2;
    s32 keyframeIdx1;
    s32 keyframeIdx0;
    s32 temp;

    switch (groaner->model.anim.status)
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
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 191;
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
            keyframeIdx2 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 371;

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
                keyframeIdx0 = (keyframeIdx2 - 14) - !(keyframeIdx2 < 24);
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
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 16;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 10);
            keyframeIdx1 = (keyframeIdx2 - !(keyframeIdx2 < 9)) - !(keyframeIdx2 < 19);
            func_80070400(groaner, &sharedData_800EF368_2_s00[keyframeIdx0], &sharedData_800EF368_2_s00[keyframeIdx1]);

            groanerProps.relKeyframeIdx_100 = 5;
            break;

        case ANIM_STATUS(GroanerAnim_6, false):
            CopyData(groaner, sharedData_800EF4D0_2_s00[2]);
            break;

        case ANIM_STATUS(GroanerAnim_6, true):
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 111;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 11);
            keyframeIdx1 = keyframeIdx2 - !(keyframeIdx2 < 10);
            func_80070400(groaner, &sharedData_800EF4D0_2_s00[keyframeIdx0], &sharedData_800EF4D0_2_s00[keyframeIdx1]);

            groanerProps.relKeyframeIdx_100 = 13;
            break;

        case ANIM_STATUS(GroanerAnim_12, false):
            CopyData(groaner, sharedData_800EF638_2_s00[3]);
            break;

        case ANIM_STATUS(GroanerAnim_12, true):
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 265;
            keyframeIdx0 = (keyframeIdx2 - !(keyframeIdx2 < 9));
            keyframeIdx1 = (FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 264) - !(keyframeIdx2 < 8);
            func_80070400(groaner, &sharedData_800EF638_2_s00[keyframeIdx0], &sharedData_800EF638_2_s00[keyframeIdx1]);

            groanerProps.relKeyframeIdx_100 = 25;
            break;

        case ANIM_STATUS(GroanerAnim_3, false):
            CopyData(groaner, sharedData_800EF7B4_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_3, true):
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 37;
            keyframeIdx0 = ((FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 39) - !(keyframeIdx2 < 17)) - !(keyframeIdx2 < 38);
            keyframeIdx1 = (((FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 38) - !(keyframeIdx2 < 16)) - !(keyframeIdx2 < 37)) - !(keyframeIdx2 < 39);
            func_80070400(groaner, &sharedData_800EF7B4_2_s00[keyframeIdx0], &sharedData_800EF7B4_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_7, false):
            CopyData(groaner, sharedData_800EFA84_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_7, true):
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 131;
            keyframeIdx0 = (FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 134) - !(keyframeIdx2 < 31);
            keyframeIdx1 = (FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 133) - !(keyframeIdx2 < 30);
            func_80070400(groaner, &sharedData_800EFA84_2_s00[keyframeIdx0], &sharedData_800EFA84_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_13, false):
            CopyData(groaner, sharedData_800EFCDC_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_13, true):
            keyframeIdx2 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 285;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 31);
            keyframeIdx1 = (keyframeIdx2 - !(keyframeIdx2 < 30)) - !(keyframeIdx2 < 32);
            func_80070400(groaner, &sharedData_800EFCDC_2_s00[keyframeIdx0], &sharedData_800EFCDC_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_4, false):
            CopyData(groaner, sharedData_800EFF48_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_4, true):
            keyframeIdx2 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 78;
            keyframeIdx0 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 82;

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
                    if ((keyframeIdx2 - 1) < 6)
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
            keyframeIdx2 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 165;
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
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 319;
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
            keyframeIdx0 = FP_FROM(groaner->model.anim.time, Q12_SHIFT);
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
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 94;
            keyframeIdx0 = (keyframeIdx2 - !(keyframeIdx2 < 13)) - !(keyframeIdx2 < 15);
            keyframeIdx1 = (((FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 93) - !(keyframeIdx2 < 12)) - !(keyframeIdx2 < 14)) - !(keyframeIdx2 < 15);
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
            keyframeIdx2 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 244;
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
            keyframeIdx0 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 363;
            func_80070400(groaner, &sharedData_800EF1B0_2_s00[keyframeIdx0], &sharedData_800EF1B0_2_s00[(FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 362) & 0x7]);
            break;

        case ANIM_STATUS(GroanerAnim_15, false):
            CopyData(groaner, sharedData_800EF0AC_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_15, true):
            keyframeIdx2      = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 346;
            keyframeIdx0 = (((keyframeIdx2 - !(keyframeIdx2 < 3)) - !(keyframeIdx2 < 9)) - !(keyframeIdx2 < 12)) - !(keyframeIdx2 < 13);
            keyframeIdx1 = ((((FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 345) - !(keyframeIdx2 < 2)) - !(keyframeIdx2 < 8)) - !(keyframeIdx2 < 11)) - !(keyframeIdx2 < 12);
            func_80070400(groaner, &sharedData_800EF0AC_2_s00[keyframeIdx0], &sharedData_800EF0AC_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_10, false):
            func_80070400(groaner, &sharedData_800EF19C_2_s00, &sharedData_800EEE54_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_10, true):
            keyframeIdx0 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 214;
            keyframeIdx1 = FP_FROM(groaner->model.anim.time, Q12_SHIFT) - 213;
            func_80070400(groaner, &sharedData_800EEE54_2_s00[keyframeIdx0], &sharedData_800EEE54_2_s00[keyframeIdx1]);

            groaner->collision.box.field_8 = Q12(-0.8f);
            break;
    }

    func_8005C814(&groaner->collision.shapeOffsets, groaner);
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
            func_8005DC1C(Sfx_Unk1411, &groaner->position, Q8(0.5f), 0);
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

                if (groaner->health > Q12(0.0f) &&
                    (groanerProps.flags.val32 & (GroanerFlag_3 | GroanerFlag_12)) == GroanerFlag_3)
                {
                    func_8005DC1C(Sfx_Unk1409, &groaner->position, Q8(0.5f), 0);
                }
                else
                {
                    func_8005DC1C(Sfx_Unk1414, &groaner->position, Q8(0.5f), 0);
                }

                groanerProps.flags.val16[0] &= ~GroanerFlag_12;
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
                (groaner->health > Q12(0.0f)))
            {
                if (groaner->model.anim.status == 33)
                {
                    func_8005DC1C(Sfx_Unk1410, &groaner->position, Q8(0.25f), 0);
                    groanerProps.timer_10C = Rng_GenerateInt(Q12(0.5f), Q12(0.6f) - 1);
                    groanerProps.field_10E = 3;
                }
                else if (ANIM_STATUS_IDX_GET(groaner->model.anim.status) != GroanerAnim_10 &&
                         ANIM_STATUS_IDX_GET(groaner->model.anim.status) != GroanerAnim_15 &&
                         !Rng_GenerateUInt(0, 15))
                {
                    func_8005DC1C(Sfx_Unk1406, &groaner->position, (Q12_DIV(groaner->health, Q12(280.0f)) >> 7) + 32, 0);
                    groanerProps.timer_10C = Rng_GenerateInt(Q12(4.8f), Q12(8.0f) - 2);
                    groanerProps.field_10E = 1;
                }
            }
            break;
    }

    groanerProps.field_10F = 0;

    keyframeIdx = FP_FROM(groaner->model.anim.time, Q12_SHIFT);
    sfxVol      = (Q12_DIV(groaner->moveSpeed, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f))) >> 6) + 64;
    sfxPitch    = (Q12_DIV(groaner->moveSpeed, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f))) >> 7) + Rng_GenerateUInt(0, 7);

    if ((keyframeIdx > 365 && keyframeIdx < 370) ||
        (keyframeIdx > 374 && keyframeIdx < 382))
    {
        if (groanerProps.field_110 == 0)
        {
            func_8005DD44(Sfx_Unk1413, &groaner->position, sfxVol, sfxPitch);
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
        if (!groanerProps.field_111)
        {
            func_8005DD44(Sfx_Unk1413, &groaner->position, sfxVol, sfxPitch);
            groanerProps.field_111++;
        }
    }
    else
    {
        groanerProps.field_111 = false;
    }
}

#undef groanerProps

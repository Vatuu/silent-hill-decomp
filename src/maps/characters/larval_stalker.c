#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/larval_stalker.h"

#define larvalStalkerProps larvalStalker->properties_E4.larvalStalker

void Ai_LarvalStalker_Update(s_SubCharacter* larvalStalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s8* mapOverlayPtr;

    // Initialize.
    if (larvalStalker->model_0.controlState_2 == LarvalStalkerControl_None)
    {
        Ai_LarvalStalker_Init(larvalStalker);
    }

    sharedFunc_800D17BC_1_s00(larvalStalker);
    Ai_LarvalStalker_ControlUpdate(larvalStalker);
    sharedFunc_800D140C_1_s00(larvalStalker, coords);
    sharedFunc_800D1524_1_s00(larvalStalker, anmHdr, coords);
    sharedFunc_800D1DBC_1_s00(larvalStalker);

    if (larvalStalkerProps.timer_10A < Q12(3.5f))
    {
        return;
    }

    larvalStalker->timer_C6 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
    if (larvalStalker->timer_C6 <= Q12(1.0f))
    {
        return;
    }

    // TODO: Weird hack, or a drunk developer.
    mapOverlayPtr = &g_SavegamePtr->mapOverlayId_A4;

    larvalStalker->timer_C6               = Q12(1.0f);
    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_1;

    if (*mapOverlayPtr == 37 || !Rng_GenerateInt(0, 3)) // 1 in 4 chance.
    {
        Savegame_EnemyStateUpdate(larvalStalker);
    }
}

#define Chara_TurnModulate(angle, limit, mult)                                    \
    angleDeltaToPlayer = angle;                                                   \
                                                                                  \
    if (limit <= ABS(angleDeltaToPlayer))                                         \
    {                                                                             \
        if ((angleDeltaToPlayer) > Q12_ANGLE(0.0f))                               \
        {                                                                         \
            larvalStalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, mult); \
        }                                                                         \
        else                                                                      \
        {                                                                         \
            larvalStalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, mult); \
        }                                                                         \
    }

#define Chara_TurnModulate_REV(angle, limit, mult)                                \
    if (limit <= ABS(angle))                                                      \
    {                                                                             \
        if ((angle) < Q12_ANGLE(0.0f))                                            \
        {                                                                         \
            larvalStalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, mult); \
        }                                                                         \
        else                                                                      \
        {                                                                         \
            larvalStalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, mult); \
        }                                                                         \
    }

#define ANIM_STUFF(mult, div)                                                                                                     \
    temp = Q12_MULT_PRECISE(LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime) * \
           mult / div;                                                                                                            \
    larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(larvalStalker->rotation_24.vy), Q12_SHIFT);                            \
    larvalStalkerProps.angle_102 = FP_FROM(temp * Math_Cos(larvalStalker->rotation_24.vy), Q12_SHIFT);

void Ai_LarvalStalker_ControlUpdate(s_SubCharacter* larvalStalker)
{
    s32     temp;
    VECTOR3 pos;
    q19_12  distToTarget;
    s32     validStep;
    s32     idxInfo;
    q19_12  distStep;
    q19_12  baseDistMax;
    q19_12  angleDeltaToPlayer;
    q19_12  sinRotY;
    q19_12  cosRotY;
    q19_12  targetX;
    q19_12  targetZ;

    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(larvalStalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       larvalStalker->rotation_24.vy);
    distToTarget       = Math_Vector2MagCalc(larvalStalkerProps.targetPositionX - larvalStalker->position_18.vx,
                                             larvalStalkerProps.targetPositionZ - larvalStalker->position_18.vz);

    larvalStalker->rotation_24.vy = func_8005BF38(larvalStalker->rotation_24.vy);

    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != LarvalStalkerAnim_1)
    {
        larvalStalker->field_44.field_0 = 0;
    }

    idxInfo = g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1));
    if (idxInfo == 0)
    {
        baseDistMax = Q12(2.5f);
        distStep = Q12(8.0f);
    }
    else if (idxInfo == 2)
    {
        baseDistMax = Q12(3.5f);
        distStep = Q12(10.0f);
    }
    else
    {
        baseDistMax = Q12(0.5f);
        distStep = Q12(1.5f);
    }

    if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - larvalStalker->position_18.vx,
                            g_SysWork.playerWork_4C.player_0.position_18.vz - larvalStalker->position_18.vz) < ((baseDistMax * 2) + distStep))
    {
        larvalStalkerProps.targetPositionX = g_SysWork.playerWork_4C.player_0.position_18.vx;
        larvalStalkerProps.targetPositionZ = g_SysWork.playerWork_4C.player_0.position_18.vz;
    }

    // Handle control state.
    switch (larvalStalker->model_0.controlState_2)
    {
        case LarvalStalkerControl_1:
            larvalStalker->moveSpeed_38 = Q12(0.0f);

            if (!Rng_GenerateInt(0, 31)) // 1 in 32 chance.
            {
                larvalStalker->health_B0 = NO_VALUE;
            }
            break;

        case LarvalStalkerControl_2:
            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(0.3f));

            if (func_80070184(larvalStalker, Q12(1.0f), larvalStalker->rotation_24.vy) || !Rng_GenerateInt(0, 63)) // 1 in 64 chance.
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_3;
            }

            if (func_8006FD90(larvalStalker, 3, baseDistMax, distStep))
            {
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_7;
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_2;
            }
            break;

        case LarvalStalkerControl_3:
            Chara_MoveSpeedUpdate(larvalStalker, Q12(1.5f));

            if (larvalStalker->model_0.anim_4.status_0 == ANIM_STATUS(LarvalStalkerAnim_11, true))
            {
                if (larvalStalkerProps.angle_108 > Q12_ANGLE(0.0f))
                {
                    larvalStalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
                    larvalStalkerProps.angle_108  -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));

                    if ((larvalStalkerProps.angle_108) <= Q12_ANGLE(0.0f))
                    {
                        larvalStalkerProps.angle_108 = Q12_ANGLE(0.0f);
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                    }
                }
                else if (larvalStalkerProps.angle_108 < Q12_ANGLE(0.0f))
                {
                    larvalStalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
                    larvalStalkerProps.angle_108  += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));

                    if (!(larvalStalkerProps.angle_108 < Q12_ANGLE(0.0f)))
                    {
                        larvalStalkerProps.angle_108 = Q12_ANGLE(0.0f);
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                    }
                }
                else
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                }
            }

            if (larvalStalker->model_0.anim_4.status_0 == ANIM_STATUS(LarvalStalkerAnim_10, true))
            {
                validStep = func_80070184(larvalStalker, Q12(0.6f), larvalStalker->rotation_24.vy);
                if ((validStep && !Rng_GenerateInt(0, 3)) || // 1 in 4 chance.
                    !Rng_GenerateInt(0, 31))                 // 1 in 32 chance.
                {
                    larvalStalkerProps.angle_108           = Rng_GenerateUInt(Q12_ANGLE(-90.0f), Q12_ANGLE(90.0f) - 1); // -90 >< 90 angle.
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_11, false);
                }
                else if (!Rng_GenerateInt(0, 15)) // 1 in 16 chance.
                {
                    if (validStep == false)
                    {
                        larvalStalker->model_0.controlState_2 = LarvalStalkerControl_2;
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_11, false);
                    }
                }
            }

            if (func_8006FD90(larvalStalker, 3, baseDistMax, distStep))
            {
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_7;
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                larvalStalkerProps.angle_108 = Q12_ANGLE(0.0f);
                larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_2;
            }
            break;

        case LarvalStalkerControl_4:
            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(0.3f));

            if ((larvalStalkerProps.flags_E8 & LarvalStalkerFlag_2) &&
                ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_11 &&
                ((distToTarget < (Q12(3.5f) - FP_TO(larvalStalkerProps.field_EA, Q12_SHIFT))) || !Rng_GenerateInt(0, 31))) // 1 in 32 chance.
            {
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_7;
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_3;
                break;
            }

            if (distToTarget >= (FP_TO(larvalStalkerProps.field_EA, Q12_SHIFT) + Q12(2.0f)) ||
                g_SysWork.playerWork_4C.player_0.moveSpeed_38 <= ((larvalStalkerProps.field_EA * Q12(1.5f) )+ Q12(0.5f)))
            {
                if (Q12_ANGLE(45.0f) > ABS(angleDeltaToPlayer) &&
                    (distToTarget < ((larvalStalker->field_D4.radius_0 + Q12(0.05f)) + g_SysWork.playerWork_4C.player_0.field_D4.radius_0)))
                {
                    if (!Rng_GenerateInt(0, 7)) // 1 in 8 chance.
                    {
                        targetX = larvalStalkerProps.targetPositionX + Rng_GenerateInt(0, Q12(1.5f) - 1);
                        targetZ = larvalStalkerProps.targetPositionZ + Rng_GenerateInt(0, Q12(1.5f) - 1);
                        larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker, Q12(2.0f), targetX, targetZ, Q12(1.0f), true);
                        Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), Q12_ANGLE(1.5f), Q12_ANGLE(30.0f));
                    }
                    else
                    {
                        Chara_TurnModulate_REV(angleDeltaToPlayer, Q12_ANGLE(1.5f), Q12_ANGLE(30.0f));
                    }
                    break;
                }

                if ((distStep >> 1) < distToTarget)
                {
                    if (!Rng_GenerateInt(0, 31)) // 1 in 32 chance.
                    {
                        larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker, Q12(2.0f), larvalStalkerProps.targetPositionX, larvalStalkerProps.targetPositionZ, Q12(1.0f), true);
                    }

                    Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), Q12_ANGLE(1.5f), Q12_ANGLE(30.0f));
                    break;
                }

                if (larvalStalkerProps.flags_E8 & LarvalStalkerFlag_3)
                {
                    Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), Q12_ANGLE(1.5f), Q12_ANGLE(30.0f));
                    if (!Rng_GenerateInt(0, 15)) // 1 in 16 chance.
                    {
                        larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_3;
                    }
                    break;
                }

                if (!(g_SysWork.field_2284[3] & 0x1))
                {
                    Chara_TurnModulate(angleDeltaToPlayer, Q12_ANGLE(1.5f), Q12_ANGLE(30.0f));
                }
                else
                {
                    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_7;
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                }
            }
            else
            {
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_8;

                func_8005DC1C(Sfx_Unk1429, &larvalStalker->position_18, Q8(0.5f), 0);

                larvalStalkerProps.timer_EC = Q12(0.0f);
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_12, false);
                larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_3;

            }
            break;

        case LarvalStalkerControl_5:
            Chara_TurnModulate(angleDeltaToPlayer, Q12_ANGLE(1.5f), Q12_ANGLE(30.0f));

            if (larvalStalkerProps.flags_E8 & LarvalStalkerFlag_6)
            {
                larvalStalkerProps.animTime_104 = larvalStalker->model_0.anim_4.time_4;
                larvalStalker->moveSpeed_38 = Q12(0.0f);
                larvalStalkerProps.timer_EC    += g_DeltaTime;

                if (larvalStalkerProps.timer_EC > Q12(1.8f))
                {
                    if (!Rng_GenerateInt(0, 7)) // 1 in 8 chance.
                    {
                        func_8005DC1C(0, &larvalStalker->position_18, Q8(0.5f), 0);
                        larvalStalkerProps.timer_EC = Q12(0.0f);

                        if (g_SysWork.playerWork_4C.player_0.field_40 == NO_VALUE)
                        {
                            g_SysWork.playerWork_4C.player_0.field_40 = Chara_NpcIdxGet(larvalStalker);
                        }

                        Chara_AttackReceivedSet(&g_SysWork.playerWork_4C.player_0, WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Multitap));
                        g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Multitap)].field_4, Q12_SHIFT) * ((Rng_Rand16() & 0x1F) + 0x55)) / 100;
                    }
                }

                angleDeltaToPlayer = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - larvalStalker->rotation_24.vy);
                if (Q12_ANGLE(90.0f) < ABS(angleDeltaToPlayer))
                {
                    if (distToTarget >= Q12(0.29004f))
                    {
                        sinRotY = Math_Sin(larvalStalker->rotation_24.vy);
                        larvalStalkerProps.angle_100 = ((distToTarget - Q12(0.28f)) <= Q12(0.02f)) ?
                                                       Q12_MULT(distToTarget - Q12(0.28f), sinRotY) :
                                                       Q12_MULT(Q12(0.02f), sinRotY);

                        cosRotY = Math_Cos(larvalStalker->rotation_24.vy);
                        larvalStalkerProps.angle_102 = ((distToTarget - Q12(0.28f)) <= Q12(0.02f)) ?
                                                       Q12_MULT(distToTarget - Q12(0.28f), cosRotY) :
                                                       Q12_MULT(Q12(0.02f), cosRotY);
                    }

                    if (distToTarget < Q12(0.27f))
                    {
                        larvalStalkerProps.angle_100 = Q12_MULT(((distToTarget - Q12(0.28f)) < Q12(-0.02f)) ? Q12(-0.02f) : (distToTarget - Q12(0.28f)), Math_Sin(larvalStalker->rotation_24.vy));
                        larvalStalkerProps.angle_102 = Q12_MULT(((distToTarget - Q12(0.28f)) < Q12(-0.02f)) ? Q12(-0.02f) : (distToTarget - Q12(0.28f)), Math_Cos(larvalStalker->rotation_24.vy));
                    }
                }
                else
                {
                    if (distToTarget > Q12(0.18f))
                    {
                        sinRotY = Math_Sin(larvalStalker->rotation_24.vy);
                        larvalStalkerProps.angle_100 = ((distToTarget - Q12(0.17f)) <= Q12(0.02f)) ?
                                                       Q12_MULT(distToTarget - Q12(0.17f), sinRotY) :
                                                       Q12_MULT(Q12(0.02f), sinRotY);

                        sinRotY = Math_Cos(larvalStalker->rotation_24.vy);
                        larvalStalkerProps.angle_102 = ((distToTarget - Q12(0.17f)) <= Q12(0.02f)) ?
                                                       Q12_MULT(distToTarget - Q12(0.17f), sinRotY) :
                                                       Q12_MULT(Q12(0.02f), sinRotY);
                    }

                    if (distToTarget < Q12(0.16f))
                    {
                        larvalStalkerProps.angle_100 = Q12_MULT(((distToTarget - Q12(0.17f)) < Q12(-0.02f)) ? Q12(-0.02f) : (distToTarget - Q12(0.17f)), Math_Sin(larvalStalker->rotation_24.vy));
                        larvalStalkerProps.angle_102 = Q12_MULT(((distToTarget - Q12(0.17f)) < Q12(-0.02f)) ? Q12(-0.02f) : (distToTarget - Q12(0.17f)), Math_Cos(larvalStalker->rotation_24.vy));
                    }
                }

                if (Chara_AttackReceivedGet(&g_SysWork.playerWork_4C.player_0) == NO_VALUE)
                {
                    g_SysWork.field_2284[3] &= ~(1 << 0);
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_5, false);
                    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_10;
                    larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_6;
                    larvalStalker->field_E1_0 = 3;
                    larvalStalkerProps.keyframeIdx_F4 = 0;

                    func_8005DC1C(Sfx_Unk1429, &larvalStalker->position_18, Q8(0.5f), 0);
                }
                else
                {
                    larvalStalker->field_E1_0 = 1;
                }
            }
            else
            {
                if (distToTarget < ((larvalStalker->field_D4.radius_0 + Q12(0.02f)) + g_SysWork.playerWork_4C.player_0.field_D4.radius_0))
                {
                    Chara_MoveSpeedUpdate(larvalStalker, Q12(1.5f));
                }

                pos     = larvalStalker->position_18;
                pos.vy += larvalStalker->field_C8.field_8;

                if (func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_Unk31, AttackInputType_Multitap), larvalStalker, &pos, &g_SysWork.playerWork_4C.player_0, larvalStalker->rotation_24.vy, Q12_ANGLE(90.0f)) != NO_VALUE)
                {
                    larvalStalkerProps.timer_EC = Q12(0.0f);
                    larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_6;
                }
                else if (distToTarget > Q12(0.5f))
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_11, false);
                    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_4;
                }

            }
            break;

        case LarvalStalkerControl_6:
            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(1.0f));

            if (larvalStalkerProps.timer_EC == Q12(0.0f))
            {
                larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker, Q12(2.0f), larvalStalkerProps.targetPositionX, larvalStalkerProps.targetPositionZ, Q12(1.0f), false);
                if (larvalStalkerProps.angle_108 == Q12(1.0f))
                {
                    larvalStalkerProps.angle_108 = Rng_GenerateUInt(0, Q12_ANGLE(360.0f) - 1);
                }
            }

            larvalStalkerProps.timer_EC += g_DeltaTime;
            if (larvalStalkerProps.timer_EC > Q12(0.8f))
            {
                larvalStalkerProps.timer_EC = Q12(0.0f);
            }

            Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), 33, 682);

            if (larvalStalker->moveSpeed_38 >= Q12(0.9004f) && !Rng_GenerateUInt(0, 255))
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_6, false);
                larvalStalkerProps.timer_EC = Q12(0.0f);
                larvalStalkerProps.keyframeIdx_F4 = 0;
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_9;

                func_8005DC1C(Sfx_Unk1429, &larvalStalker->position_18, Q8(0.5f), 0);
            }
            else
            {
                if ((Q12(4.8f) - (larvalStalkerProps.field_EA * Q12(1.2f))) < distToTarget && !Rng_GenerateInt(0, 31)) // 1 in 32 chance.
                {
                    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_7;
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                    larvalStalkerProps.timer_EC = Q12(0.0f);
                    larvalStalkerProps.angle_108 = Q12(0.0f);
                    larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_2;
                }
            }
            break;

        case LarvalStalkerControl_7:
            if (func_800700F8(larvalStalker, &g_SysWork.playerWork_4C.player_0) || (distStep * 2) < distToTarget)
            {
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_3;

                if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != LarvalStalkerAnim_10)
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                }
            }
            else
            {
                if (Q12_ANGLE(1.5f) <= ABS(angleDeltaToPlayer) &&
                    ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != LarvalStalkerAnim_10)
                {
                    Chara_MoveSpeedUpdate3(larvalStalker, Q12(0.375f), Q12(0.0f));

                    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != ANIM_STATUS(LarvalStalkerAnim_5, true))
                    {
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_11, false);
                    }

                    if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
                    {
                        larvalStalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
                    }
                    else
                    {
                        larvalStalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
                    }
                }
                else
                {
                    Chara_MoveSpeedUpdate(larvalStalker, Q12(1.5f));

                    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != LarvalStalkerAnim_10)
                    {
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                    }
                }

                larvalStalkerProps.timer_EC += g_DeltaTime;

                if (!(g_SysWork.field_2284[3] & 0x1) && (Q12(5.0f) - FP_TO(larvalStalkerProps.field_EA, Q12_SHIFT)) < larvalStalkerProps.timer_EC)
                {
                    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_4;
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_11, false);
                    larvalStalkerProps.timer_EC = Q12(0.0f);

                    larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_2;
                    if (larvalStalkerProps.field_EA < 2)
                    {
                        larvalStalkerProps.field_EA++;
                    }
                }
                else
                {
                    if (distToTarget < (FP_TO(larvalStalkerProps.field_EA, Q12_SHIFT) + Q12(2.0f)) &&
                        g_SysWork.playerWork_4C.player_0.moveSpeed_38 > ((larvalStalkerProps.field_EA * Q12(1.5f)) + Q12(0.5f)))
                    {
                        larvalStalker->model_0.controlState_2 = LarvalStalkerControl_8;

                        func_8005DC1C(Sfx_Unk1429, &larvalStalker->position_18, Q8(0.5f), 0);

                        larvalStalkerProps.timer_EC = Q12(0.0f);
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_12, false);
                        larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_3;
                    }
                }
            }
            break;

        case LarvalStalkerControl_8:
            larvalStalkerProps.timer_10A += Q12_MULT_PRECISE(g_DeltaTime, Rng_Rand16() & 0xFFF);
            if (larvalStalkerProps.timer_10A > Q12(3.5f))
            {
                larvalStalkerProps.timer_10A = Q12(3.5f);
            }

            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(1.0f));

            if (larvalStalkerProps.timer_EC == Q12(0.0f))
            {
                larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker, Q12(1.5f), larvalStalkerProps.targetPositionX, larvalStalkerProps.targetPositionZ, Q12(1.0f), false);
                if (larvalStalkerProps.angle_108 == Q12(1.0f))
                {
                    larvalStalkerProps.angle_108 = Rng_Rand16() & 0xFFF;
                }
            }

            larvalStalkerProps.timer_EC += g_DeltaTime;
            if (larvalStalkerProps.timer_EC > Q12(0.8f))
            {
                larvalStalkerProps.timer_EC = Q12(0.0f);
            }

            Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), Q12_ANGLE(1.5f), 682);

            if ((larvalStalker->moveSpeed_38 >= Q12(0.9004f)) && !Rng_GenerateInt(0, 63)) // 1 in 64 chance.
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_6, false);
                larvalStalkerProps.timer_EC = Q12(0.0f);
                larvalStalkerProps.keyframeIdx_F4 = 0;
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_9;

                func_8005DC1C(Sfx_Unk1429, &larvalStalker->position_18, Q8(0.5f), 0);
            }

            if (!(larvalStalkerProps.flags_E8 & LarvalStalkerFlag_7))
            {
                larvalStalkerProps.timer_F0 += g_DeltaTime;
                if (larvalStalkerProps.timer_F0 > Q12(5.0f) && !Rng_GenerateInt(0, 63)) // 1 in 64 chance.
                {
                    larvalStalkerProps.timer_F0 = Q12(0.0f);
                    larvalStalkerProps.timer_EC = Q12(0.0f);
                    larvalStalkerProps.angle_108 = Q12(0.0f);
                    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_6;
                }
            }
            break;

        case LarvalStalkerControl_9:
            larvalStalkerProps.timer_10A += Q12_MULT_PRECISE(g_DeltaTime, (Rng_Rand16() & 0x7FF) + Q12(0.5f));
            if (larvalStalkerProps.timer_10A > Q12(3.5f))
            {
                larvalStalkerProps.timer_10A = Q12(3.5f);
            }

            Chara_MoveSpeedUpdate(larvalStalker, Q12(0.5f));

            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 86, 92))
            {
                ANIM_STUFF(Q12(0.15f), Q12(6.0f));
            }

            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 95, 105))
            {
                larvalStalker->moveSpeed_38 = 0;
            }

            if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_10)
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_12, false);
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_8;
            }
            break;

        case LarvalStalkerControl_10:
            Chara_MoveSpeedUpdate(larvalStalker, Q12(1.5f));

            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 86, 92))
            {
                ANIM_STUFF(Q12(0.15f), Q12(6.0f));
            }

            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 41, 49))
            {
                temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].duration_8.constant,
                                           g_DeltaTime, Q12_SHIFT) * Q12(0.3f) / Q12(9.0f);
                larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(larvalStalker->rotation_24.vy + Q12_ANGLE(180.0f)), Q12_SHIFT);
                larvalStalkerProps.angle_102 = FP_FROM(temp * Math_Cos(larvalStalker->rotation_24.vy + Q12_ANGLE(180.0f)), Q12_SHIFT);
            }

            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 95, 96) && larvalStalker->moveSpeed_38 != Q12(0.0f))
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_16, true);
            }

            if (larvalStalker->model_0.anim_4.status_0 == ANIM_STATUS(LarvalStalkerAnim_16, true) &&
                larvalStalker->moveSpeed_38 == Q12(0.0f) && !Rng_GenerateInt(0, 7)) // 1 in 8 chance.
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_6, true);
            }

            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 61, 62) && larvalStalker->moveSpeed_38 != Q12(0.0f))
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_15, true);
            }

            if (larvalStalker->model_0.anim_4.status_0 == ANIM_STATUS(LarvalStalkerAnim_15, true) &&
                larvalStalker->moveSpeed_38 == Q12(0.0f) && !Rng_GenerateInt(0, 7)) // 1 in 8 chance.
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_5, true);
            }

            if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_10 &&
                !Rng_GenerateInt(0, 7)) // 1 in 8 chance.
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_12, false);
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_8;
                larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_1;
            }
            break;

        case LarvalStalkerControl_11:
            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 143, 151))
            {
                ANIM_STUFF(Q12(0.3f), Q12(9.0f));
            }

            if (larvalStalker->health_B0 == Q12(0.0f) && ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_9)
            {
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_13;
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_4, false);
                Savegame_EnemyStateUpdate(larvalStalker);
            }

            if (larvalStalkerProps.flags_E8 & LarvalStalkerFlag_1)
            {
                Chara_MoveSpeedUpdate(larvalStalker, Q12(1.5f));

                if (larvalStalker->moveSpeed_38 == Q12(0.0f))
                {
                    larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_1;
                }
                break;
            }

            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(0.1f));

            if (larvalStalkerProps.timer_EC == Q12(0.0f))
            {
                larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker, Q12_ANGLE(180.0f), larvalStalkerProps.targetPositionX, larvalStalkerProps.targetPositionZ, Q12(1.0f), false);
            }

            larvalStalkerProps.timer_EC += g_DeltaTime;
            if (larvalStalkerProps.timer_EC > Q12(1.0f))
            {
                larvalStalkerProps.timer_EC = Q12(0.0f);
            }

            Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), Q12_ANGLE(1.5f), 170);
            break;

        case LarvalStalkerControl_12:
            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 121, 127))
            {
                temp = (FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].duration_8.constant,
                                            g_DeltaTime,
                                            Q12_SHIFT) * Q12(0.15f)) / Q12(6.0f);
                larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(larvalStalker->rotation_24.vy + Q12_ANGLE(180.0f)), Q12_SHIFT);
                larvalStalkerProps.angle_102 = FP_FROM(temp * Math_Cos(larvalStalker->rotation_24.vy + Q12_ANGLE(180.0f)), Q12_SHIFT);
            }

            larvalStalker->flags_3E |= CharaFlag_Unk2;

            if (larvalStalker->health_B0 <= Q12(0.0f) &&
                ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_2)
            {
                larvalStalker->flags_3E &= ~CharaFlag_Unk2;
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_13;
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_3, false);
                Savegame_EnemyStateUpdate(larvalStalker);
            }

            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(0.0f));
            break;

        case LarvalStalkerControl_13:
            larvalStalker->flags_3E &= ~CharaFlag_Unk2;

            if (larvalStalker->health_B0 <= Q12(0.0f) && Chara_NpcIdxGet(larvalStalker) != g_SysWork.targetNpcIdx_2353)
            {
                larvalStalker->health_B0 = NO_VALUE;
                larvalStalker->field_E1_0 = 0;
            }

            // TODO: Weird property cast. Originally, maybe a wrong properties struct was mistakenly accessed?
            if (larvalStalker->moveSpeed_38 == Q12(0.0f) && !(*(s32*)&larvalStalkerProps.flags_E8 & (LarvalStalkerFlag_4 | LarvalStalkerFlag_5)))
            {
                if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_13)
                {
                    func_800622B8(3, larvalStalker, 3, 3);
                    larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_4;
                }
                else if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_14)
                {
                    func_800622B8(3, larvalStalker, 4, 3);
                    larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_4;
                }
            }

            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(0.0f));
            break;
    }

    Chara_DamageClear(larvalStalker);
}

void sharedFunc_800D140C_1_s00(s_SubCharacter* larvalStalker, GsCOORDINATE2* coords)
{
    s_800C4590 sp18;

    larvalStalker->fallSpeed_34 += g_GravitySpeed >> 1;

    if (!(larvalStalkerProps.flags_E8 & LarvalStalkerFlag_1))
    {
        larvalStalker->headingAngle_3C = larvalStalker->rotation_24.vy;
    }

    if (g_DeltaTime != Q12(0.0f))
    {
        func_8005CB20(larvalStalker, &sp18, larvalStalkerProps.angle_100, larvalStalkerProps.angle_102);
    }

    larvalStalkerProps.angle_102 = Q12_ANGLE(0.0f);
    larvalStalkerProps.angle_100 = Q12_ANGLE(0.0f);

    if (larvalStalker->fallSpeed_34 != Q12(0.0f))
    {
        larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_5;
    }
    else
    {
        larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_5;
    }

    if (larvalStalker->moveSpeed_38 > Q12(0.0f))
    {
        if (sp18.offset_0.vx == Q12(0.0f) &&
            sp18.offset_0.vz == Q12(0.0f))
        {
            larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker,
                                                                          Q12(1.0f),
                                                                          larvalStalkerProps.targetPositionX,
                                                                          larvalStalkerProps.targetPositionZ,
                                                                          Q12(1.0f),
                                                                          false);
            larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_3;
        }
    }

    Math_MatrixTransform(&larvalStalker->position_18, &larvalStalker->rotation_24, coords);
}

void sharedFunc_800D1524_1_s00(s_SubCharacter* larvalStalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    #define activeAnimInfo     LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0]

    switch (larvalStalker->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(LarvalStalkerAnim_5, false):
            activeAnimInfo.endKeyframeIdx_E = larvalStalkerProps.keyframeIdx_F4 + 41;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_5, true):
            activeAnimInfo.startKeyframeIdx_C = larvalStalkerProps.keyframeIdx_F4 + 41;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_7, false):
            activeAnimInfo.endKeyframeIdx_E = larvalStalkerProps.keyframeIdx_F4 + 121;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_7, true):
            activeAnimInfo.startKeyframeIdx_C = larvalStalkerProps.keyframeIdx_F4 + 121;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_6, false):
            activeAnimInfo.endKeyframeIdx_E = larvalStalkerProps.keyframeIdx_F4 + 86;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_6, true):
            activeAnimInfo.startKeyframeIdx_C = larvalStalkerProps.keyframeIdx_F4 + 86;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_8, false):
            activeAnimInfo.endKeyframeIdx_E = larvalStalkerProps.keyframeIdx_F4 + 143;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_8, true):
            activeAnimInfo.startKeyframeIdx_C = larvalStalkerProps.keyframeIdx_F4 + 143;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_12, true):
            activeAnimInfo.duration_8.constant = Q12_MULT_FLOAT_PRECISE(larvalStalker->moveSpeed_38, 32.0f);
            break;
    }

    animInfo = &LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&larvalStalker->model_0, anmHdr, coords, animInfo);

    #undef activeAnimInfo
}

void Ai_LarvalStalker_Init(s_SubCharacter* larvalStalker)
{
    s32 i;

    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_3;
    larvalStalker->model_0.anim_4.time_4  = Q12(0.0f);
    Character_AnimSet(larvalStalker, ANIM_STATUS(LarvalStalkerAnim_10, false), 162);

    larvalStalkerProps.flags_E8 = LarvalStalkerFlag_None;
    larvalStalker->model_0.anim_4.alpha_A = Q12(0.0f);
    larvalStalker->model_0.stateStep_3    = 0;
    ModelAnim_AnimInfoSet(&larvalStalker->model_0.anim_4, LARVAL_STALKER_ANIM_INFOS);

    larvalStalker->health_B0    = Q12(300.0f);
    larvalStalker->fallSpeed_34 = Q12(0.0f);
    larvalStalker->moveSpeed_38 = Q12(0.0f);

    Chara_DamageClear(larvalStalker);
    larvalStalker->field_E1_0      = 0;
    larvalStalker->headingAngle_3C = larvalStalker->rotation_24.vy;

    Chara_PropertiesClear(larvalStalker);
    larvalStalkerProps.targetPositionX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    larvalStalkerProps.targetPositionZ = g_SysWork.playerWork_4C.player_0.position_18.vz;
}

void sharedFunc_800D17BC_1_s00(s_SubCharacter* larvalStalker)
{
    q19_12 angle;
    s32    keyframe;
    s32    keyframe2;
    s16    keyframeOffset;

    if (larvalStalker->damage_B4.amount_C <= Q12(0.0f) || larvalStalker->health_B0 <= Q12(0.0f))
    {
        return;
    }

    func_8005DC1C(0, &larvalStalker->position_18, Q8_CLAMPED(0.5f), 0);

    larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_7;

    larvalStalker->health_B0                = MAX(larvalStalker->health_B0 - larvalStalker->damage_B4.amount_C, Q12(0.0f));
    larvalStalker->damage_B4.position_0.vx += FP_FROM(larvalStalker->moveSpeed_38 * Math_Sin(larvalStalker->headingAngle_3C), Q12_SHIFT);
    larvalStalker->damage_B4.position_0.vz += FP_FROM(larvalStalker->moveSpeed_38 * Math_Cos(larvalStalker->headingAngle_3C), Q12_SHIFT);
    larvalStalker->moveSpeed_38             = FP_TO(Math_Vector2MagCalc(larvalStalker->damage_B4.position_0.vx, larvalStalker->damage_B4.position_0.vz), Q12_SHIFT) / Q12(2.4f);
    larvalStalker->fallSpeed_34             = FP_TO(larvalStalker->damage_B4.position_0.vy, Q12_SHIFT) / Q12(2.4f);
    larvalStalker->headingAngle_3C          = ratan2(larvalStalker->damage_B4.position_0.vx, larvalStalker->damage_B4.position_0.vz);

    larvalStalkerProps.flags_E8       |= LarvalStalkerFlag_1;
    larvalStalkerProps.targetPositionX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    larvalStalkerProps.targetPositionZ = g_SysWork.playerWork_4C.player_0.position_18.vz;

    if (larvalStalker->model_0.controlState_2 == LarvalStalkerControl_11)
    {
        if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_9)
        {
            larvalStalkerProps.keyframeIdx_F8                         = NO_VALUE;
            larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_17, false);
        }
    }
    else if (larvalStalker->model_0.controlState_2 == LarvalStalkerControl_12)
    {
        if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == LarvalStalkerAnim_2)
        {
            larvalStalkerProps.keyframeIdx_F8                         = NO_VALUE;
            larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_18, false);
        }
    }
    else
    {
        if (func_8005BF38(Math_AngleBetweenPositionsGet(larvalStalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                          larvalStalker->rotation_24.vy) < Q12_ANGLE(0.0f))
        {
            angle = -func_8005BF38(Math_AngleBetweenPositionsGet(larvalStalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                   larvalStalker->rotation_24.vy);
        }
        else
        {
            angle = func_8005BF38(Math_AngleBetweenPositionsGet(larvalStalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                  larvalStalker->rotation_24.vy);
        }

        if (larvalStalker->health_B0 > Q12(100.0f))
        {
            larvalStalker->model_0.controlState_2 = LarvalStalkerControl_10;
            if (angle < Q12_ANGLE(90.0f))
            {
                keyframe2      = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 41;
                if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 41, 65))
                {
                    // No-op.
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 66, 72))
                {
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    if (keyframeOffset == 30)
                    {
                        larvalStalker->model_0.anim_4.time_4 -= Q12(1.0f);
                    }

                    larvalStalker->model_0.anim_4.status_0                       = ANIM_STATUS(LarvalStalkerAnim_5, false);
                    larvalStalkerProps.keyframeIdx_F4 = 76 - FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 73, 74))
                {
                    larvalStalkerProps.keyframeIdx_F8                                               = keyframeOffset;
                    larvalStalker->model_0.anim_4.status_0                       = ANIM_STATUS(LarvalStalkerAnim_5, false);
                    larvalStalkerProps.keyframeIdx_F4 = 5;
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 75, 78))
                {
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    if (keyframeOffset == 36)
                    {
                        larvalStalker->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(LarvalStalkerAnim_5, false);
                    larvalStalkerProps.keyframeIdx_F4 = 79 - FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else
                {
                    larvalStalkerProps.keyframeIdx_F4 = 0;
                    larvalStalker->model_0.anim_4.status_0                       = ANIM_STATUS(LarvalStalkerAnim_5, false);
                }
            }
            else
            {
                keyframe2      = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 86;
                if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 86, 104))
                {
                    // No-op.
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 105, 118))
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_6, false);
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    larvalStalkerProps.keyframeIdx_F4 = 7 - ((FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) - 104) >> 1);
                }
                else
                {
                    larvalStalkerProps.keyframeIdx_F4 = 0;
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_6, false);
                }
            }
        }
        else
        {
            if (Rng_GenerateInt(0, 7) == 0) // 1 in 8 chance.
            {
                Savegame_EnemyStateUpdate(larvalStalker);
            }

            if (angle < Q12_ANGLE(90.0f))
            {
                keyframe       = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe - 41;
                if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 41, 51))
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_7, false);
                    keyframeOffset = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) - 41;
                    larvalStalkerProps.keyframeIdx_F4 = keyframeOffset;
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 52, 65))
                {
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_2, false);
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 66, 72))
                {
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    if (keyframeOffset == 30)
                    {
                        larvalStalker->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_7, false);
                    larvalStalkerProps.keyframeIdx_F4 = 76 - FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 73, 74))
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_7, false);
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    larvalStalker->model_0.anim_4.time_4 = 5;
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 75, 78))
                {
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    if (keyframeOffset == 36)
                    {
                        larvalStalker->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_7, false);
                    larvalStalker->model_0.anim_4.time_4   = 79 - FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else
                {
                    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != LarvalStalkerAnim_7)
                    {
                        larvalStalkerProps.keyframeIdx_F4 = 0;
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_7, false);
                    }
                }

                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_12;
            }
            else
            {
                keyframe2 = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 86;
                if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 86, 96))
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_8, false);
                    keyframeOffset = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) - 86;
                    larvalStalkerProps.keyframeIdx_F4 = keyframeOffset;
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 97, 104))
                {
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_9, false);
                }
                else if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 105, 118))
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_8, false);
                    larvalStalkerProps.keyframeIdx_F8 = keyframeOffset;
                    larvalStalkerProps.keyframeIdx_F4 = 7 - ((FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) - 104) >> 1);
                }
                else
                {
                    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != LarvalStalkerAnim_8)
                    {
                        larvalStalkerProps.keyframeIdx_F4 = 0;
                    }
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_8, false);
                }

                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_11;
            }
        }
    }

    larvalStalkerProps.angle_108 = 0;
    larvalStalkerProps.timer_EC = Q12(0.0f);
}

#include "bodyprog/bodyprog.h"

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
                                              \
    arg0->field_C8.field_0 = data.field_0;    \
                                              \
    __temp = data.field_2;                    \
    arg0->field_C8.field_2 = __temp;          \
    arg0->field_C8.field_4 = data.field_4;    \
                                              \
    __temp = data.field_6;                    \
    arg0->field_C8.field_6 = __temp;          \
    arg0->field_D8.offsetX_4 = data.field_10; \
                                              \
    __temp = data.field_12;                   \
    arg0->field_D8.offsetZ_6 = __temp;        \
    arg0->field_D4.radius_0   = data.field_8;  \
    arg0->field_D8.offsetX_0 = data.field_C;  \
                                              \
    __temp = data.field_E;                    \
    arg0->field_D8.offsetZ_2 = __temp;        \
                                              \
    __temp = data.field_A;                    \
    arg0->field_D4.field_2 = __temp;          \
}

extern s_Keyframe sharedData_800DA928_1_s00[];
extern s_Keyframe sharedData_800DA93C_1_s00;
extern s_Keyframe sharedData_800DA950_1_s00;
extern s_Keyframe sharedData_800DA964_1_s00[];

extern s_Keyframe sharedData_800DAC34_1_s00[];
extern s_Keyframe sharedData_800DAE28_1_s00[];

extern s_Keyframe sharedData_800DAF54_1_s00;
extern s_Keyframe sharedData_800DAF68_1_s00[];

extern s_Keyframe sharedData_800DAFF4_1_s00;

extern s_Keyframe sharedData_800DB008_1_s00;
extern s_Keyframe sharedData_800DB01C_1_s00;

extern s_Keyframe sharedData_800DB030_1_s00;

void sharedFunc_800D1DBC_1_s00(s_SubCharacter* larvalStalker)
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 keyframeIdx2;
    s32 var_a0;
    s32 relKeyframeIdx;
    s32 var_a2;
    s32 var_a3;

    switch (larvalStalker->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(LarvalStalkerAnim_2, false):
            keyframeIdx1 = larvalStalkerProps.keyframeIdx_F8;
            if (keyframeIdx1 != -1)
            {
                if (keyframeIdx1 == -2)
                {
                    func_80070400(larvalStalker, &sharedData_800DAF54_1_s00, &sharedData_800DA93C_1_s00);
                    break;
                }

                relKeyframeIdx = keyframeIdx1;
                if (relKeyframeIdx < 15)
                {
                    keyframeIdx0 = relKeyframeIdx - (relKeyframeIdx >= 11);
                }
                else
                {
                    if ((relKeyframeIdx - 24) >= 0)
                    {
                        keyframeIdx0 = relKeyframeIdx - 10;
                    }
                    else
                    {
                        keyframeIdx0 = 14;
                    }
                }

                func_80070400(larvalStalker, &sharedData_800DA964_1_s00[keyframeIdx0], &sharedData_800DA93C_1_s00);
                break;
            }

            CopyData(larvalStalker, sharedData_800DA928_1_s00[1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_3, true):
        case ANIM_STATUS(LarvalStalkerAnim_18, true):
            keyframeIdx0 = (FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) > 24 && FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) < 30) ? 0 : 1;
            keyframeIdx1 = (FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) > 23 && FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) < 29) ? 0 : 1;
            func_80070400(larvalStalker, &sharedData_800DA928_1_s00[keyframeIdx0], &sharedData_800DA928_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_2, true):
        case ANIM_STATUS(LarvalStalkerAnim_3, false):
        case ANIM_STATUS(LarvalStalkerAnim_14, false):
        case ANIM_STATUS(LarvalStalkerAnim_14, true):
        case ANIM_STATUS(LarvalStalkerAnim_18, false):
            CopyData(larvalStalker, sharedData_800DA928_1_s00[1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_4, false):
            func_80070400(larvalStalker, &sharedData_800DB008_1_s00, &sharedData_800DA950_1_s00);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_4, true):
        case ANIM_STATUS(LarvalStalkerAnim_13, false):
        case ANIM_STATUS(LarvalStalkerAnim_13, true):
            CopyData(larvalStalker, sharedData_800DA950_1_s00);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_5, false):
            var_a3 = larvalStalkerProps.keyframeIdx_F4;
            if (var_a3 == 0)
            {
                CopyData(larvalStalker, sharedData_800DA964_1_s00[0]);
                break;
            }

            keyframeIdx1 = larvalStalkerProps.keyframeIdx_F8;
            if ((keyframeIdx1 - 24) >= 0)
            {
                keyframeIdx0 = keyframeIdx1 - 10;
            }
            else
            {
                keyframeIdx0 = 14;
            }

            func_80070400(larvalStalker, &sharedData_800DA964_1_s00[keyframeIdx0], &sharedData_800DA964_1_s00[var_a3]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_5, true):
        case ANIM_STATUS(LarvalStalkerAnim_15, true):
            var_a0 = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
            relKeyframeIdx = var_a0 - 41;
            if (relKeyframeIdx < 15)
            {
                keyframeIdx0 = relKeyframeIdx - (relKeyframeIdx >= 11);
                keyframeIdx1 = (var_a0 - 40) - (relKeyframeIdx >= 10);
            }
            else
            {
                if ((var_a0 - 65) >= 0)
                {
                    keyframeIdx0 = var_a0 - 51;
                }
                else
                {
                    keyframeIdx0 = 14;
                }

                if ((var_a0 - 64) >= 0)
                {
                    keyframeIdx1 = var_a0 - 50;
                }
                else
                {
                    keyframeIdx1 = 14;
                }
            }

            func_80070400(larvalStalker, &sharedData_800DA964_1_s00[keyframeIdx0], &sharedData_800DA964_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_6, false):
            keyframeIdx2 = larvalStalkerProps.keyframeIdx_F4;
            if (keyframeIdx2 == 0)
            {
                CopyData(larvalStalker, sharedData_800DAC34_1_s00[0]);
                break;
            }

            relKeyframeIdx = larvalStalkerProps.keyframeIdx_F8;
            keyframeIdx0 = ((relKeyframeIdx - 7) - (relKeyframeIdx >= 23)) - (relKeyframeIdx >= 24);
            func_80070400(larvalStalker, &sharedData_800DAC34_1_s00[keyframeIdx0], &sharedData_800DAC34_1_s00[keyframeIdx2]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_6, true):
        case ANIM_STATUS(LarvalStalkerAnim_16, true):
            var_a2 = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
            relKeyframeIdx = var_a2 - 86;
            if (relKeyframeIdx < 15)
            {
                keyframeIdx0 = MIN(8, relKeyframeIdx);
                keyframeIdx1 = MIN(8, var_a2 - 85);
            }
            else
            {
                keyframeIdx0 = (var_a2 - 93) - (relKeyframeIdx >= 23) - (relKeyframeIdx >= 24);
                keyframeIdx1 = (var_a2 - 92) - (relKeyframeIdx >= 22) - (relKeyframeIdx >= 23) - (relKeyframeIdx >= 33);
            }

            func_80070400(larvalStalker, &sharedData_800DAC34_1_s00[keyframeIdx0], &sharedData_800DAC34_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_7, false):
            if (larvalStalkerProps.keyframeIdx_F4 == 0)
            {
                CopyData(larvalStalker, sharedData_800DAE28_1_s00[0]);
                break;
            }

            relKeyframeIdx = larvalStalkerProps.keyframeIdx_F8;
            if (relKeyframeIdx < 15)
            {
                keyframeIdx0 = relKeyframeIdx - (relKeyframeIdx >= 11);
            }
            else
            {
                if ((relKeyframeIdx - 24) >= 0)
                {
                    keyframeIdx0 = relKeyframeIdx - 10;
                }
                else
                {
                    keyframeIdx0 = 14;
                }
            }

            keyframeIdx1 = larvalStalkerProps.keyframeIdx_F4;
            func_80070400(larvalStalker, &sharedData_800DA964_1_s00[keyframeIdx0], &sharedData_800DAE28_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_7, true):
            larvalStalkerProps.keyframeIdx_F8 = -2;
            keyframeIdx1 = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);

            relKeyframeIdx = keyframeIdx1 - 121;
            keyframeIdx0   = relKeyframeIdx - (relKeyframeIdx > 10) < 16 ? relKeyframeIdx - (relKeyframeIdx > 10) : 15;

            keyframeIdx1 = relKeyframeIdx + 1;
            keyframeIdx1 = relKeyframeIdx + (relKeyframeIdx < 10) < 16 ? relKeyframeIdx + (relKeyframeIdx < 10) : 15;

            func_80070400(larvalStalker, &sharedData_800DAE28_1_s00[keyframeIdx0], &sharedData_800DAE28_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_8, false):
            if (larvalStalkerProps.keyframeIdx_F4 == 0)
            {
                CopyData(larvalStalker, sharedData_800DAF68_1_s00[0]);
                break;
            }

            relKeyframeIdx = larvalStalkerProps.keyframeIdx_F8;
            if (relKeyframeIdx < 15)
            {
                keyframeIdx0 = MIN(8, relKeyframeIdx);
            }
            else
            {
                keyframeIdx0 = ((relKeyframeIdx - 7) - (relKeyframeIdx >= 23)) - (relKeyframeIdx >= 24);
            }

            keyframeIdx1 = larvalStalkerProps.keyframeIdx_F4;
            func_80070400(larvalStalker, &sharedData_800DAC34_1_s00[keyframeIdx0], &sharedData_800DAF68_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_8, true):
            larvalStalkerProps.keyframeIdx_F8 = -2;
            var_a0 = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
            relKeyframeIdx = var_a0 - 143;

            keyframeIdx0 = MIN(7, relKeyframeIdx);
            keyframeIdx1 = MIN(7, var_a0 - 142);
            func_80070400(larvalStalker, &sharedData_800DAF68_1_s00[keyframeIdx0], &sharedData_800DAF68_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_9, false):
            keyframeIdx1 = larvalStalkerProps.keyframeIdx_F8;
            if (keyframeIdx1 == -1)
            {
                CopyData(larvalStalker, sharedData_800DB008_1_s00);
                break;
            }
            if (keyframeIdx1 == -2)
            {
                func_80070400(larvalStalker, &sharedData_800DAFF4_1_s00, &sharedData_800DB008_1_s00);
                break;
            }

            relKeyframeIdx = keyframeIdx1;
            if (relKeyframeIdx < 15)
            {
                keyframeIdx0 = MIN(8, relKeyframeIdx);
            }
            else
            {
                keyframeIdx0 = relKeyframeIdx - 7;
            }

            func_80070400(larvalStalker, &sharedData_800DAC34_1_s00[keyframeIdx0], &sharedData_800DB008_1_s00);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_9, true):
        case ANIM_STATUS(LarvalStalkerAnim_17, false):
        case ANIM_STATUS(LarvalStalkerAnim_17, true):
            CopyData(larvalStalker, sharedData_800DB008_1_s00);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_10, false):
        case ANIM_STATUS(LarvalStalkerAnim_10, true):
            CopyData(larvalStalker, sharedData_800DB01C_1_s00);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_11, false):
        case ANIM_STATUS(LarvalStalkerAnim_11, true):
        case ANIM_STATUS(LarvalStalkerAnim_12, false):
        case ANIM_STATUS(LarvalStalkerAnim_12, true):
            CopyData(larvalStalker, sharedData_800DB030_1_s00);
            break;

        case ANIM_STATUS(LarvalStalkerAnim_1, false):
        case ANIM_STATUS(LarvalStalkerAnim_1, true):
            larvalStalker->field_C8.field_0   = Q12(-0.72f);
            larvalStalker->field_C8.field_4   = Q12(-0.2f);
            larvalStalker->field_C8.field_6   = Q12(-0.66f);
            larvalStalker->field_D4.radius_0   = Q12(0.12f);
            larvalStalker->field_D8.offsetZ_2 = Q12(0.02f);
            larvalStalker->field_D4.field_2   = Q12(0.11f);
            larvalStalker->field_C8.field_2   = Q12(0.0f);
            larvalStalker->field_D8.offsetX_4 = Q12(0.0f);
            larvalStalker->field_D8.offsetZ_6 = Q12(0.0f);
            larvalStalker->field_D8.offsetX_0 = Q12(0.0f);
            larvalStalker->field_C8.field_8   = Q12(-0.59f);
            break;
    }

    func_8005C814(&larvalStalker->field_D8, larvalStalker);
}

#undef larvalStalkerProps

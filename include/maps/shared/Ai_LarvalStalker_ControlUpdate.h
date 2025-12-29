#define Chara_TurnModulate(angle, limit, mult)                                                   \
    angleDeltaToPlayer = angle;                                                                  \
                                                                                                 \
    if (limit <= ABS(angleDeltaToPlayer))                                                        \
    {                                                                                            \
        if ((angleDeltaToPlayer) > FP_ANGLE(0.0f))                                               \
        {                                                                                        \
            larvalStalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT); \
        }                                                                                        \
        else                                                                                     \
        {                                                                                        \
            larvalStalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT); \
        }                                                                                        \
    }

#define Chara_TurnModulate_REV(angle, limit, mult)                                               \
    if (limit <= ABS(angle))                                                                     \
    {                                                                                            \
        if ((angle) < FP_ANGLE(0.0f))                                                            \
        {                                                                                        \
            larvalStalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT); \
        }                                                                                        \
        else                                                                                     \
        {                                                                                        \
            larvalStalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT); \
        }                                                                                        \
    }

#define ANIM_STUFF(mult, div)                                                                                                                    \
    temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) * \
           mult / div;                                                                                                                           \
    larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(larvalStalker->rotation_24.vy), Q12_SHIFT);                                           \
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

    #define larvalStalkerProps larvalStalker->properties_E4.larvalStalker

    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(larvalStalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       larvalStalker->rotation_24.vy);
    distToTarget       = Math_Vector2MagCalc(larvalStalkerProps.targetPositionX - larvalStalker->position_18.vx,
                                             larvalStalkerProps.targetPositionZ - larvalStalker->position_18.vz);

    larvalStalker->rotation_24.vy = func_8005BF38(larvalStalker->rotation_24.vy);

    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != LarvalStalkerAnim_1)
    {
        larvalStalker->field_44.field_0 = 0;
    }

    idxInfo = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1));
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
                if (larvalStalkerProps.angle_108 > FP_ANGLE(0.0f))
                {
                    larvalStalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                    larvalStalkerProps.angle_108 -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);

                    if ((larvalStalkerProps.angle_108) <= FP_ANGLE(0.0f)) 
                    {
                        larvalStalkerProps.angle_108 = FP_ANGLE(0.0f);
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                    }
                } 
                else if (larvalStalkerProps.angle_108 < FP_ANGLE(0.0f)) 
                {
                    larvalStalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                    larvalStalkerProps.angle_108 += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);

                    if (!(larvalStalkerProps.angle_108 < FP_ANGLE(0.0f)))
                    {
                        larvalStalkerProps.angle_108 = FP_ANGLE(0.0f);
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
                if ((validStep && !Rng_GenerateInt(0, 3)) || // 1 in  chance.
                    !Rng_GenerateInt(0, 31))                 // 1 in 32 chance.
                {
                    larvalStalkerProps.angle_108 = Rng_TestProbabilityBits(11) - FP_ANGLE(90.0f); // -90 >< 90 angle.
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
                larvalStalkerProps.angle_108 = FP_ANGLE(0.0f);
                larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_2;
            }
            break;

        case LarvalStalkerControl_4:
            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(0.3f));

            if ((larvalStalkerProps.flags_E8 & LarvalStalkerFlag_2) && ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == 11 &&
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
                if (FP_ANGLE(45.0f) > ABS(angleDeltaToPlayer) && 
                    (distToTarget < ((larvalStalker->field_D4.field_0 + Q12(0.05f)) + g_SysWork.playerWork_4C.player_0.field_D4.field_0)))
                {
                    if (!Rng_GenerateInt(0, 7)) // 1 in 8 chance.
                    {
                        targetX = larvalStalkerProps.targetPositionX + Rng_GenerateInt(0, Q12(1.5f) - 1);
                        targetZ = larvalStalkerProps.targetPositionZ + Rng_GenerateInt(0, Q12(1.5f) - 1);
                        larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker, Q12(2.0f), targetX, targetZ, Q12(1.0f), true);
                        Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                    } 
                    else
                    {
                        Chara_TurnModulate_REV(angleDeltaToPlayer, FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                    }
                    break;
                }

                if ((distStep >> 1) < distToTarget)
                {
                    if (!Rng_GenerateInt(0, 31)) // 1 in 32 chance.
                    {
                        larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker, Q12(2.0f), larvalStalkerProps.targetPositionX, larvalStalkerProps.targetPositionZ, Q12(1.0f), true);
                    }

                    Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                    break;
                }

                if (larvalStalkerProps.flags_E8 & LarvalStalkerFlag_3)
                {
                    Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                    if (!Rng_GenerateInt(0, 15)) // 1 in 16 chance.
                    {
                        larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_3;
                    }
                    break;
                }

                if (!(g_SysWork.field_2284[3] & 0x1)) 
                {
                    Chara_TurnModulate(angleDeltaToPlayer, FP_ANGLE(1.5f), FP_ANGLE(30.0f));
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
            Chara_TurnModulate(angleDeltaToPlayer, FP_ANGLE(1.5f), FP_ANGLE(30.0f));

            if (larvalStalkerProps.flags_E8 & LarvalStalkerFlag_6)
            {
                larvalStalkerProps.animTime_104 = larvalStalker->model_0.anim_4.time_4;
                larvalStalker->moveSpeed_38 = Q12(0.0f);
                larvalStalkerProps.timer_EC += g_DeltaTime0;

                if (larvalStalkerProps.timer_EC > Q12(1.8f)) 
                {
                    if (!(Rng_Rand16() & 0x7))
                    {
                        func_8005DC1C(0, &larvalStalker->position_18, Q8(0.5f), 0);
                        larvalStalkerProps.timer_EC = Q12(0.0f);

                        if (g_SysWork.playerWork_4C.player_0.field_40 == NO_VALUE) 
                        {
                            g_SysWork.playerWork_4C.player_0.field_40 = func_8005C7D0(larvalStalker);
                        }

                        g_SysWork.playerWork_4C.player_0.attackReceived_41 = WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Multitap);
                        g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Multitap)].field_4, Q12_SHIFT) * ((Rng_Rand16() & 0x1F) + 0x55)) / 100;
                    }
                }

                angleDeltaToPlayer = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - larvalStalker->rotation_24.vy);
                if (FP_ANGLE(90.0f) < ABS(angleDeltaToPlayer))
                {
                    if (distToTarget >= Q12(0.29004f))
                    {
                        sinRotY = Math_Sin(larvalStalker->rotation_24.vy);
                        larvalStalkerProps.angle_100 = ((distToTarget - Q12(0.28f)) <= Q12(0.02f)) ?
                                                       FP_MULTIPLY(distToTarget - Q12(0.28f), sinRotY, Q12_SHIFT) :
                                                       FP_MULTIPLY(Q12(0.02f), sinRotY, Q12_SHIFT);

                        cosRotY = Math_Cos(larvalStalker->rotation_24.vy);
                        larvalStalkerProps.angle_102 = ((distToTarget - Q12(0.28f)) <= Q12(0.02f)) ?
                                                       FP_MULTIPLY(distToTarget - Q12(0.28f), cosRotY, Q12_SHIFT) :
                                                       FP_MULTIPLY(Q12(0.02f), cosRotY, Q12_SHIFT);
                    }

                    if (distToTarget < Q12(0.27f))
                    {
                        larvalStalkerProps.angle_100 = FP_MULTIPLY(((distToTarget - Q12(0.28f)) < Q12(-0.02f)) ? Q12(-0.02f) : (distToTarget - Q12(0.28f)), Math_Sin(larvalStalker->rotation_24.vy), Q12_SHIFT);
                        larvalStalkerProps.angle_102 = FP_MULTIPLY(((distToTarget - Q12(0.28f)) < Q12(-0.02f)) ? Q12(-0.02f) : (distToTarget - Q12(0.28f)), Math_Cos(larvalStalker->rotation_24.vy), Q12_SHIFT);
                    }
                }
                else
                {
                    if (distToTarget > Q12(0.18f))
                    {
                        sinRotY = Math_Sin(larvalStalker->rotation_24.vy);
                        larvalStalkerProps.angle_100 = ((distToTarget - Q12(0.17f)) <= Q12(0.02f)) ?
                                                       FP_MULTIPLY(distToTarget - Q12(0.17f), sinRotY, Q12_SHIFT) :
                                                       FP_MULTIPLY(Q12(0.02f), sinRotY, Q12_SHIFT);

                        sinRotY = Math_Cos(larvalStalker->rotation_24.vy);
                        larvalStalkerProps.angle_102 = ((distToTarget - Q12(0.17f)) <= Q12(0.02f)) ?
                                                       FP_MULTIPLY(distToTarget - Q12(0.17f), sinRotY, Q12_SHIFT) :
                                                       FP_MULTIPLY(Q12(0.02f), sinRotY, Q12_SHIFT);
                    }

                    if (distToTarget < Q12(0.16f))
                    {
                        larvalStalkerProps.angle_100 = FP_MULTIPLY(((distToTarget - Q12(0.17f)) < Q12(-0.02f)) ? Q12(-0.02f) : (distToTarget - Q12(0.17f)), Math_Sin(larvalStalker->rotation_24.vy), Q12_SHIFT);
                        larvalStalkerProps.angle_102 = FP_MULTIPLY(((distToTarget - Q12(0.17f)) < Q12(-0.02f)) ? Q12(-0.02f) : (distToTarget - Q12(0.17f)), Math_Cos(larvalStalker->rotation_24.vy), Q12_SHIFT);
                    }
                }

                if ((&g_SysWork.playerWork_4C.player_0)->attackReceived_41 == NO_VALUE)
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
                if (distToTarget < ((larvalStalker->field_D4.field_0 + Q12(0.02f)) + g_SysWork.playerWork_4C.player_0.field_D4.field_0))
                {
                    Chara_MoveSpeedUpdate(larvalStalker, Q12(1.5f));
                }

                pos     = larvalStalker->position_18;
                pos.vy += larvalStalker->field_C8.field_8;

                if (func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_Unk31, AttackInputType_Multitap), larvalStalker, &pos, &g_SysWork.playerWork_4C.player_0, larvalStalker->rotation_24.vy, FP_ANGLE(90.0f)) != NO_VALUE)
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
                    larvalStalkerProps.angle_108 = Rng_TestProbabilityBits(12);
                }
            }

            larvalStalkerProps.timer_EC += g_DeltaTime0;
            if (larvalStalkerProps.timer_EC > Q12(0.8f))
            {
                larvalStalkerProps.timer_EC = Q12(0.0f);
            }

            Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), 33, 682);

            if ((larvalStalker->moveSpeed_38 >= Q12(0.9004f)) && !Rng_TestProbabilityBits(8))
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

                if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != ANIM_STATUS(LarvalStalkerAnim_5, false))
                {
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                }
            } 
            else
            {
                if (FP_ANGLE(1.5f) <= ABS(angleDeltaToPlayer) && ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != 10)
                {
                    Chara_MoveSpeedUpdate3(larvalStalker, Q12(0.375f), Q12(0.0f));

                    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != ANIM_STATUS(LarvalStalkerAnim_5, true))
                    {
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_11, false);
                    }

                    if (angleDeltaToPlayer > FP_ANGLE(0.0f))
                    {
                        larvalStalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                    }
                    else
                    {
                        larvalStalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                    }
                }
                else
                {
                    Chara_MoveSpeedUpdate(larvalStalker, Q12(1.5f));

                    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != ANIM_STATUS(LarvalStalkerAnim_5, false))
                    {
                        larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_10, false);
                    }
                }

                larvalStalkerProps.timer_EC += g_DeltaTime0;

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
            larvalStalkerProps.timer_10A += FP_MULTIPLY_PRECISE(g_DeltaTime0, Rng_Rand16() & 0xFFF, Q12_SHIFT);
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

            larvalStalkerProps.timer_EC += g_DeltaTime0;
            if (larvalStalkerProps.timer_EC > Q12(0.8f))
            {
                larvalStalkerProps.timer_EC = Q12(0.0f);
            }

            Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), FP_ANGLE(1.5f), 682);

            if ((larvalStalker->moveSpeed_38 >= Q12(0.9004f)) && !(Rng_Rand16() & 0x3F))
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_6, false);
                larvalStalkerProps.timer_EC = Q12(0.0f);
                larvalStalkerProps.keyframeIdx_F4 = 0;
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_9;

                func_8005DC1C(Sfx_Unk1429, &larvalStalker->position_18, Q8(0.5f), 0);
            }

            if (!(larvalStalkerProps.flags_E8 & LarvalStalkerFlag_7))
            {
                larvalStalkerProps.timer_F0 += g_DeltaTime0;
                if (larvalStalkerProps.timer_F0 > Q12(5.0f) && !(Rng_Rand16() & 0x3F))
                {
                    larvalStalkerProps.timer_F0 = Q12(0.0f);
                    larvalStalkerProps.timer_EC = Q12(0.0f);
                    larvalStalkerProps.angle_108 = Q12(0.0f);
                    larvalStalker->model_0.controlState_2 = LarvalStalkerControl_6;
                }
            }
            break;

        case LarvalStalkerControl_9:
            larvalStalkerProps.timer_10A += FP_MULTIPLY_PRECISE(g_DeltaTime0, (Rng_Rand16() & 0x7FF) + Q12(0.5f), Q12_SHIFT);
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

            if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == ANIM_STATUS(LarvalStalkerAnim_5, false))
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
                                        g_DeltaTime0, Q12_SHIFT) * Q12(0.3f) / Q12(9.0f);
                larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(larvalStalker->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
                larvalStalkerProps.angle_102 = FP_FROM(temp * Math_Cos(larvalStalker->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            }

            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 95, 96) && larvalStalker->moveSpeed_38 != Q12(0.0f))
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_16, true);
            }

            if (larvalStalker->model_0.anim_4.status_0 == ANIM_STATUS(LarvalStalkerAnim_16, true) &&
                larvalStalker->moveSpeed_38 == Q12(0.0f) && !(Rng_Rand16() & 0x7)) 
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_6, true);
            }

            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 61, 62) && larvalStalker->moveSpeed_38 != Q12(0.0f))
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_15, true);
            }

            if (larvalStalker->model_0.anim_4.status_0 == ANIM_STATUS(LarvalStalkerAnim_15, true) &&
                larvalStalker->moveSpeed_38 == Q12(0.0f) && !(Rng_Rand16() & 0x7))
            {
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_5, true);
            }

            if ((ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == 10) && !(Rng_Rand16() & 0x7))
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

            if (larvalStalker->health_B0 == Q12(0.0f) && ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == 9)
            {
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_13;
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_4, false);
                func_80037DC4(larvalStalker);
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
                larvalStalkerProps.angle_108 = Chara_HeadingAngleGet(larvalStalker, FP_ANGLE(180.0f), larvalStalkerProps.targetPositionX, larvalStalkerProps.targetPositionZ, Q12(1.0f), false);
            }

            larvalStalkerProps.timer_EC += g_DeltaTime0;
            if (larvalStalkerProps.timer_EC > Q12(1.0f))
            {
                larvalStalkerProps.timer_EC = Q12(0.0f);
            }

            Chara_TurnModulate(func_8005BF38(larvalStalkerProps.angle_108 - larvalStalker->rotation_24.vy), FP_ANGLE(1.5f), 170);
            break;

        case LarvalStalkerControl_12:
            if (ANIM_TIME_RANGE_CHECK(larvalStalker->model_0.anim_4.time_4, 0x79, 0x7F))
            {
                temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].duration_8.constant,
                                        g_DeltaTime0, Q12_SHIFT) * Q12(0.15f) / Q12(6.0f);
                larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(larvalStalker->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
                larvalStalkerProps.angle_102 = FP_FROM(temp * Math_Cos(larvalStalker->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            }

            larvalStalker->flags_3E |= CharaFlag_Unk2;

            if (larvalStalker->health_B0 <= Q12(0.0f) && ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == 2) 
            {
                larvalStalker->flags_3E &= ~CharaFlag_Unk2;
                larvalStalker->model_0.controlState_2 = LarvalStalkerControl_13;
                larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(LarvalStalkerAnim_3, false);
                func_80037DC4(larvalStalker);
            }

            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(0.0f));
            break;

        case LarvalStalkerControl_13:
            larvalStalker->flags_3E &= ~CharaFlag_Unk2;

            if (larvalStalker->health_B0 <= Q12(0.0f) && func_8005C7D0(larvalStalker) != g_SysWork.targetNpcIdx_2353)
            {
                larvalStalker->health_B0 = NO_VALUE;
                larvalStalker->field_E1_0 = 0;
            }

            // TODO: Property mismatch?
            if (larvalStalker->moveSpeed_38 == Q12(0.0f) && !(larvalStalker->properties_E4.player.afkTimer_E8 & 0x30))
            {
                if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == ANIM_STATUS(LarvalStalkerAnim_6, true)) 
                {
                    func_800622B8(3, larvalStalker, 3, 3);
                    larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_4;
                }
                else if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == ANIM_STATUS(LarvalStalkerAnim_7, false))
                {
                    func_800622B8(3, larvalStalker, 4, 3);
                    larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_4;
                }
            }

            Chara_MoveSpeedUpdate3(larvalStalker, Q12(1.5f), Q12(0.0f));
            break;
    }

    larvalStalker->damage_B4.amount_C      = Q12(0.0f);
    larvalStalker->damage_B4.position_0.vz = Q12(0.0f);
    larvalStalker->damage_B4.position_0.vy = Q12(0.0f);
    larvalStalker->damage_B4.position_0.vx = Q12(0.0f);

    #undef larvalStalkerProps
}

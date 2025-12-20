#define ANGLE_STUFF(angle, limit, mult)\
    angle0 = angle;                                                                      \
                                                                                         \
    if (limit <= ABS(angle0))                                                            \
    {                                                                                    \
        if ((angle0) > FP_ANGLE(0.0f))                                                   \
        {                                                                                \
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT); \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT); \
        }                                                                                \
    }

#define ANGLE_STUFF_REV(angle, limit, mult)                                              \
    if (limit <= ABS(angle))                                                             \
    {                                                                                    \
        if ((angle) < FP_ANGLE(0.0f))                                                    \
        {                                                                                \
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT); \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT); \
        }                                                                                \
    }

#define ANIM_STUFF(mult, div)                                                                                                            \
    temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) * \
           mult / div;                                                                                                                   \
    larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(chara->rotation_24.vy), Q12_SHIFT);                                           \
    larvalStalkerProps.angle_102 = FP_FROM(temp * Math_Cos(chara->rotation_24.vy), Q12_SHIFT);

#define Chara_MovementAngleGet func_8006FAFC
void sharedFunc_800CF168_1_s00(s_SubCharacter* chara)
{
    s32     temp;
    VECTOR3 pos;
    q19_12  mag0;
    s32     validStep;
    s32     idxInfo;
    q19_12  distStep;
    q19_12  baseDistMax;
    q19_12  angle0;
    q19_12  tmpSinCos;
    q19_12  targetX;
    q19_12  targetZ;

    #define larvalStalkerProps chara->properties_E4.larvalStalker

    angle0 = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                   g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                           chara->rotation_24.vy);
    mag0 = Math_Vector2MagCalc(larvalStalkerProps.targetX - chara->position_18.vx,
                                larvalStalkerProps.targetZ - chara->position_18.vz);
    chara->rotation_24.vy = func_8005BF38(chara->rotation_24.vy);

    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != 1)
    {
        chara->field_44.field_0 = 0;
    }

    idxInfo = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3;
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

    if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                            g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) < ((baseDistMax * 2) + distStep))
    {
        larvalStalkerProps.targetX = g_SysWork.playerWork_4C.player_0.position_18.vx;
        larvalStalkerProps.targetZ = g_SysWork.playerWork_4C.player_0.position_18.vz;
    }

    switch (chara->model_0.state_2)
    {
        case 1:
            chara->moveSpeed_38 = Q12(0.0f);

            if (!Rng_GenerateInt(0, 31))
            {
                chara->health_B0 = NO_VALUE;
            }
            break;

        case 2:
            Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(0.3f));

            if (func_80070184(chara, Q12(1.0f), chara->rotation_24.vy) || !Rng_GenerateInt(0, 63))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                chara->model_0.state_2 = 3;
            }

            if (func_8006FD90(chara, 3, baseDistMax, distStep)) 
            {
                chara->model_0.state_2 = 7;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                larvalStalkerProps.flags_E8 |= 1 << 2;
            }
            break;

        case 3:
            Chara_MoveSpeedUpdate(chara, Q12(1.5f));

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(11, true))
            {
                if (larvalStalkerProps.angle_108 > FP_ANGLE(0.0f))
                {
                    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                    larvalStalkerProps.angle_108 -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);

                    if ((larvalStalkerProps.angle_108) <= FP_ANGLE(0.0f)) 
                    {
                        larvalStalkerProps.angle_108 = FP_ANGLE(0.0f);
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                    }
                } 
                else if (larvalStalkerProps.angle_108 < FP_ANGLE(0.0f)) 
                {
                    chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                    larvalStalkerProps.angle_108 += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);

                    if (!(larvalStalkerProps.angle_108 < FP_ANGLE(0.0f)))
                    {
                        larvalStalkerProps.angle_108 = FP_ANGLE(0.0f);
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                    }
                }
                else
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                }
            }
            
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(10, true)) 
            {
                validStep = func_80070184(chara, Q12(0.6f), chara->rotation_24.vy);
                if ((validStep && !Rng_GenerateInt(0,3)) || !Rng_GenerateInt(0, 31)) 
                {
                    larvalStalkerProps.angle_108 = Rng_TestProbabilityBits(11) - FP_ANGLE(90.0f); // -90 >< 90 angle.
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                }
                else if (!Rng_GenerateInt(0, 15))
                {
                    if (validStep == false)
                    {
                        chara->model_0.state_2 = 2;
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                    }
                }
            }

            if (func_8006FD90(chara, 3, baseDistMax, distStep)) 
            {
                chara->model_0.state_2 = 7;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                larvalStalkerProps.angle_108 = FP_ANGLE(0.0f);
                larvalStalkerProps.flags_E8 |= 1 << 2;
            }
            break;

        case 4:
            Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(0.3f));

            if ((larvalStalkerProps.flags_E8 & (1 << 2)) && ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 11 &&
                ((mag0 < (Q12(3.5f) - FP_TO(larvalStalkerProps.field_EA, Q12_SHIFT))) || !Rng_GenerateInt(0, 31)))
            {
                chara->model_0.state_2 = 7;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                larvalStalkerProps.flags_E8 &= ~(1 << 3);
                break;
            }

            if (mag0 >= FP_TO(larvalStalkerProps.field_EA, Q12_SHIFT) + Q12(2.0f) ||
                g_SysWork.playerWork_4C.player_0.moveSpeed_38 <= larvalStalkerProps.field_EA * Q12(1.5f) + Q12(0.5f))
            {
                if (FP_ANGLE(45.0f) > ABS(angle0) && 
                    (mag0 < (chara->field_D4.field_0 + Q12(0.05f) + g_SysWork.playerWork_4C.player_0.field_D4.field_0)))
                {
                    if (!Rng_GenerateInt(0, 7))
                    {
                        targetX = larvalStalkerProps.targetX + Rng_GenerateInt(0, Q12(1.5f) - 1);
                        targetZ = larvalStalkerProps.targetZ + Rng_GenerateInt(0, Q12(1.5f) - 1);
                        larvalStalkerProps.angle_108 = Chara_MovementAngleGet(chara, Q12(2.0f), targetX, targetZ, Q12(1.0f), true);
                        ANGLE_STUFF(func_8005BF38(larvalStalkerProps.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                    } 
                    else
                    {
                        ANGLE_STUFF_REV(angle0, FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                    }
                    break;
                }

                if ((distStep >> 1) < mag0)
                {
                    if (!Rng_GenerateInt(0, 31))
                    {
                        larvalStalkerProps.angle_108 = Chara_MovementAngleGet(chara, Q12(2.0f), larvalStalkerProps.targetX, larvalStalkerProps.targetZ, Q12(1.0f), true);
                    }

                    ANGLE_STUFF(func_8005BF38(larvalStalkerProps.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                    break;
                }

                if (larvalStalkerProps.flags_E8 & (1 << 3))
                {
                    ANGLE_STUFF(func_8005BF38(larvalStalkerProps.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                    if (!Rng_GenerateInt(0, 15))
                    {
                        larvalStalkerProps.flags_E8 &= ~(1 << 3);
                    }
                    break;
                }

                if (!(g_SysWork.field_2284[3] & 0x1)) 
                {
                    ANGLE_STUFF(angle0, FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                } 
                else
                {
                    chara->model_0.state_2 = 7;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                }
            } 
            else
            {
                chara->model_0.state_2 = 8;

                func_8005DC1C(Sfx_Unk1429, &chara->position_18, Q8(0.5f), 0);

                larvalStalkerProps.timer_EC = 0;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                larvalStalkerProps.flags_E8 &= ~(1 << 3);

            }
            break;

        case 5:
            ANGLE_STUFF(angle0, FP_ANGLE(1.5f), FP_ANGLE(30.0f));

            if (larvalStalkerProps.flags_E8 & (1 << 6))
            {
                larvalStalkerProps.animTime_104 = chara->model_0.anim_4.time_4;
                chara->moveSpeed_38 = Q12(0.0f);
                larvalStalkerProps.timer_EC += g_DeltaTime0;

                if (larvalStalkerProps.timer_EC > Q12(1.8f)) 
                {
                    if (!(Rng_Rand16() & 0x7))
                    {
                        func_8005DC1C(0, &chara->position_18, Q8(0.5f), 0);
                        larvalStalkerProps.timer_EC = Q12(0.0f);

                        if (g_SysWork.playerWork_4C.player_0.field_40 == NO_VALUE) 
                        {
                            g_SysWork.playerWork_4C.player_0.field_40 = func_8005C7D0(chara);
                        }

                        g_SysWork.playerWork_4C.player_0.attackReceived_41 = WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Multitap);
                        g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Multitap)].field_4, Q12_SHIFT) * ((Rng_Rand16() & 0x1F) + 0x55)) / 100;
                    }
                }

                angle0 = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - chara->rotation_24.vy);
                if (FP_ANGLE(90.0f) < ABS(angle0))
                {
                    if (mag0 >= Q12(0.29004f))
                    {
                        tmpSinCos = Math_Sin(chara->rotation_24.vy);
                        larvalStalkerProps.angle_100 = ((mag0 - Q12(0.28f)) <= Q12(0.02f)) ?
                                                       FP_MULTIPLY(mag0 - Q12(0.28f), tmpSinCos, Q12_SHIFT) :
                                                       FP_MULTIPLY(Q12(0.02f), tmpSinCos, Q12_SHIFT);

                        tmpSinCos = Math_Cos(chara->rotation_24.vy);
                        larvalStalkerProps.angle_102 = ((mag0 - Q12(0.28f)) <= Q12(0.02f)) ?
                                                       FP_MULTIPLY(mag0 - Q12(0.28f), tmpSinCos, Q12_SHIFT) :
                                                       FP_MULTIPLY(Q12(0.02f), tmpSinCos, Q12_SHIFT);
                    }

                    if (mag0 < Q12(0.27f))
                    {
                        larvalStalkerProps.angle_100 = FP_MULTIPLY(((mag0 - Q12(0.28f)) < Q12(-0.02f)) ? Q12(-0.02f) : (mag0 - Q12(0.28f)), Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
                        larvalStalkerProps.angle_102 = FP_MULTIPLY(((mag0 - Q12(0.28f)) < Q12(-0.02f)) ? Q12(-0.02f) : (mag0 - Q12(0.28f)), Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
                    }
                }
                else
                {
                    if (mag0 > Q12(0.18f))
                    {
                        tmpSinCos = Math_Sin(chara->rotation_24.vy);
                        larvalStalkerProps.angle_100 = ((mag0 - Q12(0.17f)) <= Q12(0.02f)) ?
                                                       FP_MULTIPLY(mag0 - Q12(0.17f), tmpSinCos, Q12_SHIFT) :
                                                       FP_MULTIPLY(Q12(0.02f), tmpSinCos, Q12_SHIFT);

                        tmpSinCos = Math_Cos(chara->rotation_24.vy);
                        larvalStalkerProps.angle_102 = ((mag0 - Q12(0.17f)) <= Q12(0.02f)) ?
                                                       FP_MULTIPLY(mag0 - Q12(0.17f), tmpSinCos, Q12_SHIFT) :
                                                       FP_MULTIPLY(Q12(0.02f), tmpSinCos, Q12_SHIFT);
                    }

                    if (mag0 < Q12(0.16f))
                    {
                        larvalStalkerProps.angle_100 = FP_MULTIPLY(((mag0 - Q12(0.17f)) < Q12(-0.02f)) ? Q12(-0.02f) : (mag0 - Q12(0.17f)), Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
                        larvalStalkerProps.angle_102 = FP_MULTIPLY(((mag0 - Q12(0.17f)) < Q12(-0.02f)) ? Q12(-0.02f) : (mag0 - Q12(0.17f)), Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
                    }
                }

                if ((&g_SysWork.playerWork_4C.player_0)->attackReceived_41 == NO_VALUE)
                {
                    g_SysWork.field_2284[3] &= ~(1 << 0);
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(5, false);
                    chara->model_0.state_2 = 10;
                    larvalStalkerProps.flags_E8 &= ~(1 << 6);
                    chara->field_E1_0 = 3;
                    chara->properties_E4.dummy.properties_E8[3].val16[0] = 0;

                    func_8005DC1C(Sfx_Unk1429, &chara->position_18, Q8(0.5f), 0);
                }
                else
                {
                    chara->field_E1_0 = 1;
                }
            }
            else
            {
                if (mag0 < ((chara->field_D4.field_0 + Q12(0.02f)) + g_SysWork.playerWork_4C.player_0.field_D4.field_0))
                {
                    Chara_MoveSpeedUpdate(chara, Q12(1.5f));
                }

                pos     = chara->position_18;
                pos.vy += chara->field_C8.field_8;

                if (func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_Unk31, AttackInputType_Multitap), chara, &pos, &g_SysWork.playerWork_4C.player_0, chara->rotation_24.vy, FP_ANGLE(90.0f)) != NO_VALUE)
                {
                    larvalStalkerProps.timer_EC = Q12(0.0f);
                    larvalStalkerProps.flags_E8 |= 1 << 6;
                }
                else if (mag0 > Q12(0.5f))
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                    chara->model_0.state_2 = 4;
                }

            }
            break;

        case 6:
            Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(1.0f));

            if (larvalStalkerProps.timer_EC == Q12(0.0f)) 
            {
                larvalStalkerProps.angle_108 = Chara_MovementAngleGet(chara, Q12(2.0f), larvalStalkerProps.targetX, larvalStalkerProps.targetZ, Q12(1.0f), false);
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

            ANGLE_STUFF(func_8005BF38(larvalStalkerProps.angle_108 - chara->rotation_24.vy), 33, 682);

            if ((chara->moveSpeed_38 >= Q12(0.9004f)) && !Rng_TestProbabilityBits(8))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(6, false);
                larvalStalkerProps.timer_EC = Q12(0.0f);
                chara->properties_E4.dummy.properties_E8[3].val16[0] = 0;
                chara->model_0.state_2 = 9;

                func_8005DC1C(Sfx_Unk1429, &chara->position_18, Q8(0.5f), 0);
            } 
            else
            {
                if ((Q12(4.8f) - (larvalStalkerProps.field_EA * Q12(1.2f))) < mag0 && !Rng_GenerateInt(0, 31))
                {
                    chara->model_0.state_2 = 7;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                    larvalStalkerProps.timer_EC = Q12(0.0f);
                    larvalStalkerProps.angle_108 = Q12(0.0f);
                    larvalStalkerProps.flags_E8 |= 1 << 2;
                }

            }
            break;

        case 7:
            if (func_800700F8(chara, &g_SysWork.playerWork_4C.player_0) || (distStep * 2) < mag0)
            {
                chara->model_0.state_2 = 3;

                if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != ANIM_STATUS(5, false))
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                }
            } 
            else
            {
                if (FP_ANGLE(1.5f) <= ABS(angle0) && ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != 10)
                {
                    Chara_MoveSpeedUpdate3(chara, Q12(0.375f), Q12(0.0f));

                    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != ANIM_STATUS(5, true))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                    }

                    if (angle0 > FP_ANGLE(0.0f))
                    {
                        chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                    }
                    else
                    {
                        chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                    }
                }
                else
                {
                    Chara_MoveSpeedUpdate(chara, Q12(1.5f));

                    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != ANIM_STATUS(5, false))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                    }
                }

                larvalStalkerProps.timer_EC += g_DeltaTime0;

                if (!(g_SysWork.field_2284[3] & 0x1) && (Q12(5.0f) - FP_TO(larvalStalkerProps.field_EA, Q12_SHIFT)) < larvalStalkerProps.timer_EC)
                {
                    chara->model_0.state_2 = 4;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                    larvalStalkerProps.timer_EC = Q12(0.0f);

                    larvalStalkerProps.flags_E8 &= ~(1 << 2);
                    if (larvalStalkerProps.field_EA < 2)
                    {
                        larvalStalkerProps.field_EA++;
                    }
                } 
                else
                {
                    if (mag0 < (FP_TO(larvalStalkerProps.field_EA, Q12_SHIFT) + Q12(2.0f)) &&
                        g_SysWork.playerWork_4C.player_0.moveSpeed_38 > ((larvalStalkerProps.field_EA * Q12(1.5f)) + Q12(0.5f)))
                    {
                        chara->model_0.state_2 = 8;

                        func_8005DC1C(Sfx_Unk1429, &chara->position_18, Q8(0.5f), 0);

                        larvalStalkerProps.timer_EC = Q12(0.0f);
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                        larvalStalkerProps.flags_E8 &= ~(1 << 3);
                    }
                }
            }
            break;

        case 8:
            larvalStalkerProps.timer_10A += FP_MULTIPLY_PRECISE(g_DeltaTime0, Rng_Rand16() & 0xFFF, Q12_SHIFT);
            if (larvalStalkerProps.timer_10A > Q12(3.5f))
            {
                larvalStalkerProps.timer_10A = Q12(3.5f);
            }

            Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(1.0f));

            if (larvalStalkerProps.timer_EC == Q12(0.0f))
            {
                larvalStalkerProps.angle_108 = Chara_MovementAngleGet(chara, Q12(1.5f), larvalStalkerProps.targetX, larvalStalkerProps.targetZ, Q12(1.0f), false);
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

            ANGLE_STUFF(func_8005BF38(larvalStalkerProps.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), 682);

            if ((chara->moveSpeed_38 >= Q12(0.9004f)) && !(Rng_Rand16() & 0x3F))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(6, false);
                larvalStalkerProps.timer_EC = Q12(0.0f);
                chara->properties_E4.dummy.properties_E8[3].val16[0] = 0;
                chara->model_0.state_2 = 9;

                func_8005DC1C(Sfx_Unk1429, &chara->position_18, Q8(0.5f), 0);
            }

            if (!(larvalStalkerProps.flags_E8 & (1 << 7)))
            {
                chara->properties_E4.player.field_F0 += g_DeltaTime0;

                if (larvalStalkerProps.field_F0 > Q12(5.0f) && !(Rng_Rand16() & 0x3F))
                {
                    chara->properties_E4.player.field_F0 = 0;
                    larvalStalkerProps.timer_EC = Q12(0.0f);
                    larvalStalkerProps.angle_108 = Q12(0.0f);
                    chara->model_0.state_2 = 6;
                }
            }
            break;

        case 9:
            larvalStalkerProps.timer_10A += FP_MULTIPLY_PRECISE(g_DeltaTime0, (Rng_Rand16() & 0x7FF) + Q12(0.5f), Q12_SHIFT);
            if (larvalStalkerProps.timer_10A > Q12(3.5f))
            {
                larvalStalkerProps.timer_10A = Q12(3.5f);
            }

            Chara_MoveSpeedUpdate(chara, Q12(0.5f));

            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 86, 92))
            {
                ANIM_STUFF(Q12(0.15f), Q12(6.0f));
            }

            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 95, 105))
            {
                chara->moveSpeed_38 = 0;
            }

            if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == ANIM_STATUS(5, false))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                chara->model_0.state_2 = 8;
            }
            break;

        case 10:
            Chara_MoveSpeedUpdate(chara, Q12(1.5f));

            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 86, 92))
            {
                ANIM_STUFF(Q12(0.15f), Q12(6.0f));
            }

            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 41, 49))
            {
                temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant,
                                        g_DeltaTime0, Q12_SHIFT) * Q12(0.3f) / Q12(9.0f);
                larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
                larvalStalkerProps.angle_102 = FP_FROM(temp * Math_Cos(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            }

            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 95, 96) && chara->moveSpeed_38 != Q12(0.0f))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(16, true);
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(16, true) && chara->moveSpeed_38 == Q12(0.0f) && !(Rng_Rand16() & 0x7)) 
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(6, true);
            }

            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 61, 62) && chara->moveSpeed_38 != Q12(0.0f))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(15, true);
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(15, true) && chara->moveSpeed_38 == Q12(0.0f) && !(Rng_Rand16() & 0x7))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(5, true);
            }

            if ((ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 10) && !(Rng_Rand16() & 0x7))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                chara->model_0.state_2 = 8;
                larvalStalkerProps.flags_E8 &= ~(1 << 1);
            }
            break;

        case 11:
            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 143, 151)) 
            {
                ANIM_STUFF(Q12(0.3f), Q12(9.0f));
            }

            if (chara->health_B0 == Q12(0.0f) && ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 9)
            {
                chara->model_0.state_2 = 13;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(4, false);
                func_80037DC4(chara);
            }

            if (larvalStalkerProps.flags_E8 & (1 << 1))
            {
                Chara_MoveSpeedUpdate(chara, Q12(1.5f));

                if (chara->moveSpeed_38 == Q12(0.0f))
                {
                    larvalStalkerProps.flags_E8 &= ~(1 << 1);
                }
                break;
            }

            Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(0.1f));

            if (larvalStalkerProps.timer_EC == Q12(0.0f))
            {
                larvalStalkerProps.angle_108 = Chara_MovementAngleGet(chara, FP_ANGLE(180.0f), larvalStalkerProps.targetX, larvalStalkerProps.targetZ, Q12(1.0f), false);
            }

            larvalStalkerProps.timer_EC += g_DeltaTime0;
            if (larvalStalkerProps.timer_EC > Q12(1.0f))
            {
                larvalStalkerProps.timer_EC = Q12(0.0f);
            }

            ANGLE_STUFF(func_8005BF38(larvalStalkerProps.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), 170);
            break;

        case 12:
            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x79, 0x7F))
            {
                temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant,
                                        g_DeltaTime0, Q12_SHIFT) * Q12(0.15f) / Q12(6.0f);
                larvalStalkerProps.angle_100 = FP_FROM(temp * Math_Sin(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
                larvalStalkerProps.angle_102 = FP_FROM(temp * Math_Cos(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            }

            chara->flags_3E |= CharaFlag_Unk2;

            if (chara->health_B0 <= Q12(0.0f) && ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 2) 
            {
                chara->flags_3E &= ~CharaFlag_Unk2;
                chara->model_0.state_2 = 13;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(3, false);
                func_80037DC4(chara);
            }

            Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(0.0f));
            break;

        case 13:
            chara->flags_3E &= ~CharaFlag_Unk2;

            if (chara->health_B0 <= Q12(0.0f) && func_8005C7D0(chara) != g_SysWork.targetNpcIdx_2353)
            {
                chara->health_B0 = NO_VALUE;
                chara->field_E1_0 = 0;
            }

            if (chara->moveSpeed_38 == Q12(0.0f) && !(chara->properties_E4.player.afkTimer_E8 & 0x30))
            {
                if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == ANIM_STATUS(6, true)) 
                {
                    func_800622B8(3, chara, 3, 3);
                    larvalStalkerProps.flags_E8 |= 1 << 4;
                }
                else if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == ANIM_STATUS(7, false))
                {
                    func_800622B8(3, chara, 4, 3);
                    larvalStalkerProps.flags_E8 |= 1 << 4;
                }
            }

            Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(0.0f));
            break;
    }

    chara->damage_B4.amount_C      = Q12(0.0f);
    chara->damage_B4.position_0.vz = Q12(0.0f);
    chara->damage_B4.position_0.vy = Q12(0.0f);
    chara->damage_B4.position_0.vx = Q12(0.0f);
}

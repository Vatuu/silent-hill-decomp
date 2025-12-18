#define ANGLE_STUFF(anglevar, limit, mult)\
    angle0 = anglevar;\
    if (limit <= ABS(angle0)) \
    { \
        if (angle0 > 0)\
        {\
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT);\
        }\
        else\
        {\
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT);\
        }\
    }

#define ANGLE_STUFF_REV(anglevar, limit, mult)\
    if (limit <= ABS(anglevar)) \
    { \
        if (anglevar < 0)\
        {\
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT);\
        }\
        else\
        {\
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, mult, Q12_SHIFT);\
        }\
    }

#define ANIM_STUFF(mult, div)\
    temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) \
        * mult / div; \
    PROPS.angle_100 = FP_FROM(temp * Math_Sin(chara->rotation_24.vy), Q12_SHIFT); \
    PROPS.angle_102 = FP_FROM(temp * Math_Cos(chara->rotation_24.vy), Q12_SHIFT);

#define Chara_MovementAngleFind func_8006FAFC
void sharedFunc_800CF168_1_s00(s_SubCharacter* chara)
{
    s32 temp;
    VECTOR3 pos;
    s32 magn0;
    s32 validStep;
    s32 idxInfo;
    s32 distStep;
    s32 baseDistMax;
    s32 angle0;
    s32 tmpSinCos;
    s32 targetX;
    s32 targetZ;
    #define PROPS chara->properties_E4.larvalStalker

    angle0 = func_8005BF38((ratan2(
        g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
        g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) - chara->rotation_24.vy));
    magn0 = Math_Vector2MagCalc(
        PROPS.targetX - chara->position_18.vx,
        PROPS.targetZ - chara->position_18.vz
    );
    chara->rotation_24.vy = func_8005BF38(chara->rotation_24.vy);
    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != 1)
    {
        chara->field_44.field_0 = 0;
    }

    idxInfo = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3;
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

    if (Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                           g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) < ((baseDistMax * 2) + distStep))
    {
        PROPS.targetX = g_SysWork.player_4C.chara_0.position_18.vx;
        PROPS.targetZ = g_SysWork.player_4C.chara_0.position_18.vz;
    }

    switch (chara->model_0.state_2)
    {
        
    case 1:
        chara->moveSpeed_38 = 0;
        if (!Rng_GenerateInt(0, 31))
        {
            chara->health_B0 = -1;
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
            PROPS.flags_E8 |= 4;
        }
        break;
    case 3:
        Chara_MoveSpeedUpdate(chara, Q12(1.5f));
        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(11, true))
        {
            if (PROPS.angle_108 > 0)
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                PROPS.angle_108 -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);

                if ((PROPS.angle_108) <= 0) 
                {
                    PROPS.angle_108 = 0;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                }
            } 
            else if (PROPS.angle_108 < 0) 
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
                PROPS.angle_108 += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);

                if (!(PROPS.angle_108 < 0))
                {
                    PROPS.angle_108 = 0;
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
                PROPS.angle_108 = Rng_TestProbabilityBits(11) - 0x400; // -90 >< 90 angle
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
            PROPS.angle_108 = 0;
            PROPS.flags_E8 |= 4;
        }
        break;
    case 4:
        Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(0.3f));
        if ((PROPS.flags_E8 & 4) && ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 11 &&
            ((magn0 < (Q12(3.5f) - FP_TO(PROPS.field_EA, Q12_SHIFT))) || !Rng_GenerateInt(0, 31)))
        {
            chara->model_0.state_2 = 7;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
            PROPS.flags_E8 &= ~8;
            break;
        }
        if (magn0 >= FP_TO(PROPS.field_EA, Q12_SHIFT) + Q12(2.0f) ||
            g_SysWork.player_4C.chara_0.moveSpeed_38 <= PROPS.field_EA * Q12(1.5f) + Q12(0.5f))
        {
            if (FP_ANGLE(45.0f) > ABS(angle0) && 
                (magn0 < (chara->field_D4.field_0 + Q12(0.05f) + g_SysWork.player_4C.chara_0.field_D4.field_0)))
            {
                if (!Rng_GenerateInt(0, 7))
                {
                    targetX = PROPS.targetX + Rng_GenerateInt(0, 0x1800-1);
                    targetZ = PROPS.targetZ + Rng_GenerateInt(0, 0x1800-1);
                    PROPS.angle_108 = Chara_MovementAngleFind(chara, Q12(2.0f), targetX, targetZ, Q12(1.0f), true);
                    ANGLE_STUFF(func_8005BF38(PROPS.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                } 
                else
                {
                    ANGLE_STUFF_REV(angle0, FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                }
                break;
            }
            if ((distStep >> 1) < magn0)
            {
                if (!Rng_GenerateInt(0, 31))
                {
                    PROPS.angle_108 = Chara_MovementAngleFind(chara, Q12(2.0f), PROPS.targetX, PROPS.targetZ, Q12(1.0f), true);
                }
                ANGLE_STUFF(func_8005BF38(PROPS.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                break;
            }
            if (PROPS.flags_E8 & 8)
            {
                ANGLE_STUFF(func_8005BF38(PROPS.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), FP_ANGLE(30.0f));
                if (!Rng_GenerateInt(0, 15))
                {
                    PROPS.flags_E8 &= ~8;
                }
                break;
            }
            if (!(g_SysWork.field_2284[3] & 1)) 
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
            func_8005DC1C(0x595, &chara->position_18, 0x80, 0);
            PROPS.timer_EC = 0;
            chara->model_0.anim_4.status_0 = 0x18;
            PROPS.flags_E8 &= ~8;

        }
        break;
    case 5:
        ANGLE_STUFF(angle0, FP_ANGLE(1.5f), FP_ANGLE(30.0f));
        if (PROPS.flags_E8 & 0x40)
        {
            PROPS.animTime_104 = chara->model_0.anim_4.time_4;
            chara->moveSpeed_38 = 0;
            PROPS.timer_EC += g_DeltaTime0;

            if (PROPS.timer_EC > Q12(1.8f)) 
            {
                if (!(Rng_Rand16() & 7))
                {
                    func_8005DC1C(0, &chara->position_18, Q8(0.5f), 0);
                    PROPS.timer_EC = 0;
                    if (g_SysWork.player_4C.chara_0.field_40 == -1) 
                    {
                        g_SysWork.player_4C.chara_0.field_40 = func_8005C7D0(chara);
                    }
                    g_SysWork.player_4C.chara_0.attackReceived_41 = 0x34;
                    g_SysWork.player_4C.chara_0.damage_B4.amount_C += 
                        (FP_TO(D_800AD4C8[0x34].field_4, Q12_SHIFT) * ((Rng_Rand16() & 0x1F) + 0x55)) / 100;
                }
            }
            angle0 = func_8005BF38(g_SysWork.player_4C.chara_0.rotation_24.vy - chara->rotation_24.vy);
            if (FP_ANGLE(90.0f) < ABS(angle0))
            {
                if (magn0 >= 0x4A4)
                {
                    tmpSinCos = Math_Sin(chara->rotation_24.vy);
                    PROPS.angle_100 = ((magn0 - 0x47A) < 0x52)
                        ? ((magn0 - 0x47A) * tmpSinCos) >> 0xC
                        : (0x51 * tmpSinCos) >> 0xC;

                    tmpSinCos = Math_Cos(chara->rotation_24.vy);
                    PROPS.angle_102 = ((magn0 - 0x47A) < 0x52)
                        ? ((magn0 - 0x47A) * tmpSinCos) >> 0xC
                        : (0x51 * tmpSinCos) >> 0xC;
                }
                if (magn0 < 0x451)
                {
                    PROPS.angle_100 = (((magn0 - 0x47A) < -0x51 ? -0x51 : (magn0 - 0x47A)) * Math_Sin(chara->rotation_24.vy)) >> 0xC;
                    PROPS.angle_102 = (((magn0 - 0x47A) < -0x51 ? -0x51 : (magn0 - 0x47A)) * Math_Cos(chara->rotation_24.vy)) >> 0xC;
                }
            }
            else
            {
                if (magn0 >= 0x2E2)
                {
                    tmpSinCos = Math_Sin(chara->rotation_24.vy);
                    PROPS.angle_100 = ((magn0 - 0x2B8) < 0x52)
                        ? ((magn0 - 0x2B8) * tmpSinCos) >> 0xC
                        : (0x51 * tmpSinCos) >> 0xC;

                    tmpSinCos = Math_Cos(chara->rotation_24.vy);
                    PROPS.angle_102 = ((magn0 - 0x2B8) < 0x52)
                        ? ((magn0 - 0x2B8) * tmpSinCos) >> 0xC
                        : (0x51 * tmpSinCos) >> 0xC;
                }
                if (magn0 < 0x28F)
                {
                    PROPS.angle_100 = (((magn0 - 0x2B8) < -0x51 ? -0x51 : (magn0 - 0x2B8)) * Math_Sin(chara->rotation_24.vy)) >> 0xC;
                    PROPS.angle_102 = (((magn0 - 0x2B8) < -0x51 ? -0x51 : (magn0 - 0x2B8)) * Math_Cos(chara->rotation_24.vy)) >> 0xC;
                }
            }
            if ((&g_SysWork.player_4C.chara_0)->attackReceived_41 == -1)
            {
                g_SysWork.field_2284[3] &= ~1;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(5, false);
                chara->model_0.state_2 = 0xA;
                PROPS.flags_E8 &= ~0x40;
                chara->field_E1_0 = 3;
                chara->properties_E4.dummy.properties_E8[3].val16[0] = 0;
                func_8005DC1C(0x595, &chara->position_18, Q8(0.5f), 0);
            }
            else
            {
                chara->field_E1_0 = 1;
            }
        }
        else
        {
            if (magn0 < chara->field_D4.field_0 + 0x51 + g_SysWork.player_4C.chara_0.field_D4.field_0)
            {
                Chara_MoveSpeedUpdate(chara, Q12(1.5f));
            }

            
            pos = chara->position_18;
            pos.vy += chara->field_C8.field_8;
            if (func_8008A0E4(1, 0x33, chara, &pos, &g_SysWork.player_4C.chara_0, chara->rotation_24.vy, FP_ANGLE(90.0f)) != -1)
            {
                PROPS.timer_EC = 0;
                PROPS.flags_E8 |= 0x40;
            }
            else if (magn0 > Q12(0.5f))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                chara->model_0.state_2 = 4;
            }

        }
        break;
    case 6:
        Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(1.0f));
        if (PROPS.timer_EC == 0) 
        {
            PROPS.angle_108 = Chara_MovementAngleFind(chara, Q12(2.0f), PROPS.targetX, PROPS.targetZ, Q12(1.0f), false);
            if (PROPS.angle_108 == Q12(1.0f)) 
            {
                PROPS.angle_108 = Rng_TestProbabilityBits(12);
            }
        }
        PROPS.timer_EC += g_DeltaTime0;
        if (PROPS.timer_EC > Q12(0.8f))
        {
            PROPS.timer_EC = 0;
        }
        ANGLE_STUFF(func_8005BF38(PROPS.angle_108 - chara->rotation_24.vy), 0x21, 0x2AA);
        if ((chara->moveSpeed_38 >= Q12(0.9004f)) && !Rng_TestProbabilityBits(8))
        {
            chara->model_0.anim_4.status_0 = 0xC;
            PROPS.timer_EC = 0;
            chara->properties_E4.dummy.properties_E8[3].val16[0] = 0;
            chara->model_0.state_2 = 9;
            func_8005DC1C(0x595, &chara->position_18, Q8(0.5f), 0);
        } 
        else
        {
            if (Q12(4.8f) - PROPS.field_EA * Q12(1.2f) < magn0 && !Rng_GenerateInt(0, 31))
            {
                chara->model_0.state_2 = 7;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                PROPS.timer_EC = 0;
                PROPS.angle_108 = 0;
                PROPS.flags_E8 |= 4;
            }

        }
        break;
    case 7:
        if ((func_800700F8(chara, &g_SysWork.player_4C.chara_0)) || ((distStep * 2) < magn0))
        {
            chara->model_0.state_2 = 3;
            if ((chara->model_0.anim_4.status_0 >> 1) != ANIM_STATUS(5, false))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
            }
        } 
        else
        {
            if (FP_ANGLE(1.5f) <= ABS(angle0) && (chara->model_0.anim_4.status_0 >> 1) != 0xA)
            {
                Chara_MoveSpeedUpdate3(chara, Q12(0.375f), 0);
                if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != ANIM_STATUS(5, true))
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                }
                if (angle0 > 0)
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
                if ((chara->model_0.anim_4.status_0 >> 1) != ANIM_STATUS(5, false))
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                }
            }
            PROPS.timer_EC += g_DeltaTime0;
            if (!(g_SysWork.field_2284[3] & 1) && Q12(5.0f) - FP_TO(PROPS.field_EA, Q12_SHIFT) < PROPS.timer_EC)
            {
                chara->model_0.state_2 = 4;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                PROPS.timer_EC = 0;
                PROPS.flags_E8 &= ~4;
                if (PROPS.field_EA < 2)
                {
                    PROPS.field_EA++;
                }
            } 
            else
            {
                if (magn0 < FP_TO(PROPS.field_EA, Q12_SHIFT) + Q12(2.0f) &&
                    g_SysWork.player_4C.chara_0.moveSpeed_38 > PROPS.field_EA * Q12(1.5f) + Q12(0.5f))
                {
                    chara->model_0.state_2 = 8;
                    func_8005DC1C(0x595, &chara->position_18, Q8(0.5f), 0);
                    PROPS.timer_EC = 0;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                    PROPS.flags_E8 &= ~8;
                }
            }
        }
        break;
    case 8:
        PROPS.timer_10A += FP_MULTIPLY_PRECISE(g_DeltaTime0, Rng_Rand16() & 0xFFF, Q12_SHIFT);
        if (PROPS.timer_10A > Q12(3.5f))
        {
            PROPS.timer_10A = Q12(3.5f);
        }
        Chara_MoveSpeedUpdate3(chara, Q12(1.5f), Q12(1.0f));
        if (PROPS.timer_EC == 0)
        {
            PROPS.angle_108 = Chara_MovementAngleFind(chara, Q12(1.5f), PROPS.targetX, PROPS.targetZ, Q12(1.0f), false);
            if (PROPS.angle_108 == Q12(1.0f))
            {
                PROPS.angle_108 = Rng_Rand16() & 0xFFF;
            }
        }
        PROPS.timer_EC += g_DeltaTime0;
        if (PROPS.timer_EC > Q12(0.8f))
        {
            PROPS.timer_EC = 0;
        }
        ANGLE_STUFF(func_8005BF38(PROPS.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), 0x2AA);
        if ((chara->moveSpeed_38 >= Q12(0.9004f)) && !(Rng_Rand16() & 0x3F))
        {
            chara->model_0.anim_4.status_0 = 0xC;
            PROPS.timer_EC = 0;
            chara->properties_E4.dummy.properties_E8[3].val16[0] = 0;
            chara->model_0.state_2 = 9;
            func_8005DC1C(0x595, &chara->position_18, 0x80, 0);
        }
        if (!(PROPS.flags_E8 & 0x80))
        {
            chara->properties_E4.player.field_F0 += g_DeltaTime0;
            if (PROPS.field_F0 > Q12(5.0f) && !(Rng_Rand16() & 0x3F))
            {
                chara->properties_E4.player.field_F0 = 0;
                PROPS.timer_EC = 0;
                PROPS.angle_108 = 0;
                chara->model_0.state_2 = 6;
            }
        }
        break;
    case 9:
        PROPS.timer_10A += FP_MULTIPLY_PRECISE(g_DeltaTime0, (Rng_Rand16() & 0x7FF) + 0x800, Q12_SHIFT);
        if (PROPS.timer_10A > Q12(3.5f))
        {
            PROPS.timer_10A = Q12(3.5f);
        }
        Chara_MoveSpeedUpdate(chara, Q12(0.5f));

        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x56, 0x5C))
        {
            ANIM_STUFF(Q12(0.15f), Q12(6.0f));
        }

        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x5F, 0x69))
        {
            chara->moveSpeed_38 = 0;
        }
        if ((chara->model_0.anim_4.status_0 >> 1) == ANIM_STATUS(5, false))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
            chara->model_0.state_2 = 8;
        }
        break;
    case 10:
        Chara_MoveSpeedUpdate(chara, Q12(1.5f));
        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x56, 0x5C))
        {
            ANIM_STUFF(Q12(0.15f), Q12(6.0f));
        }
        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x29, 0x31))
        {
            temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant,
                    g_DeltaTime0, Q12_SHIFT) * Q12(0.3f) / Q12(9.0f);
            PROPS.angle_100 = FP_FROM(temp * Math_Sin(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            PROPS.angle_102 = FP_FROM(temp * Math_Cos(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
        }
        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x5F, 0x60) && (chara->moveSpeed_38 != 0))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(16, true);
        }
        if ((chara->model_0.anim_4.status_0 == 0x21) && (chara->moveSpeed_38 == 0) && !(Rng_Rand16() & 7)) 
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(6, true);
        }
        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x3D, 0x3E) && (chara->moveSpeed_38 != 0))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(15, true);
        }
        if ((chara->model_0.anim_4.status_0 == 0x1F) && (chara->moveSpeed_38 == 0) && !(Rng_Rand16() & 7))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(5, true);
        }
        if ((ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 0xA) && !(Rng_Rand16() & 7))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
            chara->model_0.state_2 = 8;
            PROPS.flags_E8 &= ~2;
        }
        break;
    case 11:
        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x8F, 0x97)) 
        {
            ANIM_STUFF(Q12(0.3f), Q12(9.0f));
        }
        if ((chara->health_B0 == 0) && (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 9))
        {
            chara->model_0.state_2 = 0xD;
            chara->model_0.anim_4.status_0 = 8;
            func_80037DC4(chara);
        }
        if (PROPS.flags_E8 & 2)
        {
            Chara_MoveSpeedUpdate(chara, Q12(1.5f));
            if (chara->moveSpeed_38 == 0)
            {
                PROPS.flags_E8 &= ~2;
            }
            break;
        }
        Chara_MoveSpeedUpdate3(chara, Q12(1.5f), 0x199);
        if (PROPS.timer_EC == 0)
        {
            PROPS.angle_108 = Chara_MovementAngleFind(chara, FP_ANGLE(180.0f), PROPS.targetX, PROPS.targetZ, Q12(1.0f), false);
        }
        PROPS.timer_EC += g_DeltaTime0;
        if (PROPS.timer_EC > Q12(1.0f))
        {
            PROPS.timer_EC = 0;
        }
        ANGLE_STUFF(func_8005BF38(PROPS.angle_108 - chara->rotation_24.vy), FP_ANGLE(1.5f), 0xAA);
        break;

    case 12:
        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 0x79, 0x7F))
        {
            temp = FP_MULTIPLY_PRECISE(LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant,
                    g_DeltaTime0, Q12_SHIFT) * Q12(0.15f) / Q12(6.0f);
            PROPS.angle_100 = FP_FROM(temp * Math_Sin(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            PROPS.angle_102 = FP_FROM(temp * Math_Cos(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
        }
        chara->flags_3E |= 2;
        if (chara->health_B0 <= 0 && ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 2) 
        {
            chara->flags_3E &= ~2;
            chara->model_0.state_2 = 0xD;
            chara->model_0.anim_4.status_0 = 6;
            func_80037DC4(chara);
        }
        Chara_MoveSpeedUpdate3(chara, Q12(1.5f), 0);
        break;
    case 13:
        chara->flags_3E &= ~2;
        if (chara->health_B0 <= 0 && func_8005C7D0(chara) != g_SysWork.targetNpcIdx_2353)
        {
            chara->health_B0 = -1;
            chara->field_E1_0 = 0;
        }
        if (!chara->moveSpeed_38 && !(chara->properties_E4.player.afkTimer_E8 & 0x30))
        {
            if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == ANIM_STATUS(6, true)) 
            {
                func_800622B8(3, chara, 3, 3);
                PROPS.flags_E8 |= 0x10;
            }
            else if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == ANIM_STATUS(7, false))
            {
                func_800622B8(3, chara, 4, 3);
                PROPS.flags_E8 |= 0x10;
            }
        }
        Chara_MoveSpeedUpdate3(chara, Q12(1.5f), 0);
        break;
    }
    chara->damage_B4.amount_C = 0;
    chara->damage_B4.position_0.vz = 0;
    chara->damage_B4.position_0.vy = 0;
    chara->damage_B4.position_0.vx = 0;
}

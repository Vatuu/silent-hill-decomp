void sharedFunc_800D3308_0_s00(s_SubCharacter* stalker)
{
    q3_12  angle;
    u16    keyframeIdx;
    q19_12 mag;
    q19_12 var_a0;
    q20_12 newHealth;

    #define stalkerProps stalker->properties_E4.stalker

    var_a0 = stalkerProps.timer_10C - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(20.0f), Q12_SHIFT);
    stalkerProps.timer_10C = MAX(var_a0, Q12(0.0f));

    if (stalker->damage_B4.amount_C > Q12(0.0f) && stalker->health_B0 > Q12(0.0f))
    {
        sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1365);
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_34, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_35, true))
    {
        stalker->damage_B4.amount_C = Q12(0.0f);
    }

    if (stalker->health_B0 > Q12(0.0f))
    {
        newHealth          = stalker->health_B0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800E3A28_0_s00, Q12_SHIFT);
        stalker->health_B0 = MIN(newHealth, stalkerProps.health_110);
    }

    if (stalker->damage_B4.amount_C > Q12(0.0f))
    {
        if (stalker->health_B0 > Q12(0.0f))
        {
            stalker->health_B0       = MAX(stalker->health_B0 - stalker->damage_B4.amount_C, Q12(0.0f));
            stalkerProps.health_110 -= stalker->damage_B4.amount_C >> 2;
            stalkerProps.flags_E8   |= StalkerFlag_0 | StalkerFlag_10;

            stalker->damage_B4.position_0.vx += FP_MULTIPLY(stalker->moveSpeed_38, Math_Sin(stalker->headingAngle_3C), Q12_SHIFT) >> 3;
            stalker->damage_B4.position_0.vz += FP_MULTIPLY(stalker->moveSpeed_38, Math_Cos(stalker->headingAngle_3C), Q12_SHIFT) >> 3;

            if (stalkerProps.flags_E8 & StalkerFlag_6)
            {
                mag          = Math_Vector2MagCalc(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
                stalker->moveSpeed_38 = (mag << 12) / 0xC000;
            }
            else
            {
                mag          = Math_Vector2MagCalc(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
                stalker->moveSpeed_38 = (mag << 12) / Q12(1.5f);
            }

            stalker->headingAngle_3C              = ratan2(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
            stalkerProps.flags_E8                |= StalkerFlag_13;
            stalkerProps.timer_10C += stalker->damage_B4.amount_C;

            if (stalkerProps.timer_10C >= sharedData_800E3A2C_0_s00 ||
                (!(stalkerProps.flags_E8 & StalkerFlag_6) && stalker->health_B0 <= sharedData_800E3A24_0_s00))
            {
                stalkerProps.timer_10C = 0;

                angle = ABS(func_8005BF38(Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                          stalker->rotation_24.vy));

                if (stalkerProps.flags_E8 & StalkerFlag_6)
                {
                    if (stalker->model_0.anim_4.status_0 == 53)
                    {
                        stalkerProps.keyframeIdx_FC = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 76;
                    }
                    else if (stalker->model_0.anim_4.status_0 == 35)
                    {
                        stalkerProps.keyframeIdx_FC = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 78;
                    }
                    else if (stalker->model_0.anim_4.status_0 == 37)
                    {
                        stalkerProps.keyframeIdx_FC = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 80;
                    }
                }
                else
                {
                    if (stalker->health_B0 > sharedData_800E3A24_0_s00 && !(stalkerProps.flags_E8 & 0x80))
                    {
                        if (stalker->model_0.controlState_2 == StalkerControl_5)
                        {
                            g_SysWork.field_2284[3] &= ~(1 << 1);
                        }

                        stalker->model_0.controlState_2 = StalkerControl_7;

                        if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) < StalkerAnim_22 ||
                            ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) > StalkerAnim_23)
                        {
                            if (angle >= FP_ANGLE(60.0f))
                            {
                                stalker->model_0.anim_4.status_0 = 46;
                            }
                            else
                            {
                                stalker->model_0.anim_4.status_0 = 44;
                            }
                        }
                    }
                    else if (stalkerProps.flags_E8 & StalkerFlag_7)
                    {
                        stalker->model_0.controlState_2 = StalkerControl_9;

                        if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) == 11)
                        {
                            if (stalker->model_0.anim_4.status_0 == 22)
                            {
                                stalkerProps.keyframeIdx_FC = 0;
                                stalker->model_0.anim_4.status_0                               = 76;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 106 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 109)
                            {
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;
                                stalker->model_0.anim_4.status_0                       = 76;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 108 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 113)
                            {
                                if (angle >= FP_ANGLE(60.0f))
                                {
                                    stalker->model_0.anim_4.status_0 = 84;
                                }
                                else
                                {
                                    stalker->model_0.anim_4.status_0 = 2;
                                }

                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;

                                if (stalkerProps.keyframeIdx_FC == 2)
                                {
                                    stalkerProps.relKeyframeIdx_FE = 2;
                                }
                                else if (stalkerProps.keyframeIdx_FC == 3)
                                {
                                    stalkerProps.relKeyframeIdx_FE = 1;
                                }
                                else
                                {
                                    stalkerProps.relKeyframeIdx_FE = 0;
                                }
                            }
                            else
                            {
                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 112 &&
                                    FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 118)
                                {
                                    if (angle >= FP_ANGLE(60.0f))
                                    {
                                        stalker->model_0.anim_4.status_0 = 86;
                                    }
                                    else
                                    {
                                        stalker->model_0.anim_4.status_0 = 6;
                                    }

                                    keyframeIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);

                                    stalkerProps.keyframeIdx_FC = keyframeIdx - 107;

                                    if (keyframeIdx == 116 || keyframeIdx == 117)
                                    {
                                        stalkerProps.relKeyframeIdx_FE = 1;
                                    }
                                    else
                                    {
                                        stalkerProps.relKeyframeIdx_FE = 2;
                                    }
                                }
                                else
                                {
                                    if (angle >= FP_ANGLE(60.0f))
                                    {
                                        stalker->model_0.anim_4.status_0 = 88;
                                    }
                                    else
                                    {
                                        stalker->model_0.anim_4.status_0 = 4;
                                    }

                                    stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;
                                }
                            }
                        }
                        else if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) == StalkerAnim_12)
                        {
                            if (stalker->model_0.anim_4.status_0 == 24)
                            {
                                stalkerProps.keyframeIdx_FC = 0;
                            }
                            else
                            {
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
                            }

                            if (stalker->model_0.anim_4.status_0 == 24 ||
                                (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 128 &&
                                 FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 136))
                            {
                                stalker->model_0.anim_4.status_0 = 78;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 135 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 142)
                            {
                                stalker->model_0.anim_4.status_0                               = 8;
                                stalkerProps.relKeyframeIdx_FE = (12 - stalkerProps.keyframeIdx_FC) >> 1;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 141 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 149)
                            {
                                stalker->model_0.anim_4.status_0 = 10;

                                switch (stalkerProps.keyframeIdx_FC)
                                {
                                    case 13:
                                        stalkerProps.relKeyframeIdx_FE = 5;
                                        break;

                                    case 14:
                                    case 15:
                                        stalkerProps.relKeyframeIdx_FE = 4;
                                        break;

                                    case 16:
                                    case 17:
                                        stalkerProps.relKeyframeIdx_FE = 3;
                                        break;

                                    default:
                                        stalkerProps.relKeyframeIdx_FE = 2;
                                        break;
                                }
                            }
                            else
                            {
                                stalker->model_0.anim_4.status_0                       = 10;
                                stalkerProps.relKeyframeIdx_FE = 1;
                            }
                        }
                        else
                        {
                            if (stalker->model_0.anim_4.status_0 == 26)
                            {
                                stalkerProps.keyframeIdx_FC = 0;
                                stalker->model_0.anim_4.status_0                       = 80;
                            }
                            else
                            {
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 158;

                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) == 0x9E || FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) == 159)
                                {
                                    stalker->model_0.anim_4.status_0 = 80;
                                }
                                else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 160 ||
                                         FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 168)
                                {
                                    stalkerProps.relKeyframeIdx_FE = 0;
                                    stalker->model_0.anim_4.status_0 = 10;
                                }
                                else
                                {
                                    stalker->model_0.anim_4.status_0 = 91;
                                }
                            }
                        }

                        stalkerProps.flags_E8 &= ~(1 << 7);
                    }
                    else
                    {
                        stalker->model_0.controlState_2 = StalkerControl_9;

                        if (angle < FP_ANGLE(60.0f))
                        {
                            if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 361 &&
                                FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 373)
                            {
                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) >= 364 &&
                                    FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) <= 367)
                                {
                                    stalkerProps.relKeyframeIdx_FE = 2;
                                }
                                else
                                {
                                    stalkerProps.relKeyframeIdx_FE = 1;
                                }

                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 362;
                            }
                            else
                            {
                                stalkerProps.relKeyframeIdx_FE = 0;
                            }

                            stalker->model_0.anim_4.status_0 = 48;
                        }
                        else
                        {
                            if (stalker->model_0.anim_4.status_0 == 23)
                            {
                                stalkerProps.relKeyframeIdx_FE = 23;
                                stalker->model_0.anim_4.status_0                       = 50;
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;
                            }
                            else if (stalker->model_0.anim_4.status_0 == 25)
                            {
                                stalkerProps.relKeyframeIdx_FE = 25;
                                stalker->model_0.anim_4.status_0                       = 50;
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 129;
                            }
                            else if (stalker->model_0.anim_4.status_0 == 27)
                            {
                                stalkerProps.relKeyframeIdx_FE = 27;
                                stalker->model_0.anim_4.status_0                       = 50;
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 158;
                            }
                            else
                            {
                                stalkerProps.relKeyframeIdx_FE = 83;
                                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_41, false);
                            }
                        }
                    }
                }

                stalkerProps.timer_F8  = Q12(0.0f);
                stalkerProps.flags_E8 &= 0xF7E7;
            }
        }
    }

    stalker->damage_B4.amount_C      = Q12(0.0f);
    stalker->damage_B4.position_0.vz = Q12(0.0f);
    stalker->damage_B4.position_0.vy = Q12(0.0f);
    stalker->damage_B4.position_0.vx = Q12(0.0f);

    #undef stalkerProps
}

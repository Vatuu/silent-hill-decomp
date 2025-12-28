void sharedFunc_800D3308_0_s00(s_SubCharacter* stalker)
{
    q3_12  angle;
    u16    keyframeIdx;
    q19_12 mag;
    q19_12 var_a0;
    q20_12 var_v1;

    #define stalkerProps stalker->properties_E4.stalker

    var_a0 = stalker->properties_E4.npc.field_10C - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(20.0f), Q12_SHIFT);
    stalker->properties_E4.npc.field_10C = MAX(var_a0, Q12(0.0f));

    if (stalker->damage_B4.amount_C > Q12(0.0f) && stalker->health_B0 > Q12(0.0f))
    {
        sharedFunc_800D7E04_0_s00(stalker, 1365);
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(34, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(35, true))
    {
        stalker->damage_B4.amount_C = Q12(0.0f);
    }

    if (stalker->health_B0 > Q12(0.0f))
    {
        var_v1          = stalker->health_B0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800E3A28_0_s00, Q12_SHIFT);
        stalker->health_B0 = MIN(var_v1, stalker->properties_E4.player.field_110);
    }

    if (stalker->damage_B4.amount_C > Q12(0.0f))
    {
        if (stalker->health_B0 > Q12(0.0f))
        {
            stalker->health_B0 = MAX(stalker->health_B0 - stalker->damage_B4.amount_C, Q12(0.0f));

            stalker->properties_E4.player.field_110                        -= stalker->damage_B4.amount_C >> 2;
            stalkerProps.flags_E8 |= StalkerFlag_0 | StalkerFlag_10;

            stalker->damage_B4.position_0.vx += FP_MULTIPLY(stalker->moveSpeed_38, Math_Sin(stalker->headingAngle_3C), Q12_SHIFT) >> 3;
            stalker->damage_B4.position_0.vz += FP_MULTIPLY(stalker->moveSpeed_38, Math_Cos(stalker->headingAngle_3C), Q12_SHIFT) >> 3;

            if (stalkerProps.flags_E8 & 0x40)
            {
                mag          = Math_Vector2MagCalc(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
                stalker->moveSpeed_38 = (mag << 12) / 0xC000;
            }
            else
            {
                mag          = Math_Vector2MagCalc(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
                stalker->moveSpeed_38 = (mag << 12) / 0x1800;
            }

            stalker->headingAngle_3C              = ratan2(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
            stalkerProps.flags_E8                |= 0x2000;
            stalker->properties_E4.npc.field_10C += stalker->damage_B4.amount_C;

            if (stalker->properties_E4.npc.field_10C >= sharedData_800E3A2C_0_s00 ||
                (!(stalkerProps.flags_E8 & 0x40) && stalker->health_B0 <= sharedData_800E3A24_0_s00))
            {
                stalker->properties_E4.npc.field_10C = 0;

                angle = ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                                 g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz) -
                                          stalker->rotation_24.vy));

                if (stalkerProps.flags_E8 & 0x40)
                {
                    if (stalker->model_0.anim_4.status_0 == 0x35)
                    {
                        stalker->properties_E4.dummy.properties_E8[5].val16[0] = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 0x4C;
                    }
                    else if (stalker->model_0.anim_4.status_0 == 0x23)
                    {
                        stalker->properties_E4.dummy.properties_E8[5].val16[0] = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 0x4E;
                    }
                    else if (stalker->model_0.anim_4.status_0 == 0x25)
                    {
                        stalker->properties_E4.dummy.properties_E8[5].val16[0] = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 0x50;
                    }
                }
                else
                {
                    if (stalker->health_B0 > sharedData_800E3A24_0_s00 && !(stalkerProps.flags_E8 & 0x80))
                    {
                        if (stalker->model_0.state_2 == 5)
                        {
                            g_SysWork.field_2284[3] &= 0xFFFD;
                        }

                        stalker->model_0.state_2 = 7;

                        if ((stalker->model_0.anim_4.status_0 >> 1) < 0x16 || (stalker->model_0.anim_4.status_0 >> 1) > 0x17)
                        {
                            if (angle >= 0x2AA)
                            {
                                stalker->model_0.anim_4.status_0 = 0x2E;
                            }
                            else
                            {
                                stalker->model_0.anim_4.status_0 = 0x2C;
                            }
                        }
                    }
                    else if (stalkerProps.flags_E8 & 0x80)
                    {
                        stalker->model_0.state_2 = 9;

                        if ((stalker->model_0.anim_4.status_0 >> 1) == 0xB)
                        {
                            if (stalker->model_0.anim_4.status_0 == 0x16)
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = 0;
                                stalker->model_0.anim_4.status_0                               = 0x4C;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 0x6A &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 0x6D)
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                                stalker->model_0.anim_4.status_0                       = 0x4C;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 0x6C &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 0x71)
                            {
                                if (angle >= 0x2AA)
                                {
                                    stalker->model_0.anim_4.status_0 = 0x54;
                                }
                                else
                                {
                                    stalker->model_0.anim_4.status_0 = 2;
                                }

                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;

                                if (stalker->properties_E4.dummy.properties_E8[5].val16[0] == 2)
                                {
                                    stalker->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                                }
                                else if (stalker->properties_E4.dummy.properties_E8[5].val16[0] == 3)
                                {
                                    stalker->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                                }
                                else
                                {
                                    stalker->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                                }
                            }
                            else
                            {
                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 0x70 && FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 0x76)
                                {
                                    if (angle >= 0x2AA)
                                    {
                                        stalker->model_0.anim_4.status_0 = 0x56;
                                    }
                                    else
                                    {
                                        stalker->model_0.anim_4.status_0 = 6;
                                    }

                                    keyframeIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);

                                    stalker->properties_E4.dummy.properties_E8[5].val16[0] = keyframeIdx - 0x6B;

                                    if (keyframeIdx == 0x74 || keyframeIdx == 0x75)
                                    {
                                        stalker->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                                    }
                                    else
                                    {
                                        stalker->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                                    }
                                }
                                else
                                {
                                    if (angle >= 0x2AA)
                                    {
                                        stalker->model_0.anim_4.status_0 = 0x58;
                                    }
                                    else
                                    {
                                        stalker->model_0.anim_4.status_0 = 4;
                                    }

                                    stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                                }
                            }
                        }
                        else if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) == StalkerAnim_12)
                        {
                            if (stalker->model_0.anim_4.status_0 == 0x18)
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = 0;
                            }
                            else
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
                            }

                            if (stalker->model_0.anim_4.status_0 == 0x18 || (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 0x80 && FP_FROM(stalker->model_0.anim_4.time_4, 0xC) < 0x88))
                            {
                                stalker->model_0.anim_4.status_0 = 0x4E;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 0x87 && FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 0x8E)
                            {
                                stalker->model_0.anim_4.status_0                               = 8;
                                stalker->properties_E4.dummy.properties_E8[5].val16[1] = (0xC - stalker->properties_E4.dummy.properties_E8[5].val16[0]) >> 1;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 0x8D && FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 0x95)
                            {
                                stalker->model_0.anim_4.status_0 = 0xA;

                                switch (stalker->properties_E4.dummy.properties_E8[5].val16[0])
                                {
                                    case 13:
                                        stalker->properties_E4.dummy.properties_E8[5].val16[1] = 5;
                                        break;

                                    case 14:
                                    case 15:
                                        stalker->properties_E4.dummy.properties_E8[5].val16[1] = 4;
                                        break;

                                    case 16:
                                    case 17:
                                        stalker->properties_E4.dummy.properties_E8[5].val16[1] = 3;
                                        break;

                                    default:
                                        stalker->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                                        break;
                                }
                            }
                            else
                            {
                                stalker->model_0.anim_4.status_0                       = 0xA;
                                stalker->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                            }
                        }
                        else
                        {
                            if (stalker->model_0.anim_4.status_0 == 0x1A)
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = 0;
                                stalker->model_0.anim_4.status_0                       = 0x50;
                            }
                            else
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x9E;

                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) == 0x9E || FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) == 0x9F)
                                {
                                    stalker->model_0.anim_4.status_0 = 0x50;
                                }
                                else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 0xA0 || FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 0xA8)
                                {
                                    stalker->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                                    stalker->model_0.anim_4.status_0                       = 0xA;
                                }
                                else
                                {
                                    stalker->model_0.anim_4.status_0 = 0x5B;
                                }
                            }
                        }

                        stalkerProps.flags_E8 &= 0xFF7F;
                    }
                    else
                    {
                        stalker->model_0.state_2 = 9;

                        if (angle < 0x2AA)
                        {
                            if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 0x169 && FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 0x175)
                            {
                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) >= 0x16C && FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) <= 0x16F)
                                {
                                    stalker->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                                }
                                else
                                {
                                    stalker->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                                }

                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x16A;
                            }
                            else
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                            }

                            stalker->model_0.anim_4.status_0 = 0x30;
                        }
                        else
                        {
                            if (stalker->model_0.anim_4.status_0 == 23)
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[1] = 23;
                                stalker->model_0.anim_4.status_0                       = 0x32;
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                            }
                            else if (stalker->model_0.anim_4.status_0 == 25)
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[1] = 25;
                                stalker->model_0.anim_4.status_0                       = 0x32;
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
                            }
                            else if (stalker->model_0.anim_4.status_0 == 27)
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[1] = 27;
                                stalker->model_0.anim_4.status_0                       = 0x32;
                                stalker->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x9E;
                            }
                            else
                            {
                                stalker->properties_E4.dummy.properties_E8[5].val16[1] = 83;
                                stalker->model_0.anim_4.status_0                       = ANIM_STATUS(41, false);
                            }
                        }
                    }
                }

                stalker->properties_E4.player.runTimer_F8 = Q12(0.0f);
                stalkerProps.flags_E8                     &= 0xF7E7;
            }
        }
    }

    stalker->damage_B4.amount_C      = Q12(0.0f);
    stalker->damage_B4.position_0.vz = Q12(0.0f);
    stalker->damage_B4.position_0.vy = Q12(0.0f);
    stalker->damage_B4.position_0.vx = Q12(0.0f);

    #undef stalkerProps
}

void sharedFunc_800D3308_0_s00(s_SubCharacter* chara)
{
    q3_12  angle;
    u16    keyframeIdx;
    q19_12 mag;
    q19_12 var_a0;
    q20_12 var_v1;

    var_a0 = chara->properties_E4.npc.field_10C - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(20.0f), Q12_SHIFT);
    chara->properties_E4.npc.field_10C = MAX(var_a0, Q12(0.0f));

    if (chara->damage_B4.amount_C > Q12(0.0f) && chara->health_B0 > Q12(0.0f))
    {
        sharedFunc_800D7E04_0_s00(chara, 1365);
    }

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(34, true) ||
        chara->model_0.anim_4.status_0 == ANIM_STATUS(35, true))
    {
        chara->damage_B4.amount_C = Q12(0.0f);
    }

    if (chara->health_B0 > Q12(0.0f))
    {
        var_v1          = chara->health_B0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800E3A28_0_s00, Q12_SHIFT);
        chara->health_B0 = MIN(var_v1, chara->properties_E4.player.field_110);
    }

    if (chara->damage_B4.amount_C > Q12(0.0f))
    {
        if (chara->health_B0 > Q12(0.0f))
        {
            chara->health_B0 = MAX(chara->health_B0 - chara->damage_B4.amount_C, Q12(0.0f));

            chara->properties_E4.player.field_110                        -= chara->damage_B4.amount_C >> 2;
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 0x401;

            chara->damage_B4.position_0.vx += FP_MULTIPLY(chara->moveSpeed_38, Math_Sin(chara->headingAngle_3C), Q12_SHIFT) >> 3;
            chara->damage_B4.position_0.vz += FP_MULTIPLY(chara->moveSpeed_38, Math_Cos(chara->headingAngle_3C), Q12_SHIFT) >> 3;

            if (chara->properties_E4.dummy.properties_E8[0].val16[0] & 0x40)
            {
                mag          = Math_Vector2MagCalc(chara->damage_B4.position_0.vx, chara->damage_B4.position_0.vz);
                chara->moveSpeed_38 = (mag << 12) / 0xC000;
            }
            else
            {
                mag          = Math_Vector2MagCalc(chara->damage_B4.position_0.vx, chara->damage_B4.position_0.vz);
                chara->moveSpeed_38 = (mag << 12) / 0x1800;
            }

            chara->headingAngle_3C                                        = ratan2(chara->damage_B4.position_0.vx, chara->damage_B4.position_0.vz);
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 0x2000;
            chara->properties_E4.npc.field_10C                           += chara->damage_B4.amount_C;

            if (chara->properties_E4.npc.field_10C >= sharedData_800E3A2C_0_s00 ||
                (!(chara->properties_E4.dummy.properties_E8[0].val16[0] & 0x40) && chara->health_B0 <= sharedData_800E3A24_0_s00))
            {
                chara->properties_E4.npc.field_10C = 0;

                angle = ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                                  g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                                           chara->rotation_24.vy));

                if (chara->properties_E4.dummy.properties_E8[0].val16[0] & 0x40)
                {
                    if (chara->model_0.anim_4.status_0 == 0x35)
                    {
                        chara->properties_E4.dummy.properties_E8[5].val16[0] = NO_VALUE;
                        chara->model_0.anim_4.status_0                               = 0x4C;
                    }
                    else if (chara->model_0.anim_4.status_0 == 0x23)
                    {
                        chara->properties_E4.dummy.properties_E8[5].val16[0] = NO_VALUE;
                        chara->model_0.anim_4.status_0                               = 0x4E;
                    }
                    else if (chara->model_0.anim_4.status_0 == 0x25)
                    {
                        chara->properties_E4.dummy.properties_E8[5].val16[0] = NO_VALUE;
                        chara->model_0.anim_4.status_0                               = 0x50;
                    }
                }
                else
                {
                    if (chara->health_B0 > sharedData_800E3A24_0_s00 && !(chara->properties_E4.dummy.properties_E8[0].val16[0] & 0x80))
                    {
                        if (chara->model_0.state_2 == 5)
                        {
                            g_SysWork.field_2284[3] &= 0xFFFD;
                        }

                        chara->model_0.state_2 = 7;

                        if ((chara->model_0.anim_4.status_0 >> 1) < 0x16 || (chara->model_0.anim_4.status_0 >> 1) > 0x17)
                        {
                            if (angle >= 0x2AA)
                            {
                                chara->model_0.anim_4.status_0 = 0x2E;
                            }
                            else
                            {
                                chara->model_0.anim_4.status_0 = 0x2C;
                            }
                        }
                    }
                    else if (chara->properties_E4.dummy.properties_E8[0].val16[0] & 0x80)
                    {
                        chara->model_0.state_2 = 9;

                        if ((chara->model_0.anim_4.status_0 >> 1) == 0xB)
                        {
                            if (chara->model_0.anim_4.status_0 == 0x16)
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = 0;
                                chara->model_0.anim_4.status_0                               = 0x4C;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x6A && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x6D)
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                                chara->model_0.anim_4.status_0                               = 0x4C;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x6C && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x71)
                            {
                                if (angle >= 0x2AA)
                                {
                                    chara->model_0.anim_4.status_0 = 0x54;
                                }
                                else
                                {
                                    chara->model_0.anim_4.status_0 = 2;
                                }

                                chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;

                                if (chara->properties_E4.dummy.properties_E8[5].val16[0] == 2)
                                {
                                    chara->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                                }
                                else if (chara->properties_E4.dummy.properties_E8[5].val16[0] == 3)
                                {
                                    chara->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                                }
                                else
                                {
                                    chara->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                                }
                            }
                            else
                            {
                                if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x70 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x76)
                                {
                                    if (angle >= 0x2AA)
                                    {
                                        chara->model_0.anim_4.status_0 = 0x56;
                                    }
                                    else
                                    {
                                        chara->model_0.anim_4.status_0 = 6;
                                    }

                                    keyframeIdx = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);

                                    chara->properties_E4.dummy.properties_E8[5].val16[0] = keyframeIdx - 0x6B;

                                    if (keyframeIdx == 0x74 || keyframeIdx == 0x75)
                                    {
                                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                                    }
                                    else
                                    {
                                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                                    }
                                }
                                else
                                {
                                    if (angle >= 0x2AA)
                                    {
                                        chara->model_0.anim_4.status_0 = 0x58;
                                    }
                                    else
                                    {
                                        chara->model_0.anim_4.status_0 = 4;
                                    }

                                    chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                                }
                            }
                        }
                        else if ((chara->model_0.anim_4.status_0 >> 1) == 0xC)
                        {
                            if (chara->model_0.anim_4.status_0 == 0x18)
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = 0;
                            }
                            else
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
                            }

                            if (chara->model_0.anim_4.status_0 == 0x18 || (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x80 && FP_FROM(chara->model_0.anim_4.time_4, 0xC) < 0x88))
                            {
                                chara->model_0.anim_4.status_0 = 0x4E;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x87 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x8E)
                            {
                                chara->model_0.anim_4.status_0                               = 8;
                                chara->properties_E4.dummy.properties_E8[5].val16[1] = (0xC - chara->properties_E4.dummy.properties_E8[5].val16[0]) >> 1;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x8D && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x95)
                            {
                                chara->model_0.anim_4.status_0 = 0xA;

                                switch (chara->properties_E4.dummy.properties_E8[5].val16[0])
                                {
                                    case 13:
                                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 5;
                                        break;

                                    case 14:
                                    case 15:
                                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 4;
                                        break;

                                    case 16:
                                    case 17:
                                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 3;
                                        break;

                                    default:
                                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                                        break;
                                }
                            }
                            else
                            {
                                chara->model_0.anim_4.status_0                               = 0xA;
                                chara->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                            }
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == 0x1A)
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = 0;
                                chara->model_0.anim_4.status_0                               = 0x50;
                            }
                            else
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x9E;

                                if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) == 0x9E || FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) == 0x9F)
                                {
                                    chara->model_0.anim_4.status_0 = 0x50;
                                }
                                else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0xA0 || FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0xA8)
                                {
                                    chara->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                                    chara->model_0.anim_4.status_0                               = 0xA;
                                }
                                else
                                {
                                    chara->model_0.anim_4.status_0 = 0x5B;
                                }
                            }
                        }
                        chara->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFF7F;
                    }
                    else
                    {
                        chara->model_0.state_2 = 9;

                        if (angle < 0x2AA)
                        {
                            if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x169 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x175)
                            {
                                if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) >= 0x16C && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) <= 0x16F)
                                {
                                    chara->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                                }
                                else
                                {
                                    chara->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                                }

                                chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x16A;
                            }
                            else
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                            }

                            chara->model_0.anim_4.status_0 = 0x30;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == 23)
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[1] = 23;
                                chara->model_0.anim_4.status_0                               = 0x32;
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                            }
                            else if (chara->model_0.anim_4.status_0 == 25)
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[1] = 25;
                                chara->model_0.anim_4.status_0                               = 0x32;
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
                            }
                            else if (chara->model_0.anim_4.status_0 == 27)
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[1] = 27;
                                chara->model_0.anim_4.status_0                               = 0x32;
                                chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x9E;
                            }
                            else
                            {
                                chara->properties_E4.dummy.properties_E8[5].val16[1] = 83;
                                chara->model_0.anim_4.status_0                               = ANIM_STATUS(41, false);
                            }
                        }
                    }
                }
                chara->properties_E4.player.runTimer_F8                       = Q12(0.0f);
                chara->properties_E4.dummy.properties_E8[0].val16[0] &= 0xF7E7;
            }
        }
    }

    chara->damage_B4.amount_C      = Q12(0.0f);
    chara->damage_B4.position_0.vz = Q12(0.0f);
    chara->damage_B4.position_0.vy = Q12(0.0f);
    chara->damage_B4.position_0.vx = Q12(0.0f);
}

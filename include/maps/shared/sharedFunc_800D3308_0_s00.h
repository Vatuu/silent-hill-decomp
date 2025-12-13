void sharedFunc_800D3308_0_s00(s_SubCharacter* arg0)
{
    s16 var_a1;
    u16 temp_v0_11;
    s32 temp_v0_4;
    s32 var_a0;
    u32 var_v1;

    var_a0 = arg0->properties_E4.npc.field_10C - FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x14000, Q12_SHIFT);

    arg0->properties_E4.npc.field_10C = MAX(var_a0, 0);

    if (arg0->damage_B4.amount_C > 0 && arg0->health_B0 > 0)
    {
        sharedFunc_800D7E04_0_s00(arg0, 0x555);
    }

    if (arg0->model_0.anim_4.status_0 == 0x45 || arg0->model_0.anim_4.status_0 == 0x47)
    {
        arg0->damage_B4.amount_C = 0;
    }

    if (arg0->health_B0 > 0)
    {
        var_v1          = arg0->health_B0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800E3A28_0_s00, Q12_SHIFT);
        arg0->health_B0 = MIN(var_v1, arg0->properties_E4.player.field_110);
    }

    if (arg0->damage_B4.amount_C > 0)
    {
        if (arg0->health_B0 > 0)
        {
            arg0->health_B0 = MAX(arg0->health_B0 - arg0->damage_B4.amount_C, 0);

            arg0->properties_E4.player.field_110                        -= arg0->damage_B4.amount_C >> 2;
            arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x401;

            arg0->damage_B4.position_0.vx += FP_MULTIPLY(arg0->moveSpeed_38, Math_Sin(arg0->headingAngle_3C), Q12_SHIFT) >> 3;
            arg0->damage_B4.position_0.vz += FP_MULTIPLY(arg0->moveSpeed_38, Math_Cos(arg0->headingAngle_3C), Q12_SHIFT) >> 3;

            if (arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x40)
            {
                temp_v0_4          = SquareRoot0(SQUARE(arg0->damage_B4.position_0.vx >> 6) + SQUARE(arg0->damage_B4.position_0.vz >> 6)) << 6;
                arg0->moveSpeed_38 = (temp_v0_4 << 12) / 0xC000;
            }
            else
            {
                temp_v0_4          = SquareRoot0(SQUARE(arg0->damage_B4.position_0.vx >> 6) + SQUARE(arg0->damage_B4.position_0.vz >> 6)) << 6;
                arg0->moveSpeed_38 = (temp_v0_4 << 12) / 0x1800;
            }

            arg0->headingAngle_3C                                        = ratan2(arg0->damage_B4.position_0.vx, arg0->damage_B4.position_0.vz);
            arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x2000;
            arg0->properties_E4.npc.field_10C                           += arg0->damage_B4.amount_C;

            if (arg0->properties_E4.npc.field_10C >= sharedData_800E3A2C_0_s00 ||
                (!(arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x40) && arg0->health_B0 <= sharedData_800E3A24_0_s00))
            {
                arg0->properties_E4.npc.field_10C = 0;

                var_a1 = ABS(func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - arg0->position_18.vx,
                                                  g_SysWork.player_4C.chara_0.position_18.vz - arg0->position_18.vz) -
                                           arg0->rotation_24.vy));

                if (arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x40)
                {
                    if (arg0->model_0.anim_4.status_0 == 0x35)
                    {
                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = -1;
                        arg0->model_0.anim_4.status_0                               = 0x4C;
                    }
                    else if (arg0->model_0.anim_4.status_0 == 0x23)
                    {
                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = -1;
                        arg0->model_0.anim_4.status_0                               = 0x4E;
                    }
                    else if (arg0->model_0.anim_4.status_0 == 0x25)
                    {
                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = -1;
                        arg0->model_0.anim_4.status_0                               = 0x50;
                    }
                }
                else
                {
                    if (arg0->health_B0 > sharedData_800E3A24_0_s00 && !(arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x80))
                    {
                        if (arg0->model_0.state_2 == 5)
                        {
                            g_SysWork.field_2284[3] &= 0xFFFD;
                        }

                        arg0->model_0.state_2 = 7;

                        if ((arg0->model_0.anim_4.status_0 >> 1) < 0x16 || (arg0->model_0.anim_4.status_0 >> 1) > 0x17)
                        {
                            if (var_a1 >= 0x2AA)
                            {
                                arg0->model_0.anim_4.status_0 = 0x2E;
                            }
                            else
                            {
                                arg0->model_0.anim_4.status_0 = 0x2C;
                            }
                        }
                    }
                    else if (arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x80)
                    {
                        arg0->model_0.state_2 = 9;

                        if ((arg0->model_0.anim_4.status_0 >> 1) == 0xB)
                        {
                            if (arg0->model_0.anim_4.status_0 == 0x16)
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = 0;
                                arg0->model_0.anim_4.status_0                               = 0x4C;
                            }
                            else if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0x6A && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x6D)
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                                arg0->model_0.anim_4.status_0                               = 0x4C;
                            }
                            else if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0x6C && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x71)
                            {
                                if (var_a1 >= 0x2AA)
                                {
                                    arg0->model_0.anim_4.status_0 = 0x54;
                                }
                                else
                                {
                                    arg0->model_0.anim_4.status_0 = 2;
                                }

                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;

                                if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] == 2)
                                {
                                    arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 2;
                                }
                                else if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] == 3)
                                {
                                    arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 1;
                                }
                                else
                                {
                                    arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 0;
                                }
                            }
                            else
                            {
                                if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0x70 && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x76)
                                {
                                    if (var_a1 >= 0x2AA)
                                    {
                                        arg0->model_0.anim_4.status_0 = 0x56;
                                    }
                                    else
                                    {
                                        arg0->model_0.anim_4.status_0 = 6;
                                    }

                                    temp_v0_11 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT);

                                    arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = temp_v0_11 - 0x6B;

                                    if (temp_v0_11 == 0x74 || temp_v0_11 == 0x75)
                                    {
                                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 1;
                                    }
                                    else
                                    {
                                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 2;
                                    }
                                }
                                else
                                {
                                    if (var_a1 >= 0x2AA)
                                    {
                                        arg0->model_0.anim_4.status_0 = 0x58;
                                    }
                                    else
                                    {
                                        arg0->model_0.anim_4.status_0 = 4;
                                    }

                                    arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                                }
                            }
                        }
                        else if ((arg0->model_0.anim_4.status_0 >> 1) == 0xC)
                        {
                            if (arg0->model_0.anim_4.status_0 == 0x18)
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = 0;
                            }
                            else
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
                            }

                            if (arg0->model_0.anim_4.status_0 == 0x18 || (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0x80 && FP_FROM(arg0->model_0.anim_4.time_4, 0xC) < 0x88))
                            {
                                arg0->model_0.anim_4.status_0 = 0x4E;
                            }
                            else if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0x87 && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x8E)
                            {
                                arg0->model_0.anim_4.status_0                               = 8;
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = (0xC - arg0->properties_E4.larvalStalker.properties_E8[5].val16[0]) >> 1;
                            }
                            else if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0x8D && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x95)
                            {
                                arg0->model_0.anim_4.status_0 = 0xA;

                                switch (arg0->properties_E4.larvalStalker.properties_E8[5].val16[0])
                                {
                                    case 13:
                                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 5;
                                        break;

                                    case 14:
                                    case 15:
                                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 4;
                                        break;

                                    case 16:
                                    case 17:
                                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 3;
                                        break;

                                    default:
                                        arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 2;
                                        break;
                                }
                            }
                            else
                            {
                                arg0->model_0.anim_4.status_0                               = 0xA;
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 1;
                            }
                        }
                        else
                        {
                            if (arg0->model_0.anim_4.status_0 == 0x1A)
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = 0;
                                arg0->model_0.anim_4.status_0                               = 0x50;
                            }
                            else
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x9E;

                                if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) == 0x9E || FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) == 0x9F)
                                {
                                    arg0->model_0.anim_4.status_0 = 0x50;
                                }
                                else if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0xA0 || FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0xA8)
                                {
                                    arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 0;
                                    arg0->model_0.anim_4.status_0                               = 0xA;
                                }
                                else
                                {
                                    arg0->model_0.anim_4.status_0 = 0x5B;
                                }
                            }
                        }
                        arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] &= 0xFF7F;
                    }
                    else
                    {
                        arg0->model_0.state_2 = 9;

                        if (var_a1 < 0x2AA)
                        {
                            if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) > 0x169 && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) < 0x175)
                            {
                                if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) >= 0x16C && FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) <= 0x16F)
                                {
                                    arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 2;
                                }
                                else
                                {
                                    arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 1;
                                }

                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x16A;
                            }
                            else
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 0;
                            }

                            arg0->model_0.anim_4.status_0 = 0x30;
                        }
                        else
                        {
                            if (arg0->model_0.anim_4.status_0 == 23)
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 23;
                                arg0->model_0.anim_4.status_0                               = 0x32;
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
                            }
                            else if (arg0->model_0.anim_4.status_0 == 25)
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 25;
                                arg0->model_0.anim_4.status_0                               = 0x32;
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
                            }
                            else if (arg0->model_0.anim_4.status_0 == 27)
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 27;
                                arg0->model_0.anim_4.status_0                               = 0x32;
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x9E;
                            }
                            else
                            {
                                arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] = 0x53;
                                arg0->model_0.anim_4.status_0                               = 0x52;
                            }
                        }
                    }
                }
                arg0->properties_E4.player.runTimer_F8                       = 0;
                arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] &= 0xF7E7;
            }
        }
    }

    arg0->damage_B4.amount_C      = 0;
    arg0->damage_B4.position_0.vz = 0;
    arg0->damage_B4.position_0.vy = 0;
    arg0->damage_B4.position_0.vx = 0;
}

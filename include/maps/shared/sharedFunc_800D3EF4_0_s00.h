void sharedFunc_800D3EF4_0_s00(s_SubCharacter* stalker)
{
    q3_12  angle1;
    q3_12  angle0;
    q19_12 mag;
    s32    i;

    // TODO: Use `Math_Vector2MagCalc`.
    mag   = SquareRoot0(SQUARE((sharedData_800E3A18_0_s00 - stalker->position_18.vx) >> 6) + SQUARE((sharedData_800E3A1C_0_s00 - stalker->position_18.vz) >> 6));
    mag <<= 6;
    angle0 = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx, sharedData_800E3A1C_0_s00 - stalker->position_18.vz) - stalker->rotation_24.vy);

    if (mag > Q12(8.0f) && (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_0) && !(g_SysWork.flags_22A4 & SysFlag2_MenuOpen))
    {
        if (!Vw_AabbVisibleInScreenCheck(stalker->position_18.vx - Q12(1.0f), stalker->position_18.vx + Q12(1.0f),
                                         stalker->position_18.vy - Q12(1.8f), stalker->position_18.vy,
                                         stalker->position_18.vz - Q12(1.0f), stalker->position_18.vz - Q12(1.0f)))
        {
            stalker->properties_E4.stalker.flags_E8 |= StalkerFlag_12;
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_30, true) && !func_800700F8(stalker, &g_SysWork.playerWork_4C.player_0))
    {
        stalker->properties_E4.stalker.timer_F8 = Q12(0.0f);

        if (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_12)
        {
            stalker->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);
        }
        else
        {
            if (ABS(angle0) > FP_ANGLE(90.0f))
            {
                Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
            }
            else
            {
                Chara_MoveSpeedUpdate3(stalker, FP_ANGLE(180.0f), (FP_ANGLE(90.0f) - ABS(angle0)) * 4);
            }
        }

        for (i = 3 + ((ABS(angle0) > FP_ANGLE(90.0f)) ? 1 : 0); i > 0; i--)
        {
            if (((g_DeltaTime0 >> 2) + 1) < ABS(angle0))
            {
                if (angle0 > 0)
                {
                    stalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
                else
                {
                    stalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }

                angle0 = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                             sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                      stalker->rotation_24.vy);
            }

            if (ABS(angle0) < ((g_DeltaTime0 >> 2) + 1) || mag > Q12(2.0f))
            {
                break;
            }
        }

        if ((g_SysWork.field_2284[3] & (1 << 0)) ||
            ( (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_2) && Rng_GenerateInt(0, 3) != 0) || // 1 in 4 chance.
            (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_2) && Rng_GenerateInt(0, 1) != 0))   // 1 in 2 chance.
        {
            if (mag < Q12(0.9f))
            {
                if (mag > Q12(0.7f) || Rng_GenerateInt(0, 3) == 0) // 1 in 4 chance.
                {
                    if (ABS(angle0) < FP_ANGLE(90.0f))
                    {
                        if (g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
                        {
                            stalker->model_0.state_2   = 5;
                            g_SysWork.field_2284[3] |= 2;

                            sharedFunc_800D7E04_0_s00(stalker, 1364);

                            if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 492 && FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 505)
                            {
                                stalker->model_0.anim_4.status_0        = ANIM_STATUS(StalkerAnim_37, true);
                                stalker->properties_E4.stalker.keyframeIdx_FC = 29;
                                stalker->properties_E4.stalker.field_FE = 0;
                                return;
                            }

                            stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_7, false);

                            stalker->properties_E4.stalker.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 477;

                            if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 477 &&
                                FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 482)
                            {
                                stalker->properties_E4.stalker.field_FE = 1;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 481 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 488)
                            {
                                stalker->properties_E4.stalker.field_FE = 2;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 487 && 
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 491)
                            {
                                stalker->properties_E4.stalker.field_FE = 3;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 490 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 493)
                            {
                                stalker->properties_E4.stalker.field_FE = 4;
                            }
                            else
                            {
                                stalker->properties_E4.stalker.field_FE = 0;
                            }
                            return;
                        }
                    }
                }
            }
        }
        else if (mag > Q12(0.5f) && mag < Q12(1.0f))
        {
            if (ABS(angle0) < FP_ANGLE(60.0f))
            {
                if (g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
                {
                    stalker->model_0.state_2 = 6;
                    angle1              = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - stalker->rotation_24.vy);

                    if (ABS(angle1) > FP_ANGLE(90.0f))
                    {
                        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_34, false);
                    }
                    else
                    {
                        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_35, false);
                    }

                    stalker->properties_E4.stalker.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 477;
                    g_SysWork.field_2284[3]                      |= 3;
                    return;
                }
            }
        }

        if (mag < Q12(0.7f))
        {
            stalker->model_0.state_2 = 4;
        }
    }
    else
    {
        Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(1.0f));

        if (stalker->properties_E4.stalker.timer_F8 == Q12(0.0f))
        {
            stalker->properties_E4.dummy.properties_E8[6].val16[0] = func_8006FAFC(stalker,
                                                                                   Q12(2.0f),
                                                                                   g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                                   g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                                   Q12(1.0f),
                                                                                   true);
            if (stalker->properties_E4.dummy.properties_E8[6].val16[0] == Q12(1.0f))
            {
                stalker->properties_E4.dummy.properties_E8[6].val16[0] = stalker->rotation_24.vy - FP_ANGLE(180.0f);
            }
        }

        stalker->properties_E4.stalker.timer_F8 += g_DeltaTime0;
        if (stalker->properties_E4.stalker.timer_F8 > Q12(2.5f) && Rng_GenerateInt(0, 15) == 0) // 1 in 16 chance.
        {
            stalker->properties_E4.stalker.timer_F8 = Q12(0.0f);
        }

        if (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_12)
        {
            stalker->rotation_24.vy = stalker->properties_E4.dummy.properties_E8[6].val16[0];
        }
        else
        {
            angle1 = func_8005BF38(stalker->properties_E4.dummy.properties_E8[6].val16[0] - stalker->rotation_24.vy);
            if (((g_DeltaTime0 >> 2) + 1) < ABS(angle1))
            {
                if (angle1 > FP_ANGLE(0.0f))
                {
                    stalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
                else
                {
                    stalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
            }
        }
    }
}

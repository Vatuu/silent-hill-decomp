void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara)
{
    q3_12  angle1;
    q3_12  angle0;
    q19_12 mag;
    s32    i;

    // TODO: Use `Math_Vector2MagCalc`.
    mag   = SquareRoot0(SQUARE((sharedData_800E3A18_0_s00 - chara->position_18.vx) >> 6) + SQUARE((sharedData_800E3A1C_0_s00 - chara->position_18.vz) >> 6));
    mag <<= 6;
    angle0 = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - chara->position_18.vx, sharedData_800E3A1C_0_s00 - chara->position_18.vz) - chara->rotation_24.vy);

    if (mag > Q12(8.0f) && (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 0)) && !(g_SysWork.flags_22A4 & 0x80))
    {
        if (!Vw_AabbVisibleInScreenCheck(chara->position_18.vx - Q12(1.0f), chara->position_18.vx + Q12(1.0f),
                                         chara->position_18.vy - Q12(1.8f), chara->position_18.vy,
                                         chara->position_18.vz - Q12(1.0f), chara->position_18.vz - Q12(1.0f)))
        {
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 12;
        }
    }

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(30, true) && !func_800700F8(chara, &g_SysWork.player_4C.chara_0))
    {
        chara->properties_E4.player.runTimer_F8 = Q12(0.0f);

        if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 12))
        {
            chara->rotation_24.vy = ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                           g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);
        }
        else
        {
            if (ABS(angle0) > FP_ANGLE(90.0f))
            {
                Chara_MoveSpeedUpdate(chara, Q12(1.5f));
            }
            else
            {
                Chara_MoveSpeedUpdate3(chara, FP_ANGLE(180.0f), (FP_ANGLE(90.0f) - ABS(angle0)) * 4);
            }
        }

        for (i = 3 + ((ABS(angle0) > FP_ANGLE(90.0f)) ? 1 : 0); i > 0; i--)
        {
            if (((g_DeltaTime0 >> 2) + 1) < ABS(angle0))
            {
                if (angle0 > 0)
                {
                    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
                else
                {
                    chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }

                angle0 = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - chara->position_18.vx,
                                             sharedData_800E3A1C_0_s00 - chara->position_18.vz) -
                                      chara->rotation_24.vy);
            }

            if (ABS(angle0) < ((g_DeltaTime0 >> 2) + 1) || mag > Q12(2.0f))
            {
                break;
            }
        }

        if ((g_SysWork.field_2284[3] & (1 << 0)) ||
            ( (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 2)) && Rng_GenerateInt(0, 3) != 0) || // 1 in 4 chance.
            (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 2)) && Rng_GenerateInt(0, 1) != 0))   // 1 in 2 chance.
        {
            if (mag < Q12(0.9f))
            {
                if (mag > Q12(0.7f) || Rng_GenerateInt(0, 3) == 0) // 1 in 4 chance.
                {
                    if (ABS(angle0) < FP_ANGLE(90.0f))
                    {
                        if (g_SysWork.player_4C.chara_0.health_B0 > Q12(0.0f))
                        {
                            chara->model_0.state_2   = 5;
                            g_SysWork.field_2284[3] |= 2;

                            sharedFunc_800D7E04_0_s00(chara, 1364);

                            if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 492 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 505)
                            {
                                chara->model_0.anim_4.status_0                               = ANIM_STATUS(37, true);
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = 29;
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 0;
                                return;
                            }

                            chara->model_0.anim_4.status_0 = ANIM_STATUS(7, false);

                            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 477;

                            if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 477 &&
                                FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 482)
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 1;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 481 &&
                                     FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 488)
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 2;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 487 && 
                                     FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 491)
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 3;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 490 &&
                                     FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 493)
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 4;
                            }
                            else
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 0;
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
                if (g_SysWork.player_4C.chara_0.health_B0 > Q12(0.0f))
                {
                    chara->model_0.state_2 = 6;
                    angle1              = func_8005BF38(g_SysWork.player_4C.chara_0.rotation_24.vy - chara->rotation_24.vy);

                    if (ABS(angle1) > FP_ANGLE(90.0f))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(34, false);
                    }
                    else
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(35, false);
                    }

                    chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 477;
                    g_SysWork.field_2284[3]                                     |= 3;
                    return;
                }
            }
        }

        if (mag < Q12(0.7f))
        {
            chara->model_0.state_2 = 4;
        }
    }
    else
    {
        Chara_MoveSpeedUpdate3(chara, Q12(0.5f), Q12(1.0f));

        if (chara->properties_E4.player.runTimer_F8 == Q12(0.0f))
        {
            chara->properties_E4.larvalStalker.properties_E8[6].val16[0] = func_8006FAFC(chara,
                                                                                         Q12(2.0f),
                                                                                         g_SysWork.player_4C.chara_0.position_18.vx,
                                                                                         g_SysWork.player_4C.chara_0.position_18.vz,
                                                                                         Q12(1.0f),
                                                                                         true);
            if (chara->properties_E4.larvalStalker.properties_E8[6].val16[0] == Q12(1.0f))
            {
                chara->properties_E4.larvalStalker.properties_E8[6].val16[0] = chara->rotation_24.vy - FP_ANGLE(180.0f);
            }
        }

        chara->properties_E4.player.runTimer_F8 += g_DeltaTime0;
        if ((chara->properties_E4.player.runTimer_F8 > Q12(2.5f)) && Rng_GenerateInt(0, 15) == 0) // 1 in 16 chance.
        {
            chara->properties_E4.player.runTimer_F8 = Q12(0.0f);
        }

        if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 12))
        {
            chara->rotation_24.vy = chara->properties_E4.larvalStalker.properties_E8[6].val16[0];
        }
        else
        {
            angle1 = func_8005BF38(chara->properties_E4.larvalStalker.properties_E8[6].val16[0] - chara->rotation_24.vy);
            if (((g_DeltaTime0 >> 2) + 1) < ABS(angle1))
            {
                if (angle1 > FP_ANGLE(0.0f))
                {
                    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
                else
                {
                    chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
            }
        }
    }
}

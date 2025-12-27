void sharedFunc_800D3EF4_0_s00(s_SubCharacter* stalker)
{
    q3_12  angleDeltaToTargetHeading;
    q3_12  grabAngleDelta;
    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;
    s32    i;

    // TODO: Doesn't match?
    //distToPlayer  = Math_Vector2MagCalc(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
    //                                 sharedData_800E3A1C_0_s00 - stalker->position_18.vz);
    distToPlayer   = SquareRoot0(SQUARE((sharedData_800E3A18_0_s00 - stalker->position_18.vx) >> 6) + SQUARE((sharedData_800E3A1C_0_s00 - stalker->position_18.vz) >> 6));
    distToPlayer <<= 6;
    angleDeltaToPlayer = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                              sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                       stalker->rotation_24.vy);

    if (distToPlayer > Q12(8.0f) && (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_0) && !(g_SysWork.flags_22A4 & SysFlag2_MenuOpen))
    {
        if (!Vw_AabbVisibleInScreenCheck(stalker->position_18.vx - Q12(1.0f), stalker->position_18.vx + Q12(1.0f),
                                         stalker->position_18.vy - Q12(1.8f), stalker->position_18.vy,
                                         stalker->position_18.vz - Q12(1.0f), stalker->position_18.vz - Q12(1.0f)))
        {
            stalker->properties_E4.stalker.flags_E8 |= StalkerFlag_WarpRotation;
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_30, true) &&
        !func_800700F8(stalker, &g_SysWork.playerWork_4C.player_0))
    {
        stalker->properties_E4.stalker.timer_F8 = Q12(0.0f);

        if (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_WarpRotation)
        {
            stalker->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);
        }
        else
        {
            if (ABS(angleDeltaToPlayer) > FP_ANGLE(90.0f))
            {
                Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
            }
            else
            {
                Chara_MoveSpeedUpdate3(stalker, FP_ANGLE(180.0f), (FP_ANGLE(90.0f) - ABS(angleDeltaToPlayer)) * 4);
            }
        }

        for (i = 3 + ((ABS(angleDeltaToPlayer) > FP_ANGLE(90.0f)) ? 1 : 0); i > 0; i--)
        {
            if (((g_DeltaTime0 >> 2) + 1) < ABS(angleDeltaToPlayer))
            {
                if (angleDeltaToPlayer > FP_ANGLE(0.0f))
                {
                    stalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
                else
                {
                    stalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }

                angleDeltaToPlayer = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                                     sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                              stalker->rotation_24.vy);
            }

            if (ABS(angleDeltaToPlayer) < ((g_DeltaTime0 >> 2) + 1) || distToPlayer > Q12(2.0f))
            {
                break;
            }
        }

        if ((g_SysWork.field_2284[3] & (1 << 0)) ||
            ( (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_2) && Rng_GenerateInt(0, 3) != 0) || // 1 in 4 chance.
            (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_2) && Rng_GenerateInt(0, 1) != 0))   // 1 in 2 chance.
        {
            if ( distToPlayer < Q12(0.9f) &&
                (distToPlayer > Q12(0.7f) || !Rng_GenerateInt(0, 3))) // 1 in 4 chance.
            {
                if (ABS(angleDeltaToPlayer) < FP_ANGLE(90.0f) && g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
                {
                    stalker->model_0.state_2 = 5;
                    g_SysWork.field_2284[3] |= 1 << 1;

                    sharedFunc_800D7E04_0_s00(stalker, 1364);

                    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 493, 504))
                    {
                        stalker->model_0.anim_4.status_0                 = ANIM_STATUS(StalkerAnim_37, true);
                        stalker->properties_E4.stalker.keyframeIdx_FC    = ANIM_STATUS(StalkerAnim_14, true);
                        stalker->properties_E4.stalker.relKeyframeIdx_FE = 0;
                        return;
                    }

                    stalker->model_0.anim_4.status_0              = ANIM_STATUS(StalkerAnim_7, false);
                    stalker->properties_E4.stalker.keyframeIdx_FC = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);

                    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 478, 481))
                    {
                        stalker->properties_E4.stalker.relKeyframeIdx_FE = 1;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 482, 487))
                    {
                        stalker->properties_E4.stalker.relKeyframeIdx_FE = 2;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 488, 490))
                    {
                        stalker->properties_E4.stalker.relKeyframeIdx_FE = 3;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 491, 492))
                    {
                        stalker->properties_E4.stalker.relKeyframeIdx_FE = 4;
                    }
                    else
                    {
                        stalker->properties_E4.stalker.relKeyframeIdx_FE = 0;
                    }
                    return;
                }
            }
        }
        // Attack player if player is alive.
        else if (distToPlayer > Q12(0.5f) && distToPlayer < Q12(1.0f))
        {
            if (ABS(angleDeltaToPlayer) < FP_ANGLE(60.0f))
            {
                if (g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
                {
                    stalker->model_0.state_2 = 6;

                    // Grab player in front or behind.
                    grabAngleDelta = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - stalker->rotation_24.vy);
                    if (ABS(grabAngleDelta) > FP_ANGLE(90.0f))
                    {
                        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_34, false);
                    }
                    else
                    {
                        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_35, false);
                    }

                    stalker->properties_E4.stalker.keyframeIdx_FC = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);
                    g_SysWork.field_2284[3]                      |= (1 << 0) | (1 << 1);
                    return;
                }
            }
        }

        if (distToPlayer < Q12(0.7f))
        {
            stalker->model_0.state_2 = 4;
        }
    }
    else
    {
        Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(1.0f));

        // Set target heading angle.
        if (stalker->properties_E4.stalker.timer_F8 == Q12(0.0f))
        {
            stalker->properties_E4.stalker.targetHeadingAngle_100 = Chara_HeadingAngleGet(stalker,
                                                                                  Q12(2.0f),
                                                                                  g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                                  g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                                  Q12(1.0f),
                                                                                  true);
            if (stalker->properties_E4.stalker.targetHeadingAngle_100 == FP_ANGLE(360.0f))
            {
                stalker->properties_E4.stalker.targetHeadingAngle_100 = stalker->rotation_24.vy - FP_ANGLE(180.0f);
            }
        }

        // Update timer.
        stalker->properties_E4.stalker.timer_F8 += g_DeltaTime0;
        if (stalker->properties_E4.stalker.timer_F8 > Q12(2.5f) && Rng_GenerateInt(0, 15) == 0) // 1 in 16 chance.
        {
            stalker->properties_E4.stalker.timer_F8 = Q12(0.0f);
        }

        // Turn toward target heading angle.
        if (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_WarpRotation)
        {
            stalker->rotation_24.vy = stalker->properties_E4.stalker.targetHeadingAngle_100;
        }
        else
        {
            angleDeltaToTargetHeading = func_8005BF38(stalker->properties_E4.stalker.targetHeadingAngle_100 - stalker->rotation_24.vy);
            if (((g_DeltaTime0 >> 2) + 1) < ABS(angleDeltaToTargetHeading))
            {
                if (angleDeltaToTargetHeading > FP_ANGLE(0.0f))
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

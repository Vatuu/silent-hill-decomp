void sharedFunc_800D4924_0_s00(s_SubCharacter* stalker)
{
    q3_12  grabAngleDelta;
    s16    angleDeltaToTargetHeading;
    q3_12  angleToPlayer;
    q19_12 distToPlayer;
    q19_12 radiusMax;
    q19_12 radiusMin;
    s32    i;
    bool   cond1;
    q25_6  temp;
    q19_12 temp2;

    distToPlayer  = Math_Vector2MagCalc(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                        sharedData_800E3A1C_0_s00 - stalker->position_18.vz);
    angleToPlayer = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                         sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                  stalker->rotation_24.vy);

    if (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        radiusMax = Q12(15.0f);
        radiusMin = Q12(5.5f);
        cond1  = func_8006FD90(stalker, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP5_S02) || defined(MAP6_S03) || defined(MAP6_S04) || defined(MAP7_S02)
        radiusMax = Q12(16.0f);
        radiusMin = Q12(6.0f);
        cond1  = func_8006FD90(stalker, 0, Q12(8.0f), Q12(8.0f));
#else
        radiusMax = Q12(12.0f);
        radiusMin = Q12(4.5f);
        cond1  = func_8006FD90(stalker, 0, Q12(6.0f), Q12(6.0f));
#endif
    }
    else
    {
        radiusMax = Q12(0.8f);
#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP5_S02) || defined(MAP6_S03) || defined(MAP6_S04) || defined(MAP7_S02)
        radiusMin = Q12(1.2f);
#else
        radiusMin = Q12(1.0f);
#endif
        cond1 = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.4f));
    }

    if (cond1 || func_80070360(stalker, distToPlayer, Q12(1.0f)))
    {
        stalker->properties_E4.stalker.targetPositionX_F0 = sharedData_800E3A18_0_s00;
        stalker->properties_E4.stalker.targetPositionZ_F4 = sharedData_800E3A1C_0_s00;

        if (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_10))
        {
            stalker->properties_E4.stalker.flags_E8 |= StalkerFlag_10;
            sharedFunc_800D7E04_0_s00(stalker, 1363);
        }

        stalker->properties_E4.stalker.timer_116 = Q12(0.0f);
    }
    else if (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_10)
    {
        stalker->properties_E4.stalker.timer_116 += g_DeltaTime0;

        if (!Rng_TestProbabilityBits(9) || stalker->properties_E4.stalker.timer_116 > Q12(1.2f))
        {
            stalker->properties_E4.stalker.timer_116 = Q12(0.0f);
            stalker->properties_E4.stalker.flags_E8 &= ~StalkerFlag_10;
        }
    }

    if (distToPlayer > Q12(8.0f))
    {
        if ((stalker->properties_E4.stalker.flags_E8 & StalkerFlag_0) &&
            (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_10) &&
            !(g_SysWork.flags_22A4 & SysFlag2_MenuOpen))
        {
            if (!Vw_AabbVisibleInScreenCheck(stalker->position_18.vx - Q12(1.0f), stalker->position_18.vx + Q12(1.0f),
                                             stalker->position_18.vy - Q12(1.8f), stalker->position_18.vy,
                                             stalker->position_18.vz - Q12(1.0f), stalker->position_18.vz - Q12(1.0f)))
            {
                stalker->properties_E4.stalker.flags_E8 |= StalkerFlag_WarpRotation;
            }
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_30, true) && !(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_8) &&
        !func_800700F8(stalker, &g_SysWork.playerWork_4C.player_0))
    {
        stalker->properties_E4.stalker.timer_F8 = Q12(0.0f);

        if (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_13))
        {
            Chara_MoveSpeedUpdate3(stalker, FP_ANGLE(180.0f), (FP_ANGLE(180.0f) - ABS(angleToPlayer)) * 2);
        }

        if (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_WarpRotation)
        {
            stalker->rotation_24.vy = ratan2(stalker->properties_E4.stalker.targetPositionX_F0 - stalker->position_18.vx,
                                             stalker->properties_E4.stalker.targetPositionZ_F4 - stalker->position_18.vz);
        }
        else
        {
            for (i = 3 + ((ABS(angleToPlayer) > FP_ANGLE(90.0f)) ? 1 : 0); i > 0; i--)
            {
                if (((g_DeltaTime0 >> 3) + 1) < ABS(angleToPlayer))
                {
                    if (angleToPlayer > FP_ANGLE(0.0f))
                    {
                        stalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
                    }
                    else
                    {
                        stalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
                    }

                    angleToPlayer = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                                         sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                                  stalker->rotation_24.vy);
                }

                if (ABS(angleToPlayer) < ((g_DeltaTime0 >> 3) + 1) || distToPlayer > (radiusMin >> 2))
                {
                    break;
                }
            }
        }

        if ((g_SysWork.field_2284[3] & (1 << 0)) || func_80070320() ||
            ABS(stalker->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy) > 0x4CC ||
            ( (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_2) &&  Rng_GenerateInt(0, 3)) || // 3 in 4 chance?
            (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_2) && !Rng_GenerateInt(0, 3)))   // 1 in 4 chance.
        {
            if (!(g_SysWork.playerWork_4C.player_0.flags_3E & CharaFlag_Unk4) &&
                distToPlayer < Q12(0.9f) && (distToPlayer > Q12(0.7f) || !Rng_GenerateInt(0, 3)) && // 1 in 4 chance.
                ABS(angleToPlayer) < FP_ANGLE(90.0f) && g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
            {
                stalker->model_0.state_2 = 5;
                g_SysWork.field_2284[3] |= 1 << 1;

                sharedFunc_800D7E04_0_s00(stalker, 1364);

                if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 493, 504))
                {
                    stalker->model_0.anim_4.status_0              = 75;
                    stalker->properties_E4.stalker.keyframeIdx_FC = 29;
                    stalker->properties_E4.stalker.field_FE       = 0;
                }
                else
                {
                    stalker->model_0.anim_4.status_0              = ANIM_STATUS(StalkerAnim_7, false);
                    stalker->properties_E4.stalker.keyframeIdx_FC = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);

                    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 478, 481))
                    {
                        stalker->properties_E4.stalker.field_FE = 1;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 482, 487))
                    {
                        stalker->properties_E4.stalker.field_FE = 2;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 488, 490))
                    {
                        stalker->properties_E4.stalker.field_FE = 3;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 491, 492))
                    {
                        stalker->properties_E4.stalker.field_FE = 4;
                    }
                    else
                    {
                        stalker->properties_E4.stalker.field_FE = 0;
                    }
                }
            }
            else if (distToPlayer < Q12(0.7f))
            {
                stalker->model_0.state_2 = 4;
            }
        }
        else if (!(g_SysWork.playerWork_4C.player_0.flags_3E & CharaFlag_Unk4) &&
                 distToPlayer < Q12(1.0f) && distToPlayer > Q12(0.5f) &&
                 ABS(angleToPlayer) < FP_ANGLE(59.95f) && g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
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
            stalker->field_44.field_0                     = 1;
        }
        else if (distToPlayer < Q12(0.7f))
        {
            stalker->model_0.state_2 = 4;
        }
    }
    else
    {
        if (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_13))
        {
            Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(0.7f));
        }

        if (stalker->properties_E4.stalker.timer_F8 == Q12(0.0f))
        {
            stalker->properties_E4.stalker.targetHeadingAngle_100 = func_8006FAFC(stalker,
                                                                                  Q12(2.5f),
                                                                                  stalker->properties_E4.stalker.targetPositionX_F0,
                                                                                  stalker->properties_E4.stalker.targetPositionZ_F4,
                                                                                  Q12(1.0f),
                                                                                  true);
            if (stalker->properties_E4.stalker.targetHeadingAngle_100 == FP_ANGLE(360.0f))
            {
                stalker->properties_E4.stalker.targetHeadingAngle_100 = stalker->rotation_24.vy - FP_ANGLE(180.0f);
            }
        }

        stalker->properties_E4.stalker.timer_F8 += g_DeltaTime0;
        if (stalker->properties_E4.stalker.timer_F8 > Q12(3.0f) &&
            !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
        {
            stalker->properties_E4.stalker.timer_F8 = Q12(0.0f);
        }

        if (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_WarpRotation)
        {
            stalker->rotation_24.vy = stalker->properties_E4.stalker.targetHeadingAngle_100;
        }
        else
        {
            angleDeltaToTargetHeading = func_8005BF38(stalker->properties_E4.stalker.targetHeadingAngle_100 - stalker->rotation_24.vy);
            if (((g_DeltaTime0 >> 3) + 1) < ABS(angleDeltaToTargetHeading))
            {
                if (angleDeltaToTargetHeading > FP_ANGLE(0.0f))
                {
                    stalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
                }
                else
                {
                    stalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
                }
            }
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_30, true) && (radiusMax * 2) < distToPlayer)
    {
        temp = SquareRoot0(SQUARE(Q12_TO_Q6(stalker->position_18.vx - stalker->properties_E4.stalker.targetPositionX_F0)) +
                           SQUARE(Q12_TO_Q6(stalker->position_18.vz - stalker->properties_E4.stalker.targetPositionZ_F4)));
        temp2 = radiusMin >> 1;
        if (Q6_TO_Q12(temp) < temp2)
        {
            stalker->model_0.state_2 = 4;
        }
    }
}

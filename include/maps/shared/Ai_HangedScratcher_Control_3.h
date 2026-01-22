void Ai_HangedScratcher_Control_3(s_SubCharacter* scratcher)
{
    q19_12 distToPlayer;
    q3_12  angleDeltaToPlayer;
    q3_12  targetRotDelta;
    q19_12 playerPosYDelta;

    #define scratcherProps scratcher->properties_E4.hangedScratcher

    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       scratcher->rotation_24.vy);
    angleDeltaToPlayer = ABS(angleDeltaToPlayer);

    if (angleDeltaToPlayer < TIMESTEP_ANGLE_3)
    {
        Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), scratcherProps.radiusMax_10C);

        scratcherProps.timer_EA = Q12(0.0f);
    }
    else
    {
        if (angleDeltaToPlayer < FP_ANGLE(60.0f) && distToPlayer > Q12(2.0f))
        {
            Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), scratcherProps.radiusMax_10C);
        }
        else if (angleDeltaToPlayer < FP_ANGLE(120.0f) && distToPlayer > Q12(4.0f))
        {
            Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), scratcherProps.radiusMax_10C / 2);
        }
        else
        {
            Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));
        }

        scratcherProps.timer_EA += g_DeltaTime0;
        if (distToPlayer > Q12(7.5f) && scratcherProps.timer_EA > Q12(1.8f))
        {
            scratcherProps.targetRotY_EC = Chara_HeadingAngleGet(scratcher,
                                                                                           Q12(5.0f),
                                                                                           g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                                           g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                                           FP_ANGLE(360.0f),
                                                                                           true);
            if (scratcherProps.targetRotY_EC == FP_ANGLE(360.0f))
            {
                scratcherProps.targetRotY_EC = scratcher->rotation_24.vy;
            }

            scratcherProps.timer_EA = Q12(0.0f);
        }
        else if (distToPlayer > Q12(3.0f) && scratcherProps.timer_EA > Q12(0.6f))
        {
            scratcherProps.targetRotY_EC = Chara_HeadingAngleGet(scratcher,
                Q12(1.5f),
                                                                                          g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                                          g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                                          FP_ANGLE(360.0f),
                                                                                          true);
            if (scratcherProps.targetRotY_EC == FP_ANGLE(360.0f))
            {
                scratcherProps.targetRotY_EC = scratcher->rotation_24.vy;
            }

            scratcherProps.timer_EA = Q12(0.0f);
        }
        else
        {
            scratcherProps.targetRotY_EC = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);

            scratcherProps.timer_EA = Q12(0.0f);
        }

        targetRotDelta = func_8005BF38(scratcherProps.targetRotY_EC - scratcher->rotation_24.vy);
        if (ABS(targetRotDelta) > TIMESTEP_ANGLE_3)
        {
            if (targetRotDelta > FP_ANGLE(0.0f))
            {
                scratcher->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.5f));
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.5f));
            }
        }
    }

    if (sharedFunc_800D3214_5_s00(scratcher) != 0)
    {
        scratcher->model_0.controlState_2                  = HangedScratcherControl_8;
        scratcher->model_0.anim_4.status_0                 = ANIM_STATUS(HangedScratcherAnim_16, false);
        scratcher->moveSpeed_38                            = Q12(0.0f);
        scratcherProps.flags_E8 |= HangedScratcherFlag_1;
    }
    else
    {
        if (!Chara_HasFlag(&g_SysWork.playerWork_4C.player_0, 8) && !(g_SysWork.field_2284[3] & (1 << 1)))
        {
            if (g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f) &&
                distToPlayer < Q12(1.0f) && angleDeltaToPlayer < FP_ANGLE(30.0f))
            {
                playerPosYDelta = scratcher->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy;
                if (playerPosYDelta < Q12(-3.5f))
                {
                    if (playerPosYDelta > Q12(-3.7f))
                    {
                        scratcher->model_0.controlState_2                 = HangedScratcherControl_4;
                        scratcherProps.timer_EA = Q12(0.0f);
                        scratcher->model_0.anim_4.status_0                = ANIM_STATUS(HangedScratcherAnim_4, false);
                        g_SysWork.field_2284[3]                          |= HangedScratcherFlag_1;
                        return;
                    }
                }
            }
        }

        if (distToPlayer > Q12(20.0f) && !Rng_GenerateInt(0, 31)) // 1 in 32 chance.
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_2;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_14, false);
        }
    }

    #undef scratcherProps
}

void Ai_HangedScratcher_Control_7(s_SubCharacter* scratcher)
{
    q19_12 distToPlayer;
    q3_12  angleDeltaToPlayer;
    q3_12  angleDeltaToPlayerAbs;
    q19_12 angleToPlayer;
    bool   cond;
    q3_12  targetRotDelta;

    #define scratcherProps scratcher->properties_E4.hangedScratcher

    distToPlayer          = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    angleDeltaToPlayer    = func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                          scratcher->rotation_24.vy);
    angleDeltaToPlayerAbs = ABS(angleDeltaToPlayer);
    angleToPlayer         = Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18);

    if (distToPlayer > Q12(16.0f))
    {
        scratcher->model_0.controlState_2                 = HangedScratcherControl_6;
        scratcherProps.timer_EA = Q12(0.5f);
        scratcher->model_0.anim_4.status_0                = ANIM_STATUS(HangedScratcherAnim_15, false);
        scratcherProps.field_EE = 37;
        return;
    }

    cond = func_800700F8(scratcher, &g_SysWork.playerWork_4C.player_0);

    if (angleDeltaToPlayerAbs < TIMESTEP_ANGLE_4 && !cond)
    {
        Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcherProps.radiusMin_10E);
        scratcherProps.timer_EA = Q12(0.0f);
    }
    else
    {
        if (!cond)
        {
            if (angleDeltaToPlayerAbs < FP_ANGLE(45.0f) && distToPlayer > Q12(2.0f))
            {
                Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcherProps.radiusMin_10E);
            }
            else if (angleDeltaToPlayerAbs < FP_ANGLE(90.0f) && distToPlayer > Q12(4.0f))
            {
                Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcherProps.radiusMin_10E / 2);
            }
            else
            {
                Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));
            }
        }
        else
        {
            Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcherProps.radiusMin_10E);
        }

        scratcherProps.timer_EA += g_DeltaTime0;

        if (distToPlayer < Q12(2.0f) && !cond)
        {
            scratcherProps.timer_EA      = Q12(0.0f);
            scratcherProps.targetHeadingAngle_EC = angleToPlayer;
        }
        else if (scratcherProps.timer_EA > Q12(0.6f) ||
                 (scratcherProps.timer_EA > Q12(0.3f) &&
                  cond && !Rng_GenerateInt(0, 7))) // 1 in 8 chance.
        {
            scratcherProps.timer_EA = Q12(0.0f);

            scratcherProps.targetHeadingAngle_EC = Chara_HeadingAngleGet(scratcher, Q12(1.0f), g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz, FP_ANGLE(360.0f), true);
            if (scratcherProps.targetHeadingAngle_EC == FP_ANGLE(360.0f))
            {
                scratcherProps.targetHeadingAngle_EC = scratcher->rotation_24.vy - FP_ANGLE(180.0f);
            }
        }

        targetRotDelta = func_8005BF38(scratcherProps.targetHeadingAngle_EC - scratcher->rotation_24.vy);
        if (ABS(targetRotDelta) > TIMESTEP_ANGLE_4)
        {
            if (targetRotDelta > FP_ANGLE(0.0f))
            {
                scratcher->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f));
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f));
            }
        }
        else
        {
            scratcher->rotation_24.vy = scratcherProps.targetHeadingAngle_EC;
        }
    }

    if (!cond && !(g_SysWork.field_2284[3] & 2) && !(g_SysWork.playerWork_4C.player_0.flags_3E & CharaFlag_Unk4) &&
        g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
    {
        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) < Q12(1.2f))
        {
            if (ABS(func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                  scratcher->rotation_24.vy)) < FP_ANGLE(20.0f))
            {
                scratcher->model_0.controlState_2                 = HangedScratcherControl_15;
                g_SysWork.field_2284[3]                          |= 2;
                scratcherProps.timer_EA = Q12(0.0f);
                scratcher->model_0.anim_4.status_0                = ANIM_STATUS(HangedScratcherAnim_5, false);
            }
        }
    }

    #undef scratcherProps
}

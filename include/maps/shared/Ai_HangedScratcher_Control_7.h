void Ai_HangedScratcher_Control_7(s_SubCharacter* scratcher)
{
    s32  playerDist;
    s16  playerDir;
    s16  playerDirAbs;
    s32  playerDir2;
    bool cond;
    s16  targetRotDelta;

    playerDist   = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    playerDir    = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) - scratcher->rotation_24.vy);
    playerDirAbs = ABS(playerDir);
    playerDir2   = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);

    if (playerDist > Q12(16.0f))
    {
        scratcher->model_0.controlState_2                 = 6;
        scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.5f);
        scratcher->model_0.anim_4.status_0                = ANIM_STATUS(15, false);
        scratcher->properties_E4.hangedScratcher.field_EE = 37;
        return;
    }

    cond = func_800700F8(scratcher, &g_SysWork.playerWork_4C.player_0);

    if (playerDirAbs < TIMESTEP_ANGLE_4 && !cond)
    {
        Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcher->properties_E4.hangedScratcher.radiusMin_10E);
        scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
    }
    else
    {
        if (!cond)
        {
            if (playerDirAbs < FP_ANGLE(45.0f) && playerDist > Q12(2.0f))
            {
                Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcher->properties_E4.hangedScratcher.radiusMin_10E);
            }
            else if (playerDirAbs < FP_ANGLE(90.0f) && playerDist > Q12(4.0f))
            {
                Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcher->properties_E4.hangedScratcher.radiusMin_10E / 2);
            }
            else
            {
                Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));
            }
        }
        else
        {
            Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcher->properties_E4.hangedScratcher.radiusMin_10E);
        }

        scratcher->properties_E4.hangedScratcher.timer_EA += g_DeltaTime0;

        if (playerDist < Q12(2.0f) && !cond)
        {
            scratcher->properties_E4.hangedScratcher.timer_EA      = Q12(0.0f);
            scratcher->properties_E4.hangedScratcher.targetRotY_EC = playerDir2;
        }
        else if (scratcher->properties_E4.hangedScratcher.timer_EA > Q12(0.6f) ||
                 (scratcher->properties_E4.hangedScratcher.timer_EA > Q12(0.3f) && cond && !Rng_GenerateInt(0, 7)))
        {
            scratcher->properties_E4.hangedScratcher.timer_EA      = Q12(0.0f);
            scratcher->properties_E4.hangedScratcher.targetRotY_EC = Chara_HeadingAngleGet(scratcher, Q12(1.0f), g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz, FP_ANGLE(360.0f), true);
            if (scratcher->properties_E4.hangedScratcher.targetRotY_EC == FP_ANGLE(360.0f))
            {
                scratcher->properties_E4.hangedScratcher.targetRotY_EC = scratcher->rotation_24.vy - FP_ANGLE(180.0f);
            }
        }

        targetRotDelta = func_8005BF38(scratcher->properties_E4.hangedScratcher.targetRotY_EC - scratcher->rotation_24.vy);
        if (ABS(targetRotDelta) > TIMESTEP_ANGLE_4)
        {
            if (targetRotDelta > 0)
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
            scratcher->rotation_24.vy = scratcher->properties_E4.hangedScratcher.targetRotY_EC;
        }
    }

    if (!cond && !(g_SysWork.field_2284[3] & 2) && !(g_SysWork.playerWork_4C.player_0.flags_3E & 8) &&
        g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
    {
        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) < Q12(1.2f))
        {
            if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) - scratcher->rotation_24.vy)) < FP_ANGLE(20.0f))
            {
                scratcher->model_0.controlState_2                 = 15;
                g_SysWork.field_2284[3]                          |= 2;
                scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
                scratcher->model_0.anim_4.status_0                = ANIM_STATUS(5, false);
            }
        }
    }
}

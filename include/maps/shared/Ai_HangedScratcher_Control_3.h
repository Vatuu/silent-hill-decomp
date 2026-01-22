void Ai_HangedScratcher_Control_3(s_SubCharacter* scratcher)
{
    s32 playerDist;
    s16 playerDir;
    u16 moveSpeedLimit;
    s16 targetRotDelta;
    s32 playerPosYDelta;

    playerDist = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                     g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    playerDir  = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) - scratcher->rotation_24.vy);
    playerDir  = ABS(playerDir);

    if (playerDir < TIMESTEP_ANGLE_3)
    {
        moveSpeedLimit = scratcher->properties_E4.hangedScratcher.radiusMax_10C;

        Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), moveSpeedLimit);

        scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
    }
    else
    {
        if (playerDir < FP_ANGLE(60.0f) && playerDist > Q12(2.0f))
        {

            moveSpeedLimit = scratcher->properties_E4.hangedScratcher.radiusMax_10C;

            Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), moveSpeedLimit);
        }
        else if (playerDir < FP_ANGLE(120.0f) && playerDist > Q12(4.0f))
        {
            moveSpeedLimit = scratcher->properties_E4.hangedScratcher.radiusMax_10C;

            Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), moveSpeedLimit >> 1);
        }
        else
        {
            Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));
        }
        scratcher->properties_E4.hangedScratcher.timer_EA += g_DeltaTime0;

        if (playerDist > Q12(7.5f) && scratcher->properties_E4.hangedScratcher.timer_EA > Q12(1.8f))
        {
            scratcher->properties_E4.hangedScratcher.targetRotY_EC = Chara_HeadingAngleGet(scratcher, Q12(5.0f), g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz, FP_ANGLE(360.0f), true);
            if (scratcher->properties_E4.hangedScratcher.targetRotY_EC == FP_ANGLE(360.0f))
            {
                scratcher->properties_E4.hangedScratcher.targetRotY_EC = scratcher->rotation_24.vy;
            }
            scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
        }
        else if (playerDist > Q12(3.0f) && scratcher->properties_E4.hangedScratcher.timer_EA > Q12(0.6f))
        {
            scratcher->properties_E4.hangedScratcher.targetRotY_EC = Chara_HeadingAngleGet(scratcher, Q12(1.5f), g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz, FP_ANGLE(360.0f), true);
            if (scratcher->properties_E4.hangedScratcher.targetRotY_EC == FP_ANGLE(360.0f))
            {
                scratcher->properties_E4.hangedScratcher.targetRotY_EC = scratcher->rotation_24.vy;
            }
            scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
        }
        else
        {
            scratcher->properties_E4.hangedScratcher.targetRotY_EC = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);

            scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
        }

        targetRotDelta = func_8005BF38(scratcher->properties_E4.hangedScratcher.targetRotY_EC - scratcher->rotation_24.vy);

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
        scratcher->model_0.controlState_2                  = 8;
        scratcher->model_0.anim_4.status_0                 = ANIM_STATUS(16, false);
        scratcher->moveSpeed_38                            = Q12(0.0f);
        scratcher->properties_E4.hangedScratcher.flags_E8 |= (1 << 1);
    }
    else
    {
        if (!Chara_HasFlag(&g_SysWork.playerWork_4C.player_0, 8) && !(g_SysWork.field_2284[3] & 2))
        {
            if (g_SysWork.playerWork_4C.player_0.health_B0 > 0 && playerDist < Q12(1.0f) && playerDir < FP_ANGLE(30.0f))
            {
                playerPosYDelta = scratcher->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy;
                if (playerPosYDelta < Q12(-3.5f))
                {
                    if (playerPosYDelta > Q12(-3.7f))
                    {
                        scratcher->model_0.controlState_2                 = 4;
                        scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
                        scratcher->model_0.anim_4.status_0                = ANIM_STATUS(4, false);
                        g_SysWork.field_2284[3]                          |= 2;
                        return;
                    }
                }
            }
        }

        if (playerDist > Q12(20.0f) && !Rng_GenerateInt(0, 31))
        {
            scratcher->model_0.controlState_2  = 2;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(14, false);
        }
    }
}

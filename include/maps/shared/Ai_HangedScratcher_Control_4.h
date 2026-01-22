void Ai_HangedScratcher_Control_4(s_SubCharacter* scratcher)
{
    VECTOR3 attackPos;
    s16     playerDir;
    s16     playerDirAbs;
    s32     playerDist;

    playerDist   = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    playerDir    = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) - scratcher->rotation_24.vy);
    playerDirAbs = ABS(playerDir);

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 98, 103))
    {
        if (playerDirAbs > TIMESTEP_ANGLE_3)
        {
            if (playerDir > 0)
            {
                scratcher->rotation_24.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.5f);
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.5f);
            }
        }

        if (playerDist > Q12(0.2f))
        {
            scratcher->moveSpeed_38 = Q12(1.0f);
        }
        else
        {
            scratcher->moveSpeed_38 = Q12(0.0f);
        }

        scratcher->field_44.field_0 = 1;
    }
    else
    {
        scratcher->moveSpeed_38 = 0;

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 104, 105))
        {
            attackPos.vx                                       = scratcher->position_18.vx;
            attackPos.vy                                       = Q12(-1.45f);
            attackPos.vz                                       = scratcher->position_18.vz;
            scratcher->properties_E4.hangedScratcher.flags_E8 |= (1 << 5);

            // TODO: 44 is `WEAPON_ATTACK`?
            func_8008A0E4(1, 44, scratcher, &attackPos, &g_SysWork.playerWork_4C.player_0, scratcher->rotation_24.vy, ratan2(playerDist, (g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6) - attackPos.vy));
        }
        else if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == 14)
        {
            if (playerDist > Q12(6.0f) && !Rng_GenerateInt(0, 15))
            {
                scratcher->model_0.controlState_2                 = 3;
                scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
                scratcher->model_0.anim_4.status_0                = ANIM_STATUS(17, false);
                g_SysWork.field_2284[3]                          &= ~2;
            }
            else
            {
                scratcher->properties_E4.hangedScratcher.timer_EA += g_DeltaTime0;

                if (scratcher->properties_E4.hangedScratcher.timer_EA > Q12(3.0f) && !Rng_GenerateInt(0, 7))
                {
                    scratcher->properties_E4.hangedScratcher.timer_EA = Q12(0.0f);
                    scratcher->model_0.controlState_2                 = 2;
                    g_SysWork.field_2284[3]                          &= ~2;
                }
            }
        }
    }
}

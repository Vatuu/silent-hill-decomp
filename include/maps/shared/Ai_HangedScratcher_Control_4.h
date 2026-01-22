void Ai_HangedScratcher_Control_4(s_SubCharacter* scratcher)
{
    VECTOR3 attackPos; // Q19.12
    q19_12  distToPlayer;
    q3_12   angleDeltaToPlayer;
    q3_12   angleDeltaToPlayerAbs;

    #define scratcherProps scratcher->properties_E4.hangedScratcher

    distToPlayer          = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    angleDeltaToPlayer    = func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                          scratcher->rotation_24.vy);
    angleDeltaToPlayerAbs = ABS(angleDeltaToPlayer);

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 98, 103))
    {
        if (angleDeltaToPlayerAbs > TIMESTEP_ANGLE_3)
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                scratcher->rotation_24.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.5f);
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.5f);
            }
        }

        if (distToPlayer > Q12(0.2f))
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
        scratcher->moveSpeed_38 = Q12(0.0f);

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 104, 105))
        {
            attackPos.vx                                       = scratcher->position_18.vx;
            attackPos.vy                                       = Q12(-1.45f);
            attackPos.vz                                       = scratcher->position_18.vz;
            scratcherProps.flags_E8 |= HangedScratcherFlag_5;

            // TODO: 44 is `WEAPON_ATTACK`?
            func_8008A0E4(1, 44, scratcher, &attackPos, &g_SysWork.playerWork_4C.player_0, scratcher->rotation_24.vy,
                          ratan2(distToPlayer, (g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6) - attackPos.vy));
        }
        else if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_14)
        {
            if (distToPlayer > Q12(6.0f) && !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
            {
                scratcher->model_0.controlState_2                 = HangedScratcherControl_3;
                scratcherProps.timer_EA = Q12(0.0f);
                scratcher->model_0.anim_4.status_0                = ANIM_STATUS(17, false);
                g_SysWork.field_2284[3]                          &= ~(1 << 1);
            }
            else
            {
                scratcherProps.timer_EA += g_DeltaTime0;

                if (scratcherProps.timer_EA > Q12(3.0f) && !Rng_GenerateInt(0, 7))
                {
                    scratcherProps.timer_EA = Q12(0.0f);
                    scratcher->model_0.controlState_2                 = HangedScratcherControl_2;
                    g_SysWork.field_2284[3]                          &= ~(1 << 1);
                }
            }
        }
    }

    #undef scratcherProps
}

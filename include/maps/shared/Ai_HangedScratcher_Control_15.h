void Ai_HangedScratcher_Control_15(s_SubCharacter* scratcher)
{
    VECTOR3 attackPos;
    q19_12  distToPlayer;
    q3_12   angleDeltaToPlayer;

    #define scratcherProps scratcher->properties_E4.hangedScratcher

    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       scratcher->rotation_24.vy);

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 116, 123) &&
        distToPlayer > Q12(1.0f) && angleDeltaToPlayer < FP_ANGLE(20.0f))
    {
        scratcher->moveSpeed_38 = Q12(1.0f);
    }
    else
    {
        scratcher->moveSpeed_38 = Q12(0.0f);
    }

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 116, 128))
    {
        if (ABS(angleDeltaToPlayer) > TIMESTEP_ANGLE_0)
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                scratcher->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.125f));
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.125f));
            }
        }
        else
        {
            scratcher->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                               g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
        }
    }

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 124, 130))
    {
        if (scratcher->field_44.field_0 == 0)
        {
            scratcher->field_44.field_0 = 1;
        }

        attackPos.vx = scratcher->position_18.vx;
        attackPos.vy = scratcher->position_18.vy - Q12(0.8f);
        attackPos.vz = scratcher->position_18.vz;

        scratcherProps.flags_E8 |= HangedScratcherFlag_5;

        // TODO: 45 is `WEAPON_ATTACK`?
        func_8008A0E4(1, 45, scratcher, &attackPos, &g_SysWork.playerWork_4C.player_0, scratcher->rotation_24.vy, FP_ANGLE(90.0f));
    }

    if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_15, true))
    {
        if (scratcherProps.timer_EA == Q12(0.0f))
        {
            g_SysWork.field_2284[3] &= ~(1 << 1);
        }

        scratcherProps.timer_EA += g_DeltaTime0;

        if (scratcherProps.timer_EA > Q12(2.5f) ||
            (scratcherProps.timer_EA > Q12(0.8f) &&
            !Rng_GenerateInt(0, 31))) // 1 in 32 chance.
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_7;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
        }
    }
    else
    {
        scratcherProps.timer_EA = Q12(0.0f);
    }

    #undef scratcherProps
}

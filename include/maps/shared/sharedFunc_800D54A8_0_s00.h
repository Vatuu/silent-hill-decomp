void sharedFunc_800D54A8_0_s00(s_SubCharacter* stalker)
{
    VECTOR3 vec0;
    q3_12   angleDeltaToPlayer;
    q3_12   moveSpeed;
    q19_12  distToPlayer;
    s32     i;
    u32     animStatus;

    stalker->field_E1_0 = 3;

    Chara_MoveSpeedUpdate(stalker, Q12(1.5f));

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

    moveSpeed = Q12(0.0f);
    angleDeltaToPlayer = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                              g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz) -
                                       stalker->rotation_24.vy);

    if (ABS(angleDeltaToPlayer) < FP_ANGLE(45.0f))
    {
        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_34, true) && distToPlayer > Q12(0.53f))
        {
            moveSpeed = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_35, true) && distToPlayer > Q12(0.38f))
        {
            moveSpeed = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
        }
    }

    for (i = 0; i < 3; i++)
    {
        if (((g_DeltaTime0 >> 4) + 1) < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                stalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
            }
            else
            {
                stalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
            }
        }

        angleDeltaToPlayer = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                                  g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz) -
                                           stalker->rotation_24.vy);
    }

    if (stalker->properties_E4.stalker.flags_E8 & StalkerFlag_5)
    {
        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_9, true))
        {
            if (distToPlayer < Q12(0.52f) || distToPlayer > Q12(0.54f))
            {
                moveSpeed = CLAMP_HIGH(FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT), distToPlayer - Q12(0.53f));
            }

            stalker->properties_E4.stalker.relAnimTime_104 = stalker->model_0.anim_4.time_4 - Q12(83.0f);
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_8, true))
        {
            if (distToPlayer < Q12(0.37f) || distToPlayer > Q12(0.39f))
            {
                moveSpeed = CLAMP_HIGH(FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT), distToPlayer - Q12(0.38f));
            }

            stalker->properties_E4.stalker.relAnimTime_104 = stalker->model_0.anim_4.time_4 - Q12(70.0f);
        }
        else
        {
            stalker->properties_E4.stalker.relAnimTime_104 = Q12(0.0f);
        }

        stalker->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                         g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

        if (g_SysWork.playerWork_4C.player_0.attackReceived_41 == NO_VALUE)
        {
            g_SysWork.field_2284[3]                      &= ~(1 << 0);
            animStatus                                    = stalker->model_0.anim_4.status_0;
            stalker->model_0.state_2                      = 9;
            stalker->model_0.anim_4.status_0              = ANIM_STATUS(StalkerAnim_10, false);
            stalker->properties_E4.stalker.keyframeIdx_FC = animStatus;
            stalker->field_E1_0                           = 0;
            stalker->field_E1_0                           = 3;

            stalker->properties_E4.stalker.flags_E8 |= StalkerFlag_6;
            stalker->properties_E4.stalker.flags_E8 &= ~StalkerFlag_5;
        }
        else
        {
            stalker->properties_E4.stalker.timer_F8 += g_DeltaTime0;
            if (stalker->properties_E4.stalker.timer_F8 > Q12(1.5f))
            {
                g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[50].field_4, Q12_SHIFT) * Rng_GenerateUInt(85, 116)) / 100;
                stalker->properties_E4.stalker.timer_F8              = Rng_Rand16() % Q12(0.5f);
            }
        }
    } 
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 472, 476))
    {
        vec0.vx = stalker->position_18.vx;
        vec0.vy = stalker->position_18.vy + stalker->field_C8.field_8;
        vec0.vz = stalker->position_18.vz;

        // TODO: What's weapon attack 49?
        if (func_8008A0E4(1, 49, stalker, &vec0, &g_SysWork.playerWork_4C, stalker->rotation_24.vy, FP_ANGLE(90.0f)) != NO_VALUE)
        {
            stalker->properties_E4.stalker.flags_E8 |= StalkerFlag_5;
            g_SysWork.field_2284[3]                 &= ~(1 << 1);

            sharedFunc_800D7E04_0_s00(stalker, 1366);

            stalker->properties_E4.stalker.timer_F8 = Q12(1.0f);
        }
    }
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_9, true) ||
             stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_8, true) ||
             distToPlayer > Q12(2.0f))
    {
        g_SysWork.field_2284[3] &= ~((1 << 0) | (1 << 1));
        stalker->model_0.state_2   = 9;

        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_34, true) || stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_9, false))
        {
            stalker->properties_E4.stalker.keyframeIdx_FC = ANIM_STATUS(StalkerAnim_9, true);
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_35, true) || stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_8, false))
        {
            stalker->properties_E4.stalker.keyframeIdx_FC = ANIM_STATUS(StalkerAnim_8, true);
        }
        else
        {
            stalker->properties_E4.stalker.keyframeIdx_FC = stalker->model_0.anim_4.status_0;
        }

        stalker->properties_E4.stalker.flags_E8 |= StalkerFlag_6;
        stalker->model_0.anim_4.status_0         = ANIM_STATUS(StalkerAnim_36, false);
        stalker->field_E1_0                      = 3;
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        stalker->properties_E4.stalker.offset_EC = FP_MULTIPLY(moveSpeed, Math_Sin(stalker->rotation_24.vy), Q12_SHIFT);
        stalker->properties_E4.stalker.offset_EE = FP_MULTIPLY(moveSpeed, Math_Cos(stalker->rotation_24.vy), Q12_SHIFT);
    }
}

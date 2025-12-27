void sharedFunc_800D54A8_0_s00(s_SubCharacter* stalker)
{
    VECTOR3 vec0;
    q3_12   angle;
    q3_12   var_s6;
    q19_12  dist;
    s32     i;
    u32     animStatus;

    stalker->field_E1_0 = 3;

    Chara_MoveSpeedUpdate(stalker, Q12(1.5f));

    dist = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

    var_s6 = 0;
    angle = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                 g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz) -
                          stalker->rotation_24.vy);

    if (ABS(angle) < FP_ANGLE(45.0f))
    {
        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(34, true) && dist > Q12(0.53f))
        {
            var_s6 = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(35, true) && dist > Q12(0.38f))
        {
            var_s6 = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
        }
    }

    for (i = 0; i < 3; i++)
    {
        if (((g_DeltaTime0 >> 4) + 1) < ABS(angle))
        {
            if (angle > FP_ANGLE(0.0f))
            {
                stalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
            }
            else
            {
                stalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
            }
        }

        angle = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                     g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz) -
                              stalker->rotation_24.vy);
    }

    if (stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 5))
    {
        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(9, true))
        {
            if (dist < Q12(0.52f) || dist > Q12(0.54f))
            {
                var_s6 = CLAMP_HIGH(FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT), dist - Q12(0.53f));
            }

            stalker->properties_E4.player.field_104 = stalker->model_0.anim_4.time_4 + Q12(-83.0f);
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(8, true))
        {
            if (dist < Q12(0.37f) || dist > Q12(0.39f))
            {
                var_s6 = CLAMP_HIGH(FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT), dist - Q12(0.38f));
            }

            stalker->properties_E4.player.field_104 = stalker->model_0.anim_4.time_4 + Q12(-70.0f);
        }
        else
        {
            stalker->properties_E4.player.field_104 = Q12(0.0f);
        }

        stalker->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

        if (g_SysWork.playerWork_4C.player_0.attackReceived_41 == NO_VALUE)
        {
            g_SysWork.field_2284[3]                                     &= ~(1 << 0);
            animStatus                                                   = stalker->model_0.anim_4.status_0;
            stalker->model_0.state_2                                       = 9;
            stalker->model_0.anim_4.status_0                               = ANIM_STATUS(10, false);
            stalker->properties_E4.dummy.properties_E8[5].val16[0] = animStatus;
            stalker->field_E1_0                                            = 0;
            stalker->field_E1_0                                            = 3;

            stalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 6;
            stalker->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 5);
        }
        else
        {
            stalker->properties_E4.player.runTimer_F8 += g_DeltaTime0;

            if (stalker->properties_E4.player.runTimer_F8 > Q12(1.5f))
            {
                g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[50].field_4, Q12_SHIFT) * Rng_GenerateUInt(85, 116)) / 100;
                stalker->properties_E4.player.runTimer_F8         = Rng_Rand16() % Q12(0.5f);
            }
        }
    }
    else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 471 &&
             FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 477)
    {
        vec0.vx = stalker->position_18.vx;
        vec0.vy = stalker->position_18.vy + stalker->field_C8.field_8;
        vec0.vz = stalker->position_18.vz;

        // TODO: What's weapon attack 49?
        if (func_8008A0E4(1, 49, stalker, &vec0, &g_SysWork.playerWork_4C, stalker->rotation_24.vy, FP_ANGLE(90.0f)) != NO_VALUE)
        {
            stalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 5;
            g_SysWork.field_2284[3]                                      &= ~(1 << 1);
            sharedFunc_800D7E04_0_s00(stalker, 1366);
            stalker->properties_E4.player.runTimer_F8 = Q12(1.0f);
        }
    }
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(9, true) ||
             stalker->model_0.anim_4.status_0 == ANIM_STATUS(8, true) ||
             dist > Q12(2.0f))
    {
        g_SysWork.field_2284[3] &= ~((1 << 0) | (1 << 1));
        stalker->model_0.state_2   = 9;

        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(34, true) || stalker->model_0.anim_4.status_0 == ANIM_STATUS(9, false))
        {
            stalker->properties_E4.dummy.properties_E8[5].val16[0] = ANIM_STATUS(9, true);
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(35, true) || stalker->model_0.anim_4.status_0 == ANIM_STATUS(8, false))
        {
            stalker->properties_E4.dummy.properties_E8[5].val16[0] = ANIM_STATUS(8, true);
        }
        else
        {
            stalker->properties_E4.dummy.properties_E8[5].val16[0] = stalker->model_0.anim_4.status_0;
        }

        stalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 6;
        stalker->model_0.anim_4.status_0                                = ANIM_STATUS(36, false);
        stalker->field_E1_0                                             = 3;
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        stalker->properties_E4.dummy.properties_E8[1].val16[0] = FP_MULTIPLY(var_s6, Math_Sin(stalker->rotation_24.vy), Q12_SHIFT);
        stalker->properties_E4.dummy.properties_E8[1].val16[1] = FP_MULTIPLY(var_s6, Math_Cos(stalker->rotation_24.vy), Q12_SHIFT);
    }
}

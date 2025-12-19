void sharedFunc_800D54A8_0_s00(s_SubCharacter* chara)
{
    VECTOR3 vec0;
    q3_12   angle;
    q3_12   var_s6;
    q19_12  dist;
    s32     i;
    u32     animStatus;

    chara->field_E1_0 = 3;

    Chara_MoveSpeedUpdate(chara, Q12(1.5f));

    dist = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    var_s6 = 0;
    angle = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                 g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                          chara->rotation_24.vy);

    if (ABS(angle) < FP_ANGLE(45.0f))
    {
        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(34, true) && dist > Q12(0.53f))
        {
            var_s6 = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
        }
        else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(35, true) && dist > Q12(0.38f))
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
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
            }
        }

        angle = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                     g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                              chara->rotation_24.vy);
    }

    if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 5))
    {
        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(9, true))
        {
            if (dist < Q12(0.52f) || dist > Q12(0.54f))
            {
                var_s6 = CLAMP_HIGH(FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT), dist - Q12(0.53f));
            }

            chara->properties_E4.player.field_104 = chara->model_0.anim_4.time_4 + Q12(-83.0f);
        }
        else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(8, true))
        {
            if (dist < Q12(0.37f) || dist > Q12(0.39f))
            {
                var_s6 = CLAMP_HIGH(FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT), dist - Q12(0.38f));
            }

            chara->properties_E4.player.field_104 = chara->model_0.anim_4.time_4 + Q12(-70.0f);
        }
        else
        {
            chara->properties_E4.player.field_104 = Q12(0.0f);
        }

        chara->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

        if (g_SysWork.playerWork_4C.player_0.attackReceived_41 == NO_VALUE)
        {
            g_SysWork.field_2284[3]                                     &= ~(1 << 0);
            animStatus                                                   = chara->model_0.anim_4.status_0;
            chara->model_0.state_2                                       = 9;
            chara->model_0.anim_4.status_0                               = ANIM_STATUS(10, false);
            chara->properties_E4.dummy.properties_E8[5].val16[0] = animStatus;
            chara->field_E1_0                                            = 0;
            chara->field_E1_0                                            = 3;

            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 6;
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 5);
        }
        else
        {
            chara->properties_E4.player.runTimer_F8 += g_DeltaTime0;

            if (chara->properties_E4.player.runTimer_F8 > Q12(1.5f))
            {
                g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[50].field_4, Q12_SHIFT) * Rng_GenerateUInt(85, 116)) / 100;
                chara->properties_E4.player.runTimer_F8         = Rng_Rand16() % Q12(0.5f);
            }
        }
    }
    else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 471 &&
             FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 477)
    {
        vec0.vx = chara->position_18.vx;
        vec0.vy = chara->position_18.vy + chara->field_C8.field_8;
        vec0.vz = chara->position_18.vz;

        // TODO: What's weapon attack 49?
        if (func_8008A0E4(1, 49, chara, &vec0, &g_SysWork.playerWork_4C, chara->rotation_24.vy, FP_ANGLE(90.0f)) != NO_VALUE)
        {
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 5;
            g_SysWork.field_2284[3]                                      &= ~(1 << 1);
            sharedFunc_800D7E04_0_s00(chara, 1366);
            chara->properties_E4.player.runTimer_F8 = Q12(1.0f);
        }
    }
    else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(9, true) ||
             chara->model_0.anim_4.status_0 == ANIM_STATUS(8, true) ||
             dist > Q12(2.0f))
    {
        g_SysWork.field_2284[3] &= ~((1 << 0) | (1 << 1));
        chara->model_0.state_2   = 9;

        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(34, true) || chara->model_0.anim_4.status_0 == ANIM_STATUS(9, false))
        {
            chara->properties_E4.dummy.properties_E8[5].val16[0] = ANIM_STATUS(9, true);
        }
        else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(35, true) || chara->model_0.anim_4.status_0 == ANIM_STATUS(8, false))
        {
            chara->properties_E4.dummy.properties_E8[5].val16[0] = ANIM_STATUS(8, true);
        }
        else
        {
            chara->properties_E4.dummy.properties_E8[5].val16[0] = chara->model_0.anim_4.status_0;
        }

        chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 6;
        chara->model_0.anim_4.status_0                                = ANIM_STATUS(36, false);
        chara->field_E1_0                                             = 3;
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        chara->properties_E4.dummy.properties_E8[1].val16[0] = FP_MULTIPLY(var_s6, Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
        chara->properties_E4.dummy.properties_E8[1].val16[1] = FP_MULTIPLY(var_s6, Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
    }
}

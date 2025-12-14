void sharedFunc_800D54A8_0_s00(s_SubCharacter* chara)
{
    VECTOR3 vec0;
    q3_12   angle;
    q3_12   var_s6;
    q19_12  dist;
    s32     i;
    u32     animStatus;

    // TODO: Demagic everything.

    chara->field_E1_0 = 3;

    Chara_MoveSpeedUpdate(chara, Q12(1.5f));

    dist = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

    var_s6 = 0;
    angle = func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                 g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) -
                          chara->rotation_24.vy);

    if (ABS(angle) < FP_ANGLE(45.0f))
    {
        if (chara->model_0.anim_4.status_0 == 0x45 && dist >= 0x87B)
        {
            var_s6 = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
        }
        else if (chara->model_0.anim_4.status_0 == 0x47 && dist >= 0x615)
        {
            var_s6 = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
        }
    }

    for (i = 0; i < 3; i++)
    {
        if ((g_DeltaTime0 >> 4) + 1 < ABS(angle))
        {
            if (angle > 0)
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT);
            }
        }

        angle = func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                     g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) -
                              chara->rotation_24.vy);
    }

    if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x20)
    {
        if (chara->model_0.anim_4.status_0 == 0x13)
        {
            if (dist < 0x851 || dist > 0x8A3)
            {
                var_s6 = CLAMP_HIGH(FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT), dist - 0x87A);
            }
            chara->properties_E4.player.field_104 = chara->model_0.anim_4.time_4 + Q12(-83.0f);
        }
        else if (chara->model_0.anim_4.status_0 == 0x11)
        {
            if (dist < 0x5EB || dist > 0x63D)
            {
                var_s6 = CLAMP_HIGH(FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT), dist - 0x614);
            }
            chara->properties_E4.player.field_104 = chara->model_0.anim_4.time_4 + Q12(-70.0f);
        }
        else
        {
            chara->properties_E4.player.field_104 = 0;
        }

        chara->rotation_24.vy = ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

        if (g_SysWork.player_4C.chara_0.attackReceived_41 == -1)
        {
            g_SysWork.field_2284[3]                                     &= 0xFFFE;
            animStatus                                                   = chara->model_0.anim_4.status_0;
            chara->model_0.state_2                                       = 9;
            chara->model_0.anim_4.status_0                               = 0x14;
            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = animStatus;
            chara->field_E1_0                                            = 0;
            chara->field_E1_0                                            = 3;

            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x40;
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= 0xFFDF;
        }
        else
        {
            chara->properties_E4.player.runTimer_F8 += g_DeltaTime0;

            if (chara->properties_E4.player.runTimer_F8 > 0x1800)
            {
                g_SysWork.player_4C.chara_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[50].field_4, Q12_SHIFT) * (Rng_TestProbabilityBits(5) + 0x55)) / 100;
                chara->properties_E4.player.runTimer_F8         = Rng_Rand16() % 0x800;
            }
        }
    }
    else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x1D7 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x1DD)
    {
        vec0.vx = chara->position_18.vx;
        vec0.vy = chara->position_18.vy + chara->field_C8.field_8;
        vec0.vz = chara->position_18.vz;

        if (func_8008A0E4(1, 0x31, chara, &vec0, &g_SysWork.player_4C, chara->rotation_24.vy, FP_ANGLE(90.0f)) != -1)
        {
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x20;
            g_SysWork.field_2284[3]                                      &= 0xFFFD;
            sharedFunc_800D7E04_0_s00(chara, 0x556);
            chara->properties_E4.player.runTimer_F8 = 0x1000;
        }
    }
    else if (chara->model_0.anim_4.status_0 == 0x13 || chara->model_0.anim_4.status_0 == 0x11 || dist > 0x2000)
    {
        g_SysWork.field_2284[3] &= 0xFFFC;
        chara->model_0.state_2   = 9;

        if (chara->model_0.anim_4.status_0 == 0x45 || chara->model_0.anim_4.status_0 == 0x12)
        {
            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = 0x13;
        }
        else if (chara->model_0.anim_4.status_0 == 0x47 || chara->model_0.anim_4.status_0 == 0x10)
        {
            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = 0x11;
        }
        else
        {
            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = chara->model_0.anim_4.status_0;
        }

        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x40;
        chara->model_0.anim_4.status_0                                = 0x48;
        chara->field_E1_0                                             = 3;
    }

    if (g_DeltaTime0 != 0)
    {
        chara->properties_E4.larvalStalker.properties_E8[1].val16[0] = FP_MULTIPLY(var_s6, Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
        chara->properties_E4.larvalStalker.properties_E8[1].val16[1] = FP_MULTIPLY(var_s6, Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
    }
}
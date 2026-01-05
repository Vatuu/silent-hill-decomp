void sharedFunc_800E3E94_2_s00(s_SubCharacter* arg0)
{
    s16           temp_v0_10;
    s16           angle0;
    s16           angle1;
    s32           headingAngle;
    s32           temp_s2;
    s32           temp_s4;
    s32           mag0;
    bool          temp_s6;
    bool          var_a0;
    s32           var_a1;
    s32           i;
    s_PlayerWork* player;
    s32           temp;

    if (arg0->properties_E4.groaner.flags_E8.val16[0] & 2)
    {
        return;
    }

    if (arg0->properties_E4.groaner.flags_E8.val16[0] & 0x100)
    {
        arg0->properties_E4.groaner.field_104          = 0;
        arg0->properties_E4.groaner.flags_E8.val16[0] |= 0x100;
    }

    mag0 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);

    temp = Rng_GenerateInt(0x4000, 0x7FFF);

    temp_s6 = func_800700F8(arg0, &g_SysWork.playerWork_4C.player_0);

    if (mag0 < temp && !temp_s6)
    {
        arg0->properties_E4.groaner.angle_FC = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx -
                                                          arg0->position_18.vx,
                                                      g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);
    }
    else
    {
        temp_s2 = 0xE66 - Rng_GenerateInt(0, 920);
        temp_s4 = func_8007029C(arg0, temp_s2, arg0->rotation_24.vy);

        if ((arg0->properties_E4.groaner.field_104 >= 0 && ((temp_s4 != 0 && (temp_s6 || mag0 < temp_s2)) ||
                                                            arg0->properties_E4.groaner.field_104 == 0)) ||
            !Rng_TestProbabilityBits(5))
        {
            if (temp_s4 != 0)
            {
                var_a1 = temp_s2 + Rng_GenerateInt(0, (temp_s2 >> 2) - 1);
            }
            else
            {
                var_a1 = Rng_GenerateInt(0x1800, 0x1DFF);
            }

            headingAngle = Chara_HeadingAngleGet(arg0, var_a1, arg0->properties_E4.dummy.properties_E8[3].val32,
                                                 arg0->properties_E4.dummy.properties_E8[4].val32, 0x1000, true);
            if (headingAngle == 0x1000)
            {
                headingAngle = func_8006F99C(arg0, (temp_s2 * 3) >> 2, arg0->rotation_24.vy);
            }

            if (temp_s4 != 0)
            {
                arg0->properties_E4.groaner.field_104 = -(Rng_GenerateInt(0x600, 0xBFF));
            }
            else
            {
                arg0->properties_E4.groaner.field_104 = Rng_GenerateInt(0x600, 0x17FF);
            }

            arg0->properties_E4.groaner.angle_FC = headingAngle;
        }
    }

    if (arg0->properties_E4.groaner.field_104 > 0)
    {
        arg0->properties_E4.groaner.field_104 -= g_DeltaTime0;

        if (arg0->properties_E4.groaner.field_104 < 0)
        {
            arg0->properties_E4.groaner.field_104 = 0;
        }
    }
    else
    {
        arg0->properties_E4.groaner.field_104 += g_DeltaTime0;

        if (arg0->properties_E4.groaner.field_104 > 0)
        {
            arg0->properties_E4.groaner.field_104 = 0;
        }
    }

    for (i = 0; i < 3; i++)
    {
        angle0 = func_8005BF38(arg0->properties_E4.groaner.angle_FC - arg0->rotation_24.vy);

        if ((g_DeltaTime0 >> 3) + 1 < ABS(angle0))
        {
            if (angle0 > 0)
            {
                arg0->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x400, Q12_SHIFT);
            }
            else
            {
                arg0->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x400, Q12_SHIFT);
            }
        }
        else
        {
            arg0->rotation_24.vy = arg0->properties_E4.groaner.angle_FC;
        }
    }

    angle1 = func_8005BF38(arg0->properties_E4.groaner.angle_FC - arg0->rotation_24.vy);

    if (angle1 < 0xE3)
    {
        Chara_MoveSpeedUpdate5(arg0, 0x9800, FP_MULTIPLY_PRECISE(arg0->properties_E4.groaner.field_114, 0x3999, Q12_SHIFT));
    }
    else
    {
        temp_v0_10 = 0x1000 - (((angle1 - 0xE3) * 3) >> 1);
        Chara_MoveSpeedUpdate5(arg0, 0x9800, FP_MULTIPLY_PRECISE(FP_MULTIPLY_PRECISE(arg0->properties_E4.groaner.field_114, 0x3999, Q12_SHIFT), temp_v0_10, Q12_SHIFT));
    }

    if (mag0 > 0x3000)
    {
        var_a0 = false;
    }
    else if (mag0 < 0x1800)
    {
        var_a0 = true;
    }
    else
    {
        var_a0 = Rng_TestProbabilityBits(12) > (FP_TO(mag0, Q12_SHIFT) / 0x3000) >> 2;
    }

    if (var_a0 && !temp_s6)
    {
        player = &g_SysWork.playerWork_4C;

        if (!(player->player_0.flags_3E & 8) && !(g_SysWork.field_2284[3] & 2) &&
            g_SysWork.playerWork_4C.player_0.health_B0 > 0 && g_SysWork.sysState_8 == 0 &&
            arg0->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy >= -0xCCB)
        {
            if (arg0->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy < 0xCCC)
            {
                if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) -
                                      arg0->rotation_24.vy)) < 0x155)
                {
                    g_SysWork.field_2284[3]      |= 2;
                    arg0->model_0.controlState_2  = 3;
                    arg0->model_0.anim_4.status_0 = 0x1E;
                    return;
                }
            }
        }
    }

    if (mag0 < 0x1333)
    {
        player = &g_SysWork.playerWork_4C;
        if ((player->player_0.flags_3E & 8) || (g_SysWork.field_2284[3] & 2) || g_SysWork.playerWork_4C.player_0.health_B0 <= 0 ||
            g_SysWork.sysState_8 != 0 || !Rng_TestProbabilityBits(4))
        {
            arg0->model_0.controlState_2 = 4;
            return;
        }
    }

    if (!(arg0->properties_E4.dummy.properties_E8[0].val16[0] & 0x80) && (mag0 > 0xC000 || (!Rng_TestProbabilityBits(7) && (mag0 > 0x6000))))
    {
        arg0->model_0.controlState_2                         = 1;
        arg0->model_0.anim_4.status_0                        = 0x22;
        arg0->properties_E4.dummy.properties_E8[6].val16[0]  = 0x64;
        arg0->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFBFF;
    }
}
void sharedFunc_800E3E94_2_s00(s_SubCharacter* groaner)
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
    s32           temp;
    s_PlayerWork* playerWork;

    if (groaner->properties_E4.groaner.flags_E8.val16[0] & 2)
    {
        return;
    }

    if (groaner->properties_E4.groaner.flags_E8.val16[0] & 0x100)
    {
        groaner->properties_E4.groaner.field_104          = 0;
        groaner->properties_E4.groaner.flags_E8.val16[0] |= 0x100;
    }

    mag0 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);

    temp = Rng_GenerateInt(0x4000, 0x7FFF);

    temp_s6 = func_800700F8(groaner, &g_SysWork.playerWork_4C.player_0);

    if (mag0 < temp && !temp_s6)
    {
        groaner->properties_E4.groaner.angle_FC = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                                       g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);
    }
    else
    {
        temp_s2 = 0xE66 - Rng_GenerateInt(0, 920);
        temp_s4 = func_8007029C(groaner, temp_s2, groaner->rotation_24.vy);

        if ((groaner->properties_E4.groaner.field_104 >= 0 && ((temp_s4 != 0 && (temp_s6 || mag0 < temp_s2)) ||
                                                            groaner->properties_E4.groaner.field_104 == 0)) ||
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

            headingAngle = Chara_HeadingAngleGet(groaner, var_a1, groaner->properties_E4.dummy.properties_E8[3].val32,
                                                 groaner->properties_E4.dummy.properties_E8[4].val32, FP_ANGLE(360.0f), true);
            if (headingAngle == 0x1000)
            {
                headingAngle = func_8006F99C(groaner, (temp_s2 * 3) >> 2, groaner->rotation_24.vy);
            }

            if (temp_s4 != 0)
            {
                groaner->properties_E4.groaner.field_104 = -(Rng_GenerateInt(0x600, 0xBFF));
            }
            else
            {
                groaner->properties_E4.groaner.field_104 = Rng_GenerateInt(0x600, 0x17FF);
            }

            groaner->properties_E4.groaner.angle_FC = headingAngle;
        }
    }

    if (groaner->properties_E4.groaner.field_104 > 0)
    {
        groaner->properties_E4.groaner.field_104 -= g_DeltaTime0;

        if (groaner->properties_E4.groaner.field_104 < 0)
        {
            groaner->properties_E4.groaner.field_104 = 0;
        }
    }
    else
    {
        groaner->properties_E4.groaner.field_104 += g_DeltaTime0;

        if (groaner->properties_E4.groaner.field_104 > 0)
        {
            groaner->properties_E4.groaner.field_104 = 0;
        }
    }

    for (i = 0; i < 3; i++)
    {
        angle0 = func_8005BF38(groaner->properties_E4.groaner.angle_FC - groaner->rotation_24.vy);

        if ((g_DeltaTime0 >> 3) + 1 < ABS(angle0))
        {
            if (angle0 > FP_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x400);
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x400);
            }
        }
        else
        {
            groaner->rotation_24.vy = groaner->properties_E4.groaner.angle_FC;
        }
    }

    angle1 = func_8005BF38(groaner->properties_E4.groaner.angle_FC - groaner->rotation_24.vy);

    if (angle1 < 0xE3)
    {
        Chara_MoveSpeedUpdate4(groaner, 0x9800, Q12_MULT_PRECISE(groaner->properties_E4.groaner.field_114, 0x3999));
    }
    else
    {
        temp_v0_10 = 0x1000 - (((angle1 - 0xE3) * 3) >> 1);
        Chara_MoveSpeedUpdate4(groaner, 0x9800, Q12_MULT_PRECISE(Q12_MULT_PRECISE(groaner->properties_E4.groaner.field_114, 0x3999), temp_v0_10));
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
        playerWork = &g_SysWork.playerWork_4C;

        if (!(playerWork->player_0.flags_3E & 8) && !(g_SysWork.field_2284[3] & 2) &&
            g_SysWork.playerWork_4C.player_0.health_B0 > 0 && g_SysWork.sysState_8 == 0 &&
            groaner->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy >= -0xCCB)
        {
            if (groaner->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy < 0xCCC)
            {
                if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz) -
                                      groaner->rotation_24.vy)) < 0x155)
                {
                    g_SysWork.field_2284[3]      |= 2;
                    groaner->model_0.controlState_2  = 3;
                    groaner->model_0.anim_4.status_0 = 30;
                    return;
                }
            }
        }
    }

    if (mag0 < 0x1333)
    {
        playerWork = &g_SysWork.playerWork_4C;
        if ((playerWork->player_0.flags_3E & 8) || (g_SysWork.field_2284[3] & 2) ||
            g_SysWork.playerWork_4C.player_0.health_B0 <= 0 ||
            g_SysWork.sysState_8 != 0 || !Rng_TestProbabilityBits(4))
        {
            groaner->model_0.controlState_2 = 4;
            return;
        }
    }

    if (!(groaner->properties_E4.dummy.properties_E8[0].val16[0] & 0x80) &&
        (mag0 > 0xC000 || (!Rng_TestProbabilityBits(7) && (mag0 > 0x6000))))
    {
        groaner->model_0.controlState_2                         = 1;
        groaner->model_0.anim_4.status_0                        = 34;
        groaner->properties_E4.dummy.properties_E8[6].val16[0]  = 0x64;
        groaner->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFBFF;
    }
}

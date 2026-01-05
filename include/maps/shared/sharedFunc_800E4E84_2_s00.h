void sharedFunc_800E4E84_2_s00(s_SubCharacter* arg0)
{
    s32 temp_a3;
    s32 temp_s1;
    s32 temp_s4;
    s32 temp_v1_8;
    s32 var_s0_2;
    s32 i;

    if (arg0->properties_E4.groaner.flags_E8.val16[0] & 2)
    {
        return;
    }

    if (!(arg0->properties_E4.groaner.flags_E8.val16[0] & 0x100))
    {
        arg0->properties_E4.groaner.field_108          = 0;
        arg0->properties_E4.groaner.field_104          = 0;
        arg0->properties_E4.groaner.flags_E8.val16[0] |= 0x100;
    }

    temp_s4 = func_8007029C(arg0, 0xE66 - Rng_GenerateInt(0, 920), arg0->rotation_24.vy);

    if (arg0->properties_E4.groaner.field_104 == 0 || !Rng_TestProbabilityBits(5) ||
        (temp_s4 != 0 && arg0->properties_E4.groaner.field_104 >= 0))
    {
        temp_s1 = 0x1800 - Rng_GenerateInt(0, 1535);

        arg0->properties_E4.groaner.angle_FC = Chara_HeadingAngleGet(arg0, temp_s1, arg0->properties_E4.groaner.targetPositionX_F4,
                                                                     arg0->properties_E4.groaner.targetPositionZ_F8, 0x1000, false);

        if (arg0->properties_E4.groaner.angle_FC == 0x1000)
        {
            arg0->properties_E4.groaner.angle_FC = func_8006F99C(arg0, (temp_s1 * 3) >> 2, arg0->rotation_24.vy);
        }

        if (temp_s4 != 0)
        {
            arg0->properties_E4.groaner.field_104 = -(Rng_GenerateInt(0x600, 0xBFF));
        }
        else
        {
            arg0->properties_E4.groaner.field_104 = Rng_GenerateInt(0xC00, 0x17FF);
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

    for (i = 0; i < 2; i++)
    {
        temp_a3 = func_8005BF38((arg0->properties_E4.groaner.angle_FC - arg0->rotation_24.vy));

        if ((g_DeltaTime0 >> 3) + 1 < ABS(temp_a3))
        {
            if (temp_a3 > FP_ANGLE(0.0f))
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

    temp_a3 = func_8005BF38(arg0->properties_E4.groaner.angle_FC - arg0->rotation_24.vy);

    if (arg0->properties_E4.groaner.field_104 >= 0)
    {
        Chara_MoveSpeedUpdate5(arg0, 0x9800, FP_MULTIPLY_PRECISE(arg0->properties_E4.groaner.field_114, 0x3999, Q12_SHIFT));
    }
    else
    {
        temp_a3 = 0x1000 - (((temp_a3 - 0xE3) * 3) >> 1);
        Chara_MoveSpeedUpdate5(arg0, 0x9800, FP_MULTIPLY_PRECISE(temp_a3, FP_MULTIPLY_PRECISE(arg0->properties_E4.groaner.field_114, 0x3999, Q12_SHIFT), Q12_SHIFT));
    }

    var_s0_2                               = 0;
    arg0->properties_E4.groaner.field_108 += g_DeltaTime0;

    if (arg0->properties_E4.groaner.field_108 > 0x6000)
    {
        if (arg0->properties_E4.groaner.field_108 > 0x7800)
        {
            var_s0_2 = 0x800;
        }
        else
        {
            var_s0_2 = (FP_MULTIPLY_PRECISE(arg0->properties_E4.groaner.field_108 - 0x6000, 0x1800, Q12_SHIFT) >> 2) + 0x400;
        }
    }

    temp_v1_8 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx,
                                    g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);

    if (temp_v1_8 > 0x3800)
    {
        if (temp_v1_8 > 0x5400)
        {
            var_s0_2 += 0x800;
        }
        else
        {
            var_s0_2 += 0x400 + (FP_MULTIPLY_PRECISE(temp_v1_8 - 0x3800, 0x1C00, Q12_SHIFT) >> 2);
        }
    }

    if (Rng_TestProbabilityBits(12) < var_s0_2)
    {
        arg0->model_0.controlState_2 = 2;
    }
}
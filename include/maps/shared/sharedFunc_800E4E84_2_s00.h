void sharedFunc_800E4E84_2_s00(s_SubCharacter* groaner)
{
    s32 temp_a3;
    s32 temp_s1;
    s32 temp_s4;
    s32 temp_v1_8;
    s32 var_s0_2;
    s32 i;

    #define groanerProps groaner->properties_E4.groaner

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_1)
    {
        return;
    }

    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_8))
    {
        groanerProps.field_108          = 0;
        groanerProps.field_104          = 0;
        groanerProps.flags_E8.val16[0] |= GroanerFlag_8;
    }

    // TODO: Cleaner random angle generation.
    temp_s4 = func_8007029C(groaner, 0xE66 - Rng_GenerateInt(0, 920), groaner->rotation_24.vy);

    if (groanerProps.field_104 == 0 || !Rng_TestProbabilityBits(5) ||
        (temp_s4 != 0 && groanerProps.field_104 >= 0))
    {
        temp_s1 = 0x1800 - Rng_GenerateInt(0, 1535);

        groanerProps.angle_FC = Chara_HeadingAngleGet(groaner, temp_s1, groanerProps.targetPositionX_F4,
                                                                     groanerProps.targetPositionZ_F8, 0x1000, false);

        if (groanerProps.angle_FC == 0x1000)
        {
            groanerProps.angle_FC = func_8006F99C(groaner, (temp_s1 * 3) >> 2, groaner->rotation_24.vy);
        }

        if (temp_s4 != 0)
        {
            groanerProps.field_104 = -(Rng_GenerateInt(0x600, 0xBFF));
        }
        else
        {
            groanerProps.field_104 = Rng_GenerateInt(0xC00, 0x17FF);
        }
    }

    if (groanerProps.field_104 > 0)
    {
        groanerProps.field_104 -= g_DeltaTime0;
        if (groanerProps.field_104 < 0)
        {
            groanerProps.field_104 = 0;
        }
    }
    else
    {
        groanerProps.field_104 += g_DeltaTime0;
        if (groanerProps.field_104 > 0)
        {
            groanerProps.field_104 = 0;
        }
    }

    for (i = 0; i < 2; i++)
    {
        temp_a3 = func_8005BF38((groanerProps.angle_FC - groaner->rotation_24.vy));

        if ((g_DeltaTime0 >> 3) + 1 < ABS(temp_a3))
        {
            if (temp_a3 > FP_ANGLE(0.0f))
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
            groaner->rotation_24.vy = groanerProps.angle_FC;
        }
    }

    temp_a3 = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);

    if (groanerProps.field_104 >= 0)
    {
        Chara_MoveSpeedUpdate4(groaner, 0x9800, Q12_MULT_PRECISE(groanerProps.field_114, 0x3999));
    }
    else
    {
        temp_a3 = 0x1000 - (((temp_a3 - 0xE3) * 3) >> 1);
        Chara_MoveSpeedUpdate4(groaner, 0x9800, Q12_MULT_PRECISE(temp_a3, Q12_MULT_PRECISE(groanerProps.field_114, 0x3999)));
    }

    var_s0_2                               = 0;
    groanerProps.field_108 += g_DeltaTime0;

    if (groanerProps.field_108 > 0x6000)
    {
        if (groanerProps.field_108 > 0x7800)
        {
            var_s0_2 = 0x800;
        }
        else
        {
            var_s0_2 = (Q12_MULT_PRECISE(groanerProps.field_108 - 0x6000, 0x1800) >> 2) + 0x400;
        }
    }

    temp_v1_8 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                    g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);

    if (temp_v1_8 > 0x3800)
    {
        if (temp_v1_8 > 0x5400)
        {
            var_s0_2 += 0x800;
        }
        else
        {
            var_s0_2 += 0x400 + (Q12_MULT_PRECISE(temp_v1_8 - 0x3800, 0x1C00) >> 2);
        }
    }

    if (Rng_TestProbabilityBits(12) < var_s0_2)
    {
        groaner->model_0.controlState_2 = 2;
    }

    #undef groanerProps
}

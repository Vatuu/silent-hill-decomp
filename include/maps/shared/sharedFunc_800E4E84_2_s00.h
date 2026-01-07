void sharedFunc_800E4E84_2_s00(s_SubCharacter* groaner)
{
    s32    temp_a3;
    s32    temp_s1;
    s32    temp_s4;
    q19_12 distToPlayer;
    q19_12 var_s0_2;
    s32    i;

    #define groanerProps groaner->properties_E4.groaner

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_1)
    {
        return;
    }

    if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_8))
    {
        groanerProps.field_108          = 0;
        groanerProps.timer_104          = Q12(0.0f);
        groanerProps.flags_E8.val16[0] |= GroanerFlag_8;
    }

    // TODO: Cleaner random angle generation.
    temp_s4 = func_8007029C(groaner, Q12(0.9f) - Rng_GenerateInt(0, 920), groaner->rotation_24.vy);

    if (groanerProps.timer_104 == Q12(0.0f) || !Rng_TestProbabilityBits(5) ||
        (temp_s4 != 0 && groanerProps.timer_104 >= Q12(0.0f)))
    {
        temp_s1 = Q12(1.5f) - Rng_GenerateInt(0, 1535);
        groanerProps.angle_FC = Chara_HeadingAngleGet(groaner, temp_s1, groanerProps.targetPositionX_F4,
                                                                     groanerProps.targetPositionZ_F8, Q12(1.0f), false);
        if (groanerProps.angle_FC == FP_ANGLE(360.0f))
        {
            groanerProps.angle_FC = func_8006F99C(groaner, (temp_s1 * 3) >> 2, groaner->rotation_24.vy);
        }

        if (temp_s4 != 0)
        {
            groanerProps.timer_104 = -(Rng_GenerateInt(Q12(0.375), Q12(0.75f) - 1));
        }
        else
        {
            groanerProps.timer_104 = Rng_GenerateInt(Q12(0.75f), Q12(1.5f) - 1);
        }
    }

    if (groanerProps.timer_104 > Q12(0.0f))
    {
        groanerProps.timer_104 -= g_DeltaTime0;
        if (groanerProps.timer_104 < Q12(0.0f))
        {
            groanerProps.timer_104 = Q12(0.0f);
        }
    }
    else
    {
        groanerProps.timer_104 += g_DeltaTime0;
        if (groanerProps.timer_104 > Q12(0.0f))
        {
            groanerProps.timer_104 = Q12(0.0f);
        }
    }

    for (i = 0; i < 2; i++)
    {
        temp_a3 = func_8005BF38((groanerProps.angle_FC - groaner->rotation_24.vy));
        if ((g_DeltaTime0 >> 3) + 1 < ABS(temp_a3))
        {
            if (temp_a3 > FP_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f));
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f));
            }
        }
        else
        {
            groaner->rotation_24.vy = groanerProps.angle_FC;
        }
    }

    temp_a3 = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);

    if (groanerProps.timer_104 >= Q12(0.0f))
    {
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)));
    }
    else
    {
        temp_a3 = Q12(1.0f) - (((temp_a3 - 227) * 3) >> 1);
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(temp_a3, Q12_MULT_PRECISE(groanerProps.field_114, 0x3999)));
    }

    var_s0_2                               = 0;
    groanerProps.field_108 += g_DeltaTime0;

    if (groanerProps.field_108 > Q12(6.0f))
    {
        if (groanerProps.field_108 > Q12(7.5f))
        {
            var_s0_2 = Q12(0.5f);
        }
        else
        {
            var_s0_2 = (Q12_MULT_PRECISE(groanerProps.field_108 - Q12(6.0f), Q12(1.5f)) >> 2) + Q12(0.25f);
        }
    }

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);
    if (distToPlayer > Q12(3.5f))
    {
        if (distToPlayer > Q12(5.25f))
        {
            var_s0_2 += Q12(0.5f);
        }
        else
        {
            var_s0_2 += Q12(0.25f) + (Q12_MULT_PRECISE(distToPlayer - Q12(3.5f), Q12(1.75f)) >> 2);
        }
    }

    // TODO: Wrong RNG macro.
    if (Rng_TestProbabilityBits(12) < var_s0_2)
    {
        groaner->model_0.controlState_2 = 2;
    }

    #undef groanerProps
}

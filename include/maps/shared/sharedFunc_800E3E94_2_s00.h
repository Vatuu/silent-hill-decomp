void sharedFunc_800E3E94_2_s00(s_SubCharacter* groaner)
{
    s16           temp_v0_10;
    q3_12         angle0;
    q3_12         angle1;
    q19_12        headingAngle;
    s32           temp_s2;
    s32           temp_s4;
    q19_12        distToPlayer;
    bool          temp_s6;
    bool          cond;
    s32           var_a1;
    s32           i;
    q19_12        distToPlayerMax;
    s_PlayerWork* playerWork;

    #define groanerProps  groaner->properties_E4.groaner

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_1)
    {
        return;
    }

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_8)
    {
        groanerProps.timer_104          = Q12(0.0f);
        groanerProps.flags_E8.val16[0] |= GroanerFlag_8;
    }

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);
    distToPlayerMax = Rng_GenerateInt(Q12(4.0f), Q12(8.0f) - 1);
    temp_s6 = func_800700F8(groaner, &g_SysWork.playerWork_4C.player_0);

    if (distToPlayer < distToPlayerMax && !temp_s6)
    {
        groanerProps.angle_FC = Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18);
    }
    else
    {
        temp_s2 = Q12(0.9f) - Rng_GenerateInt(0, 920);
        temp_s4 = func_8007029C(groaner, temp_s2, groaner->rotation_24.vy);

        if ((groanerProps.timer_104 >= Q12(0.0f) && ((temp_s4 != 0 && (temp_s6 || distToPlayer < temp_s2)) ||
             groanerProps.timer_104 == Q12(0.0f))) ||
            !Rng_TestProbabilityBits(5))
        {
            if (temp_s4 != 0)
            {
                var_a1 = temp_s2 + Rng_GenerateInt(0, (temp_s2 >> 2) - 1);
            }
            else
            {
                var_a1 = Rng_GenerateInt(Q12(1.5f), Q12(1.875f) - 1);
            }

            headingAngle = Chara_HeadingAngleGet(groaner, var_a1, groanerProps.targetPositionX_F4, groanerProps.targetPositionZ_F8,
                                                 FP_ANGLE(360.0f), true);
            if (headingAngle == FP_ANGLE(360.0f))
            {
                headingAngle = func_8006F99C(groaner, (temp_s2 * 3) >> 2, groaner->rotation_24.vy);
            }

            if (temp_s4 != 0)
            {
                groanerProps.timer_104 = -(Rng_GenerateInt(Q12(0.375f), Q12(0.75f) - 1));
            }
            else
            {
                groanerProps.timer_104 = Rng_GenerateInt(Q12(0.375f), Q12(1.5f) - 1);
            }

            groanerProps.angle_FC = headingAngle;
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

    for (i = 0; i < 3; i++)
    {
        angle0 = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);

        if (((g_DeltaTime0 >> 3) + 1) < ABS(angle0))
        {
            if (angle0 > FP_ANGLE(0.0f))
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

    angle1 = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);

    if (angle1 < 0xE3)
    {
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)));
    }
    else
    {
        temp_v0_10 = Q12(1.0f) - (((angle1 - 0xE3) * 3) >> 1);
        Chara_MoveSpeedUpdate4(groaner, Q12(9.5f), Q12_MULT_PRECISE(Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f)), temp_v0_10));
    }

    if (distToPlayer > Q12(3.0f))
    {
        cond = false;
    }
    else if (distToPlayer < Q12(1.5f))
    {
        cond = true;
    }
    else
    {
        cond = Rng_TestProbabilityBits(12) > (FP_TO(distToPlayer, Q12_SHIFT) / Q12(3.0f)) >> 2;
    }

    if (cond && !temp_s6)
    {
        playerWork = &g_SysWork.playerWork_4C;

        if (!(playerWork->player_0.flags_3E & CharaFlag_Unk4) &&
            !(g_SysWork.field_2284[3] & 2) &&
            g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f) &&
            g_SysWork.sysState_8 == 0 &&
            (groaner->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy) > Q12(-0.8f))
        {
            if (groaner->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy < Q12(0.8f))
            {
                if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz) -
                                      groaner->rotation_24.vy)) < FP_ANGLE(30.0f))
                {
                    g_SysWork.field_2284[3]      |= 2;
                    groaner->model_0.controlState_2  = GroanerControl_3;
                    groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_15, false);
                    return;
                }
            }
        }
    }

    if (distToPlayer < Q12(1.2f))
    {
        playerWork = &g_SysWork.playerWork_4C;
        if ((playerWork->player_0.flags_3E & CharaFlag_Unk4) ||
            (g_SysWork.field_2284[3] & 2) ||
            g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f) ||
            g_SysWork.sysState_8 != 0 ||
            !Rng_TestProbabilityBits(4))
        {
            groaner->model_0.controlState_2 = GroanerControl_4;
            return;
        }
    }

    if (!(groanerProps.flags_E8.val16[0] & 0x80) &&
        (distToPlayer > Q12(12.0f) || (!Rng_TestProbabilityBits(7) && distToPlayer > Q12(6.0f))))
    {
        groaner->model_0.controlState_2                         = GroanerControl_1;
        groaner->model_0.anim_4.status_0                        = ANIM_STATUS(GroanerAnim_17, false);
        groanerProps.relKeyframeIdx_100  = 100;
        groanerProps.flags_E8.val16[0] &= ~GroanerFlag_10;
    }

    #undef groanerProps
}

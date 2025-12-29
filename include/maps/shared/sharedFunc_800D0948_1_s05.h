void sharedFunc_800D0948_1_s05(s_SubCharacter* chara)
{
    s_func_800700F8_2 sp10;
    VECTOR3           sp30;
    q3_12             angleToPlayer2;
    q3_12             angleDeltaToPlayer;
    q3_12             angle1;
    q3_12             angle;
    q3_12             angleToPlayer;
    q19_12            distToPlayer;
    s32               var_s1;
    s32               i;
    s32               angleMult;
    s32               var_v1;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    if ((u16)chara->properties_E4.dummy.properties_E8[2].val16[1] > Q12(0.6f))
    {
        angle = FP_ANGLE(0.0f);
        angleToPlayer = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);

        if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 2))
        {
            angleMult                                               = 1;
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 2);
        }
        else
        {
            angleMult                                               = NO_VALUE;
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 2;
        }

        for (i = 0; i < 16; i++)
        {
            if (i != 0 && i != 15)
            {
                angleToPlayer2 = Rng_TestProbabilityBits(7) - 64;
                if (i & 0x1)
                {
                    angle1 = angleToPlayer2 * angleMult;
                }
                else
                {
                    angle1 = angleToPlayer2 * -angleMult;
                }
            }
            else
            {
                angle1 = FP_ANGLE(0.0f);
            }

            if (angle < FP_ANGLE(90.0f))
            {
                var_s1 = Q12(1.8f);
            }
            else
            {
                var_s1 = FP_FROM((distToPlayer * Math_Cos(angle)) + (Math_Sin(angle) * Q12(1.8f)), Q12_SHIFT);
            }

            if (distToPlayer < var_s1)
            {
                var_v1 = var_s1;
            }
            else
            {
                var_v1 = distToPlayer;
            }
            var_s1 = var_v1;

            sp30.vx = FP_MULTIPLY(var_s1, Math_Sin((angleToPlayer + angle) + angle1), Q12_SHIFT);
            sp30.vy = Q12(0.0f);
            sp30.vz = FP_MULTIPLY(var_s1, Math_Cos((angleToPlayer + angle) + angle1), Q12_SHIFT);

            func_8006DB3C(&sp10, &chara->position_18, &sp30, chara);

            if (sp10.field_0 == 0 || sp10.field_10 != 0)
            {
                chara->properties_E4.dummy.properties_E8[2].val16[0] = angle1 + (angleToPlayer + angle);
                break;
            }

            if (!(i & 1))
            {
                angle += FP_ANGLE(22.5f);
            }
        }

        if (i != 16)
        {
            chara->properties_E4.dummy.properties_E8[2].val16[1] = 0;
        }
    }

    chara->properties_E4.dummy.properties_E8[2].val16[1] += g_DeltaTime0;

    angleToPlayer = func_8005BF38((chara->properties_E4.dummy.properties_E8[2].val16[0] - chara->rotation_24.vy));
    if (TIMESTEP_ANGLE_2 < ABS(angleToPlayer))
    {
        if (angleToPlayer > FP_ANGLE(0.0f))
        {
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
        }
        else
        {
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
        }
    }
    else
    {
        chara->rotation_24.vy = chara->properties_E4.dummy.properties_E8[2].val16[0];
    }

    angleToPlayer      = ABS(func_8005BF38(chara->properties_E4.dummy.properties_E8[2].val16[0] - chara->rotation_24.vy));
    angleDeltaToPlayer = ABS(func_8005BF38(Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                           chara->rotation_24.vy));

    if (ABS(angleToPlayer - angleDeltaToPlayer) < FP_ANGLE(15.0f))
    {
        if (distToPlayer <= Q12(5.75f) && angleToPlayer < FP_ANGLE(60.0f))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(0.8f), -Q12(1.2f));
        }
        else if ((distToPlayer <= Q12(5.75f) && angleToPlayer > FP_ANGLE(60.0f)) ||
                 (distToPlayer >  Q12(5.75f) && angleToPlayer > FP_ANGLE(90.0f)))
        {
            Chara_MoveSpeedUpdate(chara, Q12(0.8f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(chara, Q12(0.8f), Q12(1.2f));
        }
    }
    else
    {
        if (angleToPlayer < FP_ANGLE(30.0f))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(0.8f), Q12(1.2f));
        }
        else
        {
            Chara_MoveSpeedUpdate(chara, Q12(0.8f));
        }
    }

    angleToPlayer2 = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);
    sp30.vx = FP_MULTIPLY(distToPlayer, Math_Sin(angleToPlayer2), Q12_SHIFT);
    sp30.vy = Q12(0.0f);
    sp30.vz = FP_MULTIPLY(distToPlayer, Math_Cos(angleToPlayer2), Q12_SHIFT);

    func_8006DB3C(&sp10, &chara->position_18, &sp30, chara);

    if (distToPlayer < Q12(6.4f) &&
        (angleDeltaToPlayer < FP_ANGLE(7.5f) || distToPlayer > Q12(3.2f) && angleDeltaToPlayer < FP_ANGLE(15.0f)) &&
        (sp10.field_0 == 0 || sp10.field_10 != 0))
    {
        chara->model_0.controlState_2 = 3;
    }

    if (!Rng_TestProbabilityBits(7))
    {
        chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 8;
    }

    if (!Rng_TestProbabilityBits(6))
    {
        chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 7;
    }
}
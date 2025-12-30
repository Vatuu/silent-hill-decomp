void sharedFunc_800D19B8_1_s05(s_SubCharacter* chara)
{
    s_func_800700F8_2 sp10;
    VECTOR3           sp30;
    q3_12             angle1;
    q3_12             angle2;
    q3_12             angle3;
    q3_12             angle;
    q3_12             angleToPlayer;
    q19_12            distToPlayer;
    s32               distMax;
    s32               i;
    s32               angleMult;
    q19_12            activeDistMax;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    if ((u16)chara->properties_E4.dummy.properties_E8[2].val16[1] > 0x666)
    {
        angle = FP_ANGLE(0.0f);
        angleToPlayer = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);

        if (chara->properties_E4.dummy.properties_E8[0].val16[0] & 4)
        {
            angleMult                                               = 1;
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 2);
        }
        else
        {
            angleMult                                               = NO_VALUE;
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 4;
        }

        for (i = 0; i < 16; i++)
        {
            if (i != 0 && i != 0xF)
            {
                angle1 = Rng_TestProbabilityBits(7) - FP_ANGLE(5.625f);
                if (i & 0x1)
                {
                    angle3 = angle1 * angleMult;
                }
                else
                {
                    angle3 = angle1 * -angleMult;
                }
            }
            else
            {
                angle3 = 0;
            }

            if (angle < FP_ANGLE(90.0f))
            {
                distMax = Q12(2.0f);
            }
            else
            {
                distMax = FP_FROM((distToPlayer * Math_Cos(angle)) + (Math_Sin(angle) << 13), Q12_SHIFT);
            }

            if (distToPlayer < distMax)
            {
                activeDistMax = distMax;
            }
            else
            {
                activeDistMax = distToPlayer;
            }
            distMax = activeDistMax;

            sp30.vx = FP_MULTIPLY(distMax, Math_Sin((angleToPlayer + angle) + angle3), Q12_SHIFT);
            sp30.vy = Q12(0.0f);
            sp30.vz = FP_MULTIPLY(distMax, Math_Cos((angleToPlayer + angle) + angle3), Q12_SHIFT);

            func_8006DB3C(&sp10, &chara->position_18, &sp30, chara);

            if (sp10.field_0 == 0 || sp10.field_10 != 0)
            {
                chara->properties_E4.dummy.properties_E8[2].val16[0] = angle3 + (angleToPlayer + angle);
                break;
            }

            if (!(i & 0x1))
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

    if (TIMESTEP_ANGLE_0 < ABS(angleToPlayer))
    {
        if (angleToPlayer > FP_ANGLE(0.0f))
        {
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
        }
        else
        {
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
        }
    }
    else
    {
        chara->rotation_24.vy = chara->properties_E4.dummy.properties_E8[2].val16[0];
    }

    angleToPlayer   = ABS(func_8005BF38(chara->properties_E4.dummy.properties_E8[2].val16[0] - chara->rotation_24.vy));
    angle2 = ABS(func_8005BF38(Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18) - chara->rotation_24.vy));

    if (ABS(angleToPlayer - angle2) < FP_ANGLE(15.0f))
    {
        if (distToPlayer <= Q12(4.8f) && angle2 > FP_ANGLE(3.75f) && angleToPlayer < FP_ANGLE(60.0f))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(2.4f), Q12(-2.4f));
        }
        else if ((distToPlayer <= Q12(4.8f) && angleToPlayer > FP_ANGLE(60.0f)) ||
                 (distToPlayer >  Q12(4.8f) && angleToPlayer > FP_ANGLE(90.0f)))
        {
            Chara_MoveSpeedUpdate(chara, Q12(2.4f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(chara, Q12(2.4f), Q12(2.4f));
        }
    }
    else
    {
        if (angleToPlayer < FP_ANGLE(30.0f))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(2.4f), Q12(2.4f));
        }
        else
        {
            Chara_MoveSpeedUpdate(chara, Q12(2.4f));
        }
    }

    angle1 = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);

    sp30.vx = FP_MULTIPLY(distToPlayer, Math_Sin(angle1), Q12_SHIFT);
    sp30.vy = Q12(0.0f);
    sp30.vz = FP_MULTIPLY(distToPlayer, Math_Cos(angle1), Q12_SHIFT);

    func_8006DB3C(&sp10, &chara->position_18, &sp30, chara);

    if (distToPlayer > Q12(2.85f) && distToPlayer < Q12(4.0f) &&
        angle2 < FP_ANGLE(15.0f) &&
        (sp10.field_0 == 0 || sp10.field_10 != 0))
    {
        chara->model_0.controlState_2 = 1;
        if (!Rng_TestProbabilityBits(3))
        {
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 8;
        }
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

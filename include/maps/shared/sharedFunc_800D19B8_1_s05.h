void sharedFunc_800D19B8_1_s05(s_SubCharacter* chara)
{
    s_func_800700F8_2 sp10;
    VECTOR3           sp30;
    q3_12             angle1;
    s16               var_s1_2;
    s16               var_s3;
    q3_12             angle;
    q3_12             angleToPlayer;
    q19_12            distToPlayer;
    s32               distMax;
    s32               i;
    s32               var_s7;
    s32               var_v1;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    if ((u16)chara->properties_E4.dummy.properties_E8[2].val16[1] > 0x666)
    {
        angle = 0;
        angleToPlayer = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);

        if (chara->properties_E4.dummy.properties_E8[0].val16[0] & 4)
        {
            var_s7                                               = 1;
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 2);
        }
        else
        {
            var_s7                                               = NO_VALUE;
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 4;
        }

        for (i = 0; i < 16; i++)
        {
            if (i != 0 && i != 0xF)
            {
                angle1 = Rng_TestProbabilityBits(7) - 0x40;
                if (i & 1)
                {
                    var_s3 = angle1 * var_s7;
                }
                else
                {
                    var_s3 = angle1 * -var_s7;
                }
            }
            else
            {
                var_s3 = 0;
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
                var_v1 = distMax;
            }
            else
            {
                var_v1 = distToPlayer;
            }
            distMax = var_v1;

            sp30.vx = FP_MULTIPLY(distMax, Math_Sin((angleToPlayer + angle) + var_s3), Q12_SHIFT);
            sp30.vy = Q12(0.0f);
            sp30.vz = FP_MULTIPLY(distMax, Math_Cos((angleToPlayer + angle) + var_s3), Q12_SHIFT);

            func_8006DB3C(&sp10, &chara->position_18, &sp30, chara);

            if (sp10.field_0 == 0 || sp10.field_10 != 0)
            {
                chara->properties_E4.dummy.properties_E8[2].val16[0] = var_s3 + (angleToPlayer + angle);
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
    var_s1_2 = ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) - chara->rotation_24.vy));

    if (ABS(angleToPlayer - var_s1_2) < 0xAA)
    {
        if (distToPlayer <= Q12(4.8f) && var_s1_2 > 42 && angleToPlayer < 0x2AA)
        {
            Chara_MoveSpeedUpdate3(chara, Q12(2.4f), Q12(-2.4f));
        }
        else if ((distToPlayer < 0x4CCD && angleToPlayer > 0x2AA) ||
                 (distToPlayer > Q12(4.8f) && angleToPlayer > 0x400))
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
        if (angleToPlayer < 0x155)
        {
            Chara_MoveSpeedUpdate3(chara, Q12(2.4f), Q12(2.4f));
        }
        else
        {
            Chara_MoveSpeedUpdate(chara, Q12(2.4f));
        }
    }

    angle1 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    sp30.vx = FP_MULTIPLY(distToPlayer, Math_Sin(angle1), Q12_SHIFT);
    sp30.vy = Q12(0.0f);
    sp30.vz = FP_MULTIPLY(distToPlayer, Math_Cos(angle1), Q12_SHIFT);

    func_8006DB3C(&sp10, &chara->position_18, &sp30, chara);

    if (distToPlayer > Q12(2.85f) && distToPlayer < Q12(4.0f) &&
        var_s1_2 < 0xAA &&
        (sp10.field_0 == 0 || sp10.field_10 != 0))
    {
        chara->model_0.controlState_2 = 1;
        if (!Rng_TestProbabilityBits(3))
        {
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 0x100;
        }
    }

    if (!Rng_TestProbabilityBits(7))
    {
        chara->properties_E4.dummy.properties_E8[0].val16[0] |= 0x100;
    }

    if (!Rng_TestProbabilityBits(6))
    {
        chara->properties_E4.dummy.properties_E8[0].val16[0] |= 0x80;
    }
}

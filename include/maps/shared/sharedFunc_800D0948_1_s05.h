void sharedFunc_800D0948_1_s05(s_SubCharacter* chara)
{
    s_func_800700F8_2 sp10;
    VECTOR3           sp30;
    s16               temp_v0_6;
    s16               var_s1_2;
    s16               var_s3;
    s16               var_s5;
    q3_12             angleToPlayer;
    s32               distToPlayer;
    s32               var_s1;
    s32               i;
    s32               var_s7;
    s32               var_v1;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    if ((u16)chara->properties_E4.dummy.properties_E8[2].val16[1] >= 0x99A)
    {
        var_s5 = 0;
        angleToPlayer = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

        if (chara->properties_E4.dummy.properties_E8[0].val16[0] & 4)
        {
            var_s7                                               = 1;
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFFFB;
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
                temp_v0_6 = Rng_TestProbabilityBits(7) - 0x40;
                if (i & 1)
                {
                    var_s3 = temp_v0_6 * var_s7;
                }
                else
                {
                    var_s3 = temp_v0_6 * -var_s7;
                }
            }
            else
            {
                var_s3 = 0;
            }

            if (var_s5 < 0x400)
            {
                var_s1 = 0x1CCC;
            }
            else
            {
                var_s1 = FP_FROM(distToPlayer * Math_Cos(var_s5) + Math_Sin(var_s5) * 0x1CCC, Q12_SHIFT);
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

            sp30.vx = FP_MULTIPLY(var_s1, Math_Sin(angleToPlayer + var_s5 + var_s3), Q12_SHIFT);
            sp30.vy = 0;
            sp30.vz = FP_MULTIPLY(var_s1, Math_Cos(angleToPlayer + var_s5 + var_s3), Q12_SHIFT);

            func_8006DB3C(&sp10, &chara->position_18, &sp30, chara);

            if (sp10.field_0 == 0 || sp10.field_10 != 0)
            {
                chara->properties_E4.dummy.properties_E8[2].val16[0] = var_s3 + (angleToPlayer + var_s5);
                break;
            }

            if (!(i & 1))
            {
                var_s5 += 0x100;
            }
        }

        if (i != 16)
        {
            chara->properties_E4.dummy.properties_E8[2].val16[1] = 0;
        }
    }

    chara->properties_E4.dummy.properties_E8[2].val16[1] += g_DeltaTime0;

    angleToPlayer = func_8005BF38((chara->properties_E4.dummy.properties_E8[2].val16[0] - chara->rotation_24.vy));

    if (((g_DeltaTime0 / 3) >> 3) + 1 < ABS(angleToPlayer))
    {
        if (angleToPlayer > 0)
        {
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x155, Q12_SHIFT);
        }
        else
        {
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x155, Q12_SHIFT);
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
        if (distToPlayer < 0x5C01 && angleToPlayer < 0x2AA)
        {
            Chara_MoveSpeedUpdate3(chara, 0xCCC, -0x1333);
        }
        else if ((distToPlayer < 0x5C01 && angleToPlayer > 0x2AA) || (distToPlayer > 0x5C00 && angleToPlayer > 0x400))
        {
            Chara_MoveSpeedUpdate(chara, 0xCCC);
        }
        else
        {
            Chara_MoveSpeedUpdate3(chara, 0xCCC, 0x1333);
        }
    }
    else
    {
        if (angleToPlayer < 0x155)
        {
            Chara_MoveSpeedUpdate3(chara, 0xCCC, 0x1333);
        }
        else
        {
            Chara_MoveSpeedUpdate(chara, 0xCCC);
        }
    }

    temp_v0_6 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    sp30.vx = FP_MULTIPLY(distToPlayer, Math_Sin(temp_v0_6), Q12_SHIFT);
    sp30.vy = 0;
    sp30.vz = FP_MULTIPLY(distToPlayer, Math_Cos(temp_v0_6), Q12_SHIFT);

    func_8006DB3C(&sp10, &chara->position_18, &sp30, chara);

    if (distToPlayer < 0x6666 && (var_s1_2 < 0x55 || distToPlayer > 0x3333 && var_s1_2 < 0xAA) && (sp10.field_0 == 0 || sp10.field_10 != 0))
    {
        chara->model_0.state_2 = 3;
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
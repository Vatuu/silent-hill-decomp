void sharedFunc_800D0948_1_s05(s_SubCharacter* arg0)
{
    s_func_800700F8_2 sp10;
    VECTOR3           sp30;
    s16               temp_v0_6;
    s16               var_s1_2;
    s16               var_s3;
    s16               var_s5;
    s16               var_s6;
    s32               temp_fp;
    s32               var_s1;
    s32               i;
    s32               var_s7;
    s32               var_v1;

    temp_fp = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx) >> 6) +
                          SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) >> 6))
              << 6;

    if ((u16)arg0->properties_E4.dummy.properties_E8[2].val16[1] >= 0x99A)
    {
        var_s5 = 0;
        var_s6 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);

        if (arg0->properties_E4.dummy.properties_E8[0].val16[0] & 4)
        {
            var_s7                                               = 1;
            arg0->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFFFB;
        }
        else
        {
            var_s7                                               = -1;
            arg0->properties_E4.dummy.properties_E8[0].val16[0] |= 4;
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
                var_s1 = FP_FROM(temp_fp * Math_Cos(var_s5) + Math_Sin(var_s5) * 0x1CCC, Q12_SHIFT);
            }

            if (temp_fp < var_s1)
            {
                var_v1 = var_s1;
            }
            else
            {
                var_v1 = temp_fp;
            }
            var_s1 = var_v1;

            sp30.vx = FP_MULTIPLY(var_s1, Math_Sin(var_s6 + var_s5 + var_s3), Q12_SHIFT);
            sp30.vy = 0;
            sp30.vz = FP_MULTIPLY(var_s1, Math_Cos(var_s6 + var_s5 + var_s3), Q12_SHIFT);

            func_8006DB3C(&sp10, &arg0->position_18, &sp30, arg0);

            if (sp10.field_0 == 0 || sp10.field_10 != 0)
            {
                arg0->properties_E4.dummy.properties_E8[2].val16[0] = var_s3 + (var_s6 + var_s5);
                break;
            }

            if (!(i & 1))
            {
                var_s5 += 0x100;
            }
        }

        if (i != 16)
        {
            arg0->properties_E4.dummy.properties_E8[2].val16[1] = 0;
        }
    }

    arg0->properties_E4.dummy.properties_E8[2].val16[1] += g_DeltaTime0;

    var_s6 = func_8005BF38((arg0->properties_E4.dummy.properties_E8[2].val16[0] - arg0->rotation_24.vy));

    if (((g_DeltaTime0 / 3) >> 3) + 1 < ABS(var_s6))
    {
        if (var_s6 > 0)
        {
            arg0->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x155, Q12_SHIFT);
        }
        else
        {
            arg0->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x155, Q12_SHIFT);
        }
    }
    else
    {
        arg0->rotation_24.vy = arg0->properties_E4.dummy.properties_E8[2].val16[0];
    }

    var_s6   = ABS(func_8005BF38(arg0->properties_E4.dummy.properties_E8[2].val16[0] - arg0->rotation_24.vy));
    var_s1_2 = ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) - arg0->rotation_24.vy));

    if (ABS(var_s6 - var_s1_2) < 0xAA)
    {
        if (temp_fp < 0x5C01 && var_s6 < 0x2AA)
        {
            Chara_MoveSpeedUpdate3(arg0, 0xCCC, -0x1333);
        }
        else if ((temp_fp < 0x5C01 && var_s6 > 0x2AA) || (temp_fp > 0x5C00 && var_s6 > 0x400))
        {
            Chara_MoveSpeedUpdate(arg0, 0xCCC);
        }
        else
        {
            Chara_MoveSpeedUpdate3(arg0, 0xCCC, 0x1333);
        }
    }
    else
    {
        if (var_s6 < 0x155)
        {
            Chara_MoveSpeedUpdate3(arg0, 0xCCC, 0x1333);
        }
        else
        {
            Chara_MoveSpeedUpdate(arg0, 0xCCC);
        }
    }

    temp_v0_6 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);

    sp30.vx = FP_MULTIPLY(temp_fp, Math_Sin(temp_v0_6), Q12_SHIFT);
    sp30.vy = 0;
    sp30.vz = FP_MULTIPLY(temp_fp, Math_Cos(temp_v0_6), Q12_SHIFT);

    func_8006DB3C(&sp10, &arg0->position_18, &sp30, arg0);

    if (temp_fp < 0x6666 && (var_s1_2 < 0x55 || temp_fp > 0x3333 && var_s1_2 < 0xAA) && (sp10.field_0 == 0 || sp10.field_10 != 0))
    {
        arg0->model_0.state_2 = 3;
    }

    if (!Rng_TestProbabilityBits(7))
    {
        arg0->properties_E4.dummy.properties_E8[0].val16[0] |= 0x100;
    }

    if (!Rng_TestProbabilityBits(6))
    {
        arg0->properties_E4.dummy.properties_E8[0].val16[0] |= 0x80;
    }
}
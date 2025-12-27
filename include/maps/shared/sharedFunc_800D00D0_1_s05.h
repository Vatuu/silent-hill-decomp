void sharedFunc_800D00D0_1_s05(s_SubCharacter* arg0)
{
    VECTOR sp10;
    s16    temp_s2;
    s32    temp_s0;

    temp_s0 = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx) >> 6) +
                          SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) >> 6))
              << 6;
    temp_s2 = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx -
                                        arg0->position_18.vx,
                                    g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) -
                             arg0->rotation_24.vy));

    if (arg0->model_0.anim_4.status_0 == 0x17)
    {
        if (temp_s0 > 0x3800)
        {
            Chara_MoveSpeedUpdate3(arg0, 0x2666, 0x2666);
        }
        else
        {
            if (ABS(temp_s2) > 0x400 || temp_s0 > 0x5000)
            {
                arg0->model_0.state_2 = 5;
            }
            else
            {
                arg0->properties_E4.dummy.properties_E8[0].val16[0] |= 8;

                Chara_MoveSpeedUpdate(arg0, 0x4CCC);

                if (sharedFunc_800D4530_1_s05(arg0) != false)
                {
                    arg0->model_0.anim_4.status_0 = 4;
                    func_8005DC1C(0x5C3, &arg0->position_18, 0x80, 0);
                }
            }
        }

        if ((g_DeltaTime0 >> 4) + 1 < ABS(temp_s2))
        {
            if (temp_s2 > 0)
            {
                arg0->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT);
            }
            else
            {
                arg0->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT);
            }
        }
        else
        {
            arg0->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);
        }
    }
    else if (arg0->model_0.anim_4.status_0 >> 1 == 4)
    {
        Chara_MoveSpeedUpdate(arg0, 0x4CCC);
    }
    else if (arg0->model_0.anim_4.status_0 >> 1 == 0xA)
    {
        Chara_MoveSpeedUpdate(arg0, 0x4CCC);

        if (arg0->properties_E4.dummy.properties_E8[0].val16[0] & 0x40)
        {
            arg0->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFFBF;
            if (!(Rng_Rand16() & 3))
            {
                arg0->model_0.state_2         = 7;
                arg0->model_0.anim_4.status_0 = 0x12;
            }
            else
            {
                arg0->model_0.anim_4.status_0 = 8;
            }
        }
        else if ((arg0->model_0.anim_4.status_0 == 0x15) && !Rng_TestProbabilityBits(5))
        {
            arg0->model_0.anim_4.status_0 = 0x16;
            arg0->model_0.state_2         = 5;
        }
    }
    else if (arg0->properties_E4.dummy.properties_E8[0].val16[0] & 2)
    {
        if (arg0->model_0.anim_4.status_0 == 5)
        {
            arg0->model_0.anim_4.status_0 = 0x1C;
        }
        Chara_MoveSpeedUpdate3(arg0, 0x1333, 0);

        if (((g_DeltaTime0 / 3) >> 4) + 1 < ABS(temp_s2))
        {
            if (temp_s2 > 0)
            {
                arg0->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xAA, Q12_SHIFT);
            }
            else
            {
                arg0->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xAA, Q12_SHIFT);
            }
        }
        else
        {
            arg0->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);
        }

        if (FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) == 0x23)
        {
            sp10.vx = (g_SysWork.playerWork_4C.player_0.position_18.vx + Rng_TestProbabilityBits(10)) - 0x400;
            sp10.vy = (g_SysWork.playerWork_4C.player_0.position_18.vy - Rng_TestProbabilityBits(11)) - 0x1000;
            sp10.vz = (g_SysWork.playerWork_4C.player_0.position_18.vz + Rng_TestProbabilityBits(10)) - 0x400;
            func_8005F6B0(&g_SysWork.playerWork_4C.player_0, &sp10, 2, 7);
        }
    }
    else
    {
        if (temp_s0 < 0x2CCC)
        {
            Chara_MoveSpeedUpdate(arg0, 0x1333);
        }
        else
        {
            Chara_MoveSpeedUpdate3(arg0, 0x1333, 0x999);
        }

        if (((g_DeltaTime0 / 3) >> 4) + 1 < ABS(temp_s2))
        {
            if (temp_s2 > 0)
            {
                arg0->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xAA, Q12_SHIFT);
            }
            else
            {
                arg0->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xAA, Q12_SHIFT);
            }
        }
        else
        {
            arg0->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);
        }
    }
}
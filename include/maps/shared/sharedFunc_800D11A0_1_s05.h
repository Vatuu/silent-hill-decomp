void sharedFunc_800D11A0_1_s05(s_SubCharacter* arg0)
{
    s16 temp_s2;
    s32 temp_s0;

    temp_s0 = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx) >> 6) +
                          SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) >> 6))
              << 6;

    temp_s2 = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) - arg0->rotation_24.vy));

    if (arg0->model_0.anim_4.status_0 == 0x17)
    {
        if (temp_s0 > 0x4000)
        {
            Chara_MoveSpeedUpdate3(arg0, 0x4000, 0x2666);
        }
        else
        {
            if (ABS(temp_s2) > 0x400 || temp_s0 > 0x8000 || temp_s0 < 0x3333 && ABS(temp_s2) > 0x100)
            {
                arg0->model_0.state_2 = 2;
            }
            else
            {
                arg0->properties_E4.dummy.properties_E8[0].val16[0] |= 8;

                Chara_MoveSpeedUpdate(arg0, 0x10000);

                if (sharedFunc_800D4530_1_s05(arg0))
                {
                    arg0->model_0.anim_4.status_0 = 6;
                    func_8005DC1C(0x5BF, &arg0->position_18, 0x80, 0);
                }
            }
        }

        if (((g_DeltaTime0 / 3) >> 3) + 1 < ABS(temp_s2))
        {
            if (temp_s2 > 0)
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
            arg0->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz);
        }
    }
    else if ((arg0->model_0.anim_4.status_0 >> 1) == 0xA)
    {
        Chara_MoveSpeedUpdate(arg0, 0x1998);

        sharedData_800D5A8C_1_s05 += g_DeltaTime0;

        if (arg0->model_0.anim_4.status_0 == 0x15 && (!Rng_TestProbabilityBits(6) || sharedData_800D5A8C_1_s05 > 0x4000))
        {
            sharedData_800D5A8C_1_s05     = 0;
            arg0->model_0.anim_4.status_0 = 0x16;
            arg0->model_0.state_2         = 2;
        }
    }
    else
    {
        if (temp_s0 < 0x6666)
        {
            Chara_MoveSpeedUpdate(arg0, 0x4000);
        }
        else
        {
            Chara_MoveSpeedUpdate3(arg0, 0x4000, 0x2666);
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
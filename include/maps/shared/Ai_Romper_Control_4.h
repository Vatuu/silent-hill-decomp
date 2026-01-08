void Ai_Romper_Control_4(s_SubCharacter* romper)
{
    s32 temp_v0_5;
    s32 temp_s0;
    s32 temp_v1;
    s32 var_s0;
    s32 i;
    s32 var_v0_5;

    temp_v1 = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3;
    if (temp_v1 == 0)
    {
        var_s0 = func_8006FD90(romper, 0, 0x2800, 0x6000);
    }
    else if (temp_v1 == 2)
    {
        var_s0 = func_8006FD90(romper, 0, 0x3000, 0x8000);
    }
    else
    {
        var_s0 = func_8006FD90(romper, 0, 0xCCC, 0x2000);
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        var_s0 |= func_80070360(romper, 0, 0x333);
    }

    if (var_s0 != false)
    {
        romper->properties_E4.romper.positionX_FC  = g_SysWork.playerWork_4C.player_0.position_18.vx;
        romper->properties_E4.romper.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        romper->properties_E4.romper.field_10E     = 0;
    }
    else
    {
        romper->properties_E4.romper.field_10E += g_DeltaTime0;
    }

    temp_s0 = func_8007029C(romper, 0x2800, romper->rotation_24.vy);

    if (romper->properties_E4.romper.field_120 == 0 ||
        (temp_s0 != 0 && romper->properties_E4.romper.field_120 >= 0))
    {
        romper->properties_E4.romper.rotationY_F2 = 0;

        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz) >= 0x800)
        {
            romper->properties_E4.romper.rotationY_F2 = Chara_HeadingAngleGet(romper, 0x2800, romper->properties_E4.romper.positionX_FC,
                                                                              romper->properties_E4.romper.positionZ_100, 0x1000, true);
        }
        else
        {
            romper->properties_E4.romper.rotationY_F2 = Chara_HeadingAngleGet(romper, 0x2800, romper->properties_E4.romper.positionX_FC,
                                                                              romper->properties_E4.romper.positionZ_100, 0x1000, false);
        }

        if (romper->properties_E4.romper.rotationY_F2 == 0x1000)
        {
            romper->properties_E4.romper.rotationY_F2 = func_8006F99C(romper, 0x2800, romper->rotation_24.vy);
        }

        if (temp_s0 != 0)
        {
            romper->properties_E4.romper.field_120 = -(Rng_Rand16() % 0x1000 + 0x1000);
        }
        else
        {
            romper->properties_E4.romper.field_120 = Rng_Rand16() % 0x2000 + 0x1000;
        }
    }

    if (romper->properties_E4.romper.field_120 > 0)
    {
        romper->properties_E4.romper.field_120 -= g_DeltaTime0;
        if (romper->properties_E4.romper.field_120 < 0)
        {
            romper->properties_E4.romper.field_120 = 0;
        }
    }
    else
    {
        romper->properties_E4.romper.field_120 += g_DeltaTime0;
        if (romper->properties_E4.romper.field_120 > 0)
        {
            romper->properties_E4.romper.field_120 = 0;
        }
    }

    for (i = 0; i < 3; i++)
    {
        temp_v0_5 = func_8005BF38(romper->properties_E4.romper.rotationY_F2 - romper->rotation_24.vy);

        if (TIMESTEP_ANGLE_0 < ABS(temp_v0_5))
        {
            if (temp_v0_5 > 0)
            {
                romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x200);
            }
            else
            {
                romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x200);
            }
        }
        else
        {
            romper->rotation_24.vy = romper->properties_E4.romper.rotationY_F2;
        }
    }

    if (!func_8007029C(romper, 0x2800, romper->rotation_24.vy) && (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x82 &&
                                                                   FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x85))
    {
        romper->model_0.anim_4.status_0 = 40;
        romper->moveSpeed_38            = 0;
        return;
    }

    temp_v0_5 = func_8005BF38(romper->properties_E4.romper.rotationY_F2 - romper->rotation_24.vy);
    if (temp_v0_5 >= 0)
    {
        var_v0_5 = 0x800 - temp_v0_5;
    }
    else
    {
        var_v0_5 = temp_v0_5 + 0x800;
    }

    Chara_MoveSpeedUpdate4(romper, 0x1333, Q12_MULT_PRECISE(var_v0_5 * 2, 0x2666));
}

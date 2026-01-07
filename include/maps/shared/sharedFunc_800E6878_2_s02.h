void sharedFunc_800E6878_2_s02(s_SubCharacter* romper)
{
    s16 temp_s0;
    s16 temp_v0;
    s32 temp_s1;
    s32 temp_v1_3;
    s32 var_s0;

    temp_v0 = func_8005BF38(romper->properties_E4.romper.rotationY_F2 - romper->rotation_24.vy);

    if (TIMESTEP_ANGLE_2 < ABS(temp_v0))
    {
        if (temp_v0 > 0)
        {
            romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x155);
        }
        else
        {
            romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x155);
        }
    }
    else
    {
        romper->rotation_24.vy = romper->properties_E4.romper.rotationY_F2;
    }

    if (romper->rotation_24.vy == romper->properties_E4.romper.rotationY_F2 || func_8007029C(romper, 0x1000, romper->rotation_24.vy))
    {
        temp_v0 = func_8005BF38(romper->rotation_24.vy - ratan2(romper->properties_E4.romper.positionX_FC - romper->position_18.vx,
                                                                romper->properties_E4.romper.positionZ_100 - romper->position_18.vz));

        if (ABS(temp_v0) >= 0xAB)
        {
            if (!Rng_TestProbabilityBits(4))
            {
                romper->properties_E4.romper.rotationY_F2 = Chara_HeadingAngleGet(romper, 0x1000, romper->properties_E4.romper.positionX_FC,
                                                                                  romper->properties_E4.romper.positionZ_100, 0x1000, true);
            }
        }
    }

    if (Math_Vector2MagCalc(romper->position_18.vx - romper->properties_E4.romper.positionX_FC,
                            romper->position_18.vz - romper->properties_E4.romper.positionZ_100) < 0x1000)
    {
        temp_s0                                    = Rng_GenerateInt(0, 20479);
        temp_s1                                    = Rng_TestProbabilityBits(12);
        romper->properties_E4.romper.positionX_FC  = romper->properties_E4.romper.positionZ_110 + Q12_MULT(temp_s0, Math_Sin(temp_s1));
        romper->properties_E4.romper.positionZ_100 = romper->properties_E4.groaner.field_108 + Q12_MULT(temp_s0, Math_Cos(temp_s1));
    }

    romper->properties_E4.groaner.field_F0 += sharedFunc_800E939C_2_s02(romper);
    romper->moveSpeed_38                   += romper->properties_E4.groaner.field_F0;

    temp_v1_3 = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3;

    if (temp_v1_3 == 0)
    {
        var_s0 = func_8006FD90(romper, 1, 0x1CCC, 0x4000);
    }
    else if (temp_v1_3 == 2)
    {
        var_s0 = func_8006FD90(romper, 1, 0x3000, 0x7000);
    }
    else
    {
        var_s0 = func_8006FD90(romper, 1, 0x1000, 0x1000);
    }

    if (g_SavegamePtr->gameDifficulty_260 != -1)
    {
        var_s0 += func_80070360(romper, 0, 0x266);
    }

    if (var_s0 != 0 && romper->model_0.anim_4.status_0 == 0x1F)
    {
        romper->model_0.anim_4.status_0 = 0x26;

        if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x94 && FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x9D)
        {
            romper->properties_E4.romper.field_10C = 7;
        }
        else
        {
            romper->properties_E4.romper.field_10C = 0x12;
        }

        romper->flags_3E |= 4;
    }
}
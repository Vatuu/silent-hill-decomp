void Ai_Romper_Control_3(s_SubCharacter* romper)
{
    s16             var_s3;
    s32             temp_s0;
    s32             temp_s4;
    s32             temp_s5;
    s32             temp_v1_2;
    s32             var_a1;
    s32             var_s0;
    s32             i;
    s16             var_s2;
    s32             temp;
    s_SubCharacter* player;

    romper->properties_E4.romper.field_F0 += sharedFunc_800E94B4_2_s02(romper);
    romper->moveSpeed_38                  += romper->properties_E4.romper.field_F0;

    temp_v1_2 = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3;
    if (temp_v1_2 == 0)
    {
        var_s0 = func_8006FD90(romper, 0, 0x2800, 0x6000);
    }
    else if (temp_v1_2 == 2)
    {
        var_s0 = func_8006FD90(romper, 0, 0x3000, 0x8000);
    }
    else
    {
        var_s0 = func_8006FD90(romper, 0, 0xCCC, 0x2000);
    }

    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        var_s0 |= func_80070360(romper, 0, 0x333);
    }

    if (var_s0)
    {
        romper->properties_E4.romper.positionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx +
                                                    (Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Sin(g_SysWork.playerWork_4C.player_0.headingAngle_3C)) >> 1);

        romper->properties_E4.romper.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz +
                                                     (Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Cos(g_SysWork.playerWork_4C.player_0.headingAngle_3C)) >> 1);
        romper->properties_E4.romper.field_10E = 0;
    }
    else
    {
        romper->properties_E4.romper.field_10E += g_DeltaTime0;
    }

    if ((FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x6F && FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x73) ||
        (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x78 && FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x7F))
    {
        romper->properties_E4.romper.flags_E8 &= ~8;
        romper->properties_E4.romper.flags_E8 &= ~0x100;
        return;
    }

    if (!(romper->properties_E4.romper.flags_E8 & 0x100))
    {
        romper->properties_E4.romper.flags_E8 |= 0x100;
        return;
    }

    temp_s5 = Math_Vector2MagCalc(romper->position_18.vx - romper->properties_E4.romper.positionX_FC,
                                  romper->position_18.vz - romper->properties_E4.romper.positionZ_100);

    temp_s4 = func_800700F8(romper, &g_SysWork.playerWork_4C.player_0);

    if (!(romper->properties_E4.romper.flags_E8 & 8))
    {
        romper->properties_E4.romper.flags_E8 |= 8;

        var_s2 = ratan2(romper->properties_E4.romper.positionX_FC - romper->position_18.vx,
                        romper->properties_E4.romper.positionZ_100 - romper->position_18.vz);

        var_s3 = ABS(func_8005BF38(var_s2 - romper->rotation_24.vy));
        temp   = Q12_MULT_PRECISE(var_s3 * 2, 0x4000);

        if (!(romper->properties_E4.romper.flags_E8 & 0x10) && temp < temp_s5)
        {
            if (var_s3 < 0x2AA && temp_s5 < 0x6000 && !temp_s4)
            {
                romper->properties_E4.romper.rotationY_F2 = var_s2;
            }
            else
            {
                var_a1 = Q12_MULT_PRECISE(Rng_TestProbabilityBits(9) + 0xF00, CLAMP_MIN_THEN_LOW(temp_s5 - 0x333, 0x333, 0x2800));

                romper->properties_E4.romper.rotationY_F2 = Chara_HeadingAngleGet(romper, var_a1,
                                                                                  romper->properties_E4.romper.positionX_FC, romper->properties_E4.romper.positionZ_100, 0x1000, true);
            }
        }
        else
        {
            var_a1 = Q12_MULT_PRECISE(Rng_TestProbabilityBits(9) + 0xF00, 0x2800);

            romper->properties_E4.romper.rotationY_F2 = Chara_HeadingAngleGet(romper, var_a1,
                                                                              romper->properties_E4.romper.positionX_FC, romper->properties_E4.romper.positionZ_100, 0x1000, false);
        }

        if (romper->properties_E4.romper.rotationY_F2 == var_s2)
        {
            temp_s0 = func_8007029C(romper, CLAMP_HIGH(temp_s5, 0x1AAA), romper->rotation_24.vy);
        }
        else
        {
            temp_s0 = func_8007029C(romper, 0x1AAA, romper->rotation_24.vy);
        }

        if (romper->properties_E4.romper.field_10E > 0x1000 && !Rng_TestProbabilityBits(4))
        {
            romper->model_0.controlState_2            = 1;
            romper->model_0.anim_4.status_0           = 24;
            romper->properties_E4.romper.rotationY_F2 = romper->rotation_24.vy;
        }
        else if (temp_s0 != 0 || romper->properties_E4.romper.rotationY_F2 == 0x1000 ||
                 temp_s5 < Q12_MULT_PRECISE(0x1000 - Math_Cos(var_s3 >> 1), 0x2800))
        {
            if (romper->properties_E4.romper.rotationY_F2 == 0x1000)
            {
                romper->properties_E4.romper.rotationY_F2 = romper->rotation_24.vy + 0x800;
            }

            if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x73 || FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x78)
            {
                romper->model_0.controlState_2         = 4;
                romper->model_0.anim_4.status_0        = 28;
                romper->properties_E4.romper.field_10C = 0;
                romper->moveSpeed_38                   = 0;
                romper->properties_E4.romper.field_120 = 0;
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        var_s2 = func_8005BF38(romper->properties_E4.romper.rotationY_F2 - romper->rotation_24.vy);

        if (TIMESTEP_ANGLE_4 < ABS(var_s2))
        {
            if (var_s2 > 0)
            {
                romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x400);
            }
            else
            {
                romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x400);
            }
        }
        else
        {
            romper->rotation_24.vy = romper->properties_E4.romper.rotationY_F2;
            break;
        }
    }

    if (romper->properties_E4.romper.flags_E8 & 0x10)
    {
        romper->properties_E4.romper.field_120 += g_DeltaTime0;
        if (temp_s5 > 0x1CCC || romper->properties_E4.romper.field_120 > 0x1CCC)
        {
            romper->properties_E4.romper.field_120 = 0;
            romper->properties_E4.romper.flags_E8 &= ~0x10;
        }
    }

    for (i = 0; i < 6; i++)
    {
        if (&g_SysWork.npcs_1A0[i] == romper)
        {
            break;
        }
    }

    if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
    {
        return;
    }

    player = &g_SysWork.playerWork_4C.player_0;

    if (player->flags_3E & 8)
    {
        return;
    }

    if (g_SysWork.sysState_8 != 0 || g_SysWork.field_2284[3] & 3)
    {
        return;
    }

    if (romper->field_34 != 0 || temp_s5 <= 0x4CC || temp_s5 >= 0x3333 ||
        romper->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy >= 0x1000 ||
        romper->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy <= -0x1333)
    {
        return;
    }

    if (romper->properties_E4.romper.flags_E8 & 0x10)
    {
        return;
    }

    if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                 g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz) -
                          romper->rotation_24.vy)) < 0x155)
    {
        romper->model_0.controlState_2         = 5;
        romper->model_0.anim_4.status_0        = 4;
        romper->field_44.field_0               = 1;
        g_SysWork.field_2284[3]               |= 3;
        romper->properties_E4.romper.flags_E8 |= 0x810;
    }
}

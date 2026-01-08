void sharedFunc_800E79D8_2_s02(s_SubCharacter* romper)
{
    s_Collision sp20;
    VECTOR3     sp30;
    s16         temp_v0_4;
    s16         temp_v0_5;
    s16         var_s3;
    s32         temp_a1;
    s32         temp_s2;
    s32         temp_v0;
    s32         temp_v0_3;
    s32         temp_v1_5;
    s16         var_a0_2;
    s32         i;
    s16         temp;

    if (romper->model_0.anim_4.status_0 == 5)
    {
        if (romper->model_0.anim_4.time_4 > 0x5000)
        {
            var_s3 = 0;
        }
        else
        {
            var_s3 = 0x800 - (FP_TO(romper->model_0.anim_4.time_4 - 0x2000, Q12_SHIFT) / 0x3000 >> 1);
        }
    }
    else
    {
        var_s3 = 0x800;
    }

    temp_v0                                   = Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Sin(g_SysWork.playerWork_4C.player_0.headingAngle_3C));
    romper->properties_E4.romper.positionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12_MULT_PRECISE(temp_v0, var_s3);

    temp_a1                                    = Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Cos(g_SysWork.playerWork_4C.player_0.headingAngle_3C));
    romper->properties_E4.romper.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12_MULT_PRECISE(temp_a1, var_s3);

    temp_v0_3 = ratan2(romper->properties_E4.romper.positionX_FC - romper->position_18.vx, romper->properties_E4.romper.positionZ_100 - romper->position_18.vz);
    temp_s2   = temp_v0_3;

    if (romper->model_0.anim_4.status_0 == 4)
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, 0xF000), 0);

        for (i = 0; i < 4; i++)
        {
            temp_v0_4 = func_8005BF38(temp_s2 - romper->rotation_24.vy);

            if (((g_DeltaTime0 >> 3) + 1) >> 1 < ABS(temp_v0_4))
            {
                if (temp_v0_4 > 0)
                {
                    romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x400) >> 1;
                }
                else
                {
                    romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x400) >> 1;
                }
            }
            else
            {
                romper->rotation_24.vy = temp_s2;
            }
        }
    }
    else if (romper->model_0.anim_4.status_0 == 5)
    {
        temp_v0_5 = func_8005BF38(temp_v0_3 - romper->rotation_24.vy);

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

        if (romper->model_0.anim_4.time_4 == 0x2000)
        {
            temp_v1_5 = Math_Vector2MagCalc(romper->properties_E4.romper.positionX_FC - romper->position_18.vx,
                                            romper->properties_E4.romper.positionZ_100 - romper->position_18.vz);

            var_a0_2             = CLAMP_LOW(temp_v1_5, 0x4CC);
            romper->moveSpeed_38 = var_a0_2 << 1;
            Collision_Get(&sp20, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
            temp                                   = sp20.groundHeight_0 - 0xCCC;
            romper->field_34                       = (temp << 1) - 0x2733;
            romper->properties_E4.romper.flags_E8 &= ~0x200;
        }
        else if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) == 5 || FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) == 6)
        {
            if (!(romper->properties_E4.romper.flags_E8 & 0x200))
            {
                func_8005DC1C(0x57B, &romper->position_18, 0x80, 0);
                romper->properties_E4.romper.flags_E8 |= 0x200;
            }

            sp30.vx = romper->position_18.vx;
            sp30.vy = romper->position_18.vy;
            sp30.vz = romper->position_18.vz;

            if (func_8008A0E4(1, 0x36, romper, &sp30, &g_SysWork.playerWork_4C.player_0, romper->rotation_24.vy, 0x400) != -1)
            {
                romper->model_0.anim_4.status_0 = 6;
                romper->model_0.controlState_2  = 0xA;
                sharedFunc_800E9714_2_s02(romper);
                romper->properties_E4.romper.flags_E8 |= 0x400;
            }
        }
    }
    else
    {
        if (romper->properties_E4.romper.flags_E8 & 1)
        {
            Chara_MoveSpeedUpdate(romper, Q12_MULT_PRECISE(romper->moveSpeed_38, 0x3000) + 0x3000);
        }
        else
        {
            romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, 0xF000), 0);
        }
    }
}
void Ai_Romper_Control_2(s_SubCharacter* romper)
{
    q3_12  moveDist;
    q3_12  angleDeltaToTarget;
    q19_12 headingAngle;
    s32    flags;
    bool   cond;

    #define romperProps romper->properties_E4.romper

    angleDeltaToTarget = func_8005BF38(romperProps.rotationY_F2 - romper->rotation_24.vy);
    if (TIMESTEP_ANGLE_2 < ABS(angleDeltaToTarget))
    {
        if (angleDeltaToTarget > FP_ANGLE(0.0f))
        {
            romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f));
        }
        else
        {
            romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f));
        }
    }
    else
    {
        romper->rotation_24.vy = romperProps.rotationY_F2;
    }

    if (romper->rotation_24.vy == romperProps.rotationY_F2 || func_8007029C(romper, Q12(1.0f), romper->rotation_24.vy))
    {
        angleDeltaToTarget = func_8005BF38(romper->rotation_24.vy - ratan2(romperProps.positionX_FC  - romper->position_18.vx,
                                                                           romperProps.positionZ_100 - romper->position_18.vz));
        if (ABS(angleDeltaToTarget) > FP_ANGLE(15.0f))
        {
            if (!Rng_TestProbabilityBits(4))
            {
                romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, Q12(1.0f), romperProps.positionX_FC,
                                                                                  romperProps.positionZ_100, FP_ANGLE(360.0f), true);
            }
        }
    }

    if (Math_Vector2MagCalc(romper->position_18.vx - romperProps.positionX_FC,
                            romper->position_18.vz - romperProps.positionZ_100) < Q12(1.0f))
    {
        moveDist                                   = Rng_GenerateInt(Q12(0.0f), Q12(5.0f) - 1);
        headingAngle                               = Rng_TestProbabilityBits(12); // TODO: Wrong macro.
        romperProps.positionX_FC  = romperProps.positionZ_110 + Q12_MULT(moveDist, Math_Sin(headingAngle));
        romperProps.positionZ_100 = romperProps.positionX_108 + Q12_MULT(moveDist, Math_Cos(headingAngle));
    }

    romperProps.field_F0 += sharedFunc_800E939C_2_s02(romper);
    romper->moveSpeed_38 += romperProps.field_F0;

    flags = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1));
    if (flags == 0)
    {
        cond = func_8006FD90(romper, 1, Q12(1.8f), Q12(4.0f));
    }
    else if (flags == (1 << 1))
    {
        cond = func_8006FD90(romper, 1, Q12(3.0f), Q12(7.0f));
    }
    else
    {
        cond = func_8006FD90(romper, 1, Q12(1.0f), Q12(1.0f));
    }

    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        cond += func_80070360(romper, Q12(0.0f), 0x266); // TODO: Last arg is angle? Unclear.
    }

    if (cond != 0 && romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_15, true))
    {
        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_19, false);

        if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 148 &&
            FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 157)
        {
            romperProps.field_10C = 7;
        }
        else
        {
            romperProps.field_10C = 18;
        }

        romper->flags_3E |= 4;
    }

    #undef romperProps
}

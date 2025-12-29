void sharedFunc_800D492C_0_s00(s_SubCharacter* stalker)
{
    q3_12  angle;
    q19_12 offsetX;
    q19_12 offsetZ;
    bool   condCombo;
    q19_12 distToPlayer;
    q19_12 distToTarget;
    q19_12 dist1;
    q19_12 deltaX;
    q19_12 deltaZ;

    #define stalkerProps stalker->properties_E4.stalker

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

    if (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        dist1     = Q12(5.5f);
        condCombo = func_8006FD90(stalker, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        dist1     = Q12(4.5f);
        condCombo = func_8006FD90(stalker, 0, Q12(12.f), Q12(0.0f));
#else
        dist1     = Q12(6.0f);
        condCombo = func_8006FD90(stalker, 0, Q12(16.0f), Q12(0.0f));
#endif
    }
    else
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        dist1 = Q12(1.0f);
#else
        dist1 = Q12(1.2f);
#endif
        condCombo = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.4f));
    }

    condCombo |= func_80070360(stalker, distToPlayer, Q12(0.8f));

    if (!(stalkerProps.flags_E8 & StalkerFlag_13))
    {
        if (stalkerProps.flags_E8 & StalkerFlag_11)
        {
            Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(0.35f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(0.7f));
        }
    }

    offsetX      = stalker->position_18.vx - stalkerProps.targetPositionX_F0;
    offsetZ      = stalker->position_18.vz - stalkerProps.targetPositionZ_F4;
    distToTarget = MAX(ABS(offsetX), ABS(offsetZ));

    if (!(stalker->properties_E4.player.afkTimer_E8 & 0x18))
    {
        if (!(Rng_GenerateInt(0, 511) && distToTarget <= Q12(4.0f)) || // 1 in 512 chance.
            (!Rng_GenerateInt(0, 127) &&                               // 1 in 128 chance.
             Rng_GenerateUInt(0, Q12(1.0f) - 1) < FP_TO(distToTarget, Q12_SHIFT) / Q12(4.0f)))
        {
            if (stalkerProps.flags_E8 & StalkerFlag_11)
            {
                deltaX = Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1) - offsetZ;
                stalkerProps.targetHeadingAngle_100 = ratan2(deltaX, deltaZ);
            }
            else
            {
                deltaX = Rng_GenerateInt(Q12(-4.0f), Q12(4.0f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Q12(-4.0f), Q12(4.0f) - 1) - offsetZ;
                stalkerProps.targetHeadingAngle_100 = ratan2(deltaX, deltaZ);
            }

            stalkerProps.flags_E8 |= StalkerFlag_3;
        }
    }

    if (!(stalkerProps.flags_E8 & StalkerFlag_4) && func_8007029C(stalker, Q12(1.0f), stalker->rotation_24.vy))
    {
        stalkerProps.targetHeadingAngle_100 = func_8006F99C(stalker, Q12(3.5f), stalker->rotation_24.vy);
        if (stalkerProps.targetHeadingAngle_100 == StalkerFlag_WarpRotation)
        {
            stalkerProps.targetHeadingAngle_100 = stalker->rotation_24.vy + FP_ANGLE(180.0f);
        }

        stalkerProps.flags_E8 |= StalkerFlag_4;
    }

    // Smoothly rotate toward target direction
    angle = func_8005BF38(stalkerProps.targetHeadingAngle_100 - stalker->rotation_24.vy);

    if (TIMESTEP_ANGLE_0 < ABS(angle))
    {
        if (angle > FP_ANGLE(0.0f))
        {
            stalker->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
        }
        else
        {
            stalker->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
        }
    }
    else
    {
        stalkerProps.flags_E8 &= ~(StalkerFlag_3 | StalkerFlag_4);
    }

    // Handle aggressive/chase mode.
    if (stalkerProps.flags_E8 & StalkerFlag_11)
    {
        if (!Rng_GenerateInt(0, 1023)) // 1 in 1024 chance.
        {
            stalkerProps.flags_E8 &= ~StalkerFlag_3;
        }

        if (!Rng_GenerateInt(0, 1023)) // 1 in 1024 chance.
        {
            stalkerProps.flags_E8 &= ~StalkerFlag_4;
        }

        if (distToPlayer < Q12(2.0f) && distToPlayer < dist1 && !func_800700F8(stalker, &g_SysWork.playerWork_4C.player_0))
        {
            stalkerProps.timer_F8  = Q12(5.0f);
            stalkerProps.flags_E8 |= StalkerFlag_0;
            stalkerProps.flags_E8 &= ~StalkerFlag_11;
        }
    }

    if ((stalkerProps.flags_E8 & StalkerFlag_0))
    {
        if ((stalkerProps.flags_E8 & StalkerFlag_10) || condCombo)
        {
            if (condCombo)
            {
                stalkerProps.targetPositionX_F0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
                stalkerProps.targetPositionZ_F4 = g_SysWork.playerWork_4C.player_0.position_18.vz;
                stalkerProps.timer_116          = Q12(0.0f);
            }

            if (!(stalkerProps.flags_E8 & StalkerFlag_10))
            {
                stalkerProps.flags_E8 |= StalkerFlag_10;
                sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1363);
            }

            if (((!Rng_GenerateInt(0, 15) && stalkerProps.timer_F8 > Q12(1.0f)) && // 1 in 16 chance.
                 (stalkerProps.flags_E8 & StalkerFlag_1)) ||
                (!Rng_GenerateInt(0, 15) && stalkerProps.timer_F8 > Q12(2.5f)) ||  // 1 in 16 chance.
                (!Rng_GenerateInt(0, 31) && ((dist1 >> 1) < distToPlayer)))        // 1 in 32 chance.
            {
                if (stalkerProps.flags_E8 & StalkerFlag_1)
                {
                    stalker->model_0.controlState_2 = 2;
                }
                else
                {
                    stalker->model_0.controlState_2 = 3;
                }

                stalkerProps.flags_E8 &= ~(StalkerFlag_3 | StalkerFlag_4);
            }
            else
            {
                stalkerProps.timer_F8 += g_DeltaTime0;
            }
        }
    }

    if (!condCombo)
    {
        if (stalkerProps.flags_E8 & StalkerFlag_10)
        {
            stalkerProps.timer_116 += g_DeltaTime0;

            if (!Rng_GenerateInt(0, 4095) || stalkerProps.timer_116 > Q12(1.2f)) // 1 in 4096 chance.
            {
                stalkerProps.timer_116 = Q12(0.0f);
                stalkerProps.flags_E8 &= ~StalkerFlag_10;
            }
        }
    }

    #undef stalkerProps
}

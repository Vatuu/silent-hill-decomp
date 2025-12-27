void sharedFunc_800D492C_0_s00(s_SubCharacter* stalker)
{
    q3_12  angle;
    q19_12 offsetX;
    q19_12 offsetZ;
    bool   condCombo;
    q19_12 dist0;
    q19_12 magMax;
    q19_12 dist1;
    q19_12 deltaX;
    q19_12 deltaZ;

    dist0 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
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

    condCombo |= func_80070360(stalker, dist0, Q12(0.8f));

    if (!(stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 13)))
    {
        if (stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 11))
        {
            Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(0.35f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(0.7f));
        }
    }

    offsetX = stalker->position_18.vx - stalker->properties_E4.player.field_F0;
    offsetZ = stalker->position_18.vz - stalker->properties_E4.player.field_F4;

    magMax = MAX(ABS(offsetX), ABS(offsetZ));

    if (!(stalker->properties_E4.player.afkTimer_E8 & 0x18))
    {
        if (!(Rng_GenerateInt(0, 511) && magMax <= Q12(4.0f)) || // 1 in 512 chance.
            (!Rng_GenerateInt(0, 127) &&                         // 1 in 128 chance.
             Rng_GenerateUInt(0, Q12(1.0f) - 1) < FP_TO(magMax, Q12_SHIFT) / Q12(4.0f)))
        {
            if (stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 11))
            {
                deltaX = Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1) - offsetZ;

                stalker->properties_E4.dummy.properties_E8[6].val16[0] = ratan2(deltaX, deltaZ);
            }
            else
            {
                deltaX = Rng_GenerateInt(Q12(-4.0f), Q12(4.0f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Q12(-4.0f), Q12(4.0f) - 1) - offsetZ;
                
                stalker->properties_E4.dummy.properties_E8[6].val16[0] = ratan2(deltaX, deltaZ);
            }
            stalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 3;
        }
    }

    if (!(stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 4)) && func_8007029C(stalker, Q12(1.0f), stalker->rotation_24.vy))
    {
        stalker->properties_E4.dummy.properties_E8[6].val16[0] = func_8006F99C(stalker, Q12(3.5f), stalker->rotation_24.vy);

        if (stalker->properties_E4.dummy.properties_E8[6].val16[0] == (1 << 12))
        {
            stalker->properties_E4.dummy.properties_E8[6].val16[0] = stalker->rotation_24.vy + FP_ANGLE(180.0f);
        }

        stalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 4;
    }

    // Smoothly rotate toward target direction
    angle = func_8005BF38(stalker->properties_E4.dummy.properties_E8[6].val16[0] - stalker->rotation_24.vy);

    if ((((g_DeltaTime0 >> 4) + 1) < ABS(angle)))
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
        stalker->properties_E4.dummy.properties_E8[0].val16[0] &= ~((1 << 3) | (1 << 4));
    }

    // Handle aggressive/chase mode.
    if (stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 11))
    {
        if (Rng_GenerateInt(0, 1023) == 0)
        {
            stalker->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 3);
        }

        if (Rng_GenerateInt(0, 1023) == 0)
        {
            stalker->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 4);
        }

        if (dist0 < Q12(2.0f) && dist0 < dist1 && !func_800700F8(stalker, &g_SysWork.playerWork_4C.player_0))
        {
            stalker->properties_E4.player.runTimer_F8                       = Q12(5.0f);
            stalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1;
            stalker->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 11);
        }
    }

    if ((stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 0)))
    {
        if ((stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 10)) || condCombo)
        {
            if (condCombo)
            {
                stalker->properties_E4.player.field_F0                          = g_SysWork.playerWork_4C.player_0.position_18.vx;
                stalker->properties_E4.player.field_F4                          = g_SysWork.playerWork_4C.player_0.position_18.vz;
                stalker->properties_E4.dummy.properties_E8[11].val16[1] = 0;
            }

            if (!(stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 10)))
            {
                stalker->properties_E4.dummy.properties_E8[0].val16[0] |= (1 << 10);
                sharedFunc_800D7E04_0_s00(stalker, 1363);
            }

            if (((Rng_GenerateInt(0, 15) == 0 && stalker->properties_E4.player.runTimer_F8 > Q12(1.0f)) && // 1 in 16 cheance.
                 (stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 1))) ||
                (Rng_GenerateInt(0, 15) == 0 && stalker->properties_E4.player.runTimer_F8 > Q12(2.5f)) ||  // 1 in 16 chance.
                (Rng_GenerateInt(0, 31) == 0 && ((dist1 >> 1) < dist0)))                                 // 1 in 32 chance.
            {
                if (stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 1))
                {
                    stalker->model_0.state_2 = 2;
                }
                else
                {
                    stalker->model_0.state_2 = 3;
                }

                stalker->properties_E4.dummy.properties_E8[0].val16[0] &= ~((1 << 3) | (1 << 4));
            }
            else
            {
                stalker->properties_E4.player.runTimer_F8 += g_DeltaTime0;
            }
        }
    }

    if (!condCombo)
    {
        if (stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 10))
        {
            stalker->properties_E4.dummy.properties_E8[11].val16[1] += g_DeltaTime0;

            if (Rng_GenerateInt(0, 4095) == 0 || (u16)stalker->properties_E4.dummy.properties_E8[11].val16[1] > Q12(1.2f)) // 1 in 4096 chance.
            {
                stalker->properties_E4.dummy.properties_E8[11].val16[1] = 0;
                stalker->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 10);
            }
        }
    }
}

void sharedFunc_800D492C_0_s00(s_SubCharacter* chara)
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

    dist0 = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

    if (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        dist1     = Q12(5.5f);
        condCombo = func_8006FD90(chara, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        dist1     = Q12(4.5f);
        condCombo = func_8006FD90(chara, 0, Q12(12.f), Q12(0.0f));
#else
        dist1     = Q12(6.0f);
        condCombo = func_8006FD90(chara, 0, Q12(16.0f), Q12(0.0f));
#endif
    }
    else
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        dist1 = Q12(1.0f);
#else
        dist1 = Q12(1.2f);
#endif
        condCombo = func_8006FD90(chara, 1, Q12(0.4f), Q12(0.4f));
    }

    condCombo |= func_80070360(chara, dist0, Q12(0.8f));

    if (!(chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 13)))
    {
        if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 11))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(0.5f), Q12(0.35f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(chara, Q12(0.5f), Q12(0.7f));
        }
    }

    offsetX = chara->position_18.vx - chara->properties_E4.player.field_F0;
    offsetZ = chara->position_18.vz - chara->properties_E4.player.field_F4;

    magMax = MAX(ABS(offsetX), ABS(offsetZ));

    if (!(chara->properties_E4.player.afkTimer_E8 & 0x18))
    {
        if (!(Rng_GenerateInt(0, 511) && magMax <= Q12(4.0f)) || // 1 in 512 chance.
            (!Rng_GenerateInt(0, 127) &&                         // 1 in 128 chance.
             Rng_GenerateUInt(0, Q12(1.0f) - 1) < FP_TO(magMax, Q12_SHIFT) / Q12(4.0f)))
        {
            if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 11))
            {
                deltaX = Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1) - offsetZ;

                chara->properties_E4.dummy.properties_E8[6].val16[0] = ratan2(deltaX, deltaZ);
            }
            else
            {
                deltaX = Rng_GenerateInt(Q12(-4.0f), Q12(4.0f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Q12(-4.0f), Q12(4.0f) - 1) - offsetZ;
                
                chara->properties_E4.dummy.properties_E8[6].val16[0] = ratan2(deltaX, deltaZ);
            }
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 3;
        }
    }

    if (!(chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 4)) && func_8007029C(chara, Q12(1.0f), chara->rotation_24.vy))
    {
        chara->properties_E4.dummy.properties_E8[6].val16[0] = func_8006F99C(chara, Q12(3.5f), chara->rotation_24.vy);

        if (chara->properties_E4.dummy.properties_E8[6].val16[0] == (1 << 12))
        {
            chara->properties_E4.dummy.properties_E8[6].val16[0] = chara->rotation_24.vy + FP_ANGLE(180.0f);
        }

        chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 4;
    }

    // Smoothly rotate toward target direction
    angle = func_8005BF38(chara->properties_E4.dummy.properties_E8[6].val16[0] - chara->rotation_24.vy);

    if ((((g_DeltaTime0 >> 4) + 1) < ABS(angle)))
    {
        if (angle > FP_ANGLE(0.0f))
        {
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
        }
        else
        {
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
        }
    }
    else
    {
        chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~((1 << 3) | (1 << 4));
    }

    // Handle aggressive/chase mode.
    if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 11))
    {
        if (Rng_GenerateInt(0, 1023) == 0)
        {
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 3);
        }

        if (Rng_GenerateInt(0, 1023) == 0)
        {
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 4);
        }

        if (dist0 < Q12(2.0f) && dist0 < dist1 && !func_800700F8(chara, &g_SysWork.player_4C.chara_0))
        {
            chara->properties_E4.player.runTimer_F8                       = Q12(5.0f);
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1;
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 11);
        }
    }

    if ((chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 0)))
    {
        if ((chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 10)) || condCombo)
        {
            if (condCombo)
            {
                chara->properties_E4.player.field_F0                          = g_SysWork.player_4C.chara_0.position_18.vx;
                chara->properties_E4.player.field_F4                          = g_SysWork.player_4C.chara_0.position_18.vz;
                chara->properties_E4.dummy.properties_E8[11].val16[1] = 0;
            }

            if (!(chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 10)))
            {
                chara->properties_E4.dummy.properties_E8[0].val16[0] |= (1 << 10);
                sharedFunc_800D7E04_0_s00(chara, 1363);
            }

            if (((Rng_GenerateInt(0, 15) == 0 && chara->properties_E4.player.runTimer_F8 > Q12(1.0f)) && // 1 in 16 cheance.
                 (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 1))) ||
                (Rng_GenerateInt(0, 15) == 0 && chara->properties_E4.player.runTimer_F8 > Q12(2.5f)) ||  // 1 in 16 chance.
                (Rng_GenerateInt(0, 31) == 0 && ((dist1 >> 1) < dist0)))                                 // 1 in 32 chance.
            {
                if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 1))
                {
                    chara->model_0.state_2 = 2;
                }
                else
                {
                    chara->model_0.state_2 = 3;
                }

                chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~((1 << 3) | (1 << 4));
            }
            else
            {
                chara->properties_E4.player.runTimer_F8 += g_DeltaTime0;
            }
        }
    }

    if (!condCombo)
    {
        if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 10))
        {
            chara->properties_E4.dummy.properties_E8[11].val16[1] += g_DeltaTime0;

            if (Rng_GenerateInt(0, 4095) == 0 || (u16)chara->properties_E4.dummy.properties_E8[11].val16[1] > Q12(1.2f)) // 1 in 4096 chance.
            {
                chara->properties_E4.dummy.properties_E8[11].val16[1] = 0;
                chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 10);
            }
        }
    }
}

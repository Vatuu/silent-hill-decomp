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

    // TODO: Demagic everything.

    dist0 = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

    if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) == 0)
    {
        dist1     = 0x5800;
        condCombo = func_8006FD90(chara, 0, 0x7800, 0x7800);
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) == 2)
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        dist1     = 0x4800;
        condCombo = func_8006FD90(chara, 0, 0xC000, 0);
#else
        dist1     = 0x6000;
        condCombo = func_8006FD90(chara, 0, 0x10000, 0);
#endif
    }
    else
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        dist1 = 0x1000;
#else
        dist1 = 0x1333;
#endif
        condCombo = func_8006FD90(chara, 1, 0x666, 0x666);
    }

    condCombo |= func_80070360(chara, dist0, 0xCCC);

    if (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x2000))
    {
        if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x800)
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
        if (!(Rng_GenerateInt(Rng_Rand16(), 0, 0x1FF) && magMax <= Q12(4.0f)) ||
            (!Rng_GenerateInt(Rng_Rand16(), 0, 0x7F) && Rng_GenerateInt((u32)Rng_Rand16(), 0, 0xFFF) < FP_TO(magMax, Q12_SHIFT) / Q12(4.0f)))
        {
            if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x800)
            {
                deltaX = Rng_GenerateInt(Rng_Rand16(), Q12(-0.5f), Q12(0.5f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Rng_Rand16(), Q12(-0.5f), Q12(0.5f) - 1) - offsetZ;

                chara->properties_E4.larvalStalker.properties_E8[6].val16[0] = ratan2(deltaX, deltaZ);
            }
            else
            {
                deltaX = Rng_GenerateInt(Rng_Rand16(), Q12(-4.0f), Q12(4.0f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Rng_Rand16(), Q12(-4.0f), Q12(4.0f) - 1) - offsetZ;
                
                chara->properties_E4.larvalStalker.properties_E8[6].val16[0] = ratan2(deltaX, deltaZ);
            }
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 8;
        }
    }

    if (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x10) && func_8007029C(chara, 0x1000, chara->rotation_24.vy))
    {
        chara->properties_E4.larvalStalker.properties_E8[6].val16[0] = func_8006F99C(chara, 0x3800, chara->rotation_24.vy);

        if (chara->properties_E4.larvalStalker.properties_E8[6].val16[0] == 0x1000)
        {
            chara->properties_E4.larvalStalker.properties_E8[6].val16[0] = chara->rotation_24.vy + 0x800;
        }

        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x10;
    }

    // Smoothly rotate toward target direction
    angle = func_8005BF38(chara->properties_E4.larvalStalker.properties_E8[6].val16[0] - chara->rotation_24.vy);

    if (((g_DeltaTime0 >> 4) + 1 < ABS(angle)))
    {
        if (angle > 0)
        {
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT);
        }
        else
        {
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT);
        }
    }
    else
    {
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= 0xFFE7;
    }

    // Handle "aggro"/chase mode
    if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x800)
    {
        if (!Rng_TestProbabilityBits(10))
        {
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= 0xFFF7;
        }

        if (!Rng_TestProbabilityBits(10))
        {
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= 0xFFEF;
        }

        if (dist0 < 0x2000 && dist0 < dist1 && !func_800700F8(chara, &g_SysWork.player_4C.chara_0))
        {
            chara->properties_E4.player.runTimer_F8                       = 0x5000;
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1;
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= 0xF7FF;
        }
    }

    if ((chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 1))
    {
        if ((chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x400) || condCombo)
        {
            if (condCombo)
            {
                chara->properties_E4.player.field_F0                           = g_SysWork.player_4C.chara_0.position_18.vx;
                chara->properties_E4.player.field_F4                           = g_SysWork.player_4C.chara_0.position_18.vz;
                chara->properties_E4.larvalStalker.properties_E8[0xB].val16[1] = 0;
            }

            if (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x400))
            {
                chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x400;
                sharedFunc_800D7E04_0_s00(chara, 0x553);
            }

            if (((!Rng_TestProbabilityBits(4) && chara->properties_E4.player.runTimer_F8 > 0x1000) && (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 2)) ||
                (!Rng_TestProbabilityBits(4) && chara->properties_E4.player.runTimer_F8 > 0x2800) ||
                (!Rng_TestProbabilityBits(5) && ((dist1 >> 1) < dist0)))
            {
                if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 2)
                {
                    chara->model_0.state_2 = 2;
                }
                else
                {
                    chara->model_0.state_2 = 3;
                }

                chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= 0xFFE7; // clear bit 3,4
            }
            else
            {
                chara->properties_E4.player.runTimer_F8 += g_DeltaTime0;
            }
        }
    }

    if (!condCombo)
    {
        if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x400)
        {
            chara->properties_E4.larvalStalker.properties_E8[0xB].val16[1] += g_DeltaTime0;

            if (!Rng_TestProbabilityBits(12) || (u16)chara->properties_E4.larvalStalker.properties_E8[0xB].val16[1] > 0x1333)
            {
                chara->properties_E4.larvalStalker.properties_E8[0xB].val16[1] = 0;
                chara->properties_E4.larvalStalker.properties_E8[0].val16[0]  &= ~0x400; // clear bit 10
            }
        }
    }
}
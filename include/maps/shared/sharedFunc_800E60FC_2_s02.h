void sharedFunc_800E60FC_2_s02(s_SubCharacter* romper)
{
    s32 var_s1;

    #define romperProps romper->properties_E4.romper

    switch (romper->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(RomperAnim_2, true):
            sharedFunc_800E5FC8_2_s02(romper, 2, 2, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_3, true):
            sharedFunc_800E5FC8_2_s02(romper, 8, 5, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_4, true):
            sharedFunc_800E5FC8_2_s02(romper, 15, 2, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_11, true):
            sharedFunc_800E5FC8_2_s02(romper, 93, 2, &romperProps.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 93, 3, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_13, true):
            sharedFunc_800E5FC8_2_s02(romper, 109, 7, &romperProps.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 109, 20, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_14, true):
            sharedFunc_800E5FC8_2_s02(romper, 131, 8, &romperProps.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 131, 15, &romperProps.field_114);
            break;

        default:
            romperProps.field_115 = 0;
            romperProps.field_114 = 0;
            break;
    }

    if (romperProps.field_116 != Q12(0.0f))
    {
        romperProps.field_116 -= g_DeltaTime0;
        if (romperProps.field_116 < Q12(0.0f))
        {
            romperProps.field_116 = Q12(0.0f);
        }
    }
    else if (romperProps.flags_E8 & RomperFlag_7)
    {
        romperProps.field_116 = Q12(0.8f);
        func_8005DC1C(Sfx_Unk1400, &romper->position_18, Q8(0.5f), 0);
    }

    romperProps.flags_E8 &= ~RomperFlag_7;

    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_5, true))
    {
        if (romperProps.timer_118 == Q12(0.0f))
        {
            func_8005DC1C(Sfx_Unk1401, &romper->position_18, Q8(0.5f), 0);
            romperProps.timer_118 = Q12(3.2f);
        }
        else
        {
            romperProps.timer_118 -= g_DeltaTime0;
            if (romperProps.timer_118 < Q12(0.0f))
            {
                romperProps.timer_118 = Q12(0.0f);
            }
        }
    }
    else if (romperProps.timer_118 > Q12(0.0f))
    {
        romperProps.timer_118 = Q12(0.0f);
        Sd_SfxStop(Sfx_Unk1401);
    }

    if (romperProps.field_11A != 0)
    {
        // TODO: Wrong RNG macro.
        func_8005DC1C(Sfx_Unk1402, &romper->position_18, Rng_TestProbabilityBits(4) + 120, 0);
        romperProps.field_11A = 0;
    }

    if (romper->model_0.anim_4.status_0 != ANIM_STATUS(RomperAnim_5, true) &&
        romperProps.field_116 == 0 &&
        romper->health_B0 > Q12(0.0f))
    {
        if (romperProps.timer_11C != Q12(0.0f))
        {
            romperProps.timer_11C -= g_DeltaTime0;
            if (romperProps.timer_11C < Q12(0.0f))
            {
                romperProps.timer_11C = Q12(0.0f);
            }
        }
        else
        {
            // TODO: Is this Q6?
            if (romper->health_B0 <= Q12(225.0f))
            {
                var_s1 = Q12_TO_Q6(Q12_DIV(romper->health_B0, Q12(450.0f))) + Q6(0.875f);
            }
            else
            {
                var_s1 = Q6(1.875f);
            }

            // TODO: Wrong RNG macro.
            func_8005DC1C(Sfx_Unk1404, &romper->position_18, (var_s1 + Rng_TestProbabilityBits(4)) >> 1, 0);
            romperProps.timer_11C = Rng_GenerateInt(Q12(4.5f), Q12(6.5f) - 1);
        }
    }

    #undef romperProps
}

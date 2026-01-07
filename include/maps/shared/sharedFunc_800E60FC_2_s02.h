void sharedFunc_800E60FC_2_s02(s_SubCharacter* romper)
{
    s32 var_s1;

    switch (romper->model_0.anim_4.status_0)
    {
        case 5:
            sharedFunc_800E5FC8_2_s02(romper, 2, 2, &romper->properties_E4.romper.field_114);
            break;

        case 7:
            sharedFunc_800E5FC8_2_s02(romper, 8, 5, &romper->properties_E4.romper.field_114);
            break;

        case 9:
            sharedFunc_800E5FC8_2_s02(romper, 15, 2, &romper->properties_E4.romper.field_114);
            break;

        case 23:
            sharedFunc_800E5FC8_2_s02(romper, 93, 2, &romper->properties_E4.romper.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 93, 3, &romper->properties_E4.romper.field_114);
            break;

        case 27:
            sharedFunc_800E5FC8_2_s02(romper, 109, 7, &romper->properties_E4.romper.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 109, 20, &romper->properties_E4.romper.field_114);
            break;

        case 29:
            sharedFunc_800E5FC8_2_s02(romper, 131, 8, &romper->properties_E4.romper.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 131, 15, &romper->properties_E4.romper.field_114);
            break;

        default:
            romper->properties_E4.romper.field_115 = 0;
            romper->properties_E4.romper.field_114 = 0;
            break;
    }

    if (romper->properties_E4.romper.field_116 != Q12(0.0f))
    {
        romper->properties_E4.romper.field_116 -= g_DeltaTime0;
        if (romper->properties_E4.romper.field_116 < Q12(0.0f))
        {
            romper->properties_E4.romper.field_116 = Q12(0.0f);
        }
    }
    else if (romper->properties_E4.romper.field_E8 & 0x80)
    {
        romper->properties_E4.romper.field_116 = 0xCCC;
        func_8005DC1C(0x578, &romper->position_18, 0x80, 0);
    }

    romper->properties_E4.romper.field_E8 &= ~0x80;

    if (romper->model_0.anim_4.status_0 == 11)
    {
        if (romper->properties_E4.romper.field_118 == 0)
        {
            func_8005DC1C(0x579, &romper->position_18, 0x80, 0);
            romper->properties_E4.romper.field_118 = 0x3333;
        }
        else
        {
            romper->properties_E4.romper.field_118 -= g_DeltaTime0;
            if (romper->properties_E4.romper.field_118 < 0)
            {
                romper->properties_E4.romper.field_118 = 0;
            }
        }
    }
    else if (romper->properties_E4.romper.field_118 > 0)
    {
        romper->properties_E4.romper.field_118 = 0;
        Sd_SfxStop(0x579);
    }

    if (romper->properties_E4.romper.field_11A != 0)
    {
        func_8005DC1C(0x57A, &romper->position_18, Rng_TestProbabilityBits(4) + 0x78, 0);
        romper->properties_E4.romper.field_11A = 0;
    }

    if (romper->model_0.anim_4.status_0 != 11 &&
        romper->properties_E4.romper.field_116 == 0 &&
        romper->health_B0 > Q12(0.0f))
    {
        if (romper->properties_E4.romper.field_11C != 0)
        {
            romper->properties_E4.romper.field_11C -= g_DeltaTime0;
            if (romper->properties_E4.romper.field_11C < 0)
            {
                romper->properties_E4.romper.field_11C = 0;
            }
        }
        else
        {
            if (romper->health_B0 <= 0xE1000)
            {
                var_s1 = ((FP_TO(romper->health_B0, Q12_SHIFT) / 0x1C2000) >> 6) + 0x38;
            }
            else
            {
                var_s1 = 120;
            }

            func_8005DC1C(0x57C, &romper->position_18, (var_s1 + Rng_TestProbabilityBits(4)) >> 1, 0);
            romper->properties_E4.romper.field_11C = Rng_GenerateInt(0x4800, 0x67FF);
        }
    }
}

void sharedFunc_800CABF8_1_s05(s32 idx, bool arg1)
{
    s32   rand;
    q3_12 randAngle;

    if (sharedData_800D8568_1_s05.field_1 == 1 &&
        Rng_GenerateUInt(0, 4095) < sharedData_800D8568_1_s05.field_10 &&
        Rng_GenerateUInt(0, 7) == 0)
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 12;
        return;
    }

    if ((sharedData_800D8568_1_s05.flags_0 & (1 << 4)) && Rng_GenerateUInt(0, 3) == 0)
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 12;
        return;
    }

    rand      = Rng_GenerateInt(0, (s16)sharedData_800D8568_1_s05.field_1C - 1);
    randAngle = Rng_GenerateUInt(0, FP_ANGLE(360.0f) - 1);

    if ((sharedData_800D8568_1_s05.flags_0 & (1 << 2)) && Rng_GenerateUInt(0, 63) == 0)
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 10;
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 8;
    }

    if (arg1 == true)
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 = Rng_GenerateUInt(0, 15);
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 = Rng_GenerateUInt(0, 4095);
    }

    if (sharedData_800D8568_1_s05.flags_0 & (1 << 4))
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = MIN((((sharedData_800D8568_1_s05.field_3 << 4) * rand) / (s16)sharedData_800D8568_1_s05.field_1C) +
                                                                 (u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 +
                                                                 sharedData_800D8568_1_s05.field_10 +
                                                                 Rng_GenerateUInt(0, 1023),
                                                                 4095);
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = MIN((((sharedData_800D8568_1_s05.field_3 << 4) * rand) / (s16)sharedData_800D8568_1_s05.field_1C) +
                                                                 (u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 +
                                                                 sharedData_800D8568_1_s05.field_10,
                                                                 4095);
    }

    sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0 = (u8)Rng_Rand16() | 0x80; // TODO: Same as `Rng_Rand16() - 128`?
    sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_1 = (u8)Rng_Rand16() | 0x80;

    sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 = Rng_GenerateUInt(0, 4095);

    if (sharedData_800D8568_1_s05.flags_0 & (1 << 0))
    {
        sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = FP_FROM(rand * Math_Cos(randAngle), Q12_SHIFT);
        sharedData_800DFB7C_0_s00[idx].field_4.vz_4 = FP_FROM(rand * Math_Sin(randAngle), Q12_SHIFT);
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = Rng_GenerateInt(-sharedData_800D8568_1_s05.field_18, sharedData_800D8568_1_s05.field_18 - 1);
        sharedData_800DFB7C_0_s00[idx].field_4.vz_4 = Rng_GenerateInt(-sharedData_800D8568_1_s05.field_1A, sharedData_800D8568_1_s05.field_1A - 1);
    }

    sharedData_800DFB7C_0_s00[idx].vy_8    = sharedData_800D8568_1_s05.field_14 + FP_FROM((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 * sharedData_800D8568_1_s05.field_16, Q12_SHIFT);
    sharedData_800DFB7C_0_s00[idx].field_B = Rng_GenerateUInt(0, 1) + (Rng_GenerateInt(0, 2) * 2);
}

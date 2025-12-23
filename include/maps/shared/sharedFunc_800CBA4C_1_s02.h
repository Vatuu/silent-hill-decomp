void sharedFunc_800CBA4C_1_s02(s32 idx, s32 arg1, s32 arg2)
{
    s32 temp_a1;
    s32 var_s2;
    s32 temp;

    var_s2 = arg2;

    if (arg1 == 2)
    {
        var_s2                                              = Rng_Rand16() % sharedData_800E30C8_1_s02.field_78;
        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0 = Rng_Rand16() % sharedData_800E30C8_1_s02.field_28[var_s2];
    }
    else
    {
        var_s2                                               = var_s2 % sharedData_800E30C8_1_s02.field_78;
        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0 = 0;
    }

    sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = sharedData_800E30C8_1_s02.field_0[var_s2];
    sharedData_800DFB7C_0_s00[idx].vy_8         = sharedData_800E30C8_1_s02.field_10[var_s2];
    sharedData_800DFB7C_0_s00[idx].field_4.vz_4 = sharedData_800E30C8_1_s02.field_18[var_s2];

    if (sharedData_800E30C8_1_s02.field_30[var_s2] == 0)
    {
        if (arg1 == 2)
        {
            sharedData_800DFB7C_0_s00[idx].field_0.vx_0 += FP_MULTIPLY(sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0, Math_Sin(sharedData_800E30C8_1_s02.field_34[var_s2]), Q12_SHIFT);
            sharedData_800DFB7C_0_s00[idx].field_4.vz_4 += FP_MULTIPLY(sharedData_800DFB7C_0_s00[idx].field_10.s_3.field_0, Math_Cos(sharedData_800E30C8_1_s02.field_34[var_s2]), Q12_SHIFT);
        }

        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 = ((sharedData_800E30C8_1_s02.field_6c[var_s2] * (Rng_TestProbabilityBits(6) + 0x60)) >> 7);
    }
    else
    {
        if (arg1 == 2)
        {
            sharedData_800DFB7C_0_s00[idx].vy_8 += sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_0;
        }

        sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 = Rng_TestProbabilityBits(5) + 0x70;
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2  = 0;
    }

    temp_a1 = Rng_Rand16() % 3;
    temp    = 4;

    sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_0 = (temp_a1 ? (temp_a1 + 1) : 0) + (var_s2 * temp);
}

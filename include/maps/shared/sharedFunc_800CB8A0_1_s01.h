void sharedFunc_800CB8A0_1_s01(s32 idx)
{
    s32    rngB;
    q19_12 angleZ;
    s16    rngX;

    if (sharedData_800DEE50_1_s01.field_2 == 0)
    {
        sharedData_800DD5B0_1_s01[idx].field_A = 14;
    }

    if (sharedData_800DEE50_1_s01.field_0 == 0)
    {
        rngX                                = (Rng_Rand16() % sharedData_800DEE50_1_s01.field_A);
        angleZ                              = Q12_FRACT(Rng_Rand16());
        sharedData_800DD5B0_1_s01[idx].field_0.vx_0 = (s32)(rngX * Math_Cos(angleZ)) >> Q12_SHIFT;
        sharedData_800DD5B0_1_s01[idx].field_4.vz_4 = (s32)(rngX * Math_Sin(angleZ)) >> Q12_SHIFT;
    }
    else
    {
        sharedData_800DD5B0_1_s01[idx].field_0.vx_0 = (Rng_Rand16() % (sharedData_800DEE50_1_s01.field_A * 2)) - sharedData_800DEE50_1_s01.field_A;
        sharedData_800DD5B0_1_s01[idx].field_4.vz_4 = (Rng_Rand16() % (sharedData_800DEE50_1_s01.field_A * 2)) - sharedData_800DEE50_1_s01.field_A;
    }

    sharedData_800DD5B0_1_s01[idx].vy_8            = sharedData_800DEE50_1_s01.field_8;
    rngB                                           = Rng_Rand16();
    sharedData_800DD5B0_1_s01[idx].field_C.field_0 = 0;
    sharedData_800DD5B0_1_s01[idx].field_B         = rngB - (rngB / 3) * 3;
}

bool sharedFunc_800CBA38_1_s01(s32 idx)
{
    sharedData_800DFB7C_0_s00[idx].field_C.field_0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, ((Rng_Rand16() % FP_ANGLE(144.0f)) + FP_ANGLE(288.0f)), Q12_SHIFT);

    if ((FP_TO((sharedData_800DEE50_1_s01.field_6 - sharedData_800DEE50_1_s01.field_8), Q12_SHIFT) / sharedData_800DEE50_1_s01.field_C) < sharedData_800DFB7C_0_s00[idx].field_C.field_0)
    {
        sharedFunc_800CB8A0_1_s01(idx);
        return true;
    }

    return false;
}

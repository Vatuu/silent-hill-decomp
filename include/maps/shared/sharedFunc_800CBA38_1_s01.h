bool sharedFunc_800CBA38_1_s01(s32 idx)
{
    sharedData_800DFB7C_0_s00[idx].field_C.field_0 += Q12_MULT_PRECISE(g_DeltaTime, ((Rng_Rand16() % Q12_ANGLE(144.0f)) + Q12_ANGLE(288.0f)));

    if (Q12_DIV(sharedData_800DEE50_1_s01.field_6 - sharedData_800DEE50_1_s01.field_8, sharedData_800DEE50_1_s01.field_C) < sharedData_800DFB7C_0_s00[idx].field_C.field_0)
    {
        sharedFunc_800CB8A0_1_s01(idx);
        return true;
    }

    return false;
}

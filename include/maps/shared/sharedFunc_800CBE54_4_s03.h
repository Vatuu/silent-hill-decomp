void sharedFunc_800CBE54_4_s03(VECTOR3* arg0, s32 arg1)
{
    s32 idx;
    s32 i;

    for (i = 0; i < 12; i++)
    {
        idx = func_8005E7E0(34);
        if (idx == NO_VALUE)
        {
            break;
        }

        sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = Rng_AddGeneratedUInt(arg0->vx, Q12(-0.25f), Q12(0.25f) - 1);
        sharedData_800DFB7C_0_s00[idx].vy_8         = Rng_AddGeneratedUInt(arg0->vy, Q12(-0.25f), Q12(0.25f) - 1);

        sharedData_800DFB7C_0_s00[idx].field_4.vz_4        = Rng_AddGeneratedUInt(arg0->vz, Q12(-0.25f), Q12(0.25f) - 1);
        sharedData_800DFB7C_0_s00[idx].field_B             = arg1;
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = Rng_GenerateInt(0, Q12(0.35f) - 1);

        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2  = Q12_MULT_PRECISE(D_800C4418.field_6, Rng_GenerateUInt(Q12(0.5f), Q12_CLAMPED(1.0f)));
        sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0 = Rng_GenerateUInt(0x40, 0x80 - 1);
    }
}

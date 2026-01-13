void sharedFunc_800CBE54_4_s03(VECTOR3* arg0, s32 arg1)
{
    s32 idx;
    s32 i;

    for (i = 0; i < 12; i++)
    {
        idx = func_8005E7E0(0x22);

        if (idx == -1)
        {
            break;
        }

        sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = (arg0->vx + Rng_TestProbabilityBits(11)) - 0x400;
        sharedData_800DFB7C_0_s00[idx].vy_8         = (arg0->vy + Rng_TestProbabilityBits(11)) - 0x400;

        sharedData_800DFB7C_0_s00[idx].field_4.vz_4        = (arg0->vz + Rng_TestProbabilityBits(11)) - 0x400;
        sharedData_800DFB7C_0_s00[idx].field_B             = arg1;
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = Rng_GenerateInt(0, 1432);

        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2  = Q12_MULT_PRECISE(D_800C4418.field_6, Rng_TestProbabilityBits(11) + 0x800);
        sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0 = Rng_TestProbabilityBits(6) + 0x40;
    }
}
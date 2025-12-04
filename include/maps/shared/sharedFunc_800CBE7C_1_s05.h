void sharedFunc_800CBE7C_1_s05(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 i;

    i = func_8005E7E0(7);

    if (i != NO_VALUE)
    {
        sharedData_800E1FF8_1_s02[i].field_0.vx_0         = ((arg0 + (Rng_Rand16() & 63)) - 32) * 16;
        sharedData_800E1FF8_1_s02[i].vy_8                 = (arg1 + (Rng_Rand16() & 63)) * 16;
        sharedData_800E1FF8_1_s02[i].field_4.vz_4         = ((arg2 + (Rng_Rand16() & 63)) - 32) * 16;
        sharedData_800E1FF8_1_s02[i].field_B              = 0;
        sharedData_800E1FF8_1_s02[i].field_C.s_0.field_0  = 0;
        sharedData_800E1FF8_1_s02[i].field_C.s_0.field_2  = arg3;
        sharedData_800E1FF8_1_s02[i].field_10.s_1.field_0 = arg4;
        sharedData_800E1FF8_1_s02[i].field_10.s_1.field_2 = (Rng_Rand16() & 31) + 16;
        sharedData_800E1FF8_1_s02[i].field_10.s_1.field_3 = Rng_Rand16() & 15;
    }
}

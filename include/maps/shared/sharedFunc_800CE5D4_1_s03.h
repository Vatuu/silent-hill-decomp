void sharedFunc_800CE5D4_1_s03(VECTOR3* arg0, u16 arg1, u16 arg2, u32 arg3)
{
    s32 temp_v0;

    temp_v0 = func_8005E7E0(35);
    if (temp_v0 != NO_VALUE)
    {
        sharedData_800E2120_1_s03[temp_v0].field_0 = Q12_TO_Q8(arg0->vx);
        sharedData_800E2120_1_s03[temp_v0].field_8 = Q12_TO_Q8(arg0->vy);
        sharedData_800E2120_1_s03[temp_v0].field_4 = Q12_TO_Q8(arg0->vz);
        sharedData_800E2120_1_s03[temp_v0].field_C = arg1 / 2;
        sharedData_800E2120_1_s03[temp_v0].field_E = Q12_TO_Q8(arg2);
        sharedData_800E2120_1_s03[temp_v0].field_B = arg3;
    }
}

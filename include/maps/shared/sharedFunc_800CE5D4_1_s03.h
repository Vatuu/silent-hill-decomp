void sharedFunc_800CE5D4_1_s03(VECTOR3* arg0, u16 arg1, u16 arg2, u32 arg3)
{
    s32 idx;

    idx = func_8005E7E0(35);
    if (idx != NO_VALUE)
    {
        sharedData_800E1FF8_1_s02[idx].vx_0            = Q12_TO_Q8(arg0->vx);
        sharedData_800E1FF8_1_s02[idx].vy_8            = Q12_TO_Q8(arg0->vy);
        sharedData_800E1FF8_1_s02[idx].vz_4            = Q12_TO_Q8(arg0->vz);
        sharedData_800E1FF8_1_s02[idx].field_C.s_0.field_0 = arg1 / 2;
        sharedData_800E1FF8_1_s02[idx].field_C.s_0.field_2 = Q12_TO_Q8(arg2);
        sharedData_800E1FF8_1_s02[idx].field_B         = arg3;
    }
}

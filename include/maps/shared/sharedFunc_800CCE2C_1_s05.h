void sharedFunc_800CCE2C_1_s05(s32 arg0, s32 arg1, s32 posX0, s32 posY0, s32 posZ0, s32 posX1, s32 posY1, s32 posZ1)
{
    s32 idx0;
    s32 idx1;

    idx0 = func_8005E7E0(5);
    if (idx0 == NO_VALUE)
    {
        return;
    }

    idx1 = func_8005E7E0(6);
    if (idx1 == NO_VALUE)
    {
        sharedData_800DFB7C_0_s00[idx0].field_A = 0;
        return;
    }

    sharedData_800DFB7C_0_s00[idx0].field_B             = arg0;
    sharedData_800DFB7C_0_s00[idx0].field_C.s_0.field_0 = idx1;
    sharedData_800DFB7C_0_s00[idx0].field_C.s_1.field_2 = arg1;
    sharedData_800DFB7C_0_s00[idx0].field_0.vx_0        = posX0;
    sharedData_800DFB7C_0_s00[idx0].vy_8                = posY0;
    sharedData_800DFB7C_0_s00[idx0].field_4.vz_4        = posZ0;

    sharedData_800DFB7C_0_s00[idx1].field_0.vx_0 = posX1;
    sharedData_800DFB7C_0_s00[idx1].vy_8         = posY1;
    sharedData_800DFB7C_0_s00[idx1].field_4.vz_4 = posZ1;
}

void sharedFunc_800CB0A4_4_s03(VECTOR3* arg0, VECTOR3* arg1)
{
    s32 idx;

    idx = func_8005E7E0(0x21);
    if (idx != NO_VALUE)
    {
        sharedData_800E1FF8_1_s02[idx].vx_0            = arg0->vx;
        sharedData_800E1FF8_1_s02[idx].vy_8            = arg0->vy;
        sharedData_800E1FF8_1_s02[idx].vz_4            = arg0->vz;
        sharedData_800E1FF8_1_s02[idx].field_C.field_0 = ratan2(arg1->vx - arg0->vx, arg1->vz - arg0->vz);
        sharedData_800E1FF8_1_s02[idx].field_E.field_0 = ratan2(arg1->vy - arg0->vy, Math_Vector2MagCalc(arg1->vx - arg0->vx, arg1->vz - arg0->vz));

        do {} while (0); // @hack

        sharedData_800E1FF8_1_s02[idx].field_10.s_0.field_0 = D_800C4420;
        sharedData_800E1FF8_1_s02[idx].field_B              = 0;
        sharedData_800E1FF8_1_s02[idx].field_10.s_0.field_2 = 0x1000;
    }
}

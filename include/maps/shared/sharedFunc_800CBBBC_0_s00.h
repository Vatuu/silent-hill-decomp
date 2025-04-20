s32 sharedFunc_800CBBBC_0_s00()
{
    s32 distance;
    s32 var_v1;

    distance = SquareRoot0(
        (ABS_DIFF(sharedData_800E323C_0_s00.vx, sharedData_800E324C_0_s00.vx) * ABS_DIFF(sharedData_800E323C_0_s00.vx, sharedData_800E324C_0_s00.vx)) + 
        (ABS_DIFF(sharedData_800E323C_0_s00.vz, sharedData_800E324C_0_s00.vz) * ABS_DIFF(sharedData_800E323C_0_s00.vz, sharedData_800E324C_0_s00.vz))
    );
    
    var_v1 = ABS_DIFF(sharedData_800E3260_0_s00, sharedData_800E0C6E_0_s00);
    
    if (distance > 10000 || var_v1 > 512)
    {
        return 1;
    }
    return 0;
}

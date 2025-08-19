bool sharedFunc_800CBBBC_0_s00()
#ifdef SHARED_FUNC_IMPL
{
    s32 dist;
    s32 var_v1;

    dist = SquareRoot0(SQUARE(ABS_DIFF(sharedData_800E323C_0_s00.vx, sharedData_800E324C_0_s00.vx)) +
                       SQUARE(ABS_DIFF(sharedData_800E323C_0_s00.vz, sharedData_800E324C_0_s00.vz)));

    var_v1 = ABS_DIFF(sharedData_800E3260_0_s00, sharedData_800E0C6E_0_s00);

    if (dist > 10000 || var_v1 > 512)
    {
        return true;
    }

    return false;
}
#else
;
#endif

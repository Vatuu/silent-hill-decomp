void sharedFunc_800D01BC_0_s00(u16* arg0, VECTOR3* arg1, s32 arg2)
{
    s32 temp_a0;
    s32 temp_s3;

    temp_a0 = (*arg0 % FP_TO(arg2, Q12_SHIFT)) + ((s32)Rng_Rand16() % FP_TO(arg2, Q12_SHIFT));
    temp_s3 = temp_a0 - FP_TO(arg2, Q12_SHIFT);
    arg1->vx = temp_s3;
    temp_s3 = FP_TO(arg2, Q12_SHIFT) - abs(temp_s3);
    arg1->vz = ((*arg0 % temp_s3) + ((s32)Rng_Rand16(temp_a0) % temp_s3)) - temp_s3;
}

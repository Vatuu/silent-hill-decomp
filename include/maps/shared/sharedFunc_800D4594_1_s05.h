void sharedFunc_800D4594_1_s05(s_sharedFunc_800D4594_1_s05* arg0, s32 posX, s32 posZ, VECTOR3* vec0, VECTOR3* vec1)
{
    s16 temp_s0;
    s16 temp_v0_6;
    s32 temp_a1;
    s32 temp_s0_2;
    s32 temp_s2;
    s32 temp_v0;

    temp_s0       = ratan2(vec1->vx - vec0->vx, vec1->vz - vec0->vz) + FP_ANGLE(90.0f);
    temp_s0_2     = posX + Math_Sin(temp_s0);
    temp_v0       = Math_Cos(temp_s0);
    temp_v0_6     = (((posX - vec0->vx) >> 2) * ((vec1->vz - vec0->vz) >> 2)) - (((posZ - vec0->vz) >> 2) * ((vec1->vx - vec0->vx) >> 2)) < 1;
    arg0->field_D = temp_v0_6;

    if ((((vec0->vx - posX) >> 2) * (temp_v0 >> 2)) - (((vec0->vz - posZ) >> 2) * ((temp_s0_2 - posX) >> 2)) < 0)
    {
        arg0->field_0 = SquareRoot0(SQUARE((posX - vec0->vx) >> 3) + SQUARE((posZ - vec0->vz) >> 3)) << 3;
        arg0->field_4 = vec0->vx;
        arg0->field_8 = vec0->vz;
        arg0->field_C = 0;
    }
    else if ((((vec1->vx - posX) >> 2) * (temp_v0 >> 2)) - (((vec1->vz - posZ) >> 2) * ((temp_s0_2 - posX) >> 2)) > 0)
    {
        arg0->field_0 = SquareRoot0(SQUARE((posX - vec1->vx) >> 3) + SQUARE((posZ - vec1->vz) >> 3)) << 3;
        arg0->field_4 = vec1->vx;
        arg0->field_8 = vec1->vz;
        arg0->field_C = 1;
    }
    else
    {
        temp_s0       = ratan2(vec1->vx - vec0->vx, vec1->vz - vec0->vz);
        temp_s2       = SquareRoot0(SQUARE((posX - vec0->vx) >> 3) + SQUARE((posZ - vec0->vz) >> 3)) << 3;
        temp_v0_6     = ratan2(posX - vec0->vx, posZ - vec0->vz) - temp_s0;
        arg0->field_0 = ABS(FP_FROM(temp_s2 * Math_Sin(temp_v0_6), Q12_SHIFT));
        temp_s2       = FP_FROM(temp_s2 * Math_Cos(temp_v0_6), Q12_SHIFT);
        arg0->field_4 = FP_FROM(temp_s2 * Math_Sin(temp_s0), Q12_SHIFT) + vec0->vx;
        arg0->field_8 = FP_FROM(temp_s2 * Math_Cos(temp_s0), Q12_SHIFT) + vec0->vz;
        arg0->field_C = 2;
    }
}

void sharedFunc_800D8714_0_s01(s_SubCharacter* airScreamer, q19_12 angle0, q19_12 angle1)
{
    q19_12           angle;
    q19_12           dist;
    q19_12           temp_v0;
    s32              idx;
    q19_12           offsetX;
    q19_12           offsetZ;
    s16*             ptr;
    s_func_800D2E04* base;

    angle = angle1;
    idx = sharedFunc_800D4A80_0_s01(airScreamer);
    base = &sharedData_800CAA98_0_s01;
    temp_v0 = base->field_D5C[idx][1];
    airScreamer->field_C8.field_2 = base->field_D5C[idx][0];

    if (angle0 == FP_ANGLE(0.0f)) 
    {
        airScreamer->field_D8.offsetX_4 = Q12(0.0f);
        airScreamer->field_D8.offsetZ_6 = Q12(0.0f);
        airScreamer->field_D4.radius_0   = temp_v0;
        return;
    }

    dist = temp_v0 - Q12(0.4f);
    if (dist < Q12(0.0f))
    {
        dist = Q12(0.0f);
    }

    if (angle0 < FP_ANGLE(0.0f))
    {
        angle ^= 0x800;
    }

    offsetX = FP_MULTIPLY_PRECISE(dist, Math_Sin(angle), Q12_SHIFT);
    offsetZ = FP_MULTIPLY_PRECISE(dist, Math_Cos(angle), Q12_SHIFT);

    airScreamer->field_D8.offsetX_4 = offsetX;
    airScreamer->field_D8.offsetZ_6 = offsetZ;
    airScreamer->field_D4.radius_0   = Q12(0.4f);
}

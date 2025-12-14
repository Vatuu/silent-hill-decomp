void sharedFunc_800D8714_0_s01(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    q19_12           angle;
    q19_12           dist;
    q19_12           temp_v0;
    s32              idx;
    q19_12           offsetX;
    q19_12           offsetZ;
    s16*             ptr;
    s_func_800D2E04* base;

    angle = arg2;
    idx = sharedFunc_800D4A80_0_s01(chara);
    base = &sharedData_800CAA98_0_s01;
    temp_v0 = base->field_D5C[idx][1];
    chara->field_C8.field_2 = base->field_D5C[idx][0];

    if (arg1 == 0) 
    {
        chara->field_D8.offsetX_4 = Q12(0.0f);
        chara->field_D8.offsetZ_6 = Q12(0.0f);
        chara->field_D4.field_0   = temp_v0;
        return;
    }

    dist = temp_v0 - Q12(0.4f);
    if (dist < Q12(0.0f))
    {
        dist = Q12(0.0f);
    }

    if (arg1 < 0)
    {
        angle ^= 0x800;
    }

    offsetX = FP_MULTIPLY_PRECISE(dist,  Math_Sin(angle), Q12_SHIFT);
    offsetZ = FP_MULTIPLY_PRECISE(dist,  Math_Cos(angle), Q12_SHIFT);

    chara->field_D8.offsetX_4 = offsetX;
    chara->field_D8.offsetZ_6 = offsetZ;
    chara->field_D4.field_0   = Q12(0.4f);
}

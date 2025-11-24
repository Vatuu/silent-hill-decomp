void sharedFunc_800DE7E0_2_s00(s_SubCharacter* chara)
{
    s32 angle;
    s32 temp_s3;
    s32 var_s4;
    s32 var_s6;

    if (chara->properties_E4.unk0.field_E8_4 != 0)
    {
        var_s6 = Q12(6.0f);
        var_s4 = Q12(4.0f);
    }
    else
    {
        var_s6 = Q12(5.0f);
        var_s4 = Q12(3.0f);
    }

    func_800803FC(&sharedData_800F21DC_2_s00, chara->field_40);

    temp_s3 = Math_Distance2dGet(&sharedData_800F21DC_2_s00, &chara->position_18);

    angle  = func_80080478(&sharedData_800F21DC_2_s00, &chara->position_18);
    angle += FP_MULTIPLY_PRECISE(func_80080514() - FP_ANGLE(180.0f), FP_ANGLE(120.0f), Q12_SHIFT);

    temp_s3 = (temp_s3 - var_s4) / 2;

    sharedData_800F21DC_2_s00.vx += FP_MULTIPLY_PRECISE(temp_s3, Math_Sin(angle), Q12_SHIFT);
    sharedData_800F21DC_2_s00.vz += FP_MULTIPLY_PRECISE(temp_s3, Math_Cos(angle), Q12_SHIFT);

    sharedFunc_800DE6A8_2_s00(chara, &sharedData_800F21DC_2_s00, var_s6);
    sharedFunc_800D4E84_0_s01(chara);
}

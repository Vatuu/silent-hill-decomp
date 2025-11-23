bool sharedFunc_800DC67C_2_s00(s_SubCharacter* chara)
{
    if (chara->properties_E4.unk0.field_E8_0 == 1)
    {
        func_800803FC(&sharedData_800F217C_2_s00, chara->field_40);
        return Math_Distance2dGet(&chara->position_18, &sharedData_800F217C_2_s00) > Q12(40.0f);
    }

    return false;
}

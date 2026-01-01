bool sharedFunc_800DC67C_2_s00(s_SubCharacter* airScreamer)
{
    #define airScreamerProps airScreamer->properties_E4.airScreamer

    if (airScreamerProps.field_E8_0 == 1)
    {
        func_800803FC(&sharedData_800F217C_2_s00, airScreamer->field_40);
        return Math_Distance2dGet(&airScreamer->position_18, &sharedData_800F217C_2_s00) > Q12(40.0f);
    }

    return false;

    #undef airScreamerProps
}

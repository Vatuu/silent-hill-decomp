void sharedFunc_800DDE14_2_s00(s_SubCharacter* airScreamer)
{
    q19_12 angle;
    q19_12 radius;
    q19_12 distMin;
    q19_12 distMax;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    if (airScreamerProps.field_E8_4 != 0)
    {
        distMax = Q12(5.0f);
        distMin = Q12(3.0f);
    }
    else
    {
        distMax = Q12(4.0f);
        distMin = Q12(2.0f);
    }

    func_800803FC(&sharedData_800F21BC_2_s00, airScreamer->field_40);

    radius = Math_Distance2dGet(&sharedData_800F21BC_2_s00, &airScreamer->position_18);

    angle  = func_80080478(&sharedData_800F21BC_2_s00, &airScreamer->position_18);
    angle += FP_MULTIPLY_PRECISE(Rng_RandQ12() - FP_ANGLE(180.0f), FP_ANGLE(120.0f), Q12_SHIFT);

    radius = (radius - distMin) / 2;

    sharedData_800F21BC_2_s00.vx += FP_MULTIPLY_PRECISE(radius, Math_Sin(angle), Q12_SHIFT);
    sharedData_800F21BC_2_s00.vz += FP_MULTIPLY_PRECISE(radius, Math_Cos(angle), Q12_SHIFT);

    sharedFunc_800DE034_2_s00(airScreamer, &sharedData_800F21BC_2_s00, distMax);
    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef airScreamerProps
}

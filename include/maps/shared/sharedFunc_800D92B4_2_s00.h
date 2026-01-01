void sharedFunc_800D92B4_2_s00(s_SubCharacter* airScreamer)
{
    #define airScreamerProps airScreamer->properties_E4.airScreamer

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamerProps.timer_120 = (Rng_RandQ12() * 2) + Q12(0.5f);

            sharedFunc_800D529C_0_s01(airScreamer,
                                      Q12(4.0f),
                                      airScreamer->rotation_24.vy + FP_MULTIPLY_PRECISE(Rng_RandQ12() - FP_ANGLE(180.0f), FP_ANGLE(45.0f), Q12_SHIFT));

            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 1:
            if (airScreamerProps.timer_120 == Q12(0.0f) ||
                Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_F8) < Q12(2.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;
    }

    sharedFunc_800E012C_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case 0:
            break;

        case 1:
        case 2:
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2= AirScreamerControl_32;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }

    #undef airScreamerProps
}

void sharedFunc_800D6400_2_s00(s_SubCharacter* airScreamer)
{
    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedFunc_800DDF74_2_s00(airScreamer, Q12(0.5f), airScreamer->rotation_24.vy);
    sharedFunc_800DF2D0_2_s00(airScreamer);
    airScreamer->flags_3E &= ~CharaFlag_Unk3;

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch ((u32)airScreamer->properties_E4.unk0.field_E8_0)
            {
                case 0:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_4;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case 1:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_5;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case 3:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_5;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
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

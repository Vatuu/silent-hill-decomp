void Ai_AirScreamerControl_28(s_SubCharacter* airScreamer)
{
    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedFunc_800D529C_0_s01(airScreamer, Q12(0.5f), airScreamer->rotation_24.vy);
    sharedFunc_800D598C_0_s01(airScreamer);
    airScreamer->flags_3E &= ~CharaFlag_Unk3;

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            // @hack Explicit `u32` cast needed for match.
            switch ((u32)airScreamerProps.field_E8_0)
            {
                case 0:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_18;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case 1:
                case 3:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_19;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            return;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }

    #undef airScreamerProps
}

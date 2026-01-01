void sharedFunc_800DB8AC_2_s00(s_SubCharacter* airScreamer)
{
    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedFunc_800DEC84_2_s00(airScreamer, Q12(0.5f), airScreamer->rotation_24.vy);
    sharedFunc_800E021C_2_s00(airScreamer, 1, 1);
    airScreamer->flags_3E &= ~CharaFlag_Unk3;

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            // @hack Explicit `u32` cast needed for match.
            switch ((u32)airScreamer->properties_E4.unk0.field_E8_0)
            {
                case 0:
                    airScreamer->model_0.controlState_2     = AirScreamerControl_33;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case 1:
                case 3:
                    airScreamer->model_0.controlState_2     = AirScreamerControl_34;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2               = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2     = AirScreamerControl_45;
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

void Ai_AirScreamerControl_3(s_SubCharacter* airScreamer)
{
    bool cond;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    if (airScreamer->model_0.stateStep_3 == AirScreamerStateStep_0)
    {
        sharedFunc_800DDF74_2_s00(airScreamer, Q12(0.1f), airScreamer->rotation_24.vy);
        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
    }

    sharedFunc_800DF2D0_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            if (sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2)
            {
                if (!airScreamerProps.field_E8_8)
                {
                    cond = sharedFunc_800D3814_0_s01(airScreamer) >= Q12(2.0f);
                }
                else
                {
                    cond = true;
                }

                if (cond)
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    airScreamer->flags_3E              |= CharaFlag_Unk3;
                    airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                }
            }
            else
            {
                if (airScreamerProps.flags_11C & AirScreamerFlag_31)
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                }
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

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

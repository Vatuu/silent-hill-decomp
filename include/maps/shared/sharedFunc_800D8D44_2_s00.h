void sharedFunc_800D8D44_2_s00(s_SubCharacter* airScreamer)
{
    s32  temp_s2;
    s32  var_a0;
    s32  var_s1;
    s32  var_s1_2;
    u32  animStatus;
    u32  stateStep;
    bool new_var;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus             = airScreamer->model_0.anim_4.status_0;
    new_var                = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    var_s1                 = 0;
    temp_s2                = new_var;
    stateStep              = airScreamer->model_0.stateStep_3;
    airScreamer->flags_3E |= CharaFlag_Unk3;

    // Handle state step.
    switch (stateStep)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_7, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_7, false))
            {
                airScreamer->model_0.stateStep_3                           = AirScreamerStateStep_2;
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_7, true))
            {
                var_s1 = 1;
            }
            break;
    }

    sharedFunc_800D5D80_0_s01(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case 0:
        case 1:
            if (var_s1 != 0)
            {
                var_s1_2 = 0;
                if (airScreamer->properties_E4.airScreamer.field_E8_4)
                {
                    var_s1_2 = Q12(0.1f);
                }

                if (airScreamer->properties_E4.airScreamer.field_E8_0 == 3)
                {
                    sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.7f));
                }

                if (temp_s2 != 0)
                {
                    if (airScreamer->properties_E4.airScreamer.field_E8_8 == 5)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                        if (Rng_RandQ12() < ((FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1_2 * 2)))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;
                    }

                    airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_RandQ12() > ((FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1_2 * 2)))
                    {
                        airScreamer->properties_E4.airScreamer.field_E8_8 = 5;
                    }
                    else
                    {
                        airScreamer->properties_E4.airScreamer.field_E8_8 = 3;
                    }
                    break;
                }

                switch (airScreamer->properties_E4.airScreamer.field_E8_8)
                {
                    case 3:
                        airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                        if (Rng_RandQ12() < (Q12(0.5f) - (var_s1_2 * 3)))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 2;
                        }
                        break;

                    case 2:
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                        if (Rng_RandQ12() > ((FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1_2 * 2)))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 5;
                        }
                        else if (Rng_RandQ12() < ((var_s1_2 * 3) + Q12(0.3f)))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;

                    case 5:
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                        if (Rng_RandQ12() < FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;

                    case 1:
                    case 4:
                        if (Rng_RandQ12() >= ((var_s1_2 * 5) + Q12(0.2f)))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                        if (Rng_RandQ12() < ((var_s1_2 * 3) + Q12(0.5f)))
                        {
                            var_a0 = 2;
                        }
                        else
                        {
                            var_a0 = 5;
                        }

                        airScreamer->properties_E4.airScreamer.field_E8_8 = var_a0;
                        break;

                    default:
                    case 0:
                        if (airScreamer->properties_E4.airScreamer.field_E8_0 == 3)
                        {
                            var_s1_2 = Q12(1.0f);
                        }

                        if (Rng_RandQ12() >= ((var_s1_2 * 3) + Q12(0.4f)))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                        if (Rng_RandQ12() < ((var_s1_2 * 2) + Q12(0.6f)))
                        {
                            var_a0 = 2;
                        }
                        else
                        {
                            var_a0 = 5;
                        }

                        airScreamer->properties_E4.airScreamer.field_E8_8 = var_a0;
                        break;
                }
            }
            break;

        case 2:
            airScreamer->model_0.controlState_2                        = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3                           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
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

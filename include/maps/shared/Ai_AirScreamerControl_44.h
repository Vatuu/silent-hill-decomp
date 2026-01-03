// Very similar to `Ai_AirScreamerControl_16`, changes here should be copied there.
void Ai_AirScreamerControl_44(s_SubCharacter* airScreamer)
{
    s32    animStatus;
    bool   field14C_2;
    bool   field14C_2_tmp;
    bool   cond;
    s32    var_a0;
    q19_12 var_s1;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus       = airScreamer->model_0.anim_4.status_0;
    field14C_2_tmp   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    airScreamer->flags_3E |= CharaFlag_Unk3;
    field14C_2       = field14C_2_tmp;
    cond             = false;

    // Handle state step. @hack Explicit `u32` cast needed for match.
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_8, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_8, false))
            {
                airScreamer->model_0.stateStep_3           = AirScreamerStateStep_2;
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_8, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800E041C_2_s00(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case AirScreamerDamage_None:
        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            if (!cond)
            {
                break;
            }

            var_s1 = airScreamerProps.field_E8_4 ? Q12(0.1f) : Q12(0.0f);

            if (airScreamerProps.field_E8_0 == 3)
            {
                sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.7f));
            }

            if (field14C_2)
            {
                if (airScreamerProps.field_E8_8 == 5)
                {
                    airScreamer->model_0.controlState_2     = AirScreamerControl_42;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability((FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    break;
                }
                else
                {
                    airScreamer->model_0.controlState_2     = AirScreamerControl_38;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    // TODO: Can `Rng_TestProbability` fit?
                    if (Rng_RandQ12() <= ((FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    else
                    {
                        airScreamerProps.field_E8_8 = 5;
                    }
                }
                break;
            }

            switch (airScreamerProps.field_E8_8)
            {
                case 3:
                    airScreamer->model_0.controlState_2     = AirScreamerControl_41;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability(((Q12(0.5f) - (var_s1 * 3)))))
                    {
                        airScreamerProps.field_E8_8 = 2;
                    }
                    break;

                case 2:
                    airScreamer->model_0.controlState_2     = AirScreamerControl_36;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_RandQ12() > (FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 5;
                    }
                    else if (Rng_TestProbability(Q12(0.3f) + (var_s1 * 3)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    break;

                case 5:
                    airScreamer->model_0.controlState_2     = AirScreamerControl_42;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability(FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    break;

                case 1:
                case 4:
                    if (Rng_TestProbability(Q12(0.2f) + (var_s1 * 5)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12(0.5f) + (var_s1 * 3)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    airScreamerProps.field_E8_8 = var_a0;
                    break;

                case 0:
                default:
                    if (airScreamerProps.field_E8_0 == 3)
                    {
                        var_s1 = Q12(1.0f);
                    }

                    if (Rng_TestProbability(Q12(0.4f) + (var_s1 * 3)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12(0.6f) + (var_s1 * 2)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    airScreamerProps.field_E8_8 = var_a0;
                    break;
            }
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2     = AirScreamerControl_45;
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

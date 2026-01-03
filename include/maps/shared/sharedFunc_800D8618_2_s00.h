void sharedFunc_800D8618_2_s00(s_SubCharacter* airScreamer)
{
    s32  animStatus;
    bool field14C_2;
    bool field14C_1;
    bool new_var;
    bool new_var2;
    bool temp_a0;
    bool switchCond;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    switchCond = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    new_var    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_1 = new_var;
    field14C_2 = new_var2;

    temp_a0 = sharedFunc_800DC50C_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            sharedFunc_800DEBCC_2_s00(airScreamer);

        case AirScreamerStateStep_1:
            airScreamerProps.timer_120 = Q12(4.0f);
            airScreamer->model_0.stateStep_3                     = AirScreamerStateStep_2;
            break;

        case AirScreamerStateStep_2:
            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(0.5f))
            {
                sharedFunc_800DE6A8_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.5f));
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                sharedFunc_800DE6A8_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.5f));
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = true;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            switchCond = true;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case false:
                    if (sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                    }
                    else if (!field14C_2)
                    {
                        if (airScreamerProps.timer_120 == Q12(0.0f) && !field14C_1 &&
                            Rng_TestProbability(Q12(0.5f)))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case true:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
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

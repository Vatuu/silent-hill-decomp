void sharedFunc_800D80EC_2_s00(s_SubCharacter* airScreamer)
{
    bool temp_a0;
    bool unkField14C;
    s32  unkField150;
    s32  switchCond;
    s32  animStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    switchCond  = 0;
    animStatus  = airScreamer->model_0.anim_4.status_0;
    unkField150 = sharedData_800E21D0_0_s01.distance_150;
    unkField14C = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_a0     = sharedFunc_800DC50C_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamerProps.timer_120 = Q12(2.0f);
            if (Rng_RandQ12() < Q12(0.7f))
            {
                switchCond = 2;
                sharedFunc_800D529C_0_s01(airScreamer, Q12(8.0f), airScreamer->rotation_24.vy);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case 1:
            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            break;

        case 4:
            switchCond = 2;

            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (airScreamer->moveSpeed_38 > Q12(1.5f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_F8) < Q12(3.0f) ||
                     airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
            }
            break;

        case 6:
            switchCond = 3;
            break;
    }

    if (switchCond >= 2 && switchCond < 4)
    {
        sharedFunc_800D57C8_0_s01(airScreamer);
    }
    else
    {
        sharedFunc_800DEBCC_2_s00(airScreamer);
        sharedFunc_800D5B10_0_s01(airScreamer);
    }

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (airScreamerProps.timer_120 == Q12(0.0f) || unkField150 > Q12(2.0f))
                    {
                        if (!unkField14C)
                        {
                            airScreamer->model_0.controlState_2= AirScreamerControl_26;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2= AirScreamerControl_23;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (!unkField14C)
                        {
                            airScreamer->model_0.controlState_2= AirScreamerControl_13;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2= AirScreamerControl_11;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 2:
                    break;

                case 3:
                    if (sharedFunc_800D4A80_0_s01(airScreamer) == switchCond)
                    {
                        airScreamer->model_0.controlState_2= AirScreamerControl_39;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2= AirScreamerControl_29;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 2:
            airScreamer->model_0.controlState_2= AirScreamerControl_30;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2= AirScreamerControl_32;
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

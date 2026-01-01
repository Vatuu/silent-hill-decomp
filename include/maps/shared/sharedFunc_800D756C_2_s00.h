void sharedFunc_800D756C_2_s00(s_SubCharacter* airScreamer)
{
    s32    switch3;
    s32    condModelStateIs2;
    s32    animStatus;
    q19_12 angle0;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   field14C_0_tmp;
    bool   field14C_1_tmp;
    bool   field14C_2_tmp;
    bool   temp_a0;
    q19_12 rngAngle0;
    q19_12 angleSubtract;
    q19_12 angle1;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    switch3           = 0;
    condModelStateIs2 = 0;
    animStatus        = airScreamer->model_0.anim_4.status_0;
    angle0            = sharedData_800E21D0_0_s01.field_15C;

    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    field14C_2     = field14C_2_tmp;
    temp_a0        = sharedFunc_800DC50C_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamerProps.timer_120 = Q12(6.0f);

        case AirScreamerStateStep_1:
            sharedFunc_800DE6A8_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.0f));

            if (!sharedFunc_800DC3BC_2_s00(airScreamer) || Rng_RandQ12() >= FP_ANGLE(36.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_2:
            condModelStateIs2 = 1;

        case AirScreamerStateStep_3:
            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                if (condModelStateIs2)
                {
                    switch3 = 1;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (!airScreamerProps.timer_120)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;

                if (angle0 > (FP_ANGLE(2.9f)))
                {
                    angle1 = func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy;
                    angle1 = FP_ANGLE_NORM_S(angle1);
                    if (angle1 < FP_ANGLE(0.0f))
                    {
                        angle1 += FP_ANGLE(0.3f);
                    }

                    sharedFunc_800D529C_0_s01(airScreamer, Q12(2.0f), (angle1 >> 2) + airScreamer->rotation_24.vy);
                    airScreamerProps.timer_120 = Q12(6.0f);
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3                        = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);

                if (field14C_1 || field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3                        = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            switch3 = 3;
            if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                switch3 = 2;
            }
            break;

        case AirScreamerStateStep_7:
            switch3 = 3;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switch3)
            {
                case 0:
                case 1:
                    if (field14C_2 == 0)
                    {
                        if (switch3 == 1)
                        {
                            rngAngle0     = Rng_RandQ12();
                            angleSubtract = FP_ANGLE(0.0f);

                            if (airScreamerProps.field_E8_8 == switch3)
                            {
                                angleSubtract = FP_ANGLE(36.0f);
                            }

                            if (rngAngle0 < (FP_ANGLE(252.0f) - (angleSubtract * 2)))
                            {
                                airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                            }
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_22;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (!field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 3:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_7;
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
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
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

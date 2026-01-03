void sharedFunc_800D9C60_2_s00(s_SubCharacter* airScreamer)
{
    s32  temp_a0;
    s32  temp_a1;
    s32  temp_s3;
    s32  temp_s4;
    s32  temp_s5;
    s32  temp_s6;
    s32  temp_s7;
    s32  var_a0;
    s32  var_a1;
    s32  unkAngleDelta;
    s32  var_s1;
    s32  animStatus;
    bool new_var;
    bool new_var2;
    bool new_var3;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;

    var_s1 = 0;

    temp_s7 = sharedFunc_800D4A80_0_s01(airScreamer);

    temp_s6 = sharedData_800E21D0_0_s01.field_15C;

    new_var  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    new_var3 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;

    temp_s5 = new_var3;
    temp_s4 = new_var;
    temp_s3 = new_var2;

    temp_a0 = sharedFunc_800DC438_2_s00(airScreamer);
    var_a1  = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamerProps.timer_120 = Q12(6.0f);

        case AirScreamerStateStep_1:
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.0f));

            if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_TestProbability(Q12(0.1f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_8;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            break;

        case AirScreamerStateStep_2:
            var_a1 = 1;

        case AirScreamerStateStep_3:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else
            {
                if (temp_a0 == 1)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_8;
                }
                else if (airScreamerProps.timer_120 == Q12(0.0f))
                {
                    if (var_a1 != 0)
                    {
                        var_s1 = 1;
                    }
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                }
                else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
                }
                else if (temp_s5 || temp_s4 || temp_s3)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                    if (temp_s6 >= 33)
                    {

                        unkAngleDelta = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy);
                        if (unkAngleDelta < FP_ANGLE(0.0f))
                        {
                            unkAngleDelta += FP_ANGLE(0.3f);
                        }

                        sharedFunc_800DEC84_2_s00(airScreamer, Q12(2.0f), (unkAngleDelta >> 2) + airScreamer->rotation_24.vy);
                        airScreamerProps.timer_120 = Q12(6.0f);
                    }
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                var_s1                        = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);

                if (!temp_s3 && !temp_s4)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
            }
            else if (temp_s3 || temp_s4)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                var_s1                        = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            if (temp_s3 || temp_s4)
            {
                var_s1                    = 3;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                var_s1 = 2;
            }
            break;

        case AirScreamerStateStep_7:
            var_s1 = 3;
            break;

        case AirScreamerStateStep_8:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                var_s1                        = 4;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);

                if (!temp_s3 && !temp_s4)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_10;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_11;
                }
            }
            else if (temp_s3 || temp_s4)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_9;
            }
            break;

        case AirScreamerStateStep_9:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                var_s1                        = 5;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_11;
            }
            break;

        case AirScreamerStateStep_10:
            if (temp_s3 || temp_s4)
            {
                var_s1                    = 5;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_11;
            }
            else
            {
                var_s1 = 4;
            }
            break;

        case AirScreamerStateStep_11:
            var_s1 = 5;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 0, 2);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (var_s1)
            {
                case 0:
                case 1:
                    if (!temp_s3 && !temp_s4)
                    {
                        if (var_s1 == 1)
                        {
                            temp_a1 = Rng_RandQ12();

                            if (airScreamerProps.field_E8_8 == var_s1)
                            {
                                var_a0 = Q12(0.1f);
                            }
                            else
                            {
                                var_a0 = 0;
                            }

                            if (temp_a1 < (Q12(0.7f) - (var_a0 * 2)))
                            {
                                airScreamer->model_0.controlState_2 = AirScreamerControl_43;
                                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                            }
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s7 == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_s7 == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 4:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 5:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2                        = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3                           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
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

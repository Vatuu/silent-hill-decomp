void Ai_AirScreamerControl_36(s_SubCharacter* airScreamer)
{
    s32  animStatus;
    s32  switchCond;
    s32  temp_fp;
    s32  field15C;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;
    bool cond;
    s32  temp_a0;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    temp_fp        = sharedFunc_800D4A80_0_s01(airScreamer);
    field15C       = sharedData_800E21D0_0_s01.field_15C;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;

    field14C_0 = field14C_0_tmp;
    field14C_1 = field14C_1_tmp;
    field14C_2 = field14C_2_tmp;

    cond = false;
    temp_a0 = sharedFunc_800DC438_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_TestProbability(Q12(0.1f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_8;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }

        case AirScreamerStateStep_1:
            airScreamerProps.timer_120 = Q12(6.0f);
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.position_104, Q12(3.0f));
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            break;

        case AirScreamerStateStep_2:
            cond = true;

        case AirScreamerStateStep_3:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_8;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                if (cond)
                {
                    switchCond = 1;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;

                if (field15C > 32)
                {
                    q19_12 angleDiff = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy);
                    sharedFunc_800DEC84_2_s00(airScreamer, Q12(3.0f), (angleDiff / 4) + airScreamer->rotation_24.vy);
                    airScreamerProps.timer_120 = Q12(6.0f);
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);

                if (!field14C_1 && !field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            switchCond = 3;

            if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                switchCond = 2;
            }
            break;

        case AirScreamerStateStep_7:
            switchCond = 3;
            break;

        case AirScreamerStateStep_8:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 4;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);

                if (!field14C_1 && !field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_10;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_11;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_9;
            }
            break;

        case AirScreamerStateStep_9:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 5;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_11;
            }
            break;

        case AirScreamerStateStep_10:
            switchCond = 5;

            if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_11;
            }
            else
            {
                switchCond = 4;
            }
            break;

        case AirScreamerStateStep_11:
            switchCond = 5;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 1, 1);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (field14C_2)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_37;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (switchCond == 1)
                    {
                        s32 rand   = Rng_RandQ12();
                        s32 var_a0 = 0;

                        if (airScreamerProps.field_E8_8 == 1)
                        {
                            var_a0 = Q12(0.1f);
                        }

                        if (rand < (Q12(0.7f) - (var_a0 * 2)))
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_35;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 2:
                    if (temp_fp == 1)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_8;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_6;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 3:
                    if (temp_fp == 1)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_8;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_7;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 4:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_22;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_20;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 5:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_22;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = AirScreamerControl_21;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2               = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
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

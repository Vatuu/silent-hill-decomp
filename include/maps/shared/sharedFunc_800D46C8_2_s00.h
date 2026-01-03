// Note: Very close match to `sharedFunc_800D4A9C_2_s00` other than some checks being removed.
// Changes here should be copied over there.

void sharedFunc_800D46C8_2_s00(s_SubCharacter* airScreamer)
{
    s32  animStatus;
    s32  switchCond;
    bool cond;
    s32  temp_fp;
    s32  temp_fp_tmp;
    s32  field15C;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    cond         = false;
    temp_fp_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    field15C       = sharedData_800E21D0_0_s01.field_15C;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_fp        = temp_fp_tmp;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    field14C_2     = field14C_2_tmp;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamerProps.timer_120 = Q12(6.0f);

        case AirScreamerStateStep_1:
            sharedFunc_800DE034_2_s00(airScreamer, &airScreamerProps.position_104, Q12(1.5f));

            if (!sharedFunc_800DC30C_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (Rng_RandQ12() >= Q12(0.3f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_2:
            cond = true;

        case AirScreamerStateStep_3:
            if (sharedFunc_800DC598_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                if (cond)
                {
                    switchCond = 1;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (field14C_0 || field14C_1 || field14C_2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;

                switchCond = 0;

                if (field15C > 32)
                {
                    s32 var_v0 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy);
                    sharedFunc_800DDF74_2_s00(airScreamer, Q12(1.5f), (var_v0 / 4) + airScreamer->rotation_24.vy);
                    airScreamerProps.timer_120 = Q12(6.0f);
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);

                if (field14C_2 || field14C_1)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
            }
            else if (field14C_2 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            if (field14C_2 || field14C_1)
            {
                switchCond                 = 3;
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
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (field14C_2 || field14C_1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (switchCond == 1 && Rng_TestProbability(Q12(0.5f)))
                    {
                        s32 randVal = Rng_RandQ12();
                        s32 var_a0  = Q12(0.0f);

                        if (airScreamerProps.field_E8_8 == 1)
                        {
                            var_a0 = Q12(0.1f);
                        }

                        if (randVal < Q12(0.7f) - (var_a0 * 2))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_15;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 2:
                    if (temp_fp == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_fp == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
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

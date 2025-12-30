// Similar to `sharedFunc_800D4358_2_s00`
void sharedFunc_800D3FA4_2_s00(s_SubCharacter* airScreamer)
{
    s32    temp_fp;
    q19_12 distToTarget;
    s32    temp_s1_2;
    bool   temp_s5;
    bool   temp_s6;
    bool   temp_s7;
    s32    temp_v0;
    s32    var_s3;
    bool   cond;
    bool   var_v0_2;
    s32    animStatus;
    bool   new_var;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    var_s3  = 0;
    cond  = false;
    temp_fp = sharedFunc_800D4A80_0_s01(airScreamer);

    var_v0_2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_s6  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;

    temp_s5 = var_v0_2;
    temp_s7 = new_var;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_64:
            sharedFunc_800DD4A4_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case AirScreamerStateStep_0:
            sharedFunc_800DDF74_2_s00(airScreamer, Q12(4.0f), airScreamer->rotation_24.vy);
            sharedFunc_800DE034_2_s00(airScreamer, &airScreamerProps.position_F8, Q12(3.0f));
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case AirScreamerStateStep_1:
            cond                                             = true;
            airScreamerProps.timer_120 = Q12(8.0f);
            airScreamer->model_0.stateStep_3                          = AirScreamerStateStep_2;

        case AirScreamerStateStep_2:
            distToTarget = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_F8);
            temp_s1_2 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_F8) - airScreamer->rotation_24.vy);
            temp_v0   = sharedFunc_800DC598_2_s00(airScreamer);

            if (temp_v0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (temp_v0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if ((distToTarget < Q12(1.0f) && (temp_s1_2 > -57 && temp_s1_2 < 57)) ||
                     airScreamerProps.flags_11C < 0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (cond)
            {
                if (sharedFunc_800DC200_2_s00(airScreamer) && distToTarget > Q12(6.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
                }
                else if (sharedFunc_800DC30C_2_s00(airScreamer))
                {
                    if (distToTarget >= Q12(1.5f) || Rng_RandQ12() >= Q12(0.5f))
                    {
                        // @hack This check should be `if (diff >= Q12(-1.0f) && diff < Q12(1.0f))`,
                        // but that results in `sltiu 0x2000` instead of the `li 0x2000/sltu` needed.
                        if (Math_CheckSignedRange(airScreamer->properties_E4.unk0.field_F8.vy - airScreamer->position_18.vy, Q12(1.0f)))
                        {
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                    }
                }
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) || animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                var_s3                        = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            var_s3 = 1;
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) || animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                var_s3                        = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_24, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case AirScreamerStateStep_6:
            var_s3 = 2;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (var_s3)
            {
                case 0:
                    if (temp_s5 | temp_s6 | temp_s7)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (temp_fp == 2)
                    {
                        if (temp_s5 | temp_s6 | temp_s7)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_18;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_fp == 3)
                    {
                        if (temp_s5 | temp_s6 | temp_s7)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_33;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2                       = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3                          = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
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
}
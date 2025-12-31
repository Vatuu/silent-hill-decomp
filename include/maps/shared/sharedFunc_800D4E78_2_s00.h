void sharedFunc_800D4E78_2_s00(s_SubCharacter* airScreamer)
{
    s32    animStatus;
    s32    switchCond1;
    q19_12 var_s7;
    s32    sp10;
    q19_12 unkDist;
    q19_12 unkAngle;
    bool   field14C_2;
    s32    temp_s3;
    s32    switchCond0;
    s32    temp_s0;
    s32    temp_s2;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus  = airScreamer->model_0.anim_4.status_0;
    switchCond1 = 0;
    var_s7      = Q12(0.0f);
    sp10        = sharedFunc_800D4A80_0_s01(airScreamer);
    unkDist     = sharedData_800E21D0_0_s01.distance_150;
    unkAngle    = sharedData_800E21D0_0_s01.angle_154;
    field14C_2  = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;

    if (airScreamerProps.field_E8_4)
    {
        var_s7 = Q12(0.1f);
    }

    temp_s3     = sharedFunc_800DC598_2_s00(airScreamer);
    switchCond0 = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            switchCond1                                    = 1;
            airScreamerProps.timer_120 = Q12(2.0f);
            airScreamer->flags_3E                               |= CharaFlag_Unk3;

        case AirScreamerStateStep_1:
            sharedFunc_800DDF74_2_s00(airScreamer, unkDist / 2, unkAngle);

            if (!sharedFunc_800DC30C_2_s00(airScreamer) || Rng_RandQ12() >= Q12(0.3f))
            {
                if (Rng_RandQ12() < (Q12(0.2f) + (var_s7 * 2)))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                }
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_2:
            switchCond0 = 1;

            if (temp_s3 != 0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (airScreamerProps.timer_120 != Q12(0.0f))
            {
                if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_F8) < Q12(1.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
                }
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerStateStep_3:
            sharedFunc_800DDF74_2_s00(airScreamer, unkDist / 2, unkAngle);

            #define angleDiff FP_ANGLE_NORM_S(unkAngle - airScreamer->rotation_24.vy)

            if (temp_s3 != 0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (angleDiff >= FP_ANGLE(-10.0f) && angleDiff < FP_ANGLE(10.0f))
            {
                switchCond0 = 2;
            }
            break;

            #undef angleDiff

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) || animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                switchCond1                    = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond1 = 2;
            break;
    }

    switch (switchCond0)
    {
        case 1:
            sharedFunc_800DF448_2_s00(airScreamer, false);
            break;

        case 2:
            sharedFunc_800DF2D0_2_s00(airScreamer);
            break;

        default:
            sharedFunc_800DF60C_2_s00(airScreamer);
            break;
    }

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond1)
            {
                case 0:
                    if (field14C_2 == 0)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_7;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    temp_s0 = sharedFunc_800DC894_2_s00(airScreamer, unkDist);
                    temp_s2 = sharedFunc_800DC6E4_2_s00(airScreamer, unkDist);

                    if (Rng_RandQ12() < temp_s0)
                    {
                        if (airScreamerProps.field_E8_0 == 3)
                        {
                            sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.6f));
                        }

                        airScreamer->model_0.controlState_2               = AirScreamerControl_10;
                        airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
                        airScreamerProps.flags_11C |= AirScreamerFlag_4;
                    }
                    else if (Rng_RandQ12() < temp_s2)
                    {
                        airScreamer->model_0.controlState_2               = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
                        airScreamerProps.flags_11C |= AirScreamerFlag_4;
                    }
                    break;

                case 2:
                    if (sp10 == switchCond1)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_22;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2               = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2     = AirScreamerControl_17;
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

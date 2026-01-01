void sharedFunc_800DB54C_2_s00(s_SubCharacter* airScreamer)
{
    s32    temp_a0;
    bool   field14C;
    s32    angleDelta;
    q19_12 angle;
    q19_12 dist;
    s32    temp_s7;
    s32    switchCond;
    q19_12 var_s3;
    s32    var_s5; // Possibly `bool`
    s32    animStatus;
    s32    new_var;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    new_var    = sharedFunc_800D4A80_0_s01(airScreamer);
    dist       = sharedData_800E21D0_0_s01.distance_150;
    angle      = sharedData_800E21D0_0_s01.angle_154;
    field14C   = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s7    = new_var;
    var_s3     = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
    temp_a0    = sharedFunc_800DC438_2_s00(airScreamer);
    var_s5     = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            var_s5     = sharedFunc_800DF24C_2_s00(airScreamer);
            var_s3     = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleDelta = FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy);
            if (!sharedFunc_800DC30C_2_s00(airScreamer) || (angleDelta < FP_ANGLE(-30.0f) || angleDelta >= FP_ANGLE(30.0f)))
            {
                airScreamerProps.timer_120 = Q12(2.0f);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_1:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (var_s3 < Q12(2.0f) || (airScreamerProps.flags_11C & AirScreamerFlag_31))
            {
                var_s5 = sharedFunc_800DF24C_2_s00(airScreamer);
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case AirScreamerStateStep_3:
            switchCond = 1;
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond = 2;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 2, 0);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case 0:
                    if (var_s5 || (((field14C != 0 && dist < Q12(15.0f)) || dist < Q12(4.0f)) && var_s3 < Q12(1.5f)))
                    {
                        airScreamer->model_0.controlState_2               = AirScreamerControl_38;
                        airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
                        airScreamerProps.field_E8_8 = 3;
                        airScreamerProps.flags_11C |= AirScreamerFlag_4;
                    }
                    else if (dist > Q12(30.0f) && var_s3 < Q12(1.0f))
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_36;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    return;

                case 1:
                    if (temp_s7 == 1)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
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

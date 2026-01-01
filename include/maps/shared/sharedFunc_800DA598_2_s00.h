void sharedFunc_800DA598_2_s00(s_SubCharacter* airScreamer)
{
    s32    temp_a0;
    q19_12 temp_s2;
    q19_12 dist;
    s32    temp_s4;
    bool   field14C;
    q19_12 angle;
    s32    switchCond;
    q19_12 temp_s1;
    s32    animStatus;
    s32    new_var;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    switchCond = 0;
    animStatus = airScreamer->model_0.anim_4.status_0;
    new_var    = sharedFunc_800D4A80_0_s01(airScreamer);
    dist       = sharedData_800E21D0_0_s01.distance_150;
    angle      = sharedData_800E21D0_0_s01.angle_154;
    field14C   = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s4    = new_var;
    temp_a0    = sharedFunc_800DC438_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            switchCond                                     = 1;
            airScreamerProps.timer_120 = Q12(2.0f);
            airScreamer->flags_3E                               |= CharaFlag_Unk3;

        case AirScreamerStateStep_1:
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.position_104, Q12(4.0f));
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            break;

        case AirScreamerStateStep_2:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            switchCond = 2;
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case AirScreamerStateStep_6:
            switchCond = 3;
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
                    if (!field14C)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_36;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s4 == 1)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_8;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_s4 == 2)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_22;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    temp_s1 = sharedFunc_800DC894_2_s00(airScreamer, dist);
                    temp_s2 = sharedFunc_800DC6E4_2_s00(airScreamer, dist);

                    if (FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy) >= FP_ANGLE(-22.5f) &&
                        FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy) <  FP_ANGLE(22.5f) &&
                        dist > Q12(4.0f) && dist < Q12(8.0f))
                    {
                        temp_s1 += Q12(0.2f);
                    }

                    if (Rng_RandQ12() < temp_s1)
                    {
                        if (airScreamerProps.field_E8_0 == 3)
                        {
                            sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.6f));
                        }

                        airScreamer->model_0.controlState_2               = AirScreamerControl_38;
                        airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
                        airScreamerProps.flags_11C |= AirScreamerFlag_4;
                    }
                    else if (Rng_RandQ12() < temp_s2)
                    {
                        airScreamer->model_0.controlState_2               = AirScreamerControl_42;
                        airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
                        airScreamerProps.flags_11C |= AirScreamerFlag_4;
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

void sharedFunc_800D83F8_2_s00(s_SubCharacter* airScreamer)
{
    bool var_s1;
    bool var_s2;
    s32  animStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    var_s1     = false;
    var_s2     = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case 1:
            if (animStatus == ANIM_STATUS(19, true))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamer->model_0.anim_4.status_0 = 4;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(2, true) && airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                airScreamerProps.flags_11C |= 1 << 5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                var_s1 = true;
            }
            else if (airScreamer->field_44.field_8 == NO_VALUE)
            {
                var_s1                     = true;
                var_s2                     = true;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                var_s1 = true;
                var_s2 = true;
            }
            break;
    }

    sharedFunc_800D53AC_0_s01(airScreamer);
    sharedFunc_800D5C90_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case 0:
            if (var_s1)
            {
                if (airScreamer->properties_E4.unk0.field_E8_8 == 3)
                {
                    airScreamer->properties_E4.unk0.field_E8_8 = 2;

                    if (var_s2 && Rng_RandQ12() < FP_ANGLE(180.0f))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                    }
                }
                else
                {
                    if (var_s2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                    }
                    else if (Rng_RandQ12() < FP_ANGLE(180.0f))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                    }
                }
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= 1 << 3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= 1 << 3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamerProps.flags_11C |= 1 << 6;
            }
            else
            {
                airScreamerProps.flags_11C |= 1 << 3;
            }
            break;
    }

    #undef airScreamerProps
}

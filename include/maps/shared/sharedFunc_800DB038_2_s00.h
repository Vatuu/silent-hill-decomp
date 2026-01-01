void sharedFunc_800DB038_2_s00(s_SubCharacter* airScreamer)
{
    bool cond0;
    bool cond1;
    s32  animStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    cond0 = false;
    cond1 = false;

    // Handle state step.
    animStatus = airScreamer->model_0.anim_4.status_0;
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case AirScreamerStateStep_1:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_3, false);
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_3, true) &&
                airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3           = AirScreamerStateStep_3;
                airScreamerProps.flags_11C |= AirScreamerFlag_5;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                cond0 = true;
            }
            else if (airScreamer->field_44.field_8 == NO_VALUE)
            {
                cond0                      = true;
                cond1                      = true;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800DEE24_2_s00(airScreamer);
    sharedFunc_800E0514_2_s00(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case AirScreamerDamage_None:
            if (cond0)
            {
                if (airScreamerProps.field_E8_8 == 5 && cond1)
                {
                    airScreamerProps.field_E8_8 = 1;
                    airScreamer->model_0.controlState_2               = AirScreamerControl_42;
                }
                else
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_39;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
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

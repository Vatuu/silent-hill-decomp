void Ai_AirScreamerControl_12(s_SubCharacter* airScreamer)
{
    bool cond0;
    bool cond1;
    s32  animStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    cond0     = false;
    cond1     = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case 1:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(1, true) && airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
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

        case 4:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800DF358_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case 0:
            if (cond0)
            {
                if (airScreamerProps.field_E8_8 == 3)
                {
                    airScreamerProps.field_E8_8 = 2;

                    if (cond1 && Rng_TestProbability(Q12(0.5f)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                    }
                }
                else
                {
                    if (cond1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                    }
                    else if (Rng_TestProbability(Q12(0.5f)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                    }
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }

    #undef airScreamerProps
}

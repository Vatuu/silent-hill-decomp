void Ai_AirScreamerControl_9(s_SubCharacter* airScreamer)
{
    bool cond0;
    bool cond1;
    u32  temp_v1;
    s32  animStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    cond0      = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    // Handle state step.
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            sharedFunc_800DDF74_2_s00(airScreamer, Q12(0.1f), airScreamer->rotation_24.vy);
            airScreamer->model_0.stateStep_3                     = AirScreamerStateStep_7;
            airScreamerProps.timer_120 = Q12(56.0f);
            break;

        case AirScreamerStateStep_1:
        case AirScreamerStateStep_2:
        case AirScreamerStateStep_3:
        case AirScreamerStateStep_4:
        case AirScreamerStateStep_5:
        case AirScreamerStateStep_6:
        case AirScreamerStateStep_7:
            if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                cond0 = true;
            }
            else if ((((u32)airScreamer->model_0.stateStep_3 - 1) * Q12(8.0f)) >= airScreamerProps.timer_120 &&
                     animStatus == ANIM_STATUS(14, true))
            {
                airScreamer->model_0.anim_4.status_0       = ANIM_STATUS(13, false);
                airScreamer->model_0.stateStep_3           = AirScreamerStateStep_8;
                airScreamerProps.flags_11C |= AirScreamerFlag_2;
            }
            break;

        case AirScreamerStateStep_8:
            airScreamerProps.timer_120 += g_DeltaTime0;

            if (animStatus == ANIM_STATUS(14, true))
            {
                temp_v1 = Rng_RandQ12() * 12;
                if (temp_v1 < airScreamerProps.timer_120)
                {
                    airScreamerProps.timer_120 -= temp_v1;
                }
                else
                {
                    airScreamerProps.timer_120 = 0;
                }

                airScreamer->model_0.stateStep_3 = ((u32)airScreamerProps.timer_120 / Q12(8.0f)) + 1;
            }
            break;
    }

    sharedFunc_800DF2D0_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (cond0)
            {
                case 0:
                    if (ANIM_STATUS_IS_ACTIVE(animStatus))
                    {
                        if (sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2)
                        {
                            if (!airScreamerProps.field_E8_8)
                            {
                                cond1 = sharedFunc_800D3814_0_s01(airScreamer) >= Q12(2.0f);
                            }
                            else
                            {
                                cond1 = true;
                            }

                            if (cond1)
                            {
                                airScreamer->model_0.anim_4.status_0       = ANIM_STATUS(23, false);
                                airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                                airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
                                airScreamer->flags_3E                     |= CharaFlag_Unk3;
                                airScreamerProps.flags_11C |= AirScreamerFlag_4;
                                airScreamerProps.field_E8_8 = 3;
                            }
                        }
                        else if (airScreamerProps.flags_11C & AirScreamerFlag_31 ||
                                 sharedData_800E21D0_0_s01.field_14C.bits.field_14C_1 ||
                                 sharedData_800E21D0_0_s01.field_15C > Q12(10.0f))
                        {
                            airScreamer->model_0.anim_4.status_0       = ANIM_STATUS(23, false);
                            airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
                            airScreamerProps.field_E8_8 = 3;
                        }
                    }
                    break;

                case 1:
                    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    airScreamer->model_0.controlState_2 = AirScreamerControl_15;
                    airScreamer->model_0.stateStep_3     = AirScreamerStateStep_0;
                    sharedFunc_800D3DFC_0_s01(airScreamer);
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            return;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
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

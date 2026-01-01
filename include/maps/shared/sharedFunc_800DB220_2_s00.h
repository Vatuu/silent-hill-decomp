void sharedFunc_800DB220_2_s00(s_SubCharacter* airScreamer)
{
    s32    animStatus;
    s32    switchCond;
    s32    temp_s6;
    s32    temp_s6_tmp;
    bool   field14C_2;
    bool   field14C_2_tmp;
    s32    temp_s4;
    q19_12 unkDist;
    q19_12 unkDeltaAngle;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;

    // @hack Weird variable juggling needed for match, is there another way to do this?
    temp_s6_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s6        = temp_s6_tmp;
    field14C_2     = field14C_2_tmp;
    temp_s4        = sharedFunc_800DC438_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            sharedFunc_800DF22C_2_s00(airScreamer);

        case AirScreamerStateStep_1:
            airScreamerProps.timer_120 = Q12(4.0f);
            airScreamer->model_0.stateStep_3                     = AirScreamerStateStep_2;
            break;

        case AirScreamerStateStep_2:
            unkDist = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            unkDeltaAngle  = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (temp_s4 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (temp_s4 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if (unkDist < Q12(0.5f))
            {
                if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_RandQ12() < Q12(0.3f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
                }
                else
                {
                    switchCond = 1;
                }
            }
            else if (unkDist < Q12(4.0f) && Math_CheckSignedRange(unkDeltaAngle, FP_ANGLE(90.0f))) // @hack Should be `angFieldF8 >= FP_ANGLE(-90.0f) && angFieldF8 < FP_ANGLE(90.0f)`
            {
                switchCond = 2;
            }

            if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.5f));
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            switchCond = 3;
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                     = 4;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case AirScreamerStateStep_6:
            switchCond = 4;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 1, 0);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case AirScreamerDamage_None:
                case AirScreamerDamage_1:
                case AirScreamerDamage_2:
                    if (sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                    }
                    else if (field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                    }
                    else if (switchCond == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_39;
                    }
                    else if (switchCond == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                    }
                    else
                    {
                        break;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case AirScreamerDamage_3:
                    if (temp_s6 == 1)
                    {
                        if (!field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        }
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case AirScreamerDamage_4:
                    if (temp_s6 == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                        }
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

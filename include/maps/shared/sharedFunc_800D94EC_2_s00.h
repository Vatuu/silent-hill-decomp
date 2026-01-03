void sharedFunc_800D94EC_2_s00(s_SubCharacter* airScreamer)
{
    s32  animStatus;
    s32  switchCond;
    s32  sp10;
    bool cond;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;
    s32  temp_s4;
    s32  distFieldF8;
    s32  angleDiff;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    sp10       = sharedFunc_800D4A80_0_s01(airScreamer);
    cond       = 0;

    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;

    field14C_0 = field14C_0_tmp;
    field14C_1 = field14C_1_tmp;
    field14C_2 = field14C_2_tmp;

    temp_s4 = sharedFunc_800DC438_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 64:
            sharedFunc_800DD534_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 0:
            cond = true;

            airScreamerProps.timer_120 = Q12(5.0f);
            sharedFunc_800DEC84_2_s00(airScreamer, Q12(6.0f), airScreamer->rotation_24.vy);
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.targetPosition_F8, Q12(5.0f));

            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case 1:
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleDiff   = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (temp_s4 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (temp_s4 == 1 || (sharedFunc_800DC30C_2_s00(airScreamer) && 
                                      cond == true && 
                                      airScreamerProps.flags_11C & AirScreamerFlag_31 && 
                                      (distFieldF8 < Q12(2.0f) || Math_CheckSignedRange(angleDiff, FP_ANGLE(60.0f)))))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (sharedFunc_800DC3BC_2_s00(airScreamer) && 
                     cond == true && 
                     distFieldF8 < Q12(4.0f) && 
                     (angleDiff >= FP_ANGLE(-30.0f) && angleDiff <= FP_ANGLE(30.0f)) && 
                     Rng_TestProbability(Q12(0.7f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f) || distFieldF8 < Q12(3.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(16, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case 5:
            switchCond = 2;
            break;

        case 65:
            sharedFunc_800DDA80_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 66:
            sharedFunc_800DD588_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 67:
            sharedFunc_800DD834_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            airScreamerProps.flags_11C |= AirScreamerFlag_12;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 0, 1);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_1 | field14C_0 | field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (sp10 == 1)
                    {
                        if (!(field14C_1 | field14C_0 | field14C_2))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_4;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 2:
                    if (sp10 == 2)
                    {
                        if (!(field14C_1 | field14C_0 | field14C_2))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_18;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
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

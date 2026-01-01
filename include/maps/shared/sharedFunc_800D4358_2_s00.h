void sharedFunc_800D4358_2_s00(s_SubCharacter* airScreamer)
{
    s32     animStatus;
    bool    field14C_0;
    bool    field14C_1;
    bool    field14C_2;
    bool    new_var1;
    bool    new_var2;
    bool    new_var3;
    s32     switchCond;
    bool    cond;
    s32     temp_fp;
    s32     new_var;
    q19_12  angleFieldF8;
    q19_12  distFieldF8;
    s32     temp_v0;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    cond       = false;

    new_var    = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var1   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_fp    = new_var;
    field14C_0 = new_var1;
    field14C_1 = new_var2;
    field14C_2 = new_var3;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            sharedFunc_800DDE14_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case AirScreamerStateStep_1:
            cond                                           = true;
            airScreamerProps.timer_120 = Q12(6.0f);
            airScreamer->model_0.stateStep_3                     = AirScreamerStateStep_2;

        case AirScreamerStateStep_2:
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleFieldF8  = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            temp_v0     = sharedFunc_800DC598_2_s00(airScreamer);
            if (temp_v0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (temp_v0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if ((distFieldF8 < Q12(0.5f) && (angleFieldF8 >= FP_ANGLE(-5.0f) && angleFieldF8 <= FP_ANGLE(5.0f))) ||
                     (airScreamerProps.flags_11C & CharaUnk0Flag_Unk31))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (cond)
            {
                if (sharedFunc_800DC200_2_s00(airScreamer) && distFieldF8 > Q12(6.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
                }
                else if (sharedFunc_800DC30C_2_s00(airScreamer))
                {
                    // @hack This check should be `if (diff >= Q12(-1.0f) && diff < Q12(1.0f))`,
                    // but that results in `sltiu 0x2000` instead of the `li 0x2000/sltu` needed.
                    if (Math_CheckSignedRange(airScreamerProps.targetPosition_F8.vy - airScreamer->position_18.vy, Q12(1.0f)))
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                    }
                }
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            switchCond = 1;
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(24, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case AirScreamerStateStep_6:
            switchCond = 2;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_1 | field14C_0 | field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (temp_fp == 2)
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_19;
                        }
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_fp == 3)
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_34;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }

    #undef airScreamerProps
}

void sharedFunc_800D6E28_2_s00(s_SubCharacter* airScreamer)
{
    s32    animStatus;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   new_var4;
    bool   new_var2;
    bool   new_var3;
    q19_12 distFieldF8;
    q19_12 angFieldF8;
    s32    switchCond;
    s32    sp10;    // Possibly `bool`.
    s32    sp10_temp;
    bool   cond;
    bool   temp_s5;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;

    // @hack These flags/bitfields always need weird variable juggling, is there a way to remove it?
    sp10_temp    = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var4   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp10       = sp10_temp;
    cond       = false;
    field14C_0 = new_var4;
    field14C_1 = new_var2;
    field14C_2 = new_var3;

    temp_s5 = sharedFunc_800DC50C_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DE7E0_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 1:
            cond                                           = true;
            airScreamerProps.timer_120 = Q12(6.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;

        case 2:
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angFieldF8  = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (!temp_s5)
            {
                if ((distFieldF8 < Q12(0.5f) && (angFieldF8 >= FP_ANGLE(-5.0f) && angFieldF8 <= FP_ANGLE(5.0f))) ||
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
                    else if (sharedFunc_800DC3BC_2_s00(airScreamer) && distFieldF8 < Q12(2.0f) && Rng_RandQ12() < Q12(0.5f))
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                    }
                }
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case 4:
            switchCond = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(24, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
            }
            break;

        case 6:
            switchCond = 2;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_1 | field14C_0 | field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_5;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 2:
                    if (sp10 == 3)
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
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
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

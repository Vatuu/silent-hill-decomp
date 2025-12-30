void sharedFunc_800D5DAC_2_s00(s_SubCharacter* airScreamer)
{
    bool field14C_2;
    bool field14C_1;
    bool new_var2;
    bool new_var3;
    s32  switchCond;
    s32  animStatus;
    s32  temp_s4;
    s32  new_var;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    new_var    = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_1 = new_var3;
    temp_s4    = new_var;
    field14C_2 = new_var2;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DE1F8_2_s00(airScreamer);

        case 1:
            airScreamer->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
            if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_RandQ12() < Q12(0.4f))
            {
                airScreamer->model_0.stateStep_3 = 3;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = 2;
            }
            break;

        case 2:
            if (sharedFunc_800DC598_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = 3;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamer->properties_E4.unk0.field_F8) < Q12(0.5f))
            {
                sharedFunc_800DE034_2_s00(airScreamer, &airScreamer->properties_E4.unk0.pos_104, Q12(2.0f));
            }
            else if (airScreamer->properties_E4.unk0.properties_120.val32 == 0)
            {
                sharedFunc_800DE034_2_s00(airScreamer, &airScreamer->properties_E4.unk0.pos_104, Q12(2.0f));
                airScreamer->model_0.stateStep_3 = 1;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3     = 4;
            }
            break;

        case 4:
            switchCond = 1;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        if (field14C_2 == 0)
                        {
                            if (airScreamer->properties_E4.unk0.properties_120.val32 == 0 && !field14C_1 && Rng_RandQ12() < Q12(0.5f))
                            {
                                airScreamer->model_0.controlState_2     = 7;
                                airScreamer->model_0.stateStep_3 = 0;
                            }
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = 10;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2     = 14;
                        airScreamer->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    if (temp_s4 == 2)
                    {
                        if (field14C_2 != 0)
                        {
                            airScreamer->model_0.controlState_2 = 23;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = 26;
                        }

                        airScreamer->model_0.stateStep_3 = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2               = 16;
            airScreamer->model_0.stateStep_3           = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2     = 17;
            airScreamer->model_0.stateStep_3 = 0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}

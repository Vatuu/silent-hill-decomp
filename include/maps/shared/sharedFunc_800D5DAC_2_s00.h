void sharedFunc_800D5DAC_2_s00(s_SubCharacter* chara)
{
    bool field14C_2;
    bool field14C_1;
    bool new_var2;
    bool new_var3;
    s32  switchCond;
    s32  animStatus;
    s32  temp_s4;
    s32  new_var;

    animStatus = chara->model_0.anim_4.status_0;
    switchCond = 0;
    new_var    = sharedFunc_800D4A80_0_s01(chara);
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_1 = new_var3;
    temp_s4    = new_var;
    field14C_2 = new_var2;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DE1F8_2_s00(chara);

        case 1:
            chara->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
            if (sharedFunc_800DC30C_2_s00(chara) && Rng_RandQ12() < Q12(0.4f))
            {
                chara->model_0.stateStep_3 = 3;
            }
            else
            {
                chara->model_0.stateStep_3 = 2;
            }
            break;

        case 2:
            if (sharedFunc_800DC598_2_s00(chara))
            {
                chara->model_0.stateStep_3 = 3;
                break;
            }

            if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(0.5f))
            {
                sharedFunc_800DE034_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(2.0f));
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                sharedFunc_800DE034_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(2.0f));
                chara->model_0.stateStep_3 = 1;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                     = 1;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                chara->model_0.stateStep_3     = 4;
            }
            break;

        case 4:
            switchCond = 1;
            break;
    }

    sharedFunc_800DF448_2_s00(chara, 0);

    switch (Ai_AirScreamer_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(chara))
                    {
                        if (field14C_2 == 0)
                        {
                            if (chara->properties_E4.unk0.properties_120.val32 == 0 && !field14C_1 && Rng_RandQ12() < Q12(0.5f))
                            {
                                chara->model_0.controlState_2     = 7;
                                chara->model_0.stateStep_3 = 0;
                            }
                        }
                        else
                        {
                            chara->model_0.controlState_2     = 10;
                            chara->model_0.stateStep_3 = 0;
                        }
                    }
                    else
                    {
                        chara->model_0.controlState_2     = 14;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    if (temp_s4 == 2)
                    {
                        if (field14C_2 != 0)
                        {
                            chara->model_0.controlState_2 = 23;
                        }
                        else
                        {
                            chara->model_0.controlState_2 = 26;
                        }

                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            chara->model_0.controlState_2               = 16;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.controlState_2     = 17;
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}

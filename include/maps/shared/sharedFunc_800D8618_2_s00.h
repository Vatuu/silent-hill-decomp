void sharedFunc_800D8618_2_s00(s_SubCharacter* chara)
{
    s32  animStatus;
    bool field14C_2;
    bool field14C_1;
    bool new_var;
    bool new_var2;
    s32  temp_a0; // Possibly `bool`.
    bool switchCond;

    switchCond = false;
    animStatus = chara->model_0.anim_4.status_0;

    new_var    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_1 = new_var;
    field14C_2 = new_var2;

    temp_a0 = sharedFunc_800DC50C_2_s00(chara);

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DEBCC_2_s00(chara);

        case 1:
            chara->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
            chara->model_0.stateStep_3                     = 2;
            break;

        case 2:
            if (temp_a0 != 0)
            {
                chara->model_0.stateStep_3 = 3;
            }
            else if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(0.5f))
            {
                sharedFunc_800DE6A8_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(2.5f));
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                sharedFunc_800DE6A8_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(2.5f));
                chara->model_0.stateStep_3 = 1;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = true;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3     = 4;
            }
            break;

        case 4:
            switchCond = true;
            break;
    }

    sharedFunc_800D57C8_0_s01(chara);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case false:
                    if (sharedFunc_800DC67C_2_s00(chara))
                    {
                        chara->model_0.state_2 = 27;
                    }
                    else if (!field14C_2)
                    {
                        if (chara->properties_E4.unk0.properties_120.val32 == 0 && !field14C_1 &&
                            func_80080514() < Q12(0.5f))
                        {
                            chara->model_0.state_2 = 21;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        chara->model_0.state_2 = 23;
                    }

                    chara->model_0.stateStep_3 = 0;
                    break;

                case true:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_2)
                        {
                            chara->model_0.state_2 = 10;
                        }
                        else
                        {
                            chara->model_0.state_2 = 13;
                        }

                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
            }
            break;

        case 1:
            chara->model_0.state_2               = 29;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 2:
            chara->model_0.state_2               = 30;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 32;
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

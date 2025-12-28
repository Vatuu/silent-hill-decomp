void sharedFunc_800D80EC_2_s00(s_SubCharacter* chara)
{
    bool temp_a0;
    bool unkField14C;
    s32  unkField150;
    s32  switchCond;
    s32  animStatus;

    switchCond  = 0;
    animStatus  = chara->model_0.anim_4.status_0;
    unkField150 = sharedData_800E21D0_0_s01.distance_150;
    unkField14C = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_a0     = sharedFunc_800DC50C_2_s00(chara);

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->properties_E4.unk0.properties_120.val32 = Q12(2.0f);
            if (Rng_RandQ12() < Q12(0.7f))
            {
                switchCond = 2;
                sharedFunc_800D529C_0_s01(chara, Q12(8.0f), chara->rotation_24.vy);
                chara->model_0.stateStep_3 = 4;
            }
            else
            {
                chara->model_0.stateStep_3 = 1;
            }
            break;

        case 1:
            if (temp_a0)
            {
                chara->model_0.stateStep_3 = 2;
            }
            break;

        case 4:
            switchCond = 2;

            if (temp_a0)
            {
                chara->model_0.stateStep_3 = 2;
            }
            else if (chara->moveSpeed_38 > Q12(1.5f))
            {
                chara->model_0.stateStep_3 = 5;
            }
            else if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(3.0f) ||
                     chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 1;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 1;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3     = 3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 3;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                chara->model_0.stateStep_3     = 6;
            }
            break;

        case 6:
            switchCond = 3;
            break;
    }

    if (switchCond >= 2 && switchCond < 4)
    {
        sharedFunc_800D57C8_0_s01(chara);
    }
    else
    {
        sharedFunc_800DEBCC_2_s00(chara);
        sharedFunc_800D5B10_0_s01(chara);
    }

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (chara->properties_E4.unk0.properties_120.val32 == 0 || unkField150 > Q12(2.0f))
                    {
                        if (!unkField14C)
                        {
                            chara->model_0.controlState_2 = 26;
                        }
                        else
                        {
                            chara->model_0.controlState_2 = 23;
                        }

                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (!unkField14C)
                        {
                            chara->model_0.controlState_2 = 13;
                        }
                        else
                        {
                            chara->model_0.controlState_2 = 11;
                        }

                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 2:
                    break;

                case 3:
                    if (sharedFunc_800D4A80_0_s01(chara) == switchCond)
                    {
                        chara->model_0.controlState_2     = 39;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
            }
            break;

        case 1:
            chara->model_0.controlState_2               = 29;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 2:
            chara->model_0.controlState_2               = 30;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.controlState_2     = 32;
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

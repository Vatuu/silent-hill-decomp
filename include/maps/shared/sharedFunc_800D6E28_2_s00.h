void sharedFunc_800D6E28_2_s00(s_SubCharacter* chara)
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

    animStatus = chara->model_0.anim_4.status_0;
    switchCond = 0;

    // @hack These flags/bitfields always need weird variable juggling, is there a way to remove it?
    sp10_temp    = sharedFunc_800D4A80_0_s01(chara);
    new_var4   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp10       = sp10_temp;
    cond       = false;
    field14C_0 = new_var4;
    field14C_1 = new_var2;
    field14C_2 = new_var3;

    temp_s5 = sharedFunc_800DC50C_2_s00(chara);

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DE7E0_2_s00(chara);
            chara->model_0.stateStep_3 = 1;
            break;

        case 1:
            cond                                           = true;
            chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
            chara->model_0.stateStep_3                     = 2;

        case 2:
            distFieldF8 = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
            angFieldF8  = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);

            if (!temp_s5)
            {
                if ((distFieldF8 < Q12(0.5f) && (angFieldF8 >= FP_ANGLE(-5.0f) && angFieldF8 <= FP_ANGLE(5.0f))) ||
                    (chara->properties_E4.unk0.flags_11C & CharaUnk0Flag_Unk31))
                {
                    chara->model_0.stateStep_3 = 0;
                }
                else if (chara->properties_E4.unk0.properties_120.val32 == 0)
                {
                    chara->model_0.stateStep_3 = 1;
                }
                else if (cond)
                {
                    if (sharedFunc_800DC200_2_s00(chara) && distFieldF8 > Q12(6.0f))
                    {
                        chara->model_0.stateStep_3 = 5;
                    }
                    else if (sharedFunc_800DC3BC_2_s00(chara) && distFieldF8 < Q12(2.0f) && Rng_RandQ12() < Q12(0.5f))
                    {
                        chara->model_0.stateStep_3 = 3;
                    }
                }
            }
            else
            {
                chara->model_0.stateStep_3 = 3;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 1;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3     = 4;
            }
            break;

        case 4:
            switchCond = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(24, false);
                chara->model_0.stateStep_3     = 6;
            }
            break;

        case 6:
            switchCond = 2;
            break;
    }

    sharedFunc_800D57C8_0_s01(chara);

    switch (Ai_AirScreamer_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_1 | field14C_0 | field14C_2)
                    {
                        chara->model_0.controlState_2     = 20;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            chara->model_0.controlState_2 = 6;
                        }
                        else
                        {
                            chara->model_0.controlState_2 = 5;
                        }

                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 2:
                    if (sp10 == 3)
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            chara->model_0.controlState_2 = 35;
                        }
                        else
                        {
                            chara->model_0.controlState_2 = 34;
                        }

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

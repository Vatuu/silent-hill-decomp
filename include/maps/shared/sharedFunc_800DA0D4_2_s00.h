void sharedFunc_800DA0D4_2_s00(s_SubCharacter* chara)
{
    s32  animStatus;
    s32  switchCond;
    s32  temp_fp;
    s32  field15C;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;
    bool cond;
    s32  temp_a0;

    animStatus     = chara->model_0.anim_4.status_0;
    switchCond     = 0;
    temp_fp        = sharedFunc_800D4A80_0_s01(chara);
    field15C       = sharedData_800E21D0_0_s01.field_15C;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;

    field14C_0 = field14C_0_tmp;
    field14C_1 = field14C_1_tmp;
    field14C_2 = field14C_2_tmp;

    cond = false;

    temp_a0 = sharedFunc_800DC438_2_s00(chara);
    switch (chara->model_0.stateStep_3)
    {
        case 0:
            if (sharedFunc_800DC30C_2_s00(chara) && Rng_RandQ12() < Q12(0.1f))
            {
                chara->model_0.stateStep_3 = 8;
            }
            else
            {
                chara->model_0.stateStep_3 = 2;
            }

        case 1:
            chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
            sharedFunc_800DECA4_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(3.0f));
            chara->model_0.stateStep_3 = 2;
            break;

        case 2:
            cond = true;

        case 3:
            if (temp_a0 == 2)
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (temp_a0 == 1)
            {
                chara->model_0.stateStep_3 = 8;
            }
            else if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(1.0f))
            {
                if (cond)
                {
                    switchCond = 1;
                }

                chara->model_0.stateStep_3 = 0;
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 1;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                chara->model_0.stateStep_3 = 3;

                if (field15C > 32)
                {
                    q19_12 angleDiff = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.pos_104) - chara->rotation_24.vy);
                    sharedFunc_800DEC84_2_s00(chara, Q12(3.0f), (angleDiff / 4) + chara->rotation_24.vy);
                    chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
                }
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(16, false);

                if (!field14C_1 && !field14C_0)
                {
                    chara->model_0.stateStep_3 = 6;
                }
                else
                {
                    chara->model_0.stateStep_3 = 7;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                chara->model_0.stateStep_3 = 5;
            }
            break;

        case 5:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 3;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(16, false);
                chara->model_0.stateStep_3     = 7;
            }
            break;

        case 6:
            switchCond = 3;

            if (field14C_2 || field14C_1 || field14C_0)
            {
                chara->model_0.stateStep_3 = 7;
            }
            else
            {
                switchCond = 2;
            }
            break;

        case 7:
            switchCond = 3;
            break;

        case 8:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 4;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(15, false);

                if (!field14C_1 && !field14C_0)
                {
                    chara->model_0.stateStep_3 = 10;
                }
                else
                {
                    chara->model_0.stateStep_3 = 11;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                chara->model_0.stateStep_3 = 9;
            }
            break;

        case 9:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 5;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
                chara->model_0.stateStep_3     = 11;
            }
            break;

        case 10:
            switchCond = 5;

            if (field14C_2 || field14C_1 || field14C_0)
            {
                chara->model_0.stateStep_3 = 11;
            }
            else
            {
                switchCond = 4;
            }
            break;

        case 11:
            switchCond = 5;
            break;
    }

    sharedFunc_800E021C_2_s00(chara, 1, 1);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (field14C_2)
                    {
                        chara->model_0.state_2     = 37;
                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (switchCond == 1)
                    {
                        s32 rand   = Rng_RandQ12();
                        s32 var_a0 = 0;

                        if (chara->properties_E4.unk0.field_E8_8 == 1)
                        {
                            var_a0 = Q12(0.1f);
                        }

                        if (rand < (Q12(0.7f) - (var_a0 * 2)))
                        {
                            chara->model_0.state_2     = 35;
                            chara->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 2:
                    if (temp_fp == 1)
                    {
                        if (field14C_2)
                        {
                            chara->model_0.state_2     = 8;
                            chara->model_0.stateStep_3 = 0;
                        }
                        else
                        {
                            chara->model_0.state_2     = 6;
                            chara->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 3:
                    if (temp_fp == 1)
                    {
                        if (field14C_2)
                        {
                            chara->model_0.state_2     = 8;
                            chara->model_0.stateStep_3 = 0;
                        }
                        else
                        {
                            chara->model_0.state_2     = 7;
                            chara->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 4:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            chara->model_0.state_2     = 22;
                            chara->model_0.stateStep_3 = 0;
                        }
                        else
                        {
                            chara->model_0.state_2     = 20;
                            chara->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 5:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            chara->model_0.state_2     = 22;
                            chara->model_0.stateStep_3 = 0;
                        }
                        else
                        {
                            chara->model_0.state_2     = 21;
                            chara->model_0.stateStep_3 = 0;
                        }
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            chara->model_0.state_2               = 44;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 45;
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

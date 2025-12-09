void sharedFunc_800D756C_2_s00(s_SubCharacter* chara)
{
    s32    switch3;
    s32    condModelStateIs2;
    s32    animStatus;
    q19_12 angle0;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   field14C_0_tmp;
    bool   field14C_1_tmp;
    bool   field14C_2_tmp;
    bool   temp_a0;
    q19_12 rngAngle0;
    q19_12 angleSubtract;
    q19_12 angle1;

    switch3           = 0;
    condModelStateIs2 = 0;
    animStatus        = chara->model_0.anim_4.status_0;
    angle0            = sharedData_800E21D0_0_s01.field_15C;

    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    field14C_2     = field14C_2_tmp;
    temp_a0        = sharedFunc_800DC50C_2_s00(chara);

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);

        case 1:
            sharedFunc_800DE6A8_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(2.0f));

            if (!sharedFunc_800DC3BC_2_s00(chara) || func_80080514() >= FP_ANGLE(36.0f))
            {
                chara->model_0.stateStep_3 = 2;
            }
            else
            {
                chara->model_0.stateStep_3 = 4;
            }
            break;

        case 2:
            condModelStateIs2 = 1;

        case 3:
            if (temp_a0)
            {
                chara->model_0.stateStep_3 = 4;
                break;
            }

            if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(1.0f))
            {
                if (condModelStateIs2)
                {
                    switch3 = 1;
                }

                chara->model_0.stateStep_3 = 1;
            }
            else if (!chara->properties_E4.unk0.properties_120.val32)
            {
                chara->model_0.stateStep_3 = 0;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                chara->model_0.stateStep_3 = 3;

                if (angle0 > (FP_ANGLE(2.9f)))
                {
                    angle1 = func_80080478(&chara->position_18, &chara->properties_E4.unk0.pos_104) - chara->rotation_24.vy;
                    angle1 = FP_ANGLE_NORM_S(angle1);
                    if (angle1 < FP_ANGLE(0.0f))
                    {
                        angle1 += FP_ANGLE(0.3f);
                    }

                    sharedFunc_800D529C_0_s01(chara, Q12(2.0f), (angle1 >> 2) + chara->rotation_24.vy);
                    chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
                }
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3                        = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);

                if (field14C_1 || field14C_0)
                {
                    chara->model_0.stateStep_3 = 7;
                }
                else
                {
                    chara->model_0.stateStep_3 = 6;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                chara->model_0.stateStep_3 = 5;
            }
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3                        = 3;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3     = 7;
            }
            break;

        case 6:
            switch3 = 3;
            if (field14C_2 || field14C_1 || field14C_0)
            {
                chara->model_0.stateStep_3 = 7;
            }
            else
            {
                switch3 = 2;
            }
            break;

        case 7:
            switch3 = 3;
            break;
    }

    sharedFunc_800D57C8_0_s01(chara);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switch3)
            {
                case 0:
                case 1:
                    if (field14C_2 == 0)
                    {
                        if (switch3 == 1)
                        {
                            rngAngle0     = func_80080514();
                            angleSubtract = FP_ANGLE(0.0f);

                            if (chara->properties_E4.unk0.field_E8_8 == switch3)
                            {
                                angleSubtract = FP_ANGLE(36.0f);
                            }

                            if (rngAngle0 < (FP_ANGLE(252.0f) - (angleSubtract * 2)))
                            {
                                chara->model_0.state_2     = 20;
                                chara->model_0.stateStep_3 = 0;
                            }
                        }
                    }
                    else
                    {
                        chara->model_0.state_2     = 22;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (!field14C_2)
                        {
                            chara->model_0.state_2 = 6;
                        }
                        else
                        {
                            chara->model_0.state_2 = 8;
                        }

                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 3:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_2)
                        {
                            chara->model_0.state_2 = 8;
                        }
                        else
                        {
                            chara->model_0.state_2 = 7;
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

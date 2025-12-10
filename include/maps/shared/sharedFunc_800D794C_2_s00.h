void sharedFunc_800D794C_2_s00(s_SubCharacter* chara)
{
    s32    switchCond;
    s32    animStatus;
    q19_12 dist0;
    q19_12 angle0;
    bool   field14C_2;
    q19_12 angle1;
    q19_12 angle2;
    bool   temp_s3;
    s32    var_s5;
    q19_12 angleAdd;

    switchCond = 0;
    angleAdd   = FP_ANGLE(0.0f);
    animStatus = chara->model_0.anim_4.status_0;
    dist0      = sharedData_800E21D0_0_s01.distance_150;
    angle0     = sharedData_800E21D0_0_s01.angle_154;
    field14C_2 = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;

    if (chara->properties_E4.unk0.field_E8_4)
    {
        angleAdd = Q12(0.1f);
    }

    temp_s3 = sharedFunc_800DC50C_2_s00(chara);
    var_s5  = 0;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            switchCond                                     = 1;
            chara->properties_E4.unk0.properties_120.val32 = Q12(2.0f);
            chara->flags_3E                               |= CharaFlag_Unk3;

        case 1:
            sharedFunc_800D529C_0_s01(chara, dist0 / 2, angle0);

            if (Rng_RandQ12() < ((angleAdd * 2) + FP_ANGLE(72.0f)))
            {
                chara->model_0.stateStep_3 = 2;
            }
            else
            {
                chara->model_0.stateStep_3 = 3;
            }

        default:
            break;

        case 2:
            var_s5 = 1;

            if (!temp_s3)
            {
                if (chara->properties_E4.unk0.properties_120.val32 != 0)
                {
                    if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(1.0f))
                    {
                        chara->model_0.stateStep_3 = 1;
                    }
                }
                else
                {
                    chara->model_0.stateStep_3 = 0;
                }
            }
            else
            {
                chara->model_0.stateStep_3 = 4;
            }
            break;

        case 3:
            sharedFunc_800D529C_0_s01(chara, dist0 / 2, angle0);

            if (temp_s3)
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 0;
            }
            else if (FP_ANGLE_NORM_S(angle0 - chara->rotation_24.vy) >= FP_ANGLE(-10.0f) &&
                     FP_ANGLE_NORM_S(angle0 - chara->rotation_24.vy) < FP_ANGLE(10.0f))
            {
                var_s5 = 2;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3     = 5;
            }
            break;

        case 5:
            switchCond = 2;
            break;
    }

    if (var_s5 == 1)
    {
        sharedFunc_800D57C8_0_s01(chara);
    }
    else
    {
        sharedFunc_800D598C_0_s01(chara);
    }

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_2 == 0)
                    {
                        chara->model_0.state_2     = 21;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        chara->model_0.state_2     = 8;
                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 1:
                    angle1 = sharedFunc_800DC894_2_s00(chara, dist0);
                    angle2 = sharedFunc_800DC6E4_2_s00(chara, dist0);
                    if (Rng_RandQ12() < angle1)
                    {
                        if (chara->properties_E4.unk0.field_E8_0 == 3)
                        {
                            sharedFunc_800DD13C_2_s00(chara, chara->field_40 + 1, Q12(0.6f));
                        }

                        chara->model_0.state_2                 = 23;
                        chara->model_0.stateStep_3             = 0;
                        chara->properties_E4.player.flags_11C |= CharaFlag_Unk5;
                    }
                    else if (Rng_RandQ12() < angle2)
                    {
                        chara->model_0.state_2                 = 27;
                        chara->model_0.stateStep_3             = 0;
                        chara->properties_E4.player.flags_11C |= CharaFlag_Unk5;
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

void sharedFunc_800D6A7C_2_s00(s_SubCharacter* chara)
{
    s32 sp10;
    s32 flag2;
    s32 flag0;
    s32 dist0;
    s32 temp_s5;
    s32 flag1;
    s32 angle0;
    s32 var_s3;
    s32 var_s7;
    s32 animStatus;
    s32 tmp1, tmp2, tmp3;

    animStatus = chara->model_0.anim_4.status_0;
    var_s3     = 0;
    sp10       = sharedFunc_800D4A80_0_s01(chara);
    var_s7     = 0;
    tmp3       = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    tmp2       = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    tmp1       = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    flag0      = tmp3;
    flag1      = tmp2;
    flag2      = tmp1;

    temp_s5 = sharedFunc_800DC50C_2_s00(chara);
    switch (chara->model_0.stateStep_3)
    {
        case 64:
            sharedFunc_800DD4EC_2_s00(chara);
            chara->model_0.stateStep_3 = 1;
            break;

        case 0:
            sharedFunc_800D529C_0_s01(chara, Q12(5.0f), chara->rotation_24.vy);
            sharedFunc_800DE6A8_2_s00(chara, &chara->properties_E4.unk0.field_F8, Q12(4.0f));
            chara->model_0.stateStep_3 = 1;
            break;

        case 1:
            var_s7                                         = 1;
            chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
            chara->model_0.stateStep_3                     = 2;

        case 2:
            dist0  = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
            angle0 = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);
            if (!temp_s5)
            {
                if ((dist0 < Q12(1.0f) && (angle0 >= FP_ANGLE(-5.0f) && angle0 <= FP_ANGLE(5.0f))) ||
                    chara->properties_E4.player.flags_11C < 0)
                {
                    chara->model_0.stateStep_3 = 0;
                }
                else
                {
                    if (!chara->properties_E4.unk0.properties_120.val32)
                    {
                        chara->model_0.stateStep_3 = 1;
                    }
                    else if (var_s7 != 0)
                    {
                        if (sharedFunc_800DC200_2_s00(chara) && dist0 > Q12(7.0f))
                        {
                            chara->model_0.stateStep_3 = 5;
                        }
                        else if (sharedFunc_800DC3BC_2_s00(chara) && dist0 < Q12(3.0f) && func_80080514() < FP_ANGLE(252.0f))
                        {
                            chara->model_0.stateStep_3 = 3;
                        }
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
                var_s3                         = 1;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3     = 4;
            }
            break;

        case 4:
            var_s3 = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                var_s3                         = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                chara->model_0.stateStep_3     = 6;
            }
            break;

        case 6:
            var_s3 = 2;
            break;
    }

    sharedFunc_800D57C8_0_s01(chara);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (var_s3)
            {
                case 0:
                    if ((flag1 | flag0 | flag2) != 0)
                    {
                        chara->model_0.state_2     = 20;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    if ((animStatus == ANIM_STATUS(23, true)) || (animStatus == ANIM_STATUS(25, true)))
                    {
                        if ((flag1 | flag0 | flag2) == 0)
                        {
                            chara->model_0.state_2 = 4;
                        }
                        else
                        {
                            chara->model_0.state_2 = 6;
                        }
                        chara->model_0.stateStep_3 = 0;
                        break;
                    }
                    if (sharedFunc_800DC0A8_2_s00(chara) != false)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 2:
                    if (sp10 == 3)
                    {
                        if ((flag1 | flag0 | flag2) == 0)
                        {
                            chara->model_0.state_2 = 0x21;
                        }
                        else
                        {
                            chara->model_0.state_2 = 0x23;
                        }
                        chara->model_0.stateStep_3 = 0;
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
            if (chara->health_B0 <= 0)
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

void sharedFunc_800D83F8_2_s00(s_SubCharacter* chara)
{
    bool var_s1;
    bool var_s2;
    s32  animStatus;

    var_s1     = false;
    var_s2     = false;
    animStatus = chara->model_0.anim_4.status_0;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->model_0.stateStep_3 = 1;

        case 1:
            if (animStatus == ANIM_STATUS(19, true))
            {
                chara->model_0.stateStep_3     = 2;
                chara->model_0.anim_4.status_0 = 4;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(2, true) && chara->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                chara->model_0.stateStep_3           = 3;
                chara->properties_E4.unk0.flags_11C |= 1 << 5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                var_s1 = true;
            }
            else if (chara->field_4C == NO_VALUE)
            {
                var_s1                     = true;
                var_s2                     = true;
                chara->model_0.stateStep_3 = 4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                var_s1 = true;
                var_s2 = true;
            }
            break;
    }

    sharedFunc_800DE940_2_s00(chara);
    sharedFunc_800D5C90_0_s01(chara);

    switch (Chara_DamageTake(chara, Q12(1.2f)))
    {
        case 0:
            if (var_s1)
            {
                if (chara->properties_E4.unk0.field_E8_8 == 3)
                {
                    chara->properties_E4.unk0.field_E8_8 = 2;

                    if (var_s2 && func_80080514() < FP_ANGLE(180.0f))
                    {
                        chara->model_0.state_2 = 24;
                    }
                    else
                    {
                        chara->model_0.state_2 = 23;
                    }
                }
                else
                {
                    if (var_s2)
                    {
                        chara->model_0.state_2 = 24;
                    }
                    else if (func_80080514() < FP_ANGLE(180.0f))
                    {
                        chara->model_0.state_2 = 24;
                    }
                    else
                    {
                        chara->model_0.state_2 = 23;
                    }
                }
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 1:
            chara->model_0.state_2               = 29;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= 1 << 3;
            break;

        case 2:
            chara->model_0.state_2               = 30;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= 1 << 3;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 32;
            chara->model_0.stateStep_3 = 0;
            if (chara->health_B0 <= 0)
            {
                chara->properties_E4.unk0.flags_11C |= 1 << 6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= 1 << 3;
            }
            break;
    }
}

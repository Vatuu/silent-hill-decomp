void sharedFunc_800DB038_2_s00(s_SubCharacter* chara)
{
    bool var_s1;
    bool var_s2;
    s32  animStatus;

    var_s1 = false;
    var_s2 = false;

    animStatus = chara->model_0.anim_4.status_0;
    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->model_0.stateStep_3 = 1;

        case 1:
            if (animStatus == ANIM_STATUS(17, true))
            {
                chara->model_0.stateStep_3     = 2;
                chara->model_0.anim_4.status_0 = 6;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(3, true) && chara->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                chara->model_0.stateStep_3           = 3;
                chara->properties_E4.unk0.flags_11C |= 1 << 5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(17, true))
            {
                var_s1 = 1;
            }
            else if (chara->field_4C == NO_VALUE)
            {
                var_s1                     = 1;
                var_s2                     = 1;
                chara->model_0.stateStep_3 = 4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                var_s1 = 1;
                var_s2 = 1;
            }
            break;
    }

    sharedFunc_800DEE24_2_s00(chara);
    sharedFunc_800E0514_2_s00(chara);

    switch (Chara_DamageTake(chara, Q12(1.2f)))
    {
        case 0:
            if (var_s1)
            {
                if (chara->properties_E4.unk0.field_E8_8 == 5 && var_s2)
                {
                    chara->properties_E4.unk0.field_E8_8 = 1;
                    chara->model_0.state_2               = 42;
                }
                else
                {
                    chara->model_0.state_2 = 39;
                }
                chara->model_0.stateStep_3 = 0;
            }
            break;
        case 1:
        case 2:
            chara->model_0.state_2               = 44;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= 1 << 3;
            break;
        case 3:
        case 4:
            chara->model_0.state_2     = 45;
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

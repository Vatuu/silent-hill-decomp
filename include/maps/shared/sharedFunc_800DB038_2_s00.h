void sharedFunc_800DB038_2_s00(s_SubCharacter* chara)
{
    bool cond0;
    bool cond1;
    s32  animStatus;

    cond0 = false;
    cond1 = false;

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
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(17, true))
            {
                cond0 = true;
            }
            else if (chara->field_44.field_8 == NO_VALUE)
            {
                cond0                      = true;
                cond1                      = true;
                chara->model_0.stateStep_3 = 4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800DEE24_2_s00(chara);
    sharedFunc_800E0514_2_s00(chara);

    switch (Chara_DamageTake(chara, Q12(1.2f)))
    {
        case 0:
            if (cond0)
            {
                if (chara->properties_E4.unk0.field_E8_8 == 5 && cond1)
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
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 45;
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

void sharedFunc_800D5B88_2_s00(s_SubCharacter* chara)
{
    bool cond0;
    bool cond1;
    s32  animStatus;

    cond0     = false;
    cond1     = false;
    animStatus = chara->model_0.anim_4.status_0;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->model_0.stateStep_3 = 1;

        case 1:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                chara->model_0.stateStep_3     = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(1, true) && chara->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                chara->model_0.stateStep_3             = 3;
                chara->properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
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
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800DF358_2_s00(chara);

    switch (Chara_DamageTake(chara, Q12(1.2f)))
    {
        case 0:
            if (cond0)
            {
                if (chara->properties_E4.unk0.field_E8_8 == 3)
                {
                    chara->properties_E4.unk0.field_E8_8 = 2;

                    if (cond1 && Rng_RandQ12() < FP_ANGLE(180.0f))
                    {
                        chara->model_0.state_2 = 11;
                    }
                    else
                    {
                        chara->model_0.state_2 = 10;
                    }
                }
                else
                {
                    if (cond1)
                    {
                        chara->model_0.state_2 = 11;
                    }
                    else if (Rng_RandQ12() < FP_ANGLE(180.0f))
                    {
                        chara->model_0.state_2 = 11;
                    }
                    else
                    {
                        chara->model_0.state_2 = 10;
                    }
                }

                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 1:
        case 2:
            chara->model_0.state_2                 = 16;
            chara->model_0.stateStep_3             = 0;
            chara->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 17;
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                chara->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }
}

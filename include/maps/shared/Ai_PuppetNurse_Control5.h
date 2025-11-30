void Ai_PuppetNurse_Control5(s_SubCharacter* nurse)
{
    s32 modelState;

    if (!nurse->model_0.stateStep_3)
    {
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(6, false);
        nurse->properties_E4.player.field_104 = 0;
        nurse->model_0.stateStep_3++;
    }

    sharedFunc_800CE7C8_3_s03(nurse);

    modelState = nurse->model_0.stateStep_3;
    if (modelState == 1)
    {
        if (nurse->properties_E4.puppetNurse.flags_122 & (1 << 0))
        {
            nurse->model_0.stateStep_3 = 2;
        }
        else
        {
            if (nurse->properties_E4.player.field_104 <= Q12(1.5f))
            {
                if (func_80070320())
                {
                    nurse->model_0.state_2 = modelState;
                    nurse->model_0.stateStep_3 = 0;
                    nurse->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                    return;
                }
            }
            else
            {
                nurse->model_0.state_2 = 13;
                nurse->model_0.stateStep_3 = 0;
                return;
            }
        }
    }
    else if (modelState == 2)
    {
        if ((&g_SysWork.player_4C.chara_0)->attackReceived_41 == NO_VALUE)
        {
            nurse->model_0.state_2 = 8;
            nurse->model_0.stateStep_3 = 0;
            return;
        }

        if (nurse->properties_E4.puppetNurse.field_104 >= Q12(1.5f))
        {
            g_SysWork.player_4C.chara_0.damage_B4.amount_C += FP_TO(D_800ADA0C, Q12_SHIFT);
            nurse->properties_E4.puppetNurse.field_104 = 0;
        }
    }

    nurse->properties_E4.puppetNurse.field_104 += g_DeltaTime0;
}

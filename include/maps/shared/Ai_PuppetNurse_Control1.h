void Ai_PuppetNurse_Control1(s_SubCharacter* nurse)
{
    s_SubCharacter* localNurse;

    localNurse = nurse;

    if (!nurse->model_0.stateStep_3)
    {
        if (!nurse->properties_E4.puppetNurse.field_11E)
        {
            nurse->model_0.anim_4.status_0 = 2;
        }
        else
        {
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
            {
                nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_1, false);
            }
            else
            {
                nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_21, false);
            }
        }

        nurse->properties_E4.puppetNurse.field_11E = func_80070320();
        localNurse->model_0.stateStep_3++;
        nurse->properties_E4.puppetNurse.field_104 = Q12(1.0f);
        return;
    }

    if (nurse->properties_E4.puppetNurse.field_104 < Q12(0.0f) && (nurse->properties_E4.puppetNurse.flags_122 & PuppetNurseFlag_0))
    {
        nurse->properties_E4.puppetNurse.field_104 = Q12(100.0f);
        Ai_PuppetNurse_SfxPlay(nurse, 0);
    }

    if (localNurse->model_0.anim_4.status_0 == ANIM_STATUS(PuppetNurseAnim_18, false))
    {
        localNurse->model_0.controlState_2 = PuppetNurseControl_9;
        localNurse->model_0.stateStep_3 = 0;
    }

    if (nurse->properties_E4.puppetNurse.field_11E && g_SysWork.playerWork_4C.player_0.attackReceived_41 == NO_VALUE)
    {
        localNurse->model_0.controlState_2 = PuppetNurseControl_8;
        localNurse->model_0.stateStep_3 = 0;
        return;
    }

    Ai_PuppetNurse_Move(localNurse);
    nurse->properties_E4.puppetNurse.field_104 -= g_DeltaTime;
}


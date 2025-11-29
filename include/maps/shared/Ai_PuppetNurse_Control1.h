void Ai_PuppetNurse_Control1(s_SubCharacter* nurse)
{
    s_SubCharacter* nurseCpy;
    nurseCpy = nurse;
    if (!nurse->model_0.stateStep_3)
    {
        if (!nurse->properties_E4.unk1.field_11E)
        {
            nurse->model_0.anim_4.status_0 = 2;
        }
        else
        {
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
            {
                nurse->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            }
            else
            {
                nurse->model_0.anim_4.status_0 = ANIM_STATUS(21, false);
            }
        }
        
        nurse->properties_E4.unk1.field_11E = func_80070320();
        nurseCpy->model_0.stateStep_3++;
        nurse->properties_E4.unk1.field_104 = 0x1000;
        return;
    }
    if (nurse->properties_E4.unk1.field_104 < 0 && (nurse->properties_E4.unk1.flags_122 & 1))
    {
        nurse->properties_E4.unk1.field_104 = Q12(100.0f);
        Ai_PuppetNurse_SfxPlay(nurse, 0);
    }
    if (nurseCpy->model_0.anim_4.status_0 == ANIM_STATUS(18, false))
    {
        nurseCpy->model_0.state_2 = 9;
        nurseCpy->model_0.stateStep_3 = 0;
    }
    if (nurse->properties_E4.unk1.field_11E && g_SysWork.player_4C.chara_0.attackReceived_41 == NO_VALUE)
    {
        nurseCpy->model_0.state_2 = 8;
        nurseCpy->model_0.stateStep_3 = 0;
        return;
    }
    Ai_NursePuppet_Move(nurseCpy);
    nurse->properties_E4.unk1.field_104 -= g_DeltaTime0;
}


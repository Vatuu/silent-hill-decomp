void Ai_PuppetNurse_Control2(s_SubCharacter* nurse)
{
    s32 moveSpeed;

    if (!nurse->model_0.stateStep_3)
    {
        Ai_PuppetNurse_SfxPlay(nurse, 2);
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_2, false);
        nurse->model_0.stateStep_3++;
    }
    if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(PuppetNurseAnim_18, false))
    {
        nurse->model_0.state_2 = PuppetNurseControl_9;
        nurse->model_0.stateStep_3 = 0;
    }

    Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
}


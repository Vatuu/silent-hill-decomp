void Ai_PuppetNurse_Control13(s_SubCharacter* nurse)
{
    if (nurse->model_0.stateStep_3 == 0)
    {
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_10, false);
        nurse->model_0.stateStep_3++;
    }

    if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(PuppetNurseAnim_18, false))
    {
        nurse->model_0.controlState_2 = PuppetNurseControl_9;
        nurse->model_0.stateStep_3    = 0;
    }

    Chara_MoveSpeedUpdate3(nurse, Q12(4.0f), Q12(0.0f));
}

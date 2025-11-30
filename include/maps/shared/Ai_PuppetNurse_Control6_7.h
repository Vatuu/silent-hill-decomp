void Ai_PuppetNurse_Control6_7(s_SubCharacter* nurse, s32 arg1)
{
    if (!nurse->model_0.stateStep_3)
    {
        Ai_PuppetNurse_SfxPlay(nurse, arg1 + 1);

        if (arg1)
        {
            nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_8, false);
        }
        else
        {
            nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_7, false);
        }

        nurse->model_0.stateStep_3++;
    }

    if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(PuppetNurseAnim_18, false))
    {
        nurse->model_0.state_2 = 9;
        nurse->model_0.stateStep_3 = 0;
    }

    Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
}

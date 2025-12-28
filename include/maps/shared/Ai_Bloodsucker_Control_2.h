void Ai_Bloodsucker_Control_2(s_SubCharacter* bloodsucker)
{
#ifdef MAP3_S03
    if (bloodsucker->model_0.anim_4.status_0 == ((bloodsucker->model_0.stateStep_3 * 2) + 9))
    {
        bloodsucker->model_0.anim_4.status_0 = (bloodsucker->model_0.stateStep_3 * 2) + 22;
    }

    if (g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-140.75f))
    {
        bloodsucker->model_0.state_2 = BloodsuckerControl_3;
    }

    bloodsucker->properties_E4.bloodsucker.timer_F0 = Q12(0.3f);
#endif
}

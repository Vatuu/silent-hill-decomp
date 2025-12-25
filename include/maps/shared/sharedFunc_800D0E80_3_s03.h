void sharedFunc_800D0E80_3_s03(s_SubCharacter* bloodsucker)
{
    if (bloodsucker->model_0.anim_4.status_0 == ((bloodsucker->model_0.stateStep_3 * 2) + 23))
    {
        bloodsucker->model_0.anim_4.status_0 = (bloodsucker->model_0.stateStep_3 * 2) + 8;
    }

    if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-140.5f))
    {
        bloodsucker->model_0.state_2 = 2;
    }

    bloodsucker->properties_E4.bloodsucker.timer_F0 = Q12(1.0f);
}

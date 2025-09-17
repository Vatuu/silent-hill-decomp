void sharedFunc_800D88C0_0_s00(s_SubCharacter* playerChara, s32 arg1)
{
    playerChara->properties_E4.player.field_F4 = 1;

    if (arg1 != 0)
    {
        playerChara->model_0.anim_4.status_0      = ANIM_STATUS(PlayerAnim_TransitionToStill, true);
        playerChara->model_0.anim_4.keyframeIdx_8 = 0;
        playerChara->model_0.anim_4.time_4        = Q12(0.0f);
        playerChara->model_0.anim_4.alpha_A       = Q12(1.0f);
    }
    else
    {
        playerChara->properties_E4.player.afkTimer_E8 = FP_TIME(0.0f);
        playerChara->model_0.stateStep_3              = 0;
    }

    playerChara->model_0.anim_4.flags_2 |= AnimFlag_Unlocked;
}

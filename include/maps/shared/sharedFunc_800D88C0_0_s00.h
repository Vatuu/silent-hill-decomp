void sharedFunc_800D88C0_0_s00(s_SubCharacter* player, bool cond)
{
    player->properties_E4.player.field_F4 = 1;

    if (cond)
    {
        player->model_0.anim_4.status_0      = ANIM_STATUS(HarryAnim_TransitionToStill, true);
        player->model_0.anim_4.keyframeIdx_8 = 0;
        player->model_0.anim_4.time_4        = Q12(0.0f);
        player->model_0.anim_4.alpha_A       = Q12(1.0f);
    }
    else
    {
        player->properties_E4.player.afkTimer_E8 = Q12(0.0f);
        player->model_0.stateStep_3              = 0;
    }

    player->model_0.anim_4.flags_2 |= AnimFlag_Unlocked;
}

void sharedFunc_800D8904_0_s00(s_SubCharacter* player, q19_12 afkTime)
{
    player->properties_E4.player.moveDistance_126 = Q12(0.0f);
    player->properties_E4.player.runTimer_F8            = Q12(0.0f);
    player->properties_E4.player.field_F0               = Q12(0.0f);
    player->properties_E4.player.afkTimer_E8            = afkTime;
    player->model_0.stateStep_3                         = 0;
}

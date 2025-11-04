void sharedFunc_800D8904_0_s00(s_SubCharacter* playerChara, q19_12 afkTime)
{
    playerChara->properties_E4.player.playerMoveDistance_126 = Q12(0.0f);
    playerChara->properties_E4.player.runTimer_F8            = Q12(0.0f);
    playerChara->properties_E4.player.field_F0               = 0;
    playerChara->properties_E4.player.afkTimer_E8            = afkTime;
    playerChara->model_0.stateStep_3                         = 0;
}

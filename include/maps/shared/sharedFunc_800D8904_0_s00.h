void sharedFunc_800D8904_0_s00(s_SubCharacter* playerChara, s32 afkTime)
{
    playerChara->properties_E4.player.playerMoveDistance_126 = 0;
    playerChara->properties_E4.player.runTimer_F8            = 0;
    playerChara->properties_E4.player.field_F0               = 0;
    playerChara->properties_E4.player.afkTimer_E8            = afkTime;
    playerChara->model_0.stateStep_3                         = 0;
}

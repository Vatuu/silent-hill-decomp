void sharedFunc_800D2E74_0_s00(void)
{
#if defined(MAP0_S01)
    s_SubCharacter*       playerChara;
    s_MainCharacterExtra* playerExtra;

    playerChara = &g_SysWork.player_4C.chara_0;
    playerExtra = &g_SysWork.player_4C.extra_128;

    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(2.3f);
    g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124       = FP_ANGLE(180.0f);
    g_Player_HeadingAngle                                                   = FP_ANGLE(180.0f);

    Player_ExtraStateSet(playerChara, playerExtra, PlayerState_FallBackward);
#endif
}

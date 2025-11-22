void sharedFunc_800D2E84_0_s00(void)
{
#if defined(MAP6_S04)
    s_MainCharacterExtra* playerExtra;
    s_SubCharacter*       playerChara;

    playerChara = &g_SysWork.player_4C.chara_0;
    playerExtra = &g_SysWork.player_4C.extra_128;

    func_8005DC1C(Sfx_Unk1317, &playerChara->position_18, Q8_CLAMPED(0.125f), 0);

    Player_ExtraStateSet(playerChara, playerExtra, PlayerState_DamageFeetFront);
#endif
}

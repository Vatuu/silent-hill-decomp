void sharedFunc_800D2D44_0_s00(void)
{
    s_MainCharacterExtra* playerExtra;
    s_SubCharacter*       playerChara;

    playerExtra = &g_SysWork.player_4C.extra_128;
    playerChara = &g_SysWork.player_4C.chara_0;

    playerExtra->model_0.anim_4.flags_2 &= ~AnimFlag_Unlocked;
    playerChara->model_0.anim_4.flags_2 &= ~AnimFlag_Unlocked;
}

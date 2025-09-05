void sharedFunc_800D2D44_0_s00()
{
    s_MainCharacterExtra* extra = &g_SysWork.player_4C.extra_128;
    s_SubCharacter*       chara = &g_SysWork.player_4C.chara_0;

    extra = &g_SysWork.player_4C.extra_128;
    chara = &g_SysWork.player_4C.chara_0;

    extra->model_0.anim_4.flags_2 &= ~AnimFlag_Unlocked;
    chara->model_0.anim_4.flags_2 &= ~AnimFlag_Unlocked;
}

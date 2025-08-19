void sharedFunc_800D9078_0_s00(s_SubCharacter* chara)
#ifdef SHARED_FUNC_IMPL
{
    chara->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
}
#else
;
#endif

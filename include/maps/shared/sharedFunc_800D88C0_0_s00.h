void sharedFunc_800D88C0_0_s00(s_SubCharacter* playerChara, s32 arg1)
{
    playerChara->properties_E4[PlayerProperty_Unk4] = 1;

    if (arg1 != 0)
    {
        playerChara->model_0.anim_4.animIdx_0      = 3;
        playerChara->model_0.anim_4.keyframeIdx0_8 = 0;
        playerChara->model_0.anim_4.time_4         = 0;
        playerChara->model_0.anim_4.keyframeIdx1_A = FP_TO(1, Q12_SHIFT);
    }
    else
    {
        playerChara->properties_E4[PlayerProperty_AfkTimer] = 0;
        playerChara->model_0.isAnimStateUnchanged_3         = 0;
    }

    playerChara->model_0.anim_4.flags_2 |= AnimFlag_Unk1;
}

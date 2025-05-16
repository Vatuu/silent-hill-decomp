void Ai_HangedScratcher_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.state_2 == 0)
    {
        sharedFunc_800CFCA8_5_s00(chara);
    }

    sharedFunc_800CFF74_5_s00(chara);
    sharedFunc_800D029C_5_s00(chara);
    sharedFunc_800D26D8_5_s00(chara);
    sharedFunc_800D2844_5_s00(chara, arg1, arg2);
    sharedFunc_800D2C18_5_s00(chara);
    sharedFunc_800D3300_5_s00(chara);
}

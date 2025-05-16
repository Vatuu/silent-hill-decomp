void Ai_Cybil_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.stage_2 == 0)
    {
        sharedSymbol_800D9AD0_0_s01(chara);
    }

    sharedSymbol_800D8A68_0_s01(chara, arg2);
    sharedFunc_800D88D0_0_s01(chara, arg2);
    sharedFunc_800D8888_0_s01(chara, arg1, arg2);
}

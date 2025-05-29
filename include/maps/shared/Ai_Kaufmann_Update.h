void Ai_Kaufmann_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Kaufmann_Init(chara);
    }

    sharedSymbol_800CF470_3_s00(chara, arg2);
    sharedFunc_800CF2D8_3_s00(chara, arg2);
    sharedFunc_800CF290_3_s00(chara, arg1, arg2);
}

void Ai_Kaufmann_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Kaufmann_Init(chara);
    }

    sharedSymbol_800CF470_3_s00(chara, coords);
    sharedFunc_800CF2D8_3_s00(chara, coords);
    sharedFunc_800CF290_3_s00(chara, anmHeader, coords);
}

void Ai_Cybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Cybil_Init(chara);
    }

    sharedSymbol_800D8A68_0_s01(chara, coords);
    sharedFunc_800D88D0_0_s01(chara, coords);
    sharedFunc_800D8888_0_s01(chara, anmHeader, coords);
}

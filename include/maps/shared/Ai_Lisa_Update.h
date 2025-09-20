void Ai_Lisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Lisa_Init(chara);
    }

    sharedSymbol_800D0ADC_3_s04(chara, coords);
    sharedFunc_800D0944_3_s04(chara, coords);
    sharedFunc_800D08FC_3_s04(chara, anmHeader, coords);
}

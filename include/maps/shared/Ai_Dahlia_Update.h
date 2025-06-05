void Ai_Dahlia_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Dahlia_Init(chara);
    }

    sharedSymbol_800CD4A0_2_s01(chara, coords);
    sharedFunc_800CD2C8_2_s01(chara, coords);
    sharedFunc_800CD280_2_s01(chara, arg1, coords);
}

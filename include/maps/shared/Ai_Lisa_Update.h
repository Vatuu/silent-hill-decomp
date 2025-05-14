void Ai_Lisa_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.field_2 == 0)
    {
        sharedFunc_800D1350_3_s04(chara);
    }

    sharedSymbol_800D0ADC_3_s04(chara, arg2);
    sharedFunc_800D0944_3_s04(chara, arg2);
    sharedFunc_800D08FC_3_s04(chara, arg1, arg2);
}

void Ai_Alessa_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Alessa_Init(chara);
    }

    sharedFunc_800CEEDC_3_s02(chara, coords);
    sharedFunc_800CED44_3_s02(chara, coords);
    sharedFunc_800CECFC_3_s02(chara, anmHeader, coords);
}

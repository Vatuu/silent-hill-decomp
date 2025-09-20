void Ai_Romper_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Romper_Init(chara);
    }
    else if (g_DeltaTime0 != FP_TIME(0.0))
    {
        sharedFunc_800E6420_2_s02(chara);
        sharedFunc_800E66E8_2_s02(chara);
        sharedFunc_800E8730_2_s02(chara);
        sharedFunc_800E8DFC_2_s02(chara);
    }

    sharedFunc_800E8A40_2_s02(chara, anmHdr, coords);
    sharedFunc_800E60FC_2_s02(chara);
}

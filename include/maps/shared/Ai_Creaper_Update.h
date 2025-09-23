void Ai_Creaper_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Creaper_Init(chara);
    }

    if (g_DeltaTime0 != FP_TIME(0.0))
    {
        sharedFunc_800D7EE8_1_s02(chara);
        sharedFunc_800D8244_1_s02(chara);
        sharedFunc_800D983C_1_s02(chara);
    }

    sharedFunc_800D9960_1_s02(chara, anmHdr, coords);
    sharedFunc_800D99D0_1_s02(chara);
}

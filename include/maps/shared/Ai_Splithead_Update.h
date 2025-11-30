void Ai_Splithead_Update(s_SubCharacter* splithead, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    sharedData_800D8610_1_s05 = coords;

    if (splithead->model_0.state_2 == 0)
    {
        Ai_Splithead_Init(splithead);
    }

    if (g_DeltaTime0 != Q12(0.0))
    {
        sharedFunc_800CFE94_1_s05(splithead);
        sharedFunc_800D0054_1_s05(splithead);
        sharedFunc_800D267C_1_s05(splithead);
        sharedFunc_800D3AFC_1_s05(splithead);
    }

    sharedFunc_800D274C_1_s05(splithead, anmHdr);

    if (g_DeltaTime0 != Q12(0.0))
    {
        sharedFunc_800D2D74_1_s05(splithead);
        sharedFunc_800D3B30_1_s05(splithead);
    }

    sharedFunc_800D4070_1_s05(splithead);
    sharedFunc_800CF990_1_s05(splithead);
}

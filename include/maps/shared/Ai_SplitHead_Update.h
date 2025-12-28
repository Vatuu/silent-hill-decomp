void Ai_SplitHead_Update(s_SubCharacter* splitHead, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    sharedData_800D8610_1_s05 = coords;

    // Initialize.
    if (splitHead->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_SplitHead_Init(splitHead);
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        Ai_SplitHead_DamageTake(splitHead);
        sharedFunc_800D0054_1_s05(splitHead);
        sharedFunc_800D267C_1_s05(splitHead);
        sharedFunc_800D3AFC_1_s05(splitHead);
    }

    sharedFunc_800D274C_1_s05(splitHead, anmHdr);

    if (g_DeltaTime0 != Q12(0.0f))
    {
        sharedFunc_800D2D74_1_s05(splitHead);
        sharedFunc_800D3B30_1_s05(splitHead);
    }

    sharedFunc_800D4070_1_s05(splitHead);
    sharedFunc_800CF990_1_s05(splitHead);
}

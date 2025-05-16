void Ai_Splithead_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    sharedData_800D8610_1_s05 = arg2;

    if (chara->model_0.stage_2 == 0)
    {
        sharedFunc_800CF8D8_1_s05(chara);
    }

    if (g_DeltaTime0 != 0)
    {
        sharedFunc_800CFE94_1_s05(chara);
        sharedFunc_800D0054_1_s05(chara);
        sharedFunc_800D267C_1_s05(chara);
        sharedFunc_800D3AFC_1_s05(chara);
    }

    sharedFunc_800D274C_1_s05(chara, arg1);

    if (g_DeltaTime0 != 0)
    {
        sharedFunc_800D2D74_1_s05(chara);
        sharedFunc_800D3B30_1_s05(chara);
    }

    sharedFunc_800D4070_1_s05(chara);
    sharedFunc_800CF990_1_s05(chara);
}

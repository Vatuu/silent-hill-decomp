void Ai_Creaper_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Creaper_Init(chara);
    }

    if (g_DeltaTime0 != 0)
    {
        sharedFunc_800D7EE8_1_s02(chara);
        sharedFunc_800D8244_1_s02(chara);
        sharedFunc_800D983C_1_s02(chara);
    }

    sharedFunc_800D9960_1_s02(chara, arg1, arg2);
    sharedFunc_800D99D0_1_s02(chara);
}

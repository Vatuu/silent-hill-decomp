void Ai_Alessa_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Alessa_Init(chara);
    }

    sharedFunc_800CEEDC_3_s02(chara, arg2);
    sharedFunc_800CED44_3_s02(chara, arg2);
    sharedFunc_800CECFC_3_s02(chara, arg1, arg2);
}

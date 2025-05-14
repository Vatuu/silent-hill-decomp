void Ai_BloodyLisa_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.field_2 == 0)
    {
        sharedFunc_800D5CB4_7_s01(chara);
    }

    sharedFunc_800D5B3C_7_s01(chara, arg2);
    sharedFunc_800D59A4_7_s01(chara, arg2);
    sharedFunc_800D595C_7_s01(chara, arg1, arg2);
}

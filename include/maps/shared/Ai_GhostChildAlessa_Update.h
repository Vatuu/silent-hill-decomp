void Ai_GhostChildAlessa_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.charaId_0 != Chara_GhostChildAlessa)
    {
        Ai_GhostChildAlessa_Init(chara);
    }

    sharedFunc_800D4C0C_7_s01(chara, arg2);
    sharedFunc_800D4A74_7_s01(chara, arg2);
    sharedFunc_800D4A2C_7_s01(chara, arg1, arg2);
}

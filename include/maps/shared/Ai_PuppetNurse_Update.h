void Ai_PuppetNurse_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_PuppetNurse_Init(chara, 0);
    }

    sharedFunc_800CDAB8_3_s03(chara, arg1, arg2);
}

void Ai_PuppetNurse_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_PuppetNurse_Init(chara, 0);
    }

    Ai_PuppetNurse_UpdateMain(chara, arg1, coords);
}

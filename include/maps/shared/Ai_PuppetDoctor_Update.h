void Ai_PuppetDoctor_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_PuppetNurse_Init(chara, 1);
    }

    Ai_PuppetNurse_UpdateMain(chara, anmHdr, coords);
}

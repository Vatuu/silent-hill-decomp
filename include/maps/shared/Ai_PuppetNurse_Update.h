void Ai_PuppetNurse_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    // Initialize.
    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_PuppetNurse_Init(chara, false);
    }

    Ai_PuppetNurse_UpdateMain(chara, anmHdr, coords);
}

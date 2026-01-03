void Ai_PuppetNurse_Update(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    // Initialize.
    if (nurse->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_PuppetNurse_Init(nurse, false);
    }

    Ai_PuppetNurse_UpdateMain(nurse, anmHdr, coords);
}

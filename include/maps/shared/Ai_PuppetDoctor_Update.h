void Ai_PuppetDoctor_Update(s_SubCharacter* doctor, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    // Initialize.
    if (doctor->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_PuppetNurse_Init(doctor, true);
    }

    Ai_PuppetNurse_UpdateMain(doctor, anmHdr, coords);
}

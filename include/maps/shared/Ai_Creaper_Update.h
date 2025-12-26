void Ai_Creaper_Update(s_SubCharacter* creaper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    // Initialize.
    if (creaper->model_0.state_2 == ModelState_Uninitialized)
    {
        Ai_Creaper_Init(creaper);
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        sharedFunc_800D7EE8_1_s02(creaper);
        sharedFunc_800D8244_1_s02(creaper);
        sharedFunc_800D983C_1_s02(creaper);
    }

    sharedFunc_800D9960_1_s02(creaper, anmHdr, coords);
    sharedFunc_800D99D0_1_s02(creaper);
}

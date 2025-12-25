void Ai_Romper_Update(s_SubCharacter* romper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (romper->model_0.state_2 == ModelState_Uninitialized)
    {
        Ai_Romper_Init(romper);
    }
    else if (g_DeltaTime0 != Q12(0.0f))
    {
        sharedFunc_800E6420_2_s02(romper);
        sharedFunc_800E66E8_2_s02(romper);
        sharedFunc_800E8730_2_s02(romper);
        sharedFunc_800E8DFC_2_s02(romper);
    }

    sharedFunc_800E8A40_2_s02(romper, anmHdr, coords);
    sharedFunc_800E60FC_2_s02(romper);
}

void Ai_HangedScratcher_Update(s_SubCharacter* scratcher, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    // Initialize.
    if (scratcher->model_0.controlState_2 == HangedScratcherControl_None)
    {
        Ai_HangedScratcher_Init(scratcher);
    }

    sharedFunc_800CFF74_5_s00(scratcher);
    sharedFunc_800D029C_5_s00(scratcher);
    sharedFunc_800D26D8_5_s00(scratcher);
    sharedFunc_800D2844_5_s00(scratcher, anmHdr, coords);
    sharedFunc_800D2C18_5_s00(scratcher);
    sharedFunc_800D3300_5_s00(scratcher);
}

void Ai_LarvalStalker_Update(s_SubCharacter* larvalStalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s8* mapOverlayPtr;

    // Initialize.
    if (larvalStalker->model_0.state_2 == ModelState_Uninitialized)
    {
        Ai_LarvalStalker_Init(larvalStalker);
    }

    sharedFunc_800D17BC_1_s00(larvalStalker);
    sharedFunc_800CF168_1_s00(larvalStalker);
    sharedFunc_800D140C_1_s00(larvalStalker, coords);
    sharedFunc_800D1524_1_s00(larvalStalker, anmHdr, coords);
    sharedFunc_800D1DBC_1_s00(larvalStalker);

    if (larvalStalker->properties_E4.larvalStalker.timer_10A < Q12(3.5f))
    {
        return;
    }

    larvalStalker->timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
    if (larvalStalker->timer_C6 <= Q12(1.0f))
    {
        return;
    }

    // TODO: Weird hack, or a drunk developer.
    mapOverlayPtr = &g_SavegamePtr->mapOverlayId_A4;

    larvalStalker->timer_C6        = Q12(1.0f);
    larvalStalker->model_0.state_2 = 1;

    if (*mapOverlayPtr == 37 || Rng_GenerateInt(0, 3) == 0) // 1 in 4 chance.
    {
        func_80037DC4(larvalStalker);
    }
}

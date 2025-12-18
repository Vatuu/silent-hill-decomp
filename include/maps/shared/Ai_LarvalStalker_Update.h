void Ai_LarvalStalker_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s8* mapOverlayPtr;

    if (chara->model_0.state_2 == 0)
    {
        Ai_LarvalStalker_Init(chara);
    }

    sharedFunc_800D17BC_1_s00(chara);
    sharedFunc_800CF168_1_s00(chara);
    sharedFunc_800D140C_1_s00(chara, coords);
    sharedFunc_800D1524_1_s00(chara, anmHdr, coords);
    sharedFunc_800D1DBC_1_s00(chara);

    if (*((u16*)&chara->properties_E4.player.runTimer_108 + 1) < 0x3800)
    {
        return;
    }

    chara->timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);

    if (chara->timer_C6 <= Q12(1.0f))
    {
        return;
    }

    // TODO: Weird hack, or a drunk developer.
    mapOverlayPtr = &g_SavegamePtr->mapOverlayId_A4;

    chara->timer_C6        = Q12(1.0f);
    chara->model_0.state_2 = 1;

    if (*mapOverlayPtr == 37 || Rng_GenerateInt(0, 3) == 0) // 1 in 4 chance.
    {
        func_80037DC4(chara);
    }
}

void Ai_LarvalStalker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords)
{
    s8* mapOverlayPtr;

    if (chara->model_0.state_2 == 0)
    {
        Ai_LarvalStalker_Init(chara);
    }

    sharedFunc_800D17BC_1_s00(chara);
    sharedFunc_800CF168_1_s00(chara);
    sharedFunc_800D140C_1_s00(chara, coords);
    sharedFunc_800D1524_1_s00(chara, arg1, coords);
    sharedFunc_800D1DBC_1_s00(chara);

    if (*((u16*)&chara->properties_E4.player.properties_E4[9] + 1) < 0x3800)
    {
        return;
    }

    chara->timer_C6 += FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 0.25f, Q12_SHIFT);

    if (chara->timer_C6 <= FP_TO(1, Q12_SHIFT))
    {
        return;
    }

    // TODO: weird hack, or a drunk developer.
    mapOverlayPtr = &g_SavegamePtr->mapOverlayId_A4;

    chara->timer_C6        = FP_TO(1, Q12_SHIFT);
    chara->model_0.state_2 = 1;

    if (*mapOverlayPtr == 37 || !TEST_RNG(2))
    {
        func_80037DC4(chara);
    }
}

void Ai_HangedScratcher_Control_10(s_SubCharacter* scratcher)
{
    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_15 &&
        scratcher->moveSpeed_38 == Q12(0.0f) &&
        Rng_GenerateInt(0, 7) == 0) // 1 in 8 chance.
    {
        scratcher->model_0.controlState_2  = HangedScratcherControl_7;
        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
    }
}

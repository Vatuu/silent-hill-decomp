void Ai_HangedScratcher_Control_12(s_SubCharacter* scratcher)
{
    q19_12 animDur;
    q19_12 animDurScaled;

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 192, 199))
    {
        animDur       = HANGED_SCRATCHER_ANIM_INFOS[scratcher->model_0.anim_4.status_0].duration_8.constant;
        animDurScaled = (Q12_MULT_PRECISE(animDur, g_DeltaTime0) * Q12(0.7f)) / Q12(7.0f);

        scratcher->properties_E4.dummy.properties_E8[2].val16[0] += FP_FROM(animDurScaled * Math_Sin(scratcher->rotation_24.vy), Q12_SHIFT);
        scratcher->properties_E4.dummy.properties_E8[2].val16[1] += FP_FROM(animDurScaled * Math_Cos(scratcher->rotation_24.vy), Q12_SHIFT);
    }

    if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_13, true))
    {
        scratcher->flags_3E |= CharaFlag_Unk2;

        if (scratcher->health_B0 <= Q12(0.0f))
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_13;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_7, false);
        }
    }
}

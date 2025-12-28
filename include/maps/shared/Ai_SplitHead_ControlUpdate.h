void Ai_SplitHead_ControlUpdate(s_SubCharacter* splitHead)
{
    #define splitHeadProps splitHead->properties_E4.splitHead

    extern void (*g_Ai_SplitHead_ControlFuncs[])(s_SubCharacter* splitHead); // TODO: Add func table to this func.

    // Handle control state.
    splitHeadProps.flags_E8 &= ~SplitHeadFlag_3;
    g_Ai_SplitHead_ControlFuncs[splitHead->model_0.controlState_2](splitHead);

    if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, true))
    {
        splitHeadProps.animTime_F8 = splitHead->model_0.anim_4.time_4;
    }
    else if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, false))
    {
        splitHeadProps.animTime_F8 = Q12(201.0f);
    }

    #undef splitHeadProps
}

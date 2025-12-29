void Ai_HangedScratcher_ControlUpdate(s_SubCharacter* scratcher)
{
    s32 animStatus;

    animStatus = scratcher->model_0.anim_4.status_0;
    if (animStatus != ANIM_STATUS(HangedScratcherAnim_4, true) &&
        animStatus != ANIM_STATUS(HangedScratcherAnim_5, true))
    {
        scratcher->field_44.field_0 = 0;
    }

    // Handle control state.
    switch (scratcher->model_0.controlState_2)
    {
        case HangedScratcherControl_None:
            break;

        case HangedScratcherControl_1:
            Ai_HangedScratcher_Control_1(scratcher);
            break;

        case HangedScratcherControl_2:
            Ai_HangedScratcher_Control_2(scratcher);
            break;

        case HangedScratcherControl_3:
            Ai_HangedScratcher_Control_3(scratcher);
            break;

        case HangedScratcherControl_4:
            Ai_HangedScratcher_Control_4(scratcher);
            break;

        case HangedScratcherControl_5:
            Ai_HangedScratcher_Control_5(scratcher);
            break;

        case HangedScratcherControl_6:
            Ai_HangedScratcher_Control_6(scratcher);
            break;

        case HangedScratcherControl_7:
            Ai_HangedScratcher_Control_7(scratcher);
            break;

        case HangedScratcherControl_8:
            Ai_HangedScratcher_Control_8(scratcher);
            break;

        case HangedScratcherControl_9:
            Ai_HangedScratcher_Control_9(scratcher);
            break;

        case HangedScratcherControl_10:
            Ai_HangedScratcher_Control_10(scratcher);
            break;

        case HangedScratcherControl_11:
            Ai_HangedScratcher_Control_11(scratcher);
            break;

        case HangedScratcherControl_12:
            Ai_HangedScratcher_Control_12(scratcher);
            break;

        case HangedScratcherControl_13:
            Ai_HangedScratcher_Control_13(scratcher);
            break;

        case HangedScratcherControl_14:
            Ai_HangedScratcher_Control_14(scratcher);
            break;

        case HangedScratcherControl_15:
            Ai_HangedScratcher_Control_15(scratcher);
            break;

        case HangedScratcherControl_16:
            Ai_HangedScratcher_Control_16(scratcher);
            break;
    }
}

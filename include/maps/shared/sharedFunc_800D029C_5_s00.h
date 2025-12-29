void sharedFunc_800D029C_5_s00(s_SubCharacter* scratcher)
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
            sharedFunc_800D041C_5_s00(scratcher);
            break;

        case HangedScratcherControl_2:
            sharedFunc_800D0514_5_s00(scratcher);
            break;

        case HangedScratcherControl_3:
            sharedFunc_800D063C_5_s00(scratcher);
            break;

        case HangedScratcherControl_4:
            sharedFunc_800D0C44_5_s00(scratcher);
            break;

        case HangedScratcherControl_5:
            sharedFunc_800D0F04_5_s00(scratcher);
            break;

        case HangedScratcherControl_6:
            sharedFunc_800D10B8_5_s00(scratcher);
            break;

        case HangedScratcherControl_7:
            sharedFunc_800D1274_5_s00(scratcher);
            break;

        case HangedScratcherControl_8:
            sharedFunc_800D19AC_5_s00(scratcher);
            break;

        case HangedScratcherControl_9:
            sharedFunc_800D1AD0_5_s00(scratcher);
            break;

        case HangedScratcherControl_10:
            sharedFunc_800D1C0C_5_s00(scratcher);
            break;

        case HangedScratcherControl_11:
            sharedFunc_800D1CE4_5_s00(scratcher);
            break;

        case HangedScratcherControl_12:
            sharedFunc_800D1E84_5_s00(scratcher);
            break;

        case HangedScratcherControl_13:
            sharedFunc_800D2040_5_s00(scratcher);
            break;

        case HangedScratcherControl_14:
            sharedFunc_800D2180_5_s00(scratcher);
            break;

        case HangedScratcherControl_15:
            sharedFunc_800D23E0_5_s00(scratcher);
            break;

        case HangedScratcherControl_16:
            sharedFunc_800D03F8_5_s00(scratcher);
            break;
    }
}

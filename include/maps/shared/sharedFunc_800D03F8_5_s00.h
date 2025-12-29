void sharedFunc_800D03F8_5_s00(s_SubCharacter* scratcher)
{
    #define scratcherProps scratcher->properties_E4.hangedScratcher

    if (scratcherProps.field_104 != 0)
    {
        scratcher->model_0.controlState_2  = HangedScratcherControl_7;
        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
    }

    #undef scratcherProps
}

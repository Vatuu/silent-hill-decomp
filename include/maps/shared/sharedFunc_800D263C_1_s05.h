void sharedFunc_800D263C_1_s05(s_SubCharacter* splitHead)
{
    #define splitHeadProps splitHead->properties_E4.splitHead

    if (!Savegame_EventFlagGet(EventFlag_130))
    {
        return;
    }

    splitHead->model_0.controlState_2  = SplitHeadControl_2;
    splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_11, false);
    splitHeadProps.flags_E8           |= CharaUnk0Flag_Unk8;

    #undef splitHeadProps
}

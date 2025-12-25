void sharedFunc_800D263C_1_s05(s_SubCharacter* splitHead)
{
    if (Savegame_EventFlagGet(EventFlag_130))
    {
        splitHead->model_0.state_2                   = 2;
        splitHead->model_0.anim_4.status_0           = ANIM_STATUS(11, false);
        splitHead->properties_E4.splithead.flags_E8 |= CharaUnk0Flag_Unk8;
    }
}

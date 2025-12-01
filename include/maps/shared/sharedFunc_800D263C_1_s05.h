void sharedFunc_800D263C_1_s05(s_SubCharacter* splithead)
{
    if (Savegame_EventFlagGet(EventFlag_130))
    {
        splithead->model_0.state_2                   = 2;
        splithead->model_0.anim_4.status_0           = ANIM_STATUS(11, false);
        splithead->properties_E4.splitHead.flags_E8 |= CharaUnk0Flag_Unk8;
    }
}

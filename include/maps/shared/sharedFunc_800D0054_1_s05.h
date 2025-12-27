// Ai_SplitHead

void sharedFunc_800D0054_1_s05(s_SubCharacter* splitHead)
{
    extern void (*sharedData_800D5A68_1_s05[])(s_SubCharacter* splitHead); // TODO: Add func table to this func.

    splitHead->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 3);
    sharedData_800D5A68_1_s05[splitHead->model_0.state_2](splitHead);

    if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, true))
    {
        splitHead->properties_E4.player.runTimer_F8 = splitHead->model_0.anim_4.time_4;
    }
    else if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, false))
    {
        splitHead->properties_E4.player.runTimer_F8 = Q12(201.0f);
    }
}

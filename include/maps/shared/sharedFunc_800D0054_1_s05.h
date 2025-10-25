// Ai_Splithead

void sharedFunc_800D0054_1_s05(s_SubCharacter* splithead)
{
    extern void (*sharedData_800D5A68_1_s05[])(s_SubCharacter* splithead); // TODO: add func table to this func.

    splithead->properties_E4.larvalStalker.properties_E8[0].val16[0] &= ~(1 << 3);
    
    sharedData_800D5A68_1_s05[splithead->model_0.state_2](splithead);

    if (splithead->model_0.anim_4.status_0 == 23)
        splithead->properties_E4.player.runTimer_F8 = splithead->model_0.anim_4.time_4;
    else if(splithead->model_0.anim_4.status_0 == 22)
        splithead->properties_E4.player.runTimer_F8 = Q12(201.0f);
}

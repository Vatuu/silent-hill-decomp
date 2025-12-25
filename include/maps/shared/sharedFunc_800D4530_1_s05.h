bool sharedFunc_800D4530_1_s05(s_SubCharacter* splitHead)
{
    q19_12 timer;

    timer = splitHead->properties_E4.splitHead.timer_F8;
    return ((timer < Q12(0.0f) || timer > Q12(198.0f)) && splitHead->model_0.anim_4.time_4 < Q12(175.0f)) ||
           ((timer >= Q12(0.0f) && timer < Q12(175.0f)) && splitHead->model_0.anim_4.time_4 > Q12(198.0f));
}

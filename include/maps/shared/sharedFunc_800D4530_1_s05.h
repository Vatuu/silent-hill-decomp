bool sharedFunc_800D4530_1_s05(s_SubCharacter* splitHead)
{
    q19_12 animTime;

    #define splitHeadProps splitHead->properties_E4.splitHead

    animTime = splitHeadProps.animTime_F8;
    return ((animTime < Q12(0.0f) || animTime > Q12(198.0f)) && splitHead->model_0.anim_4.time_4 < Q12(175.0f)) ||
           ((animTime >= Q12(0.0f) && animTime < Q12(175.0f)) && splitHead->model_0.anim_4.time_4 > Q12(198.0f));

    #undef splitHeadProps
}

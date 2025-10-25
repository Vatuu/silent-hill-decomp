void sharedFunc_800D76A0_0_s01(s_SubCharacter* chara)
{
    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(23, true) ||
        chara->model_0.anim_4.status_0 == ANIM_STATUS(13, true) ||
        chara->model_0.anim_4.status_0 == ANIM_STATUS(14, true))
    {
        if (sharedFunc_800D77D0_0_s01(chara) != 0)
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(25, false);
        }
    }
    else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(25, true))
    {
        if (sharedFunc_800D77D0_0_s01(chara) == 0)
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
        }
    }
}

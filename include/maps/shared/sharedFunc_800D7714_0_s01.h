q19_12 sharedFunc_800D7714_0_s01(s_SubCharacter* chara)
{
    bool   cond;
    q19_12 ret;

    cond = chara->model_0.state_2 != 1;

    switch (chara->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(23, true):
            ret = Q12(30.0f);
            if (!cond)
            {
                ret = Q12(15.0f);
            }
            break;

        case ANIM_STATUS(19, false):
            ret = Q12(24.0f);
            if (!cond)
            {
                ret = Q12(30.0f);
            }
            break;

        case ANIM_STATUS(17, false):
            ret = Q12(40.0f);
            if (!cond)
            {
                ret = Q12(60.0f);
            }
            break;

        case ANIM_STATUS(24, false):
            ret = Q12(72.0f);
            if (!cond)
            {
                ret = Q12(30.0f);
            }
            break;

        case ANIM_STATUS(24, true):
            ret = Q12(40.0f);
            if (!cond)
            {
                ret = Q12(30.0f);
            }
            break;

        case ANIM_STATUS(15, false):
            ret = Q12(72.0f);
            if (!cond)
            {
                ret = Q12(30.0f);
            }
            break;

        case ANIM_STATUS(15, true):
            ret = Q12(18.0f);
            if (!cond)
            {
                ret = Q12(20.0f);
            }
            break;

        default:
            ret = Q12(10.0f);
    }

    return ret;
}

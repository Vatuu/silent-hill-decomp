void sharedFunc_800D76A0_0_s01(s_SubCharacter* airScreamer)
{
    if (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_23, true) ||
        airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_13, true) ||
        airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_14, true))
    {
        if (sharedFunc_800D77D0_0_s01(airScreamer) != Q12(0.0f))
        {
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_25, false);
        }
    }
    else if (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_25, true))
    {
        if (sharedFunc_800D77D0_0_s01(airScreamer) == Q12(0.0f))
        {
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_23, false);
        }
    }
}

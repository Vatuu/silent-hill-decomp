void sharedFunc_800D9528_1_s02(s_SubCharacter* creeper)
{
    q19_12 dist;

    if (creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_7, true))
    {
        if (creeper->rotation_24.vy != func_8005BF38(creeper->headingAngle_3C + FP_ANGLE(180.0f)))
        {
            if (func_8005BF38((creeper->headingAngle_3C + FP_ANGLE(180.0f)) - creeper->rotation_24.vy) > FP_ANGLE(0.0f))
            {
                creeper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
            else
            {
                creeper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
        }

        if (ANIM_TIME_RANGE_CHECK(creeper->model_0.anim_4.time_4, 50, 59))
        {
            dist = FP_MULTIPLY_PRECISE(CREEPER_ANIM_INFOS[creeper->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) / 9;
        }
        else
        {
            q19_12 baseDist = FP_MULTIPLY_PRECISE(CREEPER_ANIM_INFOS[creeper->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) * Q12(0.1f);
            dist            = baseDist / Q12(4.0f);
        }

        creeper->properties_E4.creeper.offsetX_EC = FP_MULTIPLY(dist, Math_Sin(creeper->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
        creeper->properties_E4.creeper.offsetZ_EE = FP_MULTIPLY(dist, Math_Cos(creeper->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
    }

    if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_3  ||
        ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_4  ||
        ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_14 ||
        ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_15)
    {
        creeper->model_0.state_2 = 5;
    }
}

void sharedFunc_800D9528_1_s02(s_SubCharacter* creaper)
{
    q19_12 dist;

    if (creaper->model_0.anim_4.status_0 == ANIM_STATUS(CreaperAnim_7, true))
    {
        if (creaper->rotation_24.vy != func_8005BF38(creaper->headingAngle_3C + FP_ANGLE(180.0f)))
        {
            if (func_8005BF38((creaper->headingAngle_3C + FP_ANGLE(180.0f)) - creaper->rotation_24.vy) > FP_ANGLE(0.0f))
            {
                creaper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
            else
            {
                creaper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
        }

        if (ANIM_TIME_RANGE_CHECK(creaper->model_0.anim_4.time_4, 50, 59))
        {
            dist = FP_MULTIPLY_PRECISE(CREAPER_ANIM_INFOS[creaper->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) / 9;
        }
        else
        {
            q19_12 baseDist = FP_MULTIPLY_PRECISE(CREAPER_ANIM_INFOS[creaper->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) * Q12(0.1f);
            dist            = baseDist / Q12(4.0f);
        }

        creaper->properties_E4.creaper.offsetX_EC = FP_MULTIPLY(dist, Math_Sin(creaper->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
        creaper->properties_E4.creaper.offsetZ_EE = FP_MULTIPLY(dist, Math_Cos(creaper->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
    }

    if (ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_3  ||
        ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_4  ||
        ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_14 ||
        ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_15)
    {
        creaper->model_0.state_2 = 5;
    }
}

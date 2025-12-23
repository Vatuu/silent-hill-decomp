void sharedFunc_800D9528_1_s02(s_SubCharacter* creaper)
{
    s32 var_s0;

    if (creaper->model_0.anim_4.status_0 == ANIM_STATUS(7, true))
    {
        if (creaper->rotation_24.vy != func_8005BF38(creaper->headingAngle_3C + FP_ANGLE(180.0f)))
        {
            if (func_8005BF38(creaper->headingAngle_3C + FP_ANGLE(180.0f) - creaper->rotation_24.vy) > FP_ANGLE(0.0f))
            {
                creaper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
            else
            {
                creaper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
        }

        if (FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT) >= 50 && FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT) < 60)
        {
            var_s0 = FP_MULTIPLY_PRECISE(CREAPER_ANIM_INFOS[creaper->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) / 9;
        }
        else
        {
            s32 temp_v0 = FP_MULTIPLY_PRECISE(CREAPER_ANIM_INFOS[creaper->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT) * Q12(0.1f);
            var_s0      = temp_v0 / Q12(4.0f);
        }

        creaper->properties_E4.dummy.properties_E8[1].val16[0] = FP_FROM(var_s0 * Math_Sin(creaper->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
        creaper->properties_E4.dummy.properties_E8[1].val16[1] = FP_FROM(var_s0 * Math_Cos(creaper->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
    }

    if (ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == 3  ||
        ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == 4  ||
        ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == 14 ||
        ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == 15)
    {
        creaper->model_0.state_2 = 5;
    }
}

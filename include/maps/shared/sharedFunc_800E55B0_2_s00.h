void sharedFunc_800E55B0_2_s00(s_SubCharacter* groaner)
{
    q3_12  timeScaled;
    s32    animTime;
    u32    animIdx;
    u8     newAnimStatus;

    #define groanerProps groaner->properties_E4.groaner

    if (!(groanerProps.flags_E8 & GroanerFlag_1))
    {
        Chara_MoveSpeedUpdate(groaner, Q12(1.8f));
    }

    if (!(groanerProps.flags_E8 & GroanerFlag_2))
    {
        groanerProps.flags_E8 &= ~GroanerFlag_4;
    }

    if (groaner->model_0.controlState_2 == GroanerControl_6)
    {
        if (ANIM_TIME_RANGE_CHECK(groaner->model_0.anim_4.time_4, 39, 48))
        {
            groanerProps.flags_E8 |= GroanerFlag_4;
        }

        if (groanerProps.flags_E8 & GroanerFlag_4)
        {
            // TODO: Uncleanr float.
            if (groanerProps.flags_E8 & GroanerFlag_5)
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 5.3333f, Q12_SHIFT);
            }
            else
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 3.2188f, Q12_SHIFT);
            }

            groanerProps.field_F0 = FP_FROM(timeScaled * Math_Sin(groaner->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            groanerProps.field_F2 = FP_FROM(timeScaled * Math_Cos(groaner->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
        }

        if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_4)
        {
            return;
        }
    }
    else
    {
        animTime = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT);
        if ((animTime >= 134 && animTime < 157) ||
            (animTime >= 288 && animTime < 311))
        {
            groanerProps.flags_E8 |= GroanerFlag_4;
        }

        if (groanerProps.flags_E8 & GroanerFlag_4)
        {
            if (groanerProps.flags_E8 & GroanerFlag_5)
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.6954f, Q12_SHIFT);
            }
            else
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.9781f, Q12_SHIFT);
            }

            if (groaner->model_0.controlState_2 == GroanerControl_7)
            {
                groanerProps.field_F0 = FP_MULTIPLY(timeScaled, Math_Sin(groaner->rotation_24.vy - FP_ANGLE(90.0f)), Q12_SHIFT);
                groanerProps.field_F2 = FP_MULTIPLY(timeScaled, Math_Cos(groaner->rotation_24.vy - FP_ANGLE(90.0f)), Q12_SHIFT);

                if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_8)
                {
                    return;
                }
            }
            else
            {
                groanerProps.field_F0 = FP_MULTIPLY(timeScaled, Math_Sin(groaner->rotation_24.vy + FP_ANGLE(90.0f)), Q12_SHIFT);
                groanerProps.field_F2 = FP_MULTIPLY(timeScaled, Math_Cos(groaner->rotation_24.vy + FP_ANGLE(90.0f)), Q12_SHIFT);

                if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_14)
                {
                    return;
                }
            }
        }
    }

    if (!(groanerProps.flags_E8 & GroanerFlag_2) && groaner->health_B0 == Q12(0.0f))
    {
        animIdx       = ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0);
        newAnimStatus = ANIM_STATUS((animIdx == GroanerAnim_4) ? GroanerAnim_1 : GroanerAnim_Still, false);
        groaner->flags_3E &= ~CharaFlag_Unk2;

        if (animIdx == GroanerAnim_8)
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_5, false);
        }
        if (animIdx == GroanerAnim_14)
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_11, false);
        }

        if (newAnimStatus != GroanerAnim_Still)
        {
            groanerProps.relKeyframeIdx_100 = 0;
            groaner->model_0.anim_4.status_0                               = newAnimStatus;
            groaner->model_0.controlState_2                                       = GroanerControl_9;
        }
    }

    #undef groanerProps
}

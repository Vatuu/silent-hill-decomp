void sharedFunc_800E55B0_2_s00(s_SubCharacter* groaner)
{
    q3_12  timeScaled;
    s32    animTime;
    u32    animStatusIdx;
    u8     newAnimStatus;

    // TODO: Wrong `properties_E4` union member used.

    if (!(groaner->properties_E4.splitHead.flags_E8 & (1 << 1)))
    {
        Chara_MoveSpeedUpdate(groaner, Q12(1.8f));
    }

    if (!(groaner->properties_E4.splitHead.flags_E8 & (1 << 2)))
    {
        groaner->properties_E4.splitHead.flags_E8 &= ~(1 << 4);
    }

    if (groaner->model_0.controlState_2 == 6)
    {
        if (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) >= 39 && FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) < 49)
        {
            groaner->properties_E4.splitHead.flags_E8 |= (1 << 4);
        }

        if (groaner->properties_E4.splitHead.flags_E8 & (1 << 4))
        {
            if (groaner->properties_E4.splitHead.flags_E8 & (1 << 5))
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 5.3333f, Q12_SHIFT);
            }
            else
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 3.2188f, Q12_SHIFT);
            }

            groaner->properties_E4.dummy.properties_E8[2].val16[0] = FP_FROM(timeScaled * Math_Sin(groaner->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            groaner->properties_E4.dummy.properties_E8[2].val16[1] = FP_FROM(timeScaled * Math_Cos(groaner->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
        }

        if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != 4)
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
            groaner->properties_E4.splitHead.flags_E8 |= (1 << 4);
        }

        if (groaner->properties_E4.splitHead.flags_E8 & (1 << 4))
        {
            if (groaner->properties_E4.splitHead.flags_E8 & (1 << 5))
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.6954f, Q12_SHIFT);
            }
            else
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.9781f, Q12_SHIFT);
            }

            if (groaner->model_0.controlState_2 == 7)
            {
                groaner->properties_E4.dummy.properties_E8[2].val16[0] = FP_FROM(timeScaled * Math_Sin(groaner->rotation_24.vy - FP_ANGLE(90.0f)), Q12_SHIFT);
                groaner->properties_E4.dummy.properties_E8[2].val16[1] = FP_FROM(timeScaled * Math_Cos(groaner->rotation_24.vy - FP_ANGLE(90.0f)), Q12_SHIFT);

                if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_8)
                {
                    return;
                }
            }
            else
            {
                groaner->properties_E4.dummy.properties_E8[2].val16[0] = FP_FROM(timeScaled * Math_Sin(groaner->rotation_24.vy + FP_ANGLE(90.0f)), Q12_SHIFT);
                groaner->properties_E4.dummy.properties_E8[2].val16[1] = FP_FROM(timeScaled * Math_Cos(groaner->rotation_24.vy + FP_ANGLE(90.0f)), Q12_SHIFT);

                if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_14)
                {
                    return;
                }
            }
        }
    }

    if (!(groaner->properties_E4.splitHead.flags_E8 & 4) && groaner->health_B0 == Q12(0.0f))
    {
        animStatusIdx    = ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0);
        newAnimStatus    = ANIM_STATUS((animStatusIdx == 4) ? 1 : 0, false);
        groaner->flags_3E &= ~CharaFlag_Unk2;

        if (animStatusIdx == GroanerAnim_8)
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_5, false);
        }
        if (animStatusIdx == GroanerAnim_14)
        {
            newAnimStatus = ANIM_STATUS(GroanerAnim_11, false);
        }

        if (newAnimStatus != GroanerAnim_Still)
        {
            groaner->properties_E4.dummy.properties_E8[6].val16[0] = 0;
            groaner->model_0.anim_4.status_0                               = newAnimStatus;
            groaner->model_0.controlState_2                                       = GroanerControl_9;
        }
    }
}

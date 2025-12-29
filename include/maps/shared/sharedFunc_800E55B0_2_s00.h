void sharedFunc_800E55B0_2_s00(s_SubCharacter* chara)
{
    q3_12  timeScaled;
    s32    animTime;
    u32    animStatusIdx;
    u8     newAnimStatus;

    // TODO: Wrong `properties_E4` union member used.

    if (!(chara->properties_E4.splitHead.flags_E8 & (1 << 1)))
    {
        Chara_MoveSpeedUpdate(chara, Q12(1.8f));
    }

    if (!(chara->properties_E4.splitHead.flags_E8 & (1 << 2)))
    {
        chara->properties_E4.splitHead.flags_E8 &= ~(1 << 4);
    }

    if (chara->model_0.controlState_2 == 6)
    {
        if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) >= 39 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 49)
        {
            chara->properties_E4.splitHead.flags_E8 |= (1 << 4);
        }

        if (chara->properties_E4.splitHead.flags_E8 & (1 << 4))
        {
            if (chara->properties_E4.splitHead.flags_E8 & (1 << 5))
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 5.3333f, Q12_SHIFT);
            }
            else
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 3.2188f, Q12_SHIFT);
            }

            chara->properties_E4.dummy.properties_E8[2].val16[0] = FP_FROM(timeScaled * Math_Sin(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
            chara->properties_E4.dummy.properties_E8[2].val16[1] = FP_FROM(timeScaled * Math_Cos(chara->rotation_24.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
        }

        if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != 4)
        {
            return;
        }
    }
    else
    {
        animTime = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
        if ((animTime >= 134 && animTime < 157) || (animTime >= 288 && animTime < 311))
        {
            chara->properties_E4.splitHead.flags_E8 |= (1 << 4);
        }

        if (chara->properties_E4.splitHead.flags_E8 & (1 << 4))
        {
            if (chara->properties_E4.splitHead.flags_E8 & (1 << 5))
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.6954f, Q12_SHIFT);
            }
            else
            {
                timeScaled = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.9781f, Q12_SHIFT);
            }

            if (chara->model_0.controlState_2 == 7)
            {
                chara->properties_E4.dummy.properties_E8[2].val16[0] = FP_FROM(timeScaled * Math_Sin(chara->rotation_24.vy - FP_ANGLE(90.0f)), Q12_SHIFT);
                chara->properties_E4.dummy.properties_E8[2].val16[1] = FP_FROM(timeScaled * Math_Cos(chara->rotation_24.vy - FP_ANGLE(90.0f)), Q12_SHIFT);

                if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != 8)
                {
                    return;
                }
            }
            else
            {
                chara->properties_E4.dummy.properties_E8[2].val16[0] = FP_FROM(timeScaled * Math_Sin(chara->rotation_24.vy + FP_ANGLE(90.0f)), Q12_SHIFT);
                chara->properties_E4.dummy.properties_E8[2].val16[1] = FP_FROM(timeScaled * Math_Cos(chara->rotation_24.vy + FP_ANGLE(90.0f)), Q12_SHIFT);

                if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != 14)
                {
                    return;
                }
            }
        }
    }

    if (!(chara->properties_E4.splitHead.flags_E8 & 4) && chara->health_B0 == Q12(0.0f))
    {
        animStatusIdx    = ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0);
        newAnimStatus    = ANIM_STATUS((animStatusIdx == 4) ? 1 : 0, false);
        chara->flags_3E &= ~CharaFlag_Unk2;

        if (animStatusIdx == 8)
        {
            newAnimStatus = ANIM_STATUS(5, false);
        }
        if (animStatusIdx == 14)
        {
            newAnimStatus = ANIM_STATUS(11, false);
        }

        if (newAnimStatus != 0)
        {
            chara->properties_E4.dummy.properties_E8[6].val16[0] = 0;
            chara->model_0.anim_4.status_0                               = newAnimStatus;
            chara->model_0.controlState_2                                       = 9;
        }
    }
}

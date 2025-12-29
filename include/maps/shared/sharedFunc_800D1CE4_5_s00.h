extern q19_12 sharedData_800DE28C_5_s00;

void sharedFunc_800D1CE4_5_s00(s_SubCharacter* scratcher)
{
    if (scratcher->properties_E4.hangedScratcher.flags_E8 & HangedScratchedFlag_0)
    {
        scratcher->field_34 += g_DeltaTime2 >> 1;

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 176, 184))
        {
            sharedData_800DE28C_5_s00 = Q12(10.0f);
        }
        else
        {
            sharedData_800DE28C_5_s00 = Q12(0.0f);
        }
    }
    else
    {
        Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

        if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_10)
        {
            if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 176, 185))
            {
                scratcher->model_0.anim_4.time_4        = Q12(186.0f);
                scratcher->model_0.anim_4.keyframeIdx_8 = 186;
            }

            sharedData_800DE28C_5_s00 = Q12(8.0f);
        }
    }

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 191, 193))
    {
        Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_12, true), 202);
        scratcher->rotation_24.vz = FP_ANGLE(0.0f);
        return;
    }

    if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_12, true))
    {
        scratcher->flags_3E |= CharaFlag_Unk2;

        if (scratcher->health_B0 <= Q12(0.0f))
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_13;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_6, false);
        }
    }
}

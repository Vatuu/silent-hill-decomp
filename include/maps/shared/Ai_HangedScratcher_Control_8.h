void Ai_HangedScratcher_Control_8(s_SubCharacter* scratcher)
{
    if (scratcher->properties_E4.hangedScratcher.flags_E8 & (1 << 0))
    {
        scratcher->field_34 += g_DeltaTime2 >> 1;

        if (FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT) == 259)
        {
            sharedData_800DE28C_5_s00 = Q12(0.0f);
        }
        else
        {
            sharedData_800DE28C_5_s00 = Q12(15.0f);
        }
    }
    else
    {
        sharedData_800DE28C_5_s00 = Q12(12.0f);
    }

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 245, 256))
    {
        // TODO: `TIMESTEP_SCALE(g_DeltaTime0, 45)` gives close match.
        // but uses `sra a0, a2, 0x6` instead of `sra a0, a2, 0x5`?
        scratcher->rotation_24.vz = MAX(0, scratcher->rotation_24.vz - ((g_DeltaTime0 * 45) / 68));
    }

    if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == 15)
    {
        scratcher->moveSpeed_38 = Q12(0.0f);

        if (scratcher->health_B0 > Q12(100.0f))
        {
            scratcher->model_0.controlState_2                 = 6;
            scratcher->properties_E4.hangedScratcher.field_EA = Q12(0.5f);
        }
        else
        {
            scratcher->model_0.controlState_2                  = 12;
            scratcher->model_0.anim_4.status_0                 = ANIM_STATUS(11, false);
            scratcher->properties_E4.hangedScratcher.unk_EC[2] = 31;
        }
    }
}

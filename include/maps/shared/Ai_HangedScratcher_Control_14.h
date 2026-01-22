void Ai_HangedScratcher_Control_14(s_SubCharacter* scratcher)
{
    s_Collision coll;
    VECTOR3     sfxPos;

    #define scratcherProps scratcher->properties_E4.hangedScratcher

    if ((scratcherProps.flags_E8 & HangedScratcherFlag_7) && 
        scratcher->model_0.anim_4.status_0 < ANIM_STATUS(HangedScratcherAnim_4, false))
    {
        HANGED_SCRATCHER_ANIM_INFOS[scratcher->model_0.anim_4.status_0].duration_8.constant = Q12(9.6f);
    }
    else
    {
        HANGED_SCRATCHER_ANIM_INFOS[scratcher->model_0.anim_4.status_0].duration_8.constant = Q12(0.0f);
    }

    if (FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT) == 51)
    {
        scratcher->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
    }
    else
    {
        scratcher->model_0.anim_4.flags_2 |= AnimFlag_Visible;
    }

    if (!(scratcherProps.flags_E8 & HangedScratcherFlag_6))
    {
        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 42, 44))
        {
            scratcherProps.flags_E8 |= HangedScratcherFlag_6;

            Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
            if (coll.field_8 == 11)
            {
                func_8005DC1C(Sfx_Unk1582, &scratcher->position_18, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1581, &scratcher->position_18, Q8(0.5f), 0);
            }
        }

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 84, 86))
        {
            scratcherProps.flags_E8 |= HangedScratcherFlag_6;

            sfxPos.vx = scratcher->position_18.vx;
            sfxPos.vy = scratcher->position_18.vy;
            sfxPos.vz = scratcher->position_18.vz + Q12(0.6f);

            Collision_Get(&coll, sfxPos.vx, sfxPos.vz);
            if (coll.field_8 == 11)
            {
                func_8005DC1C(Sfx_Unk1582, &sfxPos, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1581, &sfxPos, Q8(0.5f), 0);
            }
        }

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 94, 96))
        {
            scratcherProps.flags_E8 |= HangedScratcherFlag_6;

            sfxPos.vx = scratcher->position_18.vx;
            sfxPos.vy = scratcher->position_18.vy;
            sfxPos.vz = scratcher->position_18.vz - Q12(1.0f);

            Collision_Get(&coll, sfxPos.vx, sfxPos.vz);
            if (coll.field_8 == 11)
            {
                func_8005DC1C(Sfx_Unk1582, &sfxPos, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1581, &sfxPos, Q8(0.5f), 0);
            }
        }
    }

    if (!(scratcherProps.flags_E8 & HangedScratcherFlag_8) && 
        ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 52, 54))
    {
        scratcherProps.flags_E8 |= HangedScratcherFlag_8;
        
        sfxPos.vx = scratcher->position_18.vx;
        sfxPos.vy = scratcher->position_18.vy + Q12(0.5f);
        sfxPos.vz = scratcher->position_18.vz + Q12(1.5f);
        func_8005DC1C(Sfx_Unk1577, &sfxPos, Q8(0.5f), 0);
    }

    #undef scratcherProps
}

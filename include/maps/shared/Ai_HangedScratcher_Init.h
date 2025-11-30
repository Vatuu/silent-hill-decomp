void Ai_HangedScratcher_Init(s_SubCharacter* scratcher)
{
    s32 i;
    s64 healthbaseHard;
    s32 radiusMax;
    s32 radiusMin;

    scratcher->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    for (i = 0; i < 16; i++)
    {
        scratcher->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    scratcher->health_B0 = Q12(350.0f);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        // TODO: Weird health value, and not sure why `s64` is needed to match - maybe some `s64` multiply was optimized out?
        healthbaseHard       = Q12(472.44873f);
        scratcher->health_B0 = healthbaseHard;
    }

    scratcher->moveSpeed_38    = 0;
    scratcher->field_34        = 0;
    scratcher->headingAngle_3C = scratcher->rotation_24.vy;
    scratcher->rotation_24.vx  = 0;

    ModelAnim_AnimInfoSet(&scratcher->model_0.anim_4, HANGED_SCRATCHER_ANIM_INFOS);
    Chara_DamageClear(scratcher);

    switch (scratcher->model_0.stateStep_3)
    {
        case 3:
        case 9:
            if (scratcher->model_0.stateStep_3 == 3)
            {
                scratcher->model_0.state_2 = 2;
            }
            else if (scratcher->model_0.stateStep_3 == 7) // BUG: This will never run? Meant to be `== 9`?
            {
                scratcher->model_0.state_2 = 16;
            }
            else
            {
                scratcher->model_0.state_2 = 1;
            }

            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_Unk14, true), 222);
            scratcher->position_18.vy = Q12(-3.6f);
            scratcher->rotation_24.vz = FP_ANGLE(180.0f);

        default:
            break;

        case 7:
        case 14:
            scratcher->model_0.state_2 = 5;
            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_Unk15, true), 232);
            scratcher->position_18.vy = 0;
            scratcher->rotation_24.vz = 0;
            break;

        case 17:
            scratcher->properties_E4.larvalStalker.properties_E8[0].val16[1] = Q12(1.2f);

        case 6:
            scratcher->model_0.state_2 = 6;
            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_Unk15, true), 232);
            scratcher->position_18.vy = Q12(0.0f);
            scratcher->rotation_24.vz = FP_ANGLE(0.0f);
            break;

        case 18:
        case 19:
        case 20:
            scratcher->model_0.state_2 = 14;
            scratcher->position_18.vy  = Q12(0.0f);
            scratcher->rotation_24.vz  = FP_ANGLE(0.0f);

            switch (scratcher->model_0.stateStep_3)
            {
                case 18:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_Unk1, true), 0);
                    break;

                case 19:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_Unk2, true), 51);
                    break;

                case 20:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_Unk3, true), 87);
                    break;
            }
            break;
    }

    scratcher->properties_E4.larvalStalker.properties_E8[3].val32 = scratcher->position_18.vx;
    scratcher->properties_E4.larvalStalker.properties_E8[4].val32 = scratcher->position_18.vz;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        radiusMax = Q12(2.7f);
        radiusMin = Q12(2.4f);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        radiusMax = Q12(3.0f);
        radiusMin = Q12(2.8f);
    }
    else
    {
        radiusMax = Q12(3.8f);
        radiusMin = Q12(3.6f);
    }

    // TODO: Use `Rng_GenerateInt`.
    scratcher->properties_E4.larvalStalker.properties_E8[9].val16[0] = (Rng_Rand16() % (radiusMax >> 2)) + ((radiusMax * 3) >> 2);
    scratcher->properties_E4.larvalStalker.properties_E8[9].val16[1] = (Rng_Rand16() % (radiusMin >> 2)) + ((radiusMin * 3) >> 2);

    scratcher->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;
}

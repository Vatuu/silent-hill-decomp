void Ai_HangedScratcher_Init(s_SubCharacter* scratcher)
{
    s32    i;
    q51_12 healthBaseHard;
    q19_12 radiusMax;
    q19_12 radiusMin;

    scratcher->properties_E4.hangedScratcher.flags_E8 = 0;
    Chara_PropertiesClear(scratcher);

    scratcher->health_B0 = Q12(350.0f);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        // TODO: Weird health value, and not sure why `s64` is needed to match - maybe some `s64` multiply was optimized out?
        healthBaseHard       = Q12(472.44873f);
        scratcher->health_B0 = healthBaseHard;
    }

    scratcher->moveSpeed_38    = Q12(0.0f);
    scratcher->field_34        = Q12(0.0f);
    scratcher->headingAngle_3C = scratcher->rotation_24.vy;
    scratcher->rotation_24.vx  = FP_ANGLE(0.0f);

    ModelAnim_AnimInfoSet(&scratcher->model_0.anim_4, HANGED_SCRATCHER_ANIM_INFOS);
    Chara_DamageClear(scratcher);

    // Handle state step.
    switch (scratcher->model_0.stateStep_3)
    {
        case HangedScratcherStateStep_3:
        case HangedScratcherStateStep_9:
            if (scratcher->model_0.stateStep_3 == HangedScratcherStateStep_3)
            {
                scratcher->model_0.controlState_2 = HangedScratcherControl_2;
            }
            else if (scratcher->model_0.stateStep_3 == HangedScratcherStateStep_7) // @unused This will never run? Meant to be `HangedScratcherStateStep_9`?
            {
                scratcher->model_0.controlState_2 = HangedScratcherControl_16;
            }
            else
            {
                scratcher->model_0.controlState_2 = HangedScratcherControl_1;
            }

            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_14, true), 222);
            scratcher->position_18.vy = Q12(-3.6f);
            scratcher->rotation_24.vz = FP_ANGLE(180.0f);

        default:
            break;

        case HangedScratcherStateStep_7:
        case HangedScratcherStateStep_14:
            scratcher->model_0.controlState_2 = HangedScratcherControl_5;
            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_15, true), 232);
            scratcher->position_18.vy = Q12(0.0f);
            scratcher->rotation_24.vz = FP_ANGLE(0.0f);
            break;

        case HangedScratcherStateStep_17:
            scratcher->properties_E4.hangedScratcher.field_EA = Q12(1.2f);

        case HangedScratcherStateStep_6:
            scratcher->model_0.controlState_2 = HangedScratcherControl_6;
            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_15, true), 232);
            scratcher->position_18.vy = Q12(0.0f);
            scratcher->rotation_24.vz = FP_ANGLE(0.0f);
            break;

        case HangedScratcherStateStep_18:
        case HangedScratcherStateStep_19:
        case HangedScratcherStateStep_20:
            scratcher->model_0.controlState_2 = HangedScratcherControl_14;
            scratcher->position_18.vy = Q12(0.0f);
            scratcher->rotation_24.vz = FP_ANGLE(0.0f);

            switch (scratcher->model_0.stateStep_3)
            {
                case HangedScratcherStateStep_18:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_1, true), 0);
                    break;

                case HangedScratcherStateStep_19:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_2, true), 51);
                    break;

                case HangedScratcherStateStep_20:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_3, true), 87);
                    break;
            }
            break;
    }

    scratcher->properties_E4.hangedScratcher.positionX_F4 = scratcher->position_18.vx;
    scratcher->properties_E4.hangedScratcher.positionZ_F8 = scratcher->position_18.vz;

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
    scratcher->properties_E4.hangedScratcher.radiusMax_10C = (Rng_Rand16() % (radiusMax >> 2)) + ((radiusMax * 3) >> 2);
    scratcher->properties_E4.hangedScratcher.radiusMin_110= (Rng_Rand16() % (radiusMin >> 2)) + ((radiusMin * 3) >> 2);
    scratcher->flags_3E                                   |= CharaFlag_Unk9 | CharaFlag_Unk3;
}

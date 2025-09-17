void Ai_HangedScratcher_Init(s_SubCharacter* chara)
{
    s32 i;
    s64 healthHard;
    s32 var_s0;
    s32 var_s2;

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->health_B0 = Q12(350.0f);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        // TODO: Weird health value, and not sure why `s64` is needed to match - maybe some `s64` multiply was optimized out?
        healthHard       = Q12(472.44873f);
        chara->health_B0 = healthHard;
    }

    chara->moveSpeed_38    = 0;
    chara->field_34        = 0;
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->rotation_24.vx  = 0;

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, sharedData_800D91A0_5_s00);

    chara->damageReceived_C0 = Q12(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    switch (chara->model_0.stateStep_3)
    {
        case 3:
        case 9:
            if (chara->model_0.stateStep_3 == 3)
            {
                chara->model_0.state_2 = 2;
            }
            else if (chara->model_0.stateStep_3 == 7) // BUG: This will never run? Meant to be `== 9`?
            {
                chara->model_0.state_2 = 16;
            }
            else
            {
                chara->model_0.state_2 = 1;
            }

            Character_AnimSet(chara, ANIM_STATUS(14, true), 222);
            chara->position_18.vy = FP_METER(-3.6f);
            chara->rotation_24.vz = FP_ANGLE(180.0f);

        default:
            break;

        case 7:
        case 14:
            chara->model_0.state_2 = 5;
            Character_AnimSet(chara, ANIM_STATUS(15, true), 232);
            chara->position_18.vy = 0;
            chara->rotation_24.vz = 0;
            break;

        case 17:
            chara->properties_E4.larvalStalker.properties_E8[0].val16[1] = Q12(1.2f);

        case 6:
            chara->model_0.state_2 = 6;
            Character_AnimSet(chara, ANIM_STATUS(15, true), 232);
            chara->position_18.vy = FP_METER(0.0f);
            chara->rotation_24.vz = FP_ANGLE(0.0f);
            break;

        case 18:
        case 19:
        case 20:
            chara->model_0.state_2 = 14;
            chara->position_18.vy  = 0;
            chara->rotation_24.vz  = 0;

            switch (chara->model_0.stateStep_3)
            {
                case 18:
                    Character_AnimSet(chara, ANIM_STATUS(1, true), 0);
                    break;

                case 19:
                    Character_AnimSet(chara, ANIM_STATUS(2, true), 51);
                    break;

                case 20:
                    Character_AnimSet(chara, ANIM_STATUS(3, true), 87);
                    break;
            }
            break;
    }

    chara->properties_E4.larvalStalker.properties_E8[3].val32 = chara->position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[4].val32 = chara->position_18.vz;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        var_s0 = Q12(2.7f);
        var_s2 = Q12(2.4f);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        var_s0 = Q12(3.0f);
        var_s2 = Q12(2.8f);
    }
    else
    {
        var_s0 = Q12(3.8f);
        var_s2 = Q12(3.6f);
    }

    // TODO: Use `Rng_GenerateInt`.
    chara->properties_E4.larvalStalker.properties_E8[9].val16[0] = (Rng_Rand16() % (var_s0 >> 2)) + ((var_s0 * 3) >> 2);
    chara->properties_E4.larvalStalker.properties_E8[9].val16[1] = (Rng_Rand16() % (var_s2 >> 2)) + ((var_s2 * 3) >> 2);

    chara->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;
}

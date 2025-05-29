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

    chara->health_B0 = FP_TO(350, Q12_SHIFT);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        // TODO: Weird health value, and not sure why `s64` is needed to match - maybe some `s64` multiply was optimized out?
        healthHard       = FP_FLOAT_TO(472.44873f, Q12_SHIFT);
        chara->health_B0 = healthHard;
    }

    chara->moveSpeed_38    = 0;
    chara->field_34        = 0;
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->rotation_24.vx  = 0;

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, sharedData_800D91A0_5_s00);

    chara->field_C0 = 0;
    chara->field_BC = 0;
    chara->field_B8 = 0;
    chara->field_B4 = 0;

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
            chara->model_0.anim_4.animIdx_0      = 29;
            chara->model_0.anim_4.time_4         = FP_TO(222, Q12_SHIFT);
            chara->model_0.anim_4.keyframeIdx0_8 = 222;
            chara->position_18.vy                = FP_FLOAT_TO(-3.6f, Q12_SHIFT);
            chara->rotation_24.vz                = FP_ANGLE(180.0f);

        default:
            break;

        case 7:
        case 14:
            chara->model_0.state_2               = 5;
            chara->model_0.anim_4.animIdx_0      = 31;
            chara->model_0.anim_4.time_4         = FP_TO(232, Q12_SHIFT);
            chara->model_0.anim_4.keyframeIdx0_8 = 232;
            chara->position_18.vy                = 0;
            chara->rotation_24.vz                = 0;
            break;

        case 17:
            chara->properties_E4.larvalStalker.properties_E8[0].val16[1] = FP_FLOAT_TO(1.2f, Q12_SHIFT);

        case 6:
            chara->model_0.state_2               = 6;
            chara->model_0.anim_4.animIdx_0      = 31;
            chara->model_0.anim_4.time_4         = FP_TO(232, Q12_SHIFT);
            chara->model_0.anim_4.keyframeIdx0_8 = 232;
            chara->position_18.vy                = 0;
            chara->rotation_24.vz                = 0;
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
                    chara->model_0.anim_4.animIdx_0      = 3;
                    chara->model_0.anim_4.time_4         = 0;
                    chara->model_0.anim_4.keyframeIdx0_8 = 0;
                    break;

                case 19:
                    chara->model_0.anim_4.animIdx_0      = 5;
                    chara->model_0.anim_4.time_4         = FP_TO(51, Q12_SHIFT);
                    chara->model_0.anim_4.keyframeIdx0_8 = 51;
                    break;

                case 20:
                    chara->model_0.anim_4.animIdx_0      = 7;
                    chara->model_0.anim_4.time_4         = FP_TO(87, Q12_SHIFT);
                    chara->model_0.anim_4.keyframeIdx0_8 = 87;
                    break;
            }
            break;
    }

    chara->properties_E4.larvalStalker.properties_E8[3].val32 = chara->position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[4].val32 = chara->position_18.vz;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        var_s0 = FP_FLOAT_TO(2.7f, Q12_SHIFT);
        var_s2 = FP_FLOAT_TO(2.4f, Q12_SHIFT);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        var_s0 = FP_FLOAT_TO(3.0f, Q12_SHIFT);
        var_s2 = FP_FLOAT_TO(2.8f, Q12_SHIFT);
    }
    else
    {
        var_s0 = FP_FLOAT_TO(3.8f, Q12_SHIFT);
        var_s2 = FP_FLOAT_TO(3.6f, Q12_SHIFT);
    }

    chara->properties_E4.larvalStalker.properties_E8[9].val16[0] = ((s32)Rng_Rand16() % (var_s0 >> 2)) + ((var_s0 * 3) >> 2);
    chara->properties_E4.larvalStalker.properties_E8[9].val16[1] = ((s32)Rng_Rand16() % (var_s2 >> 2)) + ((var_s2 * 3) >> 2);

    chara->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;
}

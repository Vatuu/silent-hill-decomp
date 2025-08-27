// This inline allows getting rid of some ugly gotos, couldn't find a different way to handle it.
static inline void Ai_Creaper_PropertiesUpdateFromStep(s_SubCharacter* chara)
{
    s32 stateStep = chara->model_0.stateStep_3;
    if (chara->model_0.stateStep_3 != 3)
    {
        if (stateStep < 3)
        {
            return;
        }

        if (stateStep >= 14)
        {
            return;
        }

        if (stateStep < 12)
        {
            return;
        }

        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 4;
        chara->properties_E4.larvalStalker.properties_E8[5].val32 = chara->position_18.vx;
        chara->properties_E4.larvalStalker.properties_E8[6].val32 = chara->position_18.vz;
    }

    if (chara->model_0.stateStep_3 == 13 || chara->model_0.stateStep_3 == 3)
    {
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 6;
    }

    chara->model_0.state_2               = 1;
    chara->model_0.anim_4.animIdx_0      = 23;
    chara->model_0.anim_4.time_4         = FP_TO(94, Q12_SHIFT);
    chara->model_0.anim_4.keyframeIdx0_8 = 94;
}

void Ai_Creaper_Init(s_SubCharacter* chara)
{
    // TODO: Values used in the `Rng_Rand16` calls at the end, not sure of the actual purpose yet.
    #define BASE_EASY_VAL   0.7f
    #define BASE_NORMAL_VAL 0.9f
    #define BASE_HARD_VAL   1.2f
    #define RAND_EASY_MAX   0.2f
    #define RAND_NORMAL_MAX 0.2f
    #define RAND_HARD_MAX   0.4f

    s32 i;

    i = 0;

    // Checks if any other Creaper NPCs are also present, making sure to skip this `s_SubCharacter` instance in the NPC array.
    do
    {
        if (chara == &g_SysWork.npcs_1A0[i] || g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_Creaper)
        {
            i++;
            continue;
        }

        break;
    }
    while (i < NPC_COUNT_MAX);

    if (i == NPC_COUNT_MAX)
    {
        // No other Creapers present.
        sharedData_800E57CC_1_s02 = 0;
    }

    chara->health_B0                                             = FP_HEALTH(200.0f);
    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;
    chara->model_0.anim_4.keyframeIdx1_A                         = 0;
    chara->moveSpeed_38                                          = 0;
    chara->headingAngle_3C                                       = chara->rotation_24.vy;

    chara->field_E0_8 = 2;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    Ai_Creaper_PropertiesUpdateFromStep(chara);

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, sharedData_800E0D38_1_s02);

    chara->damageReceived_C0 = FP_HEALTH(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    chara->properties_E4.larvalStalker.properties_E8[3].val32 = chara->position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[4].val32 = chara->position_18.vz;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->properties_E4.larvalStalker.properties_E8[9].val16[0] = FP_MULTIPLY_FLOAT_PRECISE((FP_FLOAT_TO(BASE_EASY_VAL, Q12_SHIFT) + ((s32)Rng_Rand16() % FP_FLOAT_TO(RAND_EASY_MAX, Q12_SHIFT))), 2.0f, Q12_SHIFT);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        chara->properties_E4.larvalStalker.properties_E8[9].val16[0] = FP_MULTIPLY_FLOAT_PRECISE((FP_FLOAT_TO(BASE_NORMAL_VAL, Q12_SHIFT) + ((s32)Rng_Rand16() % FP_FLOAT_TO(RAND_NORMAL_MAX, Q12_SHIFT))), 2.0f, Q12_SHIFT);
    }
    else
    {
        chara->properties_E4.larvalStalker.properties_E8[9].val16[0] = FP_MULTIPLY_FLOAT_PRECISE((FP_FLOAT_TO(BASE_HARD_VAL, Q12_SHIFT) + ((s32)Rng_Rand16() % FP_FLOAT_TO(RAND_HARD_MAX, Q12_SHIFT))), 2.0f, Q12_SHIFT);
    }

#ifdef MAP5_S00
    chara->flags_3E |= CharaFlag_Unk9;
#endif
}

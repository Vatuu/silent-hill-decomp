// This inline allows getting rid of some ugly gotos, couldn't find a different way to handle it.
static inline void Ai_Creeper_PropertiesUpdateFromStep(s_SubCharacter* creeper)
{
    s32 stateStep;
    
    #define creeperProps creeper->properties_E4.creeper

    stateStep = creeper->model_0.stateStep_3;

    if (creeper->model_0.stateStep_3 != 3)
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

        creeperProps.flags_E8               |= CreeperFlag_4;
        creeperProps.prevTargetPositionX_FC  = creeper->position_18.vx;
        creeperProps.prevTargetPositionZ_100 = creeper->position_18.vz;
    }

    if (creeper->model_0.stateStep_3 == 13 || creeper->model_0.stateStep_3 == 3)
    {
        creeperProps.flags_E8 |= CreeperFlag_6;
    }

    creeper->model_0.state_2 = 1;
    Character_AnimSet(creeper, ANIM_STATUS(11, true), 94);

    #undef creeperProps
}

void Ai_Creeper_Init(s_SubCharacter* creeper)
{
    // TODO: Values used in the `Rng_Rand16` calls at the end, not sure of the actual purpose yet.
    #define BASE_EASY_VAL   0.7f
    #define BASE_NORMAL_VAL 0.9f
    #define BASE_HARD_VAL   1.2f
    #define RAND_EASY_MAX   0.2f
    #define RAND_NORMAL_MAX 0.2f
    #define RAND_HARD_MAX   0.4f

    s32 i;

    #define creeperProps creeper->properties_E4.creeper

    // Checks if any other Creeper NPCs are also present, making sure to skip this `s_SubCharacter` instance in the NPC array.
    i = 0;
    do
    {
        if (creeper == &g_SysWork.npcs_1A0[i] || g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_Creeper)
        {
            i++;
            continue;
        }

        break;
    }
    while (i < ARRAY_SIZE(g_SysWork.npcs_1A0));

    if (i == ARRAY_SIZE(g_SysWork.npcs_1A0))
    {
        // No other Creepers present.
        sharedData_800E57CC_1_s02 = 0;
    }

    creeper->health_B0              = Q12(200.0f);
    creeperProps.flags_E8           = CreeperFlag_None;
    creeper->model_0.anim_4.alpha_A = Q12(0.0f);
    creeper->moveSpeed_38           = Q12(0.0f);
    creeper->headingAngle_3C        = creeper->rotation_24.vy;
    creeper->field_E1_0             = 2;

    Chara_PropertiesClear(creeper);
    Ai_Creeper_PropertiesUpdateFromStep(creeper);
    ModelAnim_AnimInfoSet(&creeper->model_0.anim_4, CREEPER_ANIM_INFOS);
    Chara_DamageClear(creeper);

    creeperProps.targetPositionX_F4 = creeper->position_18.vx;
    creeperProps.targetPositionZ_F8 = creeper->position_18.vz;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        creeperProps.moveSpeed_10C = FP_MULTIPLY_FLOAT_PRECISE((Q12(BASE_EASY_VAL) + (Rng_Rand16() % Q12(RAND_EASY_MAX))), 2.0f, Q12_SHIFT);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        creeperProps.moveSpeed_10C = FP_MULTIPLY_FLOAT_PRECISE((Q12(BASE_NORMAL_VAL) + (Rng_Rand16() % Q12(RAND_NORMAL_MAX))), 2.0f, Q12_SHIFT);
    }
    else
    {
        creeperProps.moveSpeed_10C = FP_MULTIPLY_FLOAT_PRECISE((Q12(BASE_HARD_VAL) + (Rng_Rand16() % Q12(RAND_HARD_MAX))), 2.0f, Q12_SHIFT);
    }

#ifdef MAP5_S00
    creeper->flags_3E |= CharaFlag_Unk9;
#endif

    #undef BASE_EASY_VAL
    #undef BASE_NORMAL_VAL
    #undef BASE_HARD_VAL
    #undef RAND_EASY_MAX
    #undef RAND_NORMAL_MAX
    #undef RAND_HARD_MAX
    #undef creeperProps
}

void Ai_Groaner_Init(s_SubCharacter* chara)
{
    #define GROANER_BASE_HEALTH 210
    #define GROANER_RAND_MAX    70

    s32 i;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    chara->model_0.anim_4.keyframeIdx1_A = 0;

    chara->health_B0 = FP_TO(GROANER_BASE_HEALTH, Q12_SHIFT) + ((s32)Rng_Rand16() % FP_TO(GROANER_RAND_MAX, Q12_SHIFT));

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal && !TEST_RNG(3))
    {
        chara->health_B0 *= 2;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard && !TEST_RNG(2))
    {
        chara->health_B0 *= 2;
    }

    chara->moveSpeed_38    = 0;
    chara->field_E0_8      = 3;
    chara->headingAngle_3C = chara->rotation_24.vy;

    chara->properties_E4.larvalStalker.properties_E8[11].val16[0] = TEST_RNG(9) + 0xF00;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        chara->properties_E4.larvalStalker.properties_E8[11].val16[0] +=
            (u32)chara->properties_E4.larvalStalker.properties_E8[11].val16[0] / 8;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->properties_E4.larvalStalker.properties_E8[11].val16[0] -=
            ((s32)((u16)chara->properties_E4.larvalStalker.properties_E8[11].val16[0] << 16) >> 20); // (value * 0x10000) / 0x100000
    }

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, sharedData_800EEB14_2_s00);

    chara->damageReceived_C0 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    if (chara->model_0.stateStep_3 == 3)
    {
        chara->model_0.state_2                                        = 1;
        chara->model_0.anim_4.animIdx_0                               = 35;
        chara->model_0.anim_4.time_4                                  = FP_TO(371, Q12_SHIFT);
        chara->model_0.anim_4.keyframeIdx0_8                          = 371;
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 5;
    }

    chara->model_0.stateStep_3 = 0;

    chara->properties_E4.larvalStalker.properties_E8[3].val32 = chara->position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[4].val32 = chara->position_18.vz;

#ifdef MAP2_S00
    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard)
    {
        if (!(g_SavegamePtr->eventFlags_168[4] & (1 << 6)))
        {
            chara->properties_E4.larvalStalker.properties_E8[11].val16[0] = FP_MULTIPLY_FLOAT((s64)chara->properties_E4.larvalStalker.properties_E8[11].val16[0], 0.8f, Q12_SHIFT);
        }
        else
        {
            chara->properties_E4.larvalStalker.properties_E8[11].val16[0] = FP_MULTIPLY_FLOAT((s64)chara->properties_E4.larvalStalker.properties_E8[11].val16[0], 0.9f, Q12_SHIFT);
        }
    }
#endif
}

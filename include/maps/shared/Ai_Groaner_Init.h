void Ai_Groaner_Init(s_SubCharacter* chara)
{
    #define GROANER_HEALTH_BASE      QX_12(210.0f)
    #define GROANER_HEALTH_BONUS_MAX QX_12(70.0f)

    s32 i;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    chara->model_0.anim_4.alpha_A = QX_12(0.0f);

    chara->health_B0 = GROANER_HEALTH_BASE + (Rng_Rand16() % GROANER_HEALTH_BONUS_MAX);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal && !Rng_TestProbabilityBits(3))
    {
        chara->health_B0 *= 2;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard && !Rng_TestProbabilityBits(2))
    {
        chara->health_B0 *= 2;
    }

    chara->moveSpeed_38    = 0;
    chara->field_E0_8      = 3;
    chara->headingAngle_3C = chara->rotation_24.vy;

    chara->properties_E4.larvalStalker.properties_E8[11].val16[0] = Rng_TestProbabilityBits(9) + 0xF00;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        chara->properties_E4.larvalStalker.properties_E8[11].val16[0] += (u32)chara->properties_E4.larvalStalker.properties_E8[11].val16[0] / 8;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->properties_E4.larvalStalker.properties_E8[11].val16[0] -= ((s32)((u16)chara->properties_E4.larvalStalker.properties_E8[11].val16[0] << 16) >> 20); // (value * 0x10000) / 0x100000
    }

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, sharedData_800EEB14_2_s00);

    chara->damageReceived_C0 = QX_12(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    if (chara->model_0.stateStep_3 == 3)
    {
        chara->model_0.state_2 = 1;
        Character_AnimSet(chara, ANIM_STATUS(17, true), 371);
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 5;
    }

    chara->model_0.stateStep_3 = 0;

    chara->properties_E4.larvalStalker.properties_E8[3].val32 = chara->position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[4].val32 = chara->position_18.vz;

#ifdef MAP2_S00
    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard)
    {
        if (!Savegame_EventFlagGet(EventFlag_134))
        {
            chara->properties_E4.larvalStalker.properties_E8[11].val16[0] = FP_MULTIPLY_FLOAT_PRECISE(chara->properties_E4.larvalStalker.properties_E8[11].val16[0], 0.8f, Q12_SHIFT);
        }
        else
        {
            chara->properties_E4.larvalStalker.properties_E8[11].val16[0] = FP_MULTIPLY_FLOAT_PRECISE(chara->properties_E4.larvalStalker.properties_E8[11].val16[0], 0.9f, Q12_SHIFT);
        }
    }
#endif
}

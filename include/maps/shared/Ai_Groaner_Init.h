void Ai_Groaner_Init(s_SubCharacter* groaner)
{
    #define GROANER_HEALTH_BASE      Q12(210.0f)
    #define GROANER_HEALTH_BONUS_MAX Q12(70.0f)

    s32 i;

    for (i = 0; i < 16; i++)
    {
        groaner->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    groaner->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;
    groaner->model_0.anim_4.alpha_A = Q12(0.0f);

    groaner->health_B0 = GROANER_HEALTH_BASE + (Rng_Rand16() % GROANER_HEALTH_BONUS_MAX);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal && Rng_GenerateInt(0, 7) == 0)
    {
        groaner->health_B0 *= 2;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard && Rng_GenerateInt(0, 3) == 0)
    {
        groaner->health_B0 *= 2;
    }

    groaner->moveSpeed_38    = Q12(0.0f);
    groaner->field_E1_0      = 3;
    groaner->headingAngle_3C = groaner->rotation_24.vy;

    groaner->properties_E4.larvalStalker.properties_E8[11].val16[0] = Rng_TestProbabilityBits(9) + 0xF00;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        groaner->properties_E4.larvalStalker.properties_E8[11].val16[0] += (u32)groaner->properties_E4.larvalStalker.properties_E8[11].val16[0] / 8;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        groaner->properties_E4.larvalStalker.properties_E8[11].val16[0] -= ((s32)((u16)groaner->properties_E4.larvalStalker.properties_E8[11].val16[0] << 16) >> 20); // (value * 0x10000) / 0x100000
    }

    ModelAnim_AnimInfoSet(&groaner->model_0.anim_4, GROANER_ANIM_INFOS);
    Chara_DamageClear(groaner);

    if (groaner->model_0.stateStep_3 == 3)
    {
        groaner->model_0.state_2 = 1;
        Character_AnimSet(groaner, ANIM_STATUS(GroanerAnim_Unk17, true), 371);
        groaner->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 5;
    }

    groaner->model_0.stateStep_3 = 0;

    groaner->properties_E4.larvalStalker.properties_E8[3].val32 = groaner->position_18.vx;
    groaner->properties_E4.larvalStalker.properties_E8[4].val32 = groaner->position_18.vz;

#ifdef MAP2_S00
    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard)
    {
        if (!Savegame_EventFlagGet(EventFlag_134))
        {
            groaner->properties_E4.larvalStalker.properties_E8[11].val16[0] = FP_MULTIPLY_FLOAT_PRECISE(groaner->properties_E4.larvalStalker.properties_E8[11].val16[0], 0.8f, Q12_SHIFT);
        }
        else
        {
            groaner->properties_E4.larvalStalker.properties_E8[11].val16[0] = FP_MULTIPLY_FLOAT_PRECISE(groaner->properties_E4.larvalStalker.properties_E8[11].val16[0], 0.9f, Q12_SHIFT);
        }
    }
#endif
}

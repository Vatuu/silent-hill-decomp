void Ai_Romper_Init(s_SubCharacter* romper)
{
    #define ROMPER_HEALTH_BASE      Q12(450.0f)
    #define ROMPER_HEALTH_BONUS_MAX Q12(112.5f)

    s32 i;
    s32 temp_a0;
    s32 var_v0;

    romper->properties_E4.dummy.properties_E8[0].val32 = 0;
    romper->model_0.anim_4.alpha_A                             = Q12(0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        romper->health_B0 = ROMPER_HEALTH_BASE - ((s32)Rng_Rand16() % ROMPER_HEALTH_BONUS_MAX);
    }
    else
    {
        if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
        {
            romper->health_B0 = ROMPER_HEALTH_BASE + ((s32)Rng_Rand16() % ROMPER_HEALTH_BONUS_MAX);
        }
        else
        {
            var_v0 = (s32)Rng_Rand16();

            temp_a0 = var_v0;
            if (temp_a0 < Q12(0.0f))
            {
                var_v0 = temp_a0 + (Q12(0.5f) - 1);
            }

            // Shifts are equivalent to `var_v0_2 % Q12(0.5f)`.
            romper->health_B0 = FP_MULTIPLY_PRECISE(((temp_a0 - ((var_v0 >> 11) << 11)) + Q12(1.5f)), ROMPER_HEALTH_BASE, Q12_SHIFT);
        }
    }

    romper->moveSpeed_38    = Q12(0.0f);
    romper->field_E1_0      = 3;
    romper->headingAngle_3C = romper->rotation_24.vy;

    for (i = 0; i < 16; i++)
    {
        romper->properties_E4.dummy.properties_E8[i].val32 = 0;
    }

    romper->model_0.state_2 = 2;
    Character_AnimSet(romper, ANIM_STATUS(RomperAnim_15, true), 147);

    romper->properties_E4.dummy.properties_E8[2].val16[0] = 6;
    romper->properties_E4.dummy.properties_E8[2].val16[1] = romper->rotation_24.vy;

    romper->moveSpeed_38 = Q12(0.02175f);

    ModelAnim_AnimInfoSet(&romper->model_0.anim_4, ROPMER_ANIM_INFOS);

    Chara_DamageClear(romper);

    romper->properties_E4.dummy.properties_E8[5].val32 = romper->properties_E4.dummy.properties_E8[10].val32 = romper->position_18.vx;
    romper->properties_E4.dummy.properties_E8[6].val32 = romper->properties_E4.dummy.properties_E8[8].val32 = romper->position_18.vz;
}

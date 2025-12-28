void Ai_Romper_Init(s_SubCharacter* romper)
{
    #define ROMPER_HEALTH_BASE      Q12(450.0f)
    #define ROMPER_HEALTH_BONUS_MAX Q12(112.5f)

    s32 i;
    s32 temp_a0;
    s32 var_v0;

    #define romperProps romper->properties_E4.romper

    romperProps.field_E4 = 0;
    romper->model_0.anim_4.alpha_A = Q12(0.0f);

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
    Chara_PropertiesClear(romper);

    romper->model_0.state_2 = 2;
    Character_AnimSet(romper, ANIM_STATUS(RomperAnim_15, true), 147);

    romperProps.field_EC = 6;
    romperProps.rotationY_EE = romper->rotation_24.vy;
    romper->moveSpeed_38 = Q12(0.02175f);

    ModelAnim_AnimInfoSet(&romper->model_0.anim_4, ROPMER_ANIM_INFOS);
    Chara_DamageClear(romper);

    romperProps.positionX_F8  =
    romperProps.positionZ_10C = romper->position_18.vx;
    romperProps.positionZ_FC  =
    romperProps.positionX_104 = romper->position_18.vz;

    #undef ROMPER_HEALTH_BASE
    #undef ROMPER_HEALTH_BONUS_MAX
    #undef romperProps
}
